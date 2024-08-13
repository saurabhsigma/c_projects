 #include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
struct termios orig_termios;
// orig_termios: a global variable to store the original terminal attribites. this allows
// restoring terminal settings when the program exits

void die(const char *s) {
  perror(s);
  exit(1);
}
// die()
// Purpose: Handles errors by printing an error message and terminating the program.
// perror(s): Prints the string s followed by a description of the last error that occurred.
// exit(1): Exits the program with a status code of 1, indicating an error.

void disableRawMode() {
  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1)
    die("tcsetattr");
}
// Purpose: Restores the terminal to its original settings when the program exits.
// tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios): Sets the terminal attributes for standard input (STDIN_FILENO) to the values stored in orig_termios. TCSAFLUSH indicates that the change should be made after all pending output is transmitted.
// die("tcsetattr"): If setting the terminal attributes fails, it prints an error message and exits.

void enableRawMode() {
  if (tcgetattr(STDIN_FILENO, &orig_termios) == -1) die("tcgetattr");
  atexit(disableRawMode);
  struct termios raw = orig_termios;
  raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
  raw.c_oflag &= ~(OPOST);
  raw.c_cflag |= (CS8);
  raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
//   raw.c_cc[VMIN] = 0;
//   raw.c_cc[VTIME] = 1;
  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) die("tcsetattr");
}
int main() {
  enableRawMode();
  while (1) {
    char c = '\0';
    if (read(STDIN_FILENO, &c, 1) == -1 && errno != EAGAIN) die("read");
    if (iscntrl(c)) {
      printf("%d\r\n", c);
    } else {
      printf("%d ('%c')\r\n", c, c);
    }
    if (c == 'q') break;
  }
  return 0;
}
// Purpose: Configures the terminal to raw mode where input is processed character by character and input buffering is disabled.

// tcgetattr(STDIN_FILENO, &orig_termios): Gets the current terminal attributes for standard input (STDIN_FILENO) and stores them in orig_termios.

// atexit(disableRawMode): Registers disableRawMode to be called automatically when the program exits. This ensures terminal settings are restored.

// struct termios raw = orig_termios: Creates a copy of the terminal attributes to modify them for raw mode.

// raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON):

// BRKINT: Disable break condition generation.
// ICRNL: Disable mapping carriage return to newline.
// INPCK: Disable input parity checking.
// ISTRIP: Disable stripping of high-bit of input characters.
// IXON: Disable software flow control.
// raw.c_oflag &= ~(OPOST): Disable output processing (raw output mode).

// raw.c_cflag |= (CS8): Set character size to 8 bits.

// raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG):

// ECHO: Disable echoing of input characters.
// ICANON: Disable canonical mode (input is not line-buffered).
// IEXTEN: Disable extended input processing.
// ISIG: Disable interpretation of signal characters (e.g., Ctrl-C).
// // raw.c_cc[VMIN] = 0; and // raw.c_cc[VTIME] = 1;: These lines are commented out. If enabled:

// VMIN: Minimum number of characters to read before returning. 0 means non-blocking mode.
// VTIME: Timeout in deciseconds before read returns if no data is available. 1 means a short timeout.
// tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw): Applies the new terminal attributes to standard input.

// enableRawMode(): Sets the terminal to raw mode.

// while (1): Infinite loop to continuously read input.

// char c = '\0';: Initializes a variable c to store the read character.

// if (read(STDIN_FILENO, &c, 1) == -1 && errno != EAGAIN) die("read");:

// read(STDIN_FILENO, &c, 1): Attempts to read one byte from standard input.
// == -1 && errno != EAGAIN: Checks if read failed with an error other than EAGAIN. If so, die("read") is called to handle the error.
// if (iscntrl(c)): Checks if the character is a control character (non-printable).

// printf("%d\r\n", c);: Prints the ASCII value of the control character.
// else: For printable characters.

// printf("%d ('%c')\r\n", c, c);: Prints the ASCII value and the character itself.
// if (c == 'q') break;: If the character is 'q', exit the loop and end the program.

// return 0;: Return 0 from main, indicating successful execution.

// <ctype.h>: Provides functions to classify and transform characters (e.g., iscntrl, isalpha).

// <errno.h>: Defines macros for reporting errors. errno is a global variable used to report error codes.

// <stdio.h>: Provides functions for input and output, such as printf and perror.

// <stdlib.h>: Includes functions for memory allocation, process control, and conversions. It provides exit for terminating a program.

// <termios.h>: Provides definitions for terminal I/O interfaces, including functions to set terminal attributes.

// <unistd.h>: Provides access to the POSIX operating system API, including system calls like read and tcsetattr.