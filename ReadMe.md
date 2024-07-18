# Onyx Engine
A 3D Cross-Platform Game Engine written in C++. 

[![EwanBurnett/Onyx-Engine - GitHub](https://gh-card.dev/repos/EwanBurnett/Onyx-Engine.svg)](https://github.com/EwanBurnett/Onyx-Engine)

## Build Requirements
- A C++ 17 Compiler 
- [CMake 3.14](https://cmake.org) or higher
- The latest version of the [Vulkan SDK](https://www.lunarg.com/vulkan-sdk/)

### External Library Dependencies


## Build Instructions
- Clone the repository via Git
```bash
git clone https://github.com/EwanBurnett/Onyx-Engine.git
cd Onyx-Engine
```

### Windows
#### Visual Studio with CMake (Recommended)
- Install [Visual Studio 2022](https://visualstudio.microsoft.com/vs/)
- Install the [C++ CMake tools for Windows](https://learn.microsoft.com/en-us/cpp/build/cmake-projects-in-visual-studio?view=msvc-170) package for Visual Studio 2022
- Open the project root directory in Visual Studio 2022.
    - Visual Studio will automatically generate the CMake Project files.
- Select the project you wish to build from the "Select Startup Item" menu, and your build configuration, then build.  

#### Visual Studio
- Generate the CMake Project
```bash
mkdir build && cd build
cmake .. 
```
- Open the generated Visual Studio solution file `build/Onyx-Engine.sln`
- Build the project as normal.
 
### Linux
- Generate the CMake Project
```bash
mkdir build && cd build
cmake ..
```
- Build via your platform's build system (e.g. Make)
```bash
make
```

### CMake Options
 - Various features can be enabled/disabled through the use of CMake Options 

| Option | Description | Default Value |
| - | - | - |
| `ONYX_BUILD_TESTS` | Build the Unit Test project | OFF | 
| `ONYX_BUILD_TESTBED` | Build the Development Test project | OFF | 
| `ONYX_BUILD_SAMPLES` | Build Sample Projects | ON | 
| `ONYX_BUILD_DOCS` | Generate Local Doxygen Documentation (Requires [Doxygen](https://www.doxygen.nl/index.html)) | OFF | 

- e.g. to enable `ONYX_BUILD_SAMPLES`:
```bash
# From the CMake build directory
cmake .. -DONYX_BUILD_SAMPLES=ON

```

## Resource References
| Resource Path                | Resource Type | Resource Description                    | Source URL                                                                     | Notes                      | License                                                                                                 |
| - | - | - | - | - | - |
| /Resources/Onyx_Logo.png     | Texture       | Logo for the Application                | https://www.vecteezy.com/vector-art/5050967-logo-template-with-onyx-rock-image | Modified from Source Image | [Vecteezy Free License](https://www.vecteezy.com/vector-art/5050967-logo-template-with-onyx-rock-image) |
| /Onyx_Icon.ico               | Icon          | Icon for the Application                | https://www.vecteezy.com/vector-art/5050967-logo-template-with-onyx-rock-image | Modified from Source Image | [Vecteezy Free License](https://www.vecteezy.com/vector-art/5050967-logo-template-with-onyx-rock-image) |
| /Docs/CSS/DoxygenAwesome.css | CSS           | Stylesheet for HTML Documentation pages | https://jothepro.github.io/doxygen-awesome-css/                                |                            | [MIT License](https://github.com/jothepro/doxygen-awesome-css?tab=MIT-1-ov-file#readme)                 |

