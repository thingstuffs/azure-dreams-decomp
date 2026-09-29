#include "common.h"
#include "shared/game_work.h"
#include "m2c_compat.h"
#include "records/Rec_func_8008ACDC_arg0.h"
#include "shared/entity.h"




M2C_UNK func_80048A44(); /* extern */
M2C_UNK func_80094E34();                            /* extern */
extern u8 D_800DD0E8;

void func_80090200(void *arg0, M2C_UNK arg1, void *arg2, EntityRec *arg3) {
    /* MATCH: Keep the shared data pointer in a0 after the first call. */
    u8 *data;
    s32 mask;

    ((Rec_func_8008ACDC_arg0 *)arg0)->unk_9A.as_s8 = 0xD;
    ((Rec_func_8008ACDC_arg0 *)arg0)->unk_9B.as_s8 = 0;
    ((Rec_func_8008ACDC_arg0 *)arg0)->unk_8C.as_s32 = 0;
    ((Rec_func_8008ACDC_arg0 *)arg0)->unk_96.as_s16 = 0;
    func_80094E34(arg0);
    mask = ~0x20;
     /* MATCH: Emit the mask before loading the data pointer. */
    data = &D_800DD0E8;
    arg3->flags1C = (s32) (arg3->flags1C & mask);
    (*(M2C_UNK **)((u8 *)arg2 + 0x2C)) = data;
    func_80048A44(arg2, *((((s32) (gameWork.view.viewAngle + arg3->facing + 0x100) >> 9) & 7) + data), 0, 1);
}
