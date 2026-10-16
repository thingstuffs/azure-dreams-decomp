#include "common.h"
#include "shared/transition_slots.h"
#include "shared/game_work.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"
#include "records/Rec_func_8008D024_arg0.h"


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern u8 D_800DCFB0[8];
extern s16 D_800814E8;
extern s16 func_80042900(void *, s32);
extern void func_80048A44(void *, u8, s32, s32);
extern s16 dungeonLookupDefinitionPairValue(u8, u8);
extern s16 reserveRuntimeSlot(s16 slot_id, s16 slot_value);
extern void markCategoryItemsFlag400(s32);


extern void dungeonClearPlayerLinkedActionFlags(void);
/* Initializes action state and animation, then handles the current tile type. */
void dungeonBeginSpecialTileTransition(Rec_func_8008D024_arg0 *state, s32 unused, Rec_D_80082E80 *entity, EntityRec *actor) {
    s16 tile_type;
    s16 slot_index;

    state->unk_9A = 0x25;
    state->unk_9B.as_s8 = 0;
    state->unk_8C = 0;
    dungeonClearPlayerLinkedActionFlags();
    if (func_80042900(actor, 0xA) == 0) {
        entity->unk_2C.as_pu8 = D_800DCFB0;
        func_80048A44(entity, D_800DCFB0[((s32)(gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7], 0, 1);
    }
    tile_type = dungeonLookupDefinitionPairValue(entity->unk_24, entity->unk_25);
    if (tile_type == 3) {
        slot_index = reserveRuntimeSlot(6, 0x20);
        D_800814E8 = slot_index;
        D_80083120[slot_index].unk_6 = 1;
        state->unk_9B.as_s8 = 0x10;
        return;
    }
    if (tile_type == 4) {
        *(s32 *)0x80012090 = 2;
        markCategoryItemsFlag400(2);
    }
}
