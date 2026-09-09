#include "common.h"
#include "records/Rec_func_800AD058_arg0.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_func_800AD058_arg2.h"



typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern M2C_UNK func_800A56E0();
extern M2C_UNK func_800AD058();
extern M2C_UNK func_80174D48();
extern s16 D_8008346A[];




/* Initializes the visual effect and advances its action state. */
void func_801736EC(Rec_func_800AD058_arg0 *action, M2C_UNK context, Rec_func_800AD058_arg2 *visual, Rec_D_800E3D7C *entity) {
    M2C_UNK one;
    M2C_UNK color;
    M2C_UNK phase;

    phase = action->unk_9B;
    one = 1;
    if (phase == one) {
        goto initialize;
    }
    if (phase >= 2) {
        goto check_update;
    }
    if (phase == 0) {
        goto wait_ready;
    }
    goto done;

check_update:
    if (phase == 2) {
        goto update;
    }
    goto done;

wait_ready:
    if (D_8008346A[0] != 0) {
        goto done;
    }
    action->unk_9B = (u8)one;

initialize:
    if (entity->unk_48.at01_u8.v != 0) {
        func_80174D48(context, visual, entity);
        do {
            entity->unk_48.at00_s8.v = 0;
        } while (0);
        entity->unk_48.at01_u8.v = 0U;
        color = 0x808080;
    } else {
        color = 0x808080;
    }
    visual->unk_10 = 0x20;
    visual->unk_12 = (u16)(visual->unk_12 - 0x80);
    visual->unk_14 = (u16)(visual->unk_14 | 0xC);
    entity->unk_1C.as_s32 = entity->unk_1C.as_s32 | 0x10000000;
    visual->unk_0C = color;
    action->unk_96 = 0x10;
    action->unk_9B = (u8)(action->unk_9B + 1);
    func_800A56E0(0x805, color);
    goto done;

update:
    func_800AD058(action, context, visual, entity);

done:
    return;
}
