#include "engine/scene.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/object_links.h"
#include "shared/record_ptrs.h"
#include "shared/object_flags.h"
#include "shared/entity.h"
#include "sdk/libgte.h"
#include "dungeon/player/item.h"

   /* the 0x2 bytes before arg0 in update_held_item_attachment, addressed as arg0[-1] */

typedef struct S_8008D470_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    void * unk_90;
    u8 pad_94[0x8];
    s32 unk_9C;
    u8 pad_A0[0x2];
    union { s16 s; u16 u; } unk_A2;   /* accessed as both */
    union { u16 s; s16 u; } unk_A4;   /* accessed as both */
    u8 pad_A6[0x2];
    union { u16 s; s16 u; } unk_A8;   /* accessed as both */
    s16 unk_AA;
    s16 unk_AC;
    s16 unk_AE;
    u8 pad_B0[0x4];
    union { s16 s; u16 u; } unk_B4;   /* accessed as both */
} S_8008D470_0;   /* arg0 in update_held_item_attachment */

typedef struct S_8008D470_1 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x10];
    u32 unk_1C;
    u8 pad_20[0x104];
    void * unk_124;
} S_8008D470_1;   /* target in update_held_item_attachment */

typedef struct S_8008D470_3 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0xD];
    s16 unk_1C;
} S_8008D470_3;   /* arg2 in update_held_item_attachment */

typedef struct S_8008D470_4 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
} S_8008D470_4;   /* arg1 in update_held_item_attachment */

typedef struct S_8008D470_5 {
    u8 pad_00[0x1C];
    u32 unk_1C;
    u8 pad_20[0x7C];
    void * unk_9C;
} S_8008D470_5;   /* entity in update_held_item_attachment */

typedef struct S_8008D470_6 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
} S_8008D470_6;   /* ((S_8008D470_0 *)arg0)->unk_8C in update_held_item_attachment */

   /* ((S_8008D470_1 *)target)->unk_124 in update_held_item_attachment */

extern u8 held_item_record[];

extern s32 create_indexed_floor_object();

