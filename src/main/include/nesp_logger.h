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

#ifndef NESP_LOGGER_NESP_LOGGER_H
#define NESP_LOGGER_NESP_LOGGER_H

#include <string>
#include <set>

using namespace std;

namespace NespLogger {
    class Logger {

    public:
        enum Level {
            DEBUG, INFO, WARN, ERROR, FATAL
        };

        struct LogRecord {
            /** The time milliseconds when print the log message. */
            time_t time;

            /** The id of process which print the log message. */
            int pid;

            /** The thread name that prints the log message */
            string threadName;

            /** The log tag */
            string logName;

            /** The name of class that called log print if exits */
            string className;

            /** The name of method that called log print*/
            string methodName;

            /** The number of line that called log print*/
            int lineNumber;

            /** The level of message logged*/
            Level level;

            /** The message to logged*/
            string message;

            /** The format's message to logged*/
            string messageFormatted;

            /** The exception to logged*/
            exception exp;
        };

        class Printer {
        public:
            virtual void print(LogRecord logRecord) = 0;

            virtual ~Printer() = default;
        };

        class Format {
        public:
            virtual string format(LogRecord record) = 0;

            virtual ~Format() = default;
        };

        class Filter {
        public:
            virtual bool isLoggable(LogRecord record) = 0;

            virtual ~Filter() = default;
        };

        class Config {
        public:
            virtual Format *getFormat() = 0;

            virtual Level getLevel() = 0;

            virtual Filter *getFilter() = 0;

            virtual void setFilter(Filter *filter) = 0;

            virtual bool isEnable() = 0;

            virtual void setEnable(bool isEnable) = 0;

            virtual void addPrinter(Printer *printer) = 0;

            virtual void removePrinter(Printer *printer) = 0;

            virtual set<Printer *> getPrinters() = 0;

            virtual ~Config() = default;
        };

        virtual Config *getConfig() = 0;

        virtual void
        log(Logger::Printer *printer, Logger::Level level, int pid, const string &threadName,
            const string &className, const string &methodName, int lineNumber, const string &message,
            exception *exception) = 0;

        void log(Level level, int pid, const string &threadName, const string &className, const string &methodName,
                 int lineNumber,
                 const string &message, exception *exception) {
            log(nullptr, level, pid, threadName, className, methodName, lineNumber, message, exception);
        }

        void
        log(Printer *printer, Level level, int pid, const string &threadName, const string &className,
            const string &methodName, int lineNumber,
            const string &message) {
            log(printer, level, pid, threadName, className, methodName, lineNumber, message, nullptr);
        }

        void
        log(Level level, int pid, const string &threadName, const string &className, const string &methodName,
            int lineNumber,
            const string &message) {
            log(level, pid, threadName, className, methodName, lineNumber, message, nullptr);
        }

        void debug(int pid, const string &threadName, const string &className, const string &methodName, int lineNumber,
                   const string &message) {
            log(Level::DEBUG, pid, threadName, className, methodName, lineNumber, message);
        }

        void
        debug(Printer *printer, int pid, const string &threadName, const string &className, const string &methodName,
              int lineNumber,
              const string &message) {
            log(printer, Level::DEBUG, pid, threadName, className, methodName, lineNumber, message);
        }

        void debug(int pid, const string &threadName, const string &className, const string &methodName, int lineNumber,
                   const string &message,
                   exception *exception) {
            log(Level::DEBUG, pid, threadName, className, methodName, lineNumber, message, exception);
        }

        void
        debug(Printer *printer, int pid, const string &threadName, const string &className, const string &methodName,
              int lineNumber,
              const string &message,
              exception *exception) {
            log(printer, Level::DEBUG, pid, threadName, className, methodName, lineNumber, message, exception);
        }

        void info(int pid, const string &threadName, const string &className, const string &methodName, int lineNumber,
                  const string &message) {
            log(Level::INFO, pid, threadName, className, methodName, lineNumber, message);
        }

