#ifndef ONYX_CORE_EVENT_H
#define ONYX_CORE_EVENT_H
#include "String.h"
#include <vector> 
#include <unordered_map>
#include <functional> 

namespace Onyx {

    /**
     * @brief Base class for Events.
     * @tparam T
    */
    template<typename T>
    class Event {
    public:
        Event() = default;
        Event(T type, const String& name) : m_EventType(type), m_Name(name), m_IsHandled(false) {};
        virtual ~Event() {};

        inline const T GetType() const {
            return m_EventType;
        }

        template<typename EventType>
        inline EventType ToType() const
        {
            return static_cast<const EventType&>(*this);
        }

        inline const String& GetName() const {
            return m_Name;
        }

        virtual bool IsHandled() const {
            return m_IsHandled;
        }

    protected:
        T m_EventType;
        String m_Name;
        bool m_IsHandled;
    };

    template<typename T>
    class EventDispatcher
    {
    private:
        using Func = std::function<void(const Event<T>)>;
    public:
        /**
         * @brief Adds a listener to the event type. 
         * @param type Type of event to listen to. 
         * @param function Function to call on this event. 
        */
        inline void AddListener(T type, const Func& function) {
            m_Listeners[type].push_back(function); 
        }

    private:
        std::unordered_map<T, std::vector<Func>> m_Listeners;
    };
}
#endif
