#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/animation_views.h"
#include "engine/graphics.h"
#include "engine/texture.h"

/* Entry struct pointed to by S_80047784.unk00; only the leading u16 field is
 * accessed by this function. */

/* Object shared with select_indirect_table_entry (its first parameter). */

/* Select a table entry, set its rate, clear flags 0x6000, and update the object. */
void select_sprite_entry(SpriteFrameState *object, s16 table_index, s16 entry_index)
{
    extern u8 animation_tick_scale;

    select_indirect_table_entry(object, table_index, entry_index);
    object->frame_ticks = (*(AnimationFrameRate **)&object->unk_00)->value / animation_tick_scale;
    object->flags &= 0x9FFF;
    upload_entry_textures(object);
}
