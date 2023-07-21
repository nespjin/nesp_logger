
// Copyright (c) 2023-2023. NESP Technology.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License. You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
// Unless required by applicable law or agreed to in writing, software distributed under the License is distributed
// on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License
// for the specific language governing permissions and limitations under the License.

#include <csignal>
#include "../../main/include/nesp_logger.h"
#include "../../main/include/nesp_logger_manager.h"

using namespace nesp::logger;

int main() {
    long int i = 99999999999999999;

    while (i-- > 0) {
        LoggerManager *loggerManager = LoggerManager::shared();
        Logger *logger = loggerManager->logger("Test");
        loggerManager->Initialize(false, "", "");
        logger->Info(1, "main-thread", "Test", "main", 12, "this is info message");
        logger->Debug(1, "main-thread", "Test", "main", 13, "this is Debug message");
        logger->Warn(1, "main-thread", "Test", "main", 14, "this is warn message");
        logger->Error(1, "main-thread", "Test", "main", 15, "this is error message");
        logger->Fatal(1, "main-thread", "Test", "main", 16, "this is fatal message");

        delete loggerManager;
        sleep(1);
    }

    return 0;
}
