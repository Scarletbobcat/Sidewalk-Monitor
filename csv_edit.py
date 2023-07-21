import csv

#open input and output files
input_file = open("./test.csv", "r")
output_file = open("./data.csv", "w")

#declaring object to read input file
csvreader = csv.reader(input_file)

#put headers from input file into array
headers = []
headers = next(csvreader)

output_file.write("Latitude,Longitude,Rating\n")

# #writes 5 points in between 2 points to output file
for row in csvreader:
    data = []
    data = row
    lat1 = float(data[0])
    long1 = float(data[1])
    lat2 = float(data[2])
    long2 = float(data[3])
    lat_distance = lat2 - lat1
    long_distance = long2 - long1
    lat_interval = lat_distance / 5.000000
    long_interval = long_distance / 5.000000
    for i in range(5):
        new_lat = lat1 + (i * lat_interval)
        new_long = long1 + (i * long_interval)
        new_rating = 5 - int(data[4])
        output_file.write(str(new_lat) + "," + str(new_long) + "," + str(new_rating) + "\n")

#closing files
output_file.close()
input_file.close()