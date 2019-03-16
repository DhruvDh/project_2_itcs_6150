extern crate rand;

use rand::prelude::*;
use std::cmp::max;
use std::cmp::min;
use std::cmp::Ordering;
use std::fmt;
use std::io;
use std::rc::Rc;

use std::collections::BinaryHeap;

struct Board {
    n: usize,
    queens: Vec<(usize, usize)>,
    prev: Option<&'static Board>,
    next: BinaryHeap<Rc<Board>>,
    steps: usize,
    restarts: usize,
    kind: usize,
    cost: usize,
}

impl Ord for Board {
    fn cmp(&self, other: &Board) -> Ordering {
        other
            .cost
            .cmp(&self.cost)
            .then_with(|| self.cost.cmp(&other.cost))
    }
}

impl PartialOrd for Board {
    fn partial_cmp(&self, other: &Board) -> Option<Ordering> {
        Some(self.cmp(other))
    }
}
impl PartialEq for Board {
    fn eq(&self, other: &Board) -> bool {
        self.cost == other.cost
    }
}
impl Eq for Board {}

impl Board {
    fn new(n: usize, kind: usize) -> Board {
        println!("\nGenerating a random board..");
        let mut initial_config = Vec::<(usize, usize)>::with_capacity(n);
        let mut rng = thread_rng();
        initial_config.push((rng.gen_range(0, n), rng.gen_range(0, n)));

        Board {
            n,
            queens: initial_config,
            prev: None,
            next: BinaryHeap::with_capacity(n * n),
            steps: 0,
            restarts: 0,
            kind,
            cost: n * n + 1,
        }
    }

    fn cost(&self, new_queens: &Vec<(usize, usize)>) -> usize {
        let mut count = 0;
        for queen in new_queens {
            let (qi, qj) = queen;
            for other_queen in new_queens {
                let (oi, oj) = other_queen;
                let h_diff = max(oi, qi) - min(oi, qi);
                let v_diff = max(oj, qj) - min(oj, qj);

                if oi == qi && oj == qj {
                    continue;
                } else if oi == qi || oj == qj || h_diff == v_diff {
                    count += 1;
                }
            }
        }
        count
    }

    fn validate(&self) -> bool {
        self.queens.len() == self.n
    }

    fn compute_next(&mut self) {
        for i in 0..self.n {
            for j in 0..self.n {
                match self.queens.binary_search(&(i, j)) {
                    Ok(_) => continue,
                    Err(idx) => {
                        let mut new_queens = self.queens.clone();
                        new_queens.push((i, j));
                        let cost = self.cost(&new_queens);

                        self.next.push(Rc::from(Board {
                            n: self.n,
                            queens: new_queens,
                            prev: None,
                            next: BinaryHeap::with_capacity(self.n * self.n),
                            steps: self.steps + 1,
                            restarts: self.restarts,
                            kind: self.kind,
                            cost,
                        }))
                    }
                }
            }
        }
    }
}

impl fmt::Display for Board {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        let mut squares = vec![vec![false; self.n]; self.n];

        for queen in &self.queens {
            let &(qi, qj) = queen;
            squares[qi][qj] = true;
        }
        let mut line = String::from("");
        for row in squares {
            for square in row {
                line += if square { "Q " } else { "᛫ " };
            }
            line += "\n"
        }
        write!(f, "{}", line)
    }
}

// struct BoardGenerator {
//     initial_board: Board,
//     i: usize,
//     j: usize,
// }

// impl BoardGenerator {
//     fn from(board: Board) -> BoardGenerator {
//         BoardGenerator {
//             initial_board: board,
//             i: 0,
//             j: 0,
//         }
//     }

//     fn next(&mut self) -> Option<Board> {
//         self.j += 1;

//         if self.j >= self.initial_board.height {
//             self.i += 1;
//             self.j = 0;
//         }

//         if self.i >= self.initial_board.width {
//             return None;
//         }

//         match self.initial_board.queens.binary_search(&(self.i, self.j)) {
//             Ok(_) => self.next(),
//             Err(idx) => {
//                 let mut next_board = Board::new(&self.initial_board);
//                 next_board.queens.insert(idx, (self.i, self.j));
//                 Some(next_board)
//             }
//         }
//     }
// }

// fn correct(board: &Board, queen_number: usize) -> bool {
//     board.queens.len() == queen_number
// }

// fn backtrack(board: Board, queen_requirement: usize) -> Option<Board> {
//     if cost(&board) != 0 {
//         return None;
//     }
//     if correct(&board, queen_requirement) {
//         return Some(board);
//     }

//     let mut generator = BoardGenerator::from(board);
//     while let Some(next_board) = generator.next() {
//         if let Some(solution) = backtrack(next_board, queen_requirement) {
//             return Some(solution);
//         }
//     }

//     None
// }

fn main() {
    let mut input_text = String::new();
    println!("How many queens?");
    io::stdin()
        .read_line(&mut input_text)
        .expect("I forgot my reading glasses, I'll go get them why don't you try again.");

    let n = match input_text.trim().parse::<usize>() {
        Ok(i) => i,
        Err(..) => panic!("That didn't seem like an unsigned integer. Play nice."),
    };

    println!("And how should I go about solving it?");
    println!("1. Steepest hill-ascent climbing.\n2. Hill climbing with sideways move.\n3. Random-restart hill-climbing with sideways move.\n4. Random-restart hill-climbing without sideways move.");
    println!("\nOption? (1-4)");

    input_text = String::new();
    io::stdin()
        .read_line(&mut input_text)
        .expect("I forgot my reading glasses, I'll go get them why don't you try again.");

    let board: Board = match input_text.trim().parse::<usize>() {
        Ok(i) => match i {
            1 => Board::new(n, 1),
            2 => Board::new(n, 2),
            3 => Board::new(n, 3),
            4 => Board::new(n, 4),
            _ => panic!("Getting a number which isn't 1-4."),
        },
        Err(e) => panic!("Finding a number that didn't look like an unsigned integer. Play nice."),
    };

    println!("{}\nThis is the board", board);
}
