#include <cs50.h>
#include <stdio.h>

void whatCCType(long creditNum, int length)
{
  int oddSum = 0, evenSum = 0, idx = 0;
  long creditArray[length];

  while (creditNum != 0)
  {
    creditArray[idx] = creditNum % 10;
    creditNum /= 10;
    idx++;
  }

  for (int i = 1; i < length; i += 2)
  {
    int product = creditArray[i] * 2;
    if (product > 9)
    {
      while (product != 0)
      {
        oddSum += product % 10;
        product /= 10;
      }
    }
    else
    {
      oddSum += product;
    }
  }

  for (int i = 0; i < length; i += 2)
  {
    evenSum += creditArray[i];
  }

  if ((oddSum + evenSum) % 10 != 0)
  {
    printf("INVALID\n");
  }
  else if (length == 15)
  {
    if (creditArray[length - 1] == 3 && (creditArray[length - 2] == 4 || creditArray[length - 2] == 7))
    {
      printf("AMEX\n");
    }
    else
    {
      printf("INVALID\n");
    }
  }
  else if (length == 16)
  {
    if (creditArray[length - 1] == 5 && creditArray[length - 2] < 6)
    {
      printf("MASTERCARD\n");
    }
    else if (creditArray[length - 1] != 5)
    {
      printf("VISA\n");
    }
    else
    {
      printf("INVALID\n");
    }
  }
  else if (length == 13)
  {
    printf("VISA\n");
  }
  else
  {
    printf("INVALID\n");
  }
}

int main(void)
{
  long ccNumber = get_long("Number: ");

  //calculate length of digits using modulus
  int length = 0;
  long ccCopy = ccNumber;

  while (ccCopy != 0)
  {
    ccCopy /= 10;
    length++;
  }

  whatCCType(ccNumber, length);
}