#pragma once

#include <pebble.h>

#include "config.h"

void main_window_push();

void main_window_update_time(struct tm* tick_time);