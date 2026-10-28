#include "common.h"
#include "engine/menu.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/entity_objects.h"
#include "shared/slus_callbacks.h"
#include "shared/object_flags.h"
#include "shared/vector.h"

typedef struct State8081A3D8 {
    s16 state;
    u16 timer;
    u16 phase;
    s16 threshold;
    s16 rate;
    s16 countdown;
    u16 flags;
} State8081A3D8;

extern u16 high_display_best_score[];
extern u8 D_800200B4[];
extern u8 D_800200C0[];
extern u8 minigame_display_callback_a[];
extern u8 minigame_display_callback_b[];
extern u8 D_80024B48[];
extern s32 text_sprite_builder_address[4];

extern u8 D_800F7DFC[];

extern void clear_resident_bit(s32);
extern void set_resident_bit(s32);
#include "slus.h"
extern void sound_set_cd_cue_parameters(s32, s32, s32, s32);
extern void *allocate_list_node(s32, void *);
extern void register_node(void *, void *);
extern void clear_alternate_texture_regions(s32);

extern void tw_sd_sq_ld_call(s32, s32);

typedef struct S_800243D8_1 {
    u8 pad_00[0xA0];
    s16 unk_A0;
    u8 pad_A2[0xA];
    State8081A3D8 * unk_AC;
} S_800243D8_1;   /* object_tail in advance_object_spawning_displays_high */

