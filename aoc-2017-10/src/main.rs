// Advent of Code 2017, Day 10

use aoclib;
use std::io;

fn select_reverse(list: &mut Vec<usize>, cur_pos: u16, len: u16) -> () {
    let mut head = cur_pos;
    let mut tail = (head + len - 1) % 256;
    let count = len / 2;
    for _ in 0..count {
        list.swap(head as usize, tail as usize);
        head = (head + 1) % 256;
        if tail == 0 {
            tail = 255;
        } else {
            tail = tail - 1;
        }
    }
}

fn convert_to_bytes(list: String) -> String {
    let mut rv: String = String::new();

    for ch in list.chars() {
        let numstr = match ch {
            '0' => "48",
            '1' => "49",
            '2' => "50",
            '3' => "51",
            '4' => "52",
            '5' => "53",
            '6' => "54",
            '7' => "55",
            '8' => "56",
            '9' => "57",
            ',' => "44",
            _ => "error",
        };

        rv = rv + numstr;
        rv = rv + ",";
    }

    // add length suffix specified in the puzzle
    rv = rv + "17,31,73,47,23";

    rv
}

fn main() -> io::Result<()> {
    let filestr = aoclib::read_file_string(&"2017-10.txt")?;

    // in part 1, the input is a sequence of (integer) lengths
    let part1_str = filestr.clone();
    let part1_split = part1_str.split(",");

    let mut list: Vec<usize> = Vec::with_capacity(256);
    list.resize(256, 0);
    for i in 0..=255 {
        list[i] = i;
    }

    let mut cur_pos: u16 = 0;
    let mut skip_size: u16 = 0;

    for len_str in part1_split {
        let len = len_str.parse::<u16>().unwrap();

        // only need to select-reverse if the length is greater than 1
        if len > 1 {
            select_reverse(&mut list, cur_pos, len);
        }

        cur_pos = (cur_pos + len + skip_size) % 256;
        skip_size += 1;
    }
    println!("part 1: {}", list[0] * list[1]);

    // in part 2, the input is a string of bytes - each char is an ascii value
    let part2_str = convert_to_bytes(filestr.clone());
    let part2_split = part2_str.split(",");

    for i in 0..=255 {
        list[i] = i;
    }

    let mut cur_pos: u16 = 0;
    let mut skip_size: u16 = 0;

    // in part 2, perform 64 rounds using the same length sequence
    // but preserve current position and skip size between rounds
    for _ in 0..=63 {
        for len_str in part2_split.clone() {
            let len = len_str.parse::<u16>().unwrap();

            // only need to select-reverse if the length is greater than 1
            if len > 1 {
                select_reverse(&mut list, cur_pos, len);
            }

            cur_pos = (cur_pos + len + skip_size) % 256;
            skip_size += 1;
        }
    }

    print!("part 2: ");
    for chunk in list.chunks(16) {
        let xor = chunk.iter().fold(0, |xor, x| xor ^ x);
        print!("{:x}", xor);
    }
    println!();

    Ok(())
}
