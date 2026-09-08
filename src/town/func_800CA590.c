#include "common.h"


extern void *D_800834A0;

extern void func_800C4174(void *);


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

/* Move the output toward the target position until the object countdown expires. */
void func_800C7CF0(void *moving_object, void *position) {
    register void *object ASM_REG("$7") = moving_object;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register void *out ASM_REG("$16") = position;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register s16 signed_frames ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
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

