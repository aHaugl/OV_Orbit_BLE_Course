# BLE-Course-for-Omega-V-Orbit
# Bluetooth_Low_Energy_Introduction

**Prerequisites:** 
* Make sure that you have a laptop with OS preferably within Tier 1 support range from the supported OS matrix found at https://docs.nordicsemi.com/bundle/ncs-latest/page/nrf/installation/recommended_versions.html#supported_operating_systems. 

* Read through the first lesson of nRF Connect SDK fundamentals https://academy.nordicsemi.com/courses/nrf-connect-sdk-fundamentals/lessons/lesson-1-nrf-connect-sdk-introduction/topic/nrf-connect-sdk-structure-and-content/

* Perform exercise 1 with v2.x.x steps to set up the SDK https://academy.nordicsemi.com/courses/nrf-connect-sdk-fundamentals/lessons/lesson-1-nrf-connect-sdk-introduction/topic/exercise-1-1/. In the course we will be using nRF Connect SDK v2.6.2. Setting up the toolchain and SDK may take some time the first time, so you may get a better experience during the course days if you attempt or successfully perform the installation step before the first course day. You will also find the required SW components listed under the SW Requirements section

* If you're able to do exercise 1 in lesson 1, you can also do lesson 2 to familiarize yourself a bit with how to build and flash a sample that comes with the SDK. Do note that unless you already have a development kit from Nordic available that is supported in nRF Connect SDK you won't be able to flash the firmware to the DK, but it's good that you've gotten to this part once before the course

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
- [nRF Connect for Visual Studio Code plugin](https://www.nordicsemi.com/Products/Development-tools/nRF-Connect-for-VS-Code) (If you want to, you can use *west* in terminal directly instead of nRF Connect for Visual Studio code, but we will use VS Code in this guide since setting it up for terminal requires additional steps).
- [nRF Command Line Tools](https://www.nordicsemi.com/Products/Development-tools/nrf-command-line-tools/download)

The goal for this course is to create a remote controller application that uses BLE to control the position of a PWM servo motor. Breaking this goal down into steps it will be as follows:
* Familiarize yourself with embededd programming using nRF Connect SDK and nRF devices
* Learn how to define and customize devices and nodes using Zephyr device trees and overlays
* Learn how to use various Zephyr APIs and familiarize yourself with said APIs
* Learn how to control the custom servo motor device we've created using the buttons available on the Development Kit handed out
* Learn how to create a custom Bluetooth Low Energy application and to define a custom service with custom value characteristics that we will use to control the servo motor remotely

All resources will be available in this public repository after the course has ended.

# Tutorial Steps
## Step 1 - Getting started
If you didn't set up the SDK and toolchain by following the steps in the prerequisites then the first item on the agenda is to do this. If you've already succeeded in this, please feel free to have a sneak peek at Step 2 and/or to assist the person next to you

The first step may take some time since you will both download and install both the SDK and Toolchain which is of some size. While waiting 
Perform exercise 1 with v2.x.x steps to set up the SDK https://academy.nordicsemi.com/courses/nrf-connect-sdk-fundamentals/lessons/lesson-1-nrf-connect-sdk-introduction/topic/exercise-1-1/. In the course we will be using nRF Connect SDK v2.6.2
Academy NCS Fundamentals exercise 1 steps | 
------------ |
<img src="https://github.com/aHaugl/OV_Orbit_BLE_Course/blob/main/images/Step1.1.png" width="1000"> |

</br>

In a Windows installation I recommend that you install the SDK and toolchain close to C:/ in for instance C:/ncs, which is the default installation path. Installing it close to C ensures that you don't run into any "Windows path length" issues. The path may of course vary with your OS and the default path is different on Windows/MacOS/Linux.

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

I recommend that you create your projects folder outside of the SDK and toolchain folders. For instance within a "my_projects" folder. An example location (for Windows) can be c:\ncs\my_projects\custom_ble_app\remote_controller.

Setup Application from Sample 3/3 | 
------------ |
<img src="https://github.com/aHaugl/OV_Orbit_BLE_Course/blob/main/images/Step1.4.png" width="1000"> |

</br>


* Verify that the toolchain and SDK matches (both should be version 2.6.2). Note that the image illustrates how it would look if you have selected v2.5.1.
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


## Step 2 - Enabling some basic application features
Congratulations! You have built and flashed our first application. Let's move on by doing some minor modifications. If you explore some of the samples from the *nrf* folder in NCS, you'll see that most of them use our logging module, which is what we will use as well. In order to do so, add the line `#include <zephyr/logging/log.h>` to include the log header. In order to use the log module, we need to add a few things in the prj.conf file. You will find it from the application tab (called remote_controller if you didn't change it) -> Input files -> prj.conf. At this point, it should just say `#nothing here`.
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

### Configure buttons and LEDs
Before we start adding Bluetooth, we want to set up some LEDs that we can use to indicate that our application is still running, and hasn't crashed. We also want to set up some buttons that we can use later to trigger certain BLE calls.
Start by including `<dk_buttons_and_leds.h>` in your main.c file.

Next, create a function to initiate the LEDs and buttons. I will call mine 'static void configure_dk_buttons_and_leds(void)'. The first thing we need to do in this function is to enable the LEDs. From the [documentation page for DK buttons and LEDS](https://docs.nordicsemi.com/bundle/ncs-2.6.2/page/nrf/libraries/others/dk_buttons_and_leds.html) (or by right clicking `#include <dk_buttons_and_leds.h>` and selecting "Go to definition") we can also see two important functions to initialize LEDS and buttons, one of them beeing dk_leds_init().

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

From the [DK buttons and LEDs](https://docs.nordicsemi.com/bundle/ncs-2.6.2/page/nrf/libraries/others/dk_buttons_and_leds.html) documentation page we see that to enable this library we will need to add `CONFIG_DK_LIBRARY=y` to our `prj.conf`. By opening the KConfig reference search for this page we can see that [`CONFIG_DK_LIBRARY`](https://docs.nordicsemi.com/bundle/ncs-latest/page/kconfig/index.html#CONFIG_DK_LIBRARY) also selects another configuration which we will use: `CONFIG_GPIO`.

<br>

To `prj.conf` add: 
```
# Configure buttons and LEDs.
CONFIG_DK_LIBRARY=y
```
This snippet will enable the GPIOs and include the DK library. The way this is done in NCS/Zephyr is a bit complex. If you are interrested in how this works, you can look into the CMakeLists.txt file found in NCS\nrf\lib\CMakeLists.txt, and see how it includes files and folders based on the configurations. For now we will accept that this is just how it works.

<br>

Now we've enabled and initialized our LEDs, so lets do some blinking. Under the [API documentation](https://docs.nordicsemi.com/bundle/ncs-2.6.2/page/nrf/libraries/others/dk_buttons_and_leds.html#c.DK_LED1) for DK buttons and LEDs you can see some masks that you can use as macros for various peripherals connected to various GPIOs on the SoC on the board, among them [DK_LED1](https://docs.nordicsemi.com/bundle/ncs-2.6.2/page/nrf/libraries/others/dk_buttons_and_leds.html#c.DK_LED1). Which GPIO these definitions are connected to will be different on different boards (such as a nRF52840DK and a nRF5340DK), and we will at a later point look closer into how you can configure which GPIO which is connected to what device definition using pin control. For now we will leave it as it is.

Near the top of main.c add a specific LED and a blinking interval:

```C
#define RUN_STATUS_LED DK_LED1
#define RUN_LED_BLINK_INTERVAL 1000
```

Open `dk_buttons_and_leds.h` or the DK buttons and LEDS [library API page](https://docs.nordicsemi.com/bundle/ncs-2.6.2/page/nrf/libraries/others/dk_buttons_and_leds.html) to see if there is any ways you can turn on and off this LED from your main function. Our goal is to toggle the LED in a `for(;;)` loop (equivalent to a while(true) loop). There are a couple of options in the API to achieve this. Try to find one that works for you. </br>
*Hint: You can use k_sleep() to wait a given amount of time, and there is a macro called K_MSEC() that takes an input of ms, and converts it to ticks. To use k_sleep you will need to add `#include <zephyr/kernel.h>` to the top of main.c*

Build and flash your firmware. If you've done everything "as intended" you should now see that LED1 toggles on and off with a 1 sec interval.

</br>
Now, let us look for a function that can enable the buttons in the `dk_buttons_and_leds.h` file or [library API page](https://docs.nordicsemi.com/bundle/ncs-2.6.2/page/nrf/libraries/others/dk_buttons_and_leds.html#api_documentation) Remember to check the return value of the button init function. When you have a button handler set up, try to use it to print something in the log, so that we can see that it triggers correctly. We can tweak the button handler later.

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
***Without peeking at the solution below, try to implement your button handler so that it stores the button number of the button that was pressed, and prints it in the log only when the button was pressed (and not released). Try printing out the parameters `button_state` and `has_changed` to see what they look like when you press the buttons. The library we're using contains a [button_handler callback function](https://docs.nordicsemi.com/bundle/ncs-2.6.2/page/nrf/libraries/others/dk_buttons_and_leds.html#c.button_handler_t) that can be used***
</br>

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

## Step 3 - Motor Control
The motor that we used is the Tower Pro MG90S. You can find a very simple datasheet [here](https://www.electronicoscaldas.com/datasheet/MG90S_Tower-Pro.pdf). For some background information on how PWM motors work, you can check out [this guide](https://www.jameco.com/Jameco/workshop/Howitworks/how-servo-motors-work.html), and [this lesson in our Intermediate course on Academy for NCS](https://academy.nordicsemi.com/courses/nrf-connect-sdk-intermediate/lessons/lesson-4-pulse-width-modulation-pwm/)). We will do our implementation in this exercize similarly to what is done in the second exercise in the PWM repository mentioned.

Basically, we want to output a PWM signal, and the duty cycle of the PWM signal determines what angle/position the rotor will maintain. In our case, the motor wants a duty cycle between 1 and 2 ms, and a PWM period of 20ms. 

Because we want to keep main.c as clutter free as possible, we will try to do most of the PWM configurations and handling in another file, and implement some simple functions that we can call from main.c. Therefore we will add a couple of custom files. Inside your application folder (probably called `remote_controller`, you should see a folder named `src`. Inside this you will see your main.c file. Start by creating a new folder next to main.c called `custom_files`. You can either do this from Visual Studio Code, or you can do it from your Operative System's file explorer. Inside that folder, create two new files: `motor_control.h` and `motor_control.c`. To include these two files to your project, open `CMakeLists.txt` in Visual Studio Code and add the following to the end of CMakeLists.txt
</br>
```C
# Custom files and folders

target_sources(app PRIVATE
    src/custom_files/motor_control.c
)

zephyr_library_include_directories(src/custom_files)
```
In my project it looks like this:

```C
# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(remote_controller)

target_sources(app PRIVATE src/main.c)

# Custom files and folders

target_sources(app PRIVATE
    src/custom_files/motor_control.c
)

zephyr_library_include_directories(src/custom_files)
```

The line pointing to the `motor_control.c` file will include this .c file to your application project. The last line pointing to the folder `src/custom_files` will add that folder to the list of folders where the compiler will look for header files (.h files). 

If everything is done correctly, the project should compile, and we should be able to see our motor_control.c in our application tree as well as shown below. 

Application Tree | 
------------ |
<img src="https://github.com/aHaugl/OV_Orbit_BLE_Course/blob/main/images/Step3.1.png" width="1000"> |

<br>

Open `motor_control.c` and start by adding this line to the very top:

```C
#include "motor_control.h"
```

Open `motor_control.h` and add:
```C
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
```

**Challenge:** </br>
Try to create a function called `motor_init()` inside your `motor_control.c` file, that you also need to declare in `motor_control.h` file. Make the function return 0 (int), and check the return value of this function after you call it from your `main()` function. Add whatever that is needed in these two files so that you can use this function to print "*Initializing motor control.*" to our log. Remember to include `motor_control.h` from your `main.c` file.
</br>
*Hint: Give `motor_control.c` another log module name, so that it is easy to see from what file the log messages are coming from. Initialize the log module from `motor_control.c` pretty much the same way that you did in `main.c`.*
</br>

Build and flash your new firmware. What you should see as output is the same as in step 1 with the addition of a Log message from `motor_init()` from `motor_control.c` stating that you've initialized motor control.

Congratulations! You have successfully written your first function in a different .c file. Now, let us start adding PWM for our actual motor.

### PWM control
In this hands on we will implement a PWM device two ways. The first way will be to add the PWM module to drive a LED GPIO, which can be configured to drive a PWM servo motor if you customize the devicetree files and using pin control. The second way will be to drive the PWM servo motor through creating a custom device with custom parameters that you can add to your devicetree and drive said custom device with the PWM module through any available GPIO.

This README contains steps that are specific to this course, but they are nonetheless similar to the academy lesson I created regarding this topic during the spring of 2024. If you wish to read and do more around this topic or to follow the steps from another angle, please feel free to have a closer look at [lesson 4](https://academy.nordicsemi.com/courses/nrf-connect-sdk-intermediate/lessons/lesson-4-pulse-width-modulation-pwm/) in the official Nordic Semiconductor intermediate course for NCS.

So to reiterate: We will divide this into three parts.
* The first part will cover the common sections used in both method 1 and method 2 and show you how to set up and use the zephyr PWM module
* The second part (Method 1 which is optional) will show we can create a custom PWM device and select which GPIO the PWM module should drive 
* The third part (Method 2, mandatory) will show you how to create a custom device with custom parameters that you can add to your devicetree and drive said custom device with the PWM module through any available GPIO.

When we are using the nRF Connect SDK, we have several driver options to control the PWM. We have our own drivers that are tailored for the Nordic Semiconductor devices, or we can use Zephyr's drivers, which will use Nordic's drivers "underneath the hood". For this course we will use Zephyr's PWM drivers. 

Let us start by adding some configurations to our prj.conf file:

To enable the zephyr PWM driver add the following to your prj.conf:
```C
# PWM
CONFIG_PWM=y
CONFIG_PWM_LOG_LEVEL_DBG=y
```

What we are doing here is that we enable the PWM in our project, so that we can use it to control our motor. We will continue by adding the pwm header file near the top of `motor_control.h`. `motor_control.c` will inherit this, as long as it includes `motor_control.h`. Add near the top of motor_control.h:

```C
#include <zephyr/drivers/pwm.h>
```

The beauty of Zephyr drivers is that once we have enabled them through configurations in our prj.conf file, it will automagically be enabled and ready for use. 

Every nRF SoC has a set of peripherals available and every DK based on a nRF SoC has a set of predefined devices available. The nRF52840DK has among them multiple predefined PWM modules and one of them is the pwm_led that we can use to verify that we've set up our PWM module correctly. 

Under the devicetree tab in your applicaiton tree you can see the devicetree used for the current build. This board is selected from the list of boards found in [sdk_version/zephyr/boards/arm](https://github.com/nrfconnect/sdk-zephyr/tree/main/boards/arm), which is the nrf52840dk_nrf52840.dts located in [the nrf52840dk_nrf52840 folder](https://github.com/nrfconnect/sdk-zephyr/tree/main/boards/arm/nrf52840dk_nrf52840). 

Application Tree Devicetree | 
------------ |
<img src="https://github.com/aHaugl/OV_Orbit_BLE_Course/blob/main/images/Step3.2.png" width="1000"> |

<br>

Select the .dts for the nrf52840dk and open it, either in VSCode through the extension, locally in the SDK folder or on [github](https://github.com/nrfconnect/sdk-zephyr/blob/main/boards/arm/nrf52840dk_nrf52840/nrf52840dk_nrf52840.dts). What you should see is this file:

nrf52840dk_nrf52840.dts | 
------------ |
<img src="https://github.com/aHaugl/OV_Orbit_BLE_Course/blob/main/images/Step3.3.png" width="1000"> |

If you scroll through this .dts file you can see the predefined devices that are on the DK, and among are the buttons we've used in our button handler and the [pwm_led device](https://github.com/nrfconnect/sdk-zephyr/blob/93ad09a7305328387936b68059b63f64efd44f60/boards/arm/nrf52840dk_nrf52840/nrf52840dk_nrf52840.dts#L48-L53) which we will use to check if we've set up the PWM module properly: 

```
	pwmleds {
		compatible = "pwm-leds";
		pwm_led0: pwm_led_0 {
			pwms = <&pwm0 0 PWM_MSEC(20) PWM_POLARITY_INVERTED>;
		};
	};
```
Briefly explained, this is a device of the compatible type '[pwm-led](https://github.com/nrfconnect/sdk-zephyr/blob/main/dts/bindings/led/pwm-leds.yaml)', it has an alias, 'pwm_led0', and a name 'pwm_led_0'. It uses the 'pwms'-type instance which in this case is instance 0, has a duty cycle of 20 ms and inverted polarity. This device has been created and set up in Zephyr and is the default implementation for PWM devices in Zephyr for Nordic Devices, and you can find the [pwm-leds.yaml](https://github.com/nrfconnect/sdk-zephyr/blob/8005d4e87b9bcba25f441a51f4f5d29b541022b9/dts/bindings/led/pwm-leds.yaml#L6) file for this device in the SDK. In method 2 we will create our own device similarly to how this binding has been created.

<br>

To ensure that we've enabled the PWM driver properly we want to see if we can drive the pwm_led device that is predefined in the board file with the certain Devicetree and PWM APIs.

The first objective is to define and fetch this device from the .dts file into our .c files. We will do this using the [Devicetree API](https://docs.zephyrproject.org/latest/build/dts/api/api.html#devicetree-api) and the [PWM API documentation](https://docs.zephyrproject.org/latest/hardware/peripherals/pwm.html).

Under [node intentifiers and helpers](https://docs.zephyrproject.org/latest/build/dts/api/api.html#node-identifiers-and-helpers) you can find that there are various identifiers such as `DT_PATH()`, `DT_NODELABEL()`, `DT_ALIAS()`, and `DT_INST()`, and I mentioned that the pwmleds instance had an alias. Use `DT_ALIAS()` to define a PWM_LED0 device by adding the following near the top of motor_control.c

```C
#define PWM_LED0	DT_ALIAS(pwm_led0)
```
<br> 

The next we want to do is to initialize this device and populize the struct with the properties using [PWM_DT_SPEC_GET](https://docs.zephyrproject.org/latest/hardware/peripherals/pwm.html#c.PWM_DT_SPEC_GET).

Near the top, but after the PWM_LED0 definition in motor_control.c initialize and populate your device with the parameters from the .dts file:

```C
static const struct pwm_dt_spec pwm_led0 = PWM_DT_SPEC_GET(PWM_LED0);
```

Just for information, the definition above is equivalent to:

```C
static const struct pwm_dt_spec pwm_led0 = PWM_DT_SPEC_GET(DT_ALIAS(pwm_led0));
```

or to [PWM_DT_SPEC_GET_BY_NAME(node_id, name)](https://docs.zephyrproject.org/latest/hardware/peripherals/pwm.html#c.PWM_DT_SPEC_GET_BY_NAME) given that your device has a name.

<br>

Next we want to check that our PWM channel is ready when this part of the code is reached. Add these lines to your `motor_init()` function:

```C
    if (!device_is_ready(pwm_led0.dev)) {
    LOG_ERR("Error: PWM device %s is not ready",
            pwm_led0.dev->name);
    return -EBUSY;
	}
```

<br>

**Short background:** The way that PWM works is that it is a counter counting from 0 up to a `PWM period`. It starts with the PWM pin being high, and when it reaches a certain value called the `PWM duty cycle` the PWM signal will go low. When the counter reaches PWM period, the PWM pin will reset to high. See the figure from our servo motor specification:

PWM Period and PWM Duty Cycle | 
------------ |
<img src="https://github.com/aHaugl/OV_Orbit_BLE_Course/blob/main/images/Step3.4.png" width="1000"> |


**Challenge:** Before we connect our motor in method 1 and 2 in the coming sections, let us try to generate a PWM signal using our LED. You can give this a go without looking at the solution below. Open the [PWM API reference](https://docs.nordicsemi.com/bundle/ncs-2.6.2/page/zephyr/hardware/peripherals/pwm.html) and look for the description for ['pwm_set_dt()'](https://docs.nordicsemi.com/bundle/ncs-2.6.2/page/zephyr/hardware/peripherals/pwm.html#c.pwm_set_dt). Notice what the function takes as inputs and look at the servo motor's [data sheet](https://www.electronicoscaldas.com/datasheet/MG90S_Tower-Pro.pdf), to find the matching parameters you should call this function with. 

*Hint: the `spec` parameter is our pwm_led0. Since it requires a pointer, you need to use `&pwm_led0` when you use it in pwm_set_dt().*
*Hint 2: If you're struggling with finding a fitting parameter for pulse/duty cycle, try to set the pulse parameter to 1.5ms

If you find that the changes you made to your overlay file were not included in your build, you may have to perform a "pristine build" or even completely remove your build folder and build again to make the changes present in your new firmware.

If you managed to set the duty cycle of 1.5ms, you should see a faint light on LED1 on your DK (it should be fainter than the status LED from the previous part). 

That is good since we now have verified that our pwm driver is enabled, but we originally used LED1 for as the Status LED (showing us that the main() loop was running), so ideally we want to use another pin for PWM control. To do this, we need to add something called an overlay file.

Here is how my here's how my motor_control.c looks after this step.
```C
#include "motor_control.h"

#define LOG_MODULE_NAME motor_control
LOG_MODULE_REGISTER(LOG_MODULE_NAME);

#define PWM_LED0	DT_ALIAS(pwm_led0)
static const struct pwm_dt_spec pwm_led0 = PWM_DT_SPEC_GET(PWM_LED0);

#define PWM_PERIOD_NS 20000000
int motor_init(void)
{
    int err = 0;
    LOG_INF("Initializing Motor Control");

    if (!device_is_ready(pwm_led0.dev)) {
    LOG_ERR("Error: PWM device %s is not ready",
            pwm_led0.dev->name);
    return -EBUSY;
	}

    err = pwm_set_dt(&pwm_led0, PWM_PERIOD_NS, 1500000);
    if (err) {
        LOG_ERR("pwm_set_dt returned %d", err);
    }

    return err;
}
```

### Overlay Files
As mentioned earlier all boards defined in Zephyr have their own board files containing all the information about the predefined devices on the board such as GPIOs, LEDs, pwm instances and their default configuration. We can make changes to the device tree files to change e.g what pins are used for LEDs, but making changes directly to a .dts file will cause *every other project that uses these board files to also use the same configuration*. So to keep a good project-to-code-base-separation we will be using overlay files instead.

An overlay file is as the name implies: A file that lays itself over the top of the device tree or project configurations and is tailored to this specific type of device. The way that it works is that the compiler will first read the board file (.dts file), and then it will look for an overlay file. If it finds one, then all the settings found in the .overlay file will overwrite the default settings from the .dts file, but only for the current project. This way we can have multiple devices sharing a foundational code base where each device becomes unique through its own custom .overlay file

Managing multiple applications through overlay files | 
------------ |
<img src="https://github.com/aHaugl/OV_Orbit_BLE_Course/blob/main/images/Step3.5.png" width="1000"> |

</br>

Start by creating a file called `nrf52840dk_nrf52840.overlay`. You can do this by clicking the "No overlay files detected, click here to create one" button under Config files and Devicetree in the Application tree in the VS Code extension. This will create a .overlay file with the same name as the board selected for the build in your project folder on the same level as the `prj.conf` and `CMakeLists.txt` file. You can also create this file manually but make sure that it follows the mentioned naming and location convention.

</br>
If you're struggling at this point in time, please feel free to have a look at the solution for this point in time located in the [temp_files\Step_3.0_sol](https://github.com/aHaugl/OV_Orbit_BLE_Course/tree/main/temp_files/Step_3.0_sol). This partial solution also works as a jump start for both method 2 and the optional steps for method 1.

If you've managed to drive one of the LEDs with a PWM instance and set up the .overlay file as described you can now either choose to do the optional method 1, or to continue directly to Method 2, which the solution in Step 4 and has used. I personally recommend you to do method 2 and if you have time you can go through the steps to do method 1 starting from either a copy of your project at this point in time, or by starting from the project in Step_3.0_sol. 

Method 1 will show you how to create a custom PWM device and select which GPIO it should drive through the means of using the pwm_led compatible and pin control that is predefined. Method 2 will show you how to do the same *but* by defining and creating your own custom device through a .yaml, similar to the pwm-leds.yaml found in the SDK.

### Method 1 - Optional steps: Modify the pwm_led0 instance to drive the servo motor
This part is to showcase how you can reconfigure existing peripheral devices such as the predefined pwm_led0 instance to something else. It is a section that is defined to break apart some of the abstraction layers that comes with overlayfiles and devicetree.

Now to the steps for how to do this: If you open your nrf52840dk_nrf52840.dts, which is our standard board file, we can see what pwm_led0 looks like by default:

[pwm_led device](https://github.com/nrfconnect/sdk-zephyr/blob/93ad09a7305328387936b68059b63f64efd44f60/boards/arm/nrf52840dk_nrf52840/nrf52840dk_nrf52840.dts#L48-L53)  default configuration | 
------------ |
<img src="https://github.com/aHaugl/OV_Orbit_BLE_Course/blob/main/images/Step3.3.png" width="1000"> |

```
	pwmleds {
		compatible = "pwm-leds";
		pwm_led0: pwm_led_0 {
			pwms = <&pwm0 0 PWM_MSEC(20) PWM_POLARITY_INVERTED>;
		};
	};
```

As mentioned in the `overlay files` section , we don't want to change anything inside this file, because those changes will stick to all other projects that are using the same board file. This is why we want to do the changes in our overlay file. Unfortunately, the pin number is not set here directly. It is set in &pwm0 inside pwm_led0. But since the default configuration for pwm_led0 is PWM_POLARITY_INVERTED, and we want to change that as well, we need to add the pwmleds snippet to our overlay file as well. 
Let us start by adding a pwmleds snippet to our `nrf52840dk_nrf52840.overlay` file. This will overwrite the default settings from the .dts file.

```C
/{
    pwmleds {
        compatible = "pwm-leds";
        pwm_led0: pwm_led_0 {
            pwms = <&pwm0 0 PWM_MSEC(20) PWM_POLARITY_NORMAL>;
        };
    };
};
```

You can see here that the only change we did was to change the polarity from inverted to normal. This means that the PWM signal will have a high output for the duty cycle, instead of low. If you right click and select "go to definition" on the `&pwm0` in your overlay file, you will see something like this:

```C
&pwm0 {
	status = "okay";
	pinctrl-0 = <&pwm0_default>;
	pinctrl-1 = <&pwm0_sleep>;
	pinctrl-names = "default", "sleep";
};
```

So our pin numbers are set in pwm0_default and pwm0_sleep. Let us start by changing the names of these as we add this to our `overlay` file:

```C
&pwm0 {
    status = "okay";
    pinctrl-0 = <&pwm0_custom>;
    pinctrl-1 = <&pwm0_csleep>;
    pinctrl-names = "default", "sleep";
};
```

You can call them whatever you like. I used pwm0_custom and pwm0_csleep. The last part we need to do is that we need to define pwm0_custom and pwm0_csleep. Try right clicking the pwm0_default and pwm0_sleep in the .dts file to see what they look like by default:

```C
&pinctrl {
	pwm0_default: pwm0_default {
		group1 {
			psels = <NRF_PSEL(PWM_OUT0, 0, 3)>;
			nordic,invert;
		};
	};
    
	pwm0_sleep: pwm0_sleep {
		group1 {
			psels = <NRF_PSEL(PWM_OUT0, 0, 3)>;
			low-power-enable;
		};
	};
};
```

Note that I added the `&pinctrl {` and `};` at the top and bottom, since we need this when we copy it into our `.overlay` file. 

Add this to your `.overlay` file (with the names that you used in `&pwm0`):

```C
&pinctrl {
    pwm0_custom: pwm0_custom {
        group1 {
            psels = <NRF_PSEL(PWM_OUT0, 0, 3)>;
            nordic,invert;
        };
    };

    pwm0_csleep: pwm0_csleep {
        group1 {
            psels = <NRF_PSEL(PWM_OUT0, 0, 3)>;
            low-power-enable;
        };
    };
};
```

FYI: the `0, 3` is port 0, pin 3. If you wanted to use e.g. pin P1.15, you would set `psels = <NRF_PSEL(PWM_OUT0, 1, 15). 

In the end, your `nrf52840dk_nrf52840.overlay` file should look something like this:

```C
&pinctrl {
    pwm0_custom: pwm0_custom {
        group1 {
            psels = <NRF_PSEL(PWM_OUT0, 0, 3)>;
            nordic,invert;
        };
    };

    pwm0_csleep: pwm0_csleep {
        group1 {
            psels = <NRF_PSEL(PWM_OUT0, 0, 3)>;
            low-power-enable;
        };
    };
};

&pwm0 {
    status = "okay";
    pinctrl-0 = <&pwm0_custom>;
    pinctrl-1 = <&pwm0_csleep>;
    pinctrl-names = "default", "sleep";
};

/{
    pwmleds {
        compatible = "pwm-leds";
        pwm_led0: pwm_led_0 {
            pwms = <&pwm0 0 PWM_MSEC(20) PWM_POLARITY_NORMAL>;
        };
    };
};
```

Try to connect the servo motor. It has three wires. One brown, which you can connect to GND. Then you have one Red, which you can connect to VDD (not the one marked 5V), and then connect the yellow/orange wire to whatever pin you chose for your PWM pin (probably P0.03). 
Does the motor move? **Warning: Do not attempt to move the rotor by force while the motor is connected to power. The motors are fragile...**

If it does, you can try to create a function inside motor_control.c that you can call from e.g. the button handler to set the pwm signal to different values between 1ms and 2ms. These motors are cheap, so some motors goes 180 degrees between 1ms and 2ms, but yout milage may vary. Try out different values to see what the limits are for your motor. When I tested one of the motors, it turned out that the limits were 0.4ms and 2.4ms. 
Call the function `set_motor_angle()` and make it return an int (0 on success, negative value on error). Declare it in motor_control.h, and implement it in motor_control.c. make it have an input parameter either as a PWM duty cycle, or an input angle (degrees between 0 and 180).

Use this to set different angles, depending on what button you pressed. 

If you are having problems with controlling the motors, you can have a look at what my motor_control.h and motor_control.c looks like at this point in time in [the solution for step 3, method 1](https://github.com/aHaugl/OV_Orbit_BLE_Course/tree/main/temp_files/Step_3.1_sol).


### Method 2 - Create a custom motor device and use the PWM module to drive a motor
For this method we will be using what is called a .yaml file to define our new custom device. This file is will be similar to what I showed you earlier for the [`pwm-leds.yaml`](https://github.com/nrfconnect/sdk-zephyr/blob/main/dts/bindings/led/pwm-leds.yaml)

Create a new folder in your project called `"dts"` and within this folder create a new folder named `"bindings"`. Inside `"bindings"` create a file named `"pwm-servo.yaml"`. Inside `pwm-servo.yaml` add the following:

```
# Copyright (c) 2022 Nordic Semiconductor ASA
# SPDX-License-Identifier: Apache-2.0

description: PWM-driven servo motor.

compatible: "pwm-servo"

include: base.yaml
```
If you inspect [`pwm-leds.yaml`](https://github.com/nrfconnect/sdk-zephyr/blob/main/dts/bindings/led/pwm-leds.yaml) you can also see that this device has some properties. Namely `pwms`. We also want this for our pwm-servo, so we will be adding this to our device. In addition we know that from the servo motor specification, the motor itself has a minimum and maximum pulse as shown below.

Servo Motor SG 90 data sheet | 
------------ |
<img src="https://github.com/aHaugl/OV_Orbit_BLE_Course/blob/main/images/Step3.6.png" width="1000"> |

A vivid thinker might consider this to be a good property to include in your device as a required property, so we will add this as well to the servo-motor.yaml underneath what we already added.

```
properties:
  pwms:
    required: true
    type: phandle-array
    description: PWM specifier driving the servo motor.

  min-pulse:
    required: true
    type: int
    description: Minimum pulse width (nanoseconds).

  max-pulse:
    required: true
    type: int
    description: Maximum pulse width (nanoseconds).
```
Now save the pwm-servo.yaml and open the `nrf52840dk_nrf52840.overlay` we created earlier.

To your .overlay add your custom device as follows:

```
/ {
    servo: servo {
        compatible = "pwm-servo";
        pwms = <&pwm0 0 PWM_MSEC(---) PWM_POLARITY_NORMAL>;
        min-pulse = <PWM_USEC(---)>;
        max-pulse = <PWM_USEC(---)>;
    };
};
```
**Mini challenge:**
Without looking at the solution below, fill in the missing values by replacing `---` with the values from the datasheet for the [servo motor](http://www.ee.ic.ac.uk/pcheung/teaching/DE1_EE/stores/sg90_datasheet.pdf)

We've now created our device with name servo and nodelabel servo and set the default values to be within the limits and stated that PWM instance 0 should drive this device
```
/ {
    servo: servo {
        compatible = "pwm-servo";
        pwms = <&pwm0 0 PWM_MSEC(20) PWM_POLARITY_NORMAL>;
        min-pulse = <PWM_USEC(1000)>;
        max-pulse = <PWM_USEC(2000)>;
    };
};
```
We could have selected another pwm instance such as &pwm1 instead of &pwm0, but since we're only using 1 pwm instance in this project we stick with instance 0. The next step is to use Zephyrs pin control to select which GPIO pwm0 should drive. By default it drives the GPIO connected to LED1 through the pwm_led0 node, but we want it to drive a free available GPIO that we can connect our servo motor to.

Right click `&pwm0` in your overlay and click `go to definition `. You should see the following

&pwm0 definition | 
------------ |
<img src="https://github.com/aHaugl/OV_Orbit_BLE_Course/blob/main/images/Step3.7.png" width="1000"> |

Copy and paste the [&pwm0 instance](https://github.com/nrfconnect/sdk-zephyr/blob/93ad09a7305328387936b68059b63f64efd44f60/boards/arm/nrf52840dk_nrf52840/nrf52840dk_nrf52840.dts#L199C1-L204C3) to your overlay file, above the servo instance.

Next right click `&pwm0_default` and click "go to definition, which should take you here:

[&pin_control definition](https://github.com/nrfconnect/sdk-zephyr/blob/93ad09a7305328387936b68059b63f64efd44f60/boards/arm/nrf52840dk_nrf52840/nrf52840dk_nrf52840-pinctrl.dtsi#L77-L89) | 
------------ |
<img src="https://github.com/aHaugl/OV_Orbit_BLE_Course/blob/main/images/Step3.8.png" width="1000"> |


Copy and paste the pwm0_default and pwm_sleep instance to your overlay file, which now should look like this: 

```
&pinctrl {

	pwm0_default: pwm0_default {
		group1 {
			psels = <NRF_PSEL(PWM_OUT0, 0, 13)>;
			nordic,invert;
		};
	};

	pwm0_sleep: pwm0_sleep {
		group1 {
			psels = <NRF_PSEL(PWM_OUT0, 0, 13)>;
			low-power-enable;
       };
    };
};

&pwm0 {
	status = "okay";
	pinctrl-0 = <&pwm0_default>;
	pinctrl-1 = <&pwm0_sleep>;
	pinctrl-names = "default", "sleep";
};

/ {
    servo: servo {
        compatible = "pwm-servo";
        pwms = <&pwm0 0 PWM_MSEC(20) PWM_POLARITY_NORMAL>;
        min-pulse = <PWM_USEC(1000)>;
        max-pulse = <PWM_USEC(2000)>;
    };
};
```

Replace the pincontrol names with something custom, suited for your device. For instance as suggested below:

```
&pinctrl {
    pwm0_custom_motor: pwm0_custom_motor {
        group1 {
            psels = <NRF_PSEL(PWM_OUT0, 0, 13)>;
            nordic,invert;
        };
    };

    pwm0_csleep_motor: pwm0_csleep_motor {
        group1 {
            psels = <NRF_PSEL(PWM_OUT0, 0, 13)>;
            low-power-enable;
        };
    };
};

&pwm0 {
    status = "okay";
    pinctrl-0 = <&pwm0_custom_motor>;
    pinctrl-1 = <&pwm0_csleep_motor>;
    pinctrl-names = "default", "sleep";
};
```
We're almost done and ready to test our motor now. As mentioned, the default pwm_led0 node is couled with LED1 (through `GPIO 13`), so for us to be able to use this pwm instance to drive our motor we need to select a GPIO that is free to use. The [User Guide for the nRF52840DK](https://infocenter.nordicsemi.com/pdf/nRF52840_DK_User_Guide_20201203.pdf), section 8.6 gives us some hints as to what may be a good candidate. Here you can see all the available ports and GPIO, whereas many of them are already connected to certain devices such as the LEDs and DK buttons. But every GPIO that does not have gray writing next to them is so called free purpose GPIO's and can be selected. I recommend that you for instance use GPIO 3 on port 0, i.e `P0.03` due to its close proximity to both VDD and GND which we also need.

nRF52840DK Connectors | 
------------ |
<img src="https://github.com/aHaugl/OV_Orbit_BLE_Course/blob/main/images/Step3.9.png" width="1000"> |

Inspect [NRF_PSEL](https://docs.zephyrproject.org/apidoc/latest/nrf-pinctrl_8h.html#a43d0a0ad6e574456a2b69ab5354ccef4) by right clicking it and go to the link. Here you can see that this macro allows you to set which GPIO you want your pin configuration to be selected to use. In your custom pwm0_custom_motor and pwm0_csleep, replace the pin number `13` with pin number `3`.

Next we need to do the same as we did with the pwm0 led when we tested if we had included the PWM module properly. 

**Challenge** 
Without looking at the solution below: In motor_control.c define replace the pwm_led definition with your servo motor through [`DT_NODELABEL`](https://docs.zephyrproject.org/latest/build/dts/api/api.html#c.DT_NODELABEL) and initialize the device with [`PWM_DT_SPEC_GET`](https://docs.zephyrproject.org/apidoc/latest/group__pwm__interface.html#ga59a79f0b77c5b71252bde126f333a84b)

You also need to replace the name of the device you use in motor_init()

Your motor_control.c should look something like this now:

```C
#include "motor_control.h"

#define LOG_MODULE_NAME motor_control
LOG_MODULE_REGISTER(LOG_MODULE_NAME);

#define SERVO_MOTOR     DT_NODELABEL(servo)
static const struct pwm_dt_spec pwm_servo = PWM_DT_SPEC_GET(SERVO_MOTOR);


#define PWM_PERIOD_NS 20000000
int motor_init(void)
{
    int err = 0;
    LOG_INF("Initializing Motor Control");

    if (!device_is_ready(pwm_servo.dev)) {
    LOG_ERR("Error: PWM device %s is not ready",
            pwm_servo.dev->name);
    return -EBUSY;
	}

    err = pwm_set_dt(&pwm_servo, PWM_PERIOD_NS, 1500000);
    if (err) {
        LOG_ERR("pwm_set_dt returned %d", err);
    }

    return err;
}

```

Try to connect the servo motor. It has three wires. One brown, which you can connect to GND. Then you have one Red, which you can connect to VDD (not the one marked 5V), and then connect the yellow/orange wire to whatever pin you chose for your PWM pin (probably P0.03). 
Does the motor move? **Warning: Do not attempt to move the rotor by force while the motor is connected to power. The motors are fragile and quite rigid when they are powered**

If it does, you can try to create a function inside motor_control.c that you can call from e.g. the button handler to set the pwm signal to different values between 1ms and 2ms (min and max duty cycle defined in our overlay earlier). Hint: One way to use the properties defined in our overlay file for minimum and maximum duty cycles is to use [DT_PROP(node_id, prop)](https://docs.zephyrproject.org/latest/build/dts/api/api.html#c.DT_PROP)

These motors are cheap, so some motors goes 180 degrees between 1ms and 2ms, but yout milage may vary. Try out different values to see what the limits are for your motor. When I tested one of the motors, it turned out that the limits were 0.4ms and 2.4ms. 

Call the function `set_motor_angle()` and make it return an int (0 on success, negative value on error). Declare it in motor_control.h, and implement it in motor_control.c. make it have an input parameter either as a PWM duty cycle, or an input angle (degrees between 0 and 180).

Use this to set different angles, depending on what button you pressed. 

If you are having problems with controlling the motors, you can have a look at what my motor_control.h and motor_control.c looks like at this point in time in [partial solution step 3.2](https://github.com/aHaugl/OV_Orbit_BLE_Course/tree/main/temp_files/Step_3.2_sol).

## Step 4 - Adding Bluetooth
It is finally time to add bluetooth to our project. A hint was given in the project name, but in case you missed it, we will write an application that mimics some sort of bluetooth remote, where we will be able to send button presses to a connected Bluetooth Low Energy Central. We will also add the oppurtunity to write back to the remote control. That may not be a typical feature for a remote control, but for the purpose of learning how to communicate in both directions we will add this. The connected central can either be your phone, a computer, or another nRF52. For this guide we will use the DK we've been working with so far and a smartphone with nRF Connect for iOS or Android.

This part will be similar to the [BLE fundamentals course](https://academy.nordicsemi.com/courses/bluetooth-low-energy-fundamentals/) on our academy pages, which we recommend that you go through in your own time to pick up some other details that won't be mentioned in this hands-on exercise. 
In this first part we will go through a majority of the content covered in [Lesson 1 in the mentioned course](https://academy.nordicsemi.com/courses/bluetooth-low-energy-fundamentals/lessons/lesson-1-bluetooth-low-energy-introduction/).

Because we want to keep our main.c clean, we will try to do most of the bluetooth configuration and handling in another file, just like we did with PWM. Therefore we will start by adding some more custom files. Inside the custom_files folder, create two more files: remote.h and remote.c. To include these custom files to your project, open CMakeLists.txt, add on to what we changed earlier:

```C
# Custom files and folders

target_sources(app PRIVATE
    src/custom_files/motor_control.c;
    src/custom_files/remote.c;
)

zephyr_library_include_directories(src/custom_files)
```


</br>
When you build your application again, you should see remote.c appear next to motor_control.c.

</br>
Open remote.c and add the line at the very top: </br>

```C
#include "remote.h"
```
Also add a log_module similar to the other .c files we've made:

```C
#define LOG_MODULE_NAME remote
LOG_MODULE_REGISTER(LOG_MODULE_NAME);
```

And in `remote.h`, add the following:

```C
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
```
Now try to create a function called `bluetooth_init()` in your remote.c file that you also need to declare in remote.h. Make the function return `0`, and check this return value in `main()`. Just like before, add whatever is needed in these two files so that you can use this function to log "Initializing Bluetooth". Remember to include remote.h from your main.c file.
</br>
Now that we have our own file to do most of the Bluetooth, let us start by adding these four header files in our remote.h file:

```C
//Bluetooth configs
#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/uuid.h>
#include <zephyr/bluetooth/gatt.h>
#include <zephyr/bluetooth/hci.h>
```

As with the pwm and logging headers, these headers also requires a set of configurations to be enabled. To your prj.conf add the following: 

```
# Configure Bluetooth
CONFIG_BT=y
CONFIG_BT_PERIPHERAL=y
CONFIG_BT_DEVICE_NAME="Remote_controller"
CONFIG_BT_DEVICE_APPEARANCE=0
CONFIG_BT_MAX_CONN=1
CONFIG_BT_LL_SOFTDEVICE=y

CONFIG_ASSERT=y
````

What we do here is:
- Enable Bluetooth,
- Support the peripheral (advertising) role
- Set our device_name, which we will use later
- Set the appearance. Look in the description of this configuration to see what this does.
- Set the maximum number of simultaneous connections to 1.
- Tell it to use the Nordic Softdevice Controller. 

For most Bluetooth Low Energy, these four headers and these configurations will do the job. 

Let us start by finding a function to *enable bluetooth*. Inspect [The Generic Access Profile API](https://docs.nordicsemi.com/bundle/ncs-2.6.2/page/zephyr/connectivity/bluetooth/api/gap.html) and see if you find it. *(Hint: It is [this one](https://docs.nordicsemi.com/bundle/ncs-2.6.2/page/zephyr/connectivity/bluetooth/api/gap.html#c.bt_enable)).

<br>
If you've found the function, we can see by inspecting it that this is a function that returns an int and it takes an input `bt_ready_cb_t. Follow the definition of [bt_ready_cb_t](https://docs.nordicsemi.com/bundle/ncs-2.6.2/page/zephyr/connectivity/bluetooth/api/gap.html#c.bt_ready_cb_t) you will see that the bt_ready_cb_t is defined as follows:

```C
typedef void (*bt_ready_cb_t)(int err)
```

This means that `bt_ready_cb_t` takes a function pointer., i.e a callback function as input parameter. The callback is on the form `void callback_name(int err)`. Let us create a callback named "bt_ready", which we will implement above `bluetooth init()`in remote.c and pass it onto `bt_enable()`.

```C
void bt_ready(int err)
{
    if (err) {
        LOG_ERR("bt_enable returned %d", err);
    }
}
```

One important aspect when it comes to initializing, enabling and in general running time critical code is that we want to ensure that everything has enough time to finish before we race on to the next part of the code. To do this we can use a [semaphore](https://developer.nordicsemi.com/nRF_Connect_SDK/doc/latest/zephyr/kernel/services/synchronization/semaphores.html).

At the top of this page you can see 2 key properties of the semaphore and 3 criterias for how to use it and where to use it. Most of you might already know what a semaphore is already, but read through the concept before moving on anyways to refresh this topic and to see how it is used in NCS/Zephyr.

Moving back to why we want to do this: We want to wait for our callback before we continue with our application. In order to do this, we will as mentioned use a semaphore. [Define the semaphore](https://developer.nordicsemi.com/nRF_Connect_SDK/doc/latest/zephyr/kernel/services/synchronization/semaphores.html#defining-a-semaphore) near the top of remote.c:

```C
static K_SEM_DEFINE(bt_init_ok, 0, 1);
```

After `bt_enable(bt_ready_callback)` try to [take the semaphore](https://developer.nordicsemi.com/nRF_Connect_SDK/doc/latest/zephyr/kernel/services/synchronization/semaphores.html#taking-a-semaphore), so that the application waits until it is given from somewhere else, and then try to give it in the bt_ready callback. </br>
*Hint: The k_sem_take() requires a timeout. You can use K_FOREVER.*

<br>

After you've taken the semaphore you also need to give it somewhere. In the callback for checking if Bluetooth is ready and properly set up, give the semaphore after checking the error. It should look like this:

```C
void bt_ready_callback(int err)
{
    if (err) {
        LOG_ERR("bt_enable returned %d", err);
    }
    k_sem_give(&bt_init_ok);
}
```

Now is a good time to build and flash your firmware to see if you've set everything up properly. If your successfull in this step and if you connect to a terminal like we've done earlier you should see something like the following:

```
*** Booting nRF Connect SDK v2.5.1 ***
[00:00:00.000,366] <inf> app: Hello World! nrf52840dk_nrf52840

[00:00:00.000,701] <inf> motor_control: Initializing Motor Control
[00:00:00.000,732] <dbg> pwm_nrfx: pwm_nrfx_set_cycles: channel 0, pulse 24000, period 320000, prescaler: 4.
[00:00:00.000,762] <inf> remote: Initializing Bluetooth
[00:00:00.000,915] <inf> bt_sdc_hci_driver: SoftDevice Controller build revision: 
                                            c5 93 ba a9 14 4d 8d 05  30 4e 9b 92 d7 71 1e e8 |.....M.. 0N...q..
                                            aa 02 50 3c                                      |..P<             
[00:00:00.004,455] <inf> bt_hci_core: HW Platform: Nordic Semiconductor (0x0002)
[00:00:00.004,486] <inf> bt_hci_core: HW Variant: nRF52x (0x0002)
[00:00:00.004,516] <inf> bt_hci_core: Firmware: Standard Bluetooth controller (0x00) Version 197.47763 Build 2370639017
[00:00:00.005,737] <inf> bt_hci_core: Identity: CC:EA:F9:3E:56:AE (random)
[00:00:00.005,798] <inf> bt_hci_core: HCI: version 5.4 (0x0d) revision 0x1102, manufacturer 0x0059
[00:00:00.005,828] <inf> bt_hci_core: LMP: version 5.4 (0x0d) subver 0x1102
```

If you're stuck here (and you've asked for help from either the representatives hosting the course or your fellow course participants), you can inspect the [partial solution for this step here](https://github.com/aHaugl/OV_Orbit_BLE_Course/tree/main/temp_files/Step_4.0_sol).

</br>

### Advertising
We've now enabled Bluetooth but we've not yet used it for anything. Taking a page out of [Lesson 2](https://academy.nordicsemi.com/courses/bluetooth-low-energy-fundamentals/lessons/lesson-2-bluetooth-le-advertising/) in the academy course we will now enable BLE Advertising. 

We want to include two things in our advertisements. The device name and the UUID of the service that we will implement later. Let us start by adding the UUID (Universally Unique Identifier). I typically use an online UUID generator. Try using [this online UUID Generator](https://www.uuidgenerator.net/version4). In my case, I got a UUID `020f85e6-bc61-4d87-9319-9aff590fd64c` which I translated to this format:

```C
/* Add this to remote.h */
/** @brief UUID of the Remote Service. **/
#define BT_UUID_REMOTE_SERV_VAL \
BT_UUID_128_ENCODE(0x020f0001, 0xbc61, 0x4d87, 0x9319, 0x9aff590fd64c)
```
where I set the two last bytes of the first section to 0001. This is so it is easier to recognize the UUID later. Copy your own generated UUID into the same format, and set the two last bytes of the first sections to 0001, like I did. Also add the following line below the definition of your UUID:

```C
#define BT_UUID_REMOTE_SERVICE  BT_UUID_DECLARE_128(BT_UUID_REMOTE_SERV_VAL)
```
These are just two ways to define the same UUID, which we will use later. Now, open remote.c, and let us look into how we can start advertising.

If you inspect the GAP API you will find [bt_le_adv_start](https://docs.nordicsemi.com/bundle/ncs-2.6.2/page/zephyr/connectivity/bluetooth/api/gap.html#c.bt_le_adv_start), which is, as the function name states, the function we need to start advertising. It sets advertisement data, scan respons data, advertisement parameters and finally it starts advertising.

The advertisement data and scan response data needs to be defined as a [bt_data struct](https://docs.nordicsemi.com/bundle/ncs-2.6.2/page/zephyr/connectivity/bluetooth/api/gap.html#c.bt_data) constructed in a certain way. In addition we will use `CONFIG_BT_DEVICE_NAME` which we've already defined to advertise our devices name.

Add this a suitable place, near the top, in remote.c:

```C
#define DEVICE_NAME CONFIG_BT_DEVICE_NAME
#define DEVICE_NAME_LEN (sizeof(DEVICE_NAME)-1)
```
and open prj.conf and replace the name of 

*[CONFIG_BT_DEVICE_NAME](https://docs.nordicsemi.com/bundle/ncs-2.6.2/page/kconfig/index.html#CONFIG_BT_DEVICE_NAME).="Remote_controller"*

with something custom for your device.

### Prepare the advertise packet
Declare an array `ad[]` and `sd[]` of type [struct bt_data](https://docs.nordicsemi.com/bundle/ncs-2.6.2/page/zephyr/connectivity/bluetooth/api/gap.html#c.bt_data). It should look like this


```C
static const struct bt_data ad[] = {

};

static const struct bt_data sd[] = {

};
```
The next we want to do is to populate it using the helper macro [BT_DATA_BYTES()](https://developer.nordicsemi.com/nRF_Connect_SDK/doc/latest/zephyr/connectivity/bluetooth/api/gap.html#c.BT_DATA_BYTES). We also want to use the helper macro [BT_DATA()](https://developer.nordicsemi.com/nRF_Connect_SDK/doc/latest/zephyr/connectivity/bluetooth/api/gap.html#c.BT_DATA). Open the documentation for `BT_DATA_BYTES()` and `BT_DATA()` and have a look at how they are defined.

In this exercise we want to advertise that we are
* A [general discoverable](https://developer.nordicsemi.com/nRF_Connect_SDK/doc/latest/zephyr/connectivity/bluetooth/api/gap.html#c.BT_LE_AD_GENERAL) device  
* We only supports Low Energy Bluetooth through [BT_LE_AD_NO_BREDR](https://developer.nordicsemi.com/nRF_Connect_SDK/doc/latest/zephyr/connectivity/bluetooth/api/gap.html#c.BT_LE_AD_NO_BREDR) (since Nordic’s products only support Bluetooth LE, this flag should always be set to this value)
* We want to advertise the devices complete local name through [BT_DATA_NAME_COMPLETE](https://developer.nordicsemi.com/nRF_Connect_SDK/doc/latest/zephyr/connectivity/bluetooth/api/gap.html#c.BT_DATA_NAME_COMPLETE).

In our scan response pack we want to have
* our custom remote service which is a [BT_DATA_UUID128_ALL](https://developer.nordicsemi.com/nRF_Connect_SDK/doc/latest/zephyr/connectivity/bluetooth/api/gap.html#c.BT_DATA_UUID128_ALL).

Now this might seem like a lot of magic and strange names and all such things, and it is if you're not familiar with the APIs, but all the parameters and types we've mentioned comes from the specification and are defined through the various APIs created for Bluetooth. 

You can try and fill in the parameters on your own, but the solution requires that your ad and sd structs should look like this:

```C
static const struct bt_data ad[] = {
    BT_DATA_BYTES(BT_DATA_FLAGS, (BT_LE_AD_GENERAL | BT_LE_AD_NO_BREDR)),
    BT_DATA(BT_DATA_NAME_COMPLETE, DEVICE_NAME, DEVICE_NAME_LEN)
};

static const struct bt_data sd[] = {
    BT_DATA_BYTES(BT_DATA_UUID128_ALL, BT_UUID_REMOTE_SERV_VAL),
};
```

We've now set up everything we need for [bt_le_adv_start](https://developer.nordicsemi.com/nRF_Connect_SDK/doc/latest/zephyr/connectivity/bluetooth/api/gap.html#group__bt__gap_1gad2e3caef88d52d720e8e4d21df767b02).

To your bluetooth init, after you've taken the semaphore from bt_enable, add the following:

```C
/* This snippet belongs in bluetooth_init() in remote.c */
    LOG_INF("Starting advertising");
    err = bt_le_adv_start(BT_LE_ADV_CONN, ad, ARRAY_SIZE(ad), sd, ARRAY_SIZE(sd));
    if (err){
        LOG_ERR("couldn't start advertising (err = %d", err);
        return err;
    }
```

Now your device should advertise if you flash it with the latest build. Open nRF Connect for iOS or Android and start scanning for the device. If there are many BLE devices nearby, try to sort by RSSI (Received Signal Strength Indicator), or ad a filter to the advertising name. 

Scan using nRF Connect for Mobile (Android) | Listed UUIDs | 
------------ | ------------ |
<img src="https://github.com/aHaugl/OV_Orbit_BLE_Course/blob/main/images/Step4.0.png" width="300"> | <img src="https://github.com/aHaugl/OV_Orbit_BLE_Course/blob/main/images/Step4.1.png" width="300"> |

If you select this device, you should be able to see some information from the advertisements. The name should appear as we set it in our prj.conf, and the service should match the service UUID should be visible, and match the service UUID that we defined in remote.h.

You should see that you can actually connect to your device as well, since we claimed in the `BT_LE_ADV_CONN` (from bt_le_adv_start()) that we are connectable. However, if you try to connect to it, you will see that other than the Generic Attribute and the Generic Access services, we don't actually have the custom service that we claimed to have in the our advertising packet (Listed as "Advertised Services"). We will fix that later, but first, let us try to inform our application that something actually connected to us. The next part will use some elements from [Lesson 3](https://academy.nordicsemi.com/courses/bluetooth-low-energy-fundamentals/lessons/lesson-3-bluetooth-le-connections/) in the Bluetooth course, and I recommend that you have a closer look at this lesson to capture the concept of BLE connections in greater detail.

We want to receive these events in our main.c file, so that we can keep track of the state of our device. Let us start by adding a struct containing the callbacks in main.c:

```C
struct bt_conn_cb bluetooth_callbacks = {
	.connected 	= on_connected,
	.disconnected 	= on_disconnected,
};
```

Try "control clicking" bt_conn_cb, or go to [struct bt_conn_cb](https://developer.nordicsemi.com/nRF_Connect_SDK/doc/latest/zephyr/connectivity/bluetooth/api/connection_mgmt.html#c.bt_conn_cb) on the documentation pages, to see what callback types the .connected and .disconnected callback events are to understand why they have the function parameters that they have. The function parameters I'm referring to are

```C
void (*connected)(struct bt_conn *conn, uint8_t err)
```

and 

```C
void (*disconnected)(struct bt_conn *conn, uint8_t reason)
```

We will use these functions to print to our log that we are connected, and to set a connection pointer that we use to keep track of whether or not we are in a connection. Because the callbacks are triggered from the Bluetooth libraries, it is important that they have the same function parameters as described in the documentation of the API linked above.

Near top of main.c (after bluetooth_callbacks struct) add the following:

```C
/* Near top of main.c (after bluetooth_callbacks struct) */

static struct bt_conn *current_conn;    // Used to keep track of current connection status.
/* Declaration of on_connected and on_disconnected
void on_connected(struct bt_conn *conn, uint8_t err);
void on_disconnected(struct bt_conn *conn, uint8_t reason);

/* Callbacks, also in main.c: */

void on_connected(struct bt_conn *conn, uint8_t err)
{
    if (err) {
        LOG_ERR("connection failed, err %d", err);
    }
    current_conn = bt_conn_ref(conn);
    dk_set_led_on(CONN_STATUS_LED);
}

void on_disconnected(struct bt_conn *conn, uint8_t reason)
{
	LOG_INF("Disconnected (reason: %d)", reason);
	dk_set_led_off(CONN_STATUS_LED);
	if(current_conn) {
		bt_conn_unref(current_conn);
		current_conn = NULL;
	}
}
```

and near the top of your code define a CONN_STATUS_LED to indicate our connection status

```C
#define CONN_STATUS_LED DK_LED2
```

Although it may not be completely clear, what you need to know here is that we fetch a connection reference from the connection event. We will use this later. When we disconnect we remove this reference, and set the current_conn parameter back to a NULL-pointer.


**Challenge:** </br>
***Forward these callbacks (the bluetooth_callbacks parameter) to bluetooth init, and use bt_conn_cb_register() to register them to our Bluetooth stack. Do so before you call bt_enable(). In order to forward the bluetooth_callbacks I suggest that you make the bluetooth_init() function take them in as a pointer. If you are stuck, you will find a solution below.***


</br>
</br>

If you're now trying to connect to your device using nRF Connect for iOS and connect to a terminal you may see a warning stating `Ignoring data for unknown channel ID 0x003a`. You can safely disregard this warning message. Apple devices will initiate this request after connection is established, but it will always be ignored by our stack. 

If you followed the guide this far, your files should look something like [this](https://github.com/aHaugl/OV_Orbit_BLE_Course/tree/main/temp_files/Step_4.1
_sol). You can use this in case you got stuck somewhere. Please note that I also added some new code to the connected and disconnected events in main.c, and a current_conn parameter to keep track of the current connection. 

</br>

## Step 5 - Adding our first Bluetooth Service
Let us add the service that we claim that we have when we advertise. We will use the macro [BT_GATT_SERVICE_DEFINE](https://developer.nordicsemi.com/nRF_Connect_SDK/doc/latest/zephyr/connectivity/bluetooth/api/gatt.html#c.BT_GATT_SERVICE_DEFINE) to add our service. It is quite simple at the same time as it is quite complex. When we use this macro to create and add our service, the rest is done "under the hood" of NCS/Zephyr. By just adding this snippet to remote.c:


```C
/* This code snippet belongs to remote.c */
BT_GATT_SERVICE_DEFINE(remote_srv,
BT_GATT_PRIMARY_SERVICE(BT_UUID_REMOTE_SERVICE),
);
```

And voila! We have our first Bluetooth Low Energy service. Try to connect to it using nRF Connect, and see that you can see the service.

Our first service Android | Our first service iOS | 
------------ | ------------ |
<img src="https://github.com/aHaugl/OV_Orbit_BLE_Course/blob/main/images/Step4.2.png" width="300"> | <img src="https://github.com/aHaugl/OV_Orbit_BLE_Course/blob/main/images/iOS/custom_service_mobile.jpg" width="300"> |

However, a service without any characteristics isn't very impressive. Let us add a characteristic that we can read from our Central. We start by defining a new UUID for our characteristic. Basically, you can copy your previous UUID define and increment the two bytes that you set to 0001 to 0002:

```C
/* This code snippet belongs to remote.h */
/** @brief UUID of the Button Characteristic. **/
#define BT_UUID_REMOTE_BUTTON_CHRC_VAL \
	BT_UUID_128_ENCODE(0xe9ea0002, 0xe19b, 0x482d, 0x9293, 0xc7907585fc48)
```

```C
/* This code snippet belongs to remote.h */
#define BT_UUID_REMOTE_BUTTON_CHRC 	BT_UUID_DECLARE_128(BT_UUID_REMOTE_BUTTON_CHRC_VAL)
```

I called my handle BT_UUID_REMOTE_BUTTON_CHRC. Whatever you call it, we will now add it to our service macro:

```C
/* Add this to the service macro we previously defined in remote.c */
BT_GATT_SERVICE_DEFINE(remote_srv,
BT_GATT_PRIMARY_SERVICE(BT_UUID_REMOTE_SERVICE),
    BT_GATT_CHARACTERISTIC(BT_UUID_REMOTE_BUTTON_CHRC,
                    BT_GATT_CHRC_READ,
                    BT_GATT_PERM_READ,
                    read_button_characteristic_cb, NULL, NULL),
);
```
Note that the read_button_characteristic_cb is undefined at this point in time. We will implement this callback in the next few sections of the hands on.

What we are doing here is saying that we want to add a characteristic to our service using the UUID that we just defined. We claim that it is possible to read it, and then we give it the permission to be read. The read_button_characteristic is a callback that is triggered whenever someone is reading our characteristic. The first NULL is the callback for when someone is writing to our characteristic, which will never happen since it is not possible to write to this characteristic. The last NULL is the actual value. We will set that later. 
</br>

Now we need to implement the `read_button_characteristic_cb` callback function. It is a bit tricky to navigate to the callback definition of this macro, but if you look in `gatt.h`, where the [`BT_GATT_CHARACTERISTIC`](https://docs.nordicsemi.com/bundle/ncs-2.6.2/page/zephyr/connectivity/bluetooth/api/gatt.html#c.BT_GATT_CHARACTERISTIC) macro is defined, and search for "[`struct bt_gatt_attr`](https://docs.nordicsemi.com/bundle/ncs-2.6.2/page/zephyr/connectivity/bluetooth/api/gatt.html#c.bt_gatt_attr)" then this will hold the callbacks that we will use for read, and later for write callbacks. </br>

So we see that the read callback should look something like [bt_gatt_attr_read_func_t](https://docs.nordicsemi.com/bundle/ncs-2.6.2/page/zephyr/connectivity/bluetooth/api/gatt.html#c.bt_gatt_attr_read_func_t), i.e something like:

```C
typedef ssize_t (*read)(struct bt_conn *conn, const struct bt_gatt_attr *attr, void *buf, uint16_t len, uint16_t offset)
```

Replace (*read) with the name we passed in BT_GATT_CHARACTERISTIC and return the return value from bt_gatt_attr_read():

```C
ssize_t bt_gatt_attr_read(struct bt_conn *conn, const struct bt_gatt_attr *attr,
			  void *buf, uint16_t buf_len, uint16_t offset,
			  const void *value, uint16_t value_len)
```

We need this function to return the length of the value being read, and it needs to be returned using bt_gatt_attr_read().

```C
/* This snippet belongs in remote.c */
static uint8_t button_value = 0;

static ssize_t read_button_characteristic_cb(struct bt_conn *conn, const struct bt_gatt_attr *attr,
                                            void *buf, uint16_t len, uint16_t offset)
{
    return bt_gatt_attr_read(conn, attr, buf, len, offset, &button_value, sizeof(button_value));
}

```

**Challenge:**

<br>

***Before we try to connect again, create a function in remote.c that we can call from main.c (add declaration in remote.h) that changes the value of the parameter `button_value` based on an input parameter. Call it "set_button_value()" and call it in the button_handler from main.c, with the button_pressed parameter as the input.***

Now, try to connect to your device using nRF Connect, and see that you have a characteristic that you can read using the read button in nRF Connect (the button with the down pointing arrow). Whenever you push a button on your DK and read it again, you should see that the is updated. The items we've covered in this part and in the next part of the hands on exercise is largely expanded upon in [Lesson 4](https://academy.nordicsemi.com/courses/bluetooth-low-energy-fundamentals/lessons/lesson-4-bluetooth-le-data-exchange/) in the Bluetooth course on DevAcademy, so have a look at this after the hands on to inspect this topic closer.

</br>

If you are stuck you can have a look at the [partial solution for this step](https://github.com/aHaugl/OV_Orbit_BLE_Course/tree/main/temp_files/Step_4.2_sol)

</br>

## Step 6 - Characteristic Notifications
We do not want to keep having to ask our peripheral about the last pressed button all the time. It requires a lot of read requests and read response packets on the air, which is not very power efficient. Therefore we have something called "notifications", which allows the peripheral to push changes to the central whenever they occur. This is set using something called Client Characteristic Configuration Descriptor (CCCD or CCC). The first thing we need to do is to add this descriptor to our characteristic. Do this by adding the last line to your Service macro in remote.c:

```C
/* This code snippet belongs to remote.c */
BT_GATT_SERVICE_DEFINE(remote_srv,
BT_GATT_PRIMARY_SERVICE(BT_UUID_REMOTE_SERVICE),
    BT_GATT_CHARACTERISTIC(BT_UUID_REMOTE_BUTTON_CHRC,
                    BT_GATT_CHRC_READ | BT_GATT_CHRC_NOTIFY,
                    BT_GATT_PERM_READ,
                    read_button_characteristic_cb, NULL, NULL),
    BT_GATT_CCC(button_chrc_ccc_cfg_changed, BT_GATT_PERM_READ | BT_GATT_PERM_WRITE),
);
```

**Note that we added  |[`BT_GATT_CHRC_NOTIFY`](https://docs.nordicsemi.com/bundle/ncs-2.6.2/page/zephyr/connectivity/bluetooth/api/gatt.html#c.BT_GATT_CHRC_NOTIFY) on the line that previously just said [`BT_GATT_CHRC_READ`](https://docs.nordicsemi.com/bundle/ncs-2.6.2/page/zephyr/connectivity/bluetooth/api/gatt.html#c.BT_GATT_CHRC_READ).**

The first parameter is a callback that is triggered whenever someone writes to the CCC. The last parameter is the read/write permissions. Here we allow the central to both read and write to this configuration. This means that it can check whether or not notifications are enabled, and enable/disable it. Please note that we also added the `BT_GATT_CHRC_NOTIFY` in our properties for the characteristic itself, as we are now adding the possiblilty to enable notifications.

In a similar way to what we did earlier, we can use the BT_GATT_CCC macro definition to find the expected type of callback. See if you can find it in gatt.h or in the [GATT API documentation pages](https://docs.nordicsemi.com/bundle/ncs-2.6.2/page/zephyr/connectivity/bluetooth/api/gatt.html#c.BT_GATT_CHRC_READ) </br></br>
*Hint: it is a callback that is called whenever the CCC has changed*
</br></br>
The implementation of this callback itself is not that complex. We don't have to return anything. We'll just log that notifications were either enabled or disabled. 

```C
 /* This code snippet belongs to remote.c */
void button_chrc_ccc_cfg_changed(const struct bt_gatt_attr *attr, uint16_t value)
{
    bool notif_enabled = (value == BT_GATT_CCC_NOTIFY);
    LOG_INF("Notifications %s", notif_enabled? "enabled":"disabled");

}
```

The aim of this callback is to keep track of whether or not the central has enabled notifications. We would like to propagate this event to our main.c file. In order to keep things tidy, let us create an Enum that says whether notifications was enabled or disabled, and we want a callback struct similar to the one that we used to receive the connected and disconnected events. The only difference in this callback struct is that since this is a custom service, we need to implement these callbacks ourself.
</br>
Let us start by adding the enum:

```C
/* This code snippet belongs to remote.h */
enum bt_button_notifications_enabled {
	BT_BUTTON_NOTIFICATIONS_ENABLED,
	BT_BUTTON_NOTIFICATIONS_DISABLED,
};
```

Then let us declare our callback struct. Since we create this from scratch, we can call it whatever we like:

```C
/* This code snippet belongs to remote.h */
struct bt_remote_service_cb {
	void (*notif_changed)(enum bt_button_notifications_enabled status);
};
```

So far the only function that we want to forward is the notif_changed, which we will use to forward the callback whenever notifications are enabled or disabled. In order to do so, we will need an instance of the struct in remote.c as well:

```C
/* This code snippet belongs to remote.c */
static struct bt_remote_service_cb remote_service_callbacks;
```

And finally an instance actually containing the callbacks in main.c:

```C
/* This code snippet belongs to main.c */
struct bt_remote_service_cb remote_callbacks = {
	.notif_changed = on_notif_changed,
};
```

Then we need to forward this remote_callbacks struct into bluetooth_init similar to the way we did with the bluetooth_callbacks struct.

Then inside bluetooth_init() in remote.c we will first check that they are not NULL pointers, and then populate them manually:

```C
/* This code snippet belongs to remote.c */
    int err;
    LOG_INF("Initializing Bluetooth");

    if (bt_cb == NULL || remote_cb == NULL) {
        return NRFX_ERROR_NULL;
    }
    bt_conn_cb_register(bt_cb);
    remote_service_callbacks.notif_changed = remote_cb->notif_changed;
    ...
```
And modify bluetooth_init() to also take &remote_cb as an argument, i.e match your existing bluetooth_init to the following

```C
int bluetooth_init(struct bt_conn_cb * bt_cb, struct bt_remote_service_cb *remote_cb)
```
Also remember to change the declaration in remote.h.

now that we have this callback struct in remote.c, it means we can trigger the callback in main.c from remote.c. Add the following to button_chrc_ccc_cfg_changed():

```C
/* This code snippet belongs to remote.c */
void button_chrc_ccc_cfg_changed(const struct bt_gatt_attr *attr, uint16_t value)
{
    bool notif_enabled = (value == BT_GATT_CCC_NOTIFY);
    LOG_INF("Notifications %s", notif_enabled? "enabled":"disabled");
    if (remote_service_callbacks.notif_changed) {
        remote_service_callbacks.notif_changed(notif_enabled?BT_BUTTON_NOTIFICATIONS_ENABLED:BT_BUTTON_NOTIFICATIONS_DISABLED);
    }
}
```

The reason we check the `if (remote_service_callback.notif_changed)` is that we need to check that this very callback function (notif_changed) is set before we call it. Now all we need is to implement the on_notif_changed() function in main.c. All we need it to do is to print that notifications are enabled or disabled:

```C
/* This code snippet belongs to main.c */
void on_notif_changed(enum bt_button_notifications_enabled status)
{
    if (status == BT_BUTTON_NOTIFICATIONS_ENABLED) {
        LOG_INF("Notifications enabled");
    } else {
        LOG_INF("Notifications disabled");
    }
}
```



</br>
Now we are only a few steps away from sending our very first notification (!!).
Let us add a function, send_button_notification(), in remote.c that we can call from main.c (remember to declare it in remote.h). 

```C
/* This code snippet belongs to remote.c */
void on_sent(struct bt_conn *conn, void *user_data)
{
    ARG_UNUSED(user_data);
    LOG_INF("Notification sent on connection %p", (void *)conn);
}

int send_button_notification(struct bt_conn *conn, uint8_t value)
{
    int err = 0;

    struct bt_gatt_notify_params params = {0};
    const struct bt_gatt_attr *attr = &remote_srv.attrs[2];

    params.attr = attr;
    params.data = &value;
    params.len = 1;
    params.func = on_sent;

    err = bt_gatt_notify_cb(conn, &params);

    return err;
}
```

This one is a lot to take in, but let us see what is going on: In send_button_notification we take two input parameters. The pointer to the connection that we want to send the notification to, and the value of the characteristic, which is the actual payload data being transmitted. If you were to implement this from scratch, start by using the function bt_gatt_notify_cb() and look at what parameters it takes. The params parameter is the struct bt_gatt_notify_params. It holds a lot, but we only populate what we need in our case. We need the attribute, which points to the characteristic where we are actually sending the notification, and we need the value, the length of the value, and a callback function. This callback may be very useful in some cases where you are sending a lot of data, to keep track on when the data is sent. We will just use it to print that we have successfully sent a notification.

</br>

Now try to call this function from the button handler, check the return value and see if you can send a notification from your peripheral to the connected central. Remember to enable notifications on the characteristic from your phone by pressing the button with the three arrows pointing down.

</br>

## Step 7 - Writing Back to our Peripheral
So now we can send button presses from our remote to our phone. Pretty cool. But since we have a wireless device connected to our phone, and this device has a motor connected to it, it would be nice to be able to control the motor from the phone, right? For this we could use the same characteristic that we already have to send communications both ways, but let us create a new characteristic for this purpose.

**Challenge:**</br>
***Add a third UUID where you increment the byte that we did for the previous UUID once more. Call the UUID BT_UUID_REMOTE_MESSAGE_CHRC_VAL and call the characteristic handle BT_UUID_REMOTE_MESSAGE_CHRC***

Let us add the new characteristic to our service macro:

```C
/* This code snippet belongs to remote.c */
BT_GATT_SERVICE_DEFINE(remote_srv,
BT_GATT_PRIMARY_SERVICE(BT_UUID_REMOTE_SERVICE),
    BT_GATT_CHARACTERISTIC(BT_UUID_REMOTE_BUTTON_CHRC,
                    BT_GATT_CHRC_READ | BT_GATT_CHRC_NOTIFY,
                    BT_GATT_PERM_READ,
                    read_button_characteristic_cb, NULL, NULL),
    BT_GATT_CCC(button_chrc_ccc_cfg_changed, BT_GATT_PERM_READ | BT_GATT_PERM_WRITE),
    BT_GATT_CHARACTERISTIC(BT_UUID_REMOTE_MESSAGE_CHRC,
                    BT_GATT_CHRC_WRITE_WITHOUT_RESP,
                    BT_GATT_PERM_WRITE,
                    NULL, on_write, NULL),
);
```

We have seen this before. We are adding a characteristic to our old service, we claim that the central can write to it, and we give the central the permission to write to it. We don't need a read callback, but we add the `on_write` callback. We do not care about the start value of the characteristic as it is not possible for the central to read it.
</br>
</br>
What remains is to implement our on_write callback. This is a typical callback you would want to propagate to main.c, as in a commercial product, we want to control some other peripherals (PWM) depending on the content of the message from the central. Luckily we already have a way of forwarding events from remote.c to our main.c file. Let us add another event callback in our bt_remote_service_cb struct in remote.h:

```C
/* This code snippet belongs to remote.h */
struct bt_remote_service_cb {
	void (*notif_changed)(enum bt_button_notifications_enabled status);
	void (*data_received)(struct bt_conn *conn, const uint8_t *const data, uint16_t len);
};
```

The parameters that we pass on into our data_received event is totally up to you. For now we will pass the connection pointer, the actual data, and the length of the data. Now we add it to our main.c instance of our remote service callbacks:

```C
/* This code snippet belongs to main.c */
struct bt_remote_service_cb remote_callbacks = {
    .notif_changed = on_notif_changed,
    .data_received = on_data_received,
};
```
Then we need to remember to populate this callback in bluetooth_init():

```C
/* This code snippet belongs to remote.c -> bluetooth_init() */
    bt_conn_cb_register(bt_cb);
    remote_service_callbacks.notif_changed = remote_cb->notif_changed;
    remote_service_callbacks.data_received = remote_cb->data_received;
```

Before we implement the callback in main, let us look at the callback in remote.c. As we saw in the start of this tutorial, it is a bit tricky to find the callback type for the write and read callbacks. Look for the definition of the "struct bt_gatt_attr" in gatt.h, and look at the `(*write)` type. There are a lot of parameters, so let us look into them.

You can see that there are a lot of parameters, but all we really need to do is to forward the important ones to our custom callback and return the length of the message (telling the stack that we have handled the entire message).
To remote.c add the following:
```C
/* This snippet belongs to remote.c*/
static ssize_t on_write(struct bt_conn *conn,
			  const struct bt_gatt_attr *attr,
			  const void *buf,
			  uint16_t len,
			  uint16_t offset,
			  uint8_t flags)
{
    LOG_INF("Received data, handle %d, conn %p",
        attr->handle, (void *)conn);

    if (remote_service_callbacks.data_received) {
        remote_service_callbacks.data_received(conn, buf, len);
    }
    return len;
}
```


Finally, in order to print the message in main.c, you can add the following:

```C
/* This code snippet belongs to main.c */
void on_data_received(struct bt_conn *conn, const uint8_t *const data, uint16_t len)
{
    uint8_t temp_str[len+1];
    memcpy(temp_str, data, len);
    temp_str[len] = 0x00;

    LOG_INF("Received data on conn %p. Len: %d", (void *)conn, len);
    LOG_INF("Data: %s", temp_str);
}
``` 

What we are doing here is first that we copy the content of the data pointer to a temporary string. This is not strictly necessary, but in this case we want to print the data to the log, and one way to do that is to use the log_strdup() which is looking for a zero-terminated string. To avoid writing to the actual data buffer (which is a very bad idea) we copy the content and add a 0x00 byte at the end.
Then we print who sent the data, the length of the data, and the actual message. 

<br>

Try to write to your new characteristic. Note that when you press the write button (button with upwards pointing arrow), you need to select whether you want to write raw bytes using "ByteArray", or if you want to send a string of data using "UTF8". You can also use Bool or UnsignedInt, but that is not something we need to use. 

Writing to a Characteristic | 
------------ |
<img src="https://github.com/edvinand/OmegaV_BLE_Course/blob/main/images/write_to_characteristic.jpg" width="300"> |

<br>

But we said that we wanted to control our motors using these messages. Try to check the incoming data, and use this to control the motor. To check the first byte of the data, you can use `data[0]`. Try to set the motor in different positions depending on the first byte of the message.


<br>

*Hint: Perhaps just check whether the first byte is 0x00 or 0x01, and set the motor to one of two predefined angles.*


You can find the final version of the files in the NCS project [here](https://github.com/edvinand/OmegaV_BLE_Course/tree/main/remote_controller/src).
