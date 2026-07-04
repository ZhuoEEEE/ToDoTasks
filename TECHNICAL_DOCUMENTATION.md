# ToDoTasks 技术文档

本文档记录 ToDoTasks Rainmeter 皮肤的目录结构、功能实现逻辑、操作逻辑、数据模型、UI 美化方案、发布检查和维护注意事项。它面向后续维护者、二次开发者，以及希望了解实现细节的高级用户。普通安装和日常使用请先阅读 `README.md`。

## 1. 项目概览

ToDoTasks 是一个 Rainmeter 桌面待办清单皮肤。当前版本基于 Quanto Flx Gadgets 中的 ToDoList 进行改造，保留 Rainmeter 原有的配置组织方式，同时加入一组更偏“实际任务管理”的功能。

当前版本信息：

- 版本：2.01 ZhuoEEEE
- 改造与维护：ZhuoEEEE
- AI 协作：Codex-gpt5.5
- 原始来源：Quanto Flx Gadgets / ToDoList by Steve Hsu
- 许可：CC BY-NC-SA 4.0 International

核心目标：

- 保留 Rainmeter 皮肤直接复制安装的低门槛。
- 保持原 Quanto Flx 配置体系可用。
- 将待办列表从简单事件记录扩展为可排序、可备注、可读长标题的桌面清单。
- 让主界面、设置界面、缩放预览在视觉上保持一致。

## 2. 仓库结构

上传到 GitHub 后，推荐仓库根目录结构如下：

```text
.
├─ ToDoTasks\
│  ├─ @Resources\
│  └─ ToDoList\
├─ README.md
├─ TECHNICAL_DOCUMENTATION.md
└─ LICENSE.md
```

Rainmeter 运行时只需要 `ToDoTasks` 文件夹。将它复制到：

```text
%USERPROFILE%\Documents\Rainmeter\Skins\
```

即可在 Rainmeter 管理器中加载。`README.md`、`TECHNICAL_DOCUMENTATION.md` 和 `LICENSE.md` 是仓库文档，不需要复制到 Rainmeter 皮肤目录中。

## 3. Rainmeter 入口结构

每个列表实例位于：

```text
ToDoTasks\ToDoList\1
ToDoTasks\ToDoList\2
...
ToDoTasks\ToDoList\8
```

每个实例包含三个主要入口：

```text
CustomizableSize.ini
Settings.ini
Resizing.ini
```

作用如下：

- `CustomizableSize.ini`：主任务列表界面。
- `Settings.ini`：齿轮进入的设置界面。
- `Resizing.ini`：调整任务数量时使用的预览/拖动界面。

这些入口 `.ini` 文件本身很薄，主要声明元信息和变量，然后 include 共享实现文件。

主界面 include：

```ini
@include5=..\CustomizableSize.inc
@include6=..\CustomizableSize.inc
```

设置界面 include：

```ini
@include5=..\SettingsSkin.inc
```

共享脚本：

```text
ToDoTasks\@Resources\Scripts\ToDoList.lua
```

## 4. 元信息与开源标识

Rainmeter 入口 `.ini` 的 `[Metadata]` 已统一为：

```ini
Author=ZhuoEEEE, Codex-gpt5.5 (based on Quanto Flx by Steve Hsu)
Version=2.01 ZhuoEEEE
License=CC BY-NC-SA 4.0 International (original license retained)
Information=Enhanced Rainmeter to-do list skin with dark rounded panels, notes, sorting, long-title handling, and fixed-width layout.
```

项目级元信息在：

```text
ToDoTasks\@Resources\Config\Meta.inc
```

关键变量：

```ini
Project.Vrsn=2.01
Project.VBld=1200
Project.VrSx=ZhuoEEEE
Project.Athr=ZhuoEEEE, Codex-gpt5.5 (based on Quanto Flx by Steve Hsu)
Project.Licn=CC BY-NC-SA 4.0 International
```

包级元信息在：

```text
ToDoTasks\@Resources\Package\@\Config\Meta.inc
```

关键变量：

