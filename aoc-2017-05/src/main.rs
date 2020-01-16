// Advent of Code 2017, Day 5

use aoclib;
use std::io;

fn count_jumps(mut prog: Vec<isize>, offset_func: fn(isize) -> isize) -> usize {
    let mut numjumps = 0usize;
    let mut pos = 0usize;

    while pos < prog.len() {
        let offset = prog[pos];
        prog[pos] += offset_func(offset);
        if offset < 0 {
            pos = pos - offset.abs() as usize;
        } else {
            pos = pos + offset as usize;
        }
        numjumps += 1;
    }

    numjumps
}

fn main() -> io::Result<()> {
    let lines = aoclib::read_file_lines(&"2017-05.txt")?;
    let prog: Vec<isize> = lines.iter().map(|x| x.parse().unwrap()).collect();
    let prog2 = prog.clone();
    let offset1 = |_a: isize| 1;
    let offset2 = |a: isize| if a >= 3 { -1 } else { 1 };

    let mut numjumps = count_jumps(prog, offset1);
    println!("part 1: {}", numjumps);

    numjumps = count_jumps(prog2, offset2);
    println!("part 2: {}", numjumps);

    Ok(())
}
