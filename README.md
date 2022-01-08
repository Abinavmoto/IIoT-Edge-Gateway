
#  IIoT-Edge-Gateway

A  IIoT Gateway are wirelessly connected to the global Internet, collecting data from all aspects of a process and sharing it with a central server. This data enables analysis and action that has been heretofore unseen, resulting in increased efficiency and productivity


## Use Cases

 - Predictive maintenance/analytics
 - Asset tracking
 - Supply chain management and Much more
## Features

- Configurable Gateway Parameters
- Easy to deploy and integrate
- Log data to the cloud real-time and for data processing, trending and statistical analysis
- Secured data transfer


## LIB Stack

**Client:** Paho Mqtt C Client, json-c, GTest, libconfig , CMake

**Server:** Mosquitto Server -[mqtt.eclipseprojects.io]


## Environment 

**OS:** Ubuntu 20.04 LTS

**IDE:** Visual Studio


## Library Installation 

**Paho Mqtt C:** [Link to Paho C Client Installation](https://github.com/eclipse/paho.mqtt.c)

**Json-c:** [Link to Json Library](https://github.com/json-c/json-c)

**Config:** [Link to Config Library](https://hyperrealm.github.io/libconfig/libconfig_manual.html)

**GTest:**

Install GTest 

```bash
   sudo apt-get install libgtest-dev
   cd /usr/src/gtest
   sudo cmake CMakeLists.txt
   sudo make
 
   # copy or symlink libgtest.a and libgtest_main.a to your /usr/lib folder
   sudo cp *.a /usr/lib
```

**CMake:**

Install CMake 

```bash
   sudo apt-get install cmake
```
    
## Documentation

[Documentation](https://linktodocumentation)


## Run Locally

- Install library dependencies mentioned above before getting started!! 

- Clone the project

```bash
  git clone https://github.com/Abinavmoto/IIoT-Edge-Gateway.git
```

- Go to the project directory and create build folder

```bash
  cd IIoT-Edge-Gateway
  sudo mkdir build
  cd build/
```

- Run CMake and make 

```bash
   sudo cmake ..
   sudo make
```

## Running Tests

To run tests, run the following command in the build/bin folder

```bash
   ./runTest
```


## Deployment

To deploy this project run ,run the following command in the build/bin folder

```bash
   # Arguments - path to conf file
   ./MQTTPUB_CMAKE ../../common/config/conf.cfg
```


## Demo

![ScreenShot](/Screenshots/IIoT_Gateway_console.png)

![ScreenShot](/Screenshots/Log_File.PNG)

## Optimizations

- Add ACK Mechanism from SUB client for adressing data loss 



## Roadmap

- Add SSL Certifications
- Incorporate Subscriber Actions
- Create a Docker image for ease of deployment



## 🚀 About Me

- [LinkedIN](https://www.linkedin.com/in/abinavramesh/)

- [GitHub](https://github.com/Abinavmoto)
