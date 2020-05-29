#include <cs50.h>
#include <stdio.h>

int main(void)
{
  int age = get_int("What's your age?\n");
  int days = age * 365;
  printf("You are at least %i days old\n", days);
}
