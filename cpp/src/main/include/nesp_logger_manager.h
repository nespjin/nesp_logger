// Copyright (c) 2023-2023. NESP Technology.
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
// Created by jinzhaolu on 23-1-31.
//

#ifndef NESP_LOGGER_NESP_LOGGER_MANAGER_H
#define NESP_LOGGER_NESP_LOGGER_MANAGER_H

#include <map>
#include <memory>
#include <string>

#include "console_printer.h"
#include "logger_impl.h"
#include "nesp_logger.h"

using namespace std;

namespace nesp {
namespace logger {
class LoggerManager {
 private:
  LoggerManager();

  map<string, std::shared_ptr<Logger>> logger_cache_;
  static LoggerManager *instance_;

  std::shared_ptr<ConsolePrinter> console_printer_;
  Logger::Config *config_;

 public:
  static LoggerManager *shared();

  Logger::Config *config();

  void Initialize(bool debug, const string &directory_path,
                  const string &file_name);

  Logger *logger(const string &name);

  ~LoggerManager();
};

}  // namespace logger
}  // namespace nesp

#endif  // NESP_LOGGER_NESP_LOGGER_MANAGER_H
