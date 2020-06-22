from cs50 import get_float
import math

change = -1
count = 0

while change < 0:
    change = get_float('Change owed: ')

change = change*100
# this should really be a function. TODO
quarterCnt = math.floor(change / 25)
change -= quarterCnt * 25
count += quarterCnt

dimeCnt = math.floor(change / 10)
change -= dimeCnt * 10
count += dimeCnt

nickelCnt = math.floor(change / 5)
change -= nickelCnt * 5
count += nickelCnt

pennyCnt = math.floor(change / 1)
change -= pennyCnt * 1
count += pennyCnt

print(f"{count}")


