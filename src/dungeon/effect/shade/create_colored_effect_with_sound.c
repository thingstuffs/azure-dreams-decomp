#include "shared/object_node.h"
#include "slus.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"

#include "common.h"
#include "records/Rec_func_800D4BD4_arg1.h"

typedef s32 M2C_UNK;

void emit_particles_until_expired(Rec_func_800D4BD4_arg1 *emitter, ObjectPosition *position, s32 init_param);
#include "shared/sprite_source.h"
#include "dungeon/system.h"

extern SpriteSourceEntry fading_sprite_entries[];
/* Creates a colored effect at the source position and optionally plays a sound. */
void create_colored_effect_with_sound(void *source, s32 color, unsigned short sound_id)
{
    DungeonGlobalStatus *effect_state;
    s32 *color_ptr;
    s32 sound;
    s32 packed_color;
    SpriteFrameState *render_flags;
    SpriteFrameState *render_data;
    void *effect_data;
    void *sprite_data;
    ObjectNodeHeader *effect;
    ObjectPosition *position;
    color_ptr = &color;
    effect = allocate_flagged_object_node(0x12);
    if (effect != 0) {
        effect_data = NODE_BODY(effect);
        *((void **) (((u8 *) effect_data) + 0x24)) = source;
        effect->update_callback = &emit_particles_until_expired;
        *((s16 *) (((u8 *) effect_data) + 0x1E)) = 0x1E;
        render_flags = effect->sprite;
        render_flags->tpage_abr = 0x20;
        render_flags->flags = (u16) (render_flags->flags | 0xC);
        position = effect->position;
        position->x.w.i = (u16) ((ObjectNodeHeader *)source)->position->x.unsigned_parts.integer;
        position->y.w.i = (u16) ((ObjectNodeHeader *)source)->position->y.unsigned_parts.integer;
        position->z.w.i = (u16) ((ObjectNodeHeader *)source)->position->z.unsigned_parts.integer;
        render_data = effect->sprite;
        render_data->color.c.b = 0x80;
        render_data->color.c.g = 0x80;
        render_data->color.c.r = 0x80;
        packed_color = *color_ptr;
        render_data->scale_y = ONE;
        render_data->scale_x = ONE;
        render_data->color.word = packed_color;
        *((s32 *) (((u8 *) effect_data) + 0xC)) = packed_color;
        render_data->clut = 0x7DCE;
        sprite_data = fading_sprite_entries;
        render_data->flags = (u16) (render_data->flags | 0x100);
        select_record_entry_and_value(render_data, sprite_data, 0);
        sound = sound_id & 0xFFFF;
        if (sound != 0) {
            play_sound_if_enabled(sound);
        }
        effect_state = &g_dungeon_status;
        effect_state->activity_counts.parts.pending_action_count = (u16) ((((u16)(effect_state->activity_counts.parts.pending_action_count))) + 1);
    }
}
