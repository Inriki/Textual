#include "windows/main_window.h"

static Window *s_window;

static TextLayer *s_bg_text_layer, *s_fg_text_layer;

static GFont s_font, s_font_bold;

static char text[] = "ESONALASBCINCO\nUNADOSDIEZDOCE\nCUATROCHONCECD\nTRESEISNUEVEEF\nSIETEGYHMENOSI\nVEINTEVEINTIJK\nDIECINCOCHONCE\nNUEVEDIEZDOCEL\nPUNTOUNOMEDIAM\nTRECECATORCENO\nDOSTRESEISIETE\nCUATROCUARTOPQ\n";
static char *lineas[] = {
  "01110111000000\n11000110000000\n01110111011111\n",
  "00000000000000\n11100000000000\n00011100000000\n00000011110000\n00000000001111\n",
  "00000000000000\n11111100000000\n00000111100000\n00000000111100\n",
  "00000000000000\n11110000000000\n00011110000000\n00000001111100\n",
  "00000000011000\n11111000011000\n00000010000000\n11111010000000\n00000000111110\n11111000111110\n",
  "00000000000000\n11111100000000\n00000011111100\n",
  "00000000000000\n11111001111000\n11111000000000\n00011111000000\n00000001111000\n00000000001111\n",
  "00000000000000\n11111000000000\n00000111100000\n00000000011110\n",
  "00000000000000\n11111000000000\n00000111000000\n00000000111110\n",
  "00000000000000\n11111000000000\n00000111111100\n",
  "00000000000000\n11100000000000\n00011110000000\n00000011110000\n00000000011111\n",
  "00000000000000\n11111100000000\n00000011111100\n"
};

const int NUM_COLS = 15;
const int NUM_ROWS = 12;
const int ROWS_X_COLS = 180; //NUM_ROWS * NUM_COLS

static int calcularOffset0(int hora) {
  if (hora == 1) return NUM_COLS;
  if (hora == 5) return NUM_COLS * 2;
  return 0;
}

static int calcularOffset1(int hora) {
  if (hora == 1) return NUM_COLS;
  if (hora == 2) return NUM_COLS * 2;
  if (hora == 10) return NUM_COLS * 3;   
  if (hora == 12) return NUM_COLS * 4;
  return 0;
}

static int calcularOffset2(int hora) {
  if (hora == 4) return NUM_COLS;
  if (hora == 8) return NUM_COLS * 2;
  if (hora == 11) return NUM_COLS * 3;
  return 0;
}

static int calcularOffset3(int hora) {
  if (hora == 3) return NUM_COLS;            
  if (hora == 6) return NUM_COLS * 2;
  if (hora == 9) return NUM_COLS * 3;
  return 0;
}

static int calcularOffset4(int hora, int minuto, bool negativo) {
  if (minuto == 0) {
    if (hora == 7) return NUM_COLS;
    return 0;
  } else if (!negativo) {
    if (hora == 7) return NUM_COLS * 3;
    return NUM_COLS * 2;
  } else {
    if (hora == 7) return NUM_COLS * 5;
    return NUM_COLS * 4;
  }    
}

static int calcularOffset5(int minuto) {
  if (minuto == 20) return NUM_COLS;    
  if (minuto > 20 && minuto < 30) return NUM_COLS * 2;
  return 0;
}

static int calcularOffset6(int minuto) {
  if (minuto == 18) return NUM_COLS;
  if (minuto > 15 && minuto < 20) return NUM_COLS * 2;
  if (minuto % 20 == 5) return NUM_COLS * 3;    
  if (minuto % 10 == 8) return NUM_COLS * 4;
  if (minuto == 11) return NUM_COLS * 5;
  return 0;
}

static int calcularOffset7(int minuto) {
  if (minuto % 10 == 9) return NUM_COLS;                    
  if (minuto == 10) return NUM_COLS * 2;
  if (minuto == 12) return NUM_COLS * 3;
  return 0;
}

static int calcularOffset8(int minuto) {
  if (minuto == 0) return NUM_COLS;
  if (minuto % 20 == 1) return NUM_COLS * 2;
  if (minuto == 30) return NUM_COLS * 3;
  return 0;
}

static int calcularOffset9(int minuto) {
  if (minuto == 13) return NUM_COLS;
  if (minuto == 14) return NUM_COLS * 2;                    
  return 0;
}

static int calcularOffset10(int minuto) {
  if (minuto % 20 == 2) return NUM_COLS;
  if (minuto % 20 == 3) return NUM_COLS * 2;
  if (minuto % 10 == 6) return NUM_COLS * 3;
  if (minuto % 10 == 7) return NUM_COLS * 4;
  return 0;
}

