
// Copyright (c) 2023-2023. NESP Technology.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License. You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
// Unless required by applicable law or agreed to in writing, software distributed under the License is distributed
// on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License
// for the specific language governing permissions and limitations under the License.

#include "../../main/include/nesp_logger.h"
#include "../../main/include/nesp_logger_manager.h"

using namespace NespLogger;

int main() {
    LoggerManager *loggerManager = LoggerManager::shared();

    loggerManager->initialize(false, "", "");
    Logger *logger = loggerManager->getLogger("Test");
    logger->info(1, "main-thread", "Test", "main", 12, "this is info message");
    logger->debug(1, "main-thread", "Test", "main", 13, "this is debug message");
    logger->warn(1, "main-thread", "Test", "main", 14, "this is warn message");
    logger->error(1, "main-thread", "Test", "main", 15, "this is error message");
    logger->fatal(1, "main-thread", "Test", "main", 16, "this is fatal message");

    delete loggerManager;
    return 0;
}
