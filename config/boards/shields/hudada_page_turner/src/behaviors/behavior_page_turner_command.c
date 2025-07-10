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

    // ��ȡ��.keymap ���ݹ����Ĳ��� (0x01, 0x02, etc.)
    uint8_t command = binding->param1;

    LOG_INF("Sending Page Turner command: 0x%02X", command);

    // ZMK�������౨����һ��16λ��λ���롣�����޷�ֱ�ӷ���һ���ֽڡ�
    // ������������ǽ�ʹ��һ�������౨�棬�������ǵ������ֽ���Ϊ�� usage_id��
    // ����Ҫ�Ķ����ܹ��������ַǱ�׼���÷���
    // ����һ�����Է�����������У�����Ҫ���ײ��HID������
    zmk_hid_consumer_report_press(command);
    zmk_endpoints_send_consumer_report();

    // ���ͺ������ͷţ�ģ��һ��������
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