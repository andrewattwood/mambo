import subprocess
import re
HOME = "/Users/andrewattwood"
CHERI = HOME + "/cheri/output/morello-sdk/bin/"
CLANG = CHERI + "/aarch64-unknown-freebsd-clang "
FLAGS = "-c -march=morello+c64 -mabi=purecap "
OBJDUMP = CHERI + "/llvm-objdump "
TMP = "/tmp/"
OUTPUT = TMP + "/out.o"
SOURCE = TMP + "/diss.S"
INPUT = "diss.txt"
DUMPOUT = TMP + "/obdumpout"
DUMPOUTFORMAT = TMP + "/dumpoutformat"
fin = open(INPUT, "r")
fout = open(SOURCE, "w")
firstline = 0
linenumber = 0
for line in fin:
  line = line.split()  
  if firstline == 0:
    firstline = 1;
    linenumber = int(line[0],16)
  for x in line[2:]:
    fout.write(".inst " + x + "\n")
fin.close()
fout.close()

proc = subprocess.check_output(CLANG + FLAGS + SOURCE + " -o " + OUTPUT,shell=True)
proc = subprocess.check_output(OBJDUMP + "-d " + OUTPUT + " > " + DUMPOUT,shell=True)


dumpoutformat = open(DUMPOUTFORMAT,"w")
dumpout = open(DUMPOUT, "r")
count = 0
offset = linenumber
for line in dumpout:
  if count > 5:
    line = re.split("\$c\.0\+",line)
    print line
    if len(line) > 1:
      outline = hex(linenumber) + " " + line[0].rstrip() + hex(offset + int(line[1][:-2],16))
    else:
      outline = hex(linenumber) + " " + line[0]
    print(outline.rstrip())
    dumpoutformat.write(outline)
    linenumber = linenumber + 1
  count = count + 1