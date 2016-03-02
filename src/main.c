#include <pebble.h>

#include "modules/util.h"

#include "windows/main_window.h"

static void tick_handler(struct tm *tick_time, TimeUnits changed) {
  main_window_update_time(tick_time);
}

void init() {
  main_window_push();
  
  tick_timer_service_subscribe(SECOND_UNIT, tick_handler);
  main_window_update_time(util_get_tm());
}

void deinit() {}

int main() {
  init();
  app_event_loop();
  deinit();
}