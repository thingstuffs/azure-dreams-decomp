#include "common.h"

typedef s32 M2C_UNK;

extern s8 func_800374F4();
extern M2C_UNK func_8009B454();
extern M2C_UNK func_8009BFD8();

/* Randomize color during an update, then reset it when the timer expires or state changes. */
void func_800AAC64(void *object, M2C_UNK context, M2C_UNK update_param, void *color_data) {
    s32 previous_state;
    s16 ticks_left;

    *(s8 *)((s8 *)color_data + 0xC) = func_800374F4(0x100);
    *(s8 *)((s8 *)color_data + 0xD) = func_800374F4(0x100);
    *(s8 *)((s8 *)color_data + 0xE) = func_800374F4(0x100);
    previous_state = *(s32 *)((s8 *)object + 0x50);
    func_8009B454(object, context, update_param, color_data);
    ticks_left = *(u16 *)((s8 *)object + 0x6C) - 1;
    *(u16 *)((s8 *)object + 0x6C) = ticks_left;
    if ((ticks_left < 0) || (*(s32 *)((s8 *)object + 0x50) != previous_state)) {
        func_8009BFD8(object, context, update_param, color_data);
        *(u8 *)((u8 *)color_data + 0xC) = 0x80;
        *(u8 *)((u8 *)color_data + 0xD) = 0x80;
        *(u8 *)((u8 *)color_data + 0xE) = 0x80;
    }
}
