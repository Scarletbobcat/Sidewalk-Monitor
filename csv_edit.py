import csv

input_file = open("./test.csv")

csvreader = csv.reader(input_file)

headers = []

headers = next(csvreader)

print(headers)