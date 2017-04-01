//
// Created by lamoliu on 2017/4/1.
//

#include <memory>
#include "HookerFactory.h"
#include "HookerX64.h"

std::unique_ptr<hooker::HookerFactory> hooker::HookerFactory::getInstance() {
    static std::unique_ptr<hooker::HookerFactory> sInstance;
    static std::mutex sMutex;
    std::lock_guard<std::mutex> lock(sMutex);
    if (sInstance == nullptr)
        sInstance.reset(new hooker::HookerFactory);

    return std::move(sInstance);
}

hooker::Hooker* hooker::HookerFactory::getHooker() {
#ifdef __x86_64__
    return new hooker::HookerX64;
#elif defined(__i386__)
    return new HookerX86;
#elif defined(__arm__)
    return new HookerArm;
#elif defined(__thumb__)
    return new HookerThumb;
#else
	throw std::string("unsupported hook architecture");
#endif

}

