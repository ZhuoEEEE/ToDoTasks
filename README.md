# ToDoTasks Rainmeter Skin

ToDoTasks 是一个 Windows 桌面待办清单 Rainmeter 皮肤，基于 Quanto Flx Gadgets 的 ToDoList 改造。它适合把常用任务固定在桌面上，快速添加、完成、备注和排序。

当前版本加入了黑色圆角背景、可调背景透明度、两行标题显示、任务备注、任务上移/下移排序，以及更统一的设置面板。

## 预览功能

- 1 到 8 个独立待办清单实例。
- 每个清单最多显示 8 条任务。
- 添加、完成、星标、删除任务。
- 任务上移、下移排序。
- 每条任务都有独立备注。
- 备注在任务行内部展开和收起，不打开额外窗口。
- 长标题默认显示两行，超长内容可通过鼠标悬停查看完整文本。
- 主界面和设置界面使用黑色圆角背景。
- 设置页的不透明度只影响背景，不会让文字和图标一起变透明。

## 安装

1. 安装 [Rainmeter](https://www.rainmeter.net/)。
2. 下载本仓库，或下载发布包并解压。
3. 将仓库中的 `ToDoTasks` 文件夹复制到 Rainmeter 皮肤目录：

```text
C:\Users\<你的用户名>\Documents\Rainmeter\Skins\
```

复制完成后，目录应该是：

```text
C:\Users\<你的用户名>\Documents\Rainmeter\Skins\ToDoTasks\
```

4. 打开 Rainmeter 管理器。
5. 点击“刷新全部”。
6. 展开：

```text
ToDoTasks\ToDoList\1
```

7. 加载：

```text
CustomizableSize.ini
```

需要多个清单时，可以继续加载 `ToDoList\2` 到 `ToDoList\8` 下的 `CustomizableSize.ini`。

## 使用

### 添加任务

点击主窗口底部的添加按钮，输入任务标题并确认。

### 完成、星标和删除

将鼠标悬停在任务上，会显示操作按钮。可以完成任务、标记星标或删除任务。

### 编辑备注

将鼠标悬停在任务上，点击备注编辑按钮，输入备注内容并确认。备注会保存在对应任务中。

### 展开或收起备注

将鼠标悬停在任务上，点击备注切换按钮。备注会在当前任务下方展开或收起。

### 调整任务顺序

将鼠标悬停在任务上，点击上移或下移按钮。排序会交换相邻任务的完整数据，包括标题、时间、完成状态、星标状态和备注。

第一条任务不会显示上移按钮，最后一条任务不会显示下移按钮。

### 打开设置

点击主窗口右上角齿轮图标。

设置页可以调整：

- 不透明度：调整黑色背景深浅。
- 数量：调整当前清单显示的任务数量。
- 标题：修改当前清单标题。
- 恢复默认：恢复当前清单默认配置。

## 更新

如果你已经安装过旧版本，建议先退出 Rainmeter 或卸载当前 ToDoTasks 皮肤，再覆盖文件。

任务和设置保存在：

```text
ToDoTasks\@Resources\Package\@\Config\SkinSettings\ToDoList\
```

如果你想保留旧任务，请先备份这个文件夹，再覆盖新版 `ToDoTasks`。

## 常见问题

### Rainmeter 管理器里看不到皮肤

请检查目录层级。正确路径应该包含：

```text
Documents\Rainmeter\Skins\ToDoTasks\ToDoList\1\CustomizableSize.ini
```

如果路径变成下面这样，Rainmeter 不会按预期识别：

```text
Documents\Rainmeter\Skins\<外层文件夹>\ToDoTasks\...
```

只需要复制 `ToDoTasks` 文件夹，不要把整个发布包文件夹复制进 `Skins`。

### 文字和图标也变透明了

不要使用 Rainmeter 管理器的整窗透明度。请点击皮肤右上角齿轮，在设置页调整“不透明度”。这个选项只改变黑色背景深浅。

### 备注或排序没有保存

确认 Rainmeter 对皮肤目录有写入权限。任务数据会写入 `@Resources\Package\@\Config\SkinSettings\ToDoList` 下的配置文件。

## 文件说明

```text
ToDoTasks\                     # Rainmeter 需要复制安装的皮肤文件夹
README.md                      # 用户使用说明
TECHNICAL_DOCUMENTATION.md     # 开发和维护文档
LICENSE.md                     # 许可与署名说明
```

普通用户只需要安装 `ToDoTasks` 文件夹。想继续改造皮肤时，可以阅读 `TECHNICAL_DOCUMENTATION.md`。

## 许可与署名

本项目基于 Quanto Flx Gadgets / ToDoList by Steve Hsu 改造，保留原始皮肤的 `CC BY-NC-SA 4.0 International` 许可。

```text
Original Quanto Flx Gadgets / ToDoList by Steve Hsu.
Modified and maintained by ZhuoEEEE with Codex-gpt5.5.
Licensed under CC BY-NC-SA 4.0 International.
```

详细许可说明见 `LICENSE.md`。
