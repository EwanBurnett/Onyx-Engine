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

}

TEST(Maths, Vector2_Subtraction) {}
TEST(Maths, Vector2_Multiplication) {}
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
TEST(Maths, Vector3_Dot) {}
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
TEST(Maths, Quaternion_FromAxisAngle) {};
TEST(Maths, Quaternion_ToAxisAngle) {};
TEST(Maths, Quaternion_FromMatrix4x4) {};
TEST(Maths, Quaternion_ToMatrix4x4) {

    double theta = Onyx::Maths::DegToRad(30.0);

    Onyx::Maths::Quaternion qx = Onyx::Maths::Quaternion::FromAxisAngle<double>({ 1.0, 0.0, 0.0 }, theta);
    Onyx::Maths::Quaternion qy = Onyx::Maths::Quaternion::FromAxisAngle<double>({ 0.0, 1.0, 0.0 }, theta);
    Onyx::Maths::Quaternion qz = Onyx::Maths::Quaternion::FromAxisAngle<double>({ 0.0, 0.0, 1.0 }, theta);

    Onyx::Maths::Matrix4x4<double> mx = qx.ToMatrix4x4();
    Onyx::Maths::Matrix4x4<double> my = qy.ToMatrix4x4();
    Onyx::Maths::Matrix4x4<double> mz = qz.ToMatrix4x4();
    auto rx = Onyx::Maths::Matrix4x4<double>::XRotation(theta);
    auto ry = Onyx::Maths::Matrix4x4<double>::YRotation(theta);   
    auto rz = Onyx::Maths::Matrix4x4<double>::ZRotation(theta);    

    EXPECT_EQ(mx == rx, true);
    EXPECT_EQ(my == ry, true);
    EXPECT_EQ(mz == rz, true);

};
TEST(Maths, Quaternion_FromEulerAngles) {};
TEST(Maths, Quaternion_ToEulerAngles) {};
TEST(Maths, Quaternion_RotateVectorAxis) {};
TEST(Maths, Quaternion_Slerp) {};
