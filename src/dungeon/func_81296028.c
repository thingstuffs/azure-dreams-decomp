/* Relink of matched dungeon/func_800CF1BC at file 0xEF1BC; imports and data use paired retail relocations. */
#include "common.h"
#include "m2c_compat.h"

s32 func_800AA11C();                                /* extern */
extern u8 D_80158514;

typedef struct S_800D491C_0 {
    u8 pad_00[0x8C];
    M2C_UNK * unk_8C;
} S_800D491C_0;   /* arg0 in func_8015A828 */

/* Sets the object data pointer when the status check is positive. */
void func_8015A828(S_800D491C_0 *object) {
    if (func_800AA11C() > 0) {
        object->unk_8C = &D_80158514;
    }
}
