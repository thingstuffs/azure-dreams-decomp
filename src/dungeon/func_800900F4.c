#include "common.h"
#include "m2c_compat.h"

typedef struct S_80095854_0 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x46];
    s8 unk_72;
    s8 unk_73;
    u8 pad_74[0x18];
    s32 unk_8C;
    u8 pad_90[0xA];
    s8 unk_9A;
    s8 unk_9B;
    u8 pad_9C[0x88];
    void * unk_124;
} S_80095854_0;   /* arg0 in func_80095854 */

typedef struct S_80095854_1 {
    u8 pad_00[0x13];
    s8 unk_13;
} S_80095854_1;   /* temp_v1 in func_80095854 */

typedef struct S_80095854_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80095854_2;   /* arg2 in func_80095854 */


M2C_UNK func_80048A44(); /* extern */
M2C_UNK func_80094E34();                            /* extern */
M2C_UNK func_8009A21C();           /* extern */
M2C_UNK func_8009A3D0();           /* extern */
s32 func_8009B88C();   /* extern */
extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s32 D_80082EB0;
extern s16 D_80083228;
extern u8 D_800DD130;

s32 func_80095854(void *arg0_in, s32 arg1, void *arg2_in, s32 arg3_in) {
    s16 sp18;
    s16 sp1A;
    s16 sp1C;
    s16 sp1E;
    void *arg0 = arg0_in;
    void *arg2 = arg2_in;
    s32 arg3 = arg3_in;
    register s32 var_s1 ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    register s32 temp_cmp ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    s32 temp_a2;
    s32 temp_shift;
    register s32 temp_s1 ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    s8 temp_v0;
    void *temp_v1;

    var_s1 = 0;
    ASM_KEEP(arg2);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    ASM_KEEP(arg3);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    temp_v1 = ((S_80095854_0 *)arg0)->unk_124;
    ((S_80095854_0 *)arg0)->unk_9A = 0x31;
    ((S_80095854_0 *)arg0)->unk_9B = 0;
    ((S_80095854_0 *)arg0)->unk_8C = 0;
    if (temp_v1 != NULL) {
        temp_cmp = ((S_80095854_1 *)temp_v1)->unk_13;
        temp_cmp = temp_cmp > 0;
        ASM_KEEP(temp_cmp);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        var_s1 = temp_cmp;
    }
    func_80094E34();
    (*(M2C_UNK **)((u8 *)arg2 + 0x2C)) = &D_800DD130;
    func_80048A44(arg2, *((((s32) (D_80083228 + ((S_80095854_0 *)arg0)->unk_2A + 0x100) >> 9) & 7) + &D_800DD130), 0, 1);
    D_80082EB0 = arg3;
    temp_a2 = ((u16) (*(s16 *)((u8 *)arg0 + 0x2A)) >> 8) & 0xE;
    ((S_80095854_0 *)arg0)->unk_72 = (s8) (((S_80095854_2 *)arg2)->unk_24 + *(temp_a2 + &D_8006CCD8));
    temp_v0 = ((S_80095854_2 *)arg2)->unk_25 + *(temp_a2 + &D_8006CCE8);
    ((S_80095854_0 *)arg0)->unk_73 = temp_v0;
    if ((func_8009B88C(0, ((S_80095854_0 *)arg0)->unk_72, temp_v0, &sp18, &sp1A) << 0x10) != 0) {
        temp_cmp = var_s1 << 0x10;
        if (temp_cmp != 0) {
            func_8009A21C(sp18, sp1A, 0x8000);
            temp_s1 = func_8009B88C(0, ((S_80095854_0 *)arg0)->unk_72, ((S_80095854_0 *)arg0)->unk_73, &sp1C, &sp1E);
            func_8009A3D0(sp18, sp1A, 0x8000);
            temp_shift = temp_s1 << 0x10;
            ASM_CLOBBER("$17");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            if (temp_shift != 0) {
                ((S_80095854_0 *)arg0)->unk_72 = (s8) (u8) sp1C;
                ((S_80095854_0 *)arg0)->unk_73 = (s8) (u8) sp1E;
                return 1;
            }
            return 0;
        }
        ((S_80095854_0 *)arg0)->unk_72 = (s8) (u8) sp18;
        ((S_80095854_0 *)arg0)->unk_73 = (s8) (u8) sp1A;
        return 1;
    }
    return 0;
}
/* MECHANISM: Restored the dead ABI arg and pinned held roles for the exact s0/s2/s3/s1 prologue.
   Byte-typed globals removed fourfold index scaling; natural local-return CFG restored the tail.
   A split-scope s1 result plus post-shift s1 clobber preserved the v0 test and zero delay slot. */
