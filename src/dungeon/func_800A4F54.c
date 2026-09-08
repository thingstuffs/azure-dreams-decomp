#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "records/Rec_func_800AA258_arg2.h"

M2C_UNK func_80047784();         /* extern */
M2C_UNK func_800AA754();         /* extern */
extern s16 D_80083228[8];
extern void *D_80083470[3];


/* Set the entity to state 7 and select its directional sprite frame when ready. */
s32 func_800AA6B4(void *entity, M2C_UNK context, Rec_func_800AA258_arg2 *sprite, s32 direction_frames) {
    if (((Rec_func_800A9E70_arg0 *)entity)->unk_64 > 0) {
        func_800AA754(entity, context, sprite, entity);
        return 0;
    }
    D_80083470[0] = (void *) ((s8 *) entity - 0x20);
    ((Rec_func_800A9E70_arg0 *)entity)->unk_9A.as_s8 = 7;
    ((Rec_func_800A9E70_arg0 *)entity)->unk_9B.as_s8 = 0;
    ((Rec_func_800A9E70_arg0 *)entity)->unk_8C = 0;
    if (direction_frames != 0) {
        if (!(((Rec_func_800A9E70_arg0 *)entity)->unk_1C & 0x20)) {
            sprite->unk_2C.as_s32 = direction_frames;
            func_80047784(sprite, *((u8 *) direction_frames + (((s32) (D_80083228[0] + ((Rec_func_800A9E70_arg0 *)entity)->unk_2A + 0x100) >> 9) & 7)), 0);
        }
    }
    return 1;
}
