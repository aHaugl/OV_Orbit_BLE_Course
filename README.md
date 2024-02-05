# BLE-Course-for-Omega-V-Orbit
# Bluetooth_Low_Energy_Introduction

**Prerequisites:** 
* Make sure that you have a laptop with OS preferably within Tier 1 support range from the supported OS matrix found at https://developer.nordicsemi.com/nRF_Connect_SDK/doc/latest/nrf/installation/recommended_versions.html. From previous years we've spent quite a lot of time on day one on debugging various arcane OS's that has a varying degree of support for the SDK to ensure more time for the actual hands on part of the course.

* Read through the first lesson of nRF Connect SDK fundamentals https://academy.nordicsemi.com/courses/nrf-connect-sdk-fundamentals/lessons/lesson-1-nrf-connect-sdk-introduction/topic/nrf-connect-sdk-structure-and-content/

* Perform excersize 1 with v2.x.x steps to set up the SDK https://academy.nordicsemi.com/courses/nrf-connect-sdk-fundamentals/lessons/lesson-1-nrf-connect-sdk-introduction/topic/exercise-1-1/. In the course we will be using nRF Connect SDK v2.5.1. You will also find the required SW components listed under the SW Requirements section

* If you're able to do excersize 1 in lesson 1, you can also do lesson 2 to familiarize yourself a bit with how to build and flash a sample that comes with the SDK. Do note that unless you already have a development kit from Nordic available that is supported in nRF Connect SDK you won't be able to flash the firmware to the DK, but it's good that you've gotten to this part once before the course

Many of you will run into issues during installation, and thats fine. It's typically something very minor such as install location, installing the wrong version of the SW tools and/or extension or that system path variables have not been udpated or simply doing things in the wrong order. If you get flustered with the setup when going through the prerequisites, feel free to uninstall/remove what you've attempted to set up already and we will start day one of the course by going through theese steps for those in that situation and for those who did not have time to have a look at the prerequisites. The prerequisites aren't more mandatory than it is to read up on what your professor is going to present in your classes tomorrow, but as mentioned it may help you get a head start due to having seen some of what we're going to do and to let you have more fun with development rather than debugging why the installation does not work. 

For all three days we will have a set of Nordic engineers available in the auditorium for questions related to errors, the hands on exercises and anything related to Nordic Semiconductor that you think we might be able to give an answer to.

</br></br>

# HW requirements
- nRF52840 Development Kit. 
- MG90S Servo Motor
- 3x m-m jumper cables to connect the servo motor to the DK

For participants attending this course we will hand out said HW requirements at the start

