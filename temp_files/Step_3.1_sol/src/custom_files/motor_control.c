/* Step 3.2 - Add include motor_control.h*/

#include "motor_control.h"



/* Step 3.5 - Add log module */
#define LOG_MODULE_NAME motor_control
LOG_MODULE_REGISTER(LOG_MODULE_NAME); 

/* Step 3.10 - Add PWM_LED0 DT Alias */
#define SERVO_MOTOR	DT_ALIAS(pwm_led0)

/* Step 3.11 - Initialize the PWM_LED0 instance*/
static const struct pwm_dt_spec pwm_servo = PWM_DT_SPEC_GET(SERVO_MOTOR);
/* Step 3.14 - Set the pwm period*/
#define PWM_PERIOD_NS 20000000

/* Step 3.4 - create a motor init funciton */
int motor_init(void)
{
    int err = 0;
    LOG_INF("Initializing Motor Control");

    if (!device_is_ready(pwm_servo.dev)) {
    LOG_ERR("Error: PWM device %s is not ready",
            pwm_servo.dev->name);
    return -EBUSY;
	}

    /* Initialize the motor position to be in the middle of max and min*/
    err = pwm_set_dt(&pwm_servo, PWM_PERIOD_NS, 1500000);
    if (err) {
        LOG_ERR("pwm_set_dt returned %d", err);
    }

    return err;
}
/* Step 3.1.6 - Set motor angle */
int set_motor_angle(uint32_t duty_cycle_ns){
    int err;
    err = pwm_set_dt(&pwm_servo, PWM_PERIOD_NS, duty_cycle_ns);
    if (err) {
        LOG_ERR("pwm_set_dt_returned %d", err);
    }
 
    return err;
}