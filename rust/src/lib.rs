pub mod level;
pub mod log_record;
pub mod filter;
pub mod config;
pub mod format;
pub mod printer;
pub mod nesp_logger;
pub mod log_manager;

// pub fn add(left: usize, right: usize) -> usize {
//     left + right
// }

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn it_works() {
        // let result = add(2, 2);
        // assert_eq!(result, 4);

        let fatal = level::Level::Fatal;
        println!("{:?}", fatal);
    }
}
