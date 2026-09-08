#include "common.h"
#include "m2c_compat.h"

typedef struct S_800F643C_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_800F643C_0;   /* temp_v0 in func_800F643C */

typedef struct S_800F643C_1 {
    u8 pad_00[0x6];
    s16 unk_06;
    s32 unk_08;
    s32 unk_0C;
    u8 pad_10[0xA];
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} S_800F643C_1;   /* temp_s1 in func_800F643C */

typedef struct S_800F643C_2 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800F643C_2;   /* temp_s0 in func_800F643C */

typedef struct S_800F643C_3 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x4];
    s16 unk_08;
    u8 pad_0A[0x4];
    s16 unk_0E;
    s16 unk_10;
} S_800F643C_3;   /* temp_a0 in func_800F643C */


void *func_8003FC64();                       /* extern */
M2C_UNK func_8004491C();           /* extern */
s32 func_800BCB04();               /* extern */
extern M2C_UNK D_80046398;
extern s32 D_80083208;
extern M2C_UNK D_800F6160;
extern s16 *D_800F8A44[];

void func_800F643C(s16 arg0, s16 arg1, s32 arg2) {
    s16 temp_v0_2;
    s32 temp_v1;
    void *temp_a0;
    void *temp_s0;
    void *temp_s1;
    void *temp_v0;

    temp_v0 = func_8003FC64(0x16);
    if (temp_v0 != NULL) {
        ((S_800F643C_0 *)temp_v0)->unk_10 = &D_800F6160;
        func_8004491C(temp_v0, &D_80046398);
        temp_v1 = D_80083208;
        temp_s1 = ((S_800F643C_0 *)temp_v0)->unk_0C;
        (*(s16 *)((u8 *)temp_s1 + 0x20)) = 0x1000;
        ((S_800F643C_1 *)temp_s1)->unk_1E = 0x1000;
        ((S_800F643C_1 *)temp_s1)->unk_1C = 0x1000;
        ((S_800F643C_1 *)temp_s1)->unk_06 = 4;
        ((S_800F643C_1 *)temp_s1)->unk_0C = temp_v1;
        ((S_800F643C_1 *)temp_s1)->unk_08 = 0x70;
        temp_s0 = ((S_800F643C_0 *)temp_v0)->unk_08;
        ((S_800F643C_2 *)temp_s0)->unk_02 = arg0;
        ((S_800F643C_2 *)temp_s0)->unk_06 = arg1;
        temp_v0_2 = func_800BCB04(arg0 & 0xFFFF, arg1 & 0xFFFF, -0x400) - 0xC0;
        temp_a0 = temp_v0 + 0x20;
        ((S_800F643C_2 *)temp_s0)->unk_0A = temp_v0_2;
        ((S_800F643C_3 *)temp_a0)->unk_0E = temp_v0_2;
        ((S_800F643C_3 *)temp_a0)->unk_08 = arg2;
        if (arg2 != 0) {
            ((S_800F643C_3 *)temp_a0)->unk_02 = 0x800;
            ((S_800F643C_1 *)temp_s1)->unk_1A = 0x800;
        }
        D_800F8A44[arg2] = temp_a0;
        ((S_800F643C_3 *)temp_a0)->unk_10 = arg2;
        ASM_USE(arg2);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    }
}

/* MECHANISM: The 0x30/no-local frame follows from six natural held values; s32 arg2 plus
   symbolic D_800F8A44[index] removes the sign-extension and scale-by-16 length cascade.
   ASM_USE(arg2) restores retail s3/s4/s5 argument coloring, and the named one-read
   D_80083208 value hoists its lui/lw and preserves the v1 store schedule. */
