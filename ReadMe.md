# Onyx Engine
![Banner Image](/Resources/Onyx_Banner_2400x1000.png)
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


| Resource Path                                                                                                                                                                                                                                                                                                                                | Resource Type | Resource Description                     | Source URL                                                                     | Notes                      | License2                                                                                                |
| -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | ------------- | ---------------------------------------- | ------------------------------------------------------------------------------ | -------------------------- | ------------------------------------------------------------------------------------------------------- |
| /Resources/Onyx_Logo_256x256.png<br>/Resources/Onyx_Logo_2048x2048.png<br>/Resources/Onyx_Logo_2_256x256.png<br>/Resources/Onyx_Logo_2_2048x2048.png<br>/Resources/Onyx_Icon_32x32.ico<br>/Resources/Onyx_Icon_256x256.ico<br>/Resources/Onyx_Icon_2_32x32.ico<br>/Resources/Onyx_Icon_2_256x256.ico<br>/Resources/Onyx_Banner_2400x1000.png | Image         | Logo / Banner / Icon for the Application | https://www.vecteezy.com/vector-art/5050967-logo-template-with-onyx-rock-image | Modified from Source Image | [Vecteezy Free License](https://www.vecteezy.com/vector-art/5050967-logo-template-with-onyx-rock-image) |
| /Docs/CSS/DoxygenAwesome.css                                                                                                                                                                                                                                                                                                                 | CSS           | Stylesheet for HTML Documentation pages  | https://jothepro.github.io/doxygen-awesome-css/                                |                            | [MIT License](https://github.com/jothepro/doxygen-awesome-css?tab=MIT-1-ov-file#readme)                 |
| /Resources/UV-Grids/*                                                                                                                                                                                                                                                                                                                        | Image         | UV Grid Textures                         | https://www.artstation.com/marketplace/p/BnBad/free-uv-grid-textures           |                            | [Artstation Standard License](https://www.artstation.com/marketplace-product-eula)                      |

