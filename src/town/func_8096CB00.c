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

extern void SD_Call(s32);
extern s32 func_80123200(u8);
extern void func_801237A4(TownState *);
extern void func_801248C0(TownState *);
extern void func_80124908(TownState *);

extern u8 D_80083160[];
extern u8 D_801269F8[];
extern ImageList D_801278B0[];

/* Handles selection navigation, scrolling, transitions, and the idle toggle timer. */
void func_80124F98(TownState *state)
{
    u8 *input;
    u32 buttons;
    s32 index_count;
    s32 max_scroll;
    u8 current_index;
    u8 previous_index;
    u8 next_index;
    u8 side_choice;
    u16 toggle_timer;

    input = D_80083160;
    if (*(u32 *)(input + 0x10) & 0x20) {
        SD_Call(0x702);
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

        max_scroll = (D_801278B0[state->index].count - 3) << 4;
        selection = D_801269F8;
        if (((max_scroll & 0xF0) - 4) >= selection[9]) {
            state->state = 0xE;
            selection[9] += 4;
        } else {
            selection[9] = max_scroll;
        }
        goto redraw_transition;
    }

    if (buttons & 0x8000) {
        index_count = 0x32;
        state->old_index = state->index;
decrement_loop:
        if (state->index == 0) {
            state->index = index_count;
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
            u32 packed_index;
            u32 index_bits;

            packed_index = state->index;
            index_bits = packed_index;
            ASM_KEEP(index_bits);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
            state->digit0 = packed_index >> 4;
            state->digit1 = (index_bits >> 3) & 1;
            state->digit2 = state->index & 7;
        }

        current_index = state->index;
        previous_index = state->old_index;
        if (current_index < previous_index) {
            SD_Call(0x702);
            func_801248C0(state);
            state->side ^= 1;
            func_801237A4(state);
            side_choice = state->choices[state->side];
            if (side_choice != state->index) {
                state->state = 0xC;
                goto done;
            }
            state->state = 0xA;
            state->field4 = 1;
            state->field6 = 0x19;
            goto done;
        }
        if (previous_index < current_index) {
            SD_Call(0x702);
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
        index_count = 0x32;
        state->old_index = state->index;
increment_loop:
        next_index = state->index + 1;
        state->index = next_index;
        if ((next_index & 0xFF) == index_count) {
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
            u32 packed_index;
            u32 index_bits;

            packed_index = state->index;
            index_bits = packed_index;
            ASM_KEEP(index_bits);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
            state->digit0 = packed_index >> 4;
            state->digit1 = (index_bits >> 3) & 1;
            state->digit2 = state->index & 7;
        }

        current_index = state->index;
        previous_index = state->old_index;
        if (current_index < previous_index) {
            SD_Call(0x702);
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
        if (previous_index < current_index) {
            SD_Call(0x702);
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

    toggle_timer = state->field8 + 1;
    state->field8 = toggle_timer;
    if ((s16)toggle_timer >= 8) {
        state->field8 = 0;
        state->toggleC ^= 1;
    }

redraw:
    func_80124908(state);

done:
    return;
}
