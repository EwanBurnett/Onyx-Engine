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

![Constants example output](/img_maths_constants_output.png)

## Utility Methods
### Unit Conversion
Onyx provides unit conversion utility methods between Degrees and Radians, via `Onyx::Maths::DegToRad()` and `Onyx::Maths::RadToDeg()`. 

```cpp
    //Conversions between degrees and radians
    float degrees = 60; 
    float radians = Onyx::Maths::DegToRad(degrees);
    Log::Print("%f degrees = %f radians.\n", degrees, radians);
    degrees = Maths::RadToDeg(radians); 
    Log::Print("%f radians = %f degrees.\n", radians, degrees); 
```

![Unit conversion example output](/img_maths_unit_conversion_output.png)

### Clamping a value
Arithmetic type values can be clamped through `Onyx::Maths::Clamp()`, specifying a minimum and maximum range. 

```cpp
    //Clamping Arithmetic types
    //Clamp to the Maximum of the range
    float value = Onyx::Maths::PI; 
    float vMin = 0.0f; 
    float vMax = 1.0f; 
    float newValue = Maths::Clamp(value, vMin, vMax); 
    printf("Value %f Clamped to range [%f, %f] = %f\n", value, vMin, vMax, newValue);

    //Clamp to the Minimum of the range
    value = -10000.0f; 
    vMin = -30.0f; 
    vMax = 40.0f; 
    newValue = Maths::Clamp(value, vMin, vMax); 
    printf("Value %f Clamped to range [%f, %f] = %f\n", value, vMin, vMax, newValue);

    //Value is within our range, so don't modify it. 
    value = 50.0f; 
    vMin = 0.0f; 
    vMax = 100.0f; 
    newValue = Maths::Clamp(value, vMin, vMax); 
    printf("Value %f Clamped to range [%f, %f] = %f\n", value, vMin, vMax, newValue);
```

![Clamp example output](/img_maths_clamp_output.png)

### Linear Interpolation
`Onyx::Maths::Lerp()` Provides Scalar Linear Interpolation between `a` and `b` by constant `t`, defined as \f$ lerp(a, b, t) = ((b - a) \cdot t) \f$.
```cpp
    //Linear interpolation
    float a = 0.0; 
    float b = 1.0; 

    float v; 
    v = Onyx::Maths::Lerp(a, b, 0.0f);  // v = a = 0.0
    v = Onyx::Maths::Lerp(a, b, 1.0f);  // v = b = 1.0
    v = Onyx::Maths::Lerp(a, b, -50.0f);  // v = (b - a) * t = -50.0


```

### Fast Inverse Square Root
`Onyx::Maths::RSqrt()` Computes an approximation of the Inverse Square Root, using the [Fast Inverse Square Root algorithm](https://en.wikipedia.org/wiki/Fast_inverse_square_root). This yields an approximate Reciprocal of the Square Root of x, and should be used where `sqrt` precision is not worth the cost of the instruction. 

```cpp
    //Inverse Square Root
    float x = 25;

    float sqrt_x = sqrt(n); // sqrt_x == 5
    float rsqrt_x = 1.0 / Onyx::Maths::RSqrt(x);    //rsqrt_x == ~5
```


# Vectors
Mathemetical Vectors with between 2 and 4 components: 
    - `Vector2<T>`
    - `Vector3<T>`
    - `Vector4<T>`

## Standard Operations
### Accessing Vector Elements
### Arithmetic Operators
## Additional Operations
### Vector Set
### Dot Product
### Cross Product
## Static Methods
### Directional Constants
### Distance
### Interpolation
#### Linear Interpolation
#### Spherical Interpolation
### Vector Orthonormalization

# Matrices

# Quaternions


<div class="section_buttons">
 
| Previous          |                              Next |
|:------------------|----------------------------------:|
| [Console Variables](CVars.md) | [Random Number Generation](RNG.md) |
 
</div>