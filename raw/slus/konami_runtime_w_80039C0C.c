#include "common.h"

typedef struct {
    u8 unk00[0x10];
    void (*handler)(void);
    u8 unk14[0x08];
    u8 *cursor;
    u8 unk20[0x12];
    u8 first;
    u8 second;
} FuncState;

extern void func_8003875C(void);

void func_80039C0C(FuncState *arg0) {
    u8 *cursor = arg0->cursor;
    u8 value = *cursor++;

    arg0->cursor = cursor;
    arg0->first = value;
    value = *cursor++;
    arg0->cursor = cursor;
    arg0->handler = func_8003875C;
    arg0->second = value;
}
