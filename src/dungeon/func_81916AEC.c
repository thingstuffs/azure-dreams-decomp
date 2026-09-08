#include "common.h"

typedef s32 unk32;

typedef struct Copy6 {
    s32 word[6];
} Copy6;

#ifndef NULL
#define NULL 0
#endif


extern void *func_8003FC64(s32);
extern void func_8003DB94(void *, void *, s32);
extern void func_8004491C(void *, void *);

extern unk32 D_800241E4;
extern unk32 D_80045340;
extern unk32 D_800DEC70;


typedef struct S_800242EC_0 {
    u8 pad_00[0x8];
    Copy6 * unk_08;
    void * unk_0C;
    unk32 * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_800242EC_0;   /* temp_v0 in func_800242EC */

typedef struct S_800242EC_1 {
    u8 pad_00[0x4];
    s16 unk_04;
    s16 unk_06;
    s16 unk_08;
    u16 unk_0A;
} S_800242EC_1;   /* temp_v1 in func_800242EC */

typedef struct S_800242EC_2 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_800242EC_2;   /* arg2 in func_800242EC */

typedef struct S_800242EC_3 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    u16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_800242EC_3;   /* temp_s0 in func_800242EC */

void *func_800242EC(s32 arg0, void *arg1, S_800242EC_2 *arg2)
{
    S_800242EC_3 *temp_s0;
    void *temp_v0;
    S_800242EC_1 *temp_v1;
    Copy6 *temp_v1_2;
    register void *var_v0 ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

    temp_v0 = func_8003FC64(0x212);
    var_v0 = NULL;
    if (temp_v0 != NULL) {
        temp_v1 = (u8 *)temp_v0 + 0x20;
        ((S_800242EC_0 *)temp_v0)->unk_10 = &D_800241E4;
        ((S_800242EC_0 *)temp_v0)->unk_20 = arg0;
        temp_v1->unk_04 = 0;
        temp_v1->unk_06 = 8;
        temp_v1->unk_08 = 8;
        temp_v1->unk_0A = arg2->unk_2A;
        temp_s0 = ((S_800242EC_0 *)temp_v0)->unk_0C;
        temp_s0->unk_0D = 0x30;
        temp_s0->unk_0C = 0x30;
        temp_s0->unk_0E = 0xC0;
        temp_s0->unk_12 = 0x7DCF;
        temp_s0->unk_14 |= 0xC;
        temp_s0->unk_10 |= 0x20;
        temp_s0->unk_14 |= 0x100;
        func_8003DB94(temp_s0, &D_800DEC70, 0);
        temp_s0->unk_1E = 0x1000;
        temp_s0->unk_1C = 0x1000;
        func_8004491C(temp_v0, &D_80045340);
        temp_v1_2 = ((S_800242EC_0 *)temp_v0)->unk_08;
        var_v0 = temp_v0;
        *temp_v1_2 = *(Copy6 *)arg1;
    }
    return var_v0;
}
