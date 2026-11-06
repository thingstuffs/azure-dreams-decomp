#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/game_work.h"
#include "m2c_compat.h"
#include "dungeon/effect/sprite.h"
#include "dungeon/effect/radial_effect_segment.h"
#include "engine/graphics.h"
#include "engine/node.h"
#include "sdk/libgte.h"
#include "dungeon/data.h"
#include "dungeon/effect/shade.h"

typedef struct S_800D6C18_2 S_800D6C18_2;

/* cfail-repair: tf7-phase1-cache-v3 */
extern void update_expiring_sprite_effect(RadialEffectSegmentBody *effect, S_800D6C18_2 *size_state);

typedef struct {
    s32 w0;
    s32 w1;
    s32 w2;
    s32 w3;
} CopyQuad;

typedef struct {
    u8 pad[8];
    void *field8;
    void *fieldc;
    void *field10;
} AllocBlock;

   /* arg3 in create_radial_effect_segments */

/* Creates eight radial effect segments using the source position and render data. */
void create_radial_effect_segments(ActorRecord *unused, ObjectPosition *origin, void *render_template, ActorRecord *orientation) {
    s32 end_y_scaled;
    s32 start_angle;
    u8 * copy_end;
    s32 start_x;
    s32 end_x;
    s32 start_y;
    s32 end_y;
    s32 end_angle;
    s32 segment;
    ObjectPosition *position;
    RadialEffectSegmentBody *effect_state;
    SpriteFrameState *render_data;
    ObjectNodeHeader *effect;
    void *copy_dst;
    void *copy_src;
    u8 *direction_table;
    s32 scale = 3;

    segment = 0;
    direction_table = (u8 *)&radial_effect_frames;
    end_angle = 0x200;
    do {
        effect = allocate_list_node(0x112, &scene_object_list_anchor.next);
        effect_state = NODE_BODY(effect);
        if (effect != NULL) {
            copy_src = render_template;
            effect_state->unk_0C = 0x1E;
            effect_state->unk_0E = 0x1E;
            effect_state->unk_14 = origin;
            effect_state->unk_10 = segment;
            render_data = effect->sprite;
            effect->update_callback = &update_expiring_sprite_effect;
            copy_end = ((u8 *)copy_src + 0x30);
            copy_dst = render_data;
            do {
                *(CopyQuad *)copy_dst = *(CopyQuad *)copy_src;
                copy_src += 0x10;
                copy_dst += 0x10;
            } while (copy_src != (void *)copy_end);
            render_data->tpage_abr = 0x20;
            render_data->flags = (u16) (render_data->flags | 0xC);
            register_node(effect, &draw_linked_depth_sliced_quads);
            position = effect->position;
            position->x.w.i = (u16) origin->x.unsigned_parts.integer;
            start_angle = segment << 9;
            position->y.w.i = (u16) origin->y.unsigned_parts.integer;
            position->z.w.i = (s16) (origin->z.unsigned_parts.integer + 0x28);
            render_data->scale_y = 0x1000;
            render_data->scale_x = 0x1000;
            render_data->color.c.b = 0xFA;
            render_data->color.c.g = 0xFA;
            render_data->color.c.r = 0xFA;
            start_x = (s32) (scale * rcos(start_angle)) >> 0xC;
            effect_state->x[2] = (s16) start_x;
            effect_state->x[0] = (s16) start_x;
            end_x = (s32) (scale * rcos(end_angle)) >> 0xC;
            effect_state->x[3] = (s16) end_x;
            effect_state->x[1] = (s16) end_x;
            start_y = (s32) (scale * rsin(start_angle)) >> 0xC;
            effect_state->y[2] = (s16) start_y;
            effect_state->y[0] = (s16) start_y;
            end_y_scaled = scale * rsin(end_angle);
            effect_state->unk_5A = 0;
            effect_state->unk_58 = 0;
            effect_state->unk_56 = 0;
            effect_state->unk_54 = 0;
            end_y = end_y_scaled >> 0xC;
            effect_state->y[3] = (s16) end_y;
            effect_state->y[1] = (s16) end_y;
            *((s16 *)&position->velocity_z + 1) = 0;
            render_data->frameTable = direction_table;
            select_sprite_entry(render_data, *((u8 *) (((((s32) (g_game_work.view.camera_rotation.parts.viewAngle + orientation->facing + 0x100)
                >> 9) & 7) + (s32) direction_table))), 0);
        }
        segment += 1;
        end_angle += 0x200;
    } while (segment < 8);
    return;
}
