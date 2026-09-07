#include "common.h"

#ifndef NULL
#define NULL 0
#endif

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern u8 D_800C4F20[];
extern u8 D_800C55A0[];
extern u8 D_800DF630[];

extern void *func_8003FC64(s32);
extern void func_8004491C(void *, void *);
extern s16 rand(void *, void *);
extern void func_800A56E0(s32);

void *func_800C542C(void *arg0, s16 arg1, s32 arg2, s16 arg3)
{
    void *object;
    void *display;
    void *source;
    void *target;
    void *record;
    void *callback;
    register void *call_object ASM_REG("$4");
    register s16 stored_arg3 ASM_REG("$22");
    s16 mode;
    s32 scaled;
    s32 parent;

    object = func_8003FC64(0x12);
    stored_arg3 = arg3;
    if (object != NULL) {
        call_object = object;
        ASM_KEEP(call_object);
        callback = D_800C4F20;
        ASM_KEEP(callback);
        FIELD(object, void *, 0x10) = callback;
        func_8004491C(call_object, D_800C55A0);

        display = FIELD(object, void *, 0xC);
        FIELD(display, s32, 0xC) = 0x808080;
        FIELD(display, void *, 8) = D_800DF630;
        FIELD(display, s16, 6) = 0xC;

        source = FIELD(arg0, void *, -0x18);
        target = FIELD(object, void *, 8);
        FIELD(target, u16, 2) = FIELD(source, u16, 2);
        FIELD(target, u16, 6) = FIELD(source, u16, 6);
        record = (u8 *)object + 0x20;
        FIELD(target, u16, 0xA) = FIELD(source, u16, 0xA);

        scaled = arg2 << 0x10;
        FIELD(record, s16, 0x30) = arg1;
        FIELD(record, void *, 0x1C) = source;
        parent = FIELD(arg0, s32, -0x14);
        FIELD(record, s16, 0x2E) = (s16)(scaled >> 5);
        FIELD(record, void *, 0x24) = arg0;
        FIELD(record, s32, 0x20) = parent;
        FIELD(display, s16, 0x20) = 0x2000;
        FIELD(record, s16, 0x32) = 0x400;
        FIELD(record, s16, 0x2C) = rand(source, display);

        if (arg3 == 1) {
            FIELD(record, s16, 0x2A) = 0;
        } else {
            if (arg3 == 0) {
                func_800A56E0(0x802);
                mode = 0x10;
            } else {
                func_800A56E0(0x802);
                mode = 0x20;
            }
            FIELD(record, s16, 0x2A) = mode;
        }

        ASM_KEEP(stored_arg3);
        FIELD(record, s16, 0x36) = stored_arg3;
        FIELD(arg0, s32, 0x14) |= 0x100000;
    }
    return object;
}

/* MECHANISM: The true rowbase function uses a 0x30 frame with s2/s4/s5/s3
   holding the four arguments, a post-call s6 copy, and s1/s0 object bases.
   The 800C5558/800C555C targets are local mode-store joins, not tail calls. */
