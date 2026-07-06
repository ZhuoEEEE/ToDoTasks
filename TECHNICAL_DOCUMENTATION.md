# ToDoTasks 技术文档

本文档面向后续维护者、二次开发者，以及希望了解实现细节的高级用户。普通安装和日常使用请先阅读 `README.md`。

## 1. 项目定位

ToDoTasks 是基于 `Quanto Flx Gadgets / ToDoList by Steve Hsu` 改造的 Rainmeter 桌面待办清单皮肤。当前版本保留原 Quanto Flx 的目录和配置体系，只在 ToDoList 这一组皮肤上做定向增强。

当前版本信息：

- 版本：`2.01 ZhuoEEEE`
- 改造与维护：`ZhuoEEEE`
- AI 协作：`Codex-gpt5.5`
- 原始来源：`Quanto Flx Gadgets / ToDoList by Steve Hsu`
- 许可：`CC BY-NC-SA 4.0 International`

当前功能边界：

- 支持 1 到 8 个独立 ToDoList 实例。
- 每个实例最多显示 8 条任务。
- 任务字段包含隐藏状态、强调状态、完成状态、标题、时间和备注。
- 主界面和设置界面使用黑色圆角背景，透明度由 `Op.Bg_Cstm` 控制。
- ToDoList 专用强调色由 `TaskAccentColor` 控制。
- 备注、排序、长标题显示、恢复默认和数量调整预览均为当前包的一部分。

## 2. 仓库结构

推荐 GitHub 仓库根目录结构：

```text
.
├─ ToDoTasks\
│  ├─ @Resources\
│  └─ ToDoList\
├─ README.md
├─ TECHNICAL_DOCUMENTATION.md
└─ LICENSE.md
```

Rainmeter 运行时只需要复制 `ToDoTasks` 文件夹到：

```text
%USERPROFILE%\Documents\Rainmeter\Skins\
```

`README.md`、`TECHNICAL_DOCUMENTATION.md` 和 `LICENSE.md` 是仓库文档，不需要复制到 Rainmeter 皮肤目录。

## 3. 入口文件

每个 ToDoList 实例位于：

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

职责如下：

- `CustomizableSize.ini`：主任务列表界面。
- `Settings.ini`：齿轮打开的设置界面。
- `Resizing.ini`：右下角调整数量时使用的预览界面。

这些 `.ini` 文件主要声明元信息和变量，然后 include 共享实现文件：

```ini
@include5=..\CustomizableSize.inc
@include5=..\SettingsSkin.inc
```

共享 Lua 脚本位于：

```text
ToDoTasks\@Resources\Scripts\ToDoList.lua
```

## 4. 元信息

Rainmeter 入口文件 `[Metadata]` 统一使用：

```ini
Author=ZhuoEEEE, Codex-gpt5.5 (based on Quanto Flx by Steve Hsu)
Version=2.01 ZhuoEEEE
License=CC BY-NC-SA 4.0 International (original license retained)
Information=Enhanced Rainmeter to-do list skin with dark rounded panels, notes, sorting, long-title handling, and fixed-width layout.
```

项目级元信息：

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

包级元信息：

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

`Pk.Wbst` 与 README 中的项目地址保持一致。

## 5. 配置和数据模型

用户当前任务和设置保存于：

```text
ToDoTasks\@Resources\Package\@\Config\SkinSettings\ToDoList\1.inc
...
ToDoTasks\@Resources\Package\@\Config\SkinSettings\ToDoList\8.inc
```

恢复默认模板保存于：

```text
ToDoTasks\@Resources\Package\@\Config\Default\ToDoList\1.inc
...
ToDoTasks\@Resources\Package\@\Config\Default\ToDoList\8.inc
```

每个任务槽字段：

```ini
EVENT___________0.Hdn=1
EVENT___________0.Clr=0
EVENT___________0.Cpd=0
EVENT___________0.Ttl=0
EVENT___________0.Tme=0
EVENT___________0.Nte=
```

字段含义：

- `.Hdn`：隐藏状态。`1` 为隐藏，`0` 为显示。
- `.Clr`：强调状态。
- `.Cpd`：完成状态。
- `.Ttl`：任务标题。
- `.Tme`：任务时间文本。
- `.Nte`：任务备注。

临时输入槽：

```ini
EVENT___________M.*
```

`M` 槽用于添加任务时暂存输入内容，然后写入可用任务槽。

当前默认设置：

```ini
Op.Bg_Cstm=0.5
PrvConfig=CustomizableSize.ini
Quantity=4
TaskAccentColor=247,99,12
```

这些默认值已同步到 `Default\ToDoList\1.inc` 到 `8.inc`，并由恢复默认逻辑再次强制写入，避免旧配置残留。

## 6. 主界面实现

主界面共享文件：

```text
ToDoTasks\ToDoList\CustomizableSize.inc
```

核心布局变量：

```ini
PW=5
RowH=64
RowS=32
TitleExtraH=18
TitleTextH=36
ListSlotH=(#RowH#+#TitleExtraH#)
PanelW=(64*#PW#)
PH=((#Quantity#*#ListSlotH#+64)/64)
```

