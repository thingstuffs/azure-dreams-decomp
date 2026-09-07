#include "common.h"
#include "m2c_compat.h"

typedef struct {
    s32 value;
} __attribute__((packed)) Packed4;

M2C_UNK func_80047784();         /* extern */
s32 func_800990FC();                                /* extern */
s32 func_80099194();                  /* extern */
M2C_UNK func_80099290();                         /* extern */
s32 func_8009929C();                    /* extern */
M2C_UNK func_80099368();                 /* extern */
s32 func_80099734();                     /* extern */
s32 func_800A2BDC();                          /* extern */
M2C_UNK func_800A5720();                         /* extern */
s32 func_800A6D30();                                /* extern */
void *func_80170908();                /* extern */
M2C_UNK func_8017437C();                   /* extern */
extern s16 D_80083228;
extern M2C_UNK D_80083460;
extern u16 D_80083462;
extern M2C_UNK D_8017089C;
extern M2C_UNK D_801708AC;
extern M2C_UNK D_801708B8;
extern M2C_UNK D_801708BC;
extern u8 D_80174F58[];

void func_80174234(void *arg0, void *arg1, void *arg2, void *arg3) {
    s32 temp_s2;
    s32 temp_v0;
    register s32 temp_field ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    void *temp_v0_2;
    register void *temp_a0 ASM_REG("$4");   /* MATCH pin: retail immediate-load split depends on it */
    u8 *end_base;

    M2C_FIELD(arg3, u8 *, 0x71) = (u8) (M2C_FIELD(arg3, u8 *, 0x71) & 0x7F);
    if (!(D_80083462 & 0x2000) && ((func_800A2BDC(arg3) << 0x10) == 0)) {
        if (M2C_FIELD(arg3, s32 *, 0x1C) & 0x400) {
            temp_field = M2C_FIELD(arg3, s32 *, 0x14);
            if (temp_field >= 0) {
                M2C_FIELD(arg3, s32 *, 0x14) = (s32) (temp_field | 0x80000000);
                M2C_FIELD(arg3, u16 *, 0x2A) = (u16) (M2C_FIELD(arg3, u16 *, 0x2A) + ((func_800A6D30() & 7) << 9));
            }
        }
        temp_s2 = func_800990FC();
        if (M2C_FIELD(arg3, u8 *, 0x49) == 0) {
            temp_v0_2 = func_80170908(arg2, arg3);
            if (temp_v0_2 != NULL) {
                M2C_FIELD(arg3, Packed4 *, 0x48) = *(Packed4 *) temp_v0_2;
                temp_v0 = func_80099368(temp_v0_2, func_80099194(&D_801708AC, func_8009929C(0xA, func_80099194(&D_8017089C, func_80099734(arg3, temp_s2)))));
                temp_a0 = &D_801708B8;
            } else {
                temp_v0 = func_80099734(arg3, temp_s2);
                temp_a0 = &D_801708BC;
            }
        } else {
            temp_v0 = func_80099734(arg3, temp_s2);
            temp_a0 = &D_801708BC;
        }
        func_80099290(func_80099194(temp_a0, temp_v0));
        func_800A5720(temp_s2);
        M2C_FIELD(arg0, s8 *, 0x9A) = 0x17;
        M2C_FIELD(arg0, s32 *, 0x8C) = 0;
        M2C_FIELD(arg0, s8 *, 0x9B) = 0;
        M2C_FIELD(arg2, u8 **, 0x2C) = D_80174F58;
        func_80047784(arg2, D_80174F58[((D_80083228 + (s16) M2C_FIELD(arg3, u16 *, 0x2A) + 0x100) >> 9) & 7], 0);
        end_base = (u8 *) &D_80083460;
        M2C_FIELD(arg3, u8 *, 0x6D) = (u8) (M2C_FIELD(arg3, u8 *, 0x6D) - 1);
        M2C_FIELD(end_base, u16 *, 0xA) = (u16) (M2C_FIELD(end_base, u16 *, 0xA) + 1);
    }
}

/* MECHANISM: The four-argument ABI and true-space merge preserve retail's s1/a3, s4/a2, s3/a0, s2/s0 roles.
   A packed four-byte assignment restores lwl/lwr/swl/swr; guarded v0-field and a0-merge pins close local roles.
   Byte-table indexing plus a held D_80083460 base fixes the tail and its one-word displacement cascade.
   The final packed-copy scratch is v0 only at 2.7.2-cdk-G0; 2.8.1-G0 leaves the four-word t0 residue. */
