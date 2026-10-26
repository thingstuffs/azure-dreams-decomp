#include "shared/object_node.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/dungeon_sprite_data.h"
#include "shared/slus_callbacks.h"
#include "shared/game_work.h"
#include "shared/dungeon_moving_views.h"

typedef struct S_80024550_1 {
    u8 pad_00[0x8];
    s16 unk_08;
} S_80024550_1;

   /* arg0 in mark_owner_on_target_completion */

extern s32 rand(void);
extern void select_record_entry_and_value(void *state, void *entries, short index);
extern s32 rcos(s32);
extern s32 rsin(s32);
extern void register_node(void *, void *);

extern u8 D_800244A4[];

/* Spawn an effect at a random radial offset from the given position. */
void mark_owner_on_target_completion(MovingPosition *origin)
{
    GameWork *scene_state;
    s32 random_value;
    s32 adjusted_random;
    SpriteFrameState *render_data;
    ObjectPosition *position;
    S_80024550_1 *effect_state;
    ObjectNodeHeader *effect;

    scene_state = &g_game_work;
    effect = allocate_flagged_object_node(0x212);
    if (effect != 0) {
        effect->update_callback = D_800244A4;
        adjusted_random = rand();
        random_value = adjusted_random;
        effect_state = (u8 *)effect + 0x20;
        if (random_value < 0) {
            adjusted_random = random_value + 0xFFF;
        }
        effect_state->unk_08 = (random_value % 4096);
        render_data = effect->sprite;
        render_data->color.c.b = 0x80;
        render_data->color.c.g = 0x80;
        render_data->color.c.r = 0x80;
        select_record_entry_and_value(render_data, effect_sprite_sources, 0);
        render_data->scale_y = 0x1000;
        render_data->scale_x = 0x1000;
        render_data->tpage_abr |= 0x20;
        render_data->flags |= 0xC;
        render_data->angle_z =
            (s32)(0 - ((rcos(effect_state->unk_08 -
                                      scene_state->view.camera_rotation.parts.viewAngle) >> 4) << 8)) >> 8;
        register_node(effect, project_sprite_chain);
        position = effect->position;
        position->x.w.i = origin->x +
            ((rsin(effect_state->unk_08) * 2) >> 8);
        position->y.w.i = origin->y +
            ((rcos(effect_state->unk_08) * 2) >> 8);
        position->z.w.i = origin->z;
    }
}
