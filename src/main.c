/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "button.h"
#include "logger.h"

int main() {
  logger_init();
  button_init();

  while (true) {
    button_task();
  }
}
