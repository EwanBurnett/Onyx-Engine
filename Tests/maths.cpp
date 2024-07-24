#include <gtest/gtest.h>
#include <Onyx/Maths/Maths.h> 

//UTILS

TEST(Maths, Utils_Deg2Rad) {
    //0 degrees == 0 radians
    {
        const double degrees = 0.0;
        const double radians = Onyx::Maths::DegToRad(degrees);
        EXPECT_DOUBLE_EQ(degrees, radians);
    }

    //90 degrees == PI/2 radians
    {
        const double degrees = 90.0;
        const double radians = Onyx::Maths::DegToRad(degrees);
        EXPECT_DOUBLE_EQ(radians, Onyx::Maths::PI / 2.0);
    }

    //180 degrees == PI radians
    {
        const double degrees = 180.0;
        const double radians = Onyx::Maths::DegToRad(degrees);
        EXPECT_DOUBLE_EQ(radians, Onyx::Maths::PI);
    }

    //270 degrees == 3/2 PI radians
    {
        const double degrees = 270.0;
        const double radians = Onyx::Maths::DegToRad(degrees);
        EXPECT_DOUBLE_EQ(radians, Onyx::Maths::PI * 1.5);
    }
}

TEST(Maths, Utils_Rad2Deg) {
    //0 radians == 0 degrees
    {
        const double radians = 0.0;
        const double degrees = Onyx::Maths::RadToDeg(radians);
        EXPECT_DOUBLE_EQ(degrees, radians);
    }

    //PI/2 radians == 90 degrees
    {
        const double radians = Onyx::Maths::PI / 2.0;
        const double degrees = Onyx::Maths::RadToDeg(radians);
        EXPECT_DOUBLE_EQ(degrees, 90.0);
    }

    //PI radians == 180 degrees
    {
        const double radians = Onyx::Maths::PI;
        const double degrees = Onyx::Maths::RadToDeg(radians);
        EXPECT_DOUBLE_EQ(degrees, 180.0);
    }

    //3/2 PI radians == 270 degrees
    {
        const double radians = Onyx::Maths::PI * 1.5;
        const double degrees = Onyx::Maths::RadToDeg(radians);
        EXPECT_DOUBLE_EQ(degrees, 270.0);
    }
}

TEST(Maths, Utils_Clamp) {
    {
        float f = 0.0f;
        double d = 0.0;
        int i = 0;

        const float fMin = 0.0f;
        const float fMax = 1.0f;
        const double dMin = -100.0f;
        const double dMax = 100.0f;
        const int iMin = 0;
        const int iMax = 1;
        {
            //Min-bounds clamp
            {
                f = -10000.0f;
                d = -10000.0;
                i = -10000;
                f = Onyx::Maths::Clamp(f, fMin, fMax);
                d = Onyx::Maths::Clamp(d, dMin, dMax);
                i = Onyx::Maths::Clamp(i, iMin, iMax);

                EXPECT_FLOAT_EQ(f, fMin);
                EXPECT_DOUBLE_EQ(d, dMin);
                EXPECT_EQ(i, iMin);
            }
            //Max-bounds clamp
            {
                f = 10000.0f;
                d = 10000.0;
                i = 10000;
                f = Onyx::Maths::Clamp(f, fMin, fMax);
                d = Onyx::Maths::Clamp(d, dMin, dMax);
                i = Onyx::Maths::Clamp(i, iMin, iMax);

                EXPECT_FLOAT_EQ(f, fMax);
                EXPECT_DOUBLE_EQ(d, dMax);
                EXPECT_EQ(i, iMax);
            }
            //No Clamp
            {
                f = 0.5f;
                d = 0.0f;
                i = 1;
                f = Onyx::Maths::Clamp(f, fMin, fMax);
                d = Onyx::Maths::Clamp(d, dMin, dMax);
                i = Onyx::Maths::Clamp(i, iMin, iMax);

                EXPECT_FLOAT_EQ(f, f);
                EXPECT_DOUBLE_EQ(d, d);
                EXPECT_EQ(i, i);
            }
        }
    }
}

