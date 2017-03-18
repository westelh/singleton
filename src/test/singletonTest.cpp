#include <string>
#include <gtest/gtest.h>
#include "singleton/singleton.h"

TEST(singleton, instance_reference) {
    auto* ptr = &elh::singleton<int>::get_instance();    
    auto* ptr2 = &elh::singleton<int>::get_instance();
    auto* dptr = &elh::singleton<long>::get_instance();
    ASSERT_EQ(ptr, ptr2);
    ASSERT_NE(ptr, (int*)dptr);
}

TEST(singleton, constructing_instance) {
    auto model = std::string("Weei");
    auto instance = elh::singleton<std::string>::get_instance("Weei");
    ASSERT_EQ(model, instance);
}
