Console Variables {#CVars}
===
A Console Variable is a Globally accessible value stored by the engine, mapped to a String. These values are of simple data types (`bool`, `float`, `int`, `string`), and can be loaded or changed during runtime. These variables can store any state, and as such should be used for Configuration. See `CVar.h`. 

Some examples include: 

| Variable Name | Type | Value | Description | 
| - | - | - | - |
| `Example.Game.MaxEntityCount` | `INT` | `1000` | Controls the Maximum number of entities the game can simulate at once. |
| `Example.Renderer.EnableOcclusionCulling` | `BOOL` | `false` | Whether to enable Occlusion Culling. 0: Disable, 1: Enable. |
| `Example.Debug.ShowFrameStatistics` | `BOOL` | `false` | Whether to show Framerate Statistics. 0: Disable, 1: Enable. |
| `Example.App.LogFileName` | `STRING` | `log.txt` | The name of the Application Log file. Changes to this variable will take effect on the next application load. | 
| `Example.World.WorldScale` | `FLOAT` | `1.0` | Sets the Uniform Scale of the world. |

## Usage
### CVar Definition
Console Variables must each be Defined by the application; Whether this is manually, or dynamically loaded. 
The `AutoCVar_T` type can be is the preferred method of defining a CVar. e.g. `AutoCVar_Int` defines a CVar containing an `int`. 
```cpp
    //Define CVars

    //Define these CVars with a handle, which can be used to Get / Set their values.
    Onyx::AutoCVar_Bool showFrameStatistics("Example.Debug.ShowFrameStatistics", "Whether to show Framerate Statistics. 0: Disable, 1: Enable.", true);
    Onyx::AutoCVar_Int maxEntityCount("Example.Game.MaxEntityCount", "Controls the Maximum number of entities the game can simulate at once.", 1000);    

    //Define anonymous CVars, with no handle. These can only be referenced by name.
    Onyx::AutoCVar_Bool("Example.Renderer.EnableOcclusionCulling", "Whether to enable Occlusion Culling. 0: Disable, 1: Enable.", false); 
    Onyx::AutoCVar_String("Example.App.LogFileName", "The name of the Application Log file. Changes to this variable will take effect on the next application load.", "log.txt");

    //Manually create a CVar through the manager. This method isn't recommended.
    Onyx::CVarManager::Get()->CreateCVar_Float("Example.World.WorldScale", "Sets the Uniform Scale of the World.", 1.0, 1.5);
```

### Getting / Setting CVar values
To Get / Set a CVar value, the user needs to call the appropriate method for the CVar itself. 

```cpp
    //Getting CVars
    
    //For CVars with a handle, simply call Get() on the handle for the value. 
    if(showFrameStatistics.Get()){
        ShowFrameStatistics();
    }
    Game.SetMaxEntityCount(maxEntityCount.Get()); 

    //Anonymous CVars require retrieval from the manager by name - as well as Validation. (the CVar may not exist!)
    const bool* pEnableOcclusionCulling = Onyx::CVarManager::Get()->GetCVar_Bool("Example.Renderer.EnableOcclusionCulling"); 
    if(pEnableOcclusionCulling != nullptr){  //If a CVar is invalid, it will return nullptr. 
        settings.EnableOcclusionCulling = *pEnableOcclusionCulling;
    }
```

```cpp
    //Setting CVars

    //CVars with a handle can be set by calling Set()
    showFrameStatistics.Set(false); 
    maxEntityCount.Set(1000); 

    //Anonymous CVars can be set through the manager
    Onyx::CVarManager::Get()->SetCVar_String("Example.App.LogFileName", "Dump.bin"); 
```

### Retrieving CVar Values
A Sorted List of all CVars can be retrieved from the manager via `GetCVarData()`.
This data is in the format: 
```cpp
    struct CVarData{
        const std::string* pName;
        const std::string* pDescription;
        CVarType type;
        void* pInitialData;
        void* pCurrentData;
    };
```
note: as data handles are stored as `void*`, they must be `reinterpret_cast` into the appropriate type. All pointers returned by this function are valid.

```cpp
    //This example prints all current CVars to the Logger output. 
    auto cvars = Onyx::CVarManager::Get()->GetCVarData();
    for (auto& cvar : cvars) {
        Onyx::Log::Print("%s\n\t%s\n\t%d\n", cvar.pName->c_str(), cvar.pDescription->c_str(), cvar.type);
        switch (cvar.type) {
        case(Onyx::CVarType::Bool):
            Onyx::Log::Print("\tInitial Value: %s\n\tCurrent Value: %s\n", *reinterpret_cast<bool*>(cvar.pInitialData) ? "true" : "false", *reinterpret_cast<bool*>(cvar.pCurrentData) ? "true" : "false");
            break;
        case(Onyx::CVarType::Int):
            Onyx::Log::Print("\tInitial Value: %d\n\tCurrent Value: %d\n", *reinterpret_cast<int*>(cvar.pInitialData), *reinterpret_cast<int*>(cvar.pCurrentData));
            break;
        case(Onyx::CVarType::Float):
            Onyx::Log::Print("\tInitial Value: %d\n\tCurrent Value: %d\n", *reinterpret_cast<float*>(cvar.pInitialData), *reinterpret_cast<float*>(cvar.pCurrentData));
            break; 
        case(Onyx::CVarType::String):
            Onyx::Log::Print("\tInitial Value: %s\n\tCurrent Value: %s\n", reinterpret_cast<std::string*>(cvar.pInitialData)->c_str(), reinterpret_cast<std::string*>(cvar.pCurrentData)->c_str());
            break;
        default:
            break;
        }
    }
```

![cvar example output](/Resources/img_cvars_example_output.png)

## Engine Console Variables

| Console Variable | Description | Type | Default Value | 
| - | - | - | - |
| `Onyx.Log.EnableForwarding` | Controls whether to forward log output to `stdout`, when the output stream is changed to something else. 0 to disable, 1 to enable. | `Bool` | `false` |
| `Onyx.Application.Name` | The Name of the Application. | `String` | `"Onyx-Application"` |
| `Onyx.Window.Size.x` | The Initial Width of the Application Window. | `Int` | `600` | 
| `Onyx.Window.Size.y` | The Initial Height of the Application Window. | `Int` | `400` |

## Editor Console Variables
| Console Variable | Description | Type | Default Value | 
| - | - | - | - |
| `Editor.Debug.LogFile` | | | |

<div class="section_buttons">
 
| Previous          |                              Next |
|:------------------|----------------------------------:|
| [Logging](Logging.md) | [Maths](Maths.md) |
 
</div>

