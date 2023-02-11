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
#include <ctime>
#include <iostream>

#include "../include/logger_impl.h"
#include "../include/nesp_logger_manager.h"

using namespace NespLogger;

#define TAG "LoggerImpl"

LoggerImpl::LoggerImpl(const string &name) {
    this->name = name;
}

Logger::Config *LoggerImpl::getConfig() {
    return LoggerManager::shared()->getConfig();
}

void LoggerImpl::log(Logger::Printer *printer, Logger::Level level, int pid, const string &threadName,
                     const string &className, const string &methodName, int lineNumber, const string &message,
                     exception *exception) {
    Config *config = getConfig();
    Filter *filter = nullptr;

    if (config != nullptr) {
        filter = config->getFilter();

        if (!config->isEnable()) {
            return;
        }

        if (level < config->getLevel()) {
            return;
        }
    }

    LogRecord record;
    record.time = time(nullptr);
    record.pid = pid;
    record.threadName = threadName;
    record.logName = name;
    record.className = className;
    record.methodName = methodName;
    record.lineNumber = lineNumber;
    record.level = level;
    record.message = message;
    if (exception != nullptr) {
        record.exp = *exception;
    }
    record.messageFormatted = "";

    if (config != nullptr) {
        record.messageFormatted = config->getFormat()->format(record);
    }

    if (filter != nullptr && !filter->isLoggable(record)) {
        return;
    }

    if (printer != nullptr) {
        printer->print(record);
    }

    if (config != nullptr) {
        set<Logger::Printer *> printers = config->getPrinters();
        if (printers.empty()) {
            cout << TAG << " log: Logger printers is empty";
            return;
        }

        for (const auto &item: printers) {
            item->print(record);
        }
    }
}

LoggerImpl::~LoggerImpl() = default;
