Logging {#Logging}
===
Output can be logged to any `FILE*` stream through the `Onyx::Log` class (`Onyx/Core/Logger.h`).
By default, Log output is directed to `stdout`.  
The `FILE*` stream can be changed via `Onyx::Log::SetOutputStream()`. 

## Standard Usage
`Onyx::Log` has a number of methods, intended to standardise the logging process. 

| Function               | Description                                                                                                                                                         | Example Output                                                                                                                                                                                                                         |
| ---------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------- | -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `Onyx::Log::Print()`   | Prints a formatted message in White.                                                                                                                                | <span style="color:white">**The quick brown fox jumps over the lazy dog** </span><br>                                                                                                                                                  |
| `Onyx::Log::Debug()`   | Only prints when `ONYX_DEBUG` is defined. Intended for use with `printf` Debugging.                                                                                 | <span style="color:lightgreen">**[DEBUG] The quick brown fox jumps over the lazy dog** </span>                                                                                                                                         |
| `Onyx::Log::Status()`  | Prints a Status message. Intended to notify the User of an event or status change.                                                                                  | <span style="color:cyan">**The quick brown fox jumps over the lazy dog** </span>                                                                                                                                                       |
| `Onyx::Log::Warning()` | Prints a Warning message, prefixed by "Warning". Intended for cases where the issue was probably not intended, but still valid.                                     | <span style="color:yellow">**Warning<br/>The quick brown fox jumps over the lazy dog** </span>                                                                                                                                         |
| `Onyx::Log::Success()` | Prints a Success message. Intended for use when an operation (e.g. file loading) has succeeded.                                                                     | <span style="color:green">**The quick brown fox jumps over the lazy dog** </span>                                                                                                                                                      |
| `Onyx::Log::Failure()` | Prints a Failure message. Intended for use when an operation has failed.                                                                                            | <span style="color:brown">**The quick brown fox jumps over the lazy dog** </span>                                                                                                                                                      |
| `Onyx::Log::Error()`   | Prints an Error message, alongside `__FILE__`, `__LINE__` and `__PRETTY_FUNCTION__`. Use in non-fatal cases which invalidate an operation.                          | <span style="color:#e74856">**Error**<br/>&nbsp;**FILE: Onyx-Engine\Testbed\main.cpp**<br/>**&nbsp;&nbsp;LINE: 30**<br/>**&nbsp;&nbsp;FUNCTION: int __cdecl main(void)**<br/>**The quick brown fox jumps over the lazy dog** </span>   |
| `Onyx::Log::Fatal()`   | Prints a Fatal Error message, with `__FILE__`, `__LINE__` and `__PRETTY_FUNCTION__`, and triggers a breakpoint for the current Debugger if `ONYX_DEBUG` is defined. | <span style="color:red">**Fatal Error**<br/>&nbsp;**FILE: Onyx-Engine\Testbed\main.cpp**<br/>&nbsp;&nbsp;**LINE: 30**<br/>&nbsp;&nbsp;**FUNCTION: int __cdecl main(void)**<br/>**The quick brown fox jumps over the lazy dog** </span> |

![logging example output](/Resources/img_logging_output_windows.png)
 
```cpp
//Code to reproduce the above example
Onyx::Log::Print("This is a Print message\n");
Onyx::Log::Debug("This is a Debug message\n");
Onyx::Log::Status("This is a Status Message\n");
Onyx::Log::Warning("This is a Warning message\n");
Onyx::Log::Success("This is a Success message\n");
Onyx::Log::Failure("This is a Failure message\n");
Onyx::Log::Error(__FILE__, __LINE__, __PRETTY_FUNCTION__, "This is an Error message\n");
Onyx::Log::Fatal(__FILE__, __LINE__, __PRETTY_FUNCTION__, "This is a Fatal Error message (Triggers a breakpoint!\n");
```

## Redirecting output to a File
```cpp
#include <cstdio> 

FILE* logfile = fopen("Log.txt", "a+");    //Open a logfile in append mode. 
Onyx::Log::SetOutputStream(logfile);    //Change the output stream to our logfile. 

//Log statements...
Onyx::Log::Print("This Print message will be printed to a file!\n");
Onyx::Log::Debug("This Debug message will be printed to a file!\n");
Onyx::Log::Status("This message will be printed to a file!\n");
Onyx::Log::Warning("This Warning will be printed to a file!\n");
Onyx::Log::Success("This Success message will be printed to a file!\n");
Onyx::Log::Failure("This Failure message will be printed to a file!\n");
Onyx::Log::Error(__FILE__, __LINE__, __PRETTY_FUNCTION__, "This Error message will be printed to both stderr and to a file!\n");
Onyx::Log::Fatal(__FILE__, __LINE__, __PRETTY_FUNCTION__, "This Fatal Error message will be printed to both stderr and to a file!\n");

Onyx::Log::SetOutputStream(stdout);    //Reset the output stream to stdout
fclose(logfile);    //ensure we close the logfile after use. 
```

Log.txt: 
```
This Print message will be printed to a file!
This Debug message will be printed to a file!
This Status message will be printed to a file!
Warning
This Warning will be printed to a file!
This Success message will be printed to a file!
This Failure message will be printed to a file!
Error
FILE: F:\Projects\2024\Onyx\Testbed\main.cpp
	LINE: 33
	FUNCTION: int __cdecl main(void)
This Error message will be printed to both stderr and to a file!
FATAL ERROR
FILE: F:\Projects\2024\Onyx\Testbed\main.cpp
	LINE: 34
	FUNCTION: int __cdecl main(void)
This Fatal Error message will be printed to both stderr and to a file!
```

<div class="section_buttons">
 
| Previous          |                              Next |
|:------------------|----------------------------------:|
| [Logging](Logging.md) | [Console Variables](CVars.md) |
 
</div>
