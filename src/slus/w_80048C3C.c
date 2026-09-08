#include "common.h"
#include "m2c_compat.h"

/* close_gap PERM base: REGALLOC_SWAP reg_map={'v0': 's1'}. Feed to permute.sh; wrap the diagnosed temps in PERM_VAR(...) or permute decl order. */
/* first_pass warm draft: compiles, best score 23 @ 2.7.2-cdk */
#include "common.h"

typedef struct S_80048C3C_0 {
    s32 unk_00;
    void * unk_04;
} S_80048C3C_0;   /* temp_s1 in func_80048C3C */

typedef struct S_80048C3C_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    s32 unk_20;
} S_80048C3C_1;   /* temp_s2 in func_80048C3C */

#ifndef NON_MATCHING
#undef ASM_KEEP
#define ASM_KEEP(v) __asm__("" : "=r"(v) : "0"(v))
#endif

M2C_UNK DrawSync();                          /* extern */
M2C_UNK func_8003E4FC();       /* extern */
M2C_UNK func_8003F320();                            /* extern */
M2C_UNK func_8003F80C(); /* extern */
M2C_UNK func_80046F88();                      /* extern */
M2C_UNK func_80047200();    /* extern */
M2C_UNK func_80048B8C();                      /* extern */
extern u8 D_80071210[];
extern s8 D_80080A89[9];

void *func_80048C3C(s32 arg0) {
    void *temp_s0;
    register void *temp_s1 ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    void *temp_s2;
    s32 six;
    s32 one;
    register void *call0 ASM_REG("$4");   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */

    temp_s1 = (void *)(arg0 * 8);
    six = 6;
    ASM_KEEP(six);   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
    temp_s1 = (u8 *)temp_s1 + (u32)D_80071210;
    func_8003E4FC(six, ((S_80048C3C_0 *)temp_s1)->unk_00, 0);
    func_8003F320();
    temp_s2 = ((S_80048C3C_0 *)temp_s1)->unk_04;
    temp_s0 = temp_s2 + ((S_80048C3C_1 *)temp_s2)->unk_1C;
    func_8003F80C(temp_s0, 0x7A00, ((S_80048C3C_1 *)temp_s2)->unk_20, 2);
    DrawSync(0);
    call0 = temp_s0;
    one = 1;
    ASM_KEEP(one);   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
    func_80047200(call0, one, one);
    func_8003F80C(temp_s0, 0x7980, ((S_80048C3C_1 *)temp_s2)->unk_20, 2);
    func_80046F88(temp_s2);
    func_80048B8C(temp_s2);
    temp_s1 = (u8 *)temp_s1 + 4;
    ASM_KEEP(temp_s1);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    D_80080A89[0] = 0;
    return temp_s1;
}
