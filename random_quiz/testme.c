#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

const int EXT_ASCII_LIMIT = 256;

char inputChar()
{
  // TODO: rewrite this function
  // generate random chars
  char rchar = (char)(rand() % EXT_ASCII_LIMIT);
  return rchar;
}

char *inputString()
{
  // TODO: rewrite this function
  // limit strings to 5 in length, add newline
  int stringLen = 6;
  static char inpstr[6];

  // manually set the string on 5% of the inputs
  int fixedPercentage = 5; 
  if ((rand() % 100) <= fixedPercentage)
  {
    strcpy(inpstr, "reset\0");
  }
  // populate string randomly
  else
  {
    for (int i = 0; i < stringLen; i++)
    {
      inpstr[i] = inputChar(); 
    }
  }
  return inpstr;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0)
      state = 1;
    if (c == '(' && state == 1)
      state = 2;
    if (c == '{' && state == 2)
      state = 3;
    if (c == ' ' && state == 3)
      state = 4;
    if (c == 'a' && state == 4)
      state = 5;
    if (c == 'x' && state == 5)
      state = 6;
    if (c == '}' && state == 6)
      state = 7;
    if (c == ')' && state == 7)
      state = 8;
    if (c == ']' && state == 8)
      state = 9;
    if (s[0] == 'r' && s[1] == 'e' && s[2] == 's' && s[3] == 'e' && s[4] == 't' && s[5] == '\0' && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}

int main(int argc, char *argv[])
{
  srand(time(NULL));
  testme();
  return 0;
}