static int calcularOffset11(int minuto) {
  if (minuto % 20 == 4) return NUM_COLS;
  if (minuto == 15) return NUM_COLS * 2;
  return 0;
}

static char temp[90];
static char s_foreground_text_buffer[180];
static char s_background_text_buffer[180];

static void main_window_set_texts(int hora, int minuto) {
  int rows_offset[NUM_ROWS];
  
  bool negativo = false;
    
  if (minuto > 30) {
    hora = hora + 1;
    minuto = 60 - minuto;
    negativo = true;
  }

  hora = hora % 12;
    
  rows_offset[0] = calcularOffset0(hora);
  rows_offset[1] = calcularOffset1(hora);   
  rows_offset[2] = calcularOffset2(hora);
  rows_offset[3] = calcularOffset3(hora);
  rows_offset[4] = calcularOffset4(hora, minuto, negativo);
  rows_offset[5] = calcularOffset5(minuto);
  rows_offset[6] = calcularOffset6(minuto);
  rows_offset[7] = calcularOffset7(minuto);
  rows_offset[8] = calcularOffset8(minuto);
  rows_offset[9] = calcularOffset9(minuto);
  rows_offset[10] = calcularOffset10(minuto);
  rows_offset[11] = calcularOffset11(minuto);
  
  for (int j = 0; j < NUM_ROWS; j++) {    
    strcpy(temp, lineas[j]);
    int offset = rows_offset[j];
    
    for(int i = 0; i < NUM_COLS; i++) {            
      if(temp[offset + i] == '\n') {
        s_foreground_text_buffer[i + j * NUM_COLS] = '\n';
        s_background_text_buffer[i + j * NUM_COLS] = '\n';
      } else if(temp[offset + i] == '1') {
        s_foreground_text_buffer[i + j * NUM_COLS] = text[i + j * NUM_COLS];
        s_background_text_buffer[i + j * NUM_COLS] =  ' ';
      } else {
        s_foreground_text_buffer[i + j * NUM_COLS] = ' ';
        s_background_text_buffer[i + j * NUM_COLS] = text[i + j * NUM_COLS];
      }
      APP_LOG(APP_LOG_LEVEL_DEBUG, "bg %d %d: %c", j, i, s_background_text_buffer[i + j * NUM_COLS]);
      APP_LOG(APP_LOG_LEVEL_DEBUG, "fg %d %d: %c", j, i, s_foreground_text_buffer[i + j * NUM_COLS]);
    }
  }
  
  s_foreground_text_buffer[ROWS_X_COLS - 1] = '\0';
  s_background_text_buffer[ROWS_X_COLS - 1] = '\0';
  
  //APP_LOG(APP_LOG_LEVEL_DEBUG, "%s", s_background_text_buffer);
  text_layer_set_text(s_bg_text_layer, s_background_text_buffer);
  text_layer_set_text(s_fg_text_layer, s_foreground_text_buffer);

}

static void window_load(Window *window){
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);
    
  s_bg_text_layer = text_layer_create(bounds);
  text_layer_set_background_color(s_bg_text_layer, GColorBlack);
  text_layer_set_text_color(s_bg_text_layer, GColorDarkGray);
  text_layer_set_text_alignment(s_bg_text_layer, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(s_bg_text_layer));   
  
  s_fg_text_layer = text_layer_create(bounds);
  text_layer_set_background_color(s_fg_text_layer, GColorClear);
  text_layer_set_text_color(s_fg_text_layer, GColorPastelYellow);
  text_layer_set_text_alignment(s_fg_text_layer, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(s_fg_text_layer));
    
  // Load and set custom font
  s_font_bold = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_EVERSON_MONO_BOLD_14));
  s_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_EVERSON_MONO_14));
  text_layer_set_font(s_bg_text_layer, s_font);
  text_layer_set_font(s_fg_text_layer, s_font_bold);  
}

static void window_unload(Window *window) {
 // Destroy TextLayers
  text_layer_destroy(s_bg_text_layer);
  
  window_destroy(window);
}
  
void main_window_push(){
  s_window = window_create();
  
  window_set_background_color(s_window, GColorBlack);
  window_set_window_handlers(s_window, (WindowHandlers){
    .load = window_load,
    .unload = window_unload
  });
  
  window_stack_push(s_window, true);  
}

void main_window_update_time(struct tm* tick_time){
  main_window_set_texts(tick_time->tm_hour, tick_time->tm_min);
}