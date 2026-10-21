#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/vector.h"

#ifndef NULL
#define NULL 0
#endif

extern s32 allocate_list_node();

typedef struct S_8009C390_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    s32 unk_10;
} S_8009C390_0;

typedef struct S_8009C390_1 {
    u8 pad_00[0x50];
    s32 unk_50;
    u8 pad_54[0x48];
    s32 unk_9C;
} S_8009C390_1;

   /* arg1 in create_town_effect_object */

/* Creates a type 0x116 object with an optional parent and position, and initializes its rendering. */
void *create_town_effect_object(s32 parent, IntVector3 *position, s32 object_value, s32 state_value) {
    S_8009C390_1 *state;
    IntVector3 *object_position;
    SpriteFrameState *render;
    void *object;

    if (parent != 0) {
        object = (void *)allocate_list_node(0x116, parent);
        state = object + 0x20;
    } else {
        object = allocate_flagged_object_node(0x116);
        state = object + 0x20;
    }
    if (object == NULL) {
        return NULL;
    }
    object_position = ((S_8009C390_0 *)object)->unk_08;
    render = ((S_8009C390_0 *)object)->unk_0C;
    ((S_8009C390_0 *)object)->unk_10 = object_value;
    state->unk_50 = state_value;
    if (parent != 0) {
        state->unk_9C = (s32)(parent + 0x20);
    }
    if (position != NULL) {
        object_position->x = position->x;
        object_position->y = position->y;
        object_position->z = position->z;
    }
    render->scale_y = 0x1000;
    render->scale_x = 0x1000;
    render->color.word = 0x808080;
    return object;
}
