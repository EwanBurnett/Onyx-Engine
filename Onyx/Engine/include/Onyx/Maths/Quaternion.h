#ifndef ONYX_MATHS_QUATERNION_H
#define ONYX_MATHS_QUATERNION_H

#include "Vector3.h"

namespace Onyx {

    namespace Maths {
        template <typename T>
        class Vector3;

        class Quaternion {
        public:
            Quaternion() { *this = Identity(); };
            Quaternion(double w, double x, double y, double z) : w(w), v({ x, y, z }) {};
            Quaternion(double w, Vector3<double> v) : w(w), v(v) {};

            inline Quaternion operator *(const Quaternion& rhs) {
                Vector3d _v = Vector3<double>::Cross(v, rhs.v) + (rhs.w * v) + (w * rhs.v);// -(Vector3<double>::Dot(v, rhs.v)));
                double _w = (w * rhs.w) - Vector3<double>::Dot(v, rhs.v);

                return { _w, _v };
            }

            inline Quaternion operator +(const Quaternion& rhs) {
                return { w + rhs.w, v + rhs.v };
            }

            Quaternion Conjugate() const {
                return { w, -v };
            }

            double Norm() const {
                return sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z) * (w * w));
            }

            inline static Quaternion Identity() {
                return{ 1.0, {0.0, 0.0, 0.0} };
            }
            double w;
            Vector3<double> v;

        };
    }
}

#endif