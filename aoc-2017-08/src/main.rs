// Advent of Code 2017, Day 8

use aoclib;
use std::collections::HashMap;
use std::io;

fn lookup_reg(table: &HashMap<String, isize>, reg: &str) -> isize {
    match table.get(reg) {
        Some(val) => *val,
        None => 0,
    }
}

fn logic_op(val1: isize, op: &str, val2: isize) -> bool {
    match op {
        "!=" => {
            if val1 != val2 {
                true
            } else {
                false
            }
        }
        "<" => {
            if val1 < val2 {
                true
            } else {
                false
            }
        }
        "<=" => {
            if val1 <= val2 {
                true
            } else {
                false
            }
        }
        ">" => {
            if val1 > val2 {
                true
            } else {
                false
            }
        }
        ">=" => {
            if val1 >= val2 {
                true
            } else {
                false
            }
        }
        _ => {
            if val1 == val2 {
                true
            } else {
                false
            }
        }
    }
}

fn main() -> io::Result<()> {
    let lines = aoclib::read_file_lines(&"2017-08.txt")?;
    let mut table: HashMap<String, isize> = HashMap::new();
    let mut maxopval = 0isize;
    let mut maxopreg = String::new();

    for line in lines {
        let parse: Vec<&str> = line.split_whitespace().collect();
        // parse[0] - register 1
        // parse[1] - operation (inc, dec)
        // parse[2] - isize literal
        // parse[3] - "if"
        // parse[4] - register 2
        // parse[5] - logic operation (==, <, <=, >, >=, !=)
        // parse[6] - isize literal

        let logval1: isize = lookup_reg(&table, parse[4]);
        let logval2: isize = parse[6].parse().unwrap();
        let cond = logic_op(logval1, parse[5], logval2);

        if cond {
            let mut opval = lookup_reg(&table, parse[0]);
            let argval: isize = parse[2].parse().unwrap();
            if parse[1] == "inc" {
                opval += argval;
            } else {
                opval -= argval;
            }
            if opval > maxopval {
                maxopval = opval;
                maxopreg = parse[0].to_string();
            }

            table.insert(parse[0].to_string(), opval);
        }
    }

    let mut maxval = 0isize;
    let mut maxreg = String::new();
    for (reg, val) in table {
        if val > maxval {
            maxval = val;
            maxreg = reg;
        }
    }

    println!("part 1: {} in {}", maxval, maxreg);
    println!("part 2: {} in {}", maxopval, maxopreg);

    Ok(())
}
