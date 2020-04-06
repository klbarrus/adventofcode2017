// Advent of Code 2017, Day 10

use aoclib;
use std::io;

fn main() -> io::Result<()> {
    let filestr = aoclib::read_file_string(&"2017-10.txt")?;

    let mut list: Vec<usize> = Vec::with_capacity(256);
    list.resize(256, 0);
    for i in 0..=255 {
        list[i] = i;
    }

    let mut cur_pos: u16 = 0;
    let mut skip_size: u16 = 0;

    let split = filestr.split(",");
    for len_str in split {
        let len = len_str.parse::<u16>().unwrap();

        if len > 1 {
            let mut start = cur_pos;
            let mut end = (start + len - 1) % 256;
            let count = len / 2;
            for _ in 0..count {
                list.swap(start as usize, end as usize);
                start = (start + 1) % 256;
                if end == 0 {
                    end = 255;
                } else {
                    end = end - 1;
                }
            }
        }

        cur_pos = (cur_pos + len + skip_size) % 256;
        skip_size += 1;
    }

    println!("part 1: {}", list[0] * list[1]);

    Ok(())
}
