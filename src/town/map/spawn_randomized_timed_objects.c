#include "common.h"
#include "m2c_compat.h"
#include "shared/object_node.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"
#include "shared/object_links.h"

#ifndef NULL
#define NULL 0
#endif




typedef struct S_800BFB8C_0 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
    union { s16 s; u16 u; } unk_0C;   /* accessed as both */
    u16 unk_0E;
} S_800BFB8C_0;

typedef struct S_800BFB8C_1 {
    u8 pad_00[0x10];
    s32 * unk_10;
} S_800BFB8C_1;

typedef struct S_800BFB8C_2 {
    u8 pad_00[0xBC];
    s16 unk_BC;
} S_800BFB8C_2;   /* town in spawn_randomized_timed_objects */

typedef struct S_800BFB8C_3 {
    u8 pad_00[0xC];
    s16 unk_0C;
    s16 unk_0E;
    s16 unk_10;
    u8 pad_12[0xC];
    s16 unk_1E;
    u8 pad_20[0x2];
    s16 unk_22;
    u8 pad_24[0x2];
    s16 unk_26;
} S_800BFB8C_3;


s32 test_resident_bit();
struct ObjectNodeHeader; void * allocate_list_node(s32, struct ObjectNodeHeader * *);
void register_node(void *, void *);
s32 rand(void);
extern M2C_UNK D_800BFD14;
extern M2C_UNK D_800BFFF4;

/* Spawn objects at randomized coordinates and mark completion when the countdown expires. */
void spawn_randomized_timed_objects(void *source)
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
    void *coords;
    void *new_object;
    void *object;
    void *callback;

    object = source;
    source = object;
    count_bits = ((S_800BFB8C_0 *)source)->unk_0E;
    count_bits <<= 0x10;
    spawn_count = count_bits >> 0x11;
    town = &g_game_work;
    if (spawn_count >= 0) {
        kind = (u8 *)&D_800BFD14;
        do {
            new_object = allocate_list_node((s32)((void *)0x202), (struct ObjectNodeHeader * *)(((s32 *)&scene_object_list_anchor.next)));
            if (new_object != NULL) {
                object = new_object;
                callback = &D_800BFFF4;
                coords = object + 0x20;
                ((S_800BFB8C_1 *)object)->unk_10 = (s32 *)kind;
                register_node(object, callback);
                random_value = rand();
                coord_term = town->view.camera_position.parts.camera_position_x;
                random_coord = coord_term + random_value % 1024 - 512;
                ((S_800BFB8C_3 *)coords)->unk_0C = random_coord;
                ((S_800BFB8C_3 *)coords)->unk_1E = random_coord;
                coord_term = rand()
                % (s16)((S_800BFB8C_0 *)source)->unk_0A;
                base_coord = ((S_800BFB8C_0 *)source)->unk_08;
                fixed_coord = -0x180;
                ((S_800BFB8C_3 *)coords)->unk_10 = fixed_coord;
                ((S_800BFB8C_3 *)coords)->unk_26 = fixed_coord;
                count_bits = base_coord;
                count_bits += coord_term;
                ((S_800BFB8C_3 *)coords)->unk_0E = count_bits;
                ((S_800BFB8C_3 *)coords)->unk_22 = count_bits;
            }
            spawn_count -= 1;
            object = (void *)0x202;
        } while (spawn_count >= 0);
    }
    state = ((S_800BFB8C_0 *)source)->unk_0C.s;
    switch (state) {
    case 0:
        if (test_resident_bit(0xA1) == 0) {
            return;
        }
        next_value = ((S_800BFB8C_0 *)source)->unk_0C.u + 1;
        ((S_800BFB8C_0 *)source)->unk_0C.u = next_value;
        return;
    case 1:
    next_value = ((S_800BFB8C_0 *)source)->unk_0E - 1;
    ((S_800BFB8C_0 *)source)->unk_0E = next_value;
    if ((next_value << 0x10) <= 0) {
        (*(u16 *)((u8 *)source + -2)) =
            (u16)(((ObjectStatusPrefix16 *)source)[-1].unk_00 | NODE_REMOVE);
        object_flag_block.flags = object_flag_block.flags | OBJECT_REMOVE_PENDING;
    }

    return;
    default:
        return;
    }
}
