file = input("which file to fix:")
with open(file, "r") as f_in, open(file, "w") as f_out:
    for line in f_in:
        if not line.startswith("f "):
            f_out.write(line)
            continue
        parts = line.strip().split()[1:]
        if len(parts) != 3:
            for i in range(1, len(parts) - 1):
                tri = ["f", parts[0], parts[i], parts[i + 1]]
                f_out.write(" ".join(tri) + "\n")
            continue
        f_out.write("f " + " ".join(parts) + "\n")
