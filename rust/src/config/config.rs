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
 *
 */

use std::ptr::eq;
use std::{cell::RefCell, rc::Rc};
use chrono::FixedOffset;

use crate::{
    filter::Filter,
    format::{default_message_format::DefaultMessageFormat, format::Format},
    level::Level,
    printer::printer::Printer,
};

pub struct Config {
    pub format: Option<Rc<RefCell<dyn Format>>>,
    pub level: Level,
    pub filter: Option<Rc<RefCell<dyn Filter>>>,
    pub enabled: bool,
    pub time_zone: Option<FixedOffset>,
    printers: Vec<Rc<RefCell<dyn Printer>>>,
}

impl Config {
    pub fn add_printer(&mut self, printer: Rc<RefCell<dyn Printer>>) {
        self.printers.push(printer);
    }

    pub fn remove_printer(&mut self, printer: &Rc<RefCell<dyn Printer>>) {
        self.printers.retain(|p| eq(p.as_ptr(), printer.as_ptr()));
    }

    pub fn get_printers(&self) -> Vec<Rc<RefCell<dyn Printer>>> {
        return self.printers.clone();
    }
}

impl Config {
    pub fn new_default() -> Config {
        return Config {
            format: Some(Rc::new(RefCell::new(DefaultMessageFormat::new()))),
            level: Level::Debug,
            filter: None,
            enabled: true,
            time_zone: None,
            printers: vec![],
        };
    }
}
