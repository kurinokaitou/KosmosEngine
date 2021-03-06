# KosmosEngine
Game engine project
## 初始化Vscode开发环境
本项目使用msys2提供的MinGW 64-bit C/C++工具链，使用g++作为编译器。然后构建项目需要配置CMake和NinJa的构建系统，首先下载CMake和Ninja并且添加binary到系统环境变量Path中。

[Ninja]: https://ninja-build.org/	"Ninja的官网"

首先需要确保安装并激活了以下C/C++开发的插件。第一次打开工程会推荐安装，全部安装即可：

```json
{
    "ms-vscode.cpptools",
    "llvm-vs-code-extensions.vscode-clangd",
    "twxs.cmake",
    "ms-vscode.cmake-tools",
}
```

打开项目时，会默认自动构建`GCC`工具链。如果是构建的是VS2022工程，使用`Ctrl+Shift+P`打开命令栏输入`CMake: Scan for kits`然后在`CMake: Scan for kits`中选择`GCC`对应的工具链即可。

项目使用的C++包管理器是vcpkg，目前依赖的库有`glm`,`glfw3`,`imgui`,`tinyobjloader`,`fmt`。需要自行安装vcpkg并且通过`./vcpkg.exe install xxx:x64-windows`安装库。在`settings.json`中需要指定`CMAKE_TOOLCHAIN_FILE`为本机`vcpkg.cmake`文件的位置，即可让Vscode自动配置。

## 初始化Vulkan环境

本项目使用的是`Vulkan SDK 1.3`以上的版本。需要到LunarG官网下载对应版本的SDK安装并选择添加环境变量。安装器中勾选本体和`Vulkan Memory Allocator header`即可。

## tasks.json 构建与运行命令

使用`Ctrl+Shift+P`打开命令栏输入tasks选择命令。

`cmake debug`: 构建debug模式下CMake，写入build中

`cmake release`: 构建release模式下CMake， 写入dist中

`debug build`：编译链接debug模式下的项目，写入build中

`build`：编译链接release模式下的项目，写入dist中

`debug run`：直接运行debug模式下的可执行文件

`run`：直接运行release模式下的可执行文件

## lauch.json 调试命令

`Launch Debug`：根据当前文件树的更改重新编译项目并启动调试

`Launch Debug Directly`：直接启动调试
