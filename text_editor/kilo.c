// #include <stdio.h>

// int main(void) {
//     printf("hello world");
//     return 0;

// }


// chaper 1
// #include <stdio.h>

// int main() {
//     // printf("hello world");
//     return 0;
// }

// chapter 2


// #include <unistd.h>
// #include <termios.h>
// #include <stdlib.h>


// // disabling raw mode at exit
// struct termios orig_termios;

// void disableRawMode() {
//     tcsetattr(STDERR_FILENO, TCSAFLUSH, &orig_termios);
// }


// // enabling raw mode
// void enableRawMode(){
//     // struct termios raw;
//     tcgetattr(STDIN_FILENO, &orig_termios);
//     atexit(disableRawMode);
//     // atexit() comes from <stdlib.h>.

//     struct termios raw = orig_termios;


//     // tcgetattr(STDIN_FILENO, &raw);

//     raw.c_lflag &= ~(ECHO | ICANON);

//     tcsetattr(STDERR_FILENO, TCSAFLUSH, &raw);
//     // struct termios, tcgetattr(), tcsetattr(), ECHO, and TCSAFLUSH all come from <termios.h>.
// }

// int main(void) {
//     enableRawMode();
//     char c;
//     while (read(STDIN_FILENO, &c, 1) == 1 && c != 'q');
//     return 0;
// }


// Display Kepresses

// #include <ctype.h>
// #include <stdio.h>
// #include <unistd.h>
// #include <errno.h>
// #include <termios.h>
// #include <stdlib.h>

// struct termios orig_termios;

// void die(const char *s) {
//   perror(s);
//   exit(1);
// }


// void disableRawMode() {
//   if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1)
//     die("tcsetattr");
// }


// void enableRawMode(){
   
//     if (tcgetattr(STDIN_FILENO, &orig_termios) == -1) die("tcgetattr");   
//     atexit(disableRawMode);

//     struct termios raw = orig_termios;

//     raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
//     raw.c_oflag &= ~(OPOST);
//     raw.c_cflag |= (CS8);
//     raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
//     //for timeout of the input
//     raw.c_cc[VMIN] = 0;
//     raw.c_cc[VTIME] = 1;


//     if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) die("tcsetattr");
// }


// int main(void) {
//     enableRawMode();
    
//     while (1) {
//     char c = '\0';
//     if (read(STDIN_FILENO, &c, 1) == -1 && errno != EAGAIN) die("read");
//     if (iscntrl(c)) {
//       printf("%d\r\n", c);
//     } else {
//       printf("%d ('%c')\r\n", c, c);
//     }
//     if (c == 'a') break;
//     }
//     return 0;
// }


// final code
 #include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
struct termios orig_termios;
void die(const char *s) {
  perror(s);
  exit(1);
}
void disableRawMode() {
  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1)
    die("tcsetattr");
}
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
