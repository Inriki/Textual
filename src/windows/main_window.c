#include "windows/main_window.h"

static Window *s_window;

static TextLayer *s_bg_text_layer, *s_fg_text_layer;

static GFont s_font, s_font_bold;

#ifdef PBL_RECT
static char text_square[] = "ESONALASBCINCO\nUNADOSDIEZDOCE\nCUATROCHONCECD\nTRESEISNUEVEEF\nSIETEGYHMENOSI\nVEINTEVEINTIJK\nDIECINCOCHONCE\nNUEVEDIEZDOCEL\nPUNTOUNOMEDIAM\nTRECECATORCENO\nDOSTRESEISIETE\nCUATROCUARTOPQ\n";
static char *lineas_square[] = {
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

#elif PBL_ROUND
//"ABCDEFGESONHIJKLM\nNOPQLASOCUATRORST\nUVUNADOSNUEVEWXYZ\nACINCOCHONCEDIEZB\nTRESEISIETEDOCECY\nMENOSPUNTOCATORCE\nDIEZDOCEVEINTIUNO\nDIECINCOCHOVEINTE\nDNUEVEDOSEISIETEG\nHITRECEMEDIATRESJ\nKLMCUATROONCENOPQ\nRSTUVWCUARTOZABCD\n";
static char text_round[]  = 
  "ABCDEFGESONHIJKLM\nNOPQLASOCUATRORST\nUVUNADOSNUEVEWXYZ\nACINCOCHONCEDIEZB\nTRESEISIETEDOCECY\nMENOSPUNTOCATORCE\nDIEZDOCEVEINTIUNO\nDOSDIECINCOCHONCE\nDNUEVEINTEMEDIAEF\nGHTRESEISIETEIJKL\nMNOCUATROTRECEQRS\nTUVWXYCUARTOZABCD\n";
static char *lineas_round[] = {
 //123456789012345678 123456789012345678 123456789012345678 123456789012345678 123456789012345678 123456789012345678 123456789012345678 123456789012345678 123456789012345678 123456789012345678 
  "00000000111000000\n00000001100000000\n",
  "00001110000000000\n00001100000000000\n00001110111111000\n",
  "00000000000000000\n00111000000000000\n00000111000000000\n00000000111110000\n",
  "00000000000000000\n01111100000000000\n00000111100000000\n00000000111100000\n00000000000011110\n",
  "00000000000000000\n11110000000000000\n00011110000000000\n00000011111000000\n00000000000111100\n00000000000000001\n11110000000000001\n00011110000000001\n00000011111000001\n00000000000111101\n",
  "00000000000000000\n01100111110000000\n00000000001111111\n11111000001111111\n11111000000000000\n",
  "00000000000000000\n11110000000000000\n00001111000000000\n00000000111111000\n00000000111111111\n00000000000000111\n",
  "00000000000000000\n11100000000000000\n00011111000000000\n00000011111000000\n00000000001111000\n00000000000001111\n00011111001111000\n",
  "00000000000000000\n01111100000000000\n00001111110000000\n00000000001111100\n",
  "00000000000000000\n00111100000000000\n00000111100000000\n00000000111110000\n",
  "00000000000000000\n00011111100000000\n00000000011111000\n",
  "00000000000000000\n00000011111100000\n"
};
#endif

static int calcularOffset0(int hora) {
  #ifdef PBL_RECT
  if (hora == 1) return NUM_COLS_SQR;
  if (hora == 5) return NUM_COLS_SQR * 2;
  #elif PBL_ROUND
  if (hora == 1) return NUM_COLS_RND;
  #endif
  return 0;
}

static int calcularOffset1(int hora) {
  #ifdef PBL_RECT
  if (hora == 1) return NUM_COLS_SQR;
  if (hora == 2) return NUM_COLS_SQR * 2;  
  if (hora == 10) return NUM_COLS_SQR * 3;    
  if (hora == 0) return NUM_COLS_SQR * 4;
  #elif PBL_ROUND
  if (hora == 1) return NUM_COLS_RND;
  if (hora == 4) return NUM_COLS_RND * 2;
  #endif
  return 0;
}

static int calcularOffset2(int hora) {
  #ifdef PBL_RECT
  if (hora == 4) return NUM_COLS_SQR;
  if (hora == 8) return NUM_COLS_SQR * 2;
  if (hora == 11) return NUM_COLS_SQR * 3;
  #elif PBL_ROUND
  if (hora == 1) return NUM_COLS_RND;
  if (hora == 2) return NUM_COLS_RND * 2;
  if (hora == 9) return NUM_COLS_RND * 3;
  #endif
  return 0;
}

static int calcularOffset3(int hora) {
  #ifdef PBL_RECT
  if (hora == 3) return NUM_COLS_SQR;
  if (hora == 6) return NUM_COLS_SQR * 2;
  if (hora == 9) return NUM_COLS_SQR * 3;
  #elif PBL_ROUND
  if (hora == 5) return NUM_COLS_RND;
  if (hora == 8) return NUM_COLS_RND * 2;
  if (hora == 11) return NUM_COLS_RND * 3;
  if (hora == 10) return NUM_COLS_RND * 4;
  #endif
  return 0;
}

static int calcularOffset4(int hora, int minuto, bool negativo) {
  if (minuto == 0) {
    #ifdef PBL_RECT
    if (hora == 7) return NUM_COLS_SQR;
    #elif PBL_ROUND
    if (hora == 3) return NUM_COLS_RND;
    if (hora == 6) return NUM_COLS_RND * 2;
    if (hora == 7) return NUM_COLS_RND * 3;
    if (hora == 0) return NUM_COLS_RND * 4;
    #endif
    return 0;
  } else if (!negativo) {
    #ifdef PBL_RECT
    if (hora == 7) return NUM_COLS_SQR * 3;
    return NUM_COLS_SQR * 2;
    #elif PBL_ROUND
    if (hora == 3) return NUM_COLS_RND * 6;
    if (hora == 6) return NUM_COLS_RND * 7;
    if (hora == 7) return NUM_COLS_RND * 8;
    if (hora == 0) return NUM_COLS_RND * 9;
    return NUM_COLS_RND * 5;
    #endif
  } else {
    #ifdef PBL_RECT
    if (hora == 7) return NUM_COLS_SQR * 5;
    return NUM_COLS_SQR * 4;
    #elif PBL_ROUND
    if (hora == 3) return NUM_COLS_RND;
    if (hora == 6) return NUM_COLS_RND * 2;
    if (hora == 7) return NUM_COLS_RND * 3;
    if (hora == 0) return NUM_COLS_RND * 4;
    return 0;
    #endif
  }  
  return 0;
}

#ifdef PBL_RECT
static int calcularOffset5(int minuto) {
  if (minuto == 20) return NUM_COLS_SQR;
  if (minuto > 20 && minuto < 30) return NUM_COLS_SQR * 2;
  return 0;
}
#elif PBL_ROUND
static int calcularOffset5(int minuto, bool negativo) {
  if (minuto == 0) {
    return NUM_COLS_RND;
  } else if(!negativo) {
    if(minuto == 14) {
      return NUM_COLS_RND * 2;
    }
  } else {
    if(minuto == 14) {
      return NUM_COLS_RND * 3;
    } else {
      return NUM_COLS_RND * 4;
    }
  }
  return 0;
}
#endif

static int calcularOffset6(int minuto) {
  #ifdef PBL_RECT
  if (minuto == 18) return NUM_COLS_SQR;
  if (minuto > 15 && minuto < 20) return NUM_COLS_SQR * 2;
  if (minuto % 20 == 5) return NUM_COLS_SQR * 3;    
  if (minuto % 10 == 8) return NUM_COLS_SQR * 4;
  if (minuto == 11) return NUM_COLS_SQR * 5;
  #elif PBL_ROUND
  if (minuto == 10) return NUM_COLS_RND;
  if (minuto == 12) return NUM_COLS_RND * 2;
  if (minuto > 21 && minuto < 30) return NUM_COLS_RND * 3;    
  if (minuto == 21) return NUM_COLS_RND * 4;
  if (minuto == 1) return NUM_COLS_RND * 5;
  #endif
  return 0;
}

static int calcularOffset7(int minuto) {
  #ifdef PBL_RECT
  if (minuto % 10 == 9) return NUM_COLS_SQR;                    
  if (minuto == 10) return NUM_COLS_SQR * 2;
  if (minuto == 12) return NUM_COLS_SQR * 3;
  #elif PBL_ROUND
  if (minuto % 20 == 2) return NUM_COLS_RND;
  if (minuto == 18) return NUM_COLS_RND * 6;
  if (minuto > 15 && minuto < 20) return NUM_COLS_RND * 2;
  if (minuto % 20 == 5) return NUM_COLS_RND * 3;
  if (minuto % 20 == 8) return NUM_COLS_RND * 4;    
  if (minuto == 11) return NUM_COLS_RND * 5;
  #endif
  return 0;
}

static int calcularOffset8(int minuto) {
  #ifdef PBL_RECT
  if (minuto == 0) return NUM_COLS_SQR;
  if (minuto % 20 == 1) return NUM_COLS_SQR * 2;
  if (minuto == 30) return NUM_COLS_SQR * 3;
  #elif PBL_ROUND
  if (minuto % 10 == 9) return NUM_COLS_RND;
  if (minuto == 20) return NUM_COLS_RND * 2;
  if (minuto == 30) return NUM_COLS_RND * 3;
  #endif
  return 0;
}

static int calcularOffset9(int minuto) {
  #ifdef PBL_RECT
  if (minuto == 13) return NUM_COLS_SQR;
  if (minuto == 14) return NUM_COLS_SQR * 2;  
  #elif PBL_ROUND
  if (minuto % 20 == 3) return NUM_COLS_RND;
  if (minuto % 10 == 6) return NUM_COLS_RND * 2;
  if (minuto % 10 == 7) return NUM_COLS_RND * 3;
  #endif
  return 0;
}

static int calcularOffset10(int minuto) {
  #ifdef PBL_RECT
  if (minuto % 20 == 2) return NUM_COLS_SQR;
  if (minuto % 20 == 3) return NUM_COLS_SQR * 2;
  if (minuto % 10 == 6) return NUM_COLS_SQR * 3;
  if (minuto % 10 == 7) return NUM_COLS_SQR * 4;
  #elif PBL_ROUND
  if (minuto % 20 == 4) return NUM_COLS_RND;
  if (minuto == 13) return NUM_COLS_RND * 2;
  #endif
  return 0;
}

static int calcularOffset11(int minuto) {
  #ifdef PBL_RECT
  if (minuto % 20 == 4) return NUM_COLS_SQR;
  if (minuto == 15) return NUM_COLS_SQR * 2;
  #elif PBL_ROUND
  if (minuto == 15) return NUM_COLS_RND;
  #endif
  return 0;
}

static char temp[150];
static char s_foreground_text_buffer[PBL_IF_RECT_ELSE(ROWS_X_COLS_SQR, ROWS_X_COLS_RND)];
static char s_background_text_buffer[PBL_IF_RECT_ELSE(ROWS_X_COLS_SQR, ROWS_X_COLS_RND)];

static void main_window_set_texts(int hora, int minuto) {
  int rows_offset[PBL_IF_RECT_ELSE(NUM_ROWS_SQR, NUM_ROWS_RND)];
  
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
  #ifdef PBL_RECT
  rows_offset[5] = calcularOffset5(minuto);
  #elif PBL_ROUND
  rows_offset[5] = calcularOffset5(minuto, negativo);
  #endif
  rows_offset[6] = calcularOffset6(minuto);
  rows_offset[7] = calcularOffset7(minuto);
  rows_offset[8] = calcularOffset8(minuto);
  rows_offset[9] = calcularOffset9(minuto);
  rows_offset[10] = calcularOffset10(minuto);
  rows_offset[11] = calcularOffset11(minuto);

  for (int j = 0; j < PBL_IF_RECT_ELSE(NUM_ROWS_SQR, NUM_ROWS_RND); j++) {    
    strcpy(temp, PBL_IF_RECT_ELSE(lineas_square, lineas_round)[j]);
    int offset = rows_offset[j];
    
    for(int i = 0; i < PBL_IF_RECT_ELSE(NUM_COLS_SQR, NUM_COLS_RND); i++) {
      if(temp[offset + i] == '\n') {
        s_foreground_text_buffer[i + j * PBL_IF_RECT_ELSE(NUM_COLS_SQR, NUM_COLS_RND)] = '\n';
        s_background_text_buffer[i + j * PBL_IF_RECT_ELSE(NUM_COLS_SQR, NUM_COLS_RND)] = '\n';
      } else if(temp[offset + i] == '1') {
        s_foreground_text_buffer[i + j * PBL_IF_RECT_ELSE(NUM_COLS_SQR, NUM_COLS_RND)] = PBL_IF_RECT_ELSE(text_square, text_round)[i + j * PBL_IF_RECT_ELSE(NUM_COLS_SQR, NUM_COLS_RND)];
        s_background_text_buffer[i + j * PBL_IF_RECT_ELSE(NUM_COLS_SQR, NUM_COLS_RND)] =  ' ';
      } else {
        s_foreground_text_buffer[i + j * PBL_IF_RECT_ELSE(NUM_COLS_SQR, NUM_COLS_RND)] = ' ';
        s_background_text_buffer[i + j * PBL_IF_RECT_ELSE(NUM_COLS_SQR, NUM_COLS_RND)] = PBL_IF_RECT_ELSE(text_square, text_round)[i + j * PBL_IF_RECT_ELSE(NUM_COLS_SQR, NUM_COLS_RND)];
      }
      //APP_LOG(APP_LOG_LEVEL_DEBUG, "bg %d %d: %c", j, i, s_background_text_buffer[i + j * PBL_IF_RECT_ELSE(NUM_COLS_SQR, NUM_COLS_RND)]);
      //APP_LOG(APP_LOG_LEVEL_DEBUG, "fg %d %d: %c", j, i, s_foreground_text_buffer[i + j * PBL_IF_RECT_ELSE(NUM_COLS_SQR, NUM_COLS_RND)]);
    }
  }
  
  s_foreground_text_buffer[PBL_IF_RECT_ELSE(ROWS_X_COLS_SQR, ROWS_X_COLS_RND) - 1] = '\0';
  s_background_text_buffer[PBL_IF_RECT_ELSE(ROWS_X_COLS_SQR, ROWS_X_COLS_RND) - 1] = '\0';
  
  //APP_LOG(APP_LOG_LEVEL_DEBUG, "%s", s_background_text_buffer);
  text_layer_set_text(s_bg_text_layer, s_background_text_buffer);
  text_layer_set_text(s_fg_text_layer, s_foreground_text_buffer);

}

static void window_load(Window *window){
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);
  #ifdef PBL_ROUND
  bounds = GRect(0, 5, bounds.size.w, bounds.size.h - 5);
  #endif
  
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
  s_font_bold = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_VERA_MONO_BOLD_14));
  s_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_VERA_MONO_14));
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