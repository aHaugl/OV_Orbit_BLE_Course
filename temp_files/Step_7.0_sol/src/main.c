/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>

/* Step 2.2 - Add log logging support */
#include <zephyr/logging/log.h>

/* Step 2.4 - Add  dk_buttons_and_leds.h*/
#include <dk_buttons_and_leds.h>
/* Step 2.9 - Add zephyr kernel*/
#include <zephyr/kernel.h>

/* Step 3.6 - include motor_control.h*/
#include "motor_control.h"
/* Step 4.10 - Include remote.h */
#include "remote.h"
/* Step 2.3 - Add log module */
#define LOG_MODULE_NAME app
LOG_MODULE_REGISTER(LOG_MODULE_NAME);

/* Step 2.8 - Specify blinking intervals for LED 1 */
#define RUN_STATUS_LED DK_LED1
#define RUN_LED_BLINK_INTERVAL 1000

/*Step 4.12 - Conn status LED */
#define CONN_STATUS_LED DK_LED2

/* Step 3.2.5  - Initialize the Servo Motor*/
#define SERVO_MOTOR    DT_NODELABEL(servo)
#define PWM_SERVO_MIN_DUTY_CYCLE  DT_PROP(SERVO_MOTOR, min_pulse)
#define PWM_SERVO_MAX_DUTY_CYCLE  DT_PROP(SERVO_MOTOR, max_pulse)

/* Step 4.1.10 - connected callbacks */
/* Near top of main.c (after bluetooth_callbacks struct) */
static struct bt_conn *current_conn;    // Used to keep track of current connection status.

/* Step 4.1.9 - Declare conn callbacks */
void on_connected(struct bt_conn *conn, uint8_t err);
void on_disconnected(struct bt_conn *conn, uint8_t reason);
/* Step 6.4 - Declare remote_callbacks */
void on_notif_changed(enum bt_button_notifications_enabled status);
/* Step 7.5 - declare on_data_received */
void on_data_received(struct bt_conn *conn, const uint8_t *const data, uint16_t len);

struct bt_conn_cb bluetooth_callbacks = {
	.connected 	= on_connected,
	.disconnected 	= on_disconnected,
};
/* Step 6.4 - add the remote callback for .notif_changed main.c*/
/* Step 7.2 - Add .data_received*/
struct bt_remote_service_cb remote_callbacks = {
    .notif_changed = on_notif_changed,
    .data_received = on_data_received,
};

/* Callbacks, also in main.c: */

void on_connected(struct bt_conn *conn, uint8_t err)
{
    if (err) {
        LOG_ERR("connection failed, err %d", err);
    }
	LOG_INF("In on_connected");
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
/* Step 6.6 - implement notif_changed */
/* This code snippet belongs to main.c */
void on_notif_changed(enum bt_button_notifications_enabled status)
{
    if (status == BT_BUTTON_NOTIFICATIONS_ENABLED) {
        LOG_INF("Notifications enabled");
    } else {
        LOG_INF("Notifications disabled");
    }
}
/* Step 7.5 - Add on_data_received */
/* This code snippet belongs to main.c */
void on_data_received(struct bt_conn *conn, const uint8_t *const data, uint16_t len)
{
    uint8_t temp_str[len+1];
    memcpy(temp_str, data, len);
    temp_str[len] = 0x00;

    LOG_INF("Received data on conn %p. Len: %d", (void *)conn, len);
    LOG_INF("Data: %s", temp_str);
}
/* Step 2.12 - Set up the callback function for the button handler */
void button_handler(uint32_t button_state, uint32_t has_changed)
{
	int button_pressed = 0;
	int err = 0;
	if (has_changed & button_state)
	{
		switch (has_changed)
		{
			case DK_BTN1_MSK:
				button_pressed = 1;
				
				err = set_motor_angle(PWM_SERVO_MIN_DUTY_CYCLE);
				break;
			case DK_BTN2_MSK:
				button_pressed = 2;
				err = set_motor_angle(PWM_SERVO_MAX_DUTY_CYCLE);
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
		/*Step 5.6 challenge: call set_button_pressed from button handler*/
		set_button_press(button_pressed);
		err = send_button_notification(current_conn, button_pressed);
		if (err){
			LOG_ERR ("Couldn't send notification (err: %d)", err);
		}
	}
}

/* Step 2.5 - Define button_configure */
static void configure_dk_buttons_and_leds(void){
	/* Step 2.6 - Initialize DK and LEDs with dk_leds_init() */
	int err;
	err = dk_leds_init();
	if (err){
		LOG_ERR("Couldn't init LEDS (err % d)", err);
	}

	/* Step 2.11 - Set up the button initalization function */
	err = dk_buttons_init(button_handler);
	if (err){
		LOG_ERR("Couldn't init buttons (err %d)", err);
	}
}

int main(void)
{
	/* Step 2.10 - check if the LED blinks */
	int err = 0;
	bool blink_status = false;

	printf("Hello World! %s\n", CONFIG_BOARD);

	configure_dk_buttons_and_leds();

	/* Step 3.7 - Call motor init */
	err = motor_init();
    if (err) {
        LOG_ERR("motor_init() failed. (err %d)", err);
    }
	err = bluetooth_init(&bluetooth_callbacks, &remote_callbacks);
    if (err) {
        LOG_ERR("Bluetooth_init() failed. (err %d)", err);
    }
	
	for (;;){
		dk_set_led(RUN_STATUS_LED, (blink_status));
		blink_status = !blink_status;
		k_sleep(K_MSEC(RUN_LED_BLINK_INTERVAL));

	}

	return 0;
}
