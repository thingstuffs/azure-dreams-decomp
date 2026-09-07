#include "common.h"

typedef struct S_8009A3A4_0 {
    u8 pad_00[0x44];
    void * unk_44;
} S_8009A3A4_0;   /* arg0 in func_8009A3A4 */

typedef struct S_8009A3A4_1 {
    u8 pad_00[0x40];
    s32 unk_40;
} S_8009A3A4_1;   /* call_arg0 in func_8009A3A4 */

typedef struct S_8009A3A4_2 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_8009A3A4_2;   /* ((S_8009A3A4_0 *)arg0)->unk_44 in func_8009A3A4 */



extern s32 func_80094984();
extern s32 func_80098928();
extern u8 D_80082660;

void func_8009A3A4(S_8009A3A4_0 *arg0, s32 arg1, s32 arg2) {
    register s32 arg1_save ASM_REG("$18") = arg1;   /* MATCH pin: load-bearing for the whole function shape */

    ASM_KEEP(arg1_save);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    func_80094984(((S_8009A3A4_2 *)(arg0->unk_44))->unk_14, arg0);
    {
        register void *call_arg0 ASM_REG("$4") = arg0;   /* MATCH pin: retail schedule: same instructions, different order without it */
        s32 call_arg1 = arg1_save;
        s32 call_arg2 = arg2;

        ASM_KEEP(call_arg1);   /* MATCH pin: retail schedule: same instructions, different order without it */
        ASM_KEEP(call_arg2);   /* MATCH pin: retail schedule: same instructions, different order without it */
        *(&D_80082660 + (((S_8009A3A4_1 *)call_arg0)->unk_40 * 8)) = 0;
        func_80098928(call_arg0, call_arg1, call_arg2);
    }
}

/* MECHANISM: The call-spanning arguments are held in retail's s0/s2/s1 roles,
   producing the 0x20 frame and save sequence. Guarded a0/a1/a2 staging precedes
   the byte-table address, whose clear fills the second call's delay slot. */
