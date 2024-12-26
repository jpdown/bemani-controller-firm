/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "button.hpp"
#include "encoder.hpp"
#include "logger.hpp"
#include "usb.hpp"

int main() {
  logger_init();
  button_init();
  encoder_init();
  usb_init();

  while (true) {
    button_task();
    encoder_task();
    usb_task();
  }
}
