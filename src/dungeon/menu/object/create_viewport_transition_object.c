#include "shared/object_node.h"
#include "dungeon/menu.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/dungeon_floor.h"
#include "engine/node.h"
#include "dungeon/menu_callbacks_api.h"

#ifndef NULL
#define NULL 0
#endif




typedef struct Obj12ConfigPage {
    u8 pad_00[0x3638];
    u16 unk_3638;
    u16 unk_363A;
    u16 unk_363C;
} Obj12ConfigPage;


struct ConfigWord { s32 value; };


extern u8 D_800DD7E0[];

/* Create and initialize the type 0x12 object if it is not already active. */
void create_viewport_transition_object(void) {
    ObjectNodeHeader *object;

    if (!(dungeon_floor_flags & 0x80)) {
        object = allocate_flagged_object_node(0x12);
        if (object != NULL) {
            object->update_callback = update_viewport_transition;
            register_node(object, build_transformed_sprite_quads);
            {
                u16 field_value;
                u16 field_value_2;
                u16 field_z;
                InactiveTypeTwelveObjectBody *object_state;
                ObjectPosition *child;
                s32 color;
                Obj12ConfigPage *config_value;
                s32 config_word;
                s32 config_word2;
                s32 flags;
                SpriteFrameState *render_data;

                child = object->position;
                child->z.w.i = -1;
                render_data = object->sprite;
                render_data->flags = 0xC;
                render_data->source = D_800DD7E0;
                config_value = (void *) 0x80010000;
                render_data->scale_y = 0;
                render_data->scale_x = 0;
                field_value_2 = config_value->unk_363C;
                object_state = NODE_BODY(object);
                object_state->target_scale = field_value_2;
                field_value = config_value->unk_3638;
                child->x.w.i = field_value;
                object_state->target_center_x = field_value;
                field_z = config_value->unk_363A;
                child->y.w.i = field_z;
                object_state->target_center_y = field_z;
                object_state->state = 0x10;
                object_state->frames_left = 8;
                color = 0x808080;
                render_data->color.word = color;
                config_word = ((struct ConfigWord *)0x80013630)->value;
                render_data->angle_y = 0;
                render_data->angle_x = 0;
                render_data->angle_y = 0;
                render_data->angle_x = 0;
                *(s32 *)&object_state->view_x = config_word;
                *(s32 *)&object_state->target_x = config_word;
                config_word2 = ((struct ConfigWord *)0x80013634)->value;
                *(s32 *)&object_state->view_width = config_word2;
                *(s32 *)&object_state->target_width = config_word2;
                flags = dungeon_floor_flags;
                object_state->frames_left = 4;
                object_state->unk_18 = 0;
                dungeon_floor_flags = flags | 0x80;
            }
        }
    }
}

/* MECHANISM: Direct D_800E296C RMW holds its page in s1, producing the 0x20 frame and retail save order.
   Post-call caller-register roles hold the 0x8001 page in v0, child/secondary/subobject in a2/v1/a0,
   and color in a3; reusing dead v0/v1 for the two globals, literal 4, and flag reload removes the tail nop. */
