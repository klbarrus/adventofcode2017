// Advent of Code 2017, Day 11

use aoclib;
use std::io;

// using cube coordinates and the distance formula for hex grids
// from redblobgames.com
struct Distance {
    x: i32,
    y: i32,
    z: i32,
}

fn current_distance(dist: &Distance) -> i32 {
    let curr_dist_vec = vec![dist.x.abs(), dist.y.abs(), dist.z.abs()];
    let curr_dist = curr_dist_vec.iter().max();
    match curr_dist {
        Some(x) => *x,
        None => 0,
    }
}

fn main() -> io::Result<()> {
    let filestr = aoclib::read_file_string(&"2017-11.txt")?;
    let mut dist: Distance = Distance { x: 0, y: 0, z: 0 };
    let mut max_dist: i32 = 0;

    for dir in filestr.split(",") {
        match dir {
            "n" =>  { dist.y += 1; dist.z -= 1 },
            "s" =>  { dist.y -= 1; dist.z += 1 },
            "ne" => { dist.x += 1; dist.z -= 1 },
            "sw" => { dist.x -= 1; dist.z += 1 },
            "nw" => { dist.x -= 1; dist.y += 1 },
            "se" => { dist.x += 1; dist.y -= 1 },
            _ => println!("unexpected direction"),
        };
        let curr_dist = current_distance(&dist);
        if curr_dist > max_dist {
            max_dist = curr_dist;
        }
    }
    let end_dist = current_distance(&dist);
    println!("part 1: {}", end_dist);
    println!("part 2: {}", max_dist);

    Ok(())
}
