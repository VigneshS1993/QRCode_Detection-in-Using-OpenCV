# CamController application

This is a DAEbot CamController main aplication. It performs:

* CAN communication
* CamController hardware configuration
* QR code detection
* Obstacle detection

## Dependencies

This application depends on third-party libraries:

* _libfreenect_
* _OpenCV_
* _ZBar_

In order to be able to build the application,
target sysroot must contain this libraries and their includes.

[Publisher]() library is yet another dependency.
This is a DAEbot library that enables automatic
publishing activity. To enable build, this library
and its includes should be copied into the sources directory
under _publisher/lib_ and _publisher/include_
or into sysroot include and library directories.

Finally, the application uses DAEbot-PD for CAN communication,
thus the path to DAEbot-PD sources should be specified in _CMakeLists.txt_
using DAEBOT_PD_SOURCE variable:

```cmake
set(DAEBOT_PD_SOURCE /path/to/DAEbot-PD)
```

## Build

Current version of the application was build on the node
itself. However, cross compilation is also an option,
though no cross tools are yet available in the project.

To build the project copy the sources onto the node,
and build it using _ssh_ and _cmake_:

```shell
ssh pi@172.22.166.136
cd path/to/cam-controller
mkdir build && cd build
cmake ..
```
> Note that _DAEbot-PD_ sources must also be copied
> and an appropriate path should be given in `DAEBOT_PD_SOURCE`

## Structure of the application

Class diagram of the application is shown below:

![](docs/uml/cam_controller.png)

_PublishingNode_ and _PublisherService_ belongs to [_Publisher_]()
library. _CamControllerManager_ and _LocationPublisherService_
realize the Node/Service relation. _CamControllerManager_
owns several _LocationPublisherService_ objects, each of them
using function _publish()_ to send information
about the location it is assigned to.

Beside that, _CamControllerManager_ is responsible for CAN communication,
hardware configuration and frame acquisition from the sensors.

_QrScanner_ is the clas performing QR code detection.
Each code (location) presented in the the current frame is stored
in the _Location_ vector, each _Location_ containing the data
presented in the code (_name_) and its position in the frame
