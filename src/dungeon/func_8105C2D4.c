#include "common.h"
#include "m2c_compat.h"

typedef struct S_80173AD4_0 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0x6];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x41];
    u8 unk_6D;
    u8 pad_6E[0x3];
    u8 unk_71;
} S_80173AD4_0;   /* var_s1 in func_80173AD4 */

typedef struct S_80173AD4_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x6];
    u16 unk_0A;
} S_80173AD4_1;   /* var_s3 in func_80173AD4 */

typedef struct S_80173AD4_2 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x6];
    s16 unk_96;
    u16 unk_98;
    s8 unk_9A;
    s8 unk_9B;
    u8 pad_9C[0xA];
    u16 unk_A6;
    u8 pad_A8[0x2];
    s16 unk_AA;
} S_80173AD4_2;   /* var_s0 in func_80173AD4 */

typedef struct S_80173AD4_3 {
    u8 pad_00[0x12];
    u16 unk_12;
    u8 pad_14[0x10];
    u8 unk_24;
    u8 unk_25;
} S_80173AD4_3;   /* var_s2 in func_80173AD4 */


M2C_UNK func_80047784();         /* extern */
s32 func_800990FC();                                /* extern */
s32 func_80099194();                  /* extern */
M2C_UNK func_80099290();                         /* extern */
s32 func_80099734();                     /* extern */
M2C_UNK func_8009A21C();             /* extern */
M2C_UNK func_8009A3D0();             /* extern */
s32 func_800A2BDC();                          /* extern */
M2C_UNK func_800A5720();                         /* extern */
extern s16 D_80083228;
extern M2C_UNK D_80083460;
extern u8 D_80170854[];
extern u8 D_80173FD0[];

void func_80173AD4(void *arg0, void *arg1, void *arg2, void *arg3) {
    M2C_UNK var_a2;
    s32 temp_v0;
    s32 temp_ret;
    register void *temp_a0 ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    register s32 temp_a1 ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    u8 temp_byte;
    u8 call_a0;
    u8 call_a1;
    s32 call_flags;
    void *var_s1 = arg3;
    void *var_s0;
    void *var_s2;   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    u8 *var_s3;

    temp_byte = ((S_80173AD4_0 *)var_s1)->unk_71;
    var_s0 = arg0;
    ((S_80173AD4_0 *)var_s1)->unk_71 = temp_byte & 0x7F;
    var_s3 = (u8 *)&D_80083460;
    var_s2 = arg2;
    if (!(((S_80173AD4_1 *)var_s3)->unk_02 & 0x2000) && ((func_800A2BDC(var_s1) << 0x10) == 0)) {
        ((S_80173AD4_2 *)var_s0)->unk_8C = 0;
        ((S_80173AD4_2 *)var_s0)->unk_9A = 0x17;
        ((S_80173AD4_2 *)var_s0)->unk_9B = 0;
        ((S_80173AD4_2 *)var_s0)->unk_96 = 0;
        if (!(((S_80173AD4_2 *)var_s0)->unk_98 & 0x8000)) {
            ((S_80173AD4_2 *)var_s0)->unk_A6 = (u16) ((S_80173AD4_3 *)var_s2)->unk_12;
            ((S_80173AD4_2 *)var_s0)->unk_AA = (s16) (((S_80173AD4_0 *)var_s1)->unk_14 & 7);
        }
        ((S_80173AD4_1 *)var_s3)->unk_0A = (u16) (((S_80173AD4_1 *)var_s3)->unk_0A + 1);
        ((S_80173AD4_0 *)var_s1)->unk_6D = (u8) (((S_80173AD4_0 *)var_s1)->unk_6D - 1);
        call_flags = ((S_80173AD4_0 *)var_s1)->unk_1C & 0x2000;
        call_a0 = ((S_80173AD4_3 *)var_s2)->unk_24;
        call_a1 = ((S_80173AD4_3 *)var_s2)->unk_25;
        var_a2 = 0x3000;
        if (call_flags) {
            var_a2 = 0x300;
        }
        func_8009A3D0(call_a0, call_a1, var_a2);
        ((S_80173AD4_0 *)var_s1)->unk_1C = (s32) (((S_80173AD4_0 *)var_s1)->unk_1C & ~0x2000);
        func_8009A21C(((S_80173AD4_3 *)var_s2)->unk_24, ((S_80173AD4_3 *)var_s2)->unk_25, 0x3000);
        (*(u8 **)((u8 *)var_s2 + 0x2C)) = D_80173FD0;
        func_80047784(var_s2, D_80173FD0[((D_80083228 + ((S_80173AD4_0 *)var_s1)->unk_2A + 0x100) >> 9) & 7], 0);
        temp_ret = func_800990FC();
        temp_a0 = var_s1;
        temp_a1 = temp_ret;
        ASM_KEEP(temp_a1);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        temp_v0 = temp_a1;
        func_80099290(func_80099194(&D_80170854, func_80099734(temp_a0, temp_a1)));
        ASM_KEEP(var_s1);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        func_800A5720(temp_v0);
    }
}

/* MECHANISM: The true-space four-argument ABI pins a3/s1, a0/s0, and a2/s2;
   a named scheduling seam holds D_80083460 in s3 and orders the flag/call loads.
   Splitting the final return into v0, then fenced a0/a1 live ranges, yields
   move a0,s1; move a1,v0; jal; move s0,a1 exactly. */
