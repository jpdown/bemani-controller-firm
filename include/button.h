#ifndef BUTTON_H
#define BUTTON_H

#include <stdbool.h>
#include <stdint.h>

#include "time.h"

typedef enum {
  KEY1,
  KEY2,
  KEY3,
  KEY4,
  KEY5,
  KEY6,
  KEY7,

  E1,
  E2,
  E3,
  E4,

  NUM_BUTTONS
} button_t;

static uint8_t BUTTON_TO_PIN_MAP[NUM_BUTTONS] = {2,  4,  6,  8,  10, 12,
                                                 14, 16, 18, 20, 22};

typedef struct {
  bool pin_pressed;
  uint32_t transition_time;
  bool pressed;
} button_state_t;

typedef enum {
  DEBOUNCE_EAGER,
  DEBOUNCE_DEFERRED,
  DEBOUNCE_NONE,

  NUM_DEBOUNCE_STRATEGIES
} debounce_strategy_t;

typedef void (*debounce_strategy_f)(button_state_t *, bool);

#define DEFAULT_DEBOUNCE_STRATEGY DEBOUNCE_EAGER
#define DEBOUNCE_TIME_MS TIME_4_MS

void button_init(void);
void button_task(void);

bool button_pressed(button_t button);

void debounce_eager(button_state_t *button, bool new_pin_state);
void debounce_deferred(button_state_t *button, bool new_pin_state);
void debounce_none(button_state_t *button, bool new_pin_state);

static debounce_strategy_f debounce_funcs[NUM_DEBOUNCE_STRATEGIES] = {
    debounce_eager, debounce_deferred, debounce_none};

#endif /* BUTTON_H */
