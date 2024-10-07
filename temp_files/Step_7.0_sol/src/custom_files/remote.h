/* Step 4.0.4 - Add kernel and logging */
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

/* Step 4.0.6 - Add BLE headers */
#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/uuid.h>
#include <zephyr/bluetooth/gatt.h>
#include <zephyr/bluetooth/hci.h>

/* Step 4.1.2 - Add Remote Service UUID */
#define BT_UUID_REMOTE_SERV_VAL \
BT_UUID_128_ENCODE(0x020f0001, 0xbc61, 0x4d87, 0x9319, 0x9aff590fd64c)
/* Step 4.1.3 - define the service*/
#define BT_UUID_REMOTE_SERVICE  BT_UUID_DECLARE_128(BT_UUID_REMOTE_SERV_VAL)

/* Step 5.1 - Add UUID for Button Char */
/** @brief UUID of the Button Characteristic. **/
#define BT_UUID_REMOTE_BUTTON_CHRC_VAL \
	BT_UUID_128_ENCODE(0xe9ea0002, 0xe19b, 0x482d, 0x9293, 0xc7907585fc48)
#define BT_UUID_REMOTE_BUTTON_CHRC 	BT_UUID_DECLARE_128(BT_UUID_REMOTE_BUTTON_CHRC_VAL)

/*Step 7.0 Add UUID */
#define BT_UUID_REMOTE_BUTTON_MESSAGE_VAL \
    BT_UUID_128_ENCODE(0x020f0003, 0xbc61, 0x4d87, 0x9319, 0x9aff590fd64c)
/* Step 7.0 add the UUID for REMOTE_MESSAGE_CHRC */
#define BT_UUID_REMOTE_MESSAGE_CHRC     BT_UUID_DECLARE_128(BT_UUID_REMOTE_BUTTON_MESSAGE_VAL)

/* Step 6.2 - add enum for notifications */
/* This code snippet belongs to remote.h */
enum bt_button_notifications_enabled {
	BT_BUTTON_NOTIFICATIONS_ENABLED,
	BT_BUTTON_NOTIFICATIONS_DISABLED,
};

/* Step 6.3 - Declare bt_remote_service_cb*/
/* Step 7.0 - Add data_received to the remote_service_cb*/
/* This code snippet belongs to remote.h */
struct bt_remote_service_cb {
	void (*notif_changed)(enum bt_button_notifications_enabled status);
	void (*data_received)(struct bt_conn *conn, const uint8_t *const data, uint16_t len);
};


/* Step 4.1.1 - Declare callback */
void bt_ready_callback(int err);
/* Step 5.6 - declare button press*/
void set_button_press(uint8_t btn_value);
/* Step 4.0.5 - Declare init function*/
int bluetooth_init(struct bt_conn_cb *bt_cb, struct bt_remote_service_cb *remote_cb);
/* Step 6.7 - Declare the on_sent and send_button_notification snippets */
void on_sent(struct bt_conn *conn, void *user_data);
int send_button_notification(struct bt_conn *conn, uint8_t value);