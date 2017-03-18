#ifndef INCLUDE_SINGLETON
#define INCLUDE_SINGLETON

#include <mutex>
#include "singleton_finalizer.h"

namespace elh {

    template <class T>
    class singleton final {
            // Create unique instance here
            template <class... Args>
            static void create(Args&&... args) {
                instance = new T { args... };
                singleton_finalizer::add_finalizer(destroy);
            }

            // To pass to finalizer
            static void destroy() {
                delete instance;
                instance = nullptr;
            }

            static std::once_flag flag;
            static T *instance;

            singleton() = delete;

        public:
            // Interface for users
            template <class... Args>
            static T& get_instance(Args&&... args) {
                std::call_once(flag, create<Args&&...>, args...);
                if (instance == nullptr) throw std::runtime_error{"Instance is null in spite of create() called."};
                return *instance;
            }
    };
}

template <class T> std::once_flag elh::singleton<T>::flag;
template <class T> T* elh::singleton<T>::instance;

#endif
