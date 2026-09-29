#include "common.h"
#include "shared/game_work.h"
#include "m2c_compat.h"
#include "records/Rec_func_801724B0_arg0.h"
#include "shared/entity.h"




M2C_UNK func_80047784();         /* extern */
extern u8 D_800E2360;

/* Initializes state and configures the target using an angle-indexed table entry. */
void func_80172E0C(void *state, M2C_UNK unused, void *target, EntityRec *angleSource) {
    ((Rec_func_801724B0_arg0 *)state)->unk_9A = 0x10;
    ((Rec_func_801724B0_arg0 *)state)->unk_9B = 0;
    (*(M2C_UNK **)((u8 *)target + 0x2C)) = &D_800E2360;
    func_80047784(target, *((((s32) (gameWork.view.viewAngle + angleSource->facing + 0x100) >> 9) & 7) + &D_800E2360), 0);
    ((Rec_func_801724B0_arg0 *)state)->unk_AA = 0;
}
