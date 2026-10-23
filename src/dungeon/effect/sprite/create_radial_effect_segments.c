#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/game_work.h"
#include "m2c_compat.h"
#include "records/Rec_func_800D6DC0_arg1.h"

typedef struct S_800D6C18_2 S_800D6C18_2;

/* cfail-repair: tf7-phase1-cache-v3 */
void *allocate_list_node(s32, void *);       /* extern */
void register_node(void *, void *); /* extern */
s32 rsin(s32);                           /* extern */
s32 rcos(s32);                           /* extern */
void select_sprite_entry(void *, u8, s32);              /* extern */
extern s32 draw_linked_depth_sliced_quads(void *payload, void *position, void *render_state);
extern void update_expiring_sprite_effect(void *effect, S_800D6C18_2 *size_state);
extern M2C_UNK radial_effect_frames;

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

typedef struct S_800D6DC0_0 {
    u8 pad_00[0xC];
    s16 unk_0C;
    s16 unk_0E;
    s16 unk_10;
    u8 pad_12[0x2];
    void * unk_14;
    u8 pad_18[0x2C];
    s16 unk_44;
    s16 unk_46;
    s16 unk_48;
    s16 unk_4A;
    s16 unk_4C;
    s16 unk_4E;
    s16 unk_50;
    s16 unk_52;
    s16 unk_54;
    s16 unk_56;
    s16 unk_58;
    s16 unk_5A;
} S_800D6DC0_0;


typedef struct S_800D6DC0_4 {
    u8 pad_00[0x2A];
    s16 unk_2A;
} S_800D6DC0_4;   /* arg3 in create_radial_effect_segments */

/* Creates eight radial effect segments using the source position and render data. */
void create_radial_effect_segments(void *unused, Rec_func_800D6DC0_arg1 *origin, void *render_template, S_800D6DC0_4 *orientation) {
    s32 end_y_scaled;
    s32 start_angle;
    s32 copy_end;
    s32 start_x;
    s32 end_x;
    s32 start_y;
    s32 end_y;
    s32 end_angle;
    s32 segment;
    ObjectPosition *position;
    S_800D6DC0_0 *effect_state;
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
        effect = allocate_list_node(0x112, ((u8 *)(&scene_object_list_anchor)));
        effect_state = ((void *)effect) + 0x20;
        if (effect != NULL) {
            copy_src = render_template;
            effect_state->unk_0C = 0x1E;
            effect_state->unk_0E = 0x1E;
            effect_state->unk_14 = origin;
            effect_state->unk_10 = segment;
            render_data = effect->sprite;
            effect->update_callback = &update_expiring_sprite_effect;
            copy_end = (s32)((u8 *)copy_src + 0x30);
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
            position->x.w.i = (u16) origin->unk_02;
            start_angle = segment << 9;
            position->y.w.i = (u16) origin->unk_06;
            position->z.w.i = (s16) (origin->unk_0A + 0x28);
            render_data->scale_y = 0x1000;
            render_data->scale_x = 0x1000;
            render_data->color.c.b = 0xFA;
            render_data->color.c.g = 0xFA;
            render_data->color.c.r = 0xFA;
            start_x = (s32) (scale * rcos(start_angle)) >> 0xC;
            effect_state->unk_48 = (s16) start_x;
            effect_state->unk_44 = (s16) start_x;
            end_x = (s32) (scale * rcos(end_angle)) >> 0xC;
            effect_state->unk_4A = (s16) end_x;
            effect_state->unk_46 = (s16) end_x;
            start_y = (s32) (scale * rsin(start_angle)) >> 0xC;
            effect_state->unk_50 = (s16) start_y;
            effect_state->unk_4C = (s16) start_y;
            end_y_scaled = scale * rsin(end_angle);
            effect_state->unk_5A = 0;
            effect_state->unk_58 = 0;
            effect_state->unk_56 = 0;
            effect_state->unk_54 = 0;
            end_y = end_y_scaled >> 0xC;
            effect_state->unk_52 = (s16) end_y;
            effect_state->unk_4E = (s16) end_y;
            *((s16 *)&position->velocity_z + 1) = 0;
            render_data->frameTable = direction_table;
            select_sprite_entry(render_data, *((u8 *) (((((s32) (g_game_work.view.camera_rotation.parts.viewAngle + orientation->unk_2A + 0x100)
                >> 9) & 7) + (s32) direction_table))), 0);
        }
        segment += 1;
        end_angle += 0x200;
    } while (segment < 8);
    return;
}
