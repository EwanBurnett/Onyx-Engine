#ifndef ONYX_CORE_CVAR_H
#define ONYX_CORE_CVAR_H
/**
* @file CVar.h
* @brief Console Variable System
* @details Enables the user to set and retrieve Console Variables of simple data types.
* @details Currently supports `bool`, `int`, `float` and `std::string` types.
*
* ------------------------------------------
* @author Ewan Burnett(EwanBurnettSK@Outlook.com)
* @date 2024 - 07 - 20
*/

#include <cstdint>
#include <string> 
#include <vector> 

namespace Onyx {

    /**
     * @brief The Data Type of this CVar.
    */
    enum class CVarType : char {
        NONE = 0,
        Bool,
        Int,
        Float,
        String
    };

    /**
     * @brief Represents a CVar's internal data. 
    */
    struct CVarData {
        const std::string* pName;
        const std::string* pDescription;
        CVarType type;
        void* pInitialData;
        void* pCurrentData;

        void operator = (const CVarData& cvar) {
            this->pName = cvar.pName;
            this->pDescription = cvar.pDescription;
            this->type = cvar.type;
            this->pCurrentData = cvar.pCurrentData;
            this->pInitialData = cvar.pInitialData;
        }
    };

    class CVarParameter;

    class CVarManager {
    public:
        CVarManager();
        ~CVarManager();

        static CVarManager* Get();

        //Returns nullptr if var is not found. 
        virtual const bool* GetCVar_Bool(const std::string& name) = 0;
        virtual void SetCVar_Bool(const std::string& name, const bool value) = 0;
        virtual CVarParameter* CreateCVar_Bool(const char* name, const char* description, const bool defaultValue, const bool currentValue) = 0;

        virtual const int* GetCVar_Int(const std::string& name) = 0;
        virtual void SetCVar_Int(const std::string& name, const int value) = 0;
        virtual CVarParameter* CreateCVar_Int(const char* name, const char* description, const int defaultValue, const int currentValue) = 0;

        virtual const float* GetCVar_Float(const std::string& name) = 0;
        virtual void SetCVar_Float(const std::string& name, const float value) = 0;
        virtual CVarParameter* CreateCVar_Float(const char* name, const char* description, const float defaultValue, const float currentValue) = 0;

        virtual const std::string* GetCVar_String(const std::string& name) = 0;
        virtual void SetCVar_String(const std::string& name, const std::string& value) = 0;
        virtual CVarParameter* CreateCVar_String(const char* name, const char* description, const std::string& defaultValue, const std::string& currentValue) = 0;

        virtual std::vector<CVarData> GetCVarData() const = 0;
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

    /**
    * @brief Declares an AutoCVar of type T, and a specified CVarType
    */
    #define AUTOCVAR_DECLARATION(T, CVarType) struct AutoCVar_##CVarType : AutoCVar<T> { \
        AutoCVar_##CVarType(const char* name, const char* description, T defaultValue); \
        \
        T Get(); \
        T* GetPtr(); \
        void Set(const T value); \
    }; \

    AUTOCVAR_DECLARATION(bool, Bool);
    AUTOCVAR_DECLARATION(int, Int);
    AUTOCVAR_DECLARATION(float, Float);
    AUTOCVAR_DECLARATION(std::string, String);

    /*
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
    */
}
#endif