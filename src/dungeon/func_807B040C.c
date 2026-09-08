#include "common.h"

typedef struct S_807B040C_0 {
    u8 pad_00[0x8];
    s32 * unk_08;
    u8 * unk_0C;
} S_807B040C_0;   /* root in func_807B040C */

typedef struct S_807B040C_1 {
    u8 pad_00[0x1C];
    volatile s32 unk_1C;
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
} S_807B040C_1;   /* entity in func_807B040C */

typedef struct S_807B040C_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_807B040C_2;   /* state_room in func_807B040C */

typedef struct S_807B040C_3 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_807B040C_3;   /* target in func_807B040C */

typedef struct S_807B040C_4 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_807B040C_4;   /* room in func_807B040C */

typedef struct S_807B040C_5 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_807B040C_5;   /* collision in func_807B040C */

typedef struct S_807B040C_6 {
    u8 pad_00[0x1C];
    volatile s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x5C];
    s16 unk_88;
} S_807B040C_6;   /* entity_aux in func_807B040C */

typedef struct S_807B040C_7 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0xE];
    u16 unk_16;
} S_807B040C_7;   /* motion in func_807B040C */



typedef struct DirectionOffsets {
    u16 x0;
    u16 y0;
    u16 x1;
    u16 y1;
    u16 x2;
    u16 y2;
    u16 x3;
    u16 y3;
    u16 x4;
    u16 y4;
    u16 x5;
    u16 y5;
    u16 x6;
    u16 y6;
    u16 x7;
    u16 y7;
} __attribute__((packed)) DirectionOffsets;

extern u8 D_80082E80[];
extern u8 D_80083780[];
extern u8 D_800F6050[sizeof(DirectionOffsets)];
extern s32 D_800FBE1C;

extern void func_8009A21C(u8, u8, s32);
extern void func_8009A350(u8, u8, s16, u16 *);
extern void func_8009A3D0(u8, u8, s32);
extern void func_800A2B04(void *, u8, u8);
extern s32 func_800A45D8(s32, s32, s16);
extern s16 func_800BCB04(s32, s32, s32);
extern s32 func_800F6D28(void *);
extern void func_800F7DA8(void) __attribute__((noreturn));
extern void func_800F7FD0(void) __attribute__((noreturn));
extern void func_800F80A4(void) __attribute__((noreturn));
extern void func_800F80A8(void) __attribute__((noreturn));
extern void func_800F80A8_returning(void) __asm__("func_800F80A8");

