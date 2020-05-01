#pragma once
#include "SGDefine.h"

namespace SG
{
    template <typename T>
    Interface SGISingleton
    {
    public:
        explicit SGISingleton() {}
        ~SGISingleton() {}

        static T& GetSingleton()
        {
            static T s_singleton;
            return s_singleton;
        }

    private:
        SGISingleton(const SGISingleton&) = delete;
        const SGISingleton& operator= (const SGISingleton&) = delete;
    };
}