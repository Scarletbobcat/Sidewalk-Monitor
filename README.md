# Sidewalk-Monitor #
creates a heatmap based on the rating of sidewalk that we give
<hr>

# Parts Used
The parts that were used to create a gps tracker include an Arduino Uno R3, Ublox Neo-7m gps module, microSD card module, microSD card, breadboard, and Arduino jumper wires

# How To Use
Once all parts are correctly wired together, you will need to: 
1. Import code into Arduino
2. Wait outside until gps module gets signal (can take a few minutes)
3. Follow  instructions given through Serial Monitor on ArduinoIDE
    - enter to update GPS location
    - enter x to record beginning point
    - enter v to record end point and rating of sidewalk
    - enter e to exit program
4. Once finished, **_be sure to close the file by inputting "e" to the arduino through the Serial Monitor of the ArduinoIDE_**
5. Plug microSD into laptop or computer and drag file into same directory as the python scripts
6. Run "csv_edit.py"
7. Run "heatmap_create.py"
8. Navigate to directory titled "Heatmaps" and open the heatmap of the rating you would like to see