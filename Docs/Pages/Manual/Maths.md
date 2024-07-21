Maths {#Maths}
===

  The distance between \f$(x_1,y_1)\f$ and \f$(x_2,y_2)\f$ is 
  \f$\sqrt{(x_2-x_1)^2+(y_2-y_1)^2}\f$.
## Coordinate System
- Left-handed Cartesian Coordinate system
    - Z+ goes into the screen, Z- comes out of it. 
    - X+ is Right, X- is Left
    - Y+ is Up, Y- is Down

# Utilities
Found in `Onyx/Maths/Utils.h`.

## Constants
Onyx defines a number of useful Mathematical constants:

| Constant | Description | Approximate Value | 
| - | - | - |
| `PI` | The [Numerical Constant PI](https://en.wikipedia.org/wiki/Pi), represented by \f$\pi\f$ | 3.1415926 |
| `Deg2Rad` | Constant required to [convert Degrees to Radians](https://en.wikipedia.org/wiki/Degree_%28angle%29). | \f$\frac{\pi}{180}\f$ | 
| `Rad2Deg` | Constant required to [convert Radians to Degrees](https://en.wikipedia.org/wiki/Radian). | \f$\frac{180}{\pi}\f$  |
| `Infinity` | Represents an Infinitely large number. | \f$\infty\f$ | 
| `Epsilon` | Represents an incredibly small number. | \f$\epsilon\f$ | 
| `Float_Max` | The maximum floating point value supported by the platform. | ~3.4e+38 |
| `Float_Min` | The minimum floating point value supported by the platform. | ~3.4e-38 |
| `Int_Max` | The maximum signed 32-bit Integral value supported by the platform. | 2147483647 |
| `Int_Min` | The minimum signed 32-bit Integral value supported by the platform. | -2147483648 |

```cpp
    #include <Onyx/Maths/Utils.h>
    
    // Maths Constants
    Onyx::Log::Print("PI = %f\n", Maths::PI);
    Onyx::Log::Print("Degrees to Radians constant = %.38f\n", Maths::Deg2Rad);
    Onyx::Log::Print("Radians to Degrees constant = %.38f\n", Maths::Rad2Deg);
    Onyx::Log::Print("Infinity = %f\n", Maths::Infinity); 
    Onyx::Log::Print("Epsilon = %.38f\n", Maths::Epsilon);
    Onyx::Log::Print("Float Min = %.38f\n", Maths::Float_Min);
    Onyx::Log::Print("Float Max = %f\n", Maths::Float_Max);
    Onyx::Log::Print("Int Min = %d\n", Maths::Int_Min);
    Onyx::Log::Print("Int Max = %d\n", Maths::Int_Max);

```

![constants example output](/img_maths_constants_output.png)

## Unit Conversion

## Utility Methods
### Clamping a value
### Linear Interpolation
### Fast Inverse Square Root
### Vector Orthonormalization

# Vectors

# Matrices


<div class="section_buttons">
 
| Previous          |                              Next |
|:------------------|----------------------------------:|
| [Console Variables](CVars.md) | [Random Number Generation](RNG.md) |
 
</div>