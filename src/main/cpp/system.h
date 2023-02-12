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

#ifndef NESP_LOGGER_SYSTEM_H
#define NESP_LOGGER_SYSTEM_H


namespace NespLogger {
    class System {
    public:
        enum class OS {
            WINDOWS_64,
            WINDOWS_32,
            LINUX_64,
            LINUX_32,
            UNIX_64,
            UNIX_32,
            POSIX_64,
            POSIX_32,
            ANDROID_64,
            ANDROID_32,
            iOS_32,
            iOS_64,
            iOS_32_SIMULATOR,
            iOS_64_SIMULATOR,
            MAC_OS_32,
            MAC_OS_64,
            UNKNOWN,
        };

        enum class Architecture {
            X86,
            X64,
            ARM_32,
            ARM_64,
            UNKNOWN,
        };

        System();

    private:
        static OS os;
        static Architecture architecture;

    public:
        static OS getOS();

        static std::string getOSName();

        static Architecture getArchitecture();

        static std::string getArchitectureName();

        ~System() = default;
    };
}


#endif //NESP_LOGGER_SYSTEM_H
