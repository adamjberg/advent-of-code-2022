// https://www.reddit.com/r/adventofcode/comments/z9ezjb/comment/iyk2rga/?utm_source=share&utm_medium=web2x&context=3
fn main() {
    let input: Vec<usize> = include_str!("input.txt")
        .split("\n\n")
        .map(|b| 
            b.lines()
            .map(|i| i.parse::<usize>().unwrap())
            .sum()
        )
        .collect();

    let max = input.iter().max().unwrap();
    println!("max {}", max);
}