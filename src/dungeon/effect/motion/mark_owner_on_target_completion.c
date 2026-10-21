#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/dungeon_sprite_data.h"
#include "shared/slus_callbacks.h"
#include "shared/game_work.h"
#include "shared/dungeon_moving_views.h"

typedef struct S_80024550_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80024550_0;

typedef struct S_80024550_1 {
    u8 pad_00[0x8];
    s16 unk_08;
} S_80024550_1;

typedef struct S_80024550_3 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80024550_3;

   /* arg0 in mark_owner_on_target_completion */

extern s32 rand(void);
extern void func_8003DB94(void *, void *, s32);
extern s32 func_80064584(s32);
extern s32 func_800644B8(s32);
extern void register_node(void *, void *);

extern u8 D_800244A4[];

/* Spawn an effect at a random radial offset from the given position. */
void mark_owner_on_target_completion(MovingPosition *origin)
{
    GameWork *scene_state;
    s32 random_value;
    s32 adjusted_random;
    SpriteFrameState *render_data;
    S_80024550_3 *position;
    S_80024550_1 *effect_state;
    void *effect;

    scene_state = &g_game_work;
    effect = func_8003FC64(0x212);
    if (effect != 0) {
        ((S_80024550_0 *)effect)->unk_10 = D_800244A4;
        adjusted_random = rand();
        random_value = adjusted_random;
        effect_state = (u8 *)effect + 0x20;
        if (random_value < 0) {
            adjusted_random = random_value + 0xFFF;
        }
        effect_state->unk_08 = (random_value % 4096);
        render_data = ((S_80024550_0 *)effect)->unk_0C;
        render_data->color.c.b = 0x80;
        render_data->color.c.g = 0x80;
        render_data->color.c.r = 0x80;
        func_8003DB94(render_data, effect_sprite_sources, 0);
        render_data->scale_y = 0x1000;
        render_data->scale_x = 0x1000;
        render_data->tpage_abr |= 0x20;
        render_data->flags |= 0xC;
        render_data->angle_z =
            (s32)(0 - ((func_80064584(effect_state->unk_08 -
                                      scene_state->view.camera_rotation.parts.viewAngle) >> 4) << 8)) >> 8;
        register_node(effect, project_sprite_chain);
        position = ((S_80024550_0 *)effect)->unk_08;
        position->unk_02 = origin->unk_02 +
            ((func_800644B8(effect_state->unk_08) * 2) >> 8);
        position->unk_06 = origin->unk_06 +
            ((func_80064584(effect_state->unk_08) * 2) >> 8);
        position->unk_0A = origin->unk_0A;
    }
}
