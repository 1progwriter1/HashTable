with open("../text/clean_text.txt") as f:
    s = [i[0] for i in f.readlines()]

a = set(s)
print(a)
print(s.count('"'))
print(s.count('\''))