```ini
Pk.Info=Enhanced Rainmeter to-do list skin for everyday task tracking.
Pk.Vrsn=2.01 ZhuoEEEE
Pk.VBld=1200
Pk.Athr=ZhuoEEEE, Codex-gpt5.5 (based on Quanto Flx by Steve Hsu)
Pk.Wbst=https://github.com/ZhuoEEEE/ToDoTasks
```

如果实际 GitHub 仓库地址不同，发布前只需要调整 `Pk.Wbst` 和 README 中相关链接。

## 5. 配置与数据模型

用户任务数据保存在：

```text
ToDoTasks\@Resources\Package\@\Config\SkinSettings\ToDoList\1.inc
...
ToDoTasks\@Resources\Package\@\Config\SkinSettings\ToDoList\8.inc
```

默认恢复数据保存在：

```text
ToDoTasks\@Resources\Package\@\Config\Default\ToDoList\1.inc
...
ToDoTasks\@Resources\Package\@\Config\Default\ToDoList\8.inc
```

每个任务槽使用同一组字段：

```ini
EVENT___________0.Hdn=1
EVENT___________0.Clr=0
EVENT___________0.Cpd=0
EVENT___________0.Ttl=0
EVENT___________0.Tme=0
EVENT___________0.Nte=
```

字段含义：

- `.Hdn`：是否隐藏。`1` 表示隐藏，`0` 表示显示。
- `.Clr`：星标/颜色状态。
- `.Cpd`：完成状态。
- `.Ttl`：任务标题。
- `.Tme`：任务创建或更新时间戳。
- `.Nte`：备注文本。

辅助槽：

```ini
EVENT___________M.*
```

用于添加任务时暂存输入内容，随后写入当前任务槽。

其他重要变量：

- `Op.Bg_Cstm`：背景不透明度，主窗口和设置窗口共用。
- `PrvConfig`：设置页确认后返回哪个界面。当前统一为 `CustomizableSize.ini`。
- `Quantity`：显示任务数量。
- `Title`：当前列表标题。
- `PrvIndex`：滚动/分页相关的上一次索引。

## 6. 主界面实现

主界面共享文件：

```text
ToDoTasks\ToDoList\CustomizableSize.inc
```

核心尺寸变量：

```ini
PW=5
RowH=64
RowS=32
NoteH=28
NoteLineH=16
NoteWrapUnits=13
NoteMaxLines=16
NoteX=40
NoteRightPad=20
TitleExtraH=18
TitleTextH=36
ListSlotH=(#RowH#+#TitleExtraH#)
PanelW=(64*#PW#)
TextW=(Max((#PanelW#-40-10-22-48-#TcMd#*(12+24+32)-8),80))
NoteW=(64*#PW#-#NoteX#-#NoteRightPad#)
PH=((#Quantity#*#ListSlotH#+64)/64)
```

含义：

- `PW=5`：固定面板宽度为 `64 * 5 = 320` 逻辑像素。
- `RowH=64`：每条任务基础高度。
- `RowS=32`：滚动计算步长。
- `NoteH=28`：备注抽屉基础高度。
- `NoteLineH=16`：备注显示时的单行高度。
- `NoteWrapUnits=13`：Lua 备注换行估算阈值，保持偏保守以避免 Rainmeter 单行省略。
- `NoteRightPad=20`：备注右侧安全留白。
- `TitleExtraH=18`：固定给标题预留第二行高度。
- `TitleTextH=36`：标题 meter 的固定两行显示高度。
- `PanelW`：所有主界面宽度计算的统一来源。
- `TextW`：任务标题可用文本宽度。
- `NoteW`：备注显示和备注输入框的可用宽度，当前略宽于标题区。

主界面改造重点：

- 主窗口加黑色圆角背景。
- 背景透明度由 `Op.Bg_Cstm` 控制。
- 保持 Rainmeter 管理器透明度为 `0%`，避免文字和图标一起透明。
- 标题默认支持两行显示。
- 超长标题通过 tooltip 查看完整内容。
- 设置齿轮位置与窗口右侧保持固定留白。

