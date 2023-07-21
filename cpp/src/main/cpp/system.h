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

#ifndef NESP_LOGGER_SYSTEM_H
#define NESP_LOGGER_SYSTEM_H

#include <string>

namespace nesp {
namespace logger {
class System {
 public:
  enum class OS {
    kWindows64,
    kWindows32,
    kLinux64,
    kLinux32,
    kUnix64,
    kUnix32,
    kPosix64,
    kPosix32,
    kAndroid64,
    kAndroid32,
    kIOS32,
    kIOS64,
    kIOS32Simulator,
    kIOS64Simulator,
    kMacOS32,
    kMacOS64,
    kUnknown,
  };

  enum class Architecture {
    kX86,
    kX64,
    kARM32,
    kARM64,
    kUnknown,
  };

  System();

 private:
  static OS os_;
  static Architecture architecture_;

 public:
  static OS os();

  static std::string os_name();

  static Architecture architecture();

  static std::string architecture_name();

  ~System() = default;
};
}  // namespace logger
}  // namespace nesp

#endif  // NESP_LOGGER_SYSTEM_H
