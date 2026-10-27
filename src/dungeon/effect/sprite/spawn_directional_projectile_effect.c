#include "sdk/libc.h"
#include "engine/graphics.h"
#include "slus.h"
#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "engine/node.h"

extern u8 shared_sprite_entries[];
extern u8 D_800F6000[];
extern void advance_gravity_damped_effect_motion(void *entry, void *motion, void *object);

typedef struct S_80921B2C_3 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_80921B2C_3;   /* arg0 in func_80921B2C */

typedef struct S_80921B2C_4 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_80921B2C_4;

typedef struct S_80921B2C_6 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_80921B2C_6;

/* Creates an effect at an offset position with direction-based motion and sprite settings. */
void create_damped_directional_projectile(S_80921B2C_3 *position, s16 x_offset, s16 y_offset, s16 z_offset) {
    u8 direction_table[32];
    u8 *direction_source;
    s32 effect_type;
    u8 *global_state;
    u8 *direction_state;
    ObjectPosition *motion;
    SpriteFrameState *sprite;
    ObjectNodeHeader *effect;

    direction_source = D_800F6000;
    memcpy(direction_table, direction_source, 0x20);
    effect_type = 0x212;
    global_state = ((u8 *)(&scene_object_list_anchor));
    direction_state = global_state + 0x20;
    effect = allocate_flagged_object_node(effect_type);
    if (effect != 0) {
        u8 *directions = direction_table;

        effect->update_callback = &advance_gravity_damped_effect_motion;
        register_node(effect, project_sprite_chain);
        {
            SpriteFrameState *render_state;

            render_state = effect->sprite;
            render_state->flags |= 0xC;
            render_state->tpage_abr = 0x20;
            render_state->depth_bias = 6;
            render_state->flags |= 2;
        }
        motion = effect->position;
        motion->x.v = (s32) position->unk_00;
        motion->y.v = (s32) position->unk_04;
        motion->z.v = (s32) position->unk_08;
        motion->x.w.i = (u16) (*(u16 *)&motion->x.w.i + x_offset);
        motion->y.w.i = (u16) (*(u16 *)&motion->y.w.i + y_offset);
        motion->z.w.i = (u16) (*(u16 *)&motion->z.w.i + z_offset);
        motion->velocity_x = (s32) ((*(s16 *)((u8 *)directions + (((u16) ((S_80921B2C_4 *)direction_state)->unk_2A
            >> 7) & 0x1C))) * 0x180000);
        motion->velocity_y = (s32) ((s16) ((S_80921B2C_6 *)((s8 *)directions
            + (((u16) ((S_80921B2C_4 *)direction_state)->unk_2A >> 7) & 0x1C)))->unk_02 * 0x180000);
        sprite = effect->sprite;
        sprite->scale_y = 0x800;
        sprite->scale_x = 0x800;
        sprite->color.c.b = 0x80;
        sprite->color.c.g = 0x80;
        sprite->color.c.r = 0x80;
        select_record_entry_and_value(sprite, shared_sprite_entries, 0);
    }
}
