#include "common.h"

typedef struct DungeonState {
    u8 pad0[0xA];
    u16 counter;
} DungeonState;

extern DungeonState D_80083460;
extern u8 D_800E0458[];
extern u8 D_800E0C78[];

extern s32 func_800990FC(void *, void *);
extern s32 func_80099194(void *, s32);
extern s32 func_80099254(void *, s32);
extern void func_80099290(s32);
extern s32 func_8009929C(s32, s32);
extern s32 func_80099734(void *, s32);
extern void func_800A5720(s32);

/* Conditionally advances the dungeon counter and processes the input through the result chain. */
void func_800ACF88(void *input_data, void *context) {
    u16 *flag_page;
    void *saved_input;
    s32 initial_result;
    s32 result;
    u16 counter;

    flag_page = (u16 *)0x80010000;
    saved_input = input_data;
    if (!(flag_page[0x3714 / 2] & 1)) {
        context = (void *)0x800E0000;
        input_data = (void *)0x80080000;
        ASM_KEEP(input_data);   /* MATCH pin: load-bearing for the whole function shape */
        input_data = (u8 *)input_data + 0x3460;
        counter = ((DungeonState *)input_data)->counter;
        ((s8 *)context)[-0x30B1] = 1;
        ((DungeonState *)input_data)->counter = counter + 1;
    }
    initial_result = func_800990FC(input_data, context);
    result = func_80099194(D_800E0C78, func_80099734(saved_input, initial_result));
    if (!(flag_page[0x3714 / 2] & 1)) {
        result = func_80099254(D_800E0458,
            func_8009929C(0x4C, func_8009929C(0x11, result)));
    }
    func_80099290(result);
    func_800A5720(initial_result);
}

