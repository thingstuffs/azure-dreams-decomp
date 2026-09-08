#include "common.h"
#include "records/Rec_D_80175D50.h"

#ifndef NULL
#define NULL 0
#endif


typedef struct S_80170700_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    s32 * unk_10;
    u8 pad_14[0x24];
    s16 unk_38;
} S_80170700_1;   /* temp_v0 in func_80170700 */

typedef struct S_80170700_2 {
    u8 pad_00[0x6];
    s16 unk_06;
    u8 pad_08[0x4];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x5];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0xC];
    u8 * unk_2C;
} S_80170700_2;   /* temp_s0_2 in func_80170700 */

typedef struct S_80170700_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80170700_3;   /* temp_a0 in func_80170700 */



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
    S_80170700_3 *temp_a0;
    void *temp_s0;
    S_80170700_2 *temp_s0_2;
    S_80170700_1 *temp_v0;
    void *var_a2;
    void *var_a3;
    register void *call_obj ASM_REG("$4");   /* MATCH pin: retail schedule: same instructions, different order without it */

    temp_s0 = ((Rec_D_80175D50 *)D_80175D50)->unk_0C;
    temp_v0 = func_8003FC64(0x112);
    var_a3 = temp_s0;
    if (temp_v0 != NULL) {
        temp_t0 = (s32)var_a3 + 0x30;
        temp_s0_2 = temp_v0->unk_0C;
        temp_v0->unk_38 = 0;
        temp_v0->unk_10 = &D_80170534;
        var_a2 = temp_s0_2;
        do {
            *(Copy16 *)var_a2 = *(Copy16 *)var_a3;
            var_a3 = (u8 *)var_a3 + 0x10;
            var_a2 = (u8 *)var_a2 + 0x10;
        } while (var_a3 != (void *)temp_t0);
        temp_s0_2->unk_14 =
            (temp_s0_2->unk_14 & 0xFF7F) | 0x400;
        func_8004491C(temp_v0, &D_80045340, var_a2, var_a3);
        call_obj = temp_s0_2;
        var_a1 = *(&D_80170000[0x3A80]);
        ASM_KEEP(var_a1);   /* MATCH pin: retail schedule: same instructions, different order without it */
        temp_s0_2->unk_2C = &D_80170000[0x3A80];
        func_80047784(call_obj, var_a1, 0);
        temp_s0_2->unk_06 = 6;
        temp_s0_2->unk_14 &= 0xFFF3;
        temp_a0 = temp_v0->unk_08;
        temp_a0->unk_02 = D_80083780.x2;
        temp_a0->unk_06 = D_80083780.x6 - 0x400;
        temp_a0->unk_0A = D_80083780.xA;
        temp_s0_2->unk_1E = 0x1000;
        temp_s0_2->unk_1C = 0x1000;
        temp_s0_2->unk_0E = 0x80;
        temp_s0_2->unk_0D = 0x80;
        temp_s0_2->unk_0C = 0x80;
        D_80175D64 = temp_v0;
    }
}

/* MECHANISM: Preserve the seed's 0x20 frame and long-lived s0/s1 roles.
   A widened byte local plus call_obj pinned in a0 fixes the pre-call order.
   ASM_KEEP(var_a1) delays a2=0 while the following store fills the jal slot. */