        void
        info(Printer *printer, int pid, const string &threadName, const string &className, const string &methodName,
             int lineNumber,
             const string &message) {
            log(printer, Level::INFO, pid, threadName, className, methodName, lineNumber, message);
        }

        void info(int pid, const string &threadName, const string &className, const string &methodName, int lineNumber,
                  const string &message,
                  exception *exception) {
            log(Level::INFO, pid, threadName, className, methodName, lineNumber, message, exception);
        }

        void
        info(Printer *printer, int pid, const string &threadName, const string &className, const string &methodName,
             int lineNumber,
             const string &message,
             exception *exception) {
            log(printer, Level::INFO, pid, threadName, className, methodName, lineNumber, message, exception);
        }

        void warn(int pid, const string &threadName, const string &className, const string &methodName, int lineNumber,
                  const string &message) {
            log(Level::WARN, pid, threadName, className, methodName, lineNumber, message);
        }

        void
        warn(Printer *printer, int pid, const string &threadName, const string &className, const string &methodName,
             int lineNumber,
             const string &message) {
            log(printer, Level::WARN, pid, threadName, className, methodName, lineNumber, message);
        }

        void warn(int pid, const string &threadName, const string &className, const string &methodName, int lineNumber,
                  const string &message,
                  exception *exception) {
            log(Level::WARN, pid, threadName, className, methodName, lineNumber, message, exception);
        }

        void
        warn(Printer *printer, int pid, const string &threadName, const string &className, const string &methodName,
             int lineNumber,
             const string &message,
             exception *exception) {
            log(printer, Level::WARN, pid, threadName, className, methodName, lineNumber, message, exception);
        }

        void error(int pid, const string &threadName, const string &className, const string &methodName, int lineNumber,
                   const string &message) {
            log(Level::ERROR, pid, threadName, className, methodName, lineNumber, message);
        }

        void
        error(Printer *printer, int pid, const string &threadName, const string &className, const string &methodName,
              int lineNumber,
              const string &message) {
            log(printer, Level::ERROR, pid, threadName, className, methodName, lineNumber, message);
        }

        void error(int pid, const string &threadName, const string &className, const string &methodName, int lineNumber,
                   const string &message,
                   exception *exception) {
            log(Level::ERROR, pid, threadName, className, methodName, lineNumber, message, exception);
        }

        void
        error(Printer *printer, int pid, const string &threadName, const string &className, const string &methodName,
              int lineNumber,
              const string &message,
              exception *exception) {
            log(printer, Level::ERROR, pid, threadName, className, methodName, lineNumber, message, exception);
        }

        void fatal(int pid, const string &threadName, const string &className, const string &methodName, int lineNumber,
                   const string &message) {
            log(Level::FATAL, pid, threadName, className, methodName, lineNumber, message);
        }

        void
        fatal(Printer *printer, int pid, const string &threadName, const string &className, const string &methodName,
              int lineNumber,
              const string &message) {
            log(printer, Level::FATAL, pid, threadName, className, methodName, lineNumber, message);
        }

        void fatal(int pid, const string &threadName, const string &className, const string &methodName, int lineNumber,
                   const string &message,
                   exception *exception) {
            log(Level::FATAL, pid, threadName, className, methodName, lineNumber, message, exception);
        }

        void
        fatal(Printer *printer, int pid, const string &threadName, const string &className, const string &methodName,
              int lineNumber,
              const string &message,
              exception *exception) {
            log(printer, Level::FATAL, pid, threadName, className, methodName, lineNumber, message, exception);
        }

        virtual  ~Logger() = default;
    };


    class LoggerUtil {
    private:
        LoggerUtil() = default;

    public:

        static string getLevelName(Logger::Level level) {
            switch (level) {
                case Logger::Level::DEBUG:
                    return "DEBUG";
                case Logger::Level::INFO:
                    return "INFO";
                case Logger::Level::WARN:
                    return "WARN";
                case Logger::Level::ERROR:
                    return "ERROR";
                case Logger::Level::FATAL:
                    return "FATAL";
            }
            return "UNKNOWN";
        }
    };
}

#endif //NESP_LOGGER_NESP_LOGGER_H
