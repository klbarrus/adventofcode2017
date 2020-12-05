// Advent of Code 2017 Day 13

use aoclib;
use itertools::Itertools;
use std::collections::HashMap;
use std::fmt;
use std::io;

struct Bouncer {
    state: (u8, u8, bool),
}

impl Iterator for Bouncer {
    type Item = u8;

    fn next(&mut self) -> Option<u8> {
        let val = self.state.0;
        let max = self.state.1;
        let mut dir = self.state.2;

        if val == max && dir {
            dir = false;
        }
        if val == 0 && !dir {
            dir = true;
        }

        self.state.2 = dir;

        if dir {
            self.state.0 = self.state.0 + 1;
        } else {
            //if self.state.0 > 0 {
            self.state.0 = self.state.0 - 1;
            //}
        }

        Some(val)
    }
}

impl fmt::Debug for Bouncer {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        f.debug_struct("Bouncer")
            .field("init", &self.state.0)
            .field("max", &self.state.1)
            .field("dir", &self.state.2)
            .finish()
    }
}

fn main() -> io::Result<()> {
    let lines = aoclib::read_file_lines(&"2017-13.txt")?;

    let firewall = lines
        .iter()
        .flat_map(|l| {
            l.split(':')
                .map(|s| s.trim().parse().unwrap_or(0))
                .tuples::<(u8, u8)>()
        })
        //    .map(|t| {println!("({},{})", t.0, t.1); t})
        .map(|t| {
            (
                t.0,
                Bouncer {
                    state: (0, t.1, true),
                },
            )
        })
        .collect::<HashMap<u8, _>>();

    println!("{:#?}", firewall);

    Ok(())
}
