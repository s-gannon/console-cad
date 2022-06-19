# console-cad
A console-based computer aided design (CAD) program written in C

# Dependencies
- math.h
- curses.h
- stdlib.h
- string.h

# How to compile
`gcc -std=c99 -lncurses -lm -o console_cad -Wall -Wextra -pedantic`

# How to run
`./console_cad`

# Controls
These are listed in the instructions on the bottom line of the console, but to be pedantic:
- q - exit program
- f - create point
- d - delete point
- j - move up
- k - move down
- h - move left
- l - move right
