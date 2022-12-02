// https://www.reddit.com/r/adventofcode/comments/z9ezjb/comment/iyk2rga/?utm_source=share&utm_medium=web2x&context=3
use std::time::{SystemTime};
use std::fs::File;
use std::io::prelude::*;


fn main() {
  let start = SystemTime::now();

  let mut file = File::open("input.txt").unwrap();
  let mut contents = String::new();
  file.read_to_string(&mut contents);

  let read_duration = SystemTime::now()
    .duration_since(start).unwrap();

  println!("Read: {:?}", read_duration);

  let mut input: Vec<usize> = contents
      .split("\n\n")
      .map(|b|
          b.lines()
              .map(|i| i.parse::<usize>().unwrap())
              .sum()
      )
      .collect();
      
  input.sort();
  input.reverse();
  input.truncate(3);
  let sum:usize = input.iter().sum();

  let since_the_epoch = SystemTime::now()
    .duration_since(start)
    .expect("Time went backwards");
  
  println!("{:?}", since_the_epoch);

  println!("sum {}", sum);
}