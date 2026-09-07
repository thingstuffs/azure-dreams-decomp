#include "common.h"

typedef struct S_80024334_0 {
    void * unk_00;
    u8 pad_04[0x4];
    s16 unk_08;
} S_80024334_0;   /* arg0 in func_80024334 */

typedef struct S_80024334_1 {
    u8 pad_00[0x4];
    u16 unk_04;
    u16 unk_06;
    u16 unk_08;
    u8 pad_0A[0x2];
    u16 unk_0C;
    u16 unk_0E;
    u16 unk_10;
    u8 pad_12[0x2];
    s32 unk_14;
    u8 pad_18[0xC];
    u16 unk_24;
} S_80024334_1;   /* obj in func_80024334 */

typedef struct S_80024334_2 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u8 pad_10[0x4];
    u16 unk_14;
} S_80024334_2;   /* arg2 in func_80024334 */

typedef struct S_80024334_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80024334_3;   /* arg1 in func_80024334 */



void func_80024334(S_80024334_0 *arg0, S_80024334_3 *arg1, S_80024334_2 *arg2) {
    S_80024334_1 *obj;

    obj = arg0->unk_00;

    if (obj->unk_24 & 1) {
        arg2->unk_14 |= 0x80;
    } else {
        arg2->unk_14 &= 0xFF7F;
    }

    if (obj->unk_14 != 0) {
        arg2->unk_0C = 0x808080;
    } else {
        arg2->unk_0C = 0xFFFFFF;
    }

    if (arg0->unk_08 != 0) {
        arg1->unk_02 = obj->unk_04;
        arg1->unk_06 = obj->unk_06;
        arg1->unk_0A = obj->unk_08;
    } else {
        arg1->unk_02 = obj->unk_0C;
        arg1->unk_06 = obj->unk_0E;
        arg1->unk_0A = obj->unk_10;
    }
}
