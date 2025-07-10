#define DT_DRV_COMPAT hudada_page_turner_behavior_page_turner_command

#include <zephyr/device.h>
#include <drivers/behavior.h>
#include <zephyr/logging/log.h>
#include <zmk/hid.h>
#include <zmk/endpoints.h>
#include <zmk/event_manager.h>
#include <zmk/events/position_state_changed.h>

LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

struct behavior_pt_cmd_config {};
struct behavior_pt_cmd_data {};

static int on_keymap_binding_pressed(struct zmk_behavior_binding* binding,
    struct zmk_behavior_binding_event event) {
    const struct device* dev = zmk_behavior_get_binding(binding->behavior_dev);

    // 获取从.keymap 传递过来的参数 (0x01, 0x02, etc.)
    uint8_t command = binding->param1;

    LOG_INF("Sending Page Turner command: 0x%02X", command);

    // ZMK的消费类报告是一个16位的位掩码。我们无法直接发送一个字节。
    // 替代方案：我们将使用一个消费类报告，并把我们的命令字节作为其 usage_id。
    // 这需要阅读器能够解析这种非标准的用法。
    // 这是一个折衷方案，如果不行，就需要更底层的HID操作。
    zmk_hid_consumer_report_press(command);
    zmk_endpoints_send_consumer_report();

    // 发送后立即释放，模拟一次性命令
    zmk_hid_consumer_report_release(command);
    zmk_endpoints_send_consumer_report();

    return ZMK_BEHAVIOR_OPAQUE;
}

static const struct behavior_driver_api behavior_pt_cmd_driver_api = {
   .binding_pressed = on_keymap_binding_pressed,
};

static int behavior_pt_cmd_init(const struct device* dev) { return 0; };

DEVICE_DT_INST_DEFINE(0, behavior_pt_cmd_init, NULL,
    NULL, NULL, APPLICATION,
    CONFIG_KERNEL_INIT_PRIORITY_DEFAULT,
    &behavior_pt_cmd_driver_api);