/* Move the effect toward its target, pulse its brightness, and handle expiration. */
void update_held_item_attachment(void *effect, S_8008D470_4 *position, S_8008D470_3 *visual) {
    GteShortVector offsets;
    s16 state;
    s32 expiry_mode;
    s16 brightness;
    s32 current_x;
    s32 current_y;
    s32 current_z;
    register s16 update_result;
    s32 spawn_handle;
    register s32 position_updated;
    u16 steps_left;
    u8 intensity;
    S_8008D470_1 *target;
    SpriteFrameState *source_sprite;
    S_8008D470_5 *entity;

    state = ((S_8008D470_0 *)effect)->unk_A2.s;
    position_updated = 0;
    switch (state) {
    case 0:
        ((S_8008D470_0 *)effect)->unk_A4.s = 6;
        ((S_8008D470_0 *)effect)->unk_A2.s = ((S_8008D470_0 *)effect)->unk_A2.u + 1;
    case 1:
        source_sprite = ((S_8008D470_0 *)effect)->unk_90;
        if (resolve_record_orientation_or_fallback(source_sprite->source, source_sprite, &offsets, 0) != 0 &&((PlayerRecord *)dungeon_actor_ring_anchor)->unk_124 != 0) {
            visual->unk_1C = 0x1000;
            steps_left = ((S_8008D470_0 *)effect)->unk_A4.s - 1;
            ((S_8008D470_0 *)effect)->unk_A4.s = steps_left;
            if ((s16)steps_left > 0) {
                current_x = position->unk_00.at00.v;
                position->unk_00.at00.v = current_x +
                    (((S_8008D470_6 *)(((S_8008D470_0 *)effect)->unk_8C))->unk_00.at00.v +
                     (offsets.vx << 16) - current_x) / (s16)steps_left;

                current_y = position->unk_04.at00.v;
                position->unk_04.at00.v = current_y +
                    (((S_8008D470_6 *)(((S_8008D470_0 *)effect)->unk_8C))->unk_04.at00.v +
                     (offsets.vy << 16) - current_y) / ((S_8008D470_0 *)effect)->unk_A4.u;

                current_z = position->unk_08.at00.v;
                position->unk_08.at00.v = current_z +
                    (((S_8008D470_6 *)(((S_8008D470_0 *)effect)->unk_8C))->unk_08.at00.v +
                     (offsets.vz << 16) - (((S_8008D470_0 *)effect)->unk_A4.u << 21) - current_z) /
                    ((S_8008D470_0 *)effect)->unk_A4.u;
            } else {
                ((S_8008D470_0 *)effect)->unk_A4.s = 0;
                position->unk_00.at02.v = ((S_8008D470_6 *)(((S_8008D470_0 *)effect)->unk_8C))->unk_00.at02.v
                    + (u16)offsets.vx;
                position->unk_04.at02.v = ((S_8008D470_6 *)(((S_8008D470_0 *)effect)->unk_8C))->unk_04.at02.v
                    + (u16)offsets.vy;
                position->unk_08.at02.v = ((S_8008D470_6 *)(((S_8008D470_0 *)effect)->unk_8C))->unk_08.at02.v
                    + (u16)offsets.vz;
            }
            if (((S_8008D470_0 *)effect)->unk_AA == 0) {
                ((S_8008D470_0 *)effect)->unk_AA = 1;
            }
            position_updated = 1;
        } else {
            state = ((S_8008D470_0 *)effect)->unk_AA;
            if (state == 0) {
                visual->unk_1C = 0;
            } else if (state == 1) {
                if (((S_8008D470_0 *)effect)->unk_AE == 0) {
                    ((ObjectStatusPrefix16 *)effect)[-1].flags |= 0x8000;
                    object_flag_block.flags |= OBJECT_REMOVE_PENDING;
                }
            }
        }
    }

    if (((S_8008D470_0 *)effect)->unk_AE != 0) {
        brightness = (rsin(((S_8008D470_0 *)effect)->unk_B4.s << 8) >> 6) + 0x80;
        intensity = visual->unk_0C;
        intensity += (brightness - intensity) >> 2;
        visual->unk_0C = intensity;
        visual->unk_0D = intensity;
        visual->unk_0E = intensity;
    }

    ((S_8008D470_0 *)effect)->unk_B4.u++;
    ((S_8008D470_0 *)effect)->unk_A8.s--;
    if (((S_8008D470_0 *)effect)->unk_A8.u <= 0) {
        expiry_mode = ((S_8008D470_0 *)effect)->unk_AC;
        ((S_8008D470_0 *)effect)->unk_A8.s = 0;
        if (expiry_mode == 1) {
            spawn_handle = create_indexed_floor_object(effect, position, visual, ((s32)primary_actor_record), ((S_8008D470_0 *)effect)->unk_9C,
                -1);
            if (spawn_handle != 0) {
                entity = (void *)(spawn_handle + 0x20);
                target = dungeon_actor_ring_anchor;
                target->unk_124 = entity;
                entity->unk_9C = held_item_record;
                entity->unk_1C |= 0x80000;
                ((ActorRecord *)(target->unk_124))->target = target;
                target->unk_1C |= 0x100000;
                ((ObjectStatusPrefix16 *)effect)[-1].flags |= 0x8000;
                object_flag_block.flags |= OBJECT_REMOVE_PENDING;
            }
        } else if (expiry_mode == 2) {
            ((ObjectStatusPrefix16 *)effect)[-1].flags |= 0x8000;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        } else if (expiry_mode == 0) {
            update_result = position_updated;
            if (update_result == 0) {
                ((ObjectStatusPrefix16 *)effect)[-1].flags |= 0x8000;
                object_flag_block.flags |= OBJECT_REMOVE_PENDING;
            }
        }
    }
}
