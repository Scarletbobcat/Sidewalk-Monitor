import leafmap.foliumap as leafmap

# filepath is where the csv file for heatmap is
filepath = "./data.CSV"

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
m.to_html("sidewalk_conditions.html")