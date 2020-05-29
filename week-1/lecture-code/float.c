#include <cs50.h>
#include <stdio.h>

int main(void)
{
  float price = get_float("Whats the price?\n");
  double salesTax = 1.0825;
  printf("Your total is %.2f.\n", price * salesTax);
}
