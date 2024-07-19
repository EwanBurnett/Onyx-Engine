#ifndef ONYX_CORE_CVAR_H
#define ONYX_CORE_CVAR_H

#include <cstdint>
#include <string> 

namespace Onyx {

    class CVarParameter; 

    class CVarManager {
    public:
        CVarManager(); 
        ~CVarManager(); 

        static CVarManager* Get();

        //Returns nullptr if var is not found. 
        virtual const bool* GetBoolCVar(const std::string& name) = 0;
        virtual void SetBoolCVar(const std::string& name, const bool value) = 0;

        virtual const int* GetIntCVar(const std::string& name) = 0;
        virtual void SetIntCVar(const std::string& name, const int value) = 0;

        virtual const float* GetFloatCVar(const std::string& name) = 0;
        virtual void SetFloatCVar(const std::string& name, const float value) = 0;

        virtual const std::string* GetStringCVar(const std::string& name) = 0;
        virtual void SetStringCVar(const std::string& name, const std::string& value) = 0;

        virtual CVarParameter* CreateBoolCVar(const char* name, const char* description, const bool defaultValue, const bool currentValue) = 0;
        virtual CVarParameter* CreateIntCVar(const char* name, const char* description, const int defaultValue, const int currentValue) = 0;
        virtual CVarParameter* CreateFloatCVar(const char* name, const char* description, const float defaultValue, const float currentValue) = 0;
        virtual CVarParameter* CreateStringCVar(const char* name, const char* description, const std::string& defaultValue, const std::string& currentValue) = 0;

    protected:
        constexpr static int MAX_BOOL_CVARS = 1000; 
        constexpr static int MAX_INT_CVARS = 1000; 
        constexpr static int MAX_FLOAT_CVARS = 1000; 
        constexpr static int MAX_STRING_CVARS = 200; 
    };

    template<typename T>
    struct AutoCVar {
    protected:
        int index; 
        using CVarType = T; 
    };

    struct AutoCVar_Bool : AutoCVar<bool>
    {
        AutoCVar_Bool(const char* name, const char* description, bool defaultValue);

        bool Get(); 
        bool* GetPtr(); 
        void Set(const bool value); 
    };

    struct AutoCVar_Int : AutoCVar<int>
    {
        AutoCVar_Int(const char* name, const char* description, int defaultValue);

        int Get();
        int* GetPtr();
        void Set(const int value);
    };

    struct AutoCVar_Float : AutoCVar<float>
    {
        AutoCVar_Float(const char* name, const char* description, float defaultValue);

        float Get();
        float* GetPtr();
        void Set(const float value);
    };

    struct AutoCVar_String : AutoCVar<std::string>
    {
        AutoCVar_String(const char* name, const char* description, std::string defaultValue);

        std::string Get();
        std::string* GetPtr();
        void Set(const std::string value);
    };
}
#endif