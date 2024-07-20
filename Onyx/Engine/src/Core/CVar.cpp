#include "Onyx/Core/CVar.h"
#include <unordered_map>
#include <algorithm>
#include <string> 
#include <mutex>
#include <shared_mutex>

#define AUTOCVAR_IMPLEMENTATION(T, CVarType)\
\
Onyx::AutoCVar_##CVarType::AutoCVar_##CVarType(const char* name, const char* description, T defaultValue)\
{\
    CVarParameter* param = CVarManager::Get()->CreateCVar_##CVarType(name, description, defaultValue, defaultValue);\
    index = param->arrayIndex;\
}\
\
T Onyx::AutoCVar_##CVarType::Get()\
{\
    return GetCurrentCVarByIndex<T>(index);\
}\
\
T* Onyx::AutoCVar_##CVarType::GetPtr()\
{\
    return PtrGetCurrentCVarByIndex<T>(index);\
}\
\
void Onyx::AutoCVar_##CVarType::Set(const T value)\
{\
    return SetCurrentCVarByIndex<T>(index, value);\
}\

namespace Onyx {

    class CVarParameter {
    public:
        friend class CVarManagerImpl;

        int32_t arrayIndex = -1;     //Index into CVarArray for the current type

        CVarType type = CVarType::NONE;
        std::string name;
        std::string description;
    };

    template<typename T>
    struct CVarStorage {
        T initial = {};
        T current = {};
        CVarParameter* parameter = nullptr;
    };

    template<typename T>
    struct CVarArray
    {
        CVarStorage<T>* m_CVars;
        int32_t m_LastCVar{ 0 };

        CVarArray(const size_t size);
        ~CVarArray();

        T GetCurrent(int32_t index);
        T* GetCurrentPtr(int32_t index);
        void SetCurrent(const T& value, int32_t index);


        int Add(const T& value, CVarParameter* pParam);
        int Add(const T& initialValue, const T& currentValue, CVarParameter* pParam);
    };

    class CVarManagerImpl : public CVarManager {
    public:

        CVarManagerImpl();
        ~CVarManagerImpl();

        // Inherited via CVarManager
        const bool* GetCVar_Bool(const std::string& name) override final;
        void SetCVar_Bool(const std::string& name, const bool value) override final;
        CVarParameter* CreateCVar_Bool(const char* name, const char* description, const bool defaultValue, const bool currentValue) override final;
        CVarArray<bool> m_CVars_Bool{ MAX_BOOL_CVARS };

        const int* GetCVar_Int(const std::string& name) override final;
        void SetCVar_Int(const std::string& name, const int value) override final;
        CVarParameter* CreateCVar_Int(const char* name, const char* description, const int defaultValue, const int currentValue) override final;
        CVarArray<int> m_CVars_Int{ MAX_INT_CVARS };

        const float* GetCVar_Float(const std::string& name) override final;
        void SetCVar_Float(const std::string& name, const float value) override final;
        CVarParameter* CreateCVar_Float(const char* name, const char* description, const float defaultValue, const float currentValue) override final;
        CVarArray<float> m_CVars_Float{ MAX_FLOAT_CVARS };

        const std::string* GetCVar_String(const std::string& name) override final;
        void SetCVar_String(const std::string& name, const std::string& value) override final;
        CVarParameter* CreateCVar_String(const char* name, const char* description, const std::string& defaultValue, const std::string& currentValue) override final;
        CVarArray<std::string> m_CVars_String{ MAX_STRING_CVARS };


        std::vector<CVarData> GetCVarData() const override final;

        template<typename T>
        CVarArray<T>* GetCVarArray();

        CVarParameter* GetCVar(const std::string& name);

        CVarParameter* InitCVar(const std::string& name, const std::string& description);

        template<typename T>
        T* GetCurrentCVar(const std::string& name);

        template<typename T>
        void SetCurrentCVar(const std::string& name, const T& value);

        static CVarManagerImpl* Get();

    private:
        std::unordered_map<std::string, CVarParameter> m_CVars;
        std::shared_mutex m_Mutex;

    };
}

Onyx::CVarManagerImpl::CVarManagerImpl()
{
}

Onyx::CVarManagerImpl::~CVarManagerImpl()
{
}

