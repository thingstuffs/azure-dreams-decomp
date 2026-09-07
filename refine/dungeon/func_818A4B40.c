#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8003DB94();  /* extern */
M2C_UNK func_800478B8();                      /* extern */
s32 func_800644B8();                             /* extern */
s32 func_80064584();                             /* extern */
s32 rand();                                /* extern */
extern M2C_UNK D_800DECF8;

typedef struct S_818A4B40_0 {
    void * unk_00;
    u16 unk_04;
    u16 unk_06;
    u16 unk_08;
    u16 unk_0A;
    u16 unk_0C;
} S_818A4B40_0;   /* arg0 in func_818A4B40 */

typedef struct S_818A4B40_1 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_818A4B40_1;   /* temp_v1 in func_818A4B40 */

typedef struct S_818A4B40_2 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_818A4B40_2;   /* arg1 in func_818A4B40 */

typedef struct S_818A4B40_3 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_818A4B40_3;   /* arg2 in func_818A4B40 */

/* Advance the height offset, randomize position on wrap, and update the object. */
void func_818A4B40(S_818A4B40_0 *motion, S_818A4B40_2 *position, S_818A4B40_3 *object) {
    s16 angle;
    s32 random_value;
    s32 biased_random;
    u16 height_offset;
    S_818A4B40_1 *counter;

    counter = motion->unk_00;
    counter->unk_14 = (u16) (counter->unk_14 + 1);
    height_offset = motion->unk_04 + motion->unk_06;
    motion->unk_04 = height_offset;
    if ((s16) height_offset < -0x80) {
        random_value = rand();
        biased_random = random_value;
        if (random_value < 0) {
            biased_random = random_value + 0xFFF;
        }
        angle = random_value - ((biased_random >> 0xC) << 0xC);
        position->unk_02 = (s16) (motion->unk_08 + ((s32) (func_800644B8(angle) * 2) >> 8));
        position->unk_06 = (s16) (motion->unk_0A + ((s32) (func_80064584(angle) * 2) >> 8));
        motion->unk_04 = (u16) (motion->unk_04 + 0x80);
        motion->unk_06 = (u16) (-6 - (rand() % 5));
    }
    position->unk_0A = (s16) (motion->unk_0C + motion->unk_04);
    func_800478B8(object);
    if (object->unk_14 & 0x6000) {
        func_8003DB94(object, &D_800DECF8, 0);
    }
}
