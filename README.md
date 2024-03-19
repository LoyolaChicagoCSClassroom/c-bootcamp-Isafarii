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

GCC: 
```bash
gcc -o main  main.c int_stack.c token.c -I.
```
CMAKE: 
Check if build file. If not, perform the following
```bash
mkdir build
cd build
cmake ..
make
```
Run the program with `./rforth`


## Testing

Run the tests:

1. Change to the `build` directory with

   `bash
    cd build
    `
    

2. Build the project if not already built with

    `cmake ..`

    `make`

3. Run the tests with `googletest` in `...RFORTH/build`:
   ```bash
   ./googletest
   ```
   
### Progress Updates
- **Adding Variable and Condition Support**: Recently added variable support, and made progress 3/15 commit to implement the conditions.

- 3/16: Added Test Cases, fixed bugs in main and other small adjustments

- 3/15-17~: Added support for funtions, still getting it to run in main. 