template<typename T>
Onyx::CVarArray<T>* Onyx::CVarManagerImpl::GetCVarArray() {
    return nullptr;
}


template<>
Onyx::CVarArray<int>* Onyx::CVarManagerImpl::GetCVarArray<int>() {
    return &m_CVars_Int;
}

template<>
Onyx::CVarArray<float>* Onyx::CVarManagerImpl::GetCVarArray<float>() {
    return &m_CVars_Float;
}

template<>
Onyx::CVarArray<bool>* Onyx::CVarManagerImpl::GetCVarArray<bool>() {
    return &m_CVars_Bool;
}

template<>
Onyx::CVarArray<std::string>* Onyx::CVarManagerImpl::GetCVarArray<std::string>() {
    return &m_CVars_String;
}


const bool* Onyx::CVarManagerImpl::GetCVar_Bool(const std::string& name)
{
    return GetCurrentCVar<bool>(name);
}

void Onyx::CVarManagerImpl::SetCVar_Bool(const std::string& name, const bool value)
{
    SetCurrentCVar<bool>(name, value);
}

const int* Onyx::CVarManagerImpl::GetCVar_Int(const std::string& name)
{
    return GetCurrentCVar<int>(name);
}

void Onyx::CVarManagerImpl::SetCVar_Int(const std::string& name, const int value)
{
    SetCurrentCVar<int>(name, value);
}

const float* Onyx::CVarManagerImpl::GetCVar_Float(const std::string& name)
{
    return GetCurrentCVar<float>(name);
}

void Onyx::CVarManagerImpl::SetCVar_Float(const std::string& name, const float value)
{
    SetCurrentCVar<float>(name, value);
}

const std::string* Onyx::CVarManagerImpl::GetCVar_String(const std::string& name)
{
    return GetCurrentCVar<std::string>(name);
}

void Onyx::CVarManagerImpl::SetCVar_String(const std::string& name, const std::string& value)
{
    SetCurrentCVar<std::string>(name, value);
}

Onyx::CVarParameter* Onyx::CVarManagerImpl::CreateCVar_Bool(const char* name, const char* description, const bool defaultValue, const bool currentValue)
{
    std::unique_lock<std::shared_mutex> lock(m_Mutex);
    CVarParameter* param = InitCVar(name, description);
    if (!param) {
        return nullptr;
    }

    param->type = CVarType::Bool;

    GetCVarArray<bool>()->Add(defaultValue, currentValue, param);

    return param;
}

Onyx::CVarParameter* Onyx::CVarManagerImpl::CreateCVar_Int(const char* name, const char* description, const int defaultValue, const int currentValue)
{
    std::unique_lock<std::shared_mutex> lock(m_Mutex);
    CVarParameter* param = InitCVar(name, description);
    if (!param) {
        return nullptr;
    }

    param->type = CVarType::Int;

    GetCVarArray<int>()->Add(defaultValue, currentValue, param);

    return param;
}

Onyx::CVarParameter* Onyx::CVarManagerImpl::CreateCVar_Float(const char* name, const char* description, const float defaultValue, const float currentValue)
{
    std::unique_lock<std::shared_mutex> lock(m_Mutex);
    CVarParameter* param = InitCVar(name, description);
    if (!param) {
        return nullptr;
    }

    param->type = CVarType::Float;

    GetCVarArray<float>()->Add(defaultValue, currentValue, param);

    return param;
}

Onyx::CVarParameter* Onyx::CVarManagerImpl::CreateCVar_String(const char* name, const char* description, const std::string& defaultValue, const std::string& currentValue)
{
    std::unique_lock<std::shared_mutex> lock(m_Mutex);
    CVarParameter* param = InitCVar(name, description);
    if (!param) {
        return nullptr;
    }

    param->type = CVarType::String;

    GetCVarArray<std::string>()->Add(defaultValue, currentValue, param);

    return param;
}