TEST(Maths, Utils_Lerp) {
    float f0 = 0.0f;
    float f1 = 1.0f;

    float half = (f1 + f0) / 2.0;

    //t = 1.0
    {
        float t = 1.0f;
        float v = Onyx::Maths::Lerp(f0, f1, t);

        EXPECT_FLOAT_EQ(v, f1);
    }

    //t = 0.0
    {
        float t = 0.0f;
        float v = Onyx::Maths::Lerp(f0, f1, t);

        EXPECT_FLOAT_EQ(v, f0);
    }

    //t = 0.5
    {
        float t = 0.5f;
        float v = Onyx::Maths::Lerp(f0, f1, t);

        EXPECT_FLOAT_EQ(v, half);
    }

    //t = 2.0
    {
        float t = 2.0f;
        float v = Onyx::Maths::Lerp(f0, f1, t);

        EXPECT_FLOAT_EQ(v, f1 * 2.0f);
    }
    //t = -1.0
    {
        float t = -1.0f;
        float v = Onyx::Maths::Lerp(f0, f1, t);

        EXPECT_FLOAT_EQ(v, f1 * -1.0f);
    }
}

TEST(Maths, Utils_RSqrt) {
    float n = 50;

    float sqrt_n = sqrt(n);
    float rsqrt_n = 1.0 / Onyx::Maths::RSqrt(n);

    EXPECT_NEAR(sqrt_n, rsqrt_n, 0.1);
}

//Vector 2

TEST(Maths, Vector2_Construction) {
    Onyx::Maths::Vector2<int> iv(1, -1);
    Onyx::Maths::Vector2<float> fv(2.0f, -2.0f);
    Onyx::Maths::Vector2<double> dv(3.0, -3.0);

    EXPECT_EQ(iv.x, 1);
    EXPECT_EQ(iv.y, -1);

    EXPECT_FLOAT_EQ(fv.x, 2.0f);
    EXPECT_FLOAT_EQ(fv.y, -2.0f);

    EXPECT_DOUBLE_EQ(dv.x, 3.0);
    EXPECT_DOUBLE_EQ(dv.y, -3.0);
}

TEST(Maths, Vector2_Addition) {
    Onyx::Maths::Vector2d a(-100.0, 100.0);
    Onyx::Maths::Vector2d b(0.204, -0.0001);

    Onyx::Maths::Vector2d val = a + b;

    EXPECT_DOUBLE_EQ(val.x, a.x + b.x);
    EXPECT_DOUBLE_EQ(val.y, a.y + b.y);
}

TEST(Maths, Vector2_Subtraction) {
    Onyx::Maths::Vector2d a(-100.0, 100.0);
    Onyx::Maths::Vector2d b(0.204, -0.0001);

    Onyx::Maths::Vector2d val = a - b;

    EXPECT_DOUBLE_EQ(val.x, a.x - b.x);
    EXPECT_DOUBLE_EQ(val.y, a.y - b.y);
}

TEST(Maths, Vector2_Multiplication) {
    const double scale = 300.0;

    const Onyx::Maths::Vector2d a(0.5, -0.5);
    const Onyx::Maths::Vector2d b(2.0, 0.0);

    const auto a_scaled_rhs = a * scale;
    const auto a_scaled_lhs = scale * a;
    const auto ab = a * b;

    EXPECT_DOUBLE_EQ(a_scaled_lhs.x, a.x * scale);
    EXPECT_DOUBLE_EQ(a_scaled_lhs.y, a.y * scale);

    EXPECT_DOUBLE_EQ(a_scaled_rhs.x, a_scaled_lhs.x);
    EXPECT_DOUBLE_EQ(a_scaled_rhs.y, a_scaled_lhs.y);

    EXPECT_DOUBLE_EQ(ab.x, a.x * b.x);
    EXPECT_DOUBLE_EQ(ab.y, a.y * b.y);
}

TEST(Maths, Vector2_Division) {}
TEST(Maths, Vector2_Scalar_Addition) {}
TEST(Maths, Vector2_Scalar_Subtraction) {}
TEST(Maths, Vector2_Scalar_Multiplication) {}
TEST(Maths, Vector2_Scalar_Division) {}
TEST(Maths, Vector2_Equality) {}
TEST(Maths, Vector2_Inequality) {}
TEST(Maths, Vector2_Dot) {}
TEST(Maths, Vector2_Length) {}
TEST(Maths, Vector2_Length_Squared) {}
TEST(Maths, Vector2_Normalize) {}
TEST(Maths, Vector2_Set) {}
TEST(Maths, Vector2_Distance) {};
TEST(Maths, Vector2_DistanceSquared) {};
TEST(Maths, Vector2_Lerp) {};
TEST(Maths, Vector2_Slerp) {};

