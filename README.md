# M5-RoverC

## Overview

### SKU:K036-B

Contains the driver of the M5Stack RoverC series to realize the movement of the RoverC trolley and the control of the steering gear.

## Related Link

[Document & Datasheet - RoverC-Pro](https://docs.m5stack.com/en/hat/hat_roverc_pro)

## ESP-IDF Usage

This repository can be used as an ESP-IDF component.

1. Add the repository to your project `components/` directory.
2. Include the header in your app:

```cpp
#include "M5_RoverC.h"
```

3. Initialize over native ESP-IDF I2C:

```cpp
M5_RoverC rover;
rover.begin(I2C_NUM_0, GPIO_NUM_0, GPIO_NUM_26, ROVER_ADDRESS, 400000, true);
rover.setSpeed(50, 0, 0);
```

## License

[M5_RoverC - MIT](LICENSE)
