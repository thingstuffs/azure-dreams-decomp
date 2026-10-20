#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "shared/game_work.h"
#include "m2c_compat.h"
#include "shared/object_payload.h"
#include "shared/vector.h"

typedef struct S_800BC574_7 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
} S_800BC574_7;

void *allocate_list_node();            /* extern */
s32 register_node();           /* extern */
s32 func_800644B8();                             /* extern */
s32 func_80064584();                             /* extern */
extern M2C_UNK D_800BC6CC;
extern M2C_UNK D_800F15E4;

typedef struct S_800BC574_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    s32 * unk_10;
} S_800BC574_0;

   /* copy_dst in create_directional_sprite_effect */

   /* held_arg0 in create_directional_sprite_effect */

typedef struct S_800BC574_5 {
    u8 pad_00[0xC];
    s32 unk_0C;
} S_800BC574_5;   /* (void *) tail_v0 in create_directional_sprite_effect */

/* Creates an effect at the supplied position with directional motion and initializes its sprite. */
s32 create_directional_sprite_effect(void *position, s16 angle) {
    s32 position_z;
    SpriteFrameState *sprite;
    S_800BC574_0 *effect;
    IntVector3 *source_pos = position;
    GameWork *world_state = &g_game_work;
    IntVector3 *data_ptr;
    s16 saved_angle;

    effect = allocate_list_node(0x312, ((s32 *)&D_80083498.next));
    if (effect != NULL) {
        saved_angle = angle;
        effect->unk_10 = &D_800BC6CC;
        register_node(effect, project_sprite_chain);
        sprite = effect->unk_0C;
        data_ptr = effect->unk_08;
        data_ptr->x = (s32) source_pos->x;
        data_ptr = effect->unk_08;
        data_ptr->y = (s32) source_pos->y;
        data_ptr = effect->unk_08;
        position_z = source_pos->z;
        {
            s16 angle_short;

            angle_short = (s16) saved_angle;
            data_ptr->z = position_z;
            ((S_800BC574_7 *)(((ObjectPayloadView *)effect)->unk_08))->unk_0C =
                (s32) (func_80064584(angle_short + world_state->view.camera_rotation.parts.viewAngle) * 0x30);
            ((S_800BC574_7 *)(((ObjectPayloadView *)effect)->unk_08))->unk_10 =
                (s32) (func_800644B8(angle_short + world_state->view.camera_rotation.parts.viewAngle) * 0x30);
        }
        {
            s32 init_value;
            s32 init_value_2;
            IntVector3 *sprite_table;
            s32 table_word;

            init_value_2 = 0x1000;
            sprite->scale_y = init_value_2;
            sprite->scale_x = init_value_2;
            init_value = (s32) effect->unk_08;
            init_value = ((S_800BC574_5 *)((void *) init_value))->unk_0C;
            if (init_value > 0) {
                sprite->flags = (u16) (sprite->flags | 1);
            }
            sprite_table = (IntVector3 *)&D_800F15E4;
            sprite->unk_00 = sprite_table;
            table_word = sprite_table->y;
            sprite->unk_04 = 0;
            sprite->unk_05 = 0;
            sprite->color.word = 0x808080;
            sprite->source = table_word;
        }
    }
    return 0;
}
