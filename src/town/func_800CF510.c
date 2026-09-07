#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern M2C_UNK D_800D70A0;

typedef struct S_800CCC70_0 {
    u8 pad_00[0x68];
    s16 unk_68;
} S_800CCC70_0;   /* arg0 in func_800CCC70 */

void func_800CCC70(S_800CCC70_0 *arg0) {
    ((void (*)()) (*(M2C_UNK *)((u8 *)&D_800D70A0 + ((arg0->unk_68) * 4))))();
}