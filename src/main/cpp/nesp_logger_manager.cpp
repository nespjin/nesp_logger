// Copyright (c) 2023-2023. NESP Technology.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License. You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
// Unless required by applicable law or agreed to in writing, software distributed under the License is distributed
// on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License
// for the specific language governing permissions and limitations under the License.

//
// Created by jinzhaolu on 2023/2/11.
//
#include <map>
#include "../include/nesp_logger.h"
#include "../include/nesp_logger_manager.h"
#include "default_log_config.h"

using namespace NespLogger;

class ReleaseFilter : public Logger::Filter {
    bool isLoggable(Logger::LogRecord record) override {
        return record.level != Logger::Level::DEBUG;
    }

    ~ReleaseFilter() override = default;
};

LoggerManager *LoggerManager::instance = nullptr;

LoggerManager *LoggerManager::shared() {
    if (instance == nullptr) {
        instance = new LoggerManager();
    }
    return instance;
}

LoggerManager::LoggerManager() {
    consolePrinter = new ConsolePrinter();
    config = new DefaultLogConfig();
}

Logger::Config *NespLogger::LoggerManager::getConfig() {
    return config;
}

void LoggerManager::initialize(bool isDebug, const string &directoryPath, const string &fileName) {
    config->addPrinter(consolePrinter);
    if (!isDebug) {
        config->setFilter(new ReleaseFilter());
    }
}

Logger *LoggerManager::getLogger(const string &name) {
    const int count = loggerCache.count(name);
    if (count > 0 && loggerCache[name] != nullptr) {
        return loggerCache[name];
    }
    Logger *logger = new LoggerImpl(name);
    loggerCache[name] = logger;
    return logger;
}

LoggerManager::~LoggerManager() {
    delete consolePrinter;
    delete config;

    for (const auto &item: loggerCache) {
        delete item.second;
    }

    loggerCache.clear();
}
