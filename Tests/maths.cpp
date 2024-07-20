#include <gtest/gtest.h>
#include <Onyx/Maths/Maths.h> 

TEST(Onyx, TestInit) {
    EXPECT_EQ(0, 0);
}

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

}

TEST(Maths, Utils_RSqrt) {

}

TEST(Maths, Utils_Orthonormalize) {

}

//Vector 2

TEST(Maths, Vector2_Construction) {}
TEST(Maths, Vector2_Addition) {}
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
TEST(Maths, Vector3_Cross) {}

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


