#include "common.h"
#include "m2c_compat.h"

typedef struct S_800BAF04_0 {
    u16 unk_00;
    u8 pad_02[0xA];
    s16 unk_0C;
    u8 pad_0E[0x2];
    u16 unk_10;
    s8 unk_12;
    u8 unk_13;
    u8 pad_14[0x20];
    u8 unk_34;
} S_800BAF04_0;   /* arg0 in func_800BAF04; pointer addresses record offset 0x2 */

typedef struct S_800BAF04_1 {
    u8 pad_00[0x12];
    s8 unk_12;
} S_800BAF04_1;   /* (arg0 + var_s0) in func_800BAF04 */


M2C_UNK func_8004491C();           /* extern */
s32 rand();                                /* extern */
M2C_UNK func_800BB02C();                            /* extern */
extern s32 D_800814A0[3];
extern void func_800BABA8(void);

void func_800BAF04(void *arg0) {
    s16 temp_v0;
    s16 temp_v1;
    s16 var_s0;
    u16 temp_v0_2;
    u8 temp_v0_3;

    temp_v1 = ((S_800BAF04_0 *)((u8 *)arg0 - 0x2))->unk_0C;
    if (temp_v1 != 0) {
        if (temp_v1 != 1) {
            return;
        }
        goto block_7;
    }
    var_s0 = 0;
    do {
        ((S_800BAF04_1 *)((arg0 + var_s0)))->unk_12 = (s8) (rand() & 0x1F);
        temp_v0 = var_s0 + 1;
        var_s0 = temp_v0;
    } while (temp_v0 < 0x40);
    ((S_800BAF04_0 *)((u8 *)arg0 - 0x2))->unk_10 = 0U;
    ((S_800BAF04_0 *)((u8 *)arg0 - 0x2))->unk_12 = 0;
    ((S_800BAF04_0 *)((u8 *)arg0 - 0x2))->unk_34 = 0U;
    ((S_800BAF04_0 *)((u8 *)arg0 - 0x2))->unk_13 = 1U;
    func_8004491C(arg0 - 0x20, func_800BABA8);
    ((S_800BAF04_0 *)((u8 *)arg0 - 0x2))->unk_0C = (s16) ((u16) ((S_800BAF04_0 *)((u8 *)arg0 - 0x2))->unk_0C + 1);
block_7:
    temp_v0_2 = ((S_800BAF04_0 *)((u8 *)arg0 - 0x2))->unk_10 + 1;
    ((S_800BAF04_0 *)((u8 *)arg0 - 0x2))->unk_10 = temp_v0_2;
    if ((s16) temp_v0_2 >= 0x11) {
        ((S_800BAF04_0 *)((u8 *)arg0 - 0x2))->unk_10 = 0U;
    }
    temp_v0_3 = ((S_800BAF04_0 *)((u8 *)arg0 - 0x2))->unk_34 + 1;
    ((S_800BAF04_0 *)((u8 *)arg0 - 0x2))->unk_34 = temp_v0_3;
    if ((s8) temp_v0_3 >= 0x21) {
        ((S_800BAF04_0 *)((u8 *)arg0 - 0x2))->unk_34 = 0x20U;
        ((S_800BAF04_0 *)((u8 *)arg0 - 0x2))->unk_12 = 1;
    }
    if (((S_800BAF04_0 *)((u8 *)arg0 - 0x2))->unk_13 == 0) {
        ((S_800BAF04_0 *)((u8 *)arg0 - 0x2))->unk_00 = (u16) (((S_800BAF04_0 *)((u8 *)arg0 - 0x2))->unk_00 | 0x8000);
        D_800814A0[0] |= 0x8000;
    }
}
