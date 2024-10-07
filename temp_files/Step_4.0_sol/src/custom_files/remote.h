/* Step 4.4 - Add kernel and logging */
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

/* Step 4.6 - Add BLE headers */
#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/uuid.h>
#include <zephyr/bluetooth/gatt.h>
#include <zephyr/bluetooth/hci.h>



/* Step 4.11 - Declare callback */
void bt_ready_callback(int err);
/* Step 4.5.1 - Declare init function*/
int bluetooth_init(struct bt_conn_cb * bt_cb)
