#include "modules/dungeon_ovl_e0365c.h"

void dungeonAdvanceActorStateWhenAllowed(void *state_ctx, s32 entity_id, void *action, void *entity)
{
    s32 state;
    u16 flags;

    state = ((E_80173CE0_S_80173CE0_0 *)state_ctx)->unk_9B;
    switch (state) {
    case 0:
        flags = ((E_80173CE0_S_80173CE0_1 *)action)->unk_14;
        if (flags & 0x8000) {
            ((E_80173CE0_S_80173CE0_1 *)action)->unk_14 = flags | 0x6000;
            ((E_80173CE0_S_80173CE0_0 *)state_ctx)->unk_9B = 2;
            return;
        }
        ((E_80173CE0_S_80173CE0_0 *)state_ctx)->unk_9B = 1;

    case 1:
        if (!((((E_80173CE0_S_80173CE0_1 *)action)->unk_04 == 8) &&
              (((E_80173CE0_S_80173CE0_1 *)action)->unk_14 & 0x1000)) &&
            !(((E_80173CE0_S_80173CE0_1 *)action)->unk_14 & 0xE000)) {
            return;
        }
        func_801744B8(entity);
        func_800A56E0(0x80C);
        dungeonCreateFourDirectionalEffects(state_ctx, entity_id, action);
        ((E_80173CE0_S_80173CE0_0 *)state_ctx)->unk_9B++;
        return;

    case 2:
        if (((E_80173CE0_S_80173CE0_1 *)action)->unk_14 & 0xE000) {
            dungeonReduceActorFoodMeter(entity, 0x400);
            dungeonSetRecordIntegerTileCenter(entity_id, ((E_80173CE0_S_80173CE0_1 *)action)->unk_24, ((E_80173CE0_S_80173CE0_1 *)action)->unk_25);
            ((E_80173CE0_S_80173CE0_0 *)state_ctx)->unk_8C = func_80170E5C;
            dungeonStatus.unk_0C = 0;
            (*(u16 *)((u8 *)entity + 0x46)) &= 0x7FFF;
        }

        return;
    }
}
