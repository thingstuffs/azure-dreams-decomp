#include "common.h"
#include "town/map/animation.h"
#include "m2c_compat.h"
#include "shared/object_node.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"
#include "shared/object_links.h"
#include "engine/runtime.h"
#include "sdk/libc.h"
#include "town/map.h"

#ifndef NULL
#define NULL 0
#endif



struct ObjectNodeHeader; void * allocate_list_node(s32, struct ObjectNodeHeader * *);
void register_node(void *, void *);
extern void D_800BFD14();
extern s32 D_800BFFF4(u8 *node);

/* Spawn objects at randomized coordinates and mark completion when the countdown expires. */
void spawn_randomized_timed_objects(TownMapSpawnState *source)
{
    s16 fixed_coord = 0;
    s16 state;
    s32 coord_term;
    s32 random_value;
    s32 spawn_count;
    s32 count_bits;
    s32 random_coord;
    s32 base_coord;
    u16 next_value;
    GameWork *town;
    u8 *kind;
    TownMapFallingObject *coords;
    void *new_object;
    ObjectNodeHeader *object;
    void *callback;

    object = source;
    source = object;
    count_bits = source->count;
    count_bits <<= 0x10;
    spawn_count = count_bits >> 0x11;
    town = &g_game_work;
    if (spawn_count >= 0) {
        kind = (u8 *)&D_800BFD14;
        do {
            new_object = allocate_list_node((s32)((void *)0x202), &scene_object_list_anchor.next);
            if (new_object != NULL) {
                object = new_object;
                callback = &D_800BFFF4;
                coords = ((void *)object) + 0x20;
                object->update_callback = (s32 *)kind;
                register_node(object, callback);
                random_value = rand();
                coord_term = town->view.camera_position.parts.camera_position_x;
                random_coord = coord_term + random_value % 1024 - 512;
                coords->unk_0C.s = random_coord;
                coords->motion.x.w.i = random_coord;
                coord_term = rand()
                % (s16)source->span_y;
                base_coord = source->base_y;
                fixed_coord = -0x180;
                coords->unk_10.s = fixed_coord;
                coords->motion.z.w.i = fixed_coord;
                count_bits = base_coord;
                count_bits += coord_term;
                coords->unk_0E = count_bits;
                coords->motion.y.w.i = count_bits;
            }
            spawn_count -= 1;
            object = (void *)0x202;
        } while (spawn_count >= 0);
    }
    state = source->state.s;
    switch (state) {
    case 0:
        if (test_resident_bit(0xA1) == 0) {
            return;
        }
        next_value = source->state.u + 1;
        source->state.u = next_value;
        return;
    case 1:
    next_value = source->count - 1;
    source->count = next_value;
    if ((next_value << 0x10) <= 0) {
        (*(u16 *)((u8 *)source + -2)) =
            (u16)(((ObjectStatusPrefix16 *)source)[-1].flags | NODE_REMOVE);
        object_flag_block.flags = object_flag_block.flags | OBJECT_REMOVE_PENDING;
    }

    return;
    default:
        return;
    }
}
