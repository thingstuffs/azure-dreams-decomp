#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/slus_callbacks.h"
#include "shared/dungeon_moving_views.h"

typedef struct S_80024130_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0x18];
    s32 unk_2C;
} S_80024130_0;

   /* arg1 in create_randomized_effect_object */

extern s32 func_8003DB94();
extern s32 register_node();
extern s32 rand();
extern u8 D_80024048[9];
extern u8 D_800DE8E8[9];

/* Creates an object with the given context and position and randomized rotation. */
s32 create_randomized_effect_object(s32 context, MovingPosition *position)
{
    s32 random_value;
    s32 rounded_value;
    SpriteFrameState *visual;
    S_80024130_0 *object;
    MovingPosition *object_pos;
    s32 pos_z;
    void *result;

    object = func_8003FC64(0x212);
    if (object != 0) {
        object->unk_10 = D_80024048;
        visual = object->unk_0C;
        object->unk_2C = context;
        visual->color.c.b = 0x80;
        visual->color.c.g = 0x80;
        visual->color.c.r = 0x80;
        func_8003DB94(visual, D_800DE8E8, 0);
        visual->scale_y = 0x1000;
        visual->scale_x = 0x1000;
        rounded_value = rand();
        random_value = rounded_value;
        if (random_value < 0) {
            rounded_value = random_value + 0xFFF;
        }
        visual->angle_z = (random_value % 4096);
        register_node(object, project_sprite_chain);
        object_pos = object->unk_08;
        object_pos->unk_02 = position->unk_02;
        object_pos->unk_06 = position->unk_06;
        pos_z = position->unk_0A;
        result = object;
        object_pos->unk_0A = pos_z;
        return (s32)result;
    } else {
        result = 0;
        return (s32)result;
    }
}
