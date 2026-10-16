/* Relink of matched dungeon/func_800CF1BC; every changed retail word is a paired relocation. */
#define D_800D4494 D_801654D4
#include "common.h"
#include "m2c_compat.h"

s32 func_800AB464();                                /* extern */
extern u8 D_801654D4;

typedef struct S_800D491C_0 {
    u8 pad_00[0x8C];
    M2C_UNK * unk_8C;
} S_800D491C_0;   /* arg0 in func_80168070 */

/* Sets the object data pointer when the status check is positive. */
void func_80168070(S_800D491C_0 *object) {
    if (func_800AB464() > 0) {
        object->unk_8C = &D_801654D4;
    }
}
