#include "singleton/singleton_finalizer.h"

using namespace elh;
using sf = singleton_finalizer;

std::array<std::function<void()>, sf::MAX_FINALIZERS_SIZE> sf::finalizers {};

void sf::add_finalizer(std::function<void()> func) {
    finalizers[finalizers_size()] = func;
}

int sf::finalizers_size() noexcept {
    return finalizers.size();
}

void sf::finalize() noexcept {
    for(auto& i : finalizers) {
        if(i != nullptr) i();
    }
}
