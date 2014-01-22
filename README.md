Arctic-2014-thermal
===================
For the Eagle files, they are made with Eagle 6.5 FREE. The parts can all be purchased 
from sparkfun except the MLX90614-ACC.

https://www.sparkfun.com/wish_lists/73940

IR Sensor: 35deg FOV
http://www.futureelectronics.com/en/technologies/semiconductors/analog/sensors/temperature/Pages/7012690-MLX90614ESF-ACC-000-TU.aspx?IM=0

IR Sensor: 10deg FOV
http://www.futureelectronics.com/en/technologies/semiconductors/analog/sensors/temperature/Pages/4099248-MLX90614ESF-ACF-000-TU.aspx?IM=0

The v2.0 files would not upload to OSHpark.com correctly (kept showing an old version) so I copied them to another directory, renamed them, uploaded, and it all worked fine. Not sure if it was a caching problem on their end, or something funny on mine.

The code that runs on Whistler is in the code directoy. There is a version that does not give data collection options that is antequaited, please avoid it. The fast version also turns out not to be fast, it was using the digitalWriteFast library to access the pins vai port comands directly, which should have increased the read/write speed by a factor of 10. The code did not show imporvement (mostly becuase the slowness was a factor of the serial port speed more than anything else). Instead of running the different library (which is mostly stable and seems fine) the serial speed was changed from 9600 baud to 57600 baud. This took the loop time from ~20ms to ~3ms. As a happy medium an interval of 5ms was added to ensure a constant data collection rate. This rate will vary between 5ms and 6ms, with an average around 5.1ms (the 6ms is due to the occasional loop that takes slightly longer to run.) It might be possible to get the delay down below the 3ms range with the digitalWriteFast library, but there is no real need for that at this point.  
