#include <string>
#include <gtest/gtest.h>
#include "singleton/singleton.h"
using namespace std::literals::string_literals;

TEST(singleton, instance_reference) {
    auto* ptr = &elh::singleton<int>::get_instance();
    // same
    auto* ptr2 = &elh::singleton<int>::get_instance();
    // different
    auto* dptr = &elh::singleton<long>::get_instance();

    ASSERT_EQ(ptr, ptr2);
    ASSERT_NE(ptr, (int*)dptr);
}

TEST(singleton, constructing_instance) {
    auto model = "Weei"s;
    auto instance = elh::singleton<std::string>::get_instance("Weei");
    ASSERT_EQ(model, instance);
}
