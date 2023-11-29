# sl_map_generator
A beta of the map generator for the school 42 so_long project

## Install
```bash
git clone git@github.com:NyTekCFW/sl_map_generator.git
```
## Build
```bash
make or make re
```
## Use
```bash
./sl_map_generator (map name (you can specify .ber or not)) (width) (height) (number of collectibles 0 = automatic) (number of walls in map 0 = automatic)
./sl_map_generator massive_coins 140 139 1500 1
./sl_map_generator random.ber 140 139 0 0
```
## Warning
The max that u can generate is a map of 210x209 or 209x210.
The map need to be a rectangle.
The generator test if the generated map can be playable,
if the map is not playable, a new map will be made.
After 30 000 try if the map is still not playable the program will stop.
