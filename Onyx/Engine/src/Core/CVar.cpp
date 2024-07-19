#include "Onyx/Core/CVar.h"
#include <unordered_map>
#include <string> 
#include <mutex>
#include <shared_mutex>

namespace Onyx {

    enum class CVarType : char {
        NONE = 0,
        BOOL,
        INT,
        FLOAT,
        STRING
    };

    class CVarParameter {
    public:
        friend class CVarManagerImpl;

        int32_t arrayIndex;     //Index into CVarArray for the current type

        CVarType type;
        std::string name;
        std::string description;
    };

    template<typename T>
    struct CVarStorage {
        T initial;
        T current;
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
        const bool* GetBoolCVar(const std::string& name) override final;
        void SetBoolCVar(const std::string& name, const bool value) override final;

        const int* GetIntCVar(const std::string& name) override final;
        void SetIntCVar(const std::string& name, const int value) override final;

        const float* GetFloatCVar(const std::string& name) override final;
        void SetFloatCVar(const std::string& name, const float value) override final;

        const std::string* GetStringCVar(const std::string& name) override final;
        void SetStringCVar(const std::string& name, const std::string& value) override final;

        CVarParameter* CreateBoolCVar(const char* name, const char* description, const bool defaultValue, const bool currentValue) override final;
        CVarParameter* CreateIntCVar(const char* name, const char* description, const int defaultValue, const int currentValue) override final;
        CVarParameter* CreateFloatCVar(const char* name, const char* description, const float defaultValue, const float currentValue) override final;
        CVarParameter* CreateStringCVar(const char* name, const char* description, const std::string& defaultValue, const std::string& currentValue) override final;


    private:
        CVarArray<bool> m_BoolCVars{ MAX_BOOL_CVARS };
        CVarArray<int> m_IntCVars{ MAX_INT_CVARS };
        CVarArray<float> m_FloatCVars{ MAX_FLOAT_CVARS };
        CVarArray<std::string> m_StringCVars{ MAX_STRING_CVARS };

        std::unordered_map<std::string, CVarParameter> m_CVars;

        std::shared_mutex m_Mutex;

    public:

        template<typename T>
        CVarArray<T>* GetCVarArray();

        CVarParameter* GetCVar(const std::string& name);

        CVarParameter* InitCVar(const std::string& name, const std::string& description);

        template<typename T>
        T* GetCurrentCVar(const std::string& name);

        template<typename T>
        void SetCurrentCVar(const std::string& name, const T& value);

        static CVarManagerImpl* Get();

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
    return &m_IntCVars;
}

template<>
Onyx::CVarArray<float>* Onyx::CVarManagerImpl::GetCVarArray<float>() {
    return &m_FloatCVars;
}

template<>
Onyx::CVarArray<bool>* Onyx::CVarManagerImpl::GetCVarArray<bool>() {
    return &m_BoolCVars;
}

template<>
Onyx::CVarArray<std::string>* Onyx::CVarManagerImpl::GetCVarArray<std::string>() {
    return &m_StringCVars;
}


const bool* Onyx::CVarManagerImpl::GetBoolCVar(const std::string& name)
{
    return GetCurrentCVar<bool>(name);
}

void Onyx::CVarManagerImpl::SetBoolCVar(const std::string& name, const bool value)
{
    SetCurrentCVar<bool>(name, value);
}

const int* Onyx::CVarManagerImpl::GetIntCVar(const std::string& name)
{
    return GetCurrentCVar<int>(name);
}

void Onyx::CVarManagerImpl::SetIntCVar(const std::string& name, const int value)
{
    SetCurrentCVar<int>(name, value);
}

const float* Onyx::CVarManagerImpl::GetFloatCVar(const std::string& name)
{
    return GetCurrentCVar<float>(name);
}

void Onyx::CVarManagerImpl::SetFloatCVar(const std::string& name, const float value)
{
    SetCurrentCVar<float>(name, value);
}

const std::string* Onyx::CVarManagerImpl::GetStringCVar(const std::string& name)
{
    return GetCurrentCVar<std::string>(name);
}

void Onyx::CVarManagerImpl::SetStringCVar(const std::string& name, const std::string& value)
{
    SetCurrentCVar<std::string>(name, value);
}

Onyx::CVarParameter* Onyx::CVarManagerImpl::CreateBoolCVar(const char* name, const char* description, const bool defaultValue, const bool currentValue)
{
    std::unique_lock<std::shared_mutex> lock(m_Mutex);
    CVarParameter* param = InitCVar(name, description);
    if (!param) {
        return nullptr;
    }

    param->type = CVarType::BOOL;

    GetCVarArray<bool>()->Add(defaultValue, currentValue, param);

    return param;
}

Onyx::CVarParameter* Onyx::CVarManagerImpl::CreateIntCVar(const char* name, const char* description, const int defaultValue, const int currentValue)
{
    std::unique_lock<std::shared_mutex> lock(m_Mutex);
    CVarParameter* param = InitCVar(name, description);
    if (!param) {
        return nullptr;
    }

    param->type = CVarType::INT;

    GetCVarArray<int>()->Add(defaultValue, currentValue, param);

    return param;
}

Onyx::CVarParameter* Onyx::CVarManagerImpl::CreateFloatCVar(const char* name, const char* description, const float defaultValue, const float currentValue)
{
    std::unique_lock<std::shared_mutex> lock(m_Mutex);
    CVarParameter* param = InitCVar(name, description);
    if (!param) {
        return nullptr;
    }

    param->type = CVarType::FLOAT;

    GetCVarArray<float>()->Add(defaultValue, currentValue, param);

    return param;
}

Onyx::CVarParameter* Onyx::CVarManagerImpl::CreateStringCVar(const char* name, const char* description, const std::string& defaultValue, const std::string& currentValue)
{
    std::unique_lock<std::shared_mutex> lock(m_Mutex);
    CVarParameter* param = InitCVar(name, description);
    if (!param) {
        return nullptr;
    }

    param->type = CVarType::STRING;

    GetCVarArray<std::string>()->Add(defaultValue, currentValue, param);

    return param;
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
    delete m_CVars;
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

Onyx::AutoCVar_Bool::AutoCVar_Bool(const char* name, const char* description, bool defaultValue)
{
    CVarParameter* param = CVarManager::Get()->CreateBoolCVar(name, description, defaultValue, defaultValue);
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
    CVarParameter* param = CVarManager::Get()->CreateIntCVar(name, description, defaultValue, defaultValue);
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
    CVarParameter* param = CVarManager::Get()->CreateFloatCVar(name, description, defaultValue, defaultValue);
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
    CVarParameter* param = CVarManager::Get()->CreateStringCVar(name, description, defaultValue, defaultValue);
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

