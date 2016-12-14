README
a) To run: in terminal cd into the directory with project files. type in:
gcc Value.c Gates.c Circuit.c main.c -o main
there is one warning that pertains to Ferguson’s code and then type:
./main
b) Interpreting output: there are 5 different circuits to be output. Functions for them are all in main.c
Here is what you are supposed to see:
Testing circuit1 : (x and not y) or (y and z) 
T T T -> T
T T F -> F
T F T -> T
T F F -> T
F T T -> T
F T F -> F
F F T -> F
F F F -> F
Testing circuit2 : (x nand not y) nor (y nand z) 
T T T -> F
T T F -> F
T F T -> F
T F F -> F
F T T -> F
F T F -> F
F F T -> F
F F F -> F
Testing circuit3 :  (y and x) or (not x and not y) 
T T -> T
T F -> F
F T -> F
F F -> T
Testing extra credit circuit4 for gate d: 
  (not x and y and c) or (x and not y and c) or (x and y and not c) or (x and y and c) 
T T T -> T
T T F -> T
T F T -> T
T F F -> F
F T T -> T
F T F -> F
F F T -> F
F F F -> F
Testing extra credit circuit5 for gate z : 
 (not x and not y and c) or (not x and y and not c) or (x and not y and not c) or (x and y and c) 
T T T -> T
T T F -> F
T F T -> F
T F F -> T
F T T -> F
F T F -> T
F F T -> T
F F F -> F
The output says which circuit you are testing, what’s the boolean expression for that circuit, and outputs the truth table for it
c) No collaborators
d) Thanks, George, for code