主面板底层背景：

```ini
Shape=Rectangle 0,0,(64*#PW#*#sc#),(64*#PH#*#sc#),(#Cr#),(#Cr#) | #da.sk# | Fill Color 0,0,0,(255*#Op.Bg_Cstm#)
```

实现要点：

- 背景是独立底层 Shape，不影响文字和按钮透明度。
- 标题使用 `ClipString=2`，固定两行高度，并保留完整标题 tooltip。
- `TaskAccentColor` 同时驱动左侧强调条、完成按钮和强调按钮。
- 删除、备注、上移、下移等辅助按钮保持独立颜色，不跟随强调色。
- 滚动条 `[Mt.Srbr]` 默认 `Hidden=1`。
- 左上角页码使用 `PageStart` / `PageEnd` 显示当前可见任务范围。

## 7. 备注实现

备注字段为 `.Nte`，随任务一起保存和移动。备注编辑入口仍使用 Rainmeter 原生 `InputText`，对应 measure 命名：

```ini
Ms.NteEdit0
Ms.NteEdit1
...
Ms.NteEdit7
```

备注展示不是弹窗，而是在当前任务内部展开。展开/收起状态不写入配置文件，刷新后默认收起，避免污染用户数据。

相关变量：

```ini
Nte.Open0
Nte.Anim0
NoteH.Actual0
Nte.Y0
NteEdit.Y0
```

`ActionTimer` 负责逐帧调用 Lua：

```ini
[Ms.NteAn0]
Measure=Plugin
Plugin=ActionTimer
```

Lua 中的 `AnimateNote(slot, delta)` 改变 `Nte.Anim*`，`sync_layout()` 根据动画值重新计算行高和后续任务位置。

备注换行由 Lua 估算，不是浏览器级排版。相关函数包括：

- `wrap_lines(text, limit)`
- `note_limit()`
- `note_height(slot, limit)`

## 8. 排序实现

任务排序通过交换数据槽实现，不移动 meter 本身。

Lua 函数：

```lua
Swap(slot_a, slot_b)
```

交换字段：

```text
Hdn
Clr
Cpd
Ttl
Tme
Nte
```

第一条任务不显示上移按钮，最后一条任务不显示下移按钮。排序后会调用布局同步，确保备注展开高度和页码范围重新计算。

## 9. Lua 脚本职责

脚本文件：

```text
ToDoTasks\@Resources\Scripts\ToDoList.lua
```

主要职责：

- 读取和写入任务字段。
- 计算动态行高、备注高度、页码范围和滚动范围。
- 执行备注展开/收起动画。
- 处理任务上移/下移数据交换。
- 处理恢复默认并返回主界面。

关键函数：

- `Initialize()`：初始化并同步布局。
- `Update()`：Rainmeter 更新周期内同步布局。
- `Scroll(delta)`：滚动任务列表。
- `sync_layout(requested_index)`：核心布局计算。
- `ToggleNote(slot)`：切换备注展开状态。
- `OpenNote(slot)`：备注保存后自动展开。
- `EditNote(slot)`：打开备注输入。
- `AnimateNote(slot, delta)`：逐帧改变备注动画值。
- `Swap(slot_a, slot_b)`：交换相邻任务数据。
- `RestoreDefaults()`：恢复当前实例默认配置并激活 `CustomizableSize.ini`。

## 10. 设置界面

ToDoList 专用设置定义：

```text
ToDoTasks\ToDoList\SettingsSkin.inc
```

通用设置面板样式：

```text
ToDoTasks\@Resources\Config\Style\SkinSettings.inc
```

当前设置项：

- `Op.Bg_Cstm`：不透明度。
- `Quantity`：显示数量，范围 `1` 到 `8`。
- `TaskAccentColor`：强调色，颜色选择项。
- `Title`：清单标题。

恢复默认按钮由 ToDoList 覆盖通用动作：

```ini
ReDf.Action=[!CommandMeasure "Ms.ToDoList.ReDf" "RestoreDefaults()"]
```

脚本 measure：

```ini
[Ms.ToDoList.ReDf]
Measure=Script
ScriptFile=#@#Scripts\ToDoList.lua
```

通用设置面板中已删除或不再暴露的功能：

- 渐变背景设置。
- 样式复制。
- 样式粘贴。
- 帮助按钮。
- 组合功能入口。

这些功能对当前 ToDoList 的黑色背景方案没有实际价值，或原动作不完整，因此按“真正删除 UI 和引用”的方式处理。

## 11. 恢复默认逻辑

旧版默认配置曾出现 `PrvConfig=1x1.ini`，但当前 ToDoList 实例没有对应入口，导致恢复默认后确认按钮无法返回任务界面。

当前修复：

- 默认配置统一为 `PrvConfig=CustomizableSize.ini`。
- `RestoreDefaults()` 复制当前实例的默认配置。
- 恢复后强制写入：

```ini
Op.Bg_Cstm=0.5
Quantity=4
TaskAccentColor=247,99,12
```

