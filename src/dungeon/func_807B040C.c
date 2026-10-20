#include "modules/dungeon_ovl_7ce800.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
extern int abs(int);

typedef struct S_807B040C_0 {
    u8 pad_00[0x8];
    s32 * unk_08;
    u8 * unk_0C;
} S_807B040C_0;   /* root in update_special_actor_transition */

typedef struct S_807B040C_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x68];
    s16 unk_88;
    u8 pad_8A[0xC];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
    u8 pad_9C[0xE];
    union { s16 s16; u8 u8; } unk_AA;   /* accessed as both */
    u8 pad_AC[0x2];
    union { s16 s16; u8 u8; } unk_AE;   /* accessed as both */
    u8 pad_B0[0x8];
    u8 unk_B8;
} S_807B040C_1;   /* entity in update_special_actor_transition */

typedef struct S_807B040C_6 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x5C];
    s16 unk_88;
} S_807B040C_6;   /* entity_aux in update_special_actor_transition */

typedef struct S_807B040C_7 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0xE];
    u16 unk_16;
} S_807B040C_7;   /* motion in update_special_actor_transition */

extern void cycle_map_cell_flags(s16 x, s16 y, u16 flags);
extern void get_offset_map_cell_value_and_flags(u8, u8, s16, u16 *);
extern void update_map_cell_flags_with_item_limit(u8, u8, s32);
extern void set_record_integer_tile_center(void *, u8, u8);
extern s32 check_left_tile_and_center_height(s32, s32, s16);

