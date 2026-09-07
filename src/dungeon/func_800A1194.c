#include "common.h"
#include "m2c_compat.h"

typedef struct S_800A68F4_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_800A68F4_0;   /* D_800E3D7C in func_800A68F4 */


extern u8 D_800DD878;
extern S_800A68F4_0 *D_800E3D7C;

void func_800A68F4(void) {
    if (D_800DD878 != 0) {
        D_800E3D7C->unk_1C = (s32) (D_800E3D7C->unk_1C | 0x10);
    }
}
