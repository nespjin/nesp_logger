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

#ifndef NESP_LOGGER_DEFAULT_LOG_CONFIG_H
#define NESP_LOGGER_DEFAULT_LOG_CONFIG_H

#include "../include/nesp_logger.h"

namespace NespLogger {
    class DefaultLogConfig : public Logger::Config {
    private:
        set<Logger::Printer *> printers;
        bool _isEnable;

        Logger::Format *format;
        Logger::Filter *filter;

    public:
        DefaultLogConfig();

        Logger::Format *getFormat() override;

        Logger::Level getLevel() override;

        Logger::Filter *getFilter() override;

        void setFilter(Logger::Filter *filter) override;

        bool isEnable() override;

        void setEnable(bool isEnable) override;

        void addPrinter(Logger::Printer *printer) override;

        void removePrinter(Logger::Printer *printer) override;

        set<Logger::Printer *> getPrinters() override;

        ~DefaultLogConfig() override;
    };
}

#endif //NESP_LOGGER_DEFAULT_LOG_CONFIG_H
