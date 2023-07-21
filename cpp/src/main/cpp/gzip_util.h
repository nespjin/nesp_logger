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
// Time: Create 2023/2/12 下午12:02
// Description:
//

#ifndef NESP_LOGGER_GZIP_UTIL_H
#define NESP_LOGGER_GZIP_UTIL_H

#include <zlib.h>

#include "../include/nesp_logger.h"

namespace nesp {
namespace logger {
class GzipUtil {
 private:
  GzipUtil() = default;

 public:
  static long Compress(const char *src, uint src_len, char *dest,
                       uint dest_len);

  static long Uncompress(const char *src, uint src_len, char *dest,
                         uint dest_len);

  ~GzipUtil() = default;
};
}  // namespace logger
}  // namespace nesp

#endif  // NESP_LOGGER_GZIP_UTIL_H
