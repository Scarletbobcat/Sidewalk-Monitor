import leafmap.foliumap as leafmap


with open("./Ratings/0.csv", "r") as file0, open("./Ratings/1.csv", "r") as file1, open("./Ratings/2.csv", "r") as file2, open("./Ratings/3.csv", "r") as file3, open("./Ratings/4.csv", "r") as file4, open("./Ratings/5.csv", "r") as file5:
        
    heatmap_files = ["./Heatmaps/0.html", "./Heatmaps/1.html", "./Heatmaps/2.html", "./Heatmaps/3.html", "./Heatmaps/4.html", "./Heatmaps/5.html",]
    filepaths = ["./Ratings/0.csv", "./Ratings/1.csv", "./Ratings/2.csv", "./Ratings/3.csv", "./Ratings/4.csv", "./Ratings/5.csv"]
        
    for i in range(6):
        # filepath is where the csv file for heatmap is
        filepath = filepaths[i]

        # creating basic map
        m = leafmap.Map()

        # adding heatmap layer with settings
        m.add_heatmap(
            filepath,
            latitude="Latitude",
            longitude='Longitude',
            value="Rating",
            name="Heat map",
            radius=15,
        )

        # creates heatmap
        m

        # saves heatmap to html in current directory
        m.to_html(heatmap_files[i])