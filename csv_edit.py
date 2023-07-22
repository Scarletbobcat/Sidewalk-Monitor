import csv

# open input and output files
input_file = open("./asdf.csv", "r")
output_file = open("./data.csv", "w")

# declaring object to read input file
csvreader = csv.reader(input_file)

# put headers from input file into array
headers = []
headers = next(csvreader)

output_file.write("Latitude,Longitude,Rating\n")


# writes points in between 2 coordinates to output file
for row in csvreader:
    # reading in data
    data = []
    data = row
    lat1 = float(data[0])
    long1 = float(data[1])
    lat2 = float(data[2])
    long2 = float(data[3])

    num_points_between = (float(6) - float(data[4])) ** 2
    
    if (lat1 != lat2 or long1 != long2):
        # finding distance
        lat_distance = lat2 - lat1
        long_distance = long2 - long1
    
        # finding what interval for points in between should be
        lat_interval = lat_distance / num_points_between
        long_interval = long_distance / num_points_between

        # writes each new point between the 2 by adding interval each time
        for i in range(int(num_points_between)):
            new_lat = lat1 + (i * lat_interval)
            new_long = long1 + (i * long_interval)
            new_rating = 5 - int(data[4])
            output_file.write(str(new_lat) + "," + str(new_long) + "," + str(new_rating) + "\n")

    # writes one point if beginning and end points are the same
    else:
        new_rating = 5 - int(data[4])
        output_file.write(str(lat1) + "," + str(long1) + "," + str(new_rating) + "\n")

# closing files
output_file.close()
input_file.close()