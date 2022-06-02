#![allow(dead_code)]

struct Solution;

#[derive(Debug)]
enum Token {
    Open(Open),
    Close(Close),
}

#[derive(Debug)]
enum Open {
    Paren,
    Curly,
    Bracket,
}

#[derive(Debug)]
enum Close {
    Paren,
    Curly,
    Bracket,
}

impl Solution {
    pub fn is_valid(s: String) -> bool {
        let mut string = std::collections::VecDeque::<Token>::new();
        for c in s.chars() {
            match c {
                '(' => {
                    string.push_back(Token::Open(Open::Paren));
                }
                ')' => {
                    string.push_back(Token::Close(Close::Paren));
                }
                '{' => {
                    string.push_back(Token::Open(Open::Curly));
                }
                '}' => {
                    string.push_back(Token::Close(Close::Curly));
                }
                '[' => {
                    string.push_back(Token::Open(Open::Bracket));
                }
                ']' => {
                    string.push_back(Token::Close(Close::Bracket));
                }
                _ => {
                    panic!("all characters must be parentheses");
                }
            }
        }
        let mut stack = std::collections::VecDeque::<Token>::new();
        while !string.is_empty() {
            let c = string.pop_front().unwrap();
            let top = stack.pop_front();
            if top.is_none() {
                stack.push_front(c);
                continue;
            }
            let top = top.unwrap();
            match (top, c) {
                (Token::Open(top), Token::Open(token)) => {
                    stack.push_front(Token::Open(top));
                    stack.push_front(Token::Open(token));
                }
                (Token::Close(_), Token::Close(_)) => {
                    return false;
                }
                (Token::Open(a), Token::Close(b)) => match (a, b) {
                    (Open::Paren, Close::Paren)
                    | (Open::Bracket, Close::Bracket)
                    | (Open::Curly, Close::Curly) => {
                        continue;
                    }
                    _ => {
                        return false;
                    }
                },
                (Token::Close(_), Token::Open(_)) => {
                    return false;
                }
            }
        }
        // println!("{:?}", stack.iter().collect::<Vec<&Token>>());
        stack.is_empty()
    }
}

#[cfg(test)]
mod test {
    use super::*;

    #[test]
    fn examples() {
        assert_eq!(true, Solution::is_valid("()".to_string()));
        assert_eq!(true, Solution::is_valid("()[]{}".to_string()));
        assert_eq!(false, Solution::is_valid("(]".to_string()));
    }

    #[test]
    fn challenges() {
        assert_eq!(true, Solution::is_valid("{[]}".to_string()));
    }
}
