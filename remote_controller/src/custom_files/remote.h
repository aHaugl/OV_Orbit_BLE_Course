#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

//Bluetooth configs
#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/uuid.h>
#include <zephyr/bluetooth/gatt.h>
#include <zephyr/bluetooth/hci.h>

void bt_ready_callback(int err);
int bluetooth_init();

/* Add this to remote.h */
/** @brief UUID of the Remote Service. **/
#define BT_UUID_REMOTE_SERV_VAL \
BT_UUID_128_ENCODE(0x020f0001, 0xbc61, 0x4d87, 0x9319, 0x9aff590fd64c)

#define BT_UUID_REMOTE_SERVICE  BT_UUID_DECLARE_128(BT_UUID_REMOTE_SERV_VAL)