#![allow(dead_code)]

use std::collections::HashMap;

struct Solution;

impl Solution {
    pub fn count_of_atoms(formula: String) -> String {
        let formula = formula.as_bytes();
        let mut st: Vec<HashMap<String, u32>> = vec![];
        st.push(HashMap::new());
        let mut idx: usize = 0;
        while idx < formula.len() {
            match formula[idx] {
                b'(' => {
                    st.push(HashMap::new());
                    idx += 1; // consume '('
                }
                b')' => {
                    idx += 1; // consume ')'
                    let last = st.pop().unwrap();
                    let mut factor: u32 = 0u32;
                    while idx < formula.len() && formula[idx].is_ascii_digit() {
                        factor = factor * 10 + (formula[idx] as u32 - '0' as u32);
                        idx += 1;
                    }
                    factor = factor.max(1);
                    let top = st.last_mut().unwrap();
                    for (atom_name, atom_count) in &last {
                        let old_value = top.get(atom_name).unwrap_or(&0);
                        top.insert(atom_name.clone(), old_value + (atom_count * factor));
                    }
                }
                _ => {
                    let mut atom_name: String = String::new();
                    assert!(formula[idx].is_ascii_uppercase());
                    atom_name.push(formula[idx] as char);
                    idx += 1;
                    while idx < formula.len() && formula[idx].is_ascii_lowercase() {
                        atom_name.push(formula[idx] as char);
                        idx += 1;
                    }
                    let mut factor: u32 = 0u32;
                    while idx < formula.len() && formula[idx].is_ascii_digit() {
                        factor = factor * 10 + (formula[idx] as u32 - '0' as u32);
                        idx += 1;
                    }
                    factor = factor.max(1);
                    let top = st.last_mut().unwrap();
                    let old_value = top.get(&atom_name).unwrap_or(&0);
                    top.insert(atom_name, old_value + factor);
                }
            };
        }
        let mut ans: String = String::new();
        let top = st.last().unwrap();
        let mut sorted_keys: Vec<String> = top.keys().cloned().collect();
        sorted_keys.sort();
        for atom_name in sorted_keys.into_iter() {
            ans.push_str(&atom_name);
            let atom_count = top.get(&atom_name).unwrap();
            if *atom_count > 1 {
                ans.push_str(&atom_count.to_string());
            }
        }
        return ans;
    }
}

#[cfg(test)]
mod test {
    use super::*;

    #[test]
    fn examples() {
        assert_eq!("H2O", Solution::count_of_atoms("H2O".to_string()));
        assert_eq!("H2MgO2", Solution::count_of_atoms("Mg(OH)2".to_string()));
        assert_eq!(
            "K4N2O14S4",
            Solution::count_of_atoms("K4(ON(SO3)2)2".to_string())
        );
    }
}
