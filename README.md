[![Open in Codespaces](https://classroom.github.com/assets/launch-codespace-7f7980b617ed060a017424585567c406b6ee15c891e84e1186181d67ecf80aa0.svg)](https://classroom.github.com/open-in-codespaces?assignment_repo_id=13904608)

## COMP 310: R-FORTH 
By isafari 
### How to Use

Run the program from the command line. Once started, the program will prompt you to enter. 

#### Input Format

- **Numbers**
- **Arithmetic Operators**: `+`, `-`, `*`, `/`
- **Symbols**: `:` and `;`.
- **Words**: Sequences of symbols or operators will be treated as words along with strings and characters.

Press enter afterwards.

### Building the Project

GCC: gcc -o main  main.c int_stack.c token.c -I.
CMAKE: 
Check if build file. If not, mkdir build in RFORTH directory, cd build, cmake .., make.
Run the program with ./main

## Testing

Run the tests:

1. Change to the `build` directory with

   `bash
    cd build
    `
    

2. Build the project if not already built with

    `cmake ..`

    `make`
    

3. Run the tests with googletest:

    ``./bin/googletest``

