// Copyright (c) 2023. NESP Technology.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License. You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
// Unless required by applicable law or agreed to in writing, software distributed under the License is distributed
// on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License
// for the specific language governing permissions and limitations under the License.

//
// Team: NESP Technology
// Author: JinZhaolu Email:1756404649@qq.com
// Version: 1.0
// Time: Create 2023/2/12 下午1:02
// Description:
//

#include <string>

#include "system.h"

using namespace NespLogger;

//System::OS System::os = OS::UNKNOWN;
//System::Architecture System::architecture = Architecture::UNKNOWN;

#ifdef _WIN32

#ifdef _WIN64
System::OS System::os = OS::WINDOWS_64;
#else
System::OS System::os = OS::WINDOWS_32;
#endif

#elif __linux__

#ifdef __LP64__
System::OS System::os = OS::LINUX_64;
#else
System::OS System::os = OS::LINUX_32;
#endif

#elif __unix__

#ifdef __LP64__
System::OS System::os = OS::UNIX_64;
#else
System::OS  System::os = OS::UNIX_32;
#endif

#elif defined(_POSIX_VERSION)

#ifdef __LP64__
System::OS System::os = OS::POSIX_64;
#else
System::OS System::os = OS::POSIX_32;
#endif

#elif __ANDROID__

#ifdef __LP64__
System::OS System::os = OS::ANDROID_64;
#else
System::OS System::os = OS::ANDROID_32;
#endif

#elif __APPLE__

#include "TargetConditionals.h"
#if TARGET_IPHONE_SIMULATOR
#ifdef __LP64__
System::OS  System::os = OS::iOS_64_SIMULATOR;
#else
System::OS System::os = OS::iOS_32_SIMULATOR;
#endif
#elif TARGET_OS_IPHONE
#ifdef __LP64__
System::OS System::os = OS::iOS_64;
#else
System::OS  System::os = OS::iOS_32;
#endif
#elif TARGET_OS_MAC
#ifdef __LP64__
System::OS System::os = OS::MAC_OS_64;
#else
System::OS  System::os = OS::MAC_OS_32;
#endif
#else
#error "Unknown Apple platform"
#endif

#endif

#ifdef __i386__
System::Architecture System::architecture  = Architecture::X86;
#elif __amd64__
System::Architecture System::architecture = Architecture::X64;
#elif __x86_64__
System::Architecture System::architecture  = Architecture::X64;
#elif __arm__
    System::Architecture System::architecture  = Architecture::ARM_32;
#elif __aarch64__
    System::Architecture System::architecture  = Architecture::ARM_64;
#else
#error "Unknown architecture"
#endif

System::OS System::getOS() {
    return System::os;
}

std::string System::getOSName() {
    switch (os) {
        case OS::WINDOWS_64:
            return "WINDOWS_64";
        case OS::WINDOWS_32:
            return "WINDOWS_32";
        case OS::LINUX_64:
            return "LINUX_64";
        case OS::LINUX_32:
            return "LINUX_32";
        case OS::UNIX_64:
            return "UNIX_64";
        case OS::UNIX_32:
            return "UNIX_32";
        case OS::POSIX_64:
            return "POSIX_64";
        case OS::POSIX_32:
            return "POSIX_32";
        case OS::ANDROID_64:
            return "ANDROID_64";
        case OS::ANDROID_32:
            return "ANDROID_32";
        case OS::iOS_32:
            return "iOS_32";
        case OS::iOS_64:
            return "iOS_64";
        case OS::iOS_32_SIMULATOR:
            return "iOS_32_SIMULATOR";
        case OS::iOS_64_SIMULATOR:
            return "iOS_64_SIMULATOR";
        case OS::MAC_OS_32:
            return "MAC_OS_32";
        case OS::MAC_OS_64:
            return "MAC_OS_64";
        case OS::UNKNOWN:
            return "UNKNOWN";
    }
}

System::Architecture System::getArchitecture() {
    return System::architecture;
}

std::string System::getArchitectureName() {
    switch (architecture) {
        case Architecture::X86:
            return "X86";
        case Architecture::X64:
            return "X64";
        case Architecture::ARM_32:
            return "ARM_32";
        case Architecture::ARM_64:
            return "ARM_64";
        case Architecture::UNKNOWN:
            return "UNKNOWN";
    }
}


