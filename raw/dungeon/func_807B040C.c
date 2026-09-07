#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

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

s32 func_807B040C(void) {
    DirectionOffsets offsets = *(DirectionOffsets *)D_800F6050;
    u16 collision_flags;
    u8 *root = (u8 *)D_800FBE1C;
    u8 *entity = root + 0x20;
    s32 *motion = FIELD(root, s32 *, 8);
    s32 state = FIELD(entity, u8, 0x9B);
    u8 *target = FIELD(root, u8 *, 0xC);
    u8 *entity_aux = entity;
    s32 direction;
    register s32 dx ASM_REG("$2");
    s32 dy;
    register s32 distance_x ASM_REG("$3");
    register s32 target_y ASM_REG("$4");
    register s32 entity_y ASM_REG("$2");
    register s32 scaled_distance ASM_REG("$2");
    s16 height;
    s32 tile_flags;
    u8 call_x;
    u8 call_y;
    s16 *delta;
    u8 *room;
    u8 *collision;

    if (state == 1) {
        goto move_entity;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_zero;
        }
        {
            register s32 result ASM_REG("$2");

            result = 0;
            ASM_KEEP(result);
            func_800F80A8();
            return result;
        }
    }
    if (state == 2) {
        goto state_two;
    }
    {
        register s32 result ASM_REG("$2");

        result = 0;
        ASM_KEEP(result);
        func_800F80A8();
        return result;
    }

state_zero:
    {
    register u8 *state_page ASM_REG("$2");
    register u8 *state_room ASM_REG("$4");
    register s32 state_target ASM_REG("$3");
    register s32 state_dy ASM_REG("$2");

    ASM_SCHED_BARRIER();
#ifdef NON_MATCHING
    state_page = D_80082E80 - 0x2E80;
#else
    state_page = (u8 *)0x80080000;
#endif
    ASM_KEEP_NV(state_page);
    state_room = state_page + 0x2E80;
    ASM_KEEP_NV(state_room);
    dx = FIELD(state_room, u8, 0x24);
    ASM_KEEP_NV(dx);
    state_target = FIELD(target, u8, 0x24);
    ASM_KEEP_NV(state_target);
    dx -= state_target;
    ASM_KEEP_NV(dx);
        if (dx < 0) {
            dx = -dx;
        }
        if (dx < 3) {
            state_dy = FIELD(state_room, u8, 0x25);
            ASM_KEEP_NV(state_dy);
            state_target = FIELD(target, u8, 0x25);
            ASM_KEEP_NV(state_target);
            state_dy -= state_target;
            ASM_KEEP_NV(state_dy);
            if (state_dy < 0) {
                state_dy = -state_dy;
            }
            if (state_dy < 3) {
                register s32 result ASM_REG("$2");
                register s32 store_state ASM_REG("$3");

                result = 1;
                ASM_KEEP(result);
                store_state = 0x63;
                FIELD(entity, u8, 0x9B) = store_state;
                store_state = 2;
                FIELD(entity, u8, 0xB8) = store_state;
                func_800F80A8();
                return result;
            }
        }
    }

        FIELD(entity, u8, 0x9B)++;
        direction = func_800F6D28(motion);
        direction += 4;
        if (direction >= 8) {
            direction -= 8;
        }
        room = D_80082E80;
        collision = D_80083780;

find_direction:
        func_8009A350(FIELD(room, u8, 0x24), FIELD(room, u8, 0x25),
                      (s16)direction, &collision_flags);
        if (collision_flags & 0xB400) {
            goto next_direction;
        }

        delta = (s16 *)&offsets + direction * 2;
        FIELD(entity, s16, 0xAA) = FIELD(room, u8, 0x24) + (u16)delta[0];
        FIELD(entity, s16, 0xAE) = FIELD(room, u8, 0x25) + (u16)delta[1];
        if ((s16)func_800A45D8(
                ((FIELD(entity, s16, 0xAA) << 6) + 0x20) & 0xFFE0,
                ((FIELD(entity, s16, 0xAE) << 6) + 0x20) & 0xFFE0,
                FIELD(collision, s16, 0xA)) != 0) {
next_direction:
            direction++;
            if (direction < 8) {
                goto find_direction;
            }
            direction = 0;
            ASM_TAILSLOT_PIN(direction);
            func_800F7DA8();
            return direction;
        }

        {
        register s32 target_x ASM_REG("$2");
        register s32 collision_y ASM_REG("$5");
        register s32 distance_compare ASM_REG("$2");
        s32 entity_flags;

        distance_x = FIELD(entity, s16, 0xAA);
        ASM_KEEP_NV(distance_x);
        target_x = FIELD(target, u8, 0x24);
        ASM_KEEP_NV(target_x);
        target_y = FIELD(target, u8, 0x25);
        ASM_KEEP_NV(target_y);
        distance_x -= target_x;
        ASM_KEEP_NV(distance_x);
        ASM_SCHED_BARRIER();
        entity_y = FIELD(entity, s16, 0xAE);
        ASM_KEEP_NV(entity_y);
        if (distance_x < 0) {
            distance_x = -distance_x;
        }
        ASM_KEEP_NV(distance_x);
        ASM_SCHED_BARRIER();
        entity_y -= target_y;
        ASM_KEEP_NV(entity_y);
        collision_y = entity_y;
        if (entity_y < 0) {
            collision_y = -collision_y;
        }
        ASM_KEEP_NV(collision_y);
        distance_compare = distance_x < collision_y;
        ASM_KEEP_NV(distance_compare);
        if (distance_compare) {
            scaled_distance = collision_y * 4;
        } else {
            scaled_distance = distance_x * 4;
        }
        ASM_KEEP_NV(scaled_distance);
        FIELD(entity, s16, 0x96) = scaled_distance;

        entity_flags = FIELD(entity_aux, volatile s32, 0x1C);
        ASM_SCHED_BARRIER();
        call_x = FIELD(target, u8, 0x24);
        call_y = FIELD(target, u8, 0x25);
        tile_flags = 0x3000;
        if (entity_flags & 0x2000) {
            tile_flags = 0x300;
        }
        func_8009A3D0(call_x, call_y, tile_flags);
        }
    goto move_entity;

