with open("Results/time_rdtsc/crc32.txt") as f:
    s = [i for i in f.readlines() if "load table: " in i]

s = [int(i.replace("load table: ", "")) for i in s]
print(sum(s) / len(s))

with open("Results/time_rdtsc/crc32_fast.txt") as f:
    s = [i for i in f.readlines() if "load table: " in i]

s = [int(i.replace("load table: ", "")) for i in s]
print(sum(s) / len(s))
