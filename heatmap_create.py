import leafmap.foliumap as leafmap


# filepath is where the csv file for heatmap is
filepath = "./data.CSV"


# creating heatmap settings
m = leafmap.Map()
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