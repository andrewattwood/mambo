f = open("diss.txt", "r")
fout = open("disstemp.asm", "w")
for line in f:
  line = line.split()
  for x in line[1:]:
    print x
    fout.write(x + "\n")
f.close()
fout.close()