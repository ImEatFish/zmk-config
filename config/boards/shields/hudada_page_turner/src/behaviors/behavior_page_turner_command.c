#define DT_DRV_COMPAT hudada_page_turner_behavior_page_turner_command

#include <zephyr/device.h>
#include <zephyr/logging/log.h>
#include <drivers/behavior.h>
#include <zmk/behavior.h>
#include <zmk/hid.h>

LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

struct behavior_pt_cmd_config {};
struct behavior_pt_cmd_data {
    uint16_t command;
};

static int on_keymap_binding_pressed(const struct device* dev, uint32_t position, uint32_t command_param, uint32_t _) {
    struct behavior_pt_cmd_data* data = dev->data;
    data->command = (uint16_t)command_param;
    LOG_DBG("position %d, command 0x%04X", position, data->command);
    return zmk_hid_consumer_report_press(data->command);
}

static int on_keymap_binding_released(const struct device* dev, uint32_t position, uint32_t command_param, uint32_t _) {
    struct behavior_pt_cmd_data* data = dev->data;
    LOG_DBG("position %d, command 0x%04X", position, data->command);
    return zmk_hid_consumer_report_release(data->command);
}

static int behavior_pt_cmd_init(const struct device* dev) { return 0; };

static const struct behavior_driver_api behavior_pt_cmd_driver_api = {
    .binding_pressed = on_keymap_binding_pressed,
    .binding_released = on_keymap_binding_released,
};

DEVICE_DT_INST_DEFINE(0, behavior_pt_cmd_init, NULL,
    &behavior_pt_cmd_data, &behavior_pt_cmd_config,
    APPLICATION, CONFIG_KERNEL_INIT_PRIORITY_DEFAULT,
    &behavior_pt_cmd_driver_api);