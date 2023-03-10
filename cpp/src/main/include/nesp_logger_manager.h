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
// Created by jinzhaolu on 23-1-31.
//

#ifndef NESP_LOGGER_NESP_LOGGER_MANAGER_H
#define NESP_LOGGER_NESP_LOGGER_MANAGER_H

#include <string>
#include <map>
#include "nesp_logger.h"
#include "logger_impl.h"
#include "console_printer.h"

using namespace std;

namespace NespLogger {
    class LoggerManager {
    private:
        LoggerManager();

        map<string, Logger *> loggerCache;
        static LoggerManager *instance;

        ConsolePrinter *consolePrinter;
        Logger::Config *config;
    public:
        static LoggerManager *shared();

        Logger::Config *getConfig();

        void initialize(bool isDebug, const string &directoryPath, const string &fileName);

        Logger *getLogger(const string &name);

        ~LoggerManager();
    };
}

#endif //NESP_LOGGER_NESP_LOGGER_MANAGER_H
