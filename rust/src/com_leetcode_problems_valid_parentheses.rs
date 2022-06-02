#![allow(dead_code)]

struct Solution;

#[derive(Debug, Clone, Copy)]
enum Token {
    Open(Open),
    Close(Close),
}

#[derive(Debug, Clone, Copy)]
enum Open {
    Paren,
    Curly,
    Bracket,
}

#[derive(Debug, Clone, Copy)]
enum Close {
    Paren,
    Curly,
    Bracket,
}

impl Solution {
    pub fn is_valid2(s: String) -> bool {
        let mut st = std::collections::VecDeque::<char>::new();
        for c in s.chars() {
            if st.is_empty() {
                st.push_front(c);
            } else {
                match (st.pop_front().unwrap(), c) {
                    x @ ('(' | '[' | '{', '(' | '[' | '{') => {
                        st.push_front(x.0);
                        st.push_front(x.1);
                    }
                    ('(', ')') | ('[', ']') | ('{', '}') => {}
                    _ => {
                        return false;
                    }
                }
            }
        }
        st.is_empty()
    }

    pub fn is_valid(s: String) -> bool {
        let mut string = Vec::<Token>::with_capacity(s.chars().count());
        for c in s.chars() {
            match c {
                '(' => {
                    string.push(Token::Open(Open::Paren));
                }
                ')' => {
                    string.push(Token::Close(Close::Paren));
                }
                '{' => {
                    string.push(Token::Open(Open::Curly));
                }
                '}' => {
                    string.push(Token::Close(Close::Curly));
                }
                '[' => {
                    string.push(Token::Open(Open::Bracket));
                }
                ']' => {
                    string.push(Token::Close(Close::Bracket));
                }
                _ => {
                    panic!("all characters must be parentheses");
                }
            }
        }
        let mut stack = std::collections::VecDeque::<Token>::new();
        for c in string.iter() {
            let top = stack.pop_front();
            if top.is_none() {
                stack.push_front(*c);
                continue;
            }
            let top = top.unwrap();
            match (top, c) {
                (Token::Open(top), Token::Open(token)) => {
                    stack.push_front(Token::Open(top));
                    stack.push_front(Token::Open(*token));
                }
                (Token::Open(Open::Paren), Token::Close(Close::Paren))
                | (Token::Open(Open::Bracket), Token::Close(Close::Bracket))
                | (Token::Open(Open::Curly), Token::Close(Close::Curly)) => {}
                (_, _) => {
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
