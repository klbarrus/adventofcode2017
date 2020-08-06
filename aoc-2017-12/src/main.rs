// Advent of Code 2017 Day 12

use aoclib;
use std::io;
use std::collections::HashSet;
use regex::Regex;

fn get_rhs(rhs_str: &str) -> Vec<i16> {
  let mut v: Vec<i16> = Vec::new();
  let re = Regex::new(r"(\d+)").unwrap();
  for cap in re.captures_iter(rhs_str) {
    v.push(cap[0].parse::<i16>().unwrap());
  }
  v.remove(0);

  v
}

fn main() -> io::Result<()> {
  let lines = aoclib::read_file_lines(&"2017-12.txt")?;

  let mut groups: Vec<HashSet<i16>> = Vec::new();
  let mut group: HashSet<i16> = HashSet::new();
  groups.push(group);

  let mut rhs = get_rhs(&lines[0]);
  while !rhs.is_empty() {
    let first_elem = rhs.remove(0);
    if !groups[0].contains(&first_elem) {
      groups[0].insert(first_elem);
      let new_rhs = get_rhs(&lines[first_elem as usize]);
      for new_rhs_item in new_rhs {
        rhs.push(new_rhs_item);
      }
    }
  }

  println!("part 1: {}", groups[0].len());

  Ok(())
}