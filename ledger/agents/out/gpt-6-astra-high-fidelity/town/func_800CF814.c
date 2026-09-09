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

void func_800CCF74(TownCf814State *arg0, TownCf814Obj *arg1, s32 unused, s32 arg3, s32 arg4, s32 arg5) {
    TownCf814Obj *obj = arg1;
    register s32 stack_arg4 ASM_REG("$5") = arg4;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s16 state = arg0->unk6A;
    register s32 stack_arg5 ASM_REG("$2") = arg5;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    u16 timer;

    if (state != 0) {
        if (state != 1) {
            goto done;
        }
    } else {
        arg0->unk6C = arg3;
        obj->unkE = stack_arg4;
        obj->unk12 = stack_arg5;
        arg0->unk6A++;
    }

    timer = arg0->unk6C - 1;
    arg0->unk6C = timer;
    if ((timer << 0x10) > 0) {
        register s32 curX ASM_REG("$2") = obj->unk2;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        register s32 x ASM_REG("$4") = obj->unkE; /* MATCH: retain the X increment register after removing the label call. */
        s32 curY = obj->unk6;
        s32 y = obj->unk12;

        curX += x;
        curY += y;
        obj->unk2 = curX;
        obj->unk6 = curY;
        goto done;
    }

    arg0->unk6A = 0;
    arg0->unk68++;
done:
    ASM_SCHED_BARRIER(); /* MATCH: preserve both jumps to the shared return. */
}
