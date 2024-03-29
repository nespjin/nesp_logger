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
// Created by jinzhaolu on 2023/2/11.
//

#ifndef NESP_LOGGER_CONSOLE_PRINTER_H
#define NESP_LOGGER_CONSOLE_PRINTER_H

#include "nesp_logger.h"

namespace nesp::logger {
class ConsolePrinter : public Logger::Printer {
 public:
  void Print(Logger::LogRecord log_record) override;

  ~ConsolePrinter() override;
};
}  // namespace nesp::logger

#endif  // NESP_LOGGER_CONSOLE_PRINTER_H
