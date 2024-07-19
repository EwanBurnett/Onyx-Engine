# Console Variables

A Console Variable is a Value stored by the engine, mapped to a String. These values are of simple data types (`bool`, `float`, `int`, `string`), and can be loaded or changed during runtime. These variables can store any state, and as such should be used for Configuration.

Some examples include: 

| Variable Name | Type | Value | Description | 
| - | - | - | - |
| `Example.Game.MaxEntityCount` | `INT` | `1000` | Controls the Maximum number of entities the game can simulate at once. |
| `Example.Renderer.EnableOcclusionCulling` | `BOOL` | `false` | Whether to enable Occlusion Culling. 0: Disable, 1: Enable. |
| `Example.Debug.ShowFrameStatistics` | `BOOL` | `false` | Whether to show Framerate Statistics. 0: Disable, 1: Enable. |
| `Example.App.LogFileName` | `STRING` | `log.txt` | The name of the Application Log file. Changes to this variable will take effect on the next application load. | 

## Usage

## Engine Console Variables

## Editor Console Variables
