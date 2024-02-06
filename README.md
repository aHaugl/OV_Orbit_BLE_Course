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

### Step 3 - Motor Control
The motor that we used is the Tower Pro MG90S. You can find a very simple datasheet [here](https://www.electronicoscaldas.com/datasheet/MG90S_Tower-Pro.pdf). For some background information on how PWM motors work, you can check out [this guide](https://www.jameco.com/Jameco/workshop/Howitworks/how-servo-motors-work.html), and these two samples in [this PWM sample repository](https://github.com/aHaugl/samples_for_NCS/tree/main/peripherals/pwm). We will do our implementation in this exercize similarly to what is done in the second exercise in the PWM repository mentioned.

Basically, we want to output a PWM signal, and the duty cycle of the PWM signal determines what angle/position the rotor will maintain. In our case, the motor wants a duty cycle between 1 and 2 ms, and a PWM period of 20ms. 

Because we want to keep main.c as clutter free as possible, we will try to do most of the PWM configurations and handling in another file, and implement some simple functions that we can call from main.c. Therefore we will add a couple of custom files. Inside your application folder (probably called `remote_controller`, you should see a folder named `src`. Inside this you will see your main.c file. Start by creating a new folder next to main.c called `custom_files`. You can either do this from Visual Studio Code, or you can do it from your Operative System's file explorer. Inside that folder, create two new files: `motor_control.h` and `motor_control.c`. To include these two files to your project, open `CMakeLists.txt` in Visual Studio Code and add the following
</br>
```C
# Custom files and folders

target_sources(app PRIVATE
    src/custom_files/motor_control.c
)

zephyr_library_include_directories(src/custom_files)
```

The line pointing to the `motor_control.c` file will include this .c file to your application project. The last line pointing to the folder `src/custom_files` will add that folder to the list of folders where the compiler will look for header files (.h files). 

If everything is done as intended, the project should compile, and we should be able to see our motor_control.c in our application tree as well as shown below. 

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
#include <zephyr.h>
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
<br>
In this hands on we will implement a PWM device two ways. The first way will be to add the PWM module to drive a LED GPIO, which can be configured to drive a PWM servo motor if you customize the devicetree files and pin controls as shown in the [PWM sample repo](https://github.com/aHaugl/samples_for_NCS/tree/main/peripherals/pwm) I referred to earlier, and the second way will be to drive the PWM servo motor through

If you wish to play around and learn and understand more about how to customize and use the PWM module in closer detail, feel free to have a look at the mentioned sample in your own time, but for this hands on you can follow along without doing so.

We will divide this into three parts.
* The first part will cover the common sections used in both method 1 and method 2
* The second part will show how we can use the PWM module to drive a LED and make it blink using the PWM duty cycle
* The third part will show you how to create a custom device with custom parameters that you can add to your devicetree and drive said custom device with the PWM module through any available GPIO.

When we are using the nRF Connect SDK, we have several driver options to control the PWM. We have our own drivers that are tailored for the Nordic Semiconductor devices, or we can use Zephyr's drivers, which will use Nordic's drivers "underneath the hood". For this course we will use Zephyr's PWM drivers. 

Let us start by adding some configurations to our prj.conf file:

**Enable the zephyr PWM driver**
```C
# PWM
CONFIG_PWM=y
CONFIG_PWM_LOG_LEVEL_DBG=y
```

What we are doig here is that we enable the PWM in our project, so that we can use it to control our motor. We will continue by adding the pwm header file near the top of `motor_control.h`. `motor_control.c` will inherit this, as long as it includes `motor_control.h`. Add near the top of motor_control.h:

```C
#include <zephyr/drivers/pwm.h>
```
The beauty of Zephyr drivers is that once we have enabled them through configurations in our prj.conf file, it will automagically be enabled and ready for use. 

Every nRF SoC has a set of peripherals available and every DK based on a nRF SoC has a set of predefined devices available. The nRF52840DK has among them multiple predefined PWM modules and one of them is the pwm_led that we can use to verify that we've set up our PWM module correctly. 

Under the devicetree tab in your applicaiton tree you can see the devicetree used for the current build. This board is selected from the list of boards found in [sdk_version/zephyr/boards/arm](https://github.com/nrfconnect/sdk-zephyr/tree/main/boards/arm), which is the nrf52840dk_nrf52840.dts in our case. 

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
Briefly explained, this is a device of the compatible type '[pwm-led](https://github.com/nrfconnect/sdk-zephyr/blob/main/dts/bindings/led/pwm-leds.yaml)', it has an alias, 'pwm_led0', and a name 'pwm_led_0'. It uses the 'pwms'-type instance which in this case is instance 0, has a duty cycle of 20 ms and inverted polarity. In method 2 we will create our own device similarly to how this binding has been created.

Throughout the two next sections we will be using this the 
), so keep this ready in addition to the .dts file.

<br>

## Method 1 - Use the PWM module to drive a LED
The first objective is to define and fetch this device from the .dts file into our .c files. We will do this using the [Devicetree API](https://docs.zephyrproject.org/latest/build/dts/api/api.html#devicetree-api) and the [PWM API documentation](https://docs.zephyrproject.org/latest/hardware/peripherals/pwm.html).

Under [node intentifiers and helpers](https://docs.zephyrproject.org/latest/build/dts/api/api.html#node-identifiers-and-helpers) you can find that there are various identifiers such as `DT_PATH()`, `DT_NODELABEL()`, `DT_ALIAS()`, and `DT_INST()`, and I mentioned that the pwmleds instance had an alias. Use `DT_ALIAS()` to define a PWM_LED0 device by adding the following near the top of main.c

```C
#define PWM_LED0	DT_ALIAS(pwm_led0)
```

<br> 

The next we want to do is to initialize this device with some properties using [PWM_DT_SPEC_GET](https://docs.zephyrproject.org/latest/hardware/peripherals/pwm.html#c.PWM_DT_SPEC_GET).

Near the top, but after the PWM_LED0 definition in motor_control.c initialize and populate your device with the parameters from the .dts file:

```C
static const struct pwm_dt_spec pwm_led0 = PWM_DT_SPEC_GET(PWM_LED0);
```

*Just for information, this is equivalent to:
```C
static const struct pwm_dt_spec pwm_led0 = PWM_DT_SPEC_GET(DT_ALIAS(pwm_led0));
```
or to [PWM_DT_SPEC_GET_BY_NAME(node_id, name)](https://docs.zephyrproject.org/latest/hardware/peripherals/pwm.html#c.PWM_DT_SPEC_GET_BY_NAME) given that your device has a name*

<\br>

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


**Challenge:** Before we connect our motor, let us try to generate a PWM signal using our LED. You can give this a go without looking at the solution below. Open pwm.h (ctrl + p, and search for pwm.h), and look at the description for pwm_set_dt(). Looking at our servo motor's [data sheet](https://www.electronicoscaldas.com/datasheet/MG90S_Tower-Pro.pdf), we see that we should have a period of 20ms, and a duty cycle between 1 and 2 ms. Try to set a PWM signal of 1.5ms, with a period of 20ms. 

*Hint: the `spec` parameter is our pwm_led0. Since it requires a pointer, you need to use `&pwm_led0` when you use it in pwm_set_dt().*

If you managed to set the duty cycle of 1.5ms, you should see a faint light on LED1 on your DK. That is good and all, but we originally used LED1 for something else (showing us that the main() loop was running), so ideally we want to use another pin for PWM control. To do this, we need to add something called an overlay file.

This is how my motor_control.c looks after this step:


## Overlay Files
As mentioned earlier all boards defined in Zephyr have their own board files containing all the information about the predefined devices on the board such as GPIOs, LEDs, pwm instances and their default configuration. We can make changes to the device tree files to change e.g what pins are used for LEDs, but making changes directly to a .dts file will cause *every other project that uses these board files to also use the same configuration*. So to keep a good project-to-code-base-separation we will be using overlay files instead.


An overlay file is as the name implies: A file that lays itself over the top of the device tree or project configurations and is tailored to this specific type of device. The way that it works is that the compiler will first read the board file (.dts file), and then it will look for an overlay file. If it finds one, then all the settings found in the .overlay file will overwrite the default settings from the .dts file, but only for the current project. This way we can have multiple devices sharing a foundational code base where each device becomes unique through its own custom .overlay file

Managing multiple applications through overlay files | 
------------ |
<img src="https://github.com/aHaugl/OV_Orbit_BLE_Course/blob/main/images/Step3.4.png" width="1000"> |


</br>
Start by creating a file called `nrf52840dk_nrf52840.overlay`. You can do this by clicking the "No overlay files detected, click here to create one" button under Config files and Devicetree in the Application tree in the VS Code extension. This will create a .overlay file with the same name as the board selected for the build in your project folder on the same level as the `prj.conf` and `CMakeLists.txt` file. You can also create this file manually but make sure that it follows the mentioned naming and location convention.
</br>

If you've managed to drive one of the LEDs with a PWM instance and set up the .overlay file as described you can now either choose to do the optional steps for  . If you wish, you can do the optional steps under Method 1 will show you how to create a custom PWM device and select which GPIO it should drive through the means of using the pwm_led compatible and pin control, while Method 2 will show you how to do the same *but* by defining and creating your own custom device through a .yml. I personally recommend you to do method 2 and if you have time you can go through the steps to do method 1.

If you're struggling at this point in time, please feel free to have a look at the solution for this point in time located in the [temp_files](https://github.com/aHaugl/OV_Orbit_BLE_Course/tree/main/temp_files/Step_3.0_sol). `Step_3.0_sol` works as a jump start for both method 1 and method 2.

# Optional steps for Method 1: Use the pwm_led to drive the motor


If you open your nrf52840dk_nrf52840.dts, which is our standard board file, we can see what pwm_led0 looks like by default:

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

As mentioned, we don't want to change anything inside this file, because those changes will stick to all other projects that are using the same board file. This is why we want to do the changes in our overlay file. Unfortunately, the pin number is not set here directly. It is set in &pwm0 inside pwm_led0. But since the default configuration for pwm_led0 is PWM_POLARITY_INVERTED, and we want to change that as well, we need to add the pwmleds snippet to our overlay file as well. 
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

You can call them whatever you like. I used pwm0_custom and pwm0_csleep. The last part we need to do is that we need to define pwm0_custom and pwm0_csleep. Try right clicking the pwm0_default and pwm0_sleep in the .dts file to see hwat they look like by default:

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
&i2c0 {
    status = "okay";
    compatible = "nordic,nrf-twim";
    clock-frequency = < I2C_BITRATE_STANDARD >;
};

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

If you are having problems with controlling the motors, you can have a look at what my motor_control.h and motor_control.c looks like at this point in time:


## Method 2 - Create a custom motor device and use the PWM module to drive a motor


