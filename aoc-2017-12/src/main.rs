// Advent of Code 2017 Day 12

use aoclib;
use std::io;
use std::collections::HashSet;
use regex::Regex;

// get the list of programs each program is connected to
// the regex also extracts the program left of the delimiter
// so delete that entry (element at 0)
fn get_rhs(rhs_str: &str) -> Vec<usize> {
  let mut v: Vec<usize> = Vec::new();
  let re = Regex::new(r"(\d+)").unwrap();
  for cap in re.captures_iter(rhs_str) {
    v.push(cap[0].parse::<usize>().unwrap());
  }
  v.remove(0);

  v
}

// given a program number, build a group of member programs
// do this by getting a vector of members (the right hand side of each line)
// and adding each program if it isn't already present
fn build_group(idx: usize, lines: &Vec<String>) -> HashSet<usize> {
  let mut group: HashSet<usize> = HashSet::new();
  let mut programs = get_rhs(&lines[idx]);
//    println!("create group {}", idx);
  while !programs.is_empty() {
    let prog = programs.remove(0);
    if !group.contains(&prog) {
//      println!("  insert {}", prog);
      group.insert(prog);
      let more_programs = get_rhs(&lines[prog]);
      for new_program in more_programs {
        programs.push(new_program);
      }
    }
  }

  group
}

fn main() -> io::Result<()> {
  let lines = aoclib::read_file_lines(&"2017-12.txt")?;

// create group 0, then the part 1 answer is the size of group 0
  let group_0 = build_group(0, &lines);
  println!("part 1: {}", group_0.len());

  let mut groups: Vec<HashSet<usize>> = Vec::new();
  groups.push(group_0);

// iterate over the rest of possible programs
// build a group for each one if it isn't already in any previous group
// part 2 answer is how many total groups  
  for prog_idx in 1..lines.len() {
    let mut found = false;
    for group in &groups {
      if group.contains(&prog_idx) {
        found = true;
        break;
      }
    }

    if !found {
      let group_new = build_group(prog_idx, &lines);
      groups.push(group_new);
    }
  }

  println!("part 2: {}", groups.len());

  Ok(())
}