typedef struct S_800243D8_2 {
    u8 pad_00[0x2];
    s16 unk_02;
    union { struct { void * v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_04;   /* overlapping accesses */
    s32 unk_08;
    union {
        struct { s32 v; } at00;
        struct { s16 v; } at00u;
        struct { u8 pad[0x2]; s16 v; } at02;
    } unk_0C;   /* overlapping accesses */
    union {
        struct { s32 v; } at00;
        struct { s16 v; } at00u;
        struct { u8 pad[0x2]; s16 v; } at02;
    } unk_10;   /* overlapping accesses */
    s16 unk_14;
    union { s16 s; u16 u; } unk_16;   /* accessed as both */
    u8 pad_18[0x2];
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} S_800243D8_2;   /* inner in advance_object_spawning_displays_high */

   /* ((S_800243D8_0 *)object)->unk_08 in advance_object_spawning_displays_high */

/* Advances object spawning, result displays, and high-score handling. */
void advance_object_spawning_displays_high(State8081A3D8 *controller)
{
    ObjectNodeHeader *object;
    S_800243D8_2 *object_data;
    SpriteFrameState *inner_data;
    u8 *callback;
    s16 spawn_interval;
    s16 spawn_rate;
    s32 score_threshold;
    u16 best_score;
    s32 state;
    s32 dialog_zero;

    callback = D_800200B4;
    spawn_rate = controller->rate;
    spawn_interval = 42 - spawn_rate / 6;
    if (spawn_interval < 16) {
        spawn_interval = 16;
    }

    if (view_reference_entity.y.v > 0x03200000) {
        view_reference_entity.y.v = 0x03200000;
    }

    state = controller->state;
    switch (state) {
    case 0:
    case 1:
        if (((s16)controller->timer % spawn_interval) == 0) {
            if (controller->countdown > 0 || (controller->state == 1 && (controller->flags & 4))) {
            controller->timer = 0;
            controller->phase = (controller->phase + 1) & 3;
            if (controller->state == 0) {
                controller->countdown--;
            }

            object = allocate_list_node(0x136, &scene_object_list_anchor.next);
            if (object != 0) {
                S_800243D8_1 *object_tail = (S_800243D8_1 *)(((u8 *)object) + 0x20);
                object->update_callback = D_80024B48;
                register_node(object, project_sprite_chain);
                inner_data = object->sprite;
                ((IntVector3 *)(*(u8 * *)&object->position))->x = 0x03200000;
                ((IntVector3 *)(*(u8 * *)&object->position))->y = 0x02E00000;
                ((IntVector3 *)(*(u8 * *)&object->position))->z = 0xFFFC0000;
                {
                    u16 object_phase = controller->phase;
                    object_tail->unk_AC = controller;
                    object_tail->unk_A0 = object_phase;
                }
                inner_data->scale_y = 0x1000;
                inner_data->scale_x = 0x1000;
                inner_data->depth_bias = -0x100;
                select_record_entry_and_value(inner_data, D_800F7DFC, 0);
                inner_data->color.word = 0x00808080;
            }
            controller->flags |= 1;
            }
        }
        controller->timer++;
        if (controller->flags & 1) {
            break;
        }
        if (controller->countdown > 0) {
            break;
        }
        if (controller->flags & 4) {
            controller->state = 2;
            break;
        }

        object = allocate_list_node(((s32)(1)), &scene_object_list_anchor.next);
        if (object != 0) {
            object_data = (S_800243D8_2 *)(((u8 *)object) + 0x20);
            object->update_callback = minigame_display_callback_a;
            register_node(object, text_sprite_builder_address);
            object_data->unk_14 = 0x7C;
            object_data->unk_16.s = 0x78;
            object_data->unk_1A = 0x7C80;
            object_data->unk_10.at00.v = 0x00808080;
            object_data->unk_04.at00.v = callback;
            object_data->unk_02 = 0x96;
        }

        object = allocate_list_node(((s32)(1)), &scene_object_list_anchor.next);
        if (object != 0) {
            object_data = (S_800243D8_2 *)(((u8 *)object) + 0x20);
            object->update_callback = minigame_display_callback_b;
            register_node(object, build_menu_line_tile_packets);
            object_data->unk_0C.at00u.v = 0x74;
            object_data->unk_0C.at02.v = 0x74;
            object_data->unk_10.at00u.v = 0x58;
            object_data->unk_10.at02.v = 0x10;
            object_data->unk_08 = 0x00101010;
            object_data->unk_02 = 0x96;
            object_data->unk_16.u |= 1;
        }
        controller->timer = 0x96;
        controller->state = 3;
        break;

    case 2:
        object = allocate_list_node(((s32)(1)), &scene_object_list_anchor.next);
        if (object != 0) {
            object_data = (S_800243D8_2 *)(((u8 *)object) + 0x20);
            object->update_callback = minigame_display_callback_a;
            register_node(object, text_sprite_builder_address);
            object_data->unk_14 = 0x80;
            object_data->unk_16.s = 0x78;
            object_data->unk_1A = 0x7C80;
            object_data->unk_04.at00.v = D_800200C0;
            object_data->unk_10.at00.v = 0x00808080;
            object_data->unk_02 = 0x96;
        }

        object = allocate_list_node(((s32)(1)), &scene_object_list_anchor.next);
        if (object != 0) {
            object_data = (S_800243D8_2 *)(((u8 *)object) + 0x20);
            object->update_callback = minigame_display_callback_b;
            register_node(object, build_menu_line_tile_packets);
            object_data->unk_0C.at00u.v = 0x78;
            object_data->unk_0C.at02.v = 0x74;
            object_data->unk_10.at00u.v = 0x50;
            object_data->unk_10.at02.v = 0x10;
            object_data->unk_08 = 0x00101010;
            object_data->unk_02 = 0x96;
            object_data->unk_16.u |= 1;
        }
        controller->state = 4;
        controller->timer = 0x64;
        break;

    case 4:
        controller->timer--;
        if ((s16)controller->timer >= 0) {
            break;
        }
        controller->timer = 0;
        controller->state = 1;
        break;

    case 3:
        controller->timer--;
        if ((s16)controller->timer == 0x50) {
            SD_Call(0xB1);
        }
        if ((s16)controller->timer >= 0) {
            break;
        }

        tw_sd_sq_ld_call(0x20, 0x200);
        clear_resident_bit(0xA4);
        best_score = high_display_best_score[0];
        high_display_best_score[0] = best_score;
        score_threshold = controller->threshold;
        dialog_zero = 0;
        if ((s16)best_score < score_threshold) {
            s32 dialog_id;
            dialog_id = 0x2C3D;
            sound_set_cd_cue_parameters(dialog_zero, dialog_id, 0x01000001, 0x01000271);
            SD_Call(0x300);
            high_display_best_score[0] = controller->threshold;
            set_resident_bit(0x553);
        } else {
            s32 dialog_id;
            dialog_id = 0x2C3D;
            sound_set_cd_cue_parameters(dialog_zero, dialog_id, dialog_zero, 0x01000290);
            SD_Call(0x300);
            clear_resident_bit(0x553);
        }
        clear_alternate_texture_regions(1);
        clear_resident_bit(0xA5);
        controller->state = 5;
        controller->flags |= 2;
        break;

    case 5:
        *((u16 *)controller - 1) |= 0x8000;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    default:
        break;
    }
    controller->flags &= 0xFFFE;
}
