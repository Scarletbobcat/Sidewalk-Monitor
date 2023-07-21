import leafmap.foliumap as leafmap


# filepath is where the csv file for heatmap is
filepath = "./data.csv"


# creating heatmap settings
m = leafmap.Map(tiles='stamentoner')
m.add_heatmap(
    filepath,
    latitude="Latitude",
    longitude='Longitude',
    value="Rating",
    name="Heat map",
    radius=20,
)


# creates heatmap
m


# # colorbar for our real map
# colors = ['red', 'yellow', 'green']
# m.add_colorbar(colors = colors, vmin = 0, vmax = 5)


# saves heatmap to html in current directory
m.to_html("heatmap.html")