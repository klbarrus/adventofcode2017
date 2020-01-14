use aoclib;
use itertools::Itertools;
use std::cmp;
use std::io;

fn main() -> io::Result<()> {
    let lines = aoclib::read_file_lines(&"2017-02.txt")?;
    let mut checksum1 = 0usize;
    let mut checksum2 = 0usize;

    for line in lines {
        let nums: Vec<usize> = line
            .split_whitespace()
            .map(|x| x.parse().unwrap())
            .collect();

        let max = nums.iter().max().unwrap();
        let min = nums.iter().min().unwrap();
        checksum1 += max - min;

        for (a, b) in nums.iter().tuple_combinations() {
            let minab = cmp::min(a, b);
            let maxab = cmp::max(a, b);
            if maxab % minab == 0 {
                checksum2 += maxab / minab;
                break;
            }
        }
    }

    println!("Part 1: {}", checksum1);
    println!("Part 2: {}", checksum2);

    Ok(())
}
