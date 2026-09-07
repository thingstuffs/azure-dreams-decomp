#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern void *D_800E3D7C[];
extern u32 D_800814A0[];
extern s32 D_800814A8[];
extern u8 D_80081484[];

extern s32 func_8003DE58();
extern s32 func_800644B8();
extern void func_8008D614();
extern void func_8008D680();
extern void func_8008D790();
extern s32 func_800A8E74();

void func_8008D470(void *arg0, void *arg1, void *arg2) {
    s16 offsets[3];
    s16 state;
    s32 mode;
    s16 light;
    s32 current0;
    s32 current1;
    s32 current2;
    s32 result;
    s32 spawned;
    s32 completed;
    u16 next;
    u8 color;
    void *target;
    void *entity;

    state = FIELD(arg0, s16, 0xA2);
    completed = 0;
    if (state != 0) {
        if (state != 1) {
            func_8008D680();
            return;
        }
    } else {
        FIELD(arg0, u16, 0xA4) = 6;
        FIELD(arg0, s16, 0xA2) = FIELD(arg0, u16, 0xA2) + 1;
    }

    target = FIELD(arg0, void *, 0x90);
    if (func_8003DE58(FIELD(target, s32, 8), target, offsets, 0) != 0 &&
        FIELD(D_800E3D7C[0], void *, 0x124) != 0) {
        FIELD(arg2, s16, 0x1C) = 0x1000;
        next = FIELD(arg0, u16, 0xA4) - 1;
        FIELD(arg0, u16, 0xA4) = next;
        if ((s16)next > 0) {
            current0 = FIELD(arg1, s32, 0);
            FIELD(arg1, s32, 0) = current0 +
                (FIELD(FIELD(arg0, void *, 0x8C), s32, 0) +
                 (offsets[0] << 16) - current0) / (s16)next;

            current1 = FIELD(arg1, s32, 4);
            FIELD(arg1, s32, 4) = current1 +
                (FIELD(FIELD(arg0, void *, 0x8C), s32, 4) +
                 (offsets[1] << 16) - current1) / FIELD(arg0, s16, 0xA4);

            current2 = FIELD(arg1, s32, 8);
            FIELD(arg1, s32, 8) = current2 +
                (FIELD(FIELD(arg0, void *, 0x8C), s32, 8) +
                 (offsets[2] << 16) - (FIELD(arg0, s16, 0xA4) << 21) - current2) /
                FIELD(arg0, s16, 0xA4);
            func_8008D614();
            return;
        }

        FIELD(arg0, u16, 0xA4) = 0;
        FIELD(arg1, u16, 2) = FIELD(FIELD(arg0, void *, 0x8C), u16, 2) + (u16)offsets[0];
        FIELD(arg1, u16, 6) = FIELD(FIELD(arg0, void *, 0x8C), u16, 6) + (u16)offsets[1];
        FIELD(arg1, u16, 0xA) = FIELD(FIELD(arg0, void *, 0x8C), u16, 0xA) + (u16)offsets[2];
        if (FIELD(arg0, s16, 0xAA) == 0) {
            FIELD(arg0, s16, 0xAA) = 1;
            func_8008D680();
            return;
        }
        completed = 1;
    } else {
        state = FIELD(arg0, s16, 0xAA);
        if (state != 0) {
            goto nonzero_state;
        }
        FIELD(arg2, s16, 0x1C) = 0;
        func_8008D680();
        return;
nonzero_state:
        if (state == 1) {
            if (FIELD(arg0, s16, 0xAE) == 0) {
                FIELD(arg0, u16, -2) |= 0x8000;
                D_800814A0[0] |= 0x8000;
            }
        }
    }

    if (FIELD(arg0, s16, 0xAE) != 0) {
        light = (func_800644B8(FIELD(arg0, s16, 0xB4) << 8) >> 6) + 0x80;
        color = FIELD(arg2, u8, 0xC);
        color += (light - color) >> 2;
        FIELD(arg2, u8, 0xC) = color;
        FIELD(arg2, u8, 0xD) = color;
        FIELD(arg2, u8, 0xE) = color;
    }

    FIELD(arg0, u16, 0xB4)++;
    FIELD(arg0, u16, 0xA8)--;
    if (FIELD(arg0, s16, 0xA8) <= 0) {
        mode = FIELD(arg0, s16, 0xAC);
        FIELD(arg0, u16, 0xA8) = 0;
        if (mode == 1) {
            spawned = func_800A8E74(arg0, arg1, arg2, D_800814A8[0], FIELD(arg0, s32, 0x9C), -1);
            ASM_KEEP(arg0);
            if (spawned != 0) {
                entity = (void *)(spawned + 0x20);
                target = D_800E3D7C[0];
                FIELD(target, void *, 0x124) = entity;
                FIELD(entity, void *, 0x9C) = D_80081484;
                FIELD(entity, u32, 0x1C) |= 0x80000;
                FIELD(FIELD(target, void *, 0x124), void *, 0x60) = target;
                FIELD(target, u32, 0x1C) |= 0x100000;
                func_8008D790(entity, target);
                return;
            }
        } else {
            if (mode == 2) {
                goto set_flag;
            }
            result = mode ? mode : completed;
            if (result != 0) {
                return;
            }
set_flag:
            FIELD(arg0, u16, -2) |= 0x8000;
            D_800814A0[0] |= 0x8000;
        }
    }
}
