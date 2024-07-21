#include <cstdio>
#include <Onyx.h>
#include <Onyx/Core/CVar.h>
#include <Onyx/Maths/Maths.h>
#include <cstring>
#include <cstdio>

#if ONYX_PLATFORM_WINDOWS
const char* platformName = "Windows";
#elif ONYX_PLATFORM_LINUX
const char* platformName = "Linux";
#endif

template<typename T>
std::string FormatVector2(const Onyx::Maths::Vector2<T>& vector) {
    char buffer[0xff];
    sprintf(buffer[0xff], "(%f, %f)", vector.x, vector.y);
    return buffer;
}

template<typename T>
std::string FormatVector3(const Onyx::Maths::Vector3<T>& vector) {
    static char buffer[0xff];
    sprintf(buffer, "(%f, %f, %f)", vector.x, vector.y, vector.z);

    return buffer;
}

template<typename T>
std::string FormatVector4(const Onyx::Maths::Vector4<T>& vector) {
    char buffer[0xff];
    std::string str(strlen(buffer));
    snprintf(buffer, "(%f, %f, %f, %f)", vector.x, vector.y, vector.z, vector.w);
    return str;
}

template<typename T>
std::string FormatMatrix4x4(const Onyx::Maths::Matrix4x4<T>& mat) {
    char buffer[0x1ff];
    memset(buffer, 0x00, 0x1ff);
    for (int i = 0; i < 16; i += 4) {
        char buf[0xff];
        sprintf(buf, "| %f, %f, %f, %f |\n", mat[i + 0], mat[i + 1], mat[i + 2], mat[i + 3]);
        strcat(buffer, buf);
    }
    return buffer;
}

using namespace Onyx;

int main() {
    Onyx::Init();

    Onyx::Log::Status("[%s]\tOnyx Version: %s\n", platformName, Onyx::GetVersionString().c_str());

#if ONYX_DEBUG
#endif
    Onyx::CVarManager::Get()->SetCVar_Bool("Engine.Log.EnableForwarding", true);
    FILE* logFile = fopen("Log.txt", "a+");
    Onyx::Log::SetOutputStream(logFile);

    // Maths Constants
    Log::Print("PI = %f\n", Maths::PI);
    Log::Print("Degrees to Radians constant = %.38f\n", Maths::Deg2Rad);
    Log::Print("Radians to Degrees constant = %.38f\n", Maths::Rad2Deg);
    Log::Print("Infinity = %f\n", Maths::Infinity); 
    Log::Print("Epsilon = %.38f\n", Maths::Epsilon);
    Log::Print("Float Min = %.38f\n", Maths::Float_Min);
    Log::Print("Float Max = %f\n", Maths::Float_Max);
    Log::Print("Int Min = %d\n", Maths::Int_Min);
    Log::Print("Int Max = %d\n", Maths::Int_Max);
    
    // Maths Utility Methods
    printf("\n");
    //Conversions between degrees and radians
    float degrees = 60; 
    float radians = Onyx::Maths::DegToRad(degrees);
    Log::Print("%f degrees = %f radians.\n", degrees, radians);
    degrees = Maths::RadToDeg(radians); 
    Log::Print("%f radians = %f degrees.\n", radians, degrees); 

    printf("\n"); 

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


    Onyx::Maths::Vector3f v0(3, -5, 4);
    Onyx::Maths::Vector3f v1(2, 6, 5);

    auto c = Onyx::Maths::Vector3f::Cross(v0, v1); 

    Onyx::Maths::Quaternion q0(9, 1, 4, 9);
    Onyx::Maths::Quaternion q1(3, 2, 16, 6);

    auto q2 = q0 * q1;
    printf("\n");
    printf("Quaternion Mul = [%f](%f, %f, %f)\n", q2.w, q2.v.x, q2.v.y, q2.v.z);

    Onyx::Maths::Vector3f v(0.0, 0.0, -1.0); 
    Onyx::Maths::Vector3f a(0.0, 1.0, 0.0);

    auto y = Onyx::Maths::Matrix4x4<double>::YRotationFromDegrees(90.0);
    auto ry = Onyx::Maths::Quaternion::FromMatrix4x4(y); 
    auto ry_m = ry.ToMatrix4x4(); 

    float rotationDegrees = 30; 
    Onyx::Maths::Vector4<float> vf {v.x, v.y, v.z, 1.0f};
    auto rotated = Onyx::Maths::Quaternion::RotateVector(v, a, Onyx::Maths::DegToRad(rotationDegrees));
    Onyx::Maths::Vector4f rotMat =  vf * Onyx::Maths::Matrix4x4<float>::YRotationFromDegrees(rotationDegrees);

    printf("Vector (%f, %f, %f) rotated by %f deg about axis (%f, %f, %f):\n\tQuaternion = (%f, %f, %f)\n\tMatrix = (%f, %f, %f)\n",
        v.x, v.y, v.z,
        rotationDegrees,
        a.x, a.y, a.z,
        rotated.x, rotated.y, rotated.z, 
        rotMat.x, rotMat.y, rotMat.z);
    fclose(logFile);

    return 0;
}