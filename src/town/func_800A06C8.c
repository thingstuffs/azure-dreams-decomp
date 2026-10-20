#include "town/menu/window.h"

/* Invoke the entity callback and perform follow-up processing unless its flags suppress it. */
void invoke_entity_callback_and_follow_up(func_800A06C8_EntityLike *entity, s32 callback_id, s32 callback_data)
{
    u16 *flags = (u16 *)((u8 *)entity - 2);

    entity->unk50(entity, entity, callback_id, callback_data);
    if (!(*flags & 0x8000)) {
        set_state_bytes_from_flags(update_state_when_active(callback_id), entity);
        if (entity->unk4D == 0x13) {
            func_800478B8((void *)callback_data);
        }
    }
}
