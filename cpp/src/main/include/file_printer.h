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
// Time: Create 2023/2/11 下午10:41
// Description:
//

#ifndef NESP_LOGGER_FILE_PRINTER_H
#define NESP_LOGGER_FILE_PRINTER_H

#include "nesp_logger.h"

namespace nesp::logger {
class FilePrinter final : public Logger::Printer {
 public:
  class CompressNameFormat {
    /**
     * Returns the name for compressed file.
     *
     * @param file_name the name of origin file.
     * @param num the number of current log file.
     **/
    virtual string Format(string file_name, int num) = 0;

   public:
    virtual ~CompressNameFormat() = default;
  };

 private:
  string dir_path_;

  /** The name of the log file to write, default log */
  string file_name_;

  CompressNameFormat *compress_name_format_;

  /** The max size for per log file, default 100M */
  unsigned long max_per_file_size_;

  /** The max log file count, default 5 */
  unsigned int max_file_count_;

  bool is_async_;

 public:
  explicit FilePrinter(const string &dir_path);

  void set_file_name(const string &name);

  string file_name();

  void set_max_per_file_size(uint64_t size);

  uint64_t max_per_file_size() const;

  void set_max_file_count(uint32_t count);

  uint32_t max_file_count() const;

  void set_async(bool async);

  bool async() const;

  void Print(Logger::LogRecord log_record) override;

  ~FilePrinter() override;
};
}  // namespace nesp::logger

#endif  // NESP_LOGGER_FILE_PRINTER_H
