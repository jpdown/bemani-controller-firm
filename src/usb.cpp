#include "usb.hpp"
#include "bsp/board_api.h"
#include "button.hpp"
#include "class/hid/hid_device.h"
#include "device/usbd.h"
#include "encoder.hpp"
#include "usb_descriptors.h"

#include <tusb.h>

void usb_init(void) {
  board_init();
  tusb_init();
  return;
}

void usb_task(void) {
  joystick_report_t report = {0};

  tud_task();
  if (!tud_hid_ready()) {
    return;
  }

  for (int8_t i = 0; i < NUM_BUTTONS; i++) {
    bool pressed = button_pressed((button_t)i);
    report.buttons = (report.buttons & ~(1U << i)) | (pressed << i);
  }

  report.x = get_encoder_value();

  tud_hid_n_report(0x00, REPORT_ID_JOYSTICK, &report, sizeof(report));
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
