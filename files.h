    files = glob.glob("*.c")
    for file in files:
        print(file, end= " ")
        print(file_len(file))
        totalC += file_len(file)
    print("tot .c", end = " ")
    print(totalC)