//Vector 3
TEST(Maths, Vector3_Construction) {}
TEST(Maths, Vector3_Addition) {}
TEST(Maths, Vector3_Subtraction) {}
TEST(Maths, Vector3_Multiplication) {}
TEST(Maths, Vector3_Division) {}
TEST(Maths, Vector3_Scalar_Addition) {}
TEST(Maths, Vector3_Scalar_Subtraction) {}
TEST(Maths, Vector3_Scalar_Multiplication) {}
TEST(Maths, Vector3_Scalar_Division) {}
TEST(Maths, Vector3_Equality) {}
TEST(Maths, Vector3_Inequality) {}
TEST(Maths, Vector3_Dot) {
    Onyx::Maths::Vector3f a{0.5, -0.3, 1.0};
    Onyx::Maths::Vector3f b{1.0, 0.8, 0.2};

    double theta = acos(Onyx::Maths::Vector3f::Dot(a, b));
    double angleDegrees = Onyx::Maths::RadToDeg(theta);

    EXPECT_DOUBLE_EQ(angleDegrees, 62.612893881970322);
}
TEST(Maths, Vector3_Length) {}
TEST(Maths, Vector3_Length_Squared) {}
TEST(Maths, Vector3_Normalize) {}
TEST(Maths, Vector3_Set) {}

TEST(Maths, Vector3_Cross) {
    Onyx::Maths::Vector3<float> a = { 1.0, 2.0, 3.0 };
    Onyx::Maths::Vector3<float> b = { 3.0, 4.0, 5.0 };

    Onyx::Maths::Vector3<float> cross = Onyx::Maths::Vector3<float>::Cross(a, b);

    EXPECT_FLOAT_EQ(cross.x, -2.0f);
    EXPECT_FLOAT_EQ(cross.y, 4.0f);
    EXPECT_FLOAT_EQ(cross.z, -2.0f);
}

TEST(Maths, Vector3_Distance) {};
TEST(Maths, Vector3_DistanceSquared) {};
TEST(Maths, Vector3_Lerp) {};
TEST(Maths, Vector3_Slerp) {};

//Vector 4
TEST(Maths, Vector4_Construction) {}
TEST(Maths, Vector4_Addition) {}
TEST(Maths, Vector4_Subtraction) {}
TEST(Maths, Vector4_Multiplication) {}
TEST(Maths, Vector4_Division) {}
TEST(Maths, Vector4_Scalar_Addition) {}
TEST(Maths, Vector4_Scalar_Subtraction) {}
TEST(Maths, Vector4_Scalar_Multiplication) {}
TEST(Maths, Vector4_Scalar_Division) {}
TEST(Maths, Vector4_Equality) {}
TEST(Maths, Vector4_Inequality) {}
TEST(Maths, Vector4_Dot) {}
TEST(Maths, Vector4_Length) {}
TEST(Maths, Vector4_Length_Squared) {}
TEST(Maths, Vector4_Normalize) {}
TEST(Maths, Vector4_Set) {}


//Matrix 4x4
TEST(Maths, Matrix4x4_Construction) {}
TEST(Maths, Matrix4x4_Identity) {}
TEST(Maths, Matrix4x4_Multiplication) {}
TEST(Maths, Matrix4x4_Translation) {}
TEST(Maths, Matrix4x4_Rotation_X) {}
TEST(Maths, Matrix4x4_Rotation_Y) {}
TEST(Maths, Matrix4x4_Rotation_Z) {}
TEST(Maths, Matrix4x4_Scaling) {}
TEST(Maths, Matrix4x4_View) {}
TEST(Maths, Matrix4x4_Projection_FoV) {}
TEST(Maths, Matrix4x4_Projection_Orthographic) {}
TEST(Maths, Matrix4x4_Transpose) {}
TEST(Maths, Matrix4x4_Inverse) {}

//Quaternion
TEST(Maths, Quaternion_Construction) {};
TEST(Maths, Quaternion_Identity) {};
TEST(Maths, Quaternion_Multiplication) {};
TEST(Maths, Quaternion_Addition) {};
TEST(Maths, Quaternion_Conjugate) {};
TEST(Maths, Quaternion_Norm) {};
TEST(Maths, Quaternion_Inverse) {};
TEST(Maths, Quaternion_Comparison) {};

