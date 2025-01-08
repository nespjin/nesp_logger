use std::{
    cell::RefCell,
    rc::Rc,
};

/*
 * Copyright (c) 2023. NESP Technology.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License. You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 * Unless required by applicable law or agreed to in writing, software distributed under the License is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License
 * for the specific language governing permissions and limitations under the License.
 */
use chrono::Utc;

use crate::{
    filter::Filter, format::format::Format, level::Level, log_manager::LogManager,
    log_record::LogRecord, printer::printer::Printer,
};

pub struct LogOptions {
    pub printer: Option<Rc<RefCell<dyn Printer>>>,
    pub level: Level,
    pub pid: u32,
    pub thread_name: String,
    pub class_name: String,
    pub method_name: String,
    pub line_number: u32,
    pub message: String,
    pub exception: String,
}

impl LogOptions {
    pub fn default() -> LogOptions {
        return LogOptions {
            printer: None,
            level: Level::Info,
            pid: 0,
            thread_name: String::new(),
            class_name: String::new(),
            method_name: String::new(),
            line_number: 0,
            message: String::new(),
            exception: String::new(),
        };
    }
}

pub struct LevelLogOptions {
    pub printer: Option<Rc<RefCell<dyn Printer>>>,
    pub pid: u32,
    pub thread_name: String,
    pub class_name: String,
    pub method_name: String,
    pub line_number: u32,
    pub message: String,
    pub exception: String,
}

impl LevelLogOptions {
    pub fn default() -> LevelLogOptions {
        return LevelLogOptions {
            printer: None,
            pid: 0,
            thread_name: String::new(),
            class_name: String::new(),
            method_name: String::new(),
            line_number: 0,
            message: String::new(),
            exception: String::new(),
        };
    }
}

pub trait ILogger {
    fn log(
        &self,
        printer: Option<Rc<RefCell<dyn Printer>>>,
        level: Level,
        pid: u32,
        thread_name: String,
        class_name: String,
        method_name: String,
        line_number: u32,
        message: String,
        exception: String,
    );

    fn log_with_options(&self, options: &LogOptions);

    fn debug(
        &self,
        printer: Option<Rc<RefCell<dyn Printer>>>,
        pid: u32,
        thread_name: String,
        class_name: String,
        method_name: String,
        line_number: u32,
        message: String,
        exception: String,
    );

    fn debug_with_options(&self, options: &LevelLogOptions);

    fn info(
        &self,
        printer: Option<Rc<RefCell<dyn Printer>>>,
        pid: u32,
        thread_name: String,
        class_name: String,
        method_name: String,
        line_number: u32,
        message: String,
        exception: String,
    );

    fn info_with_options(&self, options: &LevelLogOptions);

    fn warn(
        &self,
        printer: Option<Rc<RefCell<dyn Printer>>>,
        pid: u32,
        thread_name: String,
        class_name: String,
        method_name: String,
        line_number: u32,
        message: String,
        exception: String,
    );

    fn warn_with_options(&self, options: &LevelLogOptions);

    fn error(
        &self,
        printer: Option<Rc<RefCell<dyn Printer>>>,
        pid: u32,
        thread_name: String,
        class_name: String,
        method_name: String,
        line_number: u32,
        message: String,
        exception: String,
    );

    fn error_with_options(&self, options: &LevelLogOptions);

    fn fatal(
        &self,
        printer: Option<Rc<RefCell<dyn Printer>>>,
        pid: u32,
        thread_name: String,
        class_name: String,
        method_name: String,
        line_number: u32,
        message: String,
        exception: String,
    );

    fn fatal_with_options(&self, options: &LevelLogOptions);
}

#[derive(Debug, Clone)]
pub struct Logger {
    name: String,
}

impl Logger {
    pub(crate) fn new(name: String) -> Logger {
        return Logger { name };
    }
}

impl ILogger for Logger {
    fn log(
        &self,
        printer: Option<Rc<RefCell<dyn Printer>>>,
        level: Level,
        pid: u32,
        thread_name: String,
        class_name: String,
        method_name: String,
        line_number: u32,
        message: String,
        exception: String,
    ) {
        let log_manager_mutex = LogManager::shared();
        let log_manager = log_manager_mutex.lock().unwrap();
        let config = log_manager.get_config();
        drop(log_manager);

        if !config.borrow().enabled {
            return;
        }

        if level.index() < config.borrow().level.index() {
            return;
        }

        let mut record = LogRecord {
            time: Utc::now().timestamp_millis(),
            pid,
            thread_name,
            log_name: self.name.clone(),
            class_name,
            method_name,
            line_number,
            level,
            message,
            message_formatted: String::new(),
            exp: exception,
        };

        let format = config.borrow().format;
        if format.is_some() {
            let formatted_message = format.unwrap().format(&record);
            record.message_formatted = formatted_message;
        }

        let filter = &config.borrow().filter;
        if filter.is_some() {
            if !filter.as_ref().unwrap().enabled(&record) {
                return;
            }
        }

        if printer.is_some() {
            printer.unwrap().borrow().print(&record);
            return;
        }

        let printers = config.borrow().get_printers();
        if printers.is_empty() {
            println!("nesp_logger: printers is empty");
            return;
        }

        for printer in printers {
            printer.borrow().print(&record);
        }
    }

