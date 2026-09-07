#include "common.h"

typedef struct S_8005A778_D80086A40 {
    s16 unk00;
    u8 pad02[2];
    void *unk04;
    s32 unk08;
    u8 pad0C[4];
    s32 unk10;
    s32 unk14;
    u8 unk18;
    u8 pad19[2];
    u8 unk1B;
} S_8005A778_D80086A40;

typedef struct S_8007382C {
    s32 unk00;
    u8 pad04[8];
} S_8007382C;

typedef struct S_8005A778_Arg0 {
    u8 pad00[0xC];
    s32 unk0C;
    u8 pad10[2];
    u16 unk12;
    u8 pad14[4];
    u8 unk18;
    u8 unk19;
} S_8005A778_Arg0;

extern S_8005A778_D80086A40 D_80086A40[16];
extern S_8007382C D_8007382C;

extern void func_8005A1D0(s32 arg0);
extern s32 func_80059F8C(void *arg0, s32 arg1);

s32 func_8005A778(S_8005A778_Arg0 *arg0, s32 arg1, void *arg2)
{
    s16 idx;
    s32 result;
    register s32 raw ASM_REG("$3");   /* MATCH pin: slus-diff */
    s32 base;
    S_8005A778_D80086A40 *entry;
    S_8005A778_Arg0 *reader;

    idx = 0;
    D_8007382C.unk00 = 0;
    raw = arg1;
    ASM_KEEP_NV(raw);   /* MATCH pin: slus-diff */
    reader = arg0;
    ASM_KEEP_NV(reader);   /* MATCH pin: slus-diff */
    arg1 <<= 16;
    arg1 >>= 16;

    if (arg1 == -1) {
        for (;;) {
            if (D_80086A40[idx].unk00 == -1) {
                goto found;
            }
            idx = idx + 1;
            if (idx >= 16) {
                return -1;
            }
        }
    } else {
        S_8005A778_D80086A40 *checkBase;
        S_8005A778_D80086A40 *check;

        idx = raw;
        if (idx >= 16) {
            return -1;
        }
        checkBase = D_80086A40;
        check = &checkBase[idx];
        if (check->unk00 != -1) {
            func_8005A1D0(check->unk10);
        }
    }

found:
    entry = &D_80086A40[idx];
    entry->unk00 = (s16)idx;
    entry->unk04 = arg0;
    base = reader->unk12;
    entry->unk10 = (s32)arg2;
    entry->unk08 = (base << 9) + 0xA20;
    entry->unk14 = reader->unk0C - *(volatile s32 *)&entry->unk08;
    entry->unk18 = reader->unk18;
    entry->unk1B = reader->unk19;

    result = (entry->unk10 = func_80059F8C(arg2, entry->unk14));
    if (result == -1) {
        return -1;
    }
    return idx;
}
