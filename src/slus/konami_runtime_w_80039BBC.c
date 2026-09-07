#include "common.h"

typedef struct {
    u8 unk00[0x10];
    void (*handler)(void);
    u8 unk14[0x08];
    u8 *cursor;
    u8 unk20[0x12];
    u8 value;
} FuncState;

extern void func_80038690(void);

void func_80039BBC(FuncState *arg0) {
    u8 *cursor = arg0->cursor;
    u8 value = *cursor;

    arg0->cursor = cursor + 1;
    arg0->handler = func_80038690;
    arg0->value = value;
}
