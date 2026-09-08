#include "common.h"

typedef struct {
    void **images;
    u8 count;
    u8 pad[3];
} ImageList;

typedef struct {
    u8 pad0[4];
    u16 field4;
    u16 field6;
    u16 field8;
    u8 state;
    u8 fieldB;
    u8 toggleC;
    u8 padD[2];
    u8 digit0;
    u8 digit1;
    u8 digit2;
    u8 pad12;
    u8 index;
    u8 old_index;
    u8 pad15;
    u8 side;
    u8 choices[2];
} TownState;

extern void func_80053DA8(s32);
extern s32 func_80123200(u8);
extern void func_801237A4(TownState *);
extern void func_801248C0(TownState *);
extern void func_80124908(TownState *);

extern u8 D_80083160[];
extern u8 D_801269F8[];
extern ImageList D_801278B0[];

void func_80124F98(TownState *state)
{
    u8 *input;
    u32 buttons;
    s32 limit;
    s32 step;
    u8 current;
    u8 previous;
    u8 value;
    u8 choice;
    u16 timer;

    input = D_80083160;
    if (*(u32 *)(input + 0x10) & 0x20) {
        func_80053DA8(0x702);
        func_801248C0(state);
        state->state = 9;
        state->field4 = 1;
        state->field6 = 0x19;
        goto done;
    }

    buttons = *(u32 *)(input + 8);
    if (buttons & 0x1000) {
        u8 *selection = D_801269F8;

        if (selection[9] >= 4) {
            state->state = 0xD;
            selection[9] -= 4;
        } else {
            selection[9] = 0;
        }
redraw_transition:
        func_801248C0(state);
        goto redraw;
    }

    if (buttons & 0x4000) {
        u8 *selection;

        step = (D_801278B0[state->index].count - 3) << 4;
        selection = D_801269F8;
        if (((step & 0xF0) - 4) >= selection[9]) {
            state->state = 0xE;
            selection[9] += 4;
        } else {
            selection[9] = step;
        }
        goto redraw_transition;
    }

    if (buttons & 0x8000) {
        limit = 0x32;
        state->old_index = state->index;
decrement_loop:
        if (state->index == 0) {
            state->index = limit;
        }
        state->index--;
        if (!(func_80123200(state->index) & 0xFF) &&
            state->index != state->old_index) {
            goto decrement_loop;
        }

        if (state->index == 0x31) {
            state->digit1 = 1;
            state->digit2 = 0;
            state->digit0 = state->index >> 4;
        } else {
            u32 decode;
            u32 decode_copy;

            decode = state->index;
            decode_copy = decode;
            ASM_KEEP(decode_copy);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
            state->digit0 = decode >> 4;
            state->digit1 = (decode_copy >> 3) & 1;
            state->digit2 = state->index & 7;
        }

        current = state->index;
        previous = state->old_index;
        if (current < previous) {
            func_80053DA8(0x702);
            func_801248C0(state);
            state->side ^= 1;
            func_801237A4(state);
            choice = state->choices[state->side];
            if (choice != state->index) {
                state->state = 0xC;
                goto done;
            }
            state->state = 0xA;
            state->field4 = 1;
            state->field6 = 0x19;
            goto done;
        }
        if (previous < current) {
            func_80053DA8(0x702);
            func_801248C0(state);
            state->side ^= 1;
            func_801237A4(state);
            if (state->choices[state->side] == state->index) {
                state->state = 0xB;
                state->field4 = 1;
                state->field6 = 0x19;
                goto done;
            }
            state->state = 0xC;
        }
        goto done;
    }

    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
    if (buttons & 0x2000) {
        limit = 0x32;
        state->old_index = state->index;
increment_loop:
        value = state->index + 1;
        state->index = value;
        if ((value & 0xFF) == limit) {
            state->index = 0;
        }
        if (!(func_80123200(state->index) & 0xFF) &&
            state->index != state->old_index) {
            goto increment_loop;
        }

        if (state->index == 0x31) {
            state->digit1 = 1;
            state->digit2 = 0;
            state->digit0 = state->index >> 4;
        } else {
            u32 decode;
            u32 decode_copy;

            decode = state->index;
            decode_copy = decode;
            ASM_KEEP(decode_copy);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
            state->digit0 = decode >> 4;
            state->digit1 = (decode_copy >> 3) & 1;
            state->digit2 = state->index & 7;
        }

        current = state->index;
        previous = state->old_index;
        if (current < previous) {
            func_80053DA8(0x702);
            func_801248C0(state);
            state->side ^= 1;
            func_801237A4(state);
            if (state->choices[state->side] != state->index) {
                state->state = 0xC;
                goto done;
            }
            state->state = 0xA;
            state->field4 = 1;
            state->field6 = 0x19;
            goto done;
        }
        if (previous < current) {
            func_80053DA8(0x702);
            func_801248C0(state);
            state->side ^= 1;
            func_801237A4(state);
            if (state->choices[state->side] == state->index) {
                state->state = 0xB;
                state->field4 = 1;
                state->field6 = 0x19;
                goto done;
            }
            state->state = 0xC;
        }
        goto done;
    }

    timer = state->field8 + 1;
    state->field8 = timer;
    if ((s16)timer >= 8) {
        state->field8 = 0;
        state->toggleC ^= 1;
    }

redraw:
    func_80124908(state);

done:
    return;
}
