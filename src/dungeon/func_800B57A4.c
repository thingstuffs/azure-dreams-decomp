#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8004491C();           /* extern */
s32 rand();                                /* extern */
extern s32 D_800814A0[3];
extern void func_800BABA8(void);


typedef struct S_800BAF04_0_pre {
    u16 unk_00;
} S_800BAF04_0_pre;   /* the 0x2 bytes before arg0 in func_800BAF04, addressed as arg0[-1] */

typedef struct S_800BAF04_0 {
    u8 pad_00[0xA];
    s16 unk_0A;
    u8 pad_0C[0x2];
    u16 unk_0E;
    s8 unk_10;
    u8 unk_11;
    u8 pad_12[0x20];
    u8 unk_32;
} S_800BAF04_0;   /* arg0 in func_800BAF04 */

typedef struct S_800BAF04_1 {
    u8 pad_00[0x12];
    s8 unk_12;
} S_800BAF04_1;   /* (arg0 + var_s0) in func_800BAF04 */

void func_800BAF04(void *arg0) {
    s16 temp_v0;
    s16 temp_v1;
    s16 var_s0;
    u16 temp_v0_2;
    u8 temp_v0_3;

    temp_v1 = ((S_800BAF04_0 *)arg0)->unk_0A;
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
    ((S_800BAF04_0 *)arg0)->unk_0E = 0U;
    ((S_800BAF04_0 *)arg0)->unk_10 = 0;
    ((S_800BAF04_0 *)arg0)->unk_32 = 0U;
    ((S_800BAF04_0 *)arg0)->unk_11 = 1U;
    func_8004491C(arg0 - 0x20, func_800BABA8);
    ((S_800BAF04_0 *)arg0)->unk_0A = (s16) ((u16) ((S_800BAF04_0 *)arg0)->unk_0A + 1);
block_7:
    temp_v0_2 = ((S_800BAF04_0 *)arg0)->unk_0E + 1;
    ((S_800BAF04_0 *)arg0)->unk_0E = temp_v0_2;
    if ((s16) temp_v0_2 >= 0x11) {
        ((S_800BAF04_0 *)arg0)->unk_0E = 0U;
    }
    temp_v0_3 = ((S_800BAF04_0 *)arg0)->unk_32 + 1;
    ((S_800BAF04_0 *)arg0)->unk_32 = temp_v0_3;
    if ((s8) temp_v0_3 >= 0x21) {
        ((S_800BAF04_0 *)arg0)->unk_32 = 0x20U;
        ((S_800BAF04_0 *)arg0)->unk_10 = 1;
    }
    if (((S_800BAF04_0 *)arg0)->unk_11 == 0) {
        ((S_800BAF04_0_pre *)arg0)[-1].unk_00 = (u16) (((S_800BAF04_0_pre *)arg0)[-1].unk_00 | 0x8000);
        D_800814A0[0] |= 0x8000;
    }
}
