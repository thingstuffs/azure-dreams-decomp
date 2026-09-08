#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_801724B0_arg0.h"
#include "records/Rec_D_800E3D7C.h"




M2C_UNK func_80047784();         /* extern */
extern s16 D_80083228;
extern u8 D_800E2360;

/* Initializes state and configures the target using an angle-indexed table entry. */
void func_80172E0C(void *state, M2C_UNK unused, void *target, void *angleSource) {
    ((Rec_func_801724B0_arg0 *)state)->unk_9A = 0x10;
    ((Rec_func_801724B0_arg0 *)state)->unk_9B = 0;
    (*(M2C_UNK **)((u8 *)target + 0x2C)) = &D_800E2360;
    func_80047784(target, *((((s32) (D_80083228 + ((Rec_D_800E3D7C *)angleSource)->unk_2A.as_s16 + 0x100) >> 9) & 7) + &D_800E2360), 0);
    ((Rec_func_801724B0_arg0 *)state)->unk_AA = 0;
}
