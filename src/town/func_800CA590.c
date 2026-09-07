#include "common.h"

typedef struct S_800C7CF0_0 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
} S_800C7CF0_0;   /* D_800834A0 in func_800C7CF0 */

typedef struct S_800C7CF0_1 {
    u8 pad_00[0x6C];
    u16 unk_6C;
} S_800C7CF0_1;   /* object in func_800C7CF0 */

typedef struct S_800C7CF0_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
} S_800C7CF0_2;   /* out in func_800C7CF0 */



extern void *D_800834A0;

extern void func_800C4174(void *);
extern void func_800C7D9C(void);

void func_800C7CF0(void *arg0, void *arg1) {
    register void *object ASM_REG("$7") = arg0;   /* MATCH pin: retail register colouring depends on it */
    register void *out ASM_REG("$16") = arg1;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register s16 signed_frames ASM_REG("$4");   /* MATCH pin: load-bearing for the whole function shape */
    u16 target_x;
    u16 target_y;
    u16 frames;

    target_x = ((S_800C7CF0_0 *)D_800834A0)->unk_02;
    target_y = ((S_800C7CF0_0 *)D_800834A0)->unk_06 - 0x42;
    frames = ((S_800C7CF0_1 *)object)->unk_6C - 1;
    ((S_800C7CF0_1 *)object)->unk_6C = frames;
    signed_frames = (s32)((u32)frames << 16) >> 16;

    if (signed_frames <= 0) {
        func_800C4174(object);
        ((S_800C7CF0_2 *)out)->unk_02 = target_x;
        ((S_800C7CF0_2 *)out)->unk_06 = target_y;
        return;
    }

    ((S_800C7CF0_2 *)out)->unk_02 =
        (u16)(((S_800C7CF0_2 *)out)->unk_02 +
              ((s16)target_x - (s16)((S_800C7CF0_2 *)out)->unk_02) /
                  signed_frames);
    ((S_800C7CF0_2 *)out)->unk_06 =
        (s16)((u16)((S_800C7CF0_2 *)out)->unk_06 +
              ((s16)target_y - ((S_800C7CF0_2 *)out)->unk_06) /
                  (s16)((S_800C7CF0_1 *)object)->unk_6C);
}

/* MECHANISM: Preserve the seed's $a3 object and $s0 output roles and 0x20 frame.
   Split the signed frame count into a guarded $a0 live range; explicit shifts emit
   retail's sll-v0/sra-a0 pair and force move a0,a3 in the call delay slot. */
