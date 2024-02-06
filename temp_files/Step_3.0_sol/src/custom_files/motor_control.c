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
