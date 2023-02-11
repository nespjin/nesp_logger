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

#ifndef NESP_LOGGER_LOGGER_IMPL_H
#define NESP_LOGGER_LOGGER_IMPL_H

#include "nesp_logger.h"

using namespace NespLogger;

class LoggerImpl : public Logger {
private:
    string name;
public:
    explicit LoggerImpl(const string &name);

    Config *getConfig() override;

    void log(Logger::Printer *printer, Logger::Level level, int pid, const string &threadName,
             const string &className, const string &methodName, int lineNumber, const string &message,
             exception *exception) override;

    ~LoggerImpl() override;
};


#endif //NESP_LOGGER_LOGGER_IMPL_H
