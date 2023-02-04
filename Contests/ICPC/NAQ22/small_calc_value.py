x, y, z = map(int, input().split())

def do_op(i, j, op):
    if op == '+':
        return i+j
    if op == '-':
        return i-j
    if op == '*':
        return i*j
    if op == '/':
        if j == 0 or i % j != 0:
            raise ValueError()
        return i / j

ops = ['+', '-', '*', '/']
ans = x+y+z
for op1 in ops:
    for op2 in ops:
        try:
            val = do_op(do_op(x, y, op1), z, op2)
        except ValueError:
            continue
        if val >= 0:
            ans = min(ans, val)

print(int(ans))