#include <zephyr/device.h>
#include <zmk/behavior.h>
#include <zmk/hid.h>
#include <dt-bindings/zmk/hid_usage.h>
#include <dt-bindings/zmk/hid_usage_pages.h>

// --- 上一页 (Page Up) 行为驱动 ---
#define DT_DRV_COMPAT hudada_page_turner_behavior_page_up

static int on_press_up(const struct device* dev, uint32_t position) { return zmk_hid_consumer_report_press(C_SCAN_PREV); }
static int on_release_up(const struct device* dev, uint32_t position) { return zmk_hid_consumer_report_release(C_SCAN_PREV); }
static const struct behavior_driver_api api_up = { .binding_pressed = on_press_up, .binding_released = on_release_up };
DEVICE_DT_INST_DEFINE(0, NULL, NULL, NULL, NULL, APPLICATION, CONFIG_KERNEL_INIT_PRIORITY_DEFAULT, &api_up);


// --- 下一页 (Page Down) 行为驱动 ---
#define DT_DRV_COMPAT hudada_page_turner_behavior_page_down

static int on_press_down(const struct device* dev, uint32_t position) { return zmk_hid_consumer_report_press(C_SCAN_NEXT); }
static int on_release_down(const struct device* dev, uint32_t position) { return zmk_hid_consumer_report_release(C_SCAN_NEXT); }
static const struct behavior_driver_api api_down = { .binding_pressed = on_press_down, .binding_released = on_release_down };
DEVICE_DT_INST_DEFINE(0, NULL, NULL, NULL, NULL, APPLICATION, CONFIG_KERNEL_INIT_PRIORITY_DEFAULT, &api_down);


// --- 返回 (Return) 行为驱动 ---
#define DT_DRV_COMPAT hudada_page_turner_behavior_return

static int on_press_ret(const struct device* dev, uint32_t position) { return zmk_hid_consumer_report_press(C_AC_BACK); }
static int on_release_ret(const struct device* dev, uint32_t position) { return zmk_hid_consumer_report_release(C_AC_BACK); }
static const struct behavior_driver_api api_ret = { .binding_pressed = on_press_ret, .binding_released = on_release_ret };
DEVICE_DT_INST_DEFINE(0, NULL, NULL, NULL, NULL, APPLICATION, CONFIG_KERNEL_INIT_PRIORITY_DEFAULT, &api_ret);