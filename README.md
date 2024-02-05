# BLE-Course-for-Omega-V-Orbit
# Bluetooth_Low_Energy_Introduction

**Prerequisites:** 
* Make sure that you have a laptop with OS preferably within Tier 1 support range from the supported OS matrix found at https://developer.nordicsemi.com/nRF_Connect_SDK/doc/latest/nrf/installation/recommended_versions.html. From previous years we've spent quite a lot of time on day one on debugging various arcane OS's that has a varying degree of support for the SDK to ensure more time for the actual hands on part of the course.

* Read through the first lesson of nRF Connect SDK fundamentals https://academy.nordicsemi.com/courses/nrf-connect-sdk-fundamentals/lessons/lesson-1-nrf-connect-sdk-introduction/topic/nrf-connect-sdk-structure-and-content/

* Perform excersize 1 with v2.x.x steps to set up the SDK https://academy.nordicsemi.com/courses/nrf-connect-sdk-fundamentals/lessons/lesson-1-nrf-connect-sdk-introduction/topic/exercise-1-1/. In the course we will be using nRF Connect SDK v2.5.1. You will also find the required SW components listed under the SW Requirements section

* If you're able to do excersize 1 in lesson 1, you can also do lesson 2 to familiarize yourself a bit with how to build and flash a sample that comes with the SDK. Do note that unless you already have a development kit from Nordic available that is supported in nRF Connect SDK you won't be able to flash the firmware to the DK, but it's good that you've gotten to this part once before the course

Many of you will run into issues during installation, and thats fine. It's typically something very minor such as install location, installing the wrong version of the SW tools and/or extension or that system path variables have not been udpated or simply doing things in the wrong order. If you get flustered with the setup when going through the prerequisites, feel free to uninstall/remove what you've attempted to set up already and we will start day one of the course by going through theese steps for those in that situation and for those who did not have time to have a look at the prerequisites. The prerequisites aren't more mandatory than it is to read up on what your professor is going to present in your classes tomorrow, but as mentioned it may help you get a head start due to having seen some of what we're going to do and to let you have more fun with development rather than debugging why the installation does not work. 

For all three days we will have a set of Nordic engineers available in the auditorium for questions related to errors, the hands on exercises and anything related to Nordic Semiconductor that you think we might be able to give an answer to.

</br>

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
<img src="https://github.com/aHaugl/OV_Orbit_BLE_Course/blob/main/images/Step1.1.png" width="1000"> |

</br>

In a Windows installation I recommend that you install the SDK and toolchain close to C:/ in for instance C:/Nordic/ncs. Installing it close to C ensures that you don't run into any "Windows path length" issues. The path may of course vary with your OS

While waiting for the installation downloading you can have a look at the first lesson of nRF Connect SDK fundamentals https://academy.nordicsemi.com/courses/nrf-connect-sdk-fundamentals/lessons/lesson-1-nrf-connect-sdk-introduction/topic/nrf-connect-sdk-structure-and-content/. This section of text explains how the SDK is set up and which repositories it consists of and briefly mentions how the build system works.

We're now ready to create an application. The following steps will be similar to the steps in https://academy.nordicsemi.com/courses/nrf-connect-sdk-fundamentals/lessons/lesson-1-nrf-connect-sdk-introduction/topic/exercise-2-1/. We will copy the existing hello_world sample from the SDK located in NCS\zephyr\samples\hello_world. To do this you can do the following as seen in the image for how to setup an application from sample: 

* Open the VS Code extension for NCS in VS Code
* Click "Create new application"
* Select "Copy a sample" from the list

Setup Application from Sample 1/3 | 
------------ |
<img src="https://github.com/aHaugl/OV_Orbit_BLE_Course/blob/main/images/Step1.2.png" width="1000"> |

</br>

* Search for "Hello world" and select the sample from zephyr/samples/hello_world

Setup Application from Sample 2/3 | 
------------ |
<img src="https://github.com/aHaugl/OV_Orbit_BLE_Course/blob/main/images/Step1.3.png" width="1000"> |

</br>

* Select a folder for your application

I recommend that you create your projects folder outside of the SDK and toolchain folders. For instance within a "my_projects" folder. An example location (for Windows) can be c:\Nordic\SDKs\ncs\my_projects\custom_ble_app\remote_controller.

Setup Application from Sample 3/3 | 
------------ |
<img src="https://github.com/aHaugl/OV_Orbit_BLE_Course/blob/main/images/Step1.4.png" width="1000"> |

</br>


* Verify that the toolchain and SDK matches (both should be version 2.5.1). 
* Create a new build configuration
* Select your board which is the nRF52840dk_nrf52840 
* Leave everything else as default
* Press "Build Configuration"

Verify SDK and toolchain version and build your firmware | 
------------ |
<img src="https://github.com/aHaugl/OV_Orbit_BLE_Course/blob/main/images/Step1.5.png" width="1000"> |

</br>


If your build was successfull you should now be able to program your DK. Connect the micro-usb to your computer and the port on the short side of the board, select your build and select the Flash action

