#include "common.h"
#include "m2c_compat.h"

void *func_8003FC64();
M2C_UNK func_8004491C();
s32 func_800644B8();
s32 func_80064584();
extern M2C_UNK D_80024888;
extern u8 D_80020000[];
extern M2C_UNK D_800269EC;
extern M2C_UNK D_80045340;

typedef struct S_80024938_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_80024938_0;   /* temp_v0 in func_80024938 */

typedef struct S_80024938_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80024938_1;   /* temp_s2 in func_80024938 */

typedef struct S_80024938_2 {
    u8 pad_00[0x8];
    M2C_UNK * unk_08;
    s32 unk_0C;
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_80024938_2;   /* temp_a0 in func_80024938 */

typedef struct S_80024938_3 {
    u8 pad_00[0x30];
    s16 unk_30;
    u8 pad_32[0x4];
    u16 unk_36;
} S_80024938_3;   /* temp_v1 in func_80024938 */

void *func_80024938(s16 arg0, s16 arg1, s16 arg2, s16 arg3) {
    s32 temp_s0;
    s32 temp_s0_2;
    s32 temp_s1;
    s32 temp_s5;
    register s32 temp_v1_color ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */
    s32 var_s4;
    S_80024938_2 *temp_a0;
    S_80024938_1 *temp_s2;
    void *temp_v0;
    S_80024938_3 *temp_v1;
    u8 *page_base;

    var_s4 = 0;
    temp_s5 = arg3 + 0x400;
    do {
        temp_v0 = func_8003FC64(0x202);
        if (temp_v0 != NULL) {
            ((S_80024938_0 *)temp_v0)->unk_10 = &D_80024888;
            func_8004491C(temp_v0, &D_80045340);
            temp_s2 = ((S_80024938_0 *)temp_v0)->unk_08;
            temp_s2->unk_02 = arg0;
            temp_s2->unk_06 = arg1;
            temp_s2->unk_0A = arg2;
            temp_s1 = var_s4 << 7;
            temp_s0 = func_80064584(temp_s5);
            temp_s2->unk_0C = (s32) ((s32) (temp_s0 * func_80064584(temp_s1)) >> 6);
            temp_s0_2 = func_800644B8(temp_s5);
            temp_s2->unk_10 = (s32) ((s32) (temp_s0_2 * func_80064584(temp_s1)) >> 6);
            temp_s2->unk_14 = (s32) (func_800644B8(temp_s1) << 6);
            temp_v1_color = 0x808080;
            temp_a0 = ((S_80024938_0 *)temp_v0)->unk_0C;
            temp_a0->unk_1E = 0x400;
            temp_a0->unk_1C = 0x400;
            page_base = (u8 *) 0x80020000;
            ASM_KEEP(page_base);   /* MATCH pin: keeps a statement from moving across a call/branch */
            temp_a0->unk_0C = temp_v1_color;
            temp_v1_color = temp_a0->unk_14;
            temp_a0->unk_08 = page_base + 0x69EC;
            temp_a0->unk_10 = 0x20;
            temp_a0->unk_14 = (u16) (temp_v1_color | 0xC);
            temp_v1 = temp_v0 + 0x20;
            temp_v1->unk_30 = 0xC;
            temp_v1->unk_36 = (u16) arg3;
        }
        var_s4 += 1;
    } while (var_s4 < 0x20);
    return temp_v0;
}
