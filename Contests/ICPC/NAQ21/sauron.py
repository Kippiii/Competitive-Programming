s = input().strip()

before = 0
after = 0
hit_eye = False
for c in s:
    if c == '|':
        if hit_eye:
            after += 1
        else:
            before += 1
    if c == '(':
        hit_eye = True

if before == after:
    print("correct")
else:
    print("fix")
