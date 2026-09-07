#include "common.h"


typedef struct Obj {
    char pad0[0x68];
    s16 state;
    char pad6A[2];
    u16 counter;
} Obj;

typedef struct Arg1 {
    s32 x;
    s32 y;
} Arg1;

typedef struct Arg2 {
    char pad0[0x1A];
    u16 cursor;
} Arg2;

typedef struct Entry {
    u8 bytes[8];
} Entry;

typedef struct EntryPair {
    Entry entries[2];
} EntryPair;

typedef struct Counter {
    u32 value;
    u32 pad[2];
} Counter;

extern EntryPair D_800898C4;
extern void *D_800898D4[];
extern u8 D_80011F81[];
extern Counter D_80012D5C;
extern s32 D_80083780[];

extern int abs(int);

extern s32 func_800352FC(void);
extern void func_80053DA8(s32);
extern void func_800673A0(void *, s32, s32);
extern s32 func_800C2AB4(Obj *);
/* Advances the interaction state, animating the cursor and vertical position. */
void func_800BF1C8(Obj *self, Arg1 *position, Arg2 *cursor_data) {
    EntryPair entries;
    s32 state;
    register s32 x_range_check;
    register s32 entry_index;
    register s32 target_x;
    register s32 counter_value;
    register s32 current_x;
    static void *const keepalive[5] = {&&state0, &&state3, &&state1, &&state2or5, &&state4};

    entries = D_800898C4;
    self->counter = self->counter - 1;
    state = self->state;
    if ((u32)state >= 6) {
        return;
    }
    goto *D_800898D4[state];

state0:
    do {
        const Counter *global_counter = &D_80012D5C;
        entry_index = 0;
        if (D_80011F81[0] != 0) {
            entry_index = 1;
        } else {
            counter_value = global_counter->value;
            if ((u32)counter_value >= 0x1388U) {
                entry_index = 1;
            }
        }
        func_800673A0(&entries.entries[entry_index], 0x188, 0x180);
    } while (0);
state3:
    {
        x_range_check = 0x3FFFFF;
        current_x = D_80083780[0];
        target_x = position->x;
        {
            s32 x_distance = abs((s32)((u32)current_x - (u32)target_x));
            x_range_check = x_range_check < x_distance;
        }
        if (x_range_check != 0) {
            return;
        }
    }
    if (func_800352FC() == 0) {
        return;
    }
    if (func_800C2AB4(self) == 0) {
        return;
    }
    func_80053DA8(0x50B);
    self->counter = 0x20;
    self->state = (u16)self->state + 1;
    return;

state1:
    if (D_80083780[1] < position->y + 0x800000) {
        D_80083780[1] += 0x40000;
    }
    {
        register s32 cursor = cursor_data->cursor;
        cursor -= 0x20;
        cursor_data->cursor = cursor;
        goto wait_for_counter;
    }

state2or5:
    if (func_800352FC() != 0 && func_800C2AB4(self) != 0) {
        return;
    }
    {
        s32 next_state = self->state;
        next_state += 1;
        next_state %= 6;
        self->state = (s16)next_state;
        return;
    }

state4:
    cursor_data->cursor += 0x20;
wait_for_counter:
    if ((s16)self->counter > 0) {
        return;
    }
    self->state = (u16)self->state + 1;
}
