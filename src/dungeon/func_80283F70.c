#include "common.h"
#include "m2c_compat.h"

typedef struct S_80016F70_0 {
    s8 unk_00;
    s8 unk_01;
    s8 unk_02;
} S_80016F70_0;   /* var_v1 in func_80016F70; pointer addresses record offset 0x2 */

typedef struct S_80016F70_1 {
    s8 unk_00;
    s8 unk_01;
    s8 unk_02;
} S_80016F70_1;   /* var_v1_2 in func_80016F70; pointer addresses record offset 0x2 */

typedef struct S_80016F70_2 {
    s8 unk_00;
    s8 unk_01;
    s8 unk_02;
    s8 unk_03;
    s32 unk_04;
} S_80016F70_2;   /* var_a0 in func_80016F70 */


extern s8 D_800E3DB0;

void func_80016F70(void) {
    register u32 page ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    s16 temp_v0;
    s16 temp_v0_2;
    register s16 var_a2 ASM_REG("$6");   /* MATCH pin: retail register colouring depends on it */
    s16 var_a2_2;
    s8 *var_a0;
    s8 *var_v1;
    s8 *var_v1_2;
    s8 var_a1;
    s8 var_a3;

    page = 0x800E0000;
    ASM_KEEP(page);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    var_a0 = (s8 *)(page + 0x3DB0);
    ASM_CLOBBER("$2");   /* MATCH pin: load-bearing for the whole function shape */
    var_a2 = 0;
    var_a1 = var_a2;
    var_a3 = 1;
    var_v1 = var_a0 + 3;
    do {
        temp_v0 = var_a2 + 1;
        var_a2 = temp_v0;
        *var_a0 = var_a3;
        ((S_80016F70_0 *)((u8 *)var_v1 - 0x2))->unk_02 = var_a1;
        var_a1 += 1;
        ((S_80016F70_0 *)((u8 *)var_v1 - 0x2))->unk_00 = 0;
        ((S_80016F70_0 *)((u8 *)var_v1 - 0x2))->unk_01 = 0;
        var_v1 += 8;
        var_a0 += 8;
    } while (temp_v0 < 4);
    var_a2_2 = 0;
    var_a3 = 3;
    var_v1_2 = var_a0 + 3;
    do {
        temp_v0_2 = var_a2_2 + 1;
        var_a2_2 = temp_v0_2;
        *var_a0 = var_a3;
        ((S_80016F70_1 *)((u8 *)var_v1_2 - 0x2))->unk_02 = var_a1;
        var_a1 += 1;
        ((S_80016F70_1 *)((u8 *)var_v1_2 - 0x2))->unk_00 = 0;
        ((S_80016F70_1 *)((u8 *)var_v1_2 - 0x2))->unk_01 = 0;
        var_v1_2 += 8;
        var_a0 += 8;
    } while (temp_v0_2 < 2);
    ((S_80016F70_2 *)var_a0)->unk_00 = 2;
    ((S_80016F70_2 *)var_a0)->unk_01 = 0;
    ((S_80016F70_2 *)var_a0)->unk_02 = 0;
    ((S_80016F70_2 *)var_a0)->unk_03 = var_a1;
    ((S_80016F70_2 *)var_a0)->unk_04 = 0;
}
/* MECHANISM: Frameless leaf; a pinned 0x800E0000 page in v0 forms the advancing a0 base.
   Clobbering v0 after base formation prevents the +3 pointer from folding through the page.
   Named a3 loop constants place each li before the derived v1 pointer.
   An a2 counter pin plus seam keep preserves retail's move a1,a2. */
