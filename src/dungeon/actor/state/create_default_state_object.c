#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "dungeon/actor/state.h"
#include "engine/node.h"
#include "engine/scene.h"
struct Arg0_800AFBFC;
struct Arg2_800AFBFC;

typedef s32 M2C_UNK;

#ifndef NULL
#define NULL 0
#endif

typedef struct S_800B0544_4 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} S_800B0544_4;   /* obj in create_default_state_object */

extern s16 current_dungeon_floor;
extern void advance_object_phase_counters();
extern s32 process_circular_segments(struct Arg0_800AFBFC *shape, ObjectPosition *unused, struct Arg2_800AFBFC *segment);
extern s8 D_800DCF4C;
extern M2C_UNK D_800DEF90;

typedef struct S_800B0544_3 {
    u8 pad_00[0x2];
    s16 unk_02;
} S_800B0544_3;

/* Update the current state and create an object with default color, scale, and mode flags. */
void create_default_state_object(s16 new_state) {
    s8 *state;
    s32 mode;
    S_800B0544_3 *obj_state;
    SpriteFrameState *color;
    SpriteFrameState *scale;
    ObjectNodeHeader *obj;

    state = &D_800DCF4C;
    if (*state != new_state) {
        load_indexed_resource_package(new_state);
        *state = (s8)new_state;
    }
    obj = allocate_flagged_object_node(0x12);
    if (obj != NULL) {
        obj->update_callback = &advance_object_phase_counters;
        register_node(obj, &process_circular_segments);
        obj->sprite->source = &D_800DEF90;
        color = obj->sprite;
        color->color.c.b = 0xE0;
        color->color.c.g = 0xE0;
        color->color.c.r = 0xE0;
        scale = obj->sprite;
        scale->scale_y = 0x1000;
        scale->scale_x = 0x1000;
        obj->position->x.w.i = 0;
        obj->position->y.w.i = 0;
        obj->position->z.w.i = 0x4000;
        mode = *(s32 *)0x80012090;
        obj_state = NODE_BODY(obj);
        if (mode == 0) {
            if (current_dungeon_floor == 0x28) {
                obj_state->unk_02 = 1;
                return;
            }
        } else if (mode == 2) {
            obj_state->unk_02 = (s16)mode;
        }
    }
}
