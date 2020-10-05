# Air-Hockey
The aim of this project is the analysis of an air hockey game from images. This project is composed of three main parts. First the sequence of images is treated in Labview to produce a binary file. This binary file is then treated by a C++ code which detects the position of the two pucks and returns a text file (pos.txt) to Labview for each image. Finally, Labview calls a Matlab script which analyses the trajectories of the two pucks and produces a summary of the game (number of impacts, collisions...).
![Screenshot](https://github.com/nicolasbdls/Air-Hockey/blob/main/final%20summary.JPG)

A more  in depth description can be found here.