TEST(Maths, Quaternion_FromAxisAngle) {
    double theta = Onyx::Maths::DegToRad(30.0);

    Onyx::Maths::Quaternion qx = Onyx::Maths::Quaternion::FromAxisAngle<double>({ 1.0, 0.0, 0.0 }, theta);
    Onyx::Maths::Quaternion qy = Onyx::Maths::Quaternion::FromAxisAngle<double>({ 0.0, 1.0, 0.0 }, theta);
    Onyx::Maths::Quaternion qz = Onyx::Maths::Quaternion::FromAxisAngle<double>({ 0.0, 0.0, 1.0 }, theta);

    EXPECT_NEAR(qx.w, 0.9659, 0.0001);
    EXPECT_NEAR(qx.v.x, 0.2588, 0.0001);

    EXPECT_NEAR(qy.w, 0.9659, 0.0001);
    EXPECT_NEAR(qy.v.y, 0.2588, 0.0001);

    EXPECT_NEAR(qz.w, 0.9659, 0.0001);
    EXPECT_NEAR(qz.v.z, 0.2588, 0.0001);

};

TEST(Maths, Quaternion_ToAxisAngle) {
    double theta = Onyx::Maths::DegToRad(30.0);

    Onyx::Maths::Quaternion qx = Onyx::Maths::Quaternion::FromAxisAngle<double>({ 1.0, 0.0, 0.0 }, theta);

    auto ax = qx.ToAxisAngle<double>();
    EXPECT_NEAR(ax.x, 1.0, 0.0001);
    EXPECT_NEAR(ax.y, 0.0, 0.0001);
    EXPECT_NEAR(ax.z, 0.0, 0.0001);
    EXPECT_NEAR(ax.w, theta, 0.0001);

    Onyx::Maths::Quaternion qy = Onyx::Maths::Quaternion::FromAxisAngle<double>({ 0.0, 1.0, 0.0 }, theta);
    auto ay = qy.ToAxisAngle<double>();
    EXPECT_NEAR(ay.x, 0.0, 0.0001);
    EXPECT_NEAR(ay.y, 1.0, 0.0001);
    EXPECT_NEAR(ay.z, 0.0, 0.0001);
    EXPECT_NEAR(ay.w, theta, 0.0001);

    Onyx::Maths::Quaternion qz = Onyx::Maths::Quaternion::FromAxisAngle<double>({ 0.0, 0.0, 1.0 }, theta);
    auto az = qz.ToAxisAngle<double>();
    EXPECT_NEAR(az.x, 0.0, 0.0001);
    EXPECT_NEAR(az.y, 0.0, 0.0001);
    EXPECT_NEAR(az.z, 1.0, 0.0001);
    EXPECT_NEAR(az.w, theta, 0.0001);


};

TEST(Maths, Quaternion_FromMatrix4x4) {
    double theta = Onyx::Maths::DegToRad(30.0);

    const auto rx = Onyx::Maths::Matrix4x4<double>::XRotation(theta);
    const auto ry = Onyx::Maths::Matrix4x4<double>::YRotation(theta);
    const auto rz = Onyx::Maths::Matrix4x4<double>::ZRotation(theta);

    Onyx::Maths::Quaternion qx = Onyx::Maths::Quaternion::FromMatrix4x4(rx);
    Onyx::Maths::Quaternion qy = Onyx::Maths::Quaternion::FromMatrix4x4(ry);
    Onyx::Maths::Quaternion qz = Onyx::Maths::Quaternion::FromMatrix4x4(rz);

    auto ax = Onyx::Maths::Quaternion::FromAxisAngle<double>({ 1.0, 0.0 ,0.0 }, theta);
    auto ay = Onyx::Maths::Quaternion::FromAxisAngle<double>({ 0.0, 1.0 ,0.0 }, theta);
    auto az = Onyx::Maths::Quaternion::FromAxisAngle<double>({ 0.0, 0.0 ,1.0 }, theta);

    EXPECT_TRUE(qx == ax);
    EXPECT_TRUE(qy == ay);
    EXPECT_TRUE(qz == az);

};

