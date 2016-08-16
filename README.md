# SoundToImagePortable
C++ version of my program that converts an audio file (mp3, wav) into an image. Uses SFML as it is cross-platform.
## Downloading SFML
Please see the sfml site for instructions on how to download and use the library for your operating system.
http://www.sfml-dev.org/index.php
## Installation
Run the command `make main`, which will create an executable main file. Needs the library SFML to be installed in the same folder.
Next, add the libs to the `LD_LIBRARY_PATH` name using the `export` command, as shown below:
```
export LD_LIBRARY_PATH=/home/sid/workspace/SoundToImage/SFML-2.3.2/lib/:$LD_LIBRARY_PATH
```
You will need to use the full path to make it work. Obtain the full path by using the `pwd` command.
## Usage
```
SoundToImagePortable [mode] [input_file] [output_file]
Mode Options:
0-Audio to Image
1-Image to Audio
```
