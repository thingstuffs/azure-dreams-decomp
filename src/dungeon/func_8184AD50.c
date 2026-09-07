#include "common.h"

typedef struct S_80024550_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80024550_0;   /* temp_v0 in func_80024550 */

typedef struct S_80024550_1 {
    u8 pad_00[0x8];
    s16 unk_08;
} S_80024550_1;   /* temp_s2 in func_80024550 */

typedef struct S_80024550_2 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    u16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x4];
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} S_80024550_2;   /* temp_s0 in func_80024550 */

typedef struct S_80024550_3 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80024550_3;   /* temp_s0_2 in func_80024550 */

typedef struct S_80024550_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80024550_4;   /* arg0 in func_80024550 */



extern void *func_8003FC64(s32);
extern s32 rand(void);
extern void func_8003DB94(void *, void *, s32);
extern s32 func_80064584(s32);
extern s32 func_800644B8(s32);
extern void func_8004491C(void *, void *);

extern u8 D_800244A4[];
extern u8 D_80045340[];
extern u8 D_80083160[];
extern u8 D_800DE870[];

void func_80024550(S_80024550_4 *arg0)
{
    s16 *global_base;
    s32 temp_v1;
    s32 var_v0;
    S_80024550_2 *temp_s0;
    S_80024550_3 *temp_s0_2;
    S_80024550_1 *temp_s2;
    void *temp_v0;

    global_base = (s16 *)D_80083160;
    temp_v0 = func_8003FC64(0x212);
    if (temp_v0 != 0) {
        ((S_80024550_0 *)temp_v0)->unk_10 = D_800244A4;
        var_v0 = rand();
        temp_v1 = var_v0;
        temp_s2 = (u8 *)temp_v0 + 0x20;
        if (temp_v1 < 0) {
            var_v0 = temp_v1 + 0xFFF;
        }
        temp_s2->unk_08 = temp_v1 - ((var_v0 >> 12) << 12);
        temp_s0 = ((S_80024550_0 *)temp_v0)->unk_0C;
        temp_s0->unk_0E = 0x80;
        temp_s0->unk_0D = 0x80;
        temp_s0->unk_0C = 0x80;
        func_8003DB94(temp_s0, D_800DE870, 0);
        temp_s0->unk_1E = 0x1000;
        temp_s0->unk_1C = 0x1000;
        temp_s0->unk_10 |= 0x20;
        temp_s0->unk_14 |= 0xC;
        temp_s0->unk_1A =
            (s32)(0 - ((func_80064584(temp_s2->unk_08 -
                                      global_base[0x64]) >> 4) << 8)) >> 8;
        func_8004491C(temp_v0, D_80045340);
        temp_s0_2 = ((S_80024550_0 *)temp_v0)->unk_08;
        temp_s0_2->unk_02 = arg0->unk_02 +
            ((func_800644B8(temp_s2->unk_08) * 2) >> 8);
        temp_s0_2->unk_06 = arg0->unk_06 +
            ((func_80064584(temp_s2->unk_08) * 2) >> 8);
        temp_s0_2->unk_0A = arg0->unk_0A;
    }
}
