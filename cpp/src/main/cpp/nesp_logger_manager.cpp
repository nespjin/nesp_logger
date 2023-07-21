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
#include "../include/nesp_logger_manager.h"

#include <map>

#include "../include/nesp_logger.h"
#include "default_log_config.h"

using namespace nesp::logger;

class ReleaseFilter : public Logger::Filter {
  bool IsLogEnable(Logger::LogRecord record) override {
    return record.level != Logger::Level::kDebug;
  }

  ~ReleaseFilter() override = default;
};

LoggerManager *LoggerManager::instance_ = nullptr;

LoggerManager *LoggerManager::shared() {
  if (instance_ == nullptr) {
    instance_ = new LoggerManager();
  }
  return instance_;
}

LoggerManager::LoggerManager() {
  console_printer_ = std::make_shared<ConsolePrinter>();
  config_ = new DefaultLogConfig();
}

Logger::Config *nesp::logger::LoggerManager::config() { return config_; }

void LoggerManager::Initialize(bool debug, const string &directory_path,
                               const string &file_name) {
  config_->AddPrinter(console_printer_);
  if (!debug) {
    config_->set_filter(new ReleaseFilter());
  }
}

Logger *LoggerManager::logger(const string &name) {
  const ulong count = logger_cache_.count(name);
  if (count > 0 && logger_cache_[name] != nullptr &&
      logger_cache_[name].get() != nullptr) {
    return logger_cache_[name].get();
  }
  logger_cache_[name] = std::make_shared<LoggerImpl>(name);
  return logger_cache_[name].get();
}

LoggerManager::~LoggerManager() {
  delete config_;
  logger_cache_.clear();
  instance_ = nullptr;
}
