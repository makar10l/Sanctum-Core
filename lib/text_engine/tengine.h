#ifndef TEXT_ENGINE
#define TEXT_ENGINE
#include <stdint.h>
typedef struct{
    uint16_t x;
    uint8_t y;
} text_cursor;
typedef struct{
    text_cursor cursor;
    const uint8_t (*font)[8];
} tengine_t;
int8_t tengine_putchar(tengine_t* tengine, char ch,uint8_t* buffer);
int8_t tengine_init(tengine_t* tengine, const uint8_t* font);
int8_t tengine_print(tengine_t* tengine, uint8_t* buffer, char* str, uint16_t size);
extern const uint8_t font_8x8[64][8];
#endif