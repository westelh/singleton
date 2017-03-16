#ifndef INCLUDE_SINGLETON
#define INCLUDE_SINGLETON

#include <mutex>
#include "singleton_finalizer.h"

namespace elh {

    template <class T>
    class singleton final {
        public:
            template <class... Args>
            static T& get_instance(Args&&... args) {
                std::call_once(flag, create<Args&&...>, args...);
                if (instance == nullptr) throw bad_state("Instance wasn't created in spite of call create()");
                return *instance;
            }

            class bad_state : public std::runtime_error {
                public:
                    bad_state(const char* msg) : runtime_error(msg) {};
            };

        private:
            template <class... Args>
            static void create(Args&&... args) {
                instance = new T { args... };
                singleton_finalizer::add_finalizer(destroy);
            }

            static void destroy() {
                delete instance;
                instance = nullptr;
            }

            static std::once_flag flag;
            static T *instance;
    };
}

template <class T> std::once_flag elh::singleton<T>::flag;
template <class T> T* elh::singleton<T>::instance;

#endif
