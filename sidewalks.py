import leafmap.foliumap as leafmap
filepath = "https://raw.githubusercontent.com/opengeos/leafmap/master/examples/data/us_cities.csv"

m = leafmap.Map(tiles='stamentoner')
m.add_heatmap(
    filepath,
    latitude="latitude",
    longitude='longitude',
    value="pop_max",
    name="Heat map",
    radius=20,
)
m

# # colorbar for our real map
# colors = ['red', 'yellow', 'green']
# m.add_colorbar(colors = colors, vmin = 0, vmax = 5)

m.to_html("heatmap.html")