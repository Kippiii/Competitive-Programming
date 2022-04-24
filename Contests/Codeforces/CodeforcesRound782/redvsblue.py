from math import ceil

t = int(input())
for _ in range(t):
    n, r, b = map(int, input().split())
    row = n // (b+1)
    ans = ''
    while row * b > r:
        ans += 'R'
        r -= 1
        ans += 'B'
        b -= 1
    while r > 0:
        v = min(r, row)
        ans += 'R'*v
        r -= v
        if b > 0:
            ans += 'B'
            b -= 1
    ans += 'B'*b
    print(ans)
