FILE = open("blahaj.obj", "r")
lines = FILE.readlines()
vertices = [[float(num) for num in line.split()[1:]]for line in lines if line[0] == "v"]
xsum = sum([vec[0] for vec in vertices])
ysum = sum([vec[1] for vec in vertices])
zsum = sum([vec[2] for vec in vertices])
faces = [line.split()[1:] for line in lines if line[0] == "f"]
badfaces = [face for face in faces if len(face) > 3]
splitfaces = [[[badface[0], badface[i], badface[i + 1]] for i in range(1, len(badface) - 1)] for badface in badfaces]