## 7. Lua 脚本职责

脚本位置：

```text
ToDoTasks\@Resources\Scripts\ToDoList.lua
```

Rainmeter measure：

```ini
[Ms.ToDoList]
Measure=Script
ScriptFile=#@#Scripts\ToDoList.lua
```

脚本主要负责动态布局和数据操作，避免在 `.inc` 中散落大量硬编码计算。

关键函数：

- `Initialize()`：初始化脚本并同步布局。
- `Update()`：Rainmeter 更新周期内同步布局。
- `Scroll(delta)`：滚动任务列表。
- `AnimateNote(slot, delta)`：逐步改变备注展开高度。
- `ToggleNote(slot)`：展开或收起备注抽屉。
- `OpenNote(slot)`：备注保存后自动展开。
- `EditNote(slot)`：打开备注输入框。
- `Swap(slot_a, slot_b)`：交换两个任务槽的完整数据。
- `sync_layout(requested_index)`：核心布局同步函数。

### 7.1 动态布局

`sync_layout()` 会根据以下内容计算界面：

- 当前滚动索引。
- 当前任务数量。
- 每条可见任务固定预留两行标题高度。
- 每条备注是否有内容。
- 备注展开动画值。
- 当前窗口可见范围。

它会写回 Rainmeter 变量，例如：

- `RowY0` 到 `RowY7`
- `RowH.Actual0` 到 `RowH.Actual7`
- `Ttl.Extra0` 到 `Ttl.Extra7`
- `Nte.Y0` 到 `Nte.Y7`
- `NteEdit.Y0` 到 `NteEdit.Y7`
- `NoteH.Actual0` 到 `NoteH.Actual7`
- `PageStart`
- `PageEnd`

这样 Rainmeter meter 只负责绘制，复杂计算集中在 Lua 中。

### 7.2 备注高度与换行

备注文本不是固定一行，而是根据文本宽度估算换行。

相关函数：

- `text_char(text, i)`：按 UTF-8 字符估算单字符显示宽度。
- `text_token(text, i)`：把连续英文数字作为整体 token，避免 `OpenCV`、`K230` 这类片段被从中间切开。
- `wrap_lines(text, limit)`：按宽度限制换行。
- `note_width()`：读取备注 meter 宽度；异常时按面板宽度兜底。
- `note_limit()`：根据 `NoteW` 和 `NoteWrapUnits` 计算备注换行阈值。
- `note_height(slot, limit)`：根据备注内容计算抽屉高度。

这种实现不是浏览器级排版，但能在 Rainmeter 的限制内避免备注溢出窗口。

### 7.3 任务排序

任务排序通过交换数据实现，不移动 meter 本身。

`Swap(slot_a, slot_b)` 交换字段：

```text
Hdn
Clr
Cpd
Ttl
Tme
Nte
```

因此上移/下移时，标题、完成状态、星标、时间和备注会一起移动。

## 8. 备注抽屉实现

备注功能涉及三层：

1. 数据层：`.Nte` 字段保存备注。
2. 输入层：`InputText` measure 写回 `.Nte`。
3. 展示层：备注 meter 根据动画变量展开或收起。

备注编辑入口在：

```text
ToDoTasks\ToDoList\CustomizableSize.inc
```

输入 measure 命名：

```ini
Ms.NteEdit0
Ms.NteEdit1
...
Ms.NteEdit7
```

备注展开不是弹窗，而是在当前任务行内部展开。这样用户可以保持上下文，不需要切换到另一个界面。

Rainmeter 没有网页那样的 CSS transition，因此“丝滑”效果通过 ActionTimer 和 Lua 变量逐帧模拟。

## 9. 设置界面实现

设置入口：

```ini
LeftMouseUpAction=#Ac.Skin_Settings#
```

设置页实例：

```text
ToDoTasks\ToDoList\1\Settings.ini
...
ToDoTasks\ToDoList\8\Settings.ini
```

ToDoList 专用设置定义：

```text
ToDoTasks\ToDoList\SettingsSkin.inc
```

通用设置页样式：

