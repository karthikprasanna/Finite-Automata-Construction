# Non-Deterministic-Finite-Automata-Construction

## Input Format
The input will be a file containing the regular expression in a single line

## Constraints
The regex alphabet will only consist of lower-case letters (a−z). The operators that will be used are:
1. '+' for union
2. ∗ for closure/star operation
3. Continuous letters will signify concatenation
4. () for grouping expressions

## Output Format
First line will contain 3 numbers n, k and, a respectively.

'n' is the number of states in the NFA.

Next line will consist of 'a' numbers which represent the set of accept states. 

Next 'k' lines will consist of the transition rules in the format: s1 x s2. s1 is the initial state, x is the symbol and s2 is the final state.