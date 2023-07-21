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
// Created by jinzhaolu on 23-1-31.
//

#ifndef NESP_LOGGER_NESP_LOGGER_H
#define NESP_LOGGER_NESP_LOGGER_H

#include <memory>
#include <set>
#include <string>

using namespace std;

namespace nesp {
namespace logger {
class Logger {
 public:
  enum Level { kDebug, kInfo, kWarn, kError, kFatal };

  struct LogRecord {
    /** The time milliseconds when print the log message. */
    time_t time;

    /** The id of process which print the log message. */
    int pid;

    /** The thread name that prints the log message */
    string thread_name;

    /** The log tag */
    string log_name;

    /** The name of class that called log print if exits */
    string class_name;

    /** The name of method that called log print*/
    string method_name;

    /** The number of line that called log print*/
    int line_number;

    /** The level of message logged*/
    Level level;

    /** The message to logged*/
    string message;

    /** The format's message to logged*/
    string message_formatted;

    /** The exception to logged*/
    exception exp;
  };

  class Printer {
   public:
    virtual void Print(LogRecord log_record) = 0;

    virtual ~Printer() = default;
  };

  class Formatter {
   public:
    virtual string Format(LogRecord record) = 0;

    virtual ~Formatter() = default;
  };

  class Filter {
   public:
    virtual bool IsLogEnable(LogRecord record) = 0;

    virtual ~Filter() = default;
  };

  class Config {
   public:
    virtual Formatter *format() = 0;

    virtual Level level() = 0;

    virtual Filter *filter() = 0;

    virtual void set_filter(Filter *filter) = 0;

    virtual bool enable() = 0;

    virtual void set_enable(bool enable) = 0;

    virtual void AddPrinter(std::shared_ptr<Printer> printer) = 0;

    virtual void RemovePrinter(std::shared_ptr<Printer> printer) = 0;

    virtual set<std::shared_ptr<Printer>> printers() = 0;

    virtual ~Config() = default;
  };

  virtual Config *config() = 0;

  virtual void Log(Logger::Printer *printer, Logger::Level level, int pid,
                   const string &thread_name, const string &class_name,
                   const string &method_name, int line_number,
                   const string &message, exception *exception) = 0;

  void Log(Level level, int pid, const string &thread_name,
           const string &class_name, const string &method_name, int line_number,
           const string &message, exception *exception) {
    Log(nullptr, level, pid, thread_name, class_name, method_name, line_number,
        message, exception);
  }

  void Log(Printer *printer, Level level, int pid, const string &thread_name,
           const string &class_name, const string &method_name, int line_number,
           const string &message) {
    Log(printer, level, pid, thread_name, class_name, method_name, line_number,
        message, nullptr);
  }

  void Log(Level level, int pid, const string &thread_name,
           const string &class_name, const string &method_name, int line_number,
           const string &message) {
    Log(level, pid, thread_name, class_name, method_name, line_number, message,
        nullptr);
  }

  void Debug(int pid, const string &thread_name, const string &class_name,
             const string &method_name, int line_number,
             const string &message) {
    Log(Level::kDebug, pid, thread_name, class_name, method_name, line_number,
        message);
  }

  void Debug(Printer *printer, int pid, const string &thread_name,
             const string &class_name, const string &method_name,
             int line_number, const string &message) {
    Log(printer, Level::kDebug, pid, thread_name, class_name, method_name,
        line_number, message);
  }

  void Debug(int pid, const string &thread_name, const string &class_name,
             const string &method_name, int line_number, const string &message,
             exception *exception) {
    Log(Level::kDebug, pid, thread_name, class_name, method_name, line_number,
        message, exception);
  }

  void Debug(Printer *printer, int pid, const string &thread_name,
             const string &class_name, const string &method_name,
             int line_number, const string &message, exception *exception) {
    Log(printer, Level::kDebug, pid, thread_name, class_name, method_name,
        line_number, message, exception);
  }

  void Info(int pid, const string &thread_name, const string &class_name,
            const string &method_name, int line_number, const string &message) {
    Log(Level::kInfo, pid, thread_name, class_name, method_name, line_number,
        message);
  }

