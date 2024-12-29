#include "usb.hpp"
#include "bsp/board_api.h"
#include "button.hpp"
#include "class/hid/hid_device.h"
#include "device/usbd.h"
#include "usb_descriptors.h"

#include <tusb.h>

void usb_init(void) {
  board_init();
  tusb_init();
  return;
}

void usb_task(void) {
  tud_task();
  // if (!tud_hid_ready()) {
  //   return;
  // }
  //
  // if (button_pressed(KEY1)) {
  //   uint8_t keycode[6] = {0};
  //   keycode[0] = HID_KEY_A;
  //   tud_hid_keyboard_report(REPORT_ID_GAMEPAD, 0, keycode);
  // } else {
  //   tud_hid_keyboard_report(REPORT_ID_GAMEPAD, 0, NULL);
  // }

  return;
}

extern "C" void tud_hid_set_report_cb(uint8_t instance, uint8_t report_id,
                                      hid_report_type_t report_type,
                                      uint8_t const *buffer, uint16_t bufsize) {
  (void)instance;
  (void)report_id;
  (void)report_type;
  (void)buffer;
  (void)bufsize;
}

extern "C" uint16_t tud_hid_get_report_cb(uint8_t instance, uint8_t report_id,
                                          hid_report_type_t report_type,
                                          uint8_t *buffer, uint16_t reqlen) {
  (void)instance;
  (void)report_id;
  (void)report_type;
  (void)buffer;
  (void)reqlen;

  return 0;
}
