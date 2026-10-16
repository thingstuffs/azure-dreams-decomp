#include "common.h"
#include "shared/dungeon_status.h"
#include "records/Rec_func_800AD058_arg0.h"
#include "shared/entity.h"
#include "records/Rec_func_800AD058_arg2.h"


typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern s32 func_800A56E0();
extern s32 dungeonUpdateActorDefeatRemoval();
extern void dungeonCreateAndInitializesDisplaySourcePositionAppearance();


/* Initializes the visual effect and advances its action state. */
void dungeonInitializeTheVisualEffectAdvancesActionState(Rec_func_800AD058_arg0 *action, s32 context, Rec_func_800AD058_arg2 *visual, EntityRec *entity) {
    s32 one;
    s32 phase;

    phase = action->unk_9B;
    one = 1;
    switch (phase) {
    case 0:
        if (dungeonStatus.unk_0A != 0) {
            return;
        }
        action->unk_9B = (u8)one;
    case 1:
        if (entity->unk_49 != 0) {
            dungeonCreateAndInitializesDisplaySourcePositionAppearance(context, visual, entity);
            entity->unk_48 = 0;
            entity->unk_49 = 0U;
        }

        visual->unk_10 = 0x20;
        visual->unk_12 = (u16)(visual->unk_12 - 0x80);
        visual->unk_14 = (u16)(visual->unk_14 | 0xC);
        entity->flags1C = entity->flags1C | 0x10000000;
        visual->unk_0C = 0x808080;
        action->unk_96 = 0x10;
        action->unk_9B = (u8)(action->unk_9B + 1);
        func_800A56E0(0x805);
        return;
    case 2:
        dungeonUpdateActorDefeatRemoval(action, context, visual, entity);
        return;
    }
}