TEST(Maths, Quaternion_ToMatrix4x4) {

    double theta = Onyx::Maths::DegToRad(30.0);

    Onyx::Maths::Quaternion qx = Onyx::Maths::Quaternion::FromAxisAngle<double>({ 1.0, 0.0, 0.0 }, theta);
    Onyx::Maths::Quaternion qy = Onyx::Maths::Quaternion::FromAxisAngle<double>({ 0.0, 1.0, 0.0 }, theta);
    Onyx::Maths::Quaternion qz = Onyx::Maths::Quaternion::FromAxisAngle<double>({ 0.0, 0.0, 1.0 }, theta);

    Onyx::Maths::Matrix4x4<double> mx = qx.ToMatrix4x4();
    Onyx::Maths::Matrix4x4<double> my = qy.ToMatrix4x4();
    Onyx::Maths::Matrix4x4<double> mz = qz.ToMatrix4x4();

    const auto rx = Onyx::Maths::Matrix4x4<double>::XRotation(theta);
    const auto ry = Onyx::Maths::Matrix4x4<double>::YRotation(theta);
    const auto rz = Onyx::Maths::Matrix4x4<double>::ZRotation(theta);

    EXPECT_EQ(mx == rx, true);
    EXPECT_EQ(my == ry, true);
    EXPECT_EQ(mz == rz, true);

};

TEST(Maths, Quaternion_FromEulerAngles) {

    Onyx::Maths::Vector3d axis{-40.0, 30.0, 90.0};
    Onyx::Maths::Quaternion q = Onyx::Maths::Quaternion::FromEulerAngles(axis);

    auto m0 = q.ToMatrix4x4();

    auto mx = Onyx::Maths::Matrix4x4<double>::XRotationFromDegrees(axis.x);
    auto my = Onyx::Maths::Matrix4x4<double>::YRotationFromDegrees(axis.y);
    auto mz = Onyx::Maths::Matrix4x4<double>::ZRotationFromDegrees(axis.z);

    auto rot = mx * (my * mz);

    //Rotate a point by both the quaternion and manual rotation matrix
    Onyx::Maths::Vector4d point{3.0, 400.0, -1.0, 1.0};

    auto p0 = point * q;
    auto p1 = point * rot;

    EXPECT_NEAR(p0.x, p1.x, 0.0001);
    EXPECT_NEAR(p0.y, p1.y, 0.0001);
    EXPECT_NEAR(p0.z, p1.z, 0.0001);
};

TEST(Maths, Quaternion_ToEulerAngles) {
    double theta = Onyx::Maths::DegToRad(30.0);

    Onyx::Maths::Quaternion qx = Onyx::Maths::Quaternion::FromAxisAngle<double>({ 1.0, 0.0, 0.0 }, theta);
    auto ax = qx.ToEulerAngles<double>();
    EXPECT_NEAR(ax.x, theta, 0.001);

    Onyx::Maths::Quaternion qy = Onyx::Maths::Quaternion::FromAxisAngle<double>({ 0.0, 1.0, 0.0 }, theta);
    auto ay = qy.ToEulerAngles<double>();
    EXPECT_NEAR(ay.y, theta, 0.001);

    Onyx::Maths::Quaternion qz = Onyx::Maths::Quaternion::FromAxisAngle<double>({ 0.0, 0.0, 1.0 }, theta);
    auto az = qz.ToEulerAngles<double>();
    EXPECT_NEAR(az.z, theta, 0.001);
};

TEST(Maths, Quaternion_Lerp) {

    Onyx::Maths::Quaternion q0 = Onyx::Maths::Quaternion::FromAxisAngle<double>({ 0.0, 1.0, 0.0 }, 0.0);
    Onyx::Maths::Quaternion q1 = Onyx::Maths::Quaternion::FromAxisAngle<double>({ 0.0, -1.0, 0.0 }, 0.0);

    auto q_lerp = Onyx::Maths::Quaternion::Lerp(q0, q1, 0.5);


};
TEST(Maths, Quaternion_Slerp) {
    Onyx::Maths::Quaternion q0 = Onyx::Maths::Quaternion::FromAxisAngle<double>({ 0.0, 1.0, 0.0 }, 10.0);
    Onyx::Maths::Quaternion q1 = Onyx::Maths::Quaternion::FromAxisAngle<double>({ 1.0, 1.0, 0.0 }, 0.0);

    auto q_slerp = Onyx::Maths::Quaternion::Slerp(q0, q1, 0.5);


};
