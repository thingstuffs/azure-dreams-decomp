#include "common.h"
#include "m2c_compat.h"

typedef struct S_800A68C0_0 {
    u8 pad_00[0x1C];
    u32 unk_1C;
} S_800A68C0_0;   /* D_800E3D7C in func_800A68C0 */


extern s8 D_800DD878;
extern S_800A68C0_0 *D_800E3D7C;

void func_800A68C0(void) {
    D_800DD878 = ((u32) D_800E3D7C->unk_1C >> 4) & 1;
    D_800E3D7C->unk_1C = (u32) (D_800E3D7C->unk_1C & ~0x10);
}
