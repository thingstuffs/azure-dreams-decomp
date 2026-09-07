#include "common.h"
#include "m2c_compat.h"

typedef struct S_80172E0C_0 {
    u8 pad_00[0x9A];
    s8 unk_9A;
    s8 unk_9B;
    u8 pad_9C[0xE];
    s16 unk_AA;
} S_80172E0C_0;   /* arg0 in func_80172E0C */

typedef struct S_80172E0C_1 {
    u8 pad_00[0x2A];
    s16 unk_2A;
} S_80172E0C_1;   /* arg3 in func_80172E0C */


M2C_UNK func_80047784();         /* extern */
extern s16 D_80083228;
extern u8 D_800E2360;

/* Initializes state and configures the target using an angle-indexed table entry. */
void func_80172E0C(void *state, M2C_UNK unused, void *target, void *angleSource) {
    ((S_80172E0C_0 *)state)->unk_9A = 0x10;
    ((S_80172E0C_0 *)state)->unk_9B = 0;
    (*(M2C_UNK **)((u8 *)target + 0x2C)) = &D_800E2360;
    func_80047784(target, *((((s32) (D_80083228 + ((S_80172E0C_1 *)angleSource)->unk_2A + 0x100) >> 9) & 7) + &D_800E2360), 0);
    ((S_80172E0C_0 *)state)->unk_AA = 0;
}