```text
ToDoTasks\@Resources\Config\Style\SkinSettings.inc
```

当前设置项：

- `Op.Bg_Cstm`：不透明度。
- `Quantity`：显示数量。
- `Title`：列表标题。

已经删除的设置功能：

- 渐变背景。
- 复制样式。
- 粘贴样式。
- 帮助按钮。
- 组合功能入口。

删除这些功能的原因是它们对 ToDoList 当前黑色背景方案没有实际价值，且部分按钮原本没有完整可用动作。

## 10. 恢复默认逻辑

恢复默认按钮调用：

```ini
[Ms.ReDfAction]
Measure=Plugin
Plugin=RunCommand
Parameter=xcopy "#Pk@#Config\Default\#Sk.Nm#.inc" "#CURRENTSKINSETTINGS#" /s /i /y /c /r
FinishAction=[!Delay 16][!SetOption "Mt.ReDf.01.01" "Text" "#Tm.Completed#"][!Update][!Redraw][!Delay 2000][!Refresh]
```

确认按钮返回：

```ini
LeftMouseUpAction=[!ZPos #DftZpos#][!KeepOnScreen 0][!ActivateConfig "#CURRENTCONFIG#" "#PrvConfig#"]
```

早期 `ToDoList\2` 到 `ToDoList\8` 的默认配置中 `PrvConfig=1x1.ini`，但对应目录没有 `1x1.ini`。这会导致恢复默认后确认无法回到任务列表。

当前修复：

```ini
PrvConfig=CustomizableSize.ini
```

该修复已同步到：

- `Config\Default\ToDoList\1.inc` 到 `8.inc`
- `Config\SkinSettings\ToDoList\1.inc` 到 `8.inc`

## 11. UI 美化方案

### 11.1 主窗口

主窗口使用黑色圆角背景：

- 黑色填充。
- 透明度由 `Op.Bg_Cstm` 控制。
- 与文字、图标分离，避免整窗透明造成内容发灰。
- 圆角与 resizing 预览一致。

### 11.2 设置窗口

设置窗口也使用同一套黑色背景和圆角。

第 8 轮修正中，设置页右上角按钮做了视觉统一：

- 确认按钮不再贴右边界。
- 恢复默认按钮不再贴右边界。
- 图标位置与主界面齿轮保持一致。
- hover 区域改为围绕图标的 `20x20` 区域，而不是贴边的 `32px` 工具栏块。

### 11.3 宽度统一

主窗口、设置窗口、缩放预览统一为：

```ini
PW=5
PanelW=320
```

目的：

- 避免第 8 条任务被裁切。
- 给长标题和备注留出更合理的空间。
- 让设置页标题、按钮和输入区域不拥挤。

### 11.4 任务数量调整预览

任务数量调整界面位于：

```text
ToDoTasks\ToDoList\1..8\Resizing.ini
```

它复用通用样式：

```text
ToDoTasks\@Resources\Config\Style\Resizing.inc
```

ToDoList 的任务高度已经不是旧版固定 `64`，而是：

```ini
TitleExtraH=18
ListSlotH=(#RowH#+#TitleExtraH#)
```

因此 `Resizing.ini` 的预览高度上限必须跟随 `ListSlotH`，当前使用：

```ini
Rsz.MusY=((64+#Quantity#*#ListSlotH#)*#sc#)
Rsz.MaxH=((64+#Rsz.MaxQ#*#ListSlotH#)/64)
Rsz.MinH=((64+#Rsz.MinQ#*#ListSlotH#)/64)
Rsz.CalcQ.Sub=(64*#sc#)
Rsz.CalcQ.Dvd=(#ListSlotH#*#sc#)
Rsz.MinQ=1
Rsz.MaxQ=8
```

按当前 `ListSlotH=82` 计算：

```text
6 个任务：64 + 6 * 82 = 556
7 个任务：64 + 7 * 82 = 638
8 个任务：64 + 8 * 82 = 720
```

这样预览框不会被旧的 `9 * 64 = 576` 高度裁剪，拖到 `6`、`7`、`8` 时高度应逐级增加。

