#include "remote.h"

#define LOG_MODULE_NAME remote
LOG_MODULE_REGISTER(LOG_MODULE_NAME);

static K_SEM_DEFINE(bt_init_ok, 0, 1);

#define DEVICE_NAME CONFIG_BT_DEVICE_NAME
#define DEVICE_NAME_LEN (sizeof(DEVICE_NAME)-1)

static const struct bt_data ad[] = {
    BT_DATA_BYTES(BT_DATA_FLAGS, (BT_LE_AD_GENERAL | BT_LE_AD_NO_BREDR)),
    BT_DATA(BT_DATA_NAME_COMPLETE, DEVICE_NAME, DEVICE_NAME_LEN)
};

static const struct bt_data sd[] = {
    BT_DATA_BYTES(BT_DATA_UUID128_ALL, BT_UUID_REMOTE_SERV_VAL),
};

void bt_ready_callback(int err)
{
    if (err) {
        LOG_ERR("bt_enable returned %d", err);
    }
    k_sem_give(&bt_init_ok);
}

int bluetooth_init(struct bt_conn_cb * bt_cb)
{
    int err = 0;
    LOG_INF("Initializing Bluetooth");

    if (bt_cb != NULL)
    {
        LOG_INF("register");
        bt_conn_cb_register(bt_cb);
    }

    err = bt_enable(bt_ready_callback);
    if (err) {
        LOG_ERR("bt_enable() ret %d", err);
        return err;
    }
    k_sem_take(&bt_init_ok, K_FOREVER);

    /* This snippet belongs in bluetooth_init() in remote.c */
    LOG_INF("Starting advertising");
    err = bt_le_adv_start(BT_LE_ADV_CONN, ad, ARRAY_SIZE(ad), sd, ARRAY_SIZE(sd));
    if (err){
        LOG_ERR("couldn't start advertising (err = %d", err);
        return err;
    }

    return err;
}

