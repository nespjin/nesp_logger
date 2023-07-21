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

#ifndef NESP_LOGGER_DEFAULT_LOG_CONFIG_H
#define NESP_LOGGER_DEFAULT_LOG_CONFIG_H

#include <memory>

#include "../include/nesp_logger.h"

namespace nesp {
namespace logger {
class DefaultLogConfig : public Logger::Config {
 private:
  set<std::shared_ptr<Logger::Printer> > printers_;
  bool is_enable_;

  Logger::Formatter *format_;
  Logger::Filter *filter_;

 public:
  DefaultLogConfig();

  Logger::Formatter *format() override;

  Logger::Level level() override;

  Logger::Filter *filter() override;

  void set_filter(Logger::Filter *filter) override;

  bool enable() override;

  void set_enable(bool enable) override;

  void AddPrinter(std::shared_ptr<Logger::Printer> printer) override;

  void RemovePrinter(std::shared_ptr<Logger::Printer> printer) override;

  set<std::shared_ptr<Logger::Printer>> printers() override;

  ~DefaultLogConfig() override;
};
}  // namespace logger
}  // namespace nesp

#endif  // NESP_LOGGER_DEFAULT_LOG_CONFIG_H
