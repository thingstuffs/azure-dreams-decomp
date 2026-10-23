#include "common.h"
#include "shared/entity.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "shared/dungeon_moving_views.h"

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

extern u8 D_80171704[];
extern u8 D_80171CC0[];
extern u8 D_80171D90[];
extern u8 D_80171E60[];

extern void *allocate_list_node(s32, void *);
extern void register_node(void *, void *);
extern s32 rand(void);

/* Creates an object at a randomized offset from its parent and initializes its mode and state. */
/* Creates a parent-linked trail particle with mode-specific callbacks and jitter ranges, copying the
 * supplied state values. */
void spawn_jittered_trail_particle(S_80171F30_1 *parent, s32 state_value, s16 tail_value_in, s16 mode_in)
{
    ObjectNodeHeader *object;
    SpriteFrameState *header;
    void *call_object;
    void *init_data;
    void *tail;
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
            resource_addr = (s32)D_80171D90;
        } else {
            resource_addr = (s32)D_80171E60;
        }
    }
    object->unk_10 = (void *)resource_addr;
    ((MovingPosition *)(object->position))->unk_02 =
        ((MovingPosition *)(parent->unk_08))->unk_02;
    ((MovingPosition *)(object->position))->unk_06 =
        ((MovingPosition *)(parent->unk_08))->unk_06;
    ((MovingPosition *)(object->position))->unk_0A =
        ((MovingPosition *)(parent->unk_08))->unk_0A;

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
    init_data = D_80171704;
    header = object->sprite;
    tail = (u8 *)object + 0x20;
    header->unk_06 = 0;
    ((S_80171F30_4 *)tail)->unk_32 = tail_value;
    ((S_80171F30_4 *)tail)->unk_34 = tail_value;
    register_node(call_object, init_data);
    ((S_80171F30_0 *)object)->unk_20 = state_value;
    ((S_80171F30_4 *)tail)->unk_08 = state_value;
}