  void Info(Printer *printer, int pid, const string &thread_name,
            const string &class_name, const string &method_name,
            int line_number, const string &message) {
    Log(printer, Level::kInfo, pid, thread_name, class_name, method_name,
        line_number, message);
  }

  void Info(int pid, const string &thread_name, const string &class_name,
            const string &method_name, int line_number, const string &message,
            exception *exception) {
    Log(Level::kInfo, pid, thread_name, class_name, method_name, line_number,
        message, exception);
  }

  void Info(Printer *printer, int pid, const string &thread_name,
            const string &class_name, const string &method_name,
            int line_number, const string &message, exception *exception) {
    Log(printer, Level::kInfo, pid, thread_name, class_name, method_name,
        line_number, message, exception);
  }

  void Warn(int pid, const string &thread_name, const string &class_name,
            const string &method_name, int line_number, const string &message) {
    Log(Level::kWarn, pid, thread_name, class_name, method_name, line_number,
        message);
  }

  void Warn(Printer *printer, int pid, const string &thread_name,
            const string &class_name, const string &method_name,
            int line_number, const string &message) {
    Log(printer, Level::kWarn, pid, thread_name, class_name, method_name,
        line_number, message);
  }

  void Warn(int pid, const string &thread_name, const string &class_name,
            const string &method_name, int line_number, const string &message,
            exception *exception) {
    Log(Level::kWarn, pid, thread_name, class_name, method_name, line_number,
        message, exception);
  }

  void Warn(Printer *printer, int pid, const string &thread_name,
            const string &class_name, const string &method_name,
            int line_number, const string &message, exception *exception) {
    Log(printer, Level::kWarn, pid, thread_name, class_name, method_name,
        line_number, message, exception);
  }

  void Error(int pid, const string &thread_name, const string &class_name,
             const string &method_name, int line_number,
             const string &message) {
    Log(Level::kError, pid, thread_name, class_name, method_name, line_number,
        message);
  }

  void Error(Printer *printer, int pid, const string &thread_name,
             const string &class_name, const string &method_name,
             int line_number, const string &message) {
    Log(printer, Level::kError, pid, thread_name, class_name, method_name,
        line_number, message);
  }

  void Error(int pid, const string &thread_name, const string &class_name,
             const string &method_name, int line_number, const string &message,
             exception *exception) {
    Log(Level::kError, pid, thread_name, class_name, method_name, line_number,
        message, exception);
  }

  void Error(Printer *printer, int pid, const string &thread_name,
             const string &class_name, const string &method_name,
             int line_number, const string &message, exception *exception) {
    Log(printer, Level::kError, pid, thread_name, class_name, method_name,
        line_number, message, exception);
  }

  void Fatal(int pid, const string &thread_name, const string &class_name,
             const string &method_name, int line_number,
             const string &message) {
    Log(Level::kFatal, pid, thread_name, class_name, method_name, line_number,
        message);
  }

  void Fatal(Printer *printer, int pid, const string &thread_name,
             const string &class_name, const string &method_name,
             int line_number, const string &message) {
    Log(printer, Level::kFatal, pid, thread_name, class_name, method_name,
        line_number, message);
  }

  void Fatal(int pid, const string &thread_name, const string &class_name,
             const string &method_name, int line_number, const string &message,
             exception *exception) {
    Log(Level::kFatal, pid, thread_name, class_name, method_name, line_number,
        message, exception);
  }

  void Fatal(Printer *printer, int pid, const string &thread_name,
             const string &class_name, const string &method_name,
             int line_number, const string &message, exception *exception) {
    Log(printer, Level::kFatal, pid, thread_name, class_name, method_name,
        line_number, message, exception);
  }

  virtual ~Logger() = default;
};

class LoggerUtil {
 private:
  LoggerUtil() = default;

 public:
  static string level_name(Logger::Level level) {
    switch (level) {
      case Logger::Level::kDebug:
        return "DEBUG";
      case Logger::Level::kInfo:
        return "INFO";
      case Logger::Level::kWarn:
        return "WARN";
      case Logger::Level::kError:
        return "ERROR";
      case Logger::Level::kFatal:
        return "FATAL";
    }
    return "UNKNOWN";
  }
};
}  // namespace logger
}  // namespace nesp

#endif  // NESP_LOGGER_NESP_LOGGER_H
