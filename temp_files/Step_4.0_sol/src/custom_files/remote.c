/* Step 4.2 - add remote.h*/
#include "remote.h"


/* Step 4.3 - Add logging */
#define LOG_MODULE_NAME remote
LOG_MODULE_REGISTER(LOG_MODULE_NAME);

/* Step 4.9 - Create the semaphore */
static K_SEM_DEFINE(bt_init_ok, 0, 1);

/* Step 4.8 - Add bt_ready_callback CB*/
void bt_ready_callback(int err)
{
    if (err) {
        LOG_ERR("bt_enable returned %d", err);
    }
    k_sem_give(&bt_init_ok);
}

/* Step 4.5.2 - Implement bluetooth_init */
int bluetooth_init(struct bt_conn_cb * bt_cb)
{
    int err = 0;
    LOG_INF("Initializing Bluetooth");

    err = bt_enable(bt_ready_callback);
    if (err) {
        LOG_ERR("bt_enable() ret %d", err);
        return err;
    }
        
    k_sem_take(&bt_init_ok, K_FOREVER);

    return err;
}