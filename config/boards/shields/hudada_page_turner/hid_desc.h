#pragma once

#include <zephyr/usb/class/hid.h>

// 这是从您的 Arduino 代码翻译过来的 HID 报告描述符
static const uint8_t hudada_pageturner_hid_report_desc = {
    HID_USAGE_PAGE(HID_USAGE_PAGE_CONSUMER),
    HID_USAGE(HID_USAGE_CONSUMER_CONSUMER_CONTROL),
    HID_COLLECTION(HID_COLLECTION_APPLICATION),
    HID_REPORT_ID(1),
    HID_LOGICAL_MIN8(0x01),
    HID_LOGICAL_MAX8(0x07),
    HID_REPORT_SIZE(8),
    HID_REPORT_COUNT(1),
    HID_INPUT(HID_DATA | HID_ARRAY | HID_ABSOLUTE),
    HID_END_COLLECTION,
};