from datetime import datetime
import googlemaps
from pprint import pprint
import json
from dotenv import load_dotenv, find_dotenv
import os
#
#finds .env file and loads it
load_dotenv(find_dotenv())

#saves google key from .env file
gKey = os.environ.get("GOOGLE_KEY")

#creates connection to googlemaps api
gmaps = googlemaps.Client(key = f"{gKey}")

#gets information from api as json
geocode_result = gmaps.geocode('1819 5th Avenue, Youngstown, OH')

#makes json into readable string
results_json = json.dumps(geocode_result)

#loads json
json_geocode = json.loads(results_json)

# This prints the return json into a readable format
# pprint(json_geocode[0])

# Prints the latitude, longitude, and address
pprint(json_geocode[0]['geometry']['location'])
pprint(json_geocode[0]['formatted_address'])


# # get current IP, but it's public IP so not super accurate
# import geocoder

# g = geocoder.ip('me')
# print(g.latlng)