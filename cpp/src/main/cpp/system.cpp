// Copyright (c) 2023. NESP Technology.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License. You may
// obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
// WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
// License for the specific language governing permissions and limitations under
// the License.

//
// Team: NESP Technology
// Author: JinZhaolu Email:1756404649@qq.com
// Version: 1.0
// Time: Create 2023/2/12 下午1:02
// Description:
//

#include "system.h"

#include <string>

using namespace nesp::logger;

// System::OS System::os = OS::UNKNOWN;
// System::Architecture System::architecture = Architecture::UNKNOWN;

#ifdef _WIN32

#ifdef _WIN64
System::OS System::os_ = System::OS::kWindows64;
#else
System::OS System::os = OS::WINDOWS_32;
#endif

#elif __linux__

#ifdef __LP64__
System::OS System::os_ = OS::kLinux64;
#else
System::OS System::os = OS::LINUX_32;
#endif

#elif __unix__

#ifdef __LP64__
System::OS System::os = OS::UNIX_64;
#else
System::OS System::os = OS::UNIX_32;
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
System::OS System::os = OS::iOS_64_SIMULATOR;
#else
System::OS System::os = OS::iOS_32_SIMULATOR;
#endif
#elif TARGET_OS_IPHONE
#ifdef __LP64__
System::OS System::os = OS::iOS_64;
#else
System::OS System::os = OS::iOS_32;
#endif
#elif TARGET_OS_MAC
#ifdef __LP64__
System::OS System::os = OS::MAC_OS_64;
#else
System::OS System::os = OS::MAC_OS_32;
#endif
#else
#error "Unknown Apple platform"
#endif

#endif

#ifdef __i386__
System::Architecture System::architecture = Architecture::X86;
#elif __amd64__
System::Architecture System::architecture_ = Architecture::kX64;
#elif __x86_64__
System::Architecture System::architecture = Architecture::X64;
#elif __arm__
System::Architecture System::architecture = Architecture::ARM_32;
#elif __aarch64__
System::Architecture System::architecture = Architecture::ARM_64;
#else
#error "Unknown architecture"
#endif

System::System() = default;

System::OS System::os() { return System::os_; }

std::string System::os_name() {
  switch (os_) {
    case OS::kWindows64:
      return "WINDOWS_64";
    case OS::kWindows32:
      return "WINDOWS_32";
    case OS::kLinux64:
      return "LINUX_64";
    case OS::kLinux32:
      return "LINUX_32";
    case OS::kUnix64:
      return "UNIX_64";
    case OS::kUnix32:
      return "UNIX_32";
    case OS::kPosix64:
      return "POSIX_64";
    case OS::kPosix32:
      return "POSIX_32";
    case OS::kAndroid64:
      return "ANDROID_64";
    case OS::kAndroid32:
      return "ANDROID_32";
    case OS::kIOS32:
      return "iOS_32";
    case OS::kIOS64:
      return "iOS_64";
    case OS::kIOS32Simulator:
      return "iOS_32_SIMULATOR";
    case OS::kIOS64Simulator:
      return "iOS_64_SIMULATOR";
    case OS::kMacOS32:
      return "MAC_OS_32";
    case OS::kMacOS64:
      return "MAC_OS_64";
    case OS::kUnknown:
    default:
      return "UNKNOWN";
  }
}

System::Architecture System::architecture() { return System::architecture_; }

std::string System::architecture_name() {
  switch (architecture_) {
    case Architecture::kX86:
      return "X86";
    case Architecture::kX64:
      return "X64";
    case Architecture::kARM32:
      return "ARM_32";
    case Architecture::kARM64:
      return "ARM_64";
    case Architecture::kUnknown:
    default:
      return "UNKNOWN";
  }
}