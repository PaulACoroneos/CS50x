from cs50 import get_int

rows = -1

while (rows > 8 or rows < 1):
    rows = get_int('Please enter a number of rows > 0 and < 8. ')

for row in range(rows):
    # print space
    print(f" "*(rows-row-1), end = '')
    print(f"#"*(row+1))