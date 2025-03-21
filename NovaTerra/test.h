#pragma once

#include "test.g.h"

namespace winrt::NovaTerra::implementation
{
    struct test : testT<test>
    {
        test() = default;

        int32_t MyProperty();
        void MyProperty(int32_t value);
    };
}

namespace winrt::NovaTerra::factory_implementation
{
    struct test : testT<test, implementation::test>
    {
    };
}
