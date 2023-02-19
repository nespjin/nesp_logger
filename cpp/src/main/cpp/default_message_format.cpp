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
#include "../include/nesp_logger.h"
#include "default_message_format.h"

string NespLogger::DefaultMessageFormat::format(Logger::LogRecord record) {
    char currentTimeChars[255];
    std::time_t currentTime = record.time;
    std::strftime(currentTimeChars, sizeof currentTimeChars, "%Y-%m-%d %H:%M:%S",
                  std::localtime(&currentTime));

    std::stringstream currentTimeString;
    currentTimeString << currentTimeChars;

    std::stringstream ret;
    ret << currentTimeString.str();
    ret << "\t";
    ret << LoggerUtil::getLevelName(record.level);
    ret << "\t";
    ret << record.pid;
    ret << "\t";
    ret << "[";
    ret << record.threadName;
    ret << "]";
    ret << "\t";
    ret << record.logName;
    ret << "\t";
    ret << record.className;
    if (!record.className.empty() && !record.methodName.empty()) {
        ret << ".";
    }
    ret << record.methodName;
    ret << " ";
    ret << record.lineNumber;
    ret << ":";
    ret << record.message;

    return ret.str();
}

NespLogger::DefaultMessageFormat::~DefaultMessageFormat() = default;
