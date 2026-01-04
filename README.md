Project Name: Automated Logical Reasoning System (ALRS)
Overview:
This program is a pure procedural C++ application that parses logic expressions and performs validation. It does NOT use classes, vectors, or STL stacks.
How to Compile and Run:
1. Open the source code in DevC++ or VS Code.
2. Ensure a C++ compiler (g++) is installed.
3. Compile and Run. No external libraries are needed.
Features Implemented:
1. Truth Table Generator: Parses logical expressions (infix to postfix) and generates a full truth table using binary counting.
2. Argument Validator: Accepts multiple premises and a conclusion to check for logical validity by searching for counterexamples.
3. Equivalence Checker: Compares two expressions to see if their truth tables are identical.
4. Reasoning Chain: Simulates a reasoning chain using Modus Ponens logic.
5. File Handling: Can read previous results from "results.txt".
Limitations:
1.Supports up to 5 unique variables (P, Q, R, S, T).
2.Variables must be single uppercase letters.
3.Input length is limited to 100 characters.
