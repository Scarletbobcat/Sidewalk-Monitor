import csv
from haversine import haversine, Unit

# emulates the functionality of a switch
def switch(lat, long, rating):
    if rating == 1:
        file1.write(str(lat) + "," + str(long) + "," + str(rating) + "\n")
    elif rating == 2:
        file2.write(str(lat) + "," + str(long) + "," + str(rating) + "\n")
    elif rating == 3:
        file3.write(str(lat) + "," + str(long) + "," + str(rating) + "\n")
    elif rating == 4:
        file4.write(str(lat) + "," + str(long) + "," + str(rating) + "\n")
    elif rating == 5:
        file5.write(str(lat) + "," + str(long) + "," + str(rating) + "\n")

# opening all files
with open("./DATA.CSV", "r") as input_file, open("./Ratings/1.csv", "w") as file1, open("./Ratings/2.csv", "w") as file2, open("./Ratings/3.csv", "w") as file3, open("./Ratings/4.csv", "w") as file4,  open("./Ratings/5.csv", "w") as file5:
    

    # declaring object to read input file
    csvreader = csv.reader(input_file)


    # put headers from input file into array
    headers = []
    headers = next(csvreader)


    # writing headers to rating csv's
    file1.write("Latitude,Longitude,Rating\n")
    file2.write("Latitude,Longitude,Rating\n")
    file3.write("Latitude,Longitude,Rating\n")
    file4.write("Latitude,Longitude,Rating\n")
    file5.write("Latitude,Longitude,Rating\n")


    # writes points in between 2 coordinates to each output file
    for row in csvreader:
        # reading in data
        data = []
        data = row
        if (len(data[0]) != 0):
                
            lat1 = float(data[0])
            long1 = float(data[1])
            lat2 = float(data[2])
            long2 = float(data[3])

            if ((lat1 < 42 and lat1 > 41) and (lat2 < 42 and lat2 > 41) and (long1 < -80 and long1 > -82) and (long2 < -80 and long2 > -82)):
                # usese haversine formula to find distance between two latitude and longitude points in feet
                begin_point = (lat1,long1)
                end_point = (lat2,long2)
                distance_between = haversine(begin_point, end_point, unit = Unit.FEET)

                # creates the number of points in between these points depending on the distance
                num_points_between = distance_between / 25
                
                # if the points are different at all
                if (lat1 != lat2 or long1 != long2):

                    # finding distance between latitude and longitude of points
                    lat_distance = lat2 - lat1
                    long_distance = long2 - long1
                
                    # finding interval for points in between
                    lat_interval = lat_distance / num_points_between
                    long_interval = long_distance / num_points_between
 
                    # writes each new point between the 2 by adding interval each time
                    for i in range(int(num_points_between)):
                        new_lat = lat1 + (i * lat_interval)
                        new_long = long1 + (i * long_interval)
                        switch(new_lat, new_long, int(data[4]))

                else:
                    switch(lat1, long1, int(data[4]))


    # closing files
    file1.close()
    file2.close()
    file3.close()
    file4.close()
    file5.close()
    input_file.close()