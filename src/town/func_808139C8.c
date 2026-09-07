#include "common.h"

#ifndef NULL
#define NULL 0
#endif


typedef struct FiveWords {
    s32 words[5];
} FiveWords;

extern void *func_800373DC(s32);
extern void func_8003BC18(void *, void *);
extern u8 D_8003C558[12];
extern u8 D_8052F2C8[];
extern u8 D_8028E170[];


typedef struct S_808139C8_0 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_808139C8_0;   /* temp_a0 in func_808139C8 */

typedef struct S_808139C8_1 {
    u8 pad_00[0x4];
    s8 unk_04;
    s8 unk_05;
    u8 pad_06[0x2];
    s32 unk_08;
    s32 unk_0C;
    u8 pad_10[0x4];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_808139C8_1;   /* temp_v1 in func_808139C8 */

void func_808139C8(FiveWords *arg0, s32 arg1)
{
    u8 *temp_a0;
    u8 *temp_v0;
    u8 *temp_v1;

    temp_v0 = func_800373DC(0x136);
    if (temp_v0 != NULL) {
        (*(FiveWords *)((u8 *)temp_v0 + 0x20)) = *arg0;
        (*(s32 *)((u8 *)temp_v0 + 0x10)) = (s32)D_8052F2C8;
        func_8003BC18(temp_v0, D_8003C558);
        temp_a0 = (*(u8 * *)((u8 *)temp_v0 + 8));
        temp_v1 = (*(u8 * *)((u8 *)temp_v0 + 0xC));
        ((S_808139C8_0 *)temp_a0)->unk_00 = 0x05380000;
        ((S_808139C8_0 *)temp_a0)->unk_04 = arg1;
        ((S_808139C8_0 *)temp_a0)->unk_08 = 0xFFE00000;
        ((S_808139C8_1 *)temp_v1)->unk_1E = 0x1000;
        ((S_808139C8_1 *)temp_v1)->unk_1C = 0x1000;
        ((S_808139C8_1 *)temp_v1)->unk_08 = (s32)D_8028E170;
        ((S_808139C8_1 *)temp_v1)->unk_04 = 0;
        ((S_808139C8_1 *)temp_v1)->unk_05 = 0;
        ((S_808139C8_1 *)temp_v1)->unk_0C = 0x808080;
        ((S_808139C8_1 *)temp_v1)->unk_14 = ((S_808139C8_1 *)temp_v1)->unk_14 | 0x80;
    }
}