std::vector<Onyx::CVarData> Onyx::CVarManagerImpl::GetCVarData() const
{
    std::vector<CVarData> cvars;

    for (int i = 0; i < m_CVars_Bool.m_LastCVar; i++) {
        const CVarData data = {
            &m_CVars_Bool.m_CVars[i].parameter->name,
            &m_CVars_Bool.m_CVars[i].parameter->description,
            CVarType::Bool,
            &m_CVars_Bool.m_CVars[i].initial,
            &m_CVars_Bool.m_CVars[i].current
        };

        cvars.push_back(data);
    }

    for (int i = 0; i < m_CVars_Int.m_LastCVar; i++) {
        const CVarData data = {
            &m_CVars_Int.m_CVars[i].parameter->name,
            &m_CVars_Int.m_CVars[i].parameter->description,
            CVarType::Int,
            &m_CVars_Int.m_CVars[i].initial,
            &m_CVars_Int.m_CVars[i].current
        };

        cvars.push_back(data);
    }

    for (int i = 0; i < m_CVars_Float.m_LastCVar; i++) {
        const CVarData data = {
            &m_CVars_Float.m_CVars[i].parameter->name,
            &m_CVars_Float.m_CVars[i].parameter->description,
            CVarType::Float,
            &m_CVars_Float.m_CVars[i].initial,
            &m_CVars_Float.m_CVars[i].current
        };

        cvars.push_back(data);
    }

    for (int i = 0; i < m_CVars_String.m_LastCVar; i++) {
        const CVarData data = {
            &m_CVars_String.m_CVars[i].parameter->name,
            &m_CVars_String.m_CVars[i].parameter->description,
            CVarType::String,
            &m_CVars_String.m_CVars[i].initial,
            &m_CVars_String.m_CVars[i].current
        };

        cvars.push_back(data);
    }

    std::sort(cvars.begin(), cvars.end(), [](const CVarData& a, const CVarData& b) {
        return *a.pName < *b.pName;
        });

    return cvars;

}

Onyx::CVarParameter* Onyx::CVarManagerImpl::GetCVar(const std::string& name)
{
    std::shared_lock<std::shared_mutex> lock(m_Mutex);  //Lock for concurrent access
    auto itr = m_CVars.find(name);  //Search our CVar map for the key. 
    if (itr != m_CVars.end())
    {
        return &(*itr).second;
    }

    return nullptr;     //If we can't find the CVar, return nullptr. 
}

Onyx::CVarParameter* Onyx::CVarManagerImpl::InitCVar(const std::string& name, const std::string& description)
{
    m_CVars[name] = CVarParameter{};

    CVarParameter& param = m_CVars[name];

    param.name = name;
    param.description = description;

    return &param;
}

Onyx::CVarManagerImpl* Onyx::CVarManagerImpl::Get()
{
    return static_cast<CVarManagerImpl*>(CVarManager::Get());
}


template<typename T>
T* Onyx::CVarManagerImpl::GetCurrentCVar(const std::string& name)
{
    CVarParameter* param = GetCVar(name);

    if (!param) {
        return nullptr;
    }
    else {
        return GetCVarArray<T>()->GetCurrentPtr(param->arrayIndex);
    }
}

template<typename T>
void Onyx::CVarManagerImpl::SetCurrentCVar(const std::string& name, const T& value)
{
    CVarParameter* param = GetCVar(name);
    if (param) {
        GetCVarArray<T>()->SetCurrent(value, param->arrayIndex);
    }
}



Onyx::CVarManager::CVarManager()
{
}

Onyx::CVarManager::~CVarManager()
{
}

Onyx::CVarManager* Onyx::CVarManager::Get()
{
    static CVarManagerImpl cVarMgr{};
    return &cVarMgr;
}


template<typename T>
Onyx::CVarArray<T>::CVarArray(const size_t size)
{
    m_CVars = new CVarStorage<T>[size]();
}

template<typename T>
Onyx::CVarArray<T>::~CVarArray()
{
    delete[] m_CVars;
}

template<typename T>
T Onyx::CVarArray<T>::GetCurrent(int32_t index)
{
    return m_CVars[index].current;
}

template<typename T>
T* Onyx::CVarArray<T>::GetCurrentPtr(int32_t index)
{
    return &m_CVars[index].current;
}

template<typename T>
void Onyx::CVarArray<T>::SetCurrent(const T& value, int32_t index)
{
    m_CVars[index].current = value;
}

