#ifndef WORKING_SPACE_SINGLETON_H
#define WORKING_SPACE_SINGLETON_H

#include <boost/thread/recursive_mutex.hpp>

template <typename T>
class Singleton
{
public:
    static T& get_instance()
    {
        if (m_pInstance == NULL)
        {
            lock_.lock();
            if (m_pInstance == NULL)
            {
                m_pInstance = new T();
                atexit(Destroy);
            }
            lock_.unlock();
            return *m_pInstance;
        }
        return *m_pInstance;
    }

protected:
    Singleton(void) {}
    ~Singleton(void) {}

private:
    Singleton(const Singleton& rhs) {}
    Singleton& operator = (const Singleton& rhs) {}

    static void Destroy()
    {
        if (m_pInstance != NULL)
            delete m_pInstance;
        m_pInstance = NULL;
    }

    static T* volatile m_pInstance;
    static boost::recursive_mutex lock_;
};

template <typename T>
T* volatile Singleton<T>::m_pInstance = nullptr;

template <typename T>
boost::recursive_mutex Singleton<T>::lock_;

#endif // WORKING_SPACE_SINGLETON_H
