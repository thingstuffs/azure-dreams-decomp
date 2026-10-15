#include "modules/town_town_windows.h"

/* Invoke the entity callback and perform follow-up processing unless its flags suppress it. */
void func_8009DE28(func_800A06C8_EntityLike *entity, s32 callback_id, s32 callback_data)
{
    u16 *flags = (u16 *)((u8 *)entity - 2);

    entity->unk50(entity, entity, callback_id, callback_data);
    if (!(*flags & 0x8000)) {
        func_800970AC(func_8009706C(callback_id), entity);
        if (entity->unk4D == 0x13) {
            func_800478B8((void *)callback_data);
        }
    }
}
