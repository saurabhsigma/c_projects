# Chapter one - Setup 

To compile kilo.c, run cc kilo.c -o kilo in your shell. If no errors occur, this will produce an executable named kilo. -o stands for “output”, and specifies that the output executable should be named kilo.

To run kilo, type ./kilo in your shell and press Enter. The program doesn’t print any output, but you can check its exit status (the value main() returns) by running echo $?, which should print 0.

In Unix-like operating systems, echo $? is used to display the exit status of the last executed command. The exit status, or exit code, is a numerical value returned by a command or program when it finishes running. This value typically indicates whether the command was successful or if an error occurred.

makefile

kilo: kilo.c
        $(CC) kilo.c -o kilo -Wall -Wextra -pedantic -std=c99


# Chapter two - Entering raw mode

When you run ./kilo, your terminal gets hooked up to the standard input, and so your keyboard input gets read into the c variable. However, by default your terminal starts in canonical mode, also called cooked mode. In this mode, keyboard input is only sent to your program when the user presses Enter. This is useful for many programs: it lets the user type in a line of text, use Backspace to fix errors until they get their input exactly the way they want it, and finally press Enter to send it to the program. But it does not work well for programs with more complex user interfaces, like text editors. We want to process each keypress as it comes in, so we can respond to it immediately.

What we want is raw mode. Unfortunately, there is no simple switch you can flip to set the terminal to raw mode. Raw mode is achieved by turning off a great many flags in the terminal, which we will do gradually over the course of this chapter.

To exit the above program, press Ctrl-D to tell read() that it’s reached the end of file. Or you can always press Ctrl-C to signal the process to terminate immediately.

changing terminal attribute
We can set a terminal’s attributes by (1) using tcgetattr() to read the current attributes into a struct, (2) modifying the struct by hand, and (3) passing the modified struct to tcsetattr() to write the new terminal attributes back out. Let’s try turning off the ECHO feature this way.

The c_lflag field is for “local flags”. A comment in macOS’s <termios.h> describes it as a “dumping ground for other state”. So perhaps it should be thought of as “miscellaneous flags”. The other flag fields are c_iflag (input flags), c_oflag (output flags), and c_cflag (control flags), all of which we will have to modify to enable raw mode.

ECHO is a bitflag, defined as 00000000000000000000000000001000 in binary. We use the bitwise-NOT operator (~) on this value to get 11111111111111111111111111110111. We then bitwise-AND this value with the flags field, which forces the fourth bit in the flags field to become 0, and causes every other bit to retain its current value. Flipping bits like this is common in C.

