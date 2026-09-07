#include "common.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_800242E0_0 {
    void * unk_00;
    u16 unk_04;
    u16 unk_06;
    u16 unk_08;
    u16 unk_0A;
    u16 unk_0C;
} S_800242E0_0;   /* arg0 in func_800242E0 */

typedef struct S_800242E0_1 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_800242E0_1;   /* temp_v1 in func_800242E0 */

typedef struct S_800242E0_2 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800242E0_2;   /* arg1 in func_800242E0 */




extern void func_8003DB94(void *, void *, s32);
extern void func_800478B8(void *);
extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);
extern s32 rand(void);
extern u8 D_800DEC70[];

void func_800242E0(S_800242E0_0 *arg0, S_800242E0_2 *arg1, Rec_D_80082E80 *arg2) {
    s32 temp_s0;
    u16 temp_v0;
    S_800242E0_1 *temp_v1;

    temp_v1 = arg0->unk_00;
    temp_v1->unk_14 = (u16)(temp_v1->unk_14 + 1);
    temp_v0 = arg0->unk_04 + arg0->unk_06;
    arg0->unk_04 = temp_v0;
    if ((s16)temp_v0 < -0x80) {
        temp_s0 = rand() % 0x1000;
        arg1->unk_02 = (s16)(arg0->unk_08 + ((func_800644B8(temp_s0) * 2) >> 8));
        arg1->unk_06 = (s16)(arg0->unk_0A + ((func_80064584(temp_s0) * 2) >> 8));
        arg0->unk_04 = (u16)(arg0->unk_04 + 0x80);
        arg0->unk_06 = (u16)(-6 - (rand() % 5));
    }
    arg1->unk_0A = (s16)(arg0->unk_0C + arg0->unk_04);
    func_800478B8(arg2);
    if (arg2->unk_14.at00_u16.v & 0x6000) {
        func_8003DB94(arg2, D_800DEC70, 0);
    }
}
