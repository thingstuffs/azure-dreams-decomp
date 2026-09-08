#include "common.h"
#include "m2c_compat.h"

typedef struct S_800B65D8_4 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800B65D8_4;   /* temp_s1 in func_800B65D8 */

typedef struct S_800B65D8_5 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_800B65D8_5;   /* ((S_800B65D8_4 *)temp_s1)->unk_04 in func_800B65D8 */




s32 func_80048DA0();                         /* extern */
s32 func_80048DCC();                             /* extern */
s32 func_80048DE8();                             /* extern */
M2C_UNK func_800B6580();                    /* extern */
M2C_UNK func_800B6688();                            /* extern */
extern u8 D_80089344[];

typedef struct S_800B65D8_0 {
    u8 pad_00[0x50];
    void * unk_50;
} S_800B65D8_0;   /* var_s4 in func_800B65D8 */

typedef struct S_800B65D8_1 {
    s32 unk_00;
    void * unk_04;
} S_800B65D8_1;   /* temp_s1 in func_800B65D8 */

typedef struct S_800B65D8_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_800B65D8_2;   /* temp_ptr in func_800B65D8 */

typedef struct S_800B65D8_3 {
    u8 pad_00[0x5C];
    s32 * unk_5C;
} S_800B65D8_3;   /* base in func_800B65D8 */

void func_800B65D8(void *arg0, s32 arg1) {
    S_800B65D8_3 *base;
    s32 mode;
    s32 var_s3;
    s32 var_s2;
    u8 *lookup;
    void *var_s4;
    s32 temp_v0_2;
    register s32 temp_v0 ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 var_a1;
    s32 var_s0;
    S_800B65D8_1 *temp_s1;
    S_800B65D8_2 *temp_ptr;

    base = arg0;
    mode = arg1;
    var_s2 = (var_s3 = 0);
    lookup = D_80089344;
    var_s4 = base;
    ASM_KEEP(lookup);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    ASM_KEEP(base);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP(mode);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    do {
        temp_s1 = ((S_800B65D8_0 *)var_s4)->unk_50;
        var_s0 = func_80048DA0(mode, *(u8 *)((s32)var_s2 + (s32)lookup));
        if ((var_s2 == 0) && (mode == 4)) {
            var_s0 -= 1;
        }
        temp_s1->unk_00 = func_80048DCC(var_s0);
        temp_v0 = func_80048DE8(var_s0);
        if (temp_v0 == 0x10) {
            ((S_800B65D8_5 *)(((S_800B65D8_4 *)temp_s1)->unk_04))->unk_0A = 0;
            func_800B6688();
            return;
        }
        temp_v0_2 = var_s3 - (var_s2 * 8);
        temp_ptr = temp_s1->unk_04;
        ASM_KEEP(temp_ptr);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        var_s3 += temp_v0;
        temp_ptr->unk_0A = temp_v0_2;
        ASM_KEEP(temp_ptr);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        var_s2 += 1;
        var_s4 += 4;
    } while (var_s2 < 2);
    var_a1 = 0;
    if (var_s3 != 0) {
        var_a1 = var_s3 - 0x14;
    }
    func_800B6580(*base->unk_5C, var_a1);
}
