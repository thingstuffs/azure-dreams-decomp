#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
M2C_UNK func_80067014();
M2C_UNK func_800671A8();
s32 func_80123200();
void func_80123928();
void func_801239B8();
extern M2C_UNK D_8011ACD8;
extern M2C_UNK D_80126E98;

typedef struct S_80123A60_0 {
    u8 pad_00[0xF];
    u8 unk_0F;
} S_80123A60_0;   /* arg0 in func_80123A60 */

void func_80123A60(S_80123A60_0 *arg0) {
    s16 stack_values[4];
    s32 *var_s2;
    register s32 *temp_base ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 var_s0;
    register s32 var_s1 ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    u8 temp_v0;
    u8 temp_v1;

    stack_values[0] = 0x180;
    stack_values[1] = 0x80;
    stack_values[2] = 0x36;
    stack_values[3] = 0x60;
    func_800671A8(stack_values, 0, 0, 0);
    func_801239B8(&D_8011ACD8, 0x192, 0xD0);
    func_80067014(0);
    var_s1 = 0;
    if (arg0->unk_0F == 3) {
        var_s1 = arg0->unk_0F;
        var_s0 = var_s1 * 0x10;
        if (func_80123200(var_s0 & 0xF0) & 0xFF) {
            temp_base = &D_80126E98;
            func_80123928(*(((var_s1 * 0x20) + var_s0) + temp_base), 0x180, 0x80);
        }
        var_s0 += 1;
        if (func_80123200(var_s0 & 0xFF) & 0xFF) {
            temp_base = &D_80126E98;
            func_80123928(*((var_s0 * 3) + temp_base), 0x1A4, 0xA0);
        }
        func_80067014(0);
        return;
    }
    ASM_MEM_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    temp_v0 = arg0->unk_0F;
    var_s0 = temp_v0 * 0x10;
    temp_base = &D_80126E98;
    var_s2 = ((temp_v0 * 0x20) + var_s0) + temp_base;
    do {
        if (func_80123200(var_s0 & 0xFF) & 0xFF) {
            func_80123928(*var_s2, (s16) (((var_s1 % 3) * 0x12) + 0x180), (s16) (((var_s1 / 3) * 0x10) + 0x80));
        }
        var_s1 += 1;
        var_s2 += 3;
        var_s0 += 1;
    } while (var_s1 < 0x10);
    func_80067014(0);
}
