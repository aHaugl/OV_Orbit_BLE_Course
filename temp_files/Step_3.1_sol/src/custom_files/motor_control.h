#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/pwm.h>


int motor_init(void);
int set_motor_angle(uint32_t duty_cycle_ns);
// void set_motor_angle(uint16_t angle);