#include "common.h"

#ifndef NULL
#define NULL 0
#endif

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

typedef struct ShortVec {
    s16 x;
    s16 y;
    s16 z;
} ShortVec;

extern s32 D_80045340;
extern s32 D_800814A0;
extern void *D_800814A8;
extern s16 D_80083228[5];
extern void *D_800E3D18;

extern void *func_8003DE58(void *, void *, ShortVec *, s16);
extern void func_8004491C(void *, void *);
extern s32 func_800644B8(s32);
extern void func_800B8994(void) __attribute__((noreturn));
extern void func_800B8BE8(void) __attribute__((noreturn));
extern void func_800B8BF8(void) __attribute__((noreturn));
extern void func_800B8D64(s16, s16, s16);
extern void func_800B8EA8(void *, s16, s16, s16, ShortVec *, s32, s32, s32, s32);

void func_800B8830(void *arg0, void *arg1, void *arg2) {
    ShortVec delta;
    s32 target[3];
    ShortVec current;
    s16 state;
    s16 one;
    register void *source ASM_REG("$16");
    register void *page_base ASM_REG("$4");
    void *position;
    s32 curve;
    u16 flags;
    u16 count;

    one = 1;
    state = FIELD(arg0, s16, 0x20);
    if (state != one) {
        if (state < 2) {
            if (state == 0) {
                goto state_zero;
            }
            func_800B8BE8();
            return;
        }
        page_base = (void *)0x80080000;
        if (state == 2) {
            goto state_two;
        }
        func_800B8BE8();
        return;

state_zero:
        FIELD(arg2, u8, 0xC) = FIELD(arg2, u8, 0xD) = FIELD(arg2, u8, 0xE) = 0x80;
        flags = FIELD(arg2, u16, 0x14);
        FIELD(arg2, s16, 0x1C) = FIELD(arg2, s16, 0x1E) = 0x1000;
        FIELD(arg2, u16, 0x14) = flags | 0xC;
        func_8004491C((u8 *)arg0 - 0x20, &D_80045340);
        FIELD(arg0, u16, 0x20)++;
    }

    source = FIELD(FIELD(arg0, void *, 0), void *, 0xC);
    ASM_KEEP(source);
    if ((FIELD(source, u16, 0x14) & 0x8000) ||
        func_8003DE58(FIELD(source, void *, 8), source, &delta, 0) != NULL) {
        u16 z;

        position = FIELD(FIELD(arg0, void *, 0), void *, 8);
        FIELD(arg1, u16, 2) = FIELD(position, u16, 2);
        FIELD(arg1, u16, 6) = FIELD(position, u16, 6);
        z = FIELD(position, u16, 0xA);
        FIELD(arg1, u16, 0xA) = z;

        if (!(FIELD(source, u16, 0x14) & 0x8000)) {
            u16 w;

            FIELD(arg1, u16, 2) += (u16)delta.x;
            FIELD(arg1, u16, 6) += (u16)delta.y;
            w = FIELD(arg1, u16, 0xA) + (u16)delta.z;
            ASM_TAILSLOT_PIN(w);
            func_800B8994();
            return;
        }
        ASM_SCHED_BARRIER();
        FIELD(arg1, u16, 0xA) = z - 0x20;
    }

    if (!(FIELD(FIELD(arg0, void *, 8), u16, 0) & 0x80)) {
        goto done;
    }
    FIELD(arg0, s16, 0x26) = 9;
    FIELD(arg0, u16, 0x20)++;
    func_800B8BE8();
    return;

state_two:
{
    register void *target_node ASM_REG("$3");
    void *entry;
    s32 index;
    s32 start_x;
    s32 start_y;
    s32 start_z;

    target_node = FIELD(FIELD(arg0, void *, 4), void *, 8);
    start_x = FIELD(arg1, s16, 2);
    start_y = FIELD(arg1, s16, 6);
    start_z = FIELD(arg1, s16, 0xA);
    target[0] = FIELD(target_node, s32, 0);
    target[1] = FIELD(target_node, s32, 4);
    target[2] = (FIELD(arg0, s16, 0x32) - 0x50) << 16;

    index = ((FIELD(page_base, s16, 0x3228) +
              FIELD(D_800814A8, s16, 0x2A) + 0x100) >> 7) & 0x1C;
    index += (s32)D_800E3D18;
    entry = FIELD((void *)index, void *, 0);
    if (func_8003DE58(entry, FIELD(FIELD(arg0, void *, 4), void *, 0xC), &delta, 0) != NULL) {
        target[0] += (s32)delta.x << 16;
        target[1] += (s32)delta.y << 16;
        target[2] += (s32)delta.z << 16;
    }

    FIELD(arg1, s32, 0) += (target[0] - FIELD(arg1, s32, 0)) / FIELD(arg0, s16, 0x26);
    FIELD(arg1, s32, 4) += (target[1] - FIELD(arg1, s32, 4)) / FIELD(arg0, s16, 0x26);
    curve = func_800644B8(FIELD(arg0, s16, 0x26) * 170);
    FIELD(arg1, s32, 8) +=
        (target[2] - FIELD(arg1, s32, 8)) / FIELD(arg0, s16, 0x26) - (curve << 7);

    current.x = FIELD(arg1, u16, 2);
    current.y = FIELD(arg1, u16, 6);
    current.z = FIELD(arg1, u16, 0xA);
    func_800B8EA8((u8 *)arg0 - 0x20, start_x, start_y, start_z, &current,
                  FIELD(arg0, s32, 0xC), 4, 0x1000, one);

    count = FIELD(arg0, u16, 0x26) - 1;
    FIELD(arg0, u16, 0x26) = count;
    if ((s16)count > 0) {
        goto done;
    }

    FIELD(arg1, s32, 0) = target[0];
    FIELD(arg1, s32, 4) = target[1];
    FIELD(arg1, s32, 8) = target[2];
    func_800B8D64(FIELD(arg1, s16, 2), FIELD(arg1, s16, 6), FIELD(arg1, s16, 0xA));
    ASM_SCHED_BARRIER();
    {
        register void *flags_page ASM_REG("$4");
        register s32 final_flags ASM_REG("$3");
        u16 object_flags;

        object_flags = FIELD(arg0, u16, -2);
        ASM_KEEP(object_flags);
        flags_page = (void *)0x80080000;
        ASM_KEEP_NV(flags_page);
        object_flags |= 0x8000;
        FIELD(arg0, u16, -2) = object_flags;
        ASM_SCHED_BARRIER();
        count = FIELD(arg0, u16, 0x20);
        ASM_KEEP(count);
        final_flags = FIELD(flags_page, s32, 0x14A0);
        count += 1;
        final_flags |= 0x8000;
        ASM_KEEP(final_flags);
        FIELD(arg0, u16, 0x20) = count;
        FIELD(flags_page, s32, 0x14A0) = final_flags;
    }
    func_800B8BF8();
    return;

done:
    FIELD(arg0, u16, 0x28)++;
}
}
