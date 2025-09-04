obj = open("blahaj.obj", 'r')
buf = ""
for line in obj.readlines():
    if(line[0] == 'v'):
        buf += line
    if(line[0] == 'f'):
        frm = [elem.split("//")[0] for elem in line.split()[1:]]
        buf += f"f {' '.join(frm)}\n"
print(buf)