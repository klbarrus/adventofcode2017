// Advent of Code 2017 Day 4

use aoclib;
use std::collections::HashSet;
use std::io;

fn main() -> io::Result<()> {
    let lines = aoclib::read_file_lines(&"2017-04.txt")?;
    let mut numvalid1 = 0usize;
    let mut numvalid2 = 0usize;

    for line in lines {
        let mut set1 = HashSet::new();
        let mut set2 = HashSet::new();
        let mut valid1 = true;
        let mut valid2 = true;
        let words: Vec<&str> = line.split_whitespace().collect();

        for s in words {
            let mut newval = set1.insert(s);
            if newval == false {
                valid1 = false;
            }

            let mut chars: Vec<char> = s.chars().collect();
            chars.sort();
            newval = set2.insert(chars);
            if newval == false {
                valid2 = false;
            }
        }

        if valid1 == true {
            numvalid1 += 1;
        }

        if valid2 == true {
            numvalid2 += 1;
        }
    }

    println!("part 1: {}", numvalid1);
    println!("part 1: {}", numvalid2);

    Ok(())
}
