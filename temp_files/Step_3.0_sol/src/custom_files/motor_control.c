/* Step 3.2 - Add include motor_control.h*/

#include "motor_control.h"



/* Step 3.5 - Add log module */
#define LOG_MODULE_NAME motor_control
LOG_MODULE_REGISTER(LOG_MODULE_NAME); 

/* Step 3.10 - Add PWM_LED0 DT Alias */
#define PWM_LED0	DT_ALIAS(pwm_led0)

/* Step 3.11 - Initialize the PWM_LED0 instance*/
static const struct pwm_dt_spec pwm_led0 = PWM_DT_SPEC_GET(PWM_LED0);
/* Step 3.14 - Set the pwm period*/
#define PWM_PERIOD_NS 20000000

/* Step 3.4 - create a motor init funciton */
int motor_init(){
    int err = 0;
    /* Step 3.12 - Check if the device is ready */
    LOG_INF("Initializing Motor Control");
    if (!device_is_ready(pwm_led0.dev)) {
    LOG_ERR("Error: PWM device %s is not ready",
            pwm_led0.dev->name);
    return -EBUSY;
	}
    /* Step 3.13 - Set the pwm peripheral with pwm_set_dt */
    err = pwm_set_dt(&pwm_led0, PWM_PERIOD_NS, 1500000);
    if (err) {
        LOG_ERR("pwm_set_dt returned %d", err);
    }

    return err;
}