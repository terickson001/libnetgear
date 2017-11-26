# libnetgear

A simple library to interface with Netgear routers' SOAP API
Inspired by [pynetgear by balloob](https://github.com/balloob/pynetgear)

## Installation
Currently, the install process isn't automated (e.g.: `sudo make install`)

The current method is to:
- compile libnetgear.so with `make`
- copy the lib to your systems library install directory  
&nbsp;&nbsp;&nbsp;&nbsp;e.g.: 
```bash
cp ./lib/libnetgear.so /usr/lib/libnetgear.so
```
- and finally move the headers to your systems include install directory  
&nbsp;&nbsp;&nbsp;&nbsp;e.g.: 
```bash
mkdir /usr/include/netgear
cp ./include/* /usr/include/netgear/
```

## Usage

For right now, here's an example program:
```c++
#include <netgear/router.h>
#include <netgear/device.h>
#include <netgear/trafficmeter.h>

#include <iostream>
#include <vector>

int main(int argc, char** argv)
{
    // password/username are the credentials for the router; username defaults to "admin"
    // host is the url of your router's web server         ; host defaults to "routerlogin.net"
    // port is the port of your router's SOAP interface    ; port defaults to 5000 (Some router models may require this to be 80)
    Router router(password, username, host, port);
    
    // Login in to the router
    // returns http response code
    int status = router.login();

    // Gets a list of devices connected to the router and stores it in devices
    std::vector<Device> devices;
    status = router.get_attached_devices(&devices);
    
    for (int i = 0; i < devices.size(); i++)
        std::cout << devices[i].get_name() << ": " << devices[i].get_mac() << std::endl;

    // Similar to get_attached_devices, but returns more detailed info about each device
    // Extra info includes: upload/download speed, SSID, DeviceType, QOS Priority, ...
    std::vector<Device> devices2;
    status = router.get_attached_device2(&devices2);

    // Gets the traffic meter data from the router
    TrafficMeter tm;
    status = router.get_traffic_meter(&tm)
    
    std::cout << tm << std::endl;

    // This series of commands allows you to block or allow a device by MAC address
    router.start_config();
    router.set_block_device(devices[0].get_mac(), true);
    router.end_config();

    // Note that these commands also return status codes, we're simply not using them
}
```
