use aoclib;
use std::io;

fn main() -> io::Result<()> {
    let lines = aoclib::read_file_lines(&"2017-02.txt")?;
    let mut checksum1 = 0usize;

    for line in lines {
        let nums: Vec<usize> = line
            .split_whitespace()
            .map(|x| x.parse().unwrap())
            .collect();
        let max = nums.iter().max().unwrap();
        let min = nums.iter().min().unwrap();
        checksum1 += max - min;
    }

    println!("Part 1: {}", checksum1);

    Ok(())
}
