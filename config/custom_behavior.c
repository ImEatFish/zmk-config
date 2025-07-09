// 文件路径: config/custom_behavior.c
#include <device.h>
#include <drivers/behavior.h>
#include <logging/log.h>
#include <zmk/behavior.h>
#include <zmk/hid.h>

LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

struct behavior_page_turner_data {};
struct behavior_page_turner_config {
    uint8_t usage_page;
};

static int behavior_page_turner_pressed(struct zmk_behavior_binding *binding,
                                        struct zmk_behavior_binding_event event) {
    uint8_t report[CONFIG_RAW_HID_REPORT_SIZE] = {0};
    report[0] = binding->param1; // 关键：将keymap中传递的参数作为数据发送
    int err = zmk_hid_raw_report_send(report, sizeof(report));
    if (err) {
        LOG_ERR("Failed to send raw report (%d)", err);
    }
    return ZMK_BEHAVIOR_OPAQUE;
}

static int behavior_page_turner_released(struct zmk_behavior_binding *binding,
                                         struct zmk_behavior_binding_event event) {
    return ZMK_BEHAVIOR_OPAQUE;
}

static const struct behavior_driver_api behavior_page_turner_api = {
    .binding_pressed = behavior_page_turner_pressed,
    .binding_released = behavior_page_turner_released,
};

static int behavior_page_turner_init(const struct device *dev) { return 0; };

#define PT_INST(n)                                                                                 \
    static const struct behavior_page_turner_config config_##n = {                                  \
        .usage_page = DT_INST_PROP(n, usage_page)};                                                \
    BEHAVIOR_DT_INST_DEFINE(n, behavior_page_turner_init, NULL, NULL, &config_##n, POST_KERNEL,   \
                          CONFIG_KERNEL_INIT_PRIORITY_DEFAULT, &behavior_page_turner_api);

DT_INST_FOREACH_STATUS_OKAY(PT_INST)
