/* Step 4.0.2 - add remote.h*/
#include "remote.h"

/* Step 4.0.3 - Add logging */
#define LOG_MODULE_NAME remote
LOG_MODULE_REGISTER(LOG_MODULE_NAME);

/* Step 4.1.4 - Add device name and length*/
#define DEVICE_NAME CONFIG_BT_DEVICE_NAME
#define DEVICE_NAME_LEN (sizeof(DEVICE_NAME)-1)

/* Step 4.1.6 - prepare advertise packets */
/* Step 4.1.7 - populize the advertise packets*/
static const struct bt_data ad[] = {
    BT_DATA_BYTES(BT_DATA_FLAGS, (BT_LE_AD_GENERAL | BT_LE_AD_NO_BREDR)),
    BT_DATA(BT_DATA_NAME_COMPLETE, DEVICE_NAME, DEVICE_NAME_LEN)
};

static const struct bt_data sd[] = {
    BT_DATA_BYTES(BT_DATA_UUID128_ALL, BT_UUID_REMOTE_SERV_VAL),
};


/* Step 4.0.9 - Create the semaphore */
static K_SEM_DEFINE(bt_init_ok, 0, 1);

/* Step 5.0 - Define the service */
/* This code snippet belongs to remote.c */
/* STep 5.3 - Augment the service macro*/
BT_GATT_SERVICE_DEFINE(remote_srv,
BT_GATT_PRIMARY_SERVICE(BT_UUID_REMOTE_SERVICE),
    BT_GATT_CHARACTERISTIC(BT_UUID_REMOTE_BUTTON_CHRC,
                    BT_GATT_CHRC_READ,
                    BT_GATT_PERM_READ,
                    read_button_characteristic_cb, NULL, NULL),
);
/* Step 5.4 - Add read_button_characteristic_cb */
static uint8_t button_value = 0;

static ssize_t read_button_characteristic_cb(struct bt_conn *conn, const struct bt_gatt_attr *attr,
                                            void *buf, uint16_t len, uint16_t offset)
{
    return bt_gatt_attr_read(conn, attr, buf, len, offset, &button_value, sizeof(button_value));
}

/* Step 4.0.8 - Add bt_ready_callback CB*/
void bt_ready_callback(int err)
{
    if (err) {
        LOG_ERR("bt_enable returned %d", err);
    }
    k_sem_give(&bt_init_ok);
}
/* Step 5.6 - Challenge: create set_button_press*/
void set_button_press(uint8_t btn_value)
{
    button_value = btn_value;
}

/* Step 4.0.5 - Implement bluetooth_init */
/* Step 4.1.9 - take the connection struct as an argument and check bt_cb != NULL*/
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
    /*Step 4.1.8 - Start advertising */
    LOG_INF("Starting advertising");
    err = bt_le_adv_start(BT_LE_ADV_CONN, ad, ARRAY_SIZE(ad), sd, ARRAY_SIZE(sd));
    if (err){
        LOG_ERR("couldn't start advertising (err = %d", err);
        return err;
    }
        
    k_sem_take(&bt_init_ok, K_FOREVER);

    return err;
}