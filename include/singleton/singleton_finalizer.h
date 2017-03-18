#ifndef INCLUDE_SINGLETON_FINALIZER
#define INCLUDE_SINGLETON_FINALIZER

#include <array>
#include <functional>

namespace elh{
    class singleton_finalizer final {
            static constexpr int MAX_FINALIZERS_SIZE = 50;
            static std::array<std::function<void()>, MAX_FINALIZERS_SIZE> finalizers;
        public:
            static void add_finalizer(std::function<void()> func);
            static int finalizers_size() noexcept;
            static void finalize() noexcept;
    };
}

#endif
