#include "common.h"

typedef struct TownObject {
    u8 pad0[0x70];
    s16 state;
    s16 value72;
    u8 pad74[2];
    s16 random76;
} TownObject;

typedef struct TownState {
    TownObject *objects[3];
    s16 state;
    s16 timer;
    s16 table_x;
    s16 field12;
    s16 threshold;
    u16 counter;
    s16 table_y;
    u16 flags;
} TownState;

extern u16 D_800135BE;
extern void *D_80020164[6];
extern u8 D_80026F80[];
extern int D_800814A0;
extern u8 D_80082E80[];
extern u32 D_80082E8C;
extern u8 D_80083160[];
extern s16 D_800834C8;
extern s32 D_80083780[];

extern void func_800252B8(s32, s32, s32, s32);
extern void func_80033B78(s32);
extern void func_80033B9C(s32);
extern void func_8003F540(s32, s32, s32, s32);
extern void func_800483AC(s32);
extern void func_80048568(s32);
extern void func_80053DA8(s32);
extern s32 rand(void);
extern void func_8009AC0C(void);
extern void func_8009AC8C(void);
extern void func_800C15C0(s32, s32);

void func_80025BC8(TownState *state)
{
    u8 *global;
    s32 current;
    s32 i;
    s32 x;
    static void *const sw_keep[6] = {
        &&case_0, &&case_1, &&case_2, &&case_3, &&case_4, &&case_5
    };

    global = D_80083160;
    (void)sw_keep;
    if (*(u32 *)(global + 0x10) & 0x40) {
        state->counter = 0;
    }
    state->counter++;

    current = state->state;
    if ((u32)current >= 6) {
        goto cleanup;
    }
    goto *D_80020164[current];

case_0:
    {
        TownState *state_zero = state;
        s32 target;
        TownObject *first;
        u16 timer;

        func_80048568(5);
        func_8009AC0C();
        state_zero->state = 1;
        ASM_SCHED_BARRIER();
        target = -0x80;
        *(s16 *)(global + 0xAC) +=
            (target - *(s16 *)(global + 0xAC)) >> 1;
        ASM_SCHED_BARRIER();
        first = state_zero->objects[0];
        if (first->state != 1) {
            goto cleanup;
        }
        *(s16 *)(global + 0xAC) = target;
        state_zero->counter = 0;
        timer = *(u16 *)(D_80026F80 +
                        state_zero->table_x * 40 + state_zero->table_y * 400);
        state_zero->state = 2;
        state_zero->timer = timer;
        goto cleanup;
    }

case_1:
    D_800834C8 = 0x400;
    ASM_SCHED_BARRIER();
    {
        u16 flags = state->flags;

        if (flags & 1) {
            state->flags = flags & ~1;
            state->table_x++;
            if (state->table_x >= 10) {
                state->state = 3;
                state->timer = 30;
                goto done;
            }
            state->timer = *(u16 *)(D_80026F80 +
                                    state->table_x * 40 + state->table_y * 400);
            goto done;
        }
    }

    state->timer--;
    if (state->timer > 0) {
        goto cleanup;
    }
    state->flags |= 1;
    do {
        TownObject **object;

        i = 2;
        object = &state->objects[2];
        do {
            (*object)->random76 = rand() % 3;
            object--;
            i--;
        } while (i >= 0);
    } while (state->objects[0]->random76 == state->objects[1]->random76 ||
             state->objects[1]->random76 == state->objects[2]->random76 ||
             state->objects[2]->random76 == state->objects[0]->random76);
    goto cleanup;

case_2:
    if (state->flags & 4) {
        goto cleanup;
    }
    state->timer--;
    if (state->timer > 0) {
        goto cleanup;
    }
    func_80053DA8(0xB1);
    {
        TownObject **object;
        s32 object_state;

        i = 2;
        object_state = i;
        object = &state->objects[2];
        do {
            u8 *part = (u8 *)*object + 0x20;

            object--;
            i--;
            *(s16 *)(part + 0x52) = 0;
            *(s16 *)(part + 0x50) = object_state;
        } while (i >= 0);
    }
    func_8009AC8C();
    func_8009AC0C();
    state->timer = 25;
    state->state = 4;
    goto cleanup;

case_3:
    if (state->timer < 15) {
        *(s16 *)(global + 0xAC) >>= 1;
    }
    state->timer--;
    if (state->timer >= 0) {
        u8 *color = D_80082E80;

        i = 7;
        color[0xE] += (0x90 - color[0xE]) >> 1;
        color[0xD] = color[0xE];
        color[0xC] = color[0xE];
        do {
            x = D_80083780[0] +
                (((rand() & 0x3F) - 0x20) << 16);
            func_800252B8(0xF0F0F0, x,
                          D_80083780[1] +
                              (((rand() & 0x3F) - 0x20) << 16),
                          0);
            i--;
        } while (i >= 0);
    }
    if (state->flags & 2) {
        goto cleanup;
    }
    if (state->timer > 0) {
        goto cleanup;
    }
    *(s16 *)(global + 0xAC) = 0;
    state->state = 5;
    state->flags |= 8;
    goto cleanup;

case_4:
    {
        u16 progress;
        s32 threshold;

        func_800C15C0(0x20, 0x200);
        func_8009AC8C();
        progress = D_800135BE;
        threshold = state->threshold;
        ASM_KEEP(progress);
        if ((s16)progress < threshold) {
            func_8003F540(0, 0x2C3D, 0x01000001, 0x01000271);
            func_80053DA8(0x300);
            D_800135BE = state->threshold;
            func_80033B9C(0xAE4);
        } else {
            func_8003F540(0, 0x2C3D, 0, 0x01000290);
            func_80053DA8(0x300);
            func_80033B78(0xAE4);
        }
        func_800483AC(2);
        D_80082E8C = 0x00808080;
        *(u16 *)((u8 *)state - 2) |= 0x8000;
        D_800814A0 |= 0x8000;
        goto cleanup;
    }

case_5:
cleanup:
    state->flags &= ~6;
done:
    return;
}
