#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern void *D_800834A0;

extern void func_800C4174(void *);
extern void func_800C7D9C(void);

void func_800C7CF0(void *arg0, void *arg1) {
    register void *object ASM_REG("$7") = arg0;
    register void *out ASM_REG("$16") = arg1;
    register s16 signed_frames ASM_REG("$4");
    u16 target_x;
    u16 target_y;
    u16 frames;

    target_x = FIELD(D_800834A0, u16, 2);
    target_y = FIELD(D_800834A0, u16, 6) - 0x42;
    frames = FIELD(object, u16, 0x6C) - 1;
    FIELD(object, u16, 0x6C) = frames;
    signed_frames = (s32)((u32)frames << 16) >> 16;

    if (signed_frames <= 0) {
        func_800C4174(object);
        FIELD(out, u16, 2) = target_x;
        FIELD(out, s16, 6) = target_y;
        func_800C7D9C();
        return;
    }

    FIELD(out, u16, 2) =
        (u16)(FIELD(out, u16, 2) +
              ((s16)target_x - (s16)FIELD(out, u16, 2)) /
                  signed_frames);
    FIELD(out, s16, 6) =
        (s16)((u16)FIELD(out, s16, 6) +
              ((s16)target_y - FIELD(out, s16, 6)) /
                  (s16)FIELD(object, u16, 0x6C));
}

/* MECHANISM: Preserve the seed's $a3 object and $s0 output roles and 0x20 frame.
   Split the signed frame count into a guarded $a0 live range; explicit shifts emit
   retail's sll-v0/sra-a0 pair and force move a0,a3 in the call delay slot. */
