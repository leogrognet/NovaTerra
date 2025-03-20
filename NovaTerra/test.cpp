#include "pch.h"
#include "test.h"
#if __has_include("test.g.cpp")
#include "test.g.cpp"
#endif

namespace winrt::NovaTerra::implementation
{
    int32_t test::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void test::MyProperty(int32_t /*value*/)
    {
        throw hresult_not_implemented();
    }
}
