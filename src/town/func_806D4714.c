#include "common.h"

typedef struct S_80016714_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x34];
    u8 * unk_40;
} S_80016714_0;   /* D_80016000 in func_80016714 */

typedef struct S_80016714_1 {
    u8 pad_00[0x4];
    u8 unk_04;
} S_80016714_1;   /* ((S_80016714_0 *)D_80016000)->unk_08 * 8 +
              ((S_80016714_0 *)D_80016000)->unk_40 in func_80016714 */

typedef struct S_80016714_2 {
    u8 pad_00[0x4];
    u8 unk_04;
} S_80016714_2;   /* ((S_80016714_0 *)D_80016000)->unk_08 * 8 +
                  ((S_80016714_0 *)D_80016000)->unk_40 in func_80016714 */



extern void *D_80016000;
extern u8 D_800189DC[16];
extern u8 D_80018B94[16];
extern u8 D_8001A3AE[];
extern u8 D_8001A495[];

extern s32 func_800178A8(void *, s32, s32);
extern void *func_80017960(void *, void *, s32, s32);
extern void func_80018594(s32);
extern s32 func_8001868C(s32);

void *func_80016714(s32 arg0, s32 arg1, s32 arg2)
{
    void *result;
    u8 *base;

    base = D_800189DC;
    result = func_80017960(base, D_80018B94, arg0, arg2);
    if (arg2 == 0xB) {
        func_80018594(0x1458);
        if (func_800178A8(base, arg0, 0xB) != 0) {
            return &D_8001A3AE[0];
        }
        ((S_80016714_1 *)(((S_80016714_0 *)D_80016000)->unk_08 * 8 +
              ((S_80016714_0 *)D_80016000)->unk_40))->unk_04++;
        if (((S_80016714_2 *)(((S_80016714_0 *)D_80016000)->unk_08 * 8 +
                  ((S_80016714_0 *)D_80016000)->unk_40))->unk_04 >= 5U) {
            func_80018594(0x1459);
        }
        return result;
    }
    if (arg2 == 0x1C) {
        if (func_8001868C(0x992) == 0) {
            func_80018594(0x992);
            return &D_8001A495[0];
        }
    }
    return result;
}
