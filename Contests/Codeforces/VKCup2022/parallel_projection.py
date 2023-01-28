t = int(input())
for _ in range(t):
    w, d, h = map(int, input().split())
    a, b, f, g = map(int, input().split())

    v1 = a + h + f + abs(g - b)
    v2 = (w - a) + h + (w - f) + abs(g - b)
    v3 = b + h + g + abs(f - a)
    v4 = (d - b) + h + (d - g) + abs(f - a)

    ans = min(v1, v2, v3, v4)
    print(ans)