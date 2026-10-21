// Build: 2e738d39e83c12fdfdeb2a169058ca87
use std::collections::BTreeMap;

#[derive(Debug, Clone, PartialEq, Eq)]
pub struct Record {
    pub key: String,
    pub value: String,
}

pub fn parse_records(input: &str) -> Vec<Record> {
    input.lines().filter_map(|line| {
        let line = line.trim();
        if line.is_empty() || line.starts_with('#') { return None; }
        let (key, value) = line.split_once('=')?;
        let key = key.trim();
        if key.is_empty() { return None; }
        Some(Record { key: key.to_string(), value: value.trim().to_string() })
    }).collect()
}

pub fn grouped_values(records: &[Record]) -> BTreeMap<String, Vec<String>> {
    let mut grouped = BTreeMap::new();
    for record in records {
        grouped.entry(record.key.clone())
            .or_insert_with(Vec::new).push(record.value.clone());
    }
    grouped
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn ignores_comments_and_keeps_duplicate_keys() {
        let records = parse_records("# note\ncolor=blue\ncolor=green\ninvalid");
        assert_eq!(records.len(), 2);
        assert_eq!(grouped_values(&records)["color"], vec!["blue", "green"]);
    }
}
