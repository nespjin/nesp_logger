use std::{cell::RefCell, rc::Rc};

use chrono::FixedOffset;
use nesp_logger::{
    filter::ReleaseFilter,
    log_manager::LogManager,
    nesp_logger::ILogger,
    printer::{console_printer::ConsolePrinter, printer::Printer},
};

#[test]
fn test_log_manager() {
    let printer: Rc<RefCell<dyn Printer>> = Rc::new(RefCell::new(ConsolePrinter::new()));

    static COUNT: i64 = 2;
    // static COUNT: i64 = 100000;
    // static COUNT: i64 = 99999999999999999;

    let mut i: i64 = COUNT;
    while i > 0 {
        let log_manager_arc = LogManager::shared();
        let mut log_manager = log_manager_arc.lock().unwrap();
        let logger = log_manager.get_logger("test_class".to_string());

        let cfg = log_manager.get_config();

        if i == COUNT {
            // Add a custom printer to config
            cfg.borrow_mut().add_printer(printer.clone());

            //  Set a custom filter to ReleaseFilter
            cfg.borrow_mut().filter = Some(Rc::new(RefCell::new(ReleaseFilter)));

            // Set time zone to UTC+8
            cfg.borrow_mut().time_zone = FixedOffset::east_opt(8 * 3600);
        }

        if i < COUNT {
            // Test remove a printer
            cfg.borrow_mut().remove_printer(&printer);
        }

        drop(log_manager);

        logger.info(
            None,
            1,
            "main-thread".to_string(),
            "test".to_string(),
            "main".to_string(),
            12,
            "This is info message".to_string(),
            "".to_string(),
        );
        logger.debug(
            None,
            1,
            "main-thread".to_string(),
            "test".to_string(),
            "main".to_string(),
            13,
            "This is debug message".to_string(),
            "".to_string(),
        );
        logger.warn(
            None,
            1,
            "main-thread".to_string(),
            "test".to_string(),
            "main".to_string(),
            14,
            "This is warn message".to_string(),
            "".to_string(),
        );
        logger.error(
            None,
            1,
            "main-thread".to_string(),
            "test".to_string(),
            "main".to_string(),
            15,
            "This is error message".to_string(),
            "".to_string(),
        );
        logger.fatal(
            None,
            1,
            "main-thread".to_string(),
            "test".to_string(),
            "main".to_string(),
            16,
            "This is fatal message".to_string(),
            "".to_string(),
        );
        println!();

        i -= 1;
    }
}
