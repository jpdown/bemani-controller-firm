#include "encoder.hpp"
#include "encoder.pio.h"
#include <cstdlib>
#include <hardware/pio.h>

static PIO pio = pio0;
static uint sm = 0;
static int last_encoder_value;
static uint8_t game_reported_value;
static int rolling_delta = 0;

void encoder_init(void) {
  // program must load at offset 0, so we don't need to care about the offset
  (void)pio_add_program(pio, &quadrature_encoder_program);
  // TODO: define the clock divider
  quadrature_encoder_program_init(pio, sm, ENCODER_FIRST_PIN, 0);
}

void encoder_task(void) {
  int new_value = quadrature_encoder_get_count(pio, sm);

  if (ENCODER_REVERSE) {
    rolling_delta -= new_value - last_encoder_value;
  } else {
    rolling_delta += new_value - last_encoder_value;
  }

  last_encoder_value = new_value;

  uint8_t num_game_steps = abs(rolling_delta) / THRESHOLD;

  if (rolling_delta > 0) {
    game_reported_value += num_game_steps;
    rolling_delta -= num_game_steps * THRESHOLD;
  } else {
    game_reported_value -= num_game_steps;
    rolling_delta += num_game_steps * THRESHOLD;
  }
}

uint8_t get_encoder_value(void) { return game_reported_value; }
