#[cfg(test)]
mod test {
    use std::io::{BufRead, BufReader};
    use std::path::PathBuf;
    use itertools::Itertools;

    #[test]
    fn test_fn() {
        let mut config_path = PathBuf::from(env!("CARGO_MANIFEST_DIR"));
        config_path.push("src");
        config_path.push("test.env");
        let file = std::fs::File::open(config_path).unwrap();
        let reader = BufReader::new(file);
        let ret = reader.lines().map(|line| {
            let line = line.unwrap();
            let split_lines: Vec<_> = line.split('=').collect();
            split_lines[0].to_string()
        }).join(",");
        println!("{ret}");
    }
}
