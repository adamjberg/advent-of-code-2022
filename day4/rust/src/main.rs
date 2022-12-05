use std::fs::File;
use std::io::prelude::*;

fn main() {
    let mut file = File::open("input.txt").unwrap();
    let mut contents = String::new();
    file.read_to_string(&mut contents);

    let mut count = 0;

    let lines = contents.lines();
    let mut numbers: Vec<u32> = vec!();
    let mut current_number_string = String::new();
    for line in lines {
        for c in line.chars() {
            if c == '-' || c == ',' {
                let current_number_as_int: u32 = current_number_string.parse().unwrap();
                numbers.push(current_number_as_int);
                current_number_string.clear();
            } else {
                current_number_string.push(c);
            }

            if numbers.len() == 4 {
                if numbers[0] >= numbers[2] && numbers[0] <= numbers[3] {
                    count += 1;
                } else if numbers[1] >= numbers[2] && numbers[1] <= numbers[3] {
                    count += 1;
                } else if numbers[2] <= numbers[1] && numbers[2] >= numbers[0] {
                    count += 1;
                } else if numbers[3] <= numbers[1] && numbers[3] >= numbers[0] {
                    count += 1;
                }

                numbers.clear();
            }
        }

        let current_number_as_int: u32 = current_number_string.parse().unwrap();
        numbers.push(current_number_as_int);
        current_number_string.clear();
    }

    println!("{}", count);
}
