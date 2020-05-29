#include <cs50.h>
#include <stdio.h>

int getHeight()
{
  return get_int("Enter a height between 1 and 8: \n");
}

int main(void)
{
  int height = -1;
  //loop until valid height
  while (height < 1 || height > 8)
  {
    height = getHeight();
  }

  //loop through every row
  for (int i = 1; i <= height; i++)
  {
    //left side of pyramid
    for (int j = 1; j <= height; j++)
    {
      char poundOrSpace = (j > height - i) ? '#' : ' ';
      printf("%c", poundOrSpace);
    }

    //gap
    printf("  ");

    //right side of pyramid
    for (int j = 1; j <= height; j++)
    {
      if (j <= i)
        printf("#");
    }

    printf("\n");
  }
}