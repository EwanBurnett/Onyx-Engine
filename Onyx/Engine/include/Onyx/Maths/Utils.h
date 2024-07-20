#ifndef ONYX_MATHS_UTILS_H
#define ONYX_MATHS_UTILS_H
/**
* @file Utils.h
*
* ------------------------------------------
* @author Ewan Burnett (EwanBurnettSK@outlook.com)
* @date 2024/07/20
*/
#include <type_traits>
#include <limits>
#include <cmath>
#include <cfloat>

namespace Onyx {
    namespace Maths {
        //Constants
        constexpr double PI = 3.1415926535897932385;
        constexpr float Float_Max = std::numeric_limits<float>::max();
        constexpr float Float_Min = std::numeric_limits<float>::min();

        constexpr int Int_Max = std::numeric_limits<int>::max();
        constexpr int Int_Min = std::numeric_limits<int>::min();

        constexpr float Infinity = std::numeric_limits<float>::infinity();
        constexpr float Epsilon = FLT_EPSILON;

        constexpr double Deg2Rad = PI / 180.0;
        constexpr double Rad2Deg = 180.0 / PI;


        //Helpers

        template<typename T>
        struct Vector2;

        template<typename T>
        struct Vector3;

        template<typename T>
        struct Vector4;


        /**
         * @brief Clamps a Value to a given range.
         * @tparam T Arithmetic type to Clamp
         * @param value The value to clamp.
         * @param min The minimum value of the range.
         * @param max The maximum value of the range.
         * @return The clamped value.
        */
        template <typename T>
        inline T Clamp(const T value, const T min, const T max) {

            T v = value; 

            if (value < min) {
                v = min;
            }
            else if (value > max) {
                v = max;
            }

            return v; 
        };

        /**
         * @brief Linearly Interpolates a value between a[0] and b[1].
         * @tparam T Arithmetic type to Lerp
         * @param a the start value, where t = 0.0
         * @param b the end value, where t = 1.0
         * @param t Interpolation constant
         * @return A linearly interpolated value.
        */
        template <typename T>
        inline T Lerp(const T& a, const T& b, const double t) {
            return a * (1.0 - t) + (b * t);
        }

        /**
         * @brief Converts Degrees to Radians.
         * @tparam T Arithmetic type to Convert.
         * @param degrees Angle in degrees to convert to Radians.
         * @return 'degrees' parameter in Radians.
        */
        template <typename T>
        inline constexpr T DegToRad(const T& degrees) {
            static_assert(std::is_arithmetic<T>(), "Error: T is not Arithmetic!\n");
            return static_cast<T>(degrees * Maths::Deg2Rad);
        }

        /**
         * @brief Converts Radians to Degrees.
         * @tparam T Arithmetic type to Convert.
         * @param radians Angle in Radians to convert to Degrees.
         * @return 'radians' parameter in Degrees.
        */
        template <typename T>
        inline constexpr T RadToDeg(const T& radians) {
            static_assert(std::is_arithmetic<T>(), "Error: T is not Arithmetic!\n");
            return radians * Maths::Rad2Deg;
        }


        /**
         * @brief Computes an approximation of the Inverse Square Root of a number.
         * @param number
         * @return The Inverse Square Root of a number.
         * @remark This is an implementation of the infamous Fast inverse square root algorithm found in Quake 3. This function is pure black magic.
        */
        inline float RSqrt(float number) {
            long i;
            float x2, y;
            const float threeHalfs = 1.5f;

            x2 = number * 0.5f;
            y = number;
            i = *(long*)&y;
            i = 0x5f3759df - (i >> 1);  //?????
            y = *(float*)&i;
            y = y * (threeHalfs - (x2 * y * y));

            return y;
        }


        /**
         * @brief Orthonormalizes 3 Vectors using the Modified Gram-Schmidt Algorithm.
         * @tparam T
         * @param a
         * @param b
         * @param c
        */
        template <typename T>
        inline void Orthonormalize(Vector3<T>& a, Vector3<T>& b, Vector3<T>& c) {
            Vector3<T> v[3] = { a, b, c };

            //Orthonormalize using the Modified Gram-Schmidt Algorithm 
            for (uint8_t i = 0; i < 3; i++) {
                for (uint8_t j = 0; j < i; j++) {
                    const double f = static_cast<double>(v[j].Dot(v[i]) / v[j].Dot(v[j]));

                    for (uint8_t k = 0; k < 3; k++) {
                        v[i].arr[k] -= f * v[j].arr[k];
                    }
                }
            }

            a = v[0].Normalize();
            b = v[1].Normalize();
            c = v[2].Normalize();
        }
    }
}

#endif