### 11.5 色彩策略

当前视觉重点是工作型小工具，不做复杂装饰：

- 主色为黑色半透明面板。
- 文字保持高对比。
- 交互按钮悬停时出现。
- 不使用大面积渐变。
- 不使用额外弹窗承载备注。

## 12. 操作逻辑

### 12.1 添加任务

用户点击添加行后，Rainmeter 使用 `InputText` 获取标题。新任务写入当前可用槽，并清空临时槽。

新增任务会写入：

```text
Hdn=0
Clr=0
Cpd=0
Ttl=<用户输入>
Tme=<当前时间>
Nte=
```

### 12.2 删除任务

删除任务时会把下方任务逐个上移，最后一个槽清空。

清空时必须同步处理 `.Nte`，否则备注会残留到后续任务中。

### 12.3 完成和星标

完成和星标都是任务槽字段切换，不改变任务顺序。

### 12.4 上移和下移

上移/下移调用 `Swap()`。第一条不显示上移按钮，最后一条不显示下移按钮。

### 12.5 备注编辑

备注编辑复用 Rainmeter 的单行 `InputText`。保存后写入 `.Nte` 字段，并调用 `OpenNote(slot)` 展开备注。

限制：

- 输入体验不是多行编辑器。
- 多行显示依赖保存后的换行估算。

### 12.6 滚动

当任务数量或备注展开高度超过可视范围时，Lua 根据 `Index` 和可视高度计算当前页起止范围。

右上角页码使用：

```text
PageStart
PageEnd
```

避免出现超过任务总数的范围。

## 13. 编码规范和文件格式

这个项目混用了不同编码：

- 多数 Rainmeter `.ini` 和 `.inc` 是 UTF-16 LE BOM。
- `ToDoTasks\@Resources\Package\@\Config\Meta.inc` 是 UTF-8。
- Lua 脚本是普通文本。
- Markdown 文档使用 UTF-8。

维护时要特别注意：

- 不要用会破坏 UTF-16 BOM 的编辑方式批量改 Rainmeter 配置。
- 修改 UTF-16 文件后，应检查开头字节是否仍为 `FF FE`。
- 不要随意格式化整份 `.inc` 文件，Rainmeter 配置依赖大量变量拼接。

## 14. 发布默认数据

仓库内的 `SkinSettings\ToDoList\1.inc` 到 `8.inc` 已清理为无个人任务数据。

默认状态：

- 背景透明度：`Op.Bg_Cstm=0.5`
- 返回目标：`PrvConfig=CustomizableSize.ini`
- 显示数量：`Quantity=3`
- 任务槽：全部隐藏；标题和时间使用默认 `0`，备注为空
- 备注字段：全部为空

用户安装后产生的任务数据仍保存在 `SkinSettings` 目录中。更新版本前建议备份该目录。

## 15. 发布前检查

上传到 GitHub 或制作 release zip 前，建议检查：

1. 仓库根目录包含：

```text
ToDoTasks
README.md
TECHNICAL_DOCUMENTATION.md
LICENSE.md
```

2. Rainmeter 入口和脚本存在：

```text
ToDoTasks\ToDoList\1\CustomizableSize.ini
ToDoTasks\@Resources\Scripts\ToDoList.lua
ToDoTasks\@Resources\Config\Style\SkinSettings.inc
```

3. 默认任务数据不包含个人任务、测试备注或截图验证残留。
4. `SkinSettings\ToDoList\1.inc` 到 `8.inc` 的默认状态保持：

```text
Op.Bg_Cstm=0.5
PrvConfig=CustomizableSize.ini
Quantity=3
```

5. `EVENT___________0` 到 `EVENT___________7` 默认隐藏，标题和时间为默认 `0`，备注为空。
6. 仓库中不要上传 `.git` 嵌套目录、临时备份、验证截图或运行时个人数据。
7. GitHub 新建仓库时不要自动生成 README 或 license；本仓库已经提供 `README.md` 和 `LICENSE.md`。
8. `ToDoList\1..8\Resizing.ini` 中的 `Rsz.MinH` / `Rsz.MaxH` 应跟随 `ListSlotH` 动态计算，不应回到旧的固定 `2` / `9`。
9. 如果制作 zip 发布包，压缩仓库根目录下的这几项内容，不要额外套一层本地工作目录名：

```text
ToDoTasks
README.md
TECHNICAL_DOCUMENTATION.md
LICENSE.md
```

## 16. 建议测试清单

发布前建议手动验证：

1. 将 `ToDoTasks` 复制到 Rainmeter `Skins` 目录。
2. Rainmeter 刷新全部。
3. 加载 `ToDoList\1\CustomizableSize.ini`。
4. 添加任务。
5. 编辑长标题并确认 tooltip 可查看完整标题。
6. 编辑备注并展开/收起。
7. 上移/下移任务，确认备注随任务移动。
8. 删除任务，确认下方任务补位且备注不串位。
9. 打开设置页，调整不透明度。
10. 修改数量和标题。
11. 使用右下角拖拉调整任务数量，确认 `6`、`7`、`8` 的预览高度逐级增加。
12. 恢复默认并确认能返回主列表。
13. 加载 `ToDoList\2` 到 `ToDoList\8` 任意实例，重复恢复默认返回测试。

## 17. 已知限制

- 备注输入仍使用 Rainmeter `InputText`，不是完整多行编辑器。
- 标题主行默认最多两行，超长内容通过 tooltip 查看。
- 备注换行依赖 Lua 对 Rainmeter 字体宽度的估算，已保守处理中英文混排，但不是精确排版引擎。
- 备注动画由 Rainmeter ActionTimer 和 Lua 变量模拟，不是浏览器 CSS 动画。
- 许可继承原项目的 CC BY-NC-SA 4.0，不适合改成 MIT 等更宽松许可，除非获得原作者额外授权。
- `Pk.Wbst` 当前按 `https://github.com/ZhuoEEEE/ToDoTasks` 填写，如果实际仓库名不同，发布前应修改。

## 18. 维护建议

- 先改共享文件，再同步到 1 到 8 个实例入口。
- 改任务数据字段时，必须同时更新添加、删除、清空、恢复默认、排序逻辑。
- 改设置页时，优先检查 `SettingsSkin.inc` 和 `SkinSettings.inc` 的职责边界。
- 改布局尺寸时，同时检查主界面、设置页和 Resizing 预览；如果 `ListSlotH` 改变，必须确认 `Rsz.MinH` / `Rsz.MaxH` 仍按当前行高计算。
- 任何涉及用户数据的测试都应先备份 `SkinSettings\ToDoList\*.inc`。
- 每完成一个稳定功能点，建议创建本地 git commit。

## 19. 关键文件索引

```text
ToDoTasks\ToDoList\CustomizableSize.inc
```

主任务列表 UI、任务行、按钮、输入框、备注 meter、背景层。

```text
ToDoTasks\@Resources\Scripts\ToDoList.lua
```

动态布局、备注高度计算、滚动、备注展开、排序。

```text
ToDoTasks\ToDoList\SettingsSkin.inc
```

ToDoList 设置项定义。

```text
ToDoTasks\@Resources\Config\Style\SkinSettings.inc
```

通用设置面板 UI 样式和恢复默认弹窗。

```text
ToDoTasks\ToDoList\1..8\CustomizableSize.ini
```

八个主列表实例入口。

```text
ToDoTasks\@Resources\Package\@\Config\SkinSettings\ToDoList\1..8.inc
```

用户当前任务和设置数据。

```text
ToDoTasks\@Resources\Package\@\Config\Default\ToDoList\1..8.inc
```

恢复默认使用的数据。

## 20. 署名建议

GitHub README、发布页或说明中建议保留以下署名：

```text
Original Quanto Flx Gadgets / ToDoList by Steve Hsu.
Modified and maintained by ZhuoEEEE with Codex-gpt5.5.
Licensed under CC BY-NC-SA 4.0 International.
```

这既保留原始来源，也明确当前版本的改造者和 AI 协作信息。
