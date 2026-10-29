#include "common.h"
#include "dungeon/monster/ghosh.h"
#include "shared/entity.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "shared/dungeon_moving_views.h"
#include "engine/node.h"
#include "engine/node/allocation.h"
#include "sdk/libc.h"

typedef struct S_80171F30_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_80171F30_0;   /* object in spawn_jittered_trail_particle */

typedef struct S_80171F30_1 {
    u8 pad_00[0x8];
    void * unk_08;
} S_80171F30_1;   /* arg0 in spawn_jittered_trail_particle */


typedef struct S_80171F30_4 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x26];
    s16 unk_32;
    s16 unk_34;
} S_80171F30_4;   /* tail in spawn_jittered_trail_particle */

   /* ((S_80171F30_0 *)object)->unk_08 in spawn_jittered_trail_particle */

   /* ((S_80171F30_1 *)arg0)->unk_08 in spawn_jittered_trail_particle */

extern u8 ghosh_object_callback_2[];
extern u8 D_80171CC0[];
extern u8 D_80171E60[];

/* Creates an object at a randomized offset from its parent and initializes its mode and state. */
/* Creates a parent-linked trail particle with mode-specific callbacks and jitter ranges, copying the
 * supplied state values. */
void spawn_jittered_trail_particle(S_80171F30_1 *parent, s32 state_value, s16 tail_value_in, s16 mode_in)
{
    ObjectNodeHeader *object;
    SpriteFrameState *header;
    void *call_object;
    void *init_data;
    S_80171F30_4 *tail;
    register s32 resource_addr;
    s32 mode_index;
    register s16 tail_value;
    s16 mode_value;
    s32 alloc_kind;
    void *source;
    ObjectPosition *position;
    s32 jitter;
    s32 coord;

    alloc_kind = 0x211;
    source = parent;
    mode_value = mode_in;
    tail_value = tail_value_in;
    object = allocate_list_node(alloc_kind, source);
    if (object == 0) {
        return;
    }

    resource_addr = ((s32)mode_value) << 16;
    mode_index = resource_addr >> 16;
    if (mode_index == 0) {
        resource_addr = (s32)&D_80171CC0;
    } else {
        resource_addr = 1;
        if (mode_index == resource_addr) {
            resource_addr = (s32)advance_ghosh_trail_fade;
        } else {
            resource_addr = (s32)D_80171E60;
        }
    }
    object->update_callback = (void *)resource_addr;
    object->position->x.w.i =
        ((MovingPosition *)(parent->unk_08))->x;
    object->position->y.w.i =
        ((MovingPosition *)(parent->unk_08))->y;
    object->position->z.w.i =
        ((MovingPosition *)(parent->unk_08))->z;

    if ((mode_value << 16) == 0) {
        jitter = rand();
        position = object->position;
        coord = ((u16) position->x.w.i);
        jitter &= 7;
        coord -= 4;
        coord += jitter;
        position->x.w.i = coord;
        jitter = rand();
        position = object->position;
        coord = ((u16) position->y.w.i);
        jitter &= 7;
        coord -= 4;
        coord += jitter;
        position->y.w.i = coord;
    } else {
        jitter = rand();
        position = object->position;
        coord = ((u16) position->x.w.i);
        jitter &= 0xF;
        coord -= 0xC;
        coord += jitter;
        position->x.w.i = coord;
        jitter = rand();
        position = object->position;
        coord = ((u16) position->y.w.i);
        jitter &= 0xF;
        coord -= 0xC;
        coord += jitter;
        position->y.w.i = coord;
    }

    call_object = object;
    init_data = ghosh_object_callback_2;
    header = object->sprite;
    tail = (S_80171F30_4 *)((u8 *)object + 0x20);
    header->depth_bias = 0;
    tail->unk_32 = tail_value;
    tail->unk_34 = tail_value;
    register_node(call_object, init_data);
    ((S_80171F30_0 *)object)->unk_20 = state_value;
    tail->unk_08 = state_value;
}
