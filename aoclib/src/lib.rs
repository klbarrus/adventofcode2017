// Adevent Of Code helper functions
// Karl L. Barrus <klbarrus@yahoo.com>

use std::env;
use std::fs;
use std::fs::File;
use std::io;
use std::io::BufRead;
use std::io::BufReader;
use std::string::String;

// if there is a command line argument, use that as the filename
// if not, use the specified filename passed in
fn get_filename(name: &str) -> String {
    let args: Vec<String> = env::args().collect();
    let filename: String;
    if args.len() > 1 {
        filename = args[1].clone();
    } else {
        filename = name.to_string();
    }
    filename
}

pub fn read_file_string(name: &str) -> io::Result<String> {
    let filename = get_filename(name);
    let mut filedata = fs::read_to_string(filename)?;
    filedata = filedata.trim().to_string();
    Ok(filedata)
}

pub fn read_file_lines(name: &str) -> io::Result<Vec<String>> {
    let filename = get_filename(name);
    let file = File::open(filename)?;
    let filebuf = BufReader::new(file);
    let mut res: Vec<String> = Vec::new();
    for line in filebuf.lines() {
        res.push(line.unwrap())
    }
    Ok(res)
}