Flash your firmware to the board | 
------------ |
<img src="https://github.com/aHaugl/OV_Orbit_BLE_Course/blob/main/images/Step1.6.png" width="1000"> |

</br>

You should now be able to connect your board to a serial terminal. You can use the built in terminal in the extension as shown in the image below, or any other preferred serial temrinal such as Putty, Termite or other. Do the following:

* Expand the list of connected devices and the device number matching your board
* Select the COMPORT and click the plug-icon

A popup will come up with some UART settings. Select *115200 8n1*, and open the terminal

Connect your board to a terminal and observe the output 1/2 | 
------------ |
<img src="https://github.com/aHaugl/OV_Orbit_BLE_Course/blob/main/images/Step1.7.png" width="1000"> |

</br>

When you have connected your COMPORT to the terminal, press the reset button on the board and observe the following output

Connect your board to a terminal and observe the output 2/2 | 
------------ |
<img src="https://github.com/aHaugl/OV_Orbit_BLE_Course/blob/main/images/Step1.8.png" width="1000"> |

</br>

If you at an later point in time forget how you built or flash your application you can go back to these steps and repeat them. We will be using this procedure repeatedly throughout the hands on exercise.


### Step 2 - Enabling some basic application features
Congratulations! You have built and flashed our first application. Let's move on by doing some minor modifications. If you explore some of the samples from the *nrf* folder in NCS, you'll see that most of them use our logging module, which is what we will use as well. In order to do so, please replace the line `#include <sys/printk.h>` with `#include <zephyr/logging/log.h>`. In order to use the log module, we need to add a few things in the prj.conf file. You will find it from the application tab (called remote_controller if you didn't change it) -> Input files -> prj.conf. At this point, it should just say `#nothing here`.
</br>

Open your prj.conf | 
------------ |
<img src="https://github.com/aHaugl/OV_Orbit_BLE_Course/blob/main/images/Step2.1.png" width="1000"> |

</br> 

Add the following:

```
# Configure logger
CONFIG_LOG=y
CONFIG_USE_SEGGER_RTT=n
CONFIG_LOG_BACKEND_UART=y
CONFIG_LOG_DEFAULT_LEVEL=3
```
They are quite self explaining, but what we are doing here is enabling the log module, deselecting the default RTT backend, selecting the UART backend, and setting the log level to 3 (INFO).
Back in main.c, try replacing the printk() with LOG_INF(); and add the following snippet before void main(void)

```C
#define LOG_MODULE_NAME app
LOG_MODULE_REGISTER(LOG_MODULE_NAME);
```

Compile and flash the application again, and you should see that it still prints over UART, but now we are using the log module instead of the printk module.

</br>

#### Configure buttons and LEDs
Before we start adding Bluetooth, we want to set up some LEDs that we can use to indicate that our application is still running, and hasn't crashed. We also want to set up some buttons that we can use later to trigger certain BLE calls.
Start by including `<dk_buttons_and_leds.h>` in your main.c file.

Next, create a function to initiate the LEDs and buttons. I will call mine 'static void configure_dk_buttons_and_leds(void)'. The first thing we need to do in this function is to enable the LEDs. From the documentation page for DK buttons and LEDS (or by right clicking `#include <dk_buttons_and_leds.h>` and selecting "Go to definition") we can also see two important functions to initialize LEDS and buttons, one of them beeing dk_leds_init().

Try adding `dk_leds_init()` to your configure_dk_buttons_leds() function. Since this function returns and int, we would like to check the return value. 


```C
	int err;
	err = dk_leds_init();
	if(err){
		LOG_ERR("Couldn't init LEDS (err %d)", err);
	}
```
<br>

You may see that if you try to compile the sample after adding a function from the `dk_buttons_and_leds.h`, it will fail. The reason for this is that while we included the `dk_buttons_and_leds.h`, we didn't include the dk_buttons_and_leds.c file yet. This means that the compiler will not find the definitions of the functions that the header file claims that we have. We need to tell our application how to add the `dk_buttons_and_leds.c` file. There are two ways of doing this. If you create your own files, you can add them manually, which we will do later for some custom files. But for now we want to add a file that belongs to NCS, and therefore we include it using configuration switches.

From the DK buttons and LEDs documentation page https://developer.nordicsemi.com/nRF_Connect_SDK/doc/latest/nrf/libraries/others/dk_buttons_and_leds.html we see that to enable this library we will need to add `CONFIG_DK_LIBRARY=y` to our `prj.conf`. By opening the KConfig reference search for this page we can see that `CONFIG_DK_LIBRARY` also selects another configuration which we will use: `CONFIG_GPIO`
https://developer.nordicsemi.com/nRF_Connect_SDK/doc/latest/kconfig/index.html#CONFIG_DK_LIBRARY

<br>

To `prj.conf` add: 
```
# Configure buttons and LEDs.
CONFIG_DK_LIBRARY=y
```

This snippet will enable the GPIOs and include the DK library. The way this is done in NCS/Zephyr is a bit complex. If you are interrested in how this works, you can look into the CMakeLists.txt file found in NCS\nrf\lib\CMakeLists.txt, and see how it includes files and folders based on the configurations. For now we will accept that this is just how it works.

<br>

Now we've enabled and initialized our LEDs, so lets do some blinking. Under https://developer.nordicsemi.com/nRF_Connect_SDK/doc/latest/nrf/libraries/others/dk_buttons_and_leds.html#api-documentation you can see some masks that you can use as macros for various peripherals connected to various GPIOs on the SoC on the board, among them [DK_LED1](https://developer.nordicsemi.com/nRF_Connect_SDK/doc/latest/nrf/libraries/others/dk_buttons_and_leds.html#c.DK_LED1). Which GPIO these definitions are connected to will be different on different boards (such as a nRF52840DK and a nRF5340DK), and we will at a later point look closer into how you can configure which GPIO which is connected to what device definition. For now we will leave it as it is.

Near the top of main.c add a specific LED and a blinking interval:

```C
#define RUN_STATUS_LED DK_LED1
#define RUN_LED_BLINK_INTERVAL 1000
```

Open `dk_buttons_and_leds.h` or the [DK buttons and LEDS library API page](https://developer.nordicsemi.com/nRF_Connect_SDK/doc/latest/nrf/libraries/others/dk_buttons_and_leds.html#dk-buttons-and-leds) to see if there is any ways you can turn on and off this LED from your main function. Our goal is to toggle the LED in a `for(;;)` loop (equivalent to a while(true) loop). There are several ways to do this. Try to find one that works. </br>
*Hint: You can use k_sleep() to wait a given amount of time, and there is a macro called K_MSEC() that takes an input of ms, and converts it to ticks. To use k_sleep you will need to add `#include <zephyr/kernel.h>` to the top of main.c*

Build and flash your firmware. If you've done everything "as intended" you should now see that LED1 toggles on and off with a 1 sec interval.

</br>
Now, let us look for a function that can enable the buttons in the `dk_buttons_and_leds.h` file or [Library API](https://developer.nordicsemi.com/nRF_Connect_SDK/doc/latest/nrf/libraries/others/dk_buttons_and_leds.html). Remember to check the return value of the button init function. When you have a button handler set up, try to use it to print something in the log, so that we can see that it triggers correctly. We can tweak the button handler later.
</br>

*Hint: As this function initializes our buttons, it has an input parameter which is a callback handler. Use the "Go to definition" on the button handler type to see what kind of callback function it expects. If the button handler type that is expected is defined like this:* 

```C
typedef void (*callback_handler)(uint8_t first_parameter, uint16_t second_parameter);
```

*it means that you can define your callback e.g. like this:*

```C
void my_callback_function(uint8_t my_8_bit_parameter, uint16_t my_16_bit_parameter)
```
*You would probably choose some different names for the function and the parameters, but this is an example on how to interpret the callback typedefs.*

</br>

 **Challenge:** </br>
***Without peeking at the solution below, try to implement your button handler so that it stores the button number of the button that was pressed, and prints it in the log only when the button was pressed (and not released). Try printing out the parameters `button_state` and `has_changed` to see what they look like when you press the buttons. The library we're using contains a [button_handler callback function](https://developer.nordicsemi.com/nRF_Connect_SDK/doc/latest/nrf/libraries/others/dk_buttons_and_leds.html#c.button_handler_t) that can be used***
</br>
At this point, your main.c file should look something like this. You can use this as a template if you got stuck somewhere before this point:

```C
/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

#include <dk_buttons_and_leds.h>

#define LOG_MODULE_NAME app
LOG_MODULE_REGISTER(LOG_MODULE_NAME);

#define RUN_STATUS_LED DK_LED1
#define RUN_LED_BLINK_INTERVAL 1000

/* Callbacks */
void button_handler(uint32_t button_state, uint32_t has_changed)
{
	int button_pressed = 0;
	if (has_changed & button_state)
	{
		switch (has_changed)
		{
			case DK_BTN1_MSK:
				button_pressed = 1;
				break;
			case DK_BTN2_MSK:
				button_pressed = 2;
				break;
			case DK_BTN3_MSK:
				button_pressed = 3;
				break;
			case DK_BTN4_MSK:
				button_pressed = 4;
				break;
			default:
				break;
		}
		LOG_INF("Button %d pressed.", button_pressed);
	}
}

/* Configurations */
static void configure_dk_buttons_and_leds(void){
	int err;

	err = dk_leds_init();
	if(err){
		LOG_ERR("Couldn't init LEDS (err %d)", err);
	}
	
    err = dk_buttons_init(button_handler);
    if (err) {
        LOG_ERR("Couldn't init buttons (err %d)", err);
    }
}

/* Main */
int main(void)
{
	int blink_status = 0;
	LOG_INF("Hello World! %s\n", CONFIG_BOARD);

	configure_dk_buttons_and_leds();

	for(;;){
		dk_set_led(RUN_STATUS_LED,(blink_status++)%2);
		k_sleep(K_MSEC(RUN_LED_BLINK_INTERVAL));
	}
	return 0;
}

```