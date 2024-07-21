#ifndef ONYX_MATHS_QUATERNION_H
#define ONYX_MATHS_QUATERNION_H

#include "Vector3.h"
#include "Vector4.h"

namespace Onyx {

    namespace Maths {
        template<typename T>
        struct Matrix4x4;


        class Quaternion {
        public:

            double w;
            Vector3<double> v;

            Quaternion() : w(1.0), v(0.0, 0.0, 0.0) {  };
            Quaternion(double w, double x, double y, double z) : w(w), v({ x, y, z }) {};

            template<typename T>
            Quaternion(double w, Vector3<T> v) : w(w), v(v) {};

            template<typename T>
            Quaternion(Vector4<T> v) : w(v.w), v({ v.x, v.y, v.x }) {};


            inline Quaternion operator *(const Quaternion& rhs) {
                Vector3d _v = Vector3<double>::Cross(v, rhs.v) + (rhs.w * v) + (w * rhs.v);// -(Vector3<double>::Dot(v, rhs.v)));
                double _w = (w * rhs.w) - Vector3<double>::Dot(v, rhs.v);

                return { _w, _v };
            }

            template<typename T>
            inline friend Quaternion operator *(const Quaternion& lhs, const T& rhs) {
                static_assert(std::is_arithmetic<T>(), "T Must be Arithmetic!\n");

                return { Quaternion(rhs, {0.0, 0.0, 0.0}) * lhs };
            }


            template<typename T>
            inline friend Quaternion operator *(const T& lhs, const Quaternion& rhs) {
                static_assert(std::is_arithmetic<T>(), "T Must be Arithmetic!\n");

                return { Quaternion(lhs, Vector3{0.0, 0.0, 0.0}) * rhs };
            }



            inline Quaternion operator +(const Quaternion& rhs) {
                return { w + rhs.w, v + rhs.v };
            }

            /**
             * @brief Computes the Conjugate of this Quaternion.
             * @return
            */
            inline Quaternion Conjugate() const {
                return { w, -v };
            }

            /**
             * @brief Computes the Conjugate of a given Quaternion.
             * @param q
             * @return
            */
            inline static Quaternion Conjugate(const Quaternion& q) {
                return { q.w, -q.v };
            }

            /**
             * @brief Computes the Norm of this Quaternion.
             * @return
            */
            double Norm() const {
                return sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z) * (w * w));
            }

            /**
             * @brief Computes the Norm of a given Quaternion.
             * @param q
             * @return
            */
            inline static double Norm(const Quaternion& q) {
                return sqrt((q.v.x * q.v.x) + (q.v.y * q.v.y) + (q.v.z * q.v.z) * (q.w * q.w));
            }

            /**
             * @brief Computes the Inverse of this Quaternion.
             * @return
            */
            inline Quaternion Inverse() const {
                double n = Norm();
                n = n * n;
                return ((1.0 / n) * Conjugate());
            }

            /**
             * @brief Computes the Inverse of a given Quaternion.
             * @param q
             * @return
            */
            inline static Quaternion Inverse(const Quaternion& q) {
                double n = Norm(q);
                n = n * n;
                return ((1.0 / n) * Conjugate(q));
            }

            /**
             * @brief Returns the Quaternion Identity.
            */
            inline static Quaternion Identity() {
                return{ 1.0, Vector3<double>{0.0, 0.0, 0.0} };
            }

            bool operator == (Quaternion rhs) { return w == rhs.w && v == rhs.v; };
            bool operator != (Quaternion rhs) { return !(*this == rhs); };

            template<typename T>
            inline static Vector3<T> RotateVector(const Vector3<T> vector, const Vector3<T> axis, const double radians) {
                const double r = radians / 2.0;
                const double sinTheta = sin(r);
                const double cosTheta = cos(r);
                Quaternion q = Quaternion::FromAxisAngle(axis, radians);  //Construct a unit quaternion from our rotation
                Quaternion p(0.0, vector);  //Load the Vector into a Quaternion

                return (q * p * Conjugate(q)).v;    //As a rotation quaternion, the conjugate is the inverse. 
            }

            template<typename T> 
            inline static Quaternion FromAxisAngle(const Vector3<T> axis, const double angleRadians) {
                const double r = angleRadians / 2.0; 
                const double sinTheta = sin(r); 
                const double cosTheta = cos(r); 
                return { cosTheta, (Vector3<T>::Normalize(axis) * sinTheta) }; 
            }

            /**
             * @brief Performs Spherical Linear Interpolation between two unit Quaternions. 
             * @param a 
             * @param b 
             * @param t 
             * @return 
            */
            inline static Quaternion Slerp(const Quaternion& a, const Quaternion& b, const double t) {
                double phi = acos((a.v.x * b.v.x) + (a.v.y * b.v.y) + (a.v.z * b.v.z) * (a.w * b.w)); 
                return ((sin(phi * (1.0 - t)) / sin(phi)) * a) + ((sin(phi * t) / sin(phi)) * b);
            }

            inline static Quaternion RotateTowards(const Quaternion& a, const Quaternion& b) {
                return {};
            }

            static Quaternion FromMatrix4x4(const Matrix4x4<double>& mat);
            Matrix4x4<double> ToMatrix4x4();
            static Matrix4x4<double> ToMatrix4x4(const Quaternion& q);
        };
    }
}

#endif