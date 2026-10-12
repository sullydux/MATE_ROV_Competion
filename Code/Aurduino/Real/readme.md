# Float and ROV code

## Float

## Todo for 10/25
Make ESP32 serve a WiFi and webpage. Webpage has three true buttons: Start Mission, Reload Chart, and Reset Data. There is a temperary button that inserts false data into array. There is also a 16x6 chart that reloads data on button click. Make the start button go to empty func, reload will make chart reload with new data, and reset will clear and remake array. 

## Chart
16 rows for test 1-16 and 6 collums for data. Stores as 16 structs in an array.

### Data to be displayed
- Company # - String
- IRL Time (UTC)
- Pressure (Paskals) - Float
- Depth (M or CM) - Float
- Light (irradience or lux or anything) - Float
- Temp (Celcius) - Float

At -4M, -3.5M, -3M, -2.5M, -2M, -1.5M, -1M, -0.5M, 0M collect data once. -2M on down collect 7 times.