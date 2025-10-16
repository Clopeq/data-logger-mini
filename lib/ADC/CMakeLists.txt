 cmake_minimum_required(VERSION 3.28)

 project(ADC)

 include_directories(Config/lib)
 include_directories(lib)
 include_directories(../json)

 add_library(${PROJECT_NAME} Config/src/DEV_Config.cpp Config/src/dev_hardware_SPI.cpp Config/src/RPI_sysfs_gpio.cpp Config/src/sysfs_gpio.cpp Config/src/sysfs_software_spi.cpp src/ADS1263_wrapper.cpp src/ADS1263.cpp)
