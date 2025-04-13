#ifndef USB_H
#define USB_H

#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  uint16_t buttons;
  uint8_t x;
  uint8_t y;
} joystick_report_t;

void usb_init(void);
void usb_task(void);

#ifdef __cplusplus
}
#endif

#endif /* USB_H */
