#include "common.h"
typedef s32 M2C_UNK;


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define NULL 0

M2C_UNK func_8003DB94();
void *func_8003FC64();
M2C_UNK func_8004491C();
M2C_UNK func_800478B8();
s32 func_800BCB04();
void func_80174438(void) __attribute__((noreturn));
extern M2C_UNK D_80045340;
extern u16 D_8006CCD8[8];
extern u16 D_8006CCE8[8];
extern M2C_UNK D_800DEEC0;
extern M2C_UNK D_80174254;

typedef struct {
    s32 words[6];
} Copy24;

typedef struct S_80DE6AAC_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    s16 unk_20;
} S_80DE6AAC_0;   /* temp_v0 in func_80DE6AAC */

typedef struct S_80DE6AAC_1 {
    u8 pad_00[0x2];
    s16 unk_02;
} S_80DE6AAC_1;   /* temp_s1 in func_80DE6AAC */

typedef struct S_80DE6AAC_2 {
    u8 pad_00[0x2A];
    u16 unk_2A;
    u8 pad_2C[0x5C];
    u16 unk_88;
} S_80DE6AAC_2;   /* arg0 in func_80DE6AAC */

typedef struct S_80DE6AAC_3 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x3];
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_80DE6AAC_3;   /* temp_s0 in func_80DE6AAC */

typedef struct S_80DE6AAC_4 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80DE6AAC_4;   /* arg2 in func_80DE6AAC */

typedef struct S_80DE6AAC_5 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    s32 unk_08;
} S_80DE6AAC_5;   /* temp_s0_2 in func_80DE6AAC */

s32 func_80DE6AAC(S_80DE6AAC_2 *arg0, void *arg1, S_80DE6AAC_4 *arg2) {
    S_80DE6AAC_3 *temp_s0;
    S_80DE6AAC_5 *temp_s0_2;
    S_80DE6AAC_1 *temp_s1;
    void *temp_v0;

    temp_v0 = func_8003FC64(0x212);
    if (temp_v0 != NULL) {
        temp_s1 = temp_v0 + 0x20;
        ((S_80DE6AAC_0 *)temp_v0)->unk_10 = &D_80174254;
        ((S_80DE6AAC_0 *)temp_v0)->unk_20 = 0;
        temp_s1->unk_02 = (s16)(((u16)arg0->unk_2A >> 9) & 7);
        temp_s0 = ((S_80DE6AAC_0 *)temp_v0)->unk_0C;
        temp_s0->unk_0E = 0x80;
        temp_s0->unk_0D = 0x80;
        temp_s0->unk_0C = 0x80;
        temp_s0->unk_12 = 0x7E40;
        temp_s0->unk_14 = (u16)(temp_s0->unk_14 | 0x100);
        func_8003DB94(temp_s0, &D_800DEEC0, 0);
        func_800478B8(temp_s0);
        temp_s0->unk_1E = 0x800;
        temp_s0->unk_1C = 0x800;
        func_8004491C(temp_v0, &D_80045340);
        temp_s0_2 = ((S_80DE6AAC_0 *)temp_v0)->unk_08;
        *(Copy24 *)temp_s0_2 = *(Copy24 *)arg1;
        {
            s32 temp_a1;
            s32 temp_a2;
            s32 temp_v0_2;
            s32 temp_v1;

            temp_a2 = temp_s1->unk_02 * 2;
            temp_v1 = (s32)((arg2->unk_24 + *(u16 *)((u8 *)D_8006CCD8 + temp_a2)) << 0x10) >> 0xA;
            temp_a1 = (s32)((arg2->unk_25 + *(u16 *)((u8 *)D_8006CCE8 + temp_a2)) << 0x10) >> 0xA;
            temp_s0_2->unk_02 = (s16)(temp_v1 + 0x20);
            temp_s0_2->unk_06 = (s16)(temp_a1 + 0x20);
            temp_v0_2 = func_800BCB04(temp_v1 & 0xFFC0, temp_a1 & 0xFFC0, (s16)(arg0->unk_88 - 0x20)) << 0x10;
            if (temp_v0_2 < temp_s0_2->unk_08) {
                temp_s0_2->unk_08 = temp_v0_2;
            }
        }
        {
            register s32 dispatch_result ASM_REG("$2") = (s32)temp_v0;   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */

            ASM_TAILSLOT_PIN(dispatch_result);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
            func_80174438();
        }
        return (s32)temp_v0;
    }
    return 0;
}

/* MECHANISM: A typed 24-byte assignment restores the packed lw/sw copy and natural seven-register frame.
   An unsigned color byte plus a post-copy schedule seam fixes the immediate and held table-base order.
   The moved shape selects 2.7.2-cdk-G0; a scoped $v0 tail-slot pin closes the noreturn dispatch delay. */
