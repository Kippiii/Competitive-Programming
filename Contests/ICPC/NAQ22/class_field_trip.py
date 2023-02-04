from sys import stdin

ans = ""
for s in stdin:
    ans += s.strip()

print("".join(sorted(ans)))