/* Move the entity to a passable tile near the room and update tile occupancy. */
s32 update_special_actor_transition(void) {
    DirectionOffsets offsets = dungeon_7ce800_directions;
    u16 collision_flags;
    u8 *root = (u8 *)D_800FBE1C;
    u8 *entity = root + 0x20;
    s32 *motion = ((S_807B040C_0 *)root)->unk_08;
    s32 entity_flags;
    s32 state = ((S_807B040C_1 *)entity)->unk_9B;
    u8 *target = ((S_807B040C_0 *)root)->unk_0C;
    u8 *entity_aux = entity;
    s32 direction;
    s32 dx;
    s32 dy;
    s32 distance_x;
    s32 world_x;
    s32 target_y;
    s32 delta_y;
    s32 move_ticks;
    s16 ground_height;
    s32 tile_flags;
    u8 tile_x;
    u8 tile_y;
    s16 *direction_offset;
    TileObject *room;
    EntityRec *collision;
    s32 distance_y;

    switch (state) {
    case 0:
        {
            u8 *room_page;
            TileObject *nearby_room;
            s32 target_coord;
            s32 room_distance_y;

            room_page = (u8 *)0x80080000;
            nearby_room = &D_80082E80;
            dx = nearby_room->tileX;
            target_coord = ((SpriteFrameState *)target)->unk_24;
            dx -= target_coord;
            dx = abs(dx);
            if (dx < 3) {
                room_distance_y = nearby_room->tileY;
                target_coord = ((SpriteFrameState *)target)->unk_25;
                room_distance_y -= target_coord;
                room_distance_y = abs(room_distance_y);
                if (room_distance_y < 3) {
                    s32 result;
                    s16 next_state;

                    result = 1;
                    ((S_807B040C_1 *)entity)->unk_9B = ((s16)(0x63));
                    next_state = 2;
                    ((S_807B040C_1 *)entity)->unk_B8 = next_state;
                    return result;
                }
            }
        }

        ((S_807B040C_1 *)entity)->unk_9B++;
        direction = get_direction_toward_target_position(motion);
        direction += 4;
        if (direction >= 8) {
            direction -= 8;
        }
        room = &D_80082E80;
        collision = &D_80083780;

        while (1) {
            get_offset_map_cell_value_and_flags(room->tileX, room->tileY,
                          (s16)direction, &collision_flags);
            if (!(collision_flags & 0xB400)) {
                direction_offset = (s16 *)&offsets + direction * 2;
                ((S_807B040C_1 *)entity)->unk_AA.s16 = room->tileX + (u16)direction_offset[0];
                ((S_807B040C_1 *)entity)->unk_AE.s16 = room->tileY + (u16)direction_offset[1];
                if ((s16)check_left_tile_and_center_height(
                        ((((S_807B040C_1 *)entity)->unk_AA.s16 << 6) + 0x20) & 0xFFE0,
                        ((((S_807B040C_1 *)entity)->unk_AE.s16 << 6) + 0x20) & 0xFFE0,
                        collision->z.w.i) == 0) {
                    break;
                }
            }
            direction++;
            if (direction >= 8) {
                direction = 0;
            }
        }

        {
            s32 y_is_farther;

            distance_x = ((S_807B040C_1 *)entity)->unk_AA.s16;
            delta_y = ((SpriteFrameState *)target)->unk_24;
            target_y = ((SpriteFrameState *)target)->unk_25;
            distance_x -= delta_y;
            delta_y = ((S_807B040C_1 *)entity)->unk_AE.s16;
            if (distance_x < 0) {
                distance_x = -distance_x;
            }
            delta_y -= target_y;
            move_ticks = delta_y;
            distance_y = abs(move_ticks);
            y_is_farther = distance_x < distance_y;
            if (y_is_farther) {
                move_ticks = distance_y * 4;
            } else {
                move_ticks = distance_x * 4;
            }
            ((S_807B040C_1 *)entity)->unk_96.s = move_ticks;

            entity_flags = ((S_807B040C_6 *)entity_aux)->unk_1C;
            tile_x = ((SpriteFrameState *)target)->unk_24;
            tile_y = ((SpriteFrameState *)target)->unk_25;
            tile_flags = 0x3000;
            if (entity_flags & 0x2000) {
                tile_flags = 0x300;
            }
            update_map_cell_flags_with_item_limit(tile_x, tile_y, tile_flags);
        }
        /* fall through */
    case 1:
    move_entity:
        {
            s32 aligned_x;

            world_x = ((S_807B040C_1 *)entity)->unk_AA.s16;
            world_x <<= 6;
            world_x += 0x20;
            move_ticks = ((S_807B040C_1 *)entity)->unk_AE.s16 << 6;
            distance_y = move_ticks + 0x20;
            aligned_x = world_x & 0xFFE0;
            ground_height = (s16)sample_terrain_surface_height(aligned_x, distance_y & 0xFFE0, -0x400);
        }
        world_x = ((S_807B040C_1 *)entity)->unk_AA.s16;
        world_x <<= 6;
        world_x += 0x20;
        motion[3] = ((world_x << 16) - motion[0]) /
                    ((S_807B040C_1 *)entity)->unk_96.s;
        motion[4] = ((((((S_807B040C_1 *)entity)->unk_AE.s16 << 6) + 0x20) << 16) -
                     motion[1]) /
                    ((S_807B040C_1 *)entity)->unk_96.s;
        motion[5] = (((s16)ground_height - ((S_807B040C_6 *)entity_aux)->unk_88) << 16) /
                    ((S_807B040C_1 *)entity)->unk_96.s;
        ((S_807B040C_6 *)entity_aux)->unk_88 =
            (u16)((S_807B040C_6 *)entity_aux)->unk_88 + ((S_807B040C_7 *)motion)->unk_16;

        dx = motion[3];
        motion[5] = 0;
        if (dx == 0) {
            direction = 6;
            if (motion[4] > 0) {
                direction = 2;
            }
        } else {
            dy = motion[4];
            if (dy == 0) {
                direction = (dx < 1) << 2;
            } else {
                if (dx > 0) {
                    direction = 7;
                    if (dy > 0) {
                        direction = 1;
                    }
                } else {
                    direction = 5;
                    if (dy > 0) {
                        direction = 3;
                    }
                }
            }
        }
        ((S_807B040C_6 *)entity_aux)->unk_2A = direction << 9;
        ((S_807B040C_1 *)entity)->unk_96.u--;
        if ((s16)((S_807B040C_1 *)entity)->unk_96.u > 0) {
            return 0;
        }
        ((S_807B040C_1 *)entity)->unk_9B++;
        break;

    case 2:
        ((SpriteFrameState *)target)->unk_24 = ((S_807B040C_1 *)entity)->unk_AA.u8;
        ((SpriteFrameState *)target)->unk_25 = ((S_807B040C_1 *)entity)->unk_AE.u8;
        motion[0] = ((((SpriteFrameState *)target)->unk_24 << 6) + 0x20) << 16;
        motion[1] = ((((SpriteFrameState *)target)->unk_25 << 6) + 0x20) << 16;
        motion[5] = 0;
        motion[4] = 0;
        motion[3] = 0;
        ((S_807B040C_1 *)entity)->unk_88 = (s16)sample_terrain_surface_height(((S_807B040C_7 *)motion)->unk_02,
                                                 ((S_807B040C_7 *)motion)->unk_06, -0x400);
        set_record_integer_tile_center(motion, ((SpriteFrameState *)target)->unk_24, ((SpriteFrameState *)target)->unk_25);
        {

            entity_flags = ((S_807B040C_1 *)entity)->unk_1C;
            tile_x = ((SpriteFrameState *)target)->unk_24;
            tile_y = ((SpriteFrameState *)target)->unk_25;
            tile_flags = 0x3000;
            if (entity_flags & 0x2000) {
                tile_flags = 0x300;
            }
        }
        cycle_map_cell_flags(tile_x, tile_y, tile_flags);
        ((S_807B040C_1 *)entity)->unk_B8 = state;
        return 1;
    default:
        break;
    }
    return 0;
}
