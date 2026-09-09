#include "common.h"

typedef struct {
    u8 pad0[0x68];
    u16 unk68;
    s16 unk6A;
    u16 unk6C;
} TownCf814State;

typedef struct {
    u8 pad0[2];
    u16 unk2;
    u8 pad4[2];
    u16 unk6;
    u8 pad8[6];
    u16 unkE;
    u8 pad10[2];
    u16 unk12;
} TownCf814Obj;

/* Moves the object by fixed steps until its timer expires, then advances the state. */
void func_800CCF74(TownCf814State *motion, TownCf814Obj *target, s32 unused, s32 duration, s32 step_x, s32 step_y) {
    TownCf814Obj *obj = target;
    register s32 initial_dx ASM_REG("$5") = step_x;
    s16 phase = motion->unk6A;
    register s32 initial_dy ASM_REG("$2") = step_y;
    u16 timer;

    if (phase != 0) {
        if (phase != 1) {
            goto done;
        }
    } else {
        motion->unk6C = duration;
        obj->unkE = initial_dx;
        obj->unk12 = initial_dy;
        motion->unk6A++;
    }

    timer = motion->unk6C - 1;
    motion->unk6C = timer;
    if ((timer << 0x10) > 0) {
        s32 pos_x = obj->unk2;
        register s32 delta_x ASM_REG("$4") = obj->unkE;
        s32 pos_y = obj->unk6;
        s32 delta_y = obj->unk12;

        pos_x += delta_x;
        pos_y += delta_y;
        obj->unk2 = pos_x;
        obj->unk6 = pos_y;
        goto done;
    }

    motion->unk6A = 0;
    motion->unk68++;
done:
    ASM_SCHED_BARRIER();
}
