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

#include "default_log_config.h"

#include "default_message_format.h"

using namespace nesp::logger;

DefaultLogConfig::DefaultLogConfig() {
  format_ = new DefaultMessageFormat();
  filter_ = nullptr;
  is_enable_ = true;
}

Logger::Formatter *DefaultLogConfig::format() { return format_; }

Logger::Level DefaultLogConfig::level() { return Logger::kDebug; }

void DefaultLogConfig::set_filter(Logger::Filter *filter) {
  this->filter_ = filter;
}

Logger::Filter *DefaultLogConfig::filter() { return filter_; }

bool DefaultLogConfig::enable() { return is_enable_; }

void DefaultLogConfig::set_enable(bool isEnable) {
  this->is_enable_ = isEnable;
}

void DefaultLogConfig::AddPrinter(std::shared_ptr<Logger::Printer> printer) {
  printers_.insert(printer);
}

void DefaultLogConfig::RemovePrinter(std::shared_ptr<Logger::Printer> printer) {
  printers_.erase(printer);
}

set<std::shared_ptr<Logger::Printer>> DefaultLogConfig::printers() {
  return printers_;
}

DefaultLogConfig::~DefaultLogConfig() {
  printers_.clear();

  delete format_;
  delete filter_;
  format_ = nullptr;
  filter_ = nullptr;
}
