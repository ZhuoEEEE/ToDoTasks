# ToDoTasks Rainmeter Skin

ToDoTasks 是一个 Windows 桌面待办清单 Rainmeter 皮肤，基于 `Quanto Flx Gadgets / ToDoList by Steve Hsu` 改造。当前包重点保留轻量桌面清单体验，并加入黑色圆角背景、长标题显示、任务备注、任务排序、专用强调色和更稳定的设置面板。

- 当前版本：`2.01 ZhuoEEEE`
- 改造与维护：`ZhuoEEEE`
- AI 协作：`Codex-gpt5.5`
- 许可：`CC BY-NC-SA 4.0 International`
- 项目地址：`https://github.com/ZhuoEEEE/ToDoTasks`

## 功能

- 1 到 8 个独立待办清单实例：`ToDoList\1` 到 `ToDoList\8`。
- 每个清单最多显示 8 条任务，默认显示 4 条。
- 支持添加、完成、强调、删除任务。
- 长标题默认占用两行显示；极长文本可通过鼠标悬停查看完整内容。
- 每条任务有独立备注，备注在任务内部展开和收起，不打开额外界面。
- 支持任务上移和下移，排序时会一起移动标题、时间、完成状态、强调状态和备注。
- 主界面、设置界面、数量调整预览统一为黑色圆角背景。
- 设置页“不透明度”只改变黑色背景深浅，不会让文字和图标一起透明。
- “完成”和“强调”按钮颜色跟随 ToDoList 专用强调色。
- 滚动条默认隐藏，列表范围通过左上角页码提示。
- 已删除对当前 ToDoList 无实际价值的渐变背景、复制/粘贴样式、帮助按钮和组合功能入口。

## 安装

1. 安装 [Rainmeter](https://www.rainmeter.net/)。
2. 下载本仓库，或下载发布包并解压。
3. 将仓库里的 `ToDoTasks` 文件夹复制到 Rainmeter 皮肤目录：

```text
C:\Users\<用户名>\Documents\Rainmeter\Skins\
```

复制完成后，目录应为：

```text
C:\Users\<用户名>\Documents\Rainmeter\Skins\ToDoTasks\
```

4. 打开 Rainmeter 管理器。
5. 点击“刷新全部”。
6. 展开 `ToDoTasks\ToDoList\1`。
7. 加载 `CustomizableSize.ini`。

需要多个清单时，可以继续加载 `ToDoList\2` 到 `ToDoList\8` 下的 `CustomizableSize.ini`。

## 使用

### 添加任务

点击主窗口底部的添加按钮，输入任务标题并确认。

### 完成、强调和删除

将鼠标悬停在任务行上，操作按钮会显示出来。可以标记完成、切换强调或删除任务。

### 编辑和展开备注

悬停任务行后，点击备注编辑按钮输入备注。保存后备注会写入该任务，并可通过备注展开按钮在任务内部展开或收起。

备注编辑复用 Rainmeter 的单行 `InputText`，但保存后的备注显示会在任务行内自动换行。

### 调整任务顺序

悬停任务行后，点击上移或下移按钮。第一条任务不会显示上移按钮，最后一条任务不会显示下移按钮。

### 调整显示数量

右下角缩放区可以调整当前清单显示的任务数量。也可以打开设置页，通过“数量”设置精确输入，范围为 `1` 到 `8`。

## 设置项

点击主窗口右上角齿轮打开设置页。当前 ToDoList 设置项如下：

- 不透明度：控制主界面和设置界面的黑色背景透明度。
- 数量：控制当前清单显示几条任务，默认 `4`。
- 强调色：控制任务强调条、完成按钮和强调按钮颜色，默认 `247,99,12`。
- 标题：修改当前清单标题。
- 恢复默认：恢复当前实例默认配置，并返回主任务界面。

Rainmeter 管理器的整窗透明度会同时影响文字和图标。背景深浅由皮肤设置页的“不透明度”控制，Rainmeter 管理器透明度保持 `0%`。

## 更新和备份

任务和当前设置保存在：

```text
ToDoTasks\@Resources\Package\@\Config\SkinSettings\ToDoList\
```

覆盖安装会替换该目录中的当前任务、备注、标题、显示数量、不透明度和强调色等个人配置。皮肤代码本身可以重新复制恢复。

恢复默认使用的模板保存在：

```text
ToDoTasks\@Resources\Package\@\Config\Default\ToDoList\
```

## 文件说明

```text
ToDoTasks\                     # 需要复制到 Rainmeter Skins 目录的皮肤文件夹
README.md                      # 普通用户安装和使用说明
TECHNICAL_DOCUMENTATION.md     # 实现、维护和发布说明
LICENSE.md                     # 许可与署名说明
```

普通使用只需要复制 `ToDoTasks` 文件夹。`README.md`、`TECHNICAL_DOCUMENTATION.md` 和 `LICENSE.md` 是 GitHub 仓库文档，不需要复制到 Rainmeter 皮肤目录。

## 常见问题

### Rainmeter 管理器里看不到皮肤

检查目录层级是否正确。正确路径应包含：

```text
Documents\Rainmeter\Skins\ToDoTasks\ToDoList\1\CustomizableSize.ini
```

如果路径变成下面这样，Rainmeter 通常不能按预期识别：

```text
Documents\Rainmeter\Skins\<外层文件夹>\ToDoTasks\...
```

只复制 `ToDoTasks` 文件夹；发布包外层目录不属于 Rainmeter 皮肤目录结构。

### 背景透明后文字也变透明

Rainmeter 管理器里的整窗透明度会影响全部内容。背景透明度通过齿轮设置页的“不透明度”调整。

### 备注或排序没有保存

确认 Rainmeter 对皮肤目录有写入权限。任务数据会写入：

```text
ToDoTasks\@Resources\Package\@\Config\SkinSettings\ToDoList\
```

## 许可与署名

本项目基于 `Quanto Flx Gadgets / ToDoList by Steve Hsu` 改造，保留原始皮肤的 `CC BY-NC-SA 4.0 International` 许可。

```text
Original Quanto Flx Gadgets / ToDoList by Steve Hsu.
Modified and maintained by ZhuoEEEE with Codex-gpt5.5.
Licensed under CC BY-NC-SA 4.0 International.
```

详细许可说明见 `LICENSE.md`。