/* Move the entity to a passable tile near the room and update tile occupancy. */
s32 func_807B040C(void) {
    DirectionOffsets offsets = *(DirectionOffsets *)D_800F6050;
    u16 collision_flags;
    u8 *root = (u8 *)D_800FBE1C;
    u8 *entity = root + 0x20;
    s32 *motion = ((S_807B040C_0 *)root)->unk_08;
    s32 state = ((S_807B040C_1 *)entity)->unk_9B;
    u8 *target = ((S_807B040C_0 *)root)->unk_0C;
    u8 *entity_aux = entity;
    s32 direction;
    s32 dx;
    s32 dy;
    s32 distance_x;
    s32 target_y;
    s32 delta_y;
    s32 move_ticks;
    s16 ground_height;
    s32 tile_flags;
    u8 tile_x;
    u8 tile_y;
    s16 *direction_offset;
    u8 *room;
    u8 *collision;

    if (state == 1) {
        goto move_entity;
    }
    if (state < 2) {
        if (state == 0) {
            goto begin_move;
        }
        {
            s32 result;

            result = 0;
            ASM_KEEP(result);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
            func_800F80A8();
            return result;
        }
    }
    if (state == 2) {
        goto finish_move;
    }
    {
        s32 result;

        result = 0;
        ASM_KEEP(result);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
        func_800F80A8();
        return result;
    }

begin_move:
    {
        u8 *room_page;
        u8 *nearby_room;
        s32 target_coord;
        s32 room_distance_y;

#ifdef NON_MATCHING
        room_page = D_80082E80 - 0x2E80;
#else
        room_page = (u8 *)0x80080000;
#endif
        ASM_KEEP_NV(room_page);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
        nearby_room = room_page + 0x2E80;
        dx = ((S_807B040C_2 *)nearby_room)->unk_24;
        target_coord = ((S_807B040C_3 *)target)->unk_24;
        dx -= target_coord;
        if (dx < 0) {
            dx = -dx;
        }
        if (dx < 3) {
            room_distance_y = ((S_807B040C_2 *)nearby_room)->unk_25;
            target_coord = ((S_807B040C_3 *)target)->unk_25;
            room_distance_y -= target_coord;
            if (room_distance_y < 0) {
                room_distance_y = -room_distance_y;
            }
            if (room_distance_y < 3) {
                register s32 result ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                register s32 next_state ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

                result = 1;
                ASM_KEEP(result);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
                next_state = 0x63;
                ((S_807B040C_1 *)entity)->unk_9B = next_state;
                next_state = 2;
                ((S_807B040C_1 *)entity)->unk_B8 = next_state;
                func_800F80A8();
                return result;
            }
        }
    }

    ((S_807B040C_1 *)entity)->unk_9B++;
    direction = func_800F6D28(motion);
    direction += 4;
    if (direction >= 8) {
        direction -= 8;
    }
    room = D_80082E80;
    collision = D_80083780;

find_direction:
    func_8009A350(((S_807B040C_4 *)room)->unk_24, ((S_807B040C_4 *)room)->unk_25,
                  (s16)direction, &collision_flags);
    if (collision_flags & 0xB400) {
        goto next_direction;
    }

    direction_offset = (s16 *)&offsets + direction * 2;
    ((S_807B040C_1 *)entity)->unk_AA.s16 = ((S_807B040C_4 *)room)->unk_24 + (u16)direction_offset[0];
    ((S_807B040C_1 *)entity)->unk_AE.s16 = ((S_807B040C_4 *)room)->unk_25 + (u16)direction_offset[1];
    if ((s16)func_800A45D8(
            ((((S_807B040C_1 *)entity)->unk_AA.s16 << 6) + 0x20) & 0xFFE0,
            ((((S_807B040C_1 *)entity)->unk_AE.s16 << 6) + 0x20) & 0xFFE0,
            ((S_807B040C_5 *)collision)->unk_0A) != 0) {
next_direction:
        direction++;
        if (direction < 8) {
            goto find_direction;
        }
        direction = 0;
        ASM_TAILSLOT_PIN(direction);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
        func_800F7DA8();
        return direction;
    }

    {
        s32 target_x;
        register s32 distance_y ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        s32 y_is_farther;
        s32 entity_flags;

        distance_x = ((S_807B040C_1 *)entity)->unk_AA.s16;
        ASM_KEEP_NV(distance_x);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        target_x = ((S_807B040C_3 *)target)->unk_24;
        ASM_KEEP_NV(target_x);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        target_y = ((S_807B040C_3 *)target)->unk_25;
        ASM_KEEP_NV(target_y);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
        distance_x -= target_x;
        delta_y = ((S_807B040C_1 *)entity)->unk_AE.s16;
        if (distance_x < 0) {
            distance_x = -distance_x;
        }
        delta_y -= target_y;
        distance_y = delta_y;
        if (delta_y < 0) {
            distance_y = -distance_y;
        }
        y_is_farther = distance_x < distance_y;
        if (y_is_farther) {
            move_ticks = distance_y * 4;
        } else {
            move_ticks = distance_x * 4;
        }
        ((S_807B040C_1 *)entity)->unk_96.s = move_ticks;

        entity_flags = ((S_807B040C_6 *)entity_aux)->unk_1C;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        tile_x = ((S_807B040C_3 *)target)->unk_24;
        tile_y = ((S_807B040C_3 *)target)->unk_25;
        tile_flags = 0x3000;
        if (entity_flags & 0x2000) {
            tile_flags = 0x300;
        }
        func_8009A3D0(tile_x, tile_y, tile_flags);
    }
    goto move_entity;

move_entity:
    {
        register s32 world_x ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        register s32 tile_origin_y ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        register s32 world_y ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        s32 aligned_x;

        world_x = ((S_807B040C_1 *)entity)->unk_AA.s16 << 6;
        ASM_KEEP_NV(world_x);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        world_x += 0x20;
        tile_origin_y = ((S_807B040C_1 *)entity)->unk_AE.s16 << 6;
        ASM_KEEP_NV(tile_origin_y);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        world_y = tile_origin_y + 0x20;
        aligned_x = world_x & 0xFFE0;
        ground_height = func_800BCB04(aligned_x, world_y & 0xFFE0, -0x400);
    }
    motion[3] = ((((((S_807B040C_1 *)entity)->unk_AA.s16 << 6) + 0x20) << 16) -
                 motion[0]) /
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
            ASM_TAILSLOT_PIN(direction);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
            func_800F7FD0();
            return direction;
        }
        goto set_direction;
    }
    dy = motion[4];
    if (dy == 0) {
        direction = (dx < 1) << 2;
        ASM_TAILSLOT_PIN(direction);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
        func_800F7FD0();
        return direction;
    }
    if (dx > 0) {
        direction = 7;
        if (dy > 0) {
            direction = 1;
            ASM_TAILSLOT_PIN(direction);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
            func_800F7FD0();
            return direction;
        }
        goto set_direction;
    }
    direction = 5;
    if (dy > 0) {
        direction = 3;
    }

set_direction:
    ((S_807B040C_6 *)entity_aux)->unk_2A = direction << 9;
    ((S_807B040C_1 *)entity)->unk_96.u--;
    if ((s16)((S_807B040C_1 *)entity)->unk_96.u > 0) {
        return 0;
    }
    ((S_807B040C_1 *)entity)->unk_9B++;
    func_800F80A4();
    return 0;

finish_move:
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ((S_807B040C_3 *)target)->unk_24 = ((S_807B040C_1 *)entity)->unk_AA.u8;
    ((S_807B040C_3 *)target)->unk_25 = ((S_807B040C_1 *)entity)->unk_AE.u8;
    motion[0] = ((((S_807B040C_3 *)target)->unk_24 << 6) + 0x20) << 16;
    motion[1] = ((((S_807B040C_3 *)target)->unk_25 << 6) + 0x20) << 16;
    motion[5] = 0;
    motion[4] = 0;
    motion[3] = 0;
    ((S_807B040C_1 *)entity)->unk_88 = func_800BCB04(((S_807B040C_7 *)motion)->unk_02,
                                             ((S_807B040C_7 *)motion)->unk_06, -0x400);
    func_800A2B04(motion, ((S_807B040C_3 *)target)->unk_24, ((S_807B040C_3 *)target)->unk_25);
    {
        s32 entity_flags;

        entity_flags = ((S_807B040C_1 *)entity)->unk_1C;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        tile_x = ((S_807B040C_3 *)target)->unk_24;
        tile_y = ((S_807B040C_3 *)target)->unk_25;
        tile_flags = 0x3000;
        if (entity_flags & 0x2000) {
            tile_flags = 0x300;
        }
    }
    func_8009A21C(tile_x, tile_y, tile_flags);
    ((S_807B040C_1 *)entity)->unk_B8 = state;
    {
        register s32 result ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

        result = 1;
        ASM_TAILSLOT_PIN(result);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        func_800F80A8_returning();
        return 0;
    }
}
