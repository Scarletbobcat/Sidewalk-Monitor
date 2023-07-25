import leafmap.foliumap as leafmap


# storing filepaths for data and heatmaps
heatmap_files = ["./Heatmaps/0.html", "./Heatmaps/1.html", "./Heatmaps/2.html", "./Heatmaps/3.html", "./Heatmaps/4.html", "./Heatmaps/5.html",]
filepaths = ["./Ratings/0.csv", "./Ratings/1.csv", "./Ratings/2.csv", "./Ratings/3.csv", "./Ratings/4.csv", "./Ratings/5.csv"]
    
# creates a heat map for each rating
for i in range(6):
    # filepath is where the csv file for heatmap is
    filepath = filepaths[i]

    # creating basic map
    m = leafmap.Map()
    m.add_heatmap(
        filepath,
        latitude="Latitude",
        longitude='Longitude',
        value="Rating",
        name="Heat map",
        radius=30,
    )

    # creates heatmap
    m

    # saves heatmap to html in Heatmaps directory
    m.to_html(heatmap_files[i])
