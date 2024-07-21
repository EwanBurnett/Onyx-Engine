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
    char buffer[0xff];
    memset(buffer, '\0', 0xff);
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
    Onyx::CVarManager::Get()->SetCVar_Bool("Engine.Log.EnableForwarding", true);
#endif
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

    //Conversions between degrees and radians
    float degrees = 60; 
    float radians = Onyx::Maths::DegToRad(degrees);
    Log::Print("%f degrees = %f radians.\n", degrees, radians);
    degrees = Maths::RadToDeg(radians); 
    Log::Print("%f radians = %f degrees.\n", radians, degrees); 

    //Clamp Arithmetic types
    float value = Onyx::Maths::PI; 
    float vMin = 0.0f; 
    float vMax = 1.0f; 
    value = Maths::Clamp(value, vMin, vMax); 




    Onyx::Maths::Vector3f pos = { 0.0f, 1.0f, 2.0f };
    const char* v = FormatVector3(pos).c_str();
    //Onyx::Log::Print("pos = %s\n", v);

    Onyx::Maths::Matrix4x4<> mat = {};
    static float rot = 0.0f;
    rot += 0.005f;
    mat = Onyx::Maths::Matrix4x4<>::XRotationFromDegrees(rot);
    Onyx::Log::Print("rot = %f\n", rot);
    //Onyx::Log::Print("mat = \n%s", FormatMatrix4x4(mat).c_str());
    printf("\033[6A");

    fclose(logFile);

    return 0;
}