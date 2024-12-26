/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "button.hpp"
#include "encoder.hpp"
#include "logger.hpp"

int main() {
  logger_init();
  button_init();
  encoder_init();

  while (true) {
    button_task();
    encoder_task();
  }
}
