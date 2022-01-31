n = input()
while n[0] == '0':
    n = n[1:]
if n == "1":
    print("0 2")
    exit()
digits = [False for _ in range(10)]
for i in n:
    digits[int(i)] = True

def find_upper(num):
    sig_digit = int(num[0])
    new_digit = -1
    for i in range(sig_digit, 10):
        if not digits[i]:
            new_digit = i
            break
    if new_digit == -1:
        return find_upper("1" + ("0" * len(num)))
    lowest = -1
    for i in range(10):
        if not digits[i]:
            lowest = i
            break
    return str(new_digit) + (str(lowest) * (len(num) - 1))

def find_lower(num):
    sig_digit = int(num[0])
    new_digit = -1
    for i in range(sig_digit, 0, -1):
        if not digits[i]:
            new_digit = i
            break
    if new_digit == -1:
        if len(num) == 1:
            return "-1"
        return find_lower("9" * (len(num) - 1))
    highest = -1
    for i in range(9, -1, -1):
        if not digits[i]:
            highest = i
            break
    return str(new_digit) + (str(highest) * (len(num) - 1))

possible = False
for i in range(1, len(digits)):
    b = digits[i]
    if not b:
        possible = True
if not possible:
    if not digits[0]:
        print("0")
    else:
        print("Impossible")
else:
    u = int(find_upper(n))
    l = int(find_lower(n))
    n = int(n)

    if l != -1 and n - l == u - n:
        print(f'{l} {u}')
    elif l != -1 and n - l < u - n:
        print(l)
    else:
        print(u)