- 最后激活：

```text
CustomizableSize.ini
```

这样恢复默认后应回到主任务界面，而不是停留在设置页或加载不存在的入口。

## 12. 数量调整预览

右下角调整数量使用 `Resizing.ini` 和通用样式：

```text
ToDoTasks\@Resources\Config\Style\Resizing.inc
```

ToDoList 当前任务槽高度不是旧版固定 `64`，而是：

```ini
ListSlotH=(#RowH#+#TitleExtraH#)
```

因此预览高度按 `ListSlotH` 动态计算，避免 6、7、8 条任务时预览框被旧高度裁切。

## 13. 编码注意

项目混用多种编码：

- 多数 Rainmeter `.ini` 和 `.inc` 文件为 `UTF-16 LE BOM`。
- Markdown 文档使用 `UTF-8`。
- Lua 脚本为普通文本。

维护时注意：

- 批量修改 `.ini` / `.inc` 时保持 `UTF-16 LE BOM`。
- 修改 UTF-16 文件后检查开头字节是否仍为 `FF FE`。
- 大型 `.inc` 文件保持原有格式，Rainmeter 配置依赖大量变量拼接和 include 顺序。

## 14. 发布检查

上传 GitHub 或制作 release zip 前检查：

1. 仓库根目录包含：

```text
ToDoTasks
README.md
TECHNICAL_DOCUMENTATION.md
LICENSE.md
```

2. 关键入口和脚本存在：

```text
ToDoTasks\ToDoList\1\CustomizableSize.ini
ToDoTasks\ToDoList\SettingsSkin.inc
ToDoTasks\ToDoList\CustomizableSize.inc
ToDoTasks\@Resources\Scripts\ToDoList.lua
ToDoTasks\@Resources\Config\Style\SkinSettings.inc
```

3. `Default\ToDoList\1.inc` 到 `8.inc` 保持：

```ini
Op.Bg_Cstm=0.5
PrvConfig=CustomizableSize.ini
Quantity=4
TaskAccentColor=247,99,12
```

4. `SkinSettings\ToDoList\1.inc` 到 `8.inc` 不应包含个人任务、测试备注或截图验证残留。

5. `EVENT___________0` 到 `EVENT___________7` 默认应隐藏，标题和时间为默认 `0`，备注为空。

6. 仓库中不包含本地 `.git` 嵌套目录、临时备份、验证截图或运行时个人数据。

7. 制作 zip 时压缩仓库根目录下的内容，不额外套一层本地工作目录名：

```text
ToDoTasks
README.md
TECHNICAL_DOCUMENTATION.md
LICENSE.md
```

## 15. 手动验证清单

发布前验证：

1. 将 `ToDoTasks` 复制到 Rainmeter `Skins` 目录。
2. Rainmeter 刷新全部。
3. 加载 `ToDoList\1\CustomizableSize.ini`。
4. 添加任务。
5. 输入长标题，确认标题显示两行且 tooltip 可查看完整文本。
6. 编辑备注，确认保存后可展开和收起。
7. 上移和下移任务，确认备注随任务移动。
8. 删除任务，确认下方任务补位且备注不串位。
9. 打开设置页，调整不透明度。
10. 调整数量和标题。
11. 修改强调色，确认任务强调条、完成按钮和强调按钮同步变化。
12. 使用右下角调整任务数量，确认预览高度随 `ListSlotH` 增加。
13. 恢复默认，确认能返回主任务界面，且默认值为 `Op.Bg_Cstm=0.5`、`Quantity=4`、`TaskAccentColor=247,99,12`。
14. 加载 `ToDoList\2` 到 `ToDoList\8` 任意实例，重复恢复默认返回测试。

## 16. 已知限制

- 备注输入仍使用 Rainmeter `InputText`，不是完整多行编辑器。
- 标题默认最多显示两行，极长内容依赖 tooltip 查看完整文本。
- 备注换行依赖 Lua 对字符宽度的估算，不是精确排版引擎。
- 备注动画由 Rainmeter `ActionTimer` 和 Lua 变量模拟，不是浏览器 CSS 动画。
- 当前许可继承原项目的 `CC BY-NC-SA 4.0`，不应擅自改成 MIT、Apache-2.0 等更宽松许可。

## 17. 维护注意事项

- 修改共享逻辑时优先改 `CustomizableSize.inc`、`SettingsSkin.inc`、`SkinSettings.inc` 或 `ToDoList.lua`，再确认 1 到 8 个入口是否只需 include。
- 改任务字段时，同步检查添加、删除、清空、恢复默认、排序逻辑。
- 改布局尺寸时，同时检查主界面、设置页和 Resizing 预览。
- 涉及用户数据的测试先备份 `SkinSettings\ToDoList\*.inc`。

## 18. 署名文本

README、发布页或 release 说明中的署名文本：

```text
Original Quanto Flx Gadgets / ToDoList by Steve Hsu.
Modified and maintained by ZhuoEEEE with Codex-gpt5.5.
Licensed under CC BY-NC-SA 4.0 International.
```