move_entity:
    {
        register s32 move_x ASM_REG("$3");
        register s32 move_raw_y ASM_REG("$2");
        register s32 move_y ASM_REG("$5");
        register s32 move_x_arg ASM_REG("$4");

        move_x = FIELD(entity, s16, 0xAA) << 6;
        ASM_KEEP_NV(move_x);
        move_x += 0x20;
        move_raw_y = FIELD(entity, s16, 0xAE) << 6;
        ASM_KEEP_NV(move_raw_y);
        move_y = move_raw_y + 0x20;
        ASM_KEEP_NV(move_y);
        move_x_arg = move_x & 0xFFE0;
        ASM_KEEP_NV(move_x_arg);
        height = func_800BCB04(move_x_arg, move_y & 0xFFE0, -0x400);
    }
    motion[3] = ((((FIELD(entity, s16, 0xAA) << 6) + 0x20) << 16) -
                 motion[0]) /
                FIELD(entity, s16, 0x96);
    motion[4] = ((((FIELD(entity, s16, 0xAE) << 6) + 0x20) << 16) -
                 motion[1]) /
                FIELD(entity, s16, 0x96);
    motion[5] = (((s16)height - FIELD(entity_aux, s16, 0x88)) << 16) /
                FIELD(entity, s16, 0x96);
    FIELD(entity_aux, s16, 0x88) =
        (u16)FIELD(entity_aux, s16, 0x88) + FIELD(motion, u16, 0x16);

    dx = motion[3];
    motion[5] = 0;
    if (dx == 0) {
        direction = 6;
        if (motion[4] > 0) {
            direction = 2;
            ASM_TAILSLOT_PIN(direction);
            func_800F7FD0();
            return direction;
        }
        goto set_direction;
    }
    dy = motion[4];
    if (dy == 0) {
        direction = (dx < 1) << 2;
        ASM_TAILSLOT_PIN(direction);
        func_800F7FD0();
        return direction;
    }
    if (dx > 0) {
        direction = 7;
        if (dy > 0) {
            direction = 1;
            ASM_TAILSLOT_PIN(direction);
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
    FIELD(entity_aux, s16, 0x2A) = direction << 9;
    FIELD(entity, u16, 0x96)--;
    if ((s16)FIELD(entity, u16, 0x96) > 0) {
        return 0;
    }
    FIELD(entity, u8, 0x9B)++;
    func_800F80A4();
    return 0;

state_two:
    ASM_SCHED_BARRIER();
    FIELD(target, u8, 0x24) = FIELD(entity, u8, 0xAA);
    FIELD(target, u8, 0x25) = FIELD(entity, u8, 0xAE);
    motion[0] = ((FIELD(target, u8, 0x24) << 6) + 0x20) << 16;
    motion[1] = ((FIELD(target, u8, 0x25) << 6) + 0x20) << 16;
    motion[5] = 0;
    motion[4] = 0;
    motion[3] = 0;
    FIELD(entity, s16, 0x88) = func_800BCB04(FIELD(motion, u16, 2),
                                             FIELD(motion, u16, 6), -0x400);
    func_800A2B04(motion, FIELD(target, u8, 0x24), FIELD(target, u8, 0x25));
    {
        s32 entity_flags;

        entity_flags = FIELD(entity, volatile s32, 0x1C);
        ASM_SCHED_BARRIER();
        call_x = FIELD(target, u8, 0x24);
        call_y = FIELD(target, u8, 0x25);
        tile_flags = 0x3000;
        if (entity_flags & 0x2000) {
            tile_flags = 0x300;
        }
    }
    func_8009A21C(call_x, call_y, tile_flags);
    FIELD(entity, u8, 0xB8) = state;
    {
        register s32 result ASM_REG("$2");

        result = 1;
        ASM_USE(result);
        ASM_TAILSLOT_PIN(result);
        func_800F80A8_returning();
        return 0;
    }
}
