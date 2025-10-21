FILE = open("lpb/blahaj.obj", "r")
FIXED = open("lpb/fixed.obj", "w")
lines = FILE.readlines()
nonfaces = [line for line in lines if line[0] != "f"]
faces = [line.split()[1:] for line in lines if line[0] == "f"]
badfaces = [face for face in faces if len(face) > 3]
splitfaces = [[[badface[0], badface[i], badface[i + 1]] for i in range(1, len(badface) - 1)] for badface in badfaces]
splitfaces = [["f"] + face for group in splitfaces for face in group]
splitfaces = [" ".join(splitface) + "\n" for splitface in splitfaces]
print(splitfaces)
FIXED.writelines(nonfaces)
FIXED.writelines(splitfaces)