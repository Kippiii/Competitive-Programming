t = int(input())
for _ in range(t):
    l, r, x = map(int, input().split())
    a, b = map(int, input().split())

    if a == b:
        print(0)
    elif b < l or b > r or (a + x > r and a - x < l):
        print(-1)
    elif abs(a-b) >= x:
        print(1)
    elif (abs(a - r) >= x and abs(b - r) >= x) or (abs(a - l) >= x and abs(b - l) >= x):
        print(2)
    elif (b > a and abs(a - r) >= x and abs(l - b) >= x) or (b < a and abs(a - l) >= x and abs(r - b) >= x):
        print(3)
    else:
        print(-1)