template<typename T>
int Onyx::CVarArray<T>::Add(const T& value, CVarParameter* pParam)
{
    const int index = m_LastCVar;

    m_CVars[index].initial = value;
    m_CVars[index].current = value;
    m_CVars[index].parameter = pParam;

    pParam->arrayIndex = index;
    m_LastCVar++;

    return index;
}

template<typename T>
int Onyx::CVarArray<T>::Add(const T& initialValue, const T& currentValue, CVarParameter* pParam)
{
    const int index = m_LastCVar;

    m_CVars[index].initial = initialValue;
    m_CVars[index].current = currentValue;
    m_CVars[index].parameter = pParam;

    pParam->arrayIndex = index;
    m_LastCVar++;

    return index;
}


template<typename T>
T GetCurrentCVarByIndex(int32_t index) {
    return Onyx::CVarManagerImpl::Get()->GetCVarArray<T>()->GetCurrent(index);
}

template<typename T>
T* PtrGetCurrentCVarByIndex(int32_t index) {
    return Onyx::CVarManagerImpl::Get()->GetCVarArray<T>()->GetCurrentPtr(index);
}

template<typename T>
void SetCurrentCVarByIndex(int32_t index, const T& data) {
    Onyx::CVarManagerImpl::Get()->GetCVarArray<T>()->SetCurrent(data, index);
}


AUTOCVAR_IMPLEMENTATION(bool, Bool)
AUTOCVAR_IMPLEMENTATION(int, Int)
AUTOCVAR_IMPLEMENTATION(float, Float)
AUTOCVAR_IMPLEMENTATION(std::string, String)

/*
Onyx::AutoCVar_Bool::AutoCVar_Bool(const char* name, const char* description, bool defaultValue)
{
    CVarParameter* param = CVarManager::Get()->CreateCVar_Bool(name, description, defaultValue, defaultValue);
    index = param->arrayIndex;
}

bool Onyx::AutoCVar_Bool::Get()
{
    return GetCurrentCVarByIndex<bool>(index);
}

bool* Onyx::AutoCVar_Bool::GetPtr()
{
    return PtrGetCurrentCVarByIndex<bool>(index);
}

void Onyx::AutoCVar_Bool::Set(const bool value)
{
    return SetCurrentCVarByIndex<bool>(index, value);
}

Onyx::AutoCVar_Int::AutoCVar_Int(const char* name, const char* description, int defaultValue)
{
    CVarParameter* param = CVarManager::Get()->CreateCVar_Bool(name, description, defaultValue, defaultValue);
    index = param->arrayIndex;
}

int Onyx::AutoCVar_Int::Get()
{
    return GetCurrentCVarByIndex<int>(index);
}

int* Onyx::AutoCVar_Int::GetPtr()
{
    return PtrGetCurrentCVarByIndex<int>(index);
}

void Onyx::AutoCVar_Int::Set(const int value)
{
    return SetCurrentCVarByIndex<int>(index, value);
}

Onyx::AutoCVar_Float::AutoCVar_Float(const char* name, const char* description, float defaultValue)
{
    CVarParameter* param = CVarManager::Get()->CreateCVar_Float(name, description, defaultValue, defaultValue);
    index = param->arrayIndex;
}

float Onyx::AutoCVar_Float::Get()
{
    return GetCurrentCVarByIndex<float>(index);
}

float* Onyx::AutoCVar_Float::GetPtr()
{
    return PtrGetCurrentCVarByIndex<float>(index);
}

void Onyx::AutoCVar_Float::Set(const float value)
{
    return SetCurrentCVarByIndex<float>(index, value);
}


Onyx::AutoCVar_String::AutoCVar_String(const char* name, const char* description, std::string defaultValue)
{
    CVarParameter* param = CVarManager::Get()->CreateCVar_String(name, description, defaultValue, defaultValue);
    index = param->arrayIndex;
}

std::string Onyx::AutoCVar_String::Get()
{
    return GetCurrentCVarByIndex<std::string>(index);
}

std::string* Onyx::AutoCVar_String::GetPtr()
{
    return PtrGetCurrentCVarByIndex<std::string>(index);
}

void Onyx::AutoCVar_String::Set(const std::string value)
{
    return SetCurrentCVarByIndex<std::string>(index, value);
}
*/

