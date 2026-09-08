#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_func_8008ACDC_arg0.h"

M2C_UNK func_80048A44(); /* extern */
s16 func_800A0818();       /* extern */
extern s16 D_80083228;
extern M2C_UNK D_80083460;
extern u8 D_800DD030[];



typedef struct S_80091B5C_1 {
    u8 pad_00[0x14];
    s32 unk_14;
    u8 pad_18[0x12];
    s16 unk_2A;
} S_80091B5C_1;   /* arg3 in func_80091B5C */


typedef struct S_80091B5C_3 {
    u8 pad_00[0xA];
    u16 unk_0A;
    void * unk_0C;
} S_80091B5C_3;   /* base in func_80091B5C */

typedef struct S_80091B5C_4 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80091B5C_4;   /* temp_v0 in func_80091B5C */

typedef struct S_80091B5C_5_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80091B5C_5_pre;   /* the 0x14 bytes before ((S_80091B5C_3 *)base)->unk_0C in func_80091B5C, addressed as ((S_80091B5C_3 *)base)->unk_0C[-1] */

void func_80091B5C(void *arg0, void *arg1, void *arg2, void *arg3) {
    M2C_UNK sp18;
    void *base;
    void *temp_v0;

    if (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0x8000) {
        ((S_80091B5C_1 *)arg3)->unk_14 &= 0xFFFDFFFF;
        return;
    }
    base = &D_80083460;
    ((Rec_func_8008ACDC_arg0 *)arg0)->unk_9A.as_s8 = 0x2A;
    ((Rec_func_8008ACDC_arg0 *)arg0)->unk_9B.as_s8 = 0;
    (*(s32 *)((u8 *)arg0 + (0x8C))) = 0;
    ((S_80091B5C_3 *)base)->unk_0A = (u16) (((S_80091B5C_3 *)base)->unk_0A + 1);
    ((Rec_func_8008ACDC_arg0 *)arg0)->unk_96.as_s16 = 0x10;
    (*(u8 **)((u8 *)arg2 + (0x2C))) = D_800DD030;
    func_80048A44(arg2, D_800DD030[((s32) (D_80083228 + ((S_80091B5C_1 *)arg3)->unk_2A + 0x100) >> 9) & 7], 0, 1);
    temp_v0 = ((S_80091B5C_5_pre *)(((S_80091B5C_3 *)base)->unk_0C))[-1].unk_00;
    ((Rec_func_8008ACDC_arg0 *)arg0)->unk_11A = (u16) ((S_80091B5C_1 *)arg3)->unk_2A;
    ((S_80091B5C_1 *)arg3)->unk_2A = func_800A0818(((Rec_D_80082E80 *)arg2)->unk_24, ((Rec_D_80082E80 *)arg2)->unk_25, ((S_80091B5C_4 *)temp_v0)->unk_24, ((S_80091B5C_4 *)temp_v0)->unk_25, &sp18);
}

/* MECHANISM: The incoming object bases naturally hold s1/s2/s3, while a main-path-only
   D_80083460 pointer holds s0 without crossing the early sibcall. Assigning that base
   after the early return forces retail's adjacent lui/addiu and dead-argument schedule. */
