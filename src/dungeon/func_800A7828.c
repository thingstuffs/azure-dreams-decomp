#include "common.h"
#include "shared/dungeon_status.h"

typedef struct DungeonState {
    u8 pad0[0xA];
    u16 counter;
} DungeonState;

extern DungeonState D_80083460;
extern u8 D_800DCF4F[];
extern u8 D_800E0458[];
extern u8 D_800E0C78[];

extern s32 func_800990FC(void);
extern s32 func_80099194(u8 *src, u8 *dst);
extern s32 func_80099254(u8 *src, u8 *dst);
extern void func_80099290(s8 *byte_ptr);
extern s32 func_8009929C(s8 value, s8 *dest);
extern s32 func_80099734(void *record, u8 *out);
extern void func_800A5720(s8 *text);

/* Conditionally advances the dungeon counter and processes the input through the result chain. */
void func_800ACF88(void *input_data) {
    void *context;
    u16 *flag_page;
    void *saved_input;
    s32 initial_result;
    s32 result;
    u16 counter;

    flag_page = (u16 *)0x80010000;
    saved_input = input_data;
    if (!(flag_page[0x3714 / 2] & 1)) {
        context = D_800DCF4F;
        {
            DungeonState *counter_state = &D_80083460;
            counter = counter_state->counter;
            ((u8 *)context)[0] = 1;
            counter_state->counter = counter + 1;
        }
    }
    initial_result = func_800990FC();
    result = func_80099194(D_800E0C78, func_80099734(saved_input, initial_result));
    if (!(flag_page[0x3714 / 2] & 1)) {
        result = func_80099254(D_800E0458,
            func_8009929C(0x4C, func_8009929C(0x11, result)));
    }
    func_80099290(result);
    func_800A5720(initial_result);
}