# SW Requirements
As mentioned in the prerequisites, you'll need:
- [nRF Connect for Desktop](https://www.nordicsemi.com/Products/Development-tools/nRF-Connect-for-desktop)
- [Visual Studio Code](https://code.visualstudio.com/)
- [nRF Connect for Visual Studio Code plugin](https://www.nordicsemi.com/Products/Development-tools/nRF-Connect-for-VS-Code) (If you want to, you can use *west* directly instead of nRF Connect for Visual Studio code, but we will use VS Code in this guide).
- [nRF Command Line Tools](https://www.nordicsemi.com/Products/Development-tools/nrf-command-line-tools/download)

The goal for this course is to create a remote controller application that uses BLE to control the position of a PWM servo motor. Breaking this goal down into steps it will be as follows:
* Familiarize yourself with embededd programming using nRF Connect SDK and nRF devices
* Learn how to define and customize devices and nodes using Zephyr device trees and overlays
* Learn how to use various Zephyr APIs and familiarize yourself with said APIs
* Learn how to control the custom servo motor device we've created using the buttons available on the Development Kit handed out
* Learn how to create a custom Bluetooth Low Energy application and to define a custom service with custom value characteristics that we will use to control the servo motor remotely

All resources will be available in this public repository after the course has ended

# Tutorial Steps
### Step 1 - Getting started
If you didn't set up the SDK and toolchain by following the steps in the prerequisites then the first item on the agenda is to do this. If you've already succeeded in this, please feel free to have a sneak peek at Step 2 and/or to assist the person next to you

The first step may take some time since you will both download and install both the SDK and Toolchain which is of some size. While waiting 
Perform excersize 1 with v2.x.x steps to set up the SDK https://academy.nordicsemi.com/courses/nrf-connect-sdk-fundamentals/lessons/lesson-1-nrf-connect-sdk-introduction/topic/exercise-1-1/. In the course we will be using nRF Connect SDK v2.5.1
Academy NCS Fundamentals exercise 1 steps | 
------------ |
<img src="https://github.com/aHaugl/OV_Orbit_BLE_Course/blob/main/images/Step1.1.PNG" width="1000"> |

In a Windows installation I recommend that you install the SDK and toolchain close to C:/ in for instance C:/Nordic/ncs. Installing it close to C ensures that you don't run into any "Windows path length" issues. The path may of course vary with your OS

While waiting for the installation downloading you can have a look at the first lesson of nRF Connect SDK fundamentals https://academy.nordicsemi.com/courses/nrf-connect-sdk-fundamentals/lessons/lesson-1-nrf-connect-sdk-introduction/topic/nrf-connect-sdk-structure-and-content/. This section of text explains how the SDK is set up and which repositories it consists of and briefly mentions how the build system works.

We're now ready to create an application. The following steps will be similar to the steps in https://academy.nordicsemi.com/courses/nrf-connect-sdk-fundamentals/lessons/lesson-1-nrf-connect-sdk-introduction/topic/exercise-2-1/. We will copy the existing hello_world sample from the SDK located in NCS\zephyr\samples\hello_world. To do this you can do the following as seen in the image for how to setup an application from sample: 

* Open the VS Code extension for NCS in VS Code
* Click "Create new application"
* Select "Copy a sample" from the list
Setup Application from Sample 1/3 | 
------------ |
<img src="https://github.com/aHaugl/OV_Orbit_BLE_Course/blob/main/images/Step1.2.PNG" width="1000"> |

* Search for "Hello world" and select the sample from zephyr/samples/hello_world
Setup Application from Sample 2/3 | 
------------ |
<img src="https://github.com/aHaugl/OV_Orbit_BLE_Course/blob/main/images/Step1.3.PNG" width="1000"> |

* Select a folder for your application

I recommend that you create your projects folder outside of the SDK and toolchain folders. For instance within a "my_projects" folder. An example location (for Windows) can be c:\Nordic\SDKs\ncs\my_projects\custom_ble_app\remote_controller.

Setup Application from Sample 3/3 | 
------------ |

<img src="https://github.com/aHaugl/OV_Orbit_BLE_Course/blob/main/images/Step1.4.PNG" width="1000"> |
Verify SDK and toolchain version and build your firmware | 
------------ |
* Verify that the toolchain and SDK matches (both should be version 2.5.1). 
* Create a new build configuration
* Select your board which is the nRF52840dk_nrf52840 
* Leave everything else as default
* Press "Build Configuration"
<img src="https://github.com/aHaugl/OV_Orbit_BLE_Course/blob/main/images/Step1.5.PNG" width="1000"> |

If your build was successfull you should now be able to program your DK. Connect the micro-usb to your computer and the port on the short side of the board, select your build and select the Flash action

Flash your firmware to the board | 
------------ |
<img src="https://github.com/aHaugl/OV_Orbit_BLE_Course/blob/main/images/Step1.6.PNG" width="1000"> |

You should now be able to connect your board to a serial terminal. You can use the built in terminal in the extension as shown in the image below, or any other preferred serial temrinal such as Putty, Termite or other.

Connect your board to a terminal and observe the output 1/2 | 
------------ |
<img src="https://github.com/aHaugl/OV_Orbit_BLE_Course/blob/main/images/Step1.7.PNG" width="1000"> |

Connect your board to a terminal and observe the output 2/2 | 
------------ |
<img src="https://github.com/aHaugl/OV_Orbit_BLE_Course/blob/main/images/Step1.8.PNG" width="1000"> |

