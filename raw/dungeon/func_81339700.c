#include "common.h"

#ifndef NULL
#define NULL 0
#endif

#define FIELD(expr, type, offset) (*(type *)((u8 *)(expr) + (offset)))

extern void *func_8003FC64();
extern s32 func_8004491C();
extern s32 func_80047784();
extern s32 D_80045340;
typedef struct {
    u16 x0;
    u16 x2;
    u16 x4;
    u16 x6;
    u16 x8;
    u16 xA;
} D_80083780_S;
typedef struct {
    s32 x0;
    s32 x4;
    s32 x8;
    s32 xC;
} Copy16;
extern D_80083780_S D_80083780;
extern s32 D_80170534;
extern u8 D_80170000[0x3A81];
extern void *D_80175D50;
extern void *D_80175D64;

void func_80170700(void) {
    s32 temp_t0;
    s32 var_a1;
    void *temp_a0;
    void *temp_s0;
    void *temp_s0_2;
    void *temp_v0;
    void *var_a2;
    void *var_a3;
    register void *call_obj ASM_REG("$4");

    temp_s0 = FIELD(D_80175D50, void *, 0xC);
    temp_v0 = func_8003FC64(0x112);
    var_a3 = temp_s0;
    if (temp_v0 != NULL) {
        temp_t0 = (s32)var_a3 + 0x30;
        temp_s0_2 = FIELD(temp_v0, void *, 0xC);
        FIELD(temp_v0, s16, 0x38) = 0;
        FIELD(temp_v0, s32 *, 0x10) = &D_80170534;
        var_a2 = temp_s0_2;
        do {
            *(Copy16 *)var_a2 = *(Copy16 *)var_a3;
            var_a3 = (u8 *)var_a3 + 0x10;
            var_a2 = (u8 *)var_a2 + 0x10;
        } while (var_a3 != (void *)temp_t0);
        FIELD(temp_s0_2, u16, 0x14) =
            (FIELD(temp_s0_2, u16, 0x14) & 0xFF7F) | 0x400;
        func_8004491C(temp_v0, &D_80045340, var_a2, var_a3);
        call_obj = temp_s0_2;
        var_a1 = *(&D_80170000[0x3A80]);
        ASM_KEEP(var_a1);
        FIELD(temp_s0_2, u8 *, 0x2C) = &D_80170000[0x3A80];
        func_80047784(call_obj, var_a1, 0);
        FIELD(temp_s0_2, s16, 6) = 6;
        FIELD(temp_s0_2, u16, 0x14) &= 0xFFF3;
        temp_a0 = FIELD(temp_v0, void *, 8);
        FIELD(temp_a0, u16, 2) = D_80083780.x2;
        FIELD(temp_a0, s16, 6) = D_80083780.x6 - 0x400;
        FIELD(temp_a0, u16, 0xA) = D_80083780.xA;
        FIELD(temp_s0_2, s16, 0x1E) = 0x1000;
        FIELD(temp_s0_2, s16, 0x1C) = 0x1000;
        FIELD(temp_s0_2, u8, 0xE) = 0x80;
        FIELD(temp_s0_2, u8, 0xD) = 0x80;
        FIELD(temp_s0_2, u8, 0xC) = 0x80;
        D_80175D64 = temp_v0;
    }
}

/* MECHANISM: Preserve the seed's 0x20 frame and long-lived s0/s1 roles.
   A widened byte local plus call_obj pinned in a0 fixes the pre-call order.
   ASM_KEEP(var_a1) delays a2=0 while the following store fills the jal slot. */
