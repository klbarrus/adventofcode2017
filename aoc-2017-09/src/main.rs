// Advent of Code 2017, Day 9

use aoclib;
use std::io;
use std::string::String;

fn main() -> io::Result<()> {
    let lines = aoclib::read_file_lines(&"2017-09.txt")?;

    for line in lines {
        let mut in_garb: bool = false;
        let mut skip_next: bool = false;
        let mut count: u16 = 0;
        let mut cleaned = String::from("");

        for ch in line.chars() {
            if skip_next {
                skip_next = false;
            } else {
                if in_garb {
                    // inside garbage, ! : ignore next character
                    //                 < : no special meaning
                    match ch {
                        '!' => skip_next = true,
                        '>' => in_garb = false,
                        _ => count += 1,
                    }
                } else {
                    // outside garbage, < : start garbage
                    //                  > : end garbage
                    match ch {
                        '>' => in_garb = false,
                        '<' => in_garb = true,
                        '{' => cleaned.push(ch),
                        '}' => cleaned.push(ch),
                        _ => (),
                    }
                }
            }
        }

        // at this point, only group markers remain

        let mut nesting: u16 = 0;
        let mut score: u16 = 0;

        for ch in cleaned.chars() {
            match ch {
                '{' => nesting += 1,
                '}' => {
                    score += nesting;
                    nesting -= 1;
                }
                _ => println!("unexpected character!"),
            };
        }

        println!("part 1 score: {}", score);
        println!("part 2 count: {}", count);
    }

    Ok(())
}
