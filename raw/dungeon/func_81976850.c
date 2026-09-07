#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

typedef struct Vec16 {
    s16 x;
    s16 y;
    s16 z;
} Vec16;

extern s32 D_80045340;
extern s32 D_800814A0;
extern void *D_800814A8;
extern u8 D_80082E80[];
extern s16 D_80083228;
extern u8 *D_800E3D18;

extern void func_80024188(void) __attribute__((noreturn));
extern void func_80024380() __attribute__((noreturn));
extern void func_800243A0(void) __attribute__((noreturn));
extern s32 func_8003DE58(void *, void *, Vec16 *, s16);
extern void func_8004491C(void *, void *);
extern s32 func_800644B8(s32);

void func_81976850(void *arg0, void *arg1, void *arg2)
{
    Vec16 delta;
    void *source;
    void *coords;
    void *target;
    void *global;
    void *object;
    register u8 *collision ASM_REG("$5");
    register void *incoming_a0 ASM_REG("$4");
    register u16 tail_z;
    s32 random;
    s32 index;
    s16 state;
    s16 timer;
    u16 value;
    u8 color;

    state = FIELD(arg0, s16, 0xC);
    if (state != 1) {
        if (state < 2) {
            object = (u8 *)arg0 - 0x20;
            if (state == 0) {
                goto initialize;
            }
            func_80024380(object);
            return;
        }
        collision = (u8 *)0x80080000;
        if (state == 2) {
            goto state_two;
        }
        ASM_KEEP(incoming_a0);
        func_80024380(incoming_a0, collision);
        return;
    }

    goto state_one;

initialize:
    func_8004491C(object, &D_80045340);
    FIELD(arg0, u16, 0xC)++;

state_one:
    source = FIELD(FIELD(arg0, void *, 0), void *, 0xC);
    if ((FIELD(source, u16, 0x14) & 0x8000) ||
        func_8003DE58(FIELD(source, void *, 8), source, &delta, 0)) {
        coords = FIELD(FIELD(arg0, void *, 0), void *, 8);
        FIELD(arg1, u16, 2) = FIELD(coords, u16, 2);
        FIELD(arg1, u16, 6) = FIELD(coords, u16, 6);
        value = FIELD(coords, u16, 0xA);
        FIELD(arg1, u16, 0xA) = value;

        if (!(FIELD(source, u16, 0x14) & 0x8000)) {
            FIELD(arg1, u16, 2) += delta.x;
            ASM_KEEP(arg1);
            FIELD(arg1, u16, 6) += delta.y;
            ASM_KEEP(arg1);
            tail_z = FIELD(arg1, u16, 0xA);
            tail_z += delta.z;
            ASM_TAILSLOT_PIN(tail_z);
            func_80024188();
            return;
        }
        ASM_KEEP(arg1);
        FIELD(arg1, u16, 0xA) = value - 0x20;
    }

    if (FIELD(FIELD(arg0, void *, 8), u16, 0) & 0x80) {
        FIELD(arg0, s16, 0xE) = 10;
        FIELD(arg0, u16, 0xC)++;
        func_80024380();
        return;
    }
    goto epilogue_work;

state_two:
    ASM_KEEP(collision);
    collision += 0x2E80;
    color = FIELD(arg2, u8, 0xE) + 8;
    FIELD(arg2, u8, 0xE) = color;
    FIELD(arg2, u8, 0xD) = color;
    FIELD(arg2, u8, 0xC) = color;

    target = FIELD(FIELD(arg0, void *, 4), void *, 8);
    FIELD(arg1, s32, 0xC) = FIELD(target, s32, 0);
    FIELD(arg1, s32, 0x10) = FIELD(target, s32, 4);

    global = D_800814A8;
    FIELD(arg1, s32, 0x14) =
        (FIELD(global, s16, 0x88) - 0x50) << 16;

    ASM_CLOBBER("$6");
    index = ((D_80083228 + FIELD(global, s16, 0x2A) + 0x100) >> 7) & 0x1C;
    index += (s32)D_800E3D18;
    if (func_8003DE58(
            FIELD((void *)index, void *, 0),
            collision,
            &delta,
            0) != 0) {
        FIELD(arg1, s32, 0xC) += delta.x << 16;
        FIELD(arg1, s32, 0x10) += delta.y << 16;
        FIELD(arg1, s32, 0x14) += delta.z << 16;
    }

    FIELD(arg1, s32, 0) +=
        (FIELD(arg1, s32, 0xC) - FIELD(arg1, s32, 0)) /
        FIELD(arg0, s16, 0xE);

    FIELD(arg1, s32, 4) +=
        (FIELD(arg1, s32, 0x10) - FIELD(arg1, s32, 4)) /
        FIELD(arg0, s16, 0xE);

    random = func_800644B8(FIELD(arg0, s16, 0xE) * 0xAA) << 7;
    FIELD(arg1, s32, 8) +=
        (FIELD(arg1, s32, 0x14) - FIELD(arg1, s32, 8)) /
        FIELD(arg0, s16, 0xE) - random;

    timer = FIELD(arg0, u16, 0xE) - 1;
    FIELD(arg0, s16, 0xE) = timer;
    if (timer <= 0) {
        FIELD(arg1, s32, 0) = FIELD(arg1, s32, 0xC);
        FIELD(arg1, s32, 4) = FIELD(arg1, s32, 0x10);
        FIELD(arg1, s32, 8) = FIELD(arg1, s32, 0x14);
        FIELD(arg0, u16, -2) |= 0x8000;
        D_800814A0 |= 0x8000;
        func_800243A0();
        return;
    }

epilogue_work:
    FIELD(arg0, u16, 0x10)++;
    FIELD(arg2, u16, 0x1A) += 0x300;
}
