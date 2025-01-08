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


use  std::ptr::eq;
use std::{cell::RefCell, rc::Rc};

use crate::{
    filter::{Filter, ReleaseFilter},
    format::{default_message_format::DefaultMessageFormat, format::Format},
    level::Level,
    printer::printer::Printer,
};

pub struct Config<T: Format, F: Filter> {
    pub format: Option<T>,
    pub level: Level,
    pub filter: Option<F>,
    pub enabled: bool,
    printers: Vec<Rc<RefCell<dyn Printer>>>,
}

impl<T: Format, F: Filter> Config<T, F> {
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

impl Config<DefaultMessageFormat, ReleaseFilter> {
    pub fn new_default() -> Config<DefaultMessageFormat, ReleaseFilter> {
        return Config {
            format: Some(DefaultMessageFormat::new()),
            level: Level::Debug,
            filter: None,
            enabled: true,
            printers: vec![],
        };
    }
}
