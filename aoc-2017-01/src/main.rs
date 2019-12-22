use aoclib;
use std::io;

fn captcha(code: &str, offset: usize) -> usize {
    let mut res = 0usize;

    let start = &code[0..offset];
    let end = &code[offset..code.len()];
    let mut rotated = end.to_owned();
    rotated.push_str(start);

    for (x, y) in code.chars().zip(rotated.chars()) {
        if x == y {
            res += match x {
                '0'..='9' => x.to_digit(10).unwrap(),
                _ => 0,
            } as usize;
        }
    }

    res
}

fn main() -> io::Result<()> {
    let filestring = aoclib::read_file_string(&"2017-01.txt")?;
    let mut res;

    res = captcha(&filestring, 1);
    println!("Part 1: {}", res);

    res = captcha(&filestring, filestring.len() / 2);
    println!("Part 1: {}", res);

    Ok(())
}
