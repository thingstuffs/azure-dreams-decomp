#include "shared/object_node.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"

typedef struct Rec_func_800D4BD4_arg2 Rec_func_800D4BD4_arg2;

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef int s32;
typedef s32 M2C_UNK;

extern void select_record_entry_and_value(void *, void *, s32);
extern void play_sound_if_enabled(s32);
void emit_randomized_relative_particles(void *emitter, Rec_func_800D4BD4_arg2 *position, s32 spawn_context);
#include "shared/sprite_source.h"
extern SpriteSourceEntry fading_sprite_entries[];
/* Creates a colored effect at the source object's position. */
void create_colored_effect_with_event(ObjectNodeHeader *source, s32 color, unsigned short event_id)
{
    DungeonGlobalStatus *effect_state;
    s32 *color_ptr;
    s32 event_code;
    s32 effect_color;
    SpriteFrameState *render_setup;
    SpriteFrameState *render_data;
    void *effect_data;
    void *render_params;
    ObjectNodeHeader *effect;
    ObjectPosition *position;
    color_ptr = &color;
    effect = allocate_flagged_object_node(0x12);
    if (effect != 0) {
        effect_data = ((void *)effect) + 0x20;
        *((void **) (((u8 *) effect_data) + 0x24)) = source;
        effect->update_callback = &emit_randomized_relative_particles;
        *((s16 *) (((u8 *) effect_data) + 0x1E)) = 0x32;
        render_setup = effect->sprite;
        render_setup->tpage_abr = 0x20;
        render_setup->flags = (u16) (render_setup->flags | 0xC);
        position = effect->position;
        position->x.w.i = (u16) (*((u16 *) (((u8 *) (source->position)) + 2)));
        position->y.w.i = (u16) (*((u16 *) (((u8 *) (source->position)) + 6)));
        position->z.w.i = (u16) (*((u16 *) (((u8 *) (source->position)) + 0xA)));
        render_data = effect->sprite;
        render_data->color.c.b = 0x80;
        render_data->color.c.g = 0x80;
        render_data->color.c.r = 0x80;
        effect_color = *color_ptr;
        render_data->scale_y = ONE;
        render_data->scale_x = ONE;
        render_data->color.word = effect_color;
        *((s32 *) (((u8 *) effect_data) + 0xC)) = effect_color;
        render_data->clut = 0x7DCE;
        render_params = fading_sprite_entries;
        render_data->flags = (u16) (render_data->flags | 0x100);
        select_record_entry_and_value(render_data, render_params, 0);
        event_code = event_id & 0xFFFF;
        if (event_code != 0) {
            play_sound_if_enabled(event_code);
        }
        effect_state = &g_dungeon_status;
        effect_state->activity_counts.parts.pending_action_count = (u16) ((*(u16 *)&effect_state->activity_counts.parts.pending_action_count) + 1);
    }
}
