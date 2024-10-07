/* Step 3.3 - add headers */ 

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

/* Step 3.9 - Include pwm drivers */
#include <zephyr/drivers/pwm.h>

int motor_init();
int set_motor_angle(uint32_t duty_cycle_ns);