    fn log_with_options(&self, options: &LogOptions) {
        self.log(
            options.printer.clone(),
            options.level.clone(),
            options.pid,
            options.thread_name.clone(),
            options.class_name.clone(),
            options.method_name.clone(),
            options.line_number,
            options.message.clone(),
            options.exception.clone(),
        );
    }

    fn debug(
        &self,
        printer: Option<Rc<RefCell<dyn Printer>>>,
        pid: u32,
        thread_name: String,
        class_name: String,
        method_name: String,
        line_number: u32,
        message: String,
        exception: String,
    ) {
        self.log(
            printer,
            Level::Debug,
            pid,
            thread_name,
            class_name,
            method_name,
            line_number,
            message,
            exception,
        );
    }

    fn debug_with_options(&self, options: &LevelLogOptions) {
        self.debug(
            options.printer.clone(),
            options.pid,
            options.thread_name.clone(),
            options.class_name.clone(),
            options.method_name.clone(),
            options.line_number,
            options.message.clone(),
            options.exception.clone(),
        );
    }

    fn info(
        &self,
        printer: Option<Rc<RefCell<dyn Printer>>>,
        pid: u32,
        thread_name: String,
        class_name: String,
        method_name: String,
        line_number: u32,
        message: String,
        exception: String,
    ) {
        self.log(
            printer,
            Level::Info,
            pid,
            thread_name,
            class_name,
            method_name,
            line_number,
            message,
            exception,
        );
    }

    fn info_with_options(&self, options: &LevelLogOptions) {
        self.info(
            options.printer.clone(),
            options.pid,
            options.thread_name.clone(),
            options.class_name.clone(),
            options.method_name.clone(),
            options.line_number,
            options.message.clone(),
            options.exception.clone(),
        );
    }

    fn warn(
        &self,
        printer: Option<Rc<RefCell<dyn Printer>>>,
        pid: u32,
        thread_name: String,
        class_name: String,
        method_name: String,
        line_number: u32,
        message: String,
        exception: String,
    ) {
        self.log(
            printer,
            Level::Warn,
            pid,
            thread_name,
            class_name,
            method_name,
            line_number,
            message,
            exception,
        );
    }

    fn warn_with_options(&self, options: &LevelLogOptions) {
        self.warn(
            options.printer.clone(),
            options.pid,
            options.thread_name.clone(),
            options.class_name.clone(),
            options.method_name.clone(),
            options.line_number,
            options.message.clone(),
            options.exception.clone(),
        );
    }

    fn error(
        &self,
        printer: Option<Rc<RefCell<dyn Printer>>>,
        pid: u32,
        thread_name: String,
        class_name: String,
        method_name: String,
        line_number: u32,
        message: String,
        exception: String,
    ) {
        self.log(
            printer,
            Level::Error,
            pid,
            thread_name,
            class_name,
            method_name,
            line_number,
            message,
            exception,
        );
    }

    fn error_with_options(&self, options: &LevelLogOptions) {
        self.error(
            options.printer.clone(),
            options.pid,
            options.thread_name.clone(),
            options.class_name.clone(),
            options.method_name.clone(),
            options.line_number,
            options.message.clone(),
            options.exception.clone(),
        );
    }

    fn fatal(
        &self,
        printer: Option<Rc<RefCell<dyn Printer>>>,
        pid: u32,
        thread_name: String,
        class_name: String,
        method_name: String,
        line_number: u32,
        message: String,
        exception: String,
    ) {
        self.log(
            printer,
            Level::Fatal,
            pid,
            thread_name,
            class_name,
            method_name,
            line_number,
            message,
            exception,
        );
    }

    fn fatal_with_options(&self, options: &LevelLogOptions) {
        self.fatal(
            options.printer.clone(),
            options.pid,
            options.thread_name.clone(),
            options.class_name.clone(),
            options.method_name.clone(),
            options.line_number,
            options.message.clone(),
            options.exception.clone(),
        );
    }
}
