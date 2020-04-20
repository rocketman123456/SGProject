#pragma once
#include "SGDefine.h"

namespace SG
{
    template <typename T>
    Interface SGSingleton
    {
    public:
        SGSingleton() {}
        ~SGSingleton() {}

        static T& GetSingleton()
        {
            static T s_singleton;
            return s_singleton;
        }

    private:
        SGSingleton(const SGSingleton&) = delete;
        const SGSingleton& operator= (const SGSingleton&) = delete;
    };
}