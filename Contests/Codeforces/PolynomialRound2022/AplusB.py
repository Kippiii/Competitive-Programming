t = int(input())
for _ in range(t):
    n = int(input())
    a = input()

    minus = True
    ans = ""
    for i in range(1, n):
        if a[i] == '0':
            ans += '+'
        else:
            ans += '-' if minus else '+'
            minus = not minus
    print(ans)