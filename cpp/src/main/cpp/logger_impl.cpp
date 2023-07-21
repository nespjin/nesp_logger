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
#include "../include/logger_impl.h"

#include <ctime>
#include <iostream>

#include "../include/nesp_logger_manager.h"

using namespace nesp::logger;

#define TAG "LoggerImpl"

LoggerImpl::LoggerImpl(const string &name) { this->name_ = name; }

Logger::Config *LoggerImpl::config() {
  return LoggerManager::shared()->config();
}

void LoggerImpl::Log(Logger::Printer *printer, Logger::Level level, int pid,
                     const string &thread_name, const string &class_name,
                     const string &method_name, int line_number,
                     const string &message, exception *exception) {
  Config *config = this->config();
  Filter *filter = nullptr;

  if (config != nullptr) {
    filter = config->filter();

    if (!config->enable()) {
      return;
    }

    if (level < config->level()) {
      return;
    }
  }

  LogRecord record;
  record.time = time(nullptr);
  record.pid = pid;
  record.thread_name = thread_name;
  record.log_name = name_;
  record.class_name = class_name;
  record.method_name = method_name;
  record.line_number = line_number;
  record.level = level;
  record.message = message;
  if (exception != nullptr) {
    record.exp = *exception;
  }
  record.message_formatted = "";

  if (config != nullptr) {
    record.message_formatted = config->format()->Format(record);
  }

  if (filter != nullptr && !filter->IsLogEnable(record)) {
    return;
  }

  if (printer != nullptr) {
    printer->Print(record);
  }

  if (config != nullptr) {
    set<std::shared_ptr<Logger::Printer>> printers = config->printers();
    if (printers.empty()) {
      cout << TAG << " log: Logger printers is empty";
      return;
    }

    for (const auto &item : printers) {
      item->Print(record);
    }
  }
}

LoggerImpl::~LoggerImpl() = default;
