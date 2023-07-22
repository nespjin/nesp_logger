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
// Time: Create 2023/2/12 下午12:22
// Description:
//

#include <cstring>
#include <iostream>

#include "../../main/cpp/gzip_util.h"
#include "../../main/cpp/system.h"

int main() {
  const auto os = nesp::logger::System::os_name();
  cout << os << endl;
  const auto architecture = nesp::logger::System::architecture_name();
  cout << architecture << endl;

  string src = "dsadasdasdsa";
  unsigned long size_src = strlen(src.c_str());
  char *compressed = static_cast<char *>(malloc(size_src * 2));
  memset(compressed, 0, size_src * 2);

  const string dest;

  const long size = nesp::logger::GzipUtil::Compress(src.c_str(), size_src,
                                                     compressed, size_src * 2);
  if (size <= 0) {
    cout << "compress error";
    return -1;
  }

  printf("compressed: ");
  int i = 0;
  for (; i < size; ++i) {
    printf("%02x ", compressed[i]);
  }

  return 0;
}