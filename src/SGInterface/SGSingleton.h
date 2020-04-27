#pragma once
#include "SGDefine.h"
#include "SGIRuntimeModule.h"

namespace SG
{
    template <typename T>
    Interface SGSingleton
    {
    public:
        explicit SGSingleton() {}
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