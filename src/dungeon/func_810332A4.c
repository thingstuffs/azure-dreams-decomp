#include "common.h"

#define FIELD(p, t, o) (*(t *)((u8 *)(p) + (o)))

typedef struct {
    s16 x;
    s16 y;
} Pair16;

extern void func_8009A21C(s32, s32, s32);
extern void func_8009A350(s32, s32, s32, u16 *);
extern void func_8009A3D0(s32, s32, s32);
extern void func_8009CE1C();
extern void func_800A2B04(void *, s32, s32);
extern s32 func_800A45D8(u16, u16, s16);
extern void func_800A56E0(s32);
extern void func_800AA53C(void *);
extern s16 func_800BCB04(u16, u16, s16);
extern void func_801744DC();
extern void func_801746EC();
extern void *func_801748FC(void *, s32, s32, s16);
extern s32 func_80174A00(void *, s32, s32, s16);

extern s32 D_800814A0;
extern void *D_80170858[];
extern Pair16 D_8017610C[];

/* Update a moving effect, its pushed objects, and its collision and end animations. */
void func_80174AA4(void *effect, void *motion, void *sprite)
{
    static void *const state_labels[] = {
        &&state_0, &&state_1, &&state_2,
        &&end, &&end, &&end, &&end, &&end, &&end, &&end,
        &&state_10, &&state_11, &&state_12,
    };
    u16 collision_flags;
    void *owner;
    void *object;
    void *new_object;
    register void *display ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    register void *transform ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    s32 blocked;
    s32 stop_mask;
    s32 step_coord;
    s32 step_x;
    s32 cleanup_mask;
    s32 next_tile;
    s32 collision_coord;
    register s32 coord_base ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    register void *object_data ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 state;
    s32 burst_index;
    s32 target_y;
    u32 check_x;
    u32 check_y;
    u16 object_x;
    s32 object_y;
    s32 floor_height;
    s32 object_tile_x;
    s32 tile_y;
    s32 world_coord;
    s32 tile_x;
    s32 floor_x;
    s32 floor_y;
    register s32 target_x ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    register s32 object_tile ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 fade_value;
    s32 delay_pending;
    u16 timer;
    void *held_effect;
    void *held_motion;
    register void *held_sprite ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    void *effect_owner;

    held_effect = effect;
    held_motion = motion;
    held_sprite = sprite;
#define effect held_effect
#define motion held_motion
#define sprite held_sprite

    effect_owner = FIELD(effect, void *, 0x28);
    state = FIELD(effect, s16, 0x16);
    owner = effect_owner;
    if ((u32)state >= 13U) {
        goto end;
    }
    (void)state_labels;
    goto *D_80170858[state];

state_0:
    timer = FIELD(effect, u16, 0x1E) + 1;
    FIELD(effect, u16, 0x1E) = timer;
    fade_value = ((s16)timer << 7) / 10;
    FIELD(sprite, u8, 0xE) = fade_value;
    FIELD(sprite, u8, 0xD) = fade_value;
    FIELD(sprite, u8, 0xC) = fade_value;
    fade_value = FIELD(effect, s16, 0x1E) < 10;
    if (fade_value) {
        goto end;
    }
    FIELD(effect, u16, 0x1E) = 0;
    FIELD(effect, u16, 0x16)++;
    goto end;

state_1:
    timer = FIELD(effect, u16, 0x1E) + 1;
    FIELD(effect, u16, 0x1E) = timer;
    if ((s16)timer < 30) {
        goto end;
    }
    FIELD(effect, u16, 0x16)++;
    FIELD(effect, u16, 0x1E) = 0;
    FIELD(motion, s32, 0xC) = D_8017610C[FIELD(effect, s16, 0x1C)].x << 20;
    FIELD(motion, s32, 0x10) = D_8017610C[FIELD(effect, s16, 0x1C)].y << 20;
    func_800A56E0(0x808);
    goto end;

state_2:
    if ((FIELD(effect, s8, 0x4C) << 6) + 0x20 != FIELD(motion, s16, 2)) {
        goto object_common;
    }
    if ((FIELD(effect, s8, 0x4D) << 6) + 0x20 != FIELD(motion, s16, 6)) {
        goto object_common;
    }

    FIELD(effect, s16, 0x26) = 0;
    func_8009A350(FIELD(effect, s8, 0x4C), FIELD(effect, s8, 0x4D),
                  FIELD(effect, s16, 0x1C), &collision_flags);
    if (collision_flags & 0x8400) {
        FIELD(effect, s16, 0x26) = 1;
    }
    coord_base = (s32)D_8017610C;
    step_x = FIELD(effect, s16, 0x1C);
    ASM_KEEP_NV(effect);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    next_tile = FIELD(effect, u8, 0x4C);
    step_x <<= 2;
    step_x += (s32)coord_base;
    step_x = FIELD((void *)step_x, u8, 0);
    next_tile += step_x;
    FIELD(effect, u8, 0x4C) = next_tile;
    collision_coord = FIELD(effect, s16, 0x1C);
    collision_coord <<= 2;
    collision_coord += (s32)coord_base;
    ASM_KEEP_NV(effect);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    step_coord = FIELD(effect, s8, 0x4C);
    next_tile = FIELD(effect, u8, 0x4D);
    collision_coord = FIELD((void *)collision_coord, u8, 2);
    ASM_KEEP_DEP_NV(step_coord, next_tile);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP_DEP_NV(step_coord, collision_coord);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    next_tile += collision_coord;
    FIELD(effect, u8, 0x4D) = next_tile;
    step_coord <<= 6;
    ASM_KEEP_NV(step_coord);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    target_x = step_coord + 0x20;
    target_y = (FIELD(effect, s8, 0x4D) << 6) + 0x20;
    collision_coord = FIELD(effect, s16, 0x26);
    if (collision_coord != 0) {
        goto checks_done;
    }
    ASM_KEEP_NV(target_y);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    check_x = (u16)target_x;
    check_y = (u16)target_y;
    if ((func_800A45D8(check_x, check_y,
                       FIELD(motion, s16, 0xA)) << 16) != 0) {
        FIELD(effect, s16, 0x26) = 1;
    }
    if (FIELD(effect, s16, 0x26) == 0) {
        if (func_80174A00(owner, (u16)(s8)FIELD(effect, u8, 0x4C),
                           (u16)(s8)FIELD(effect, u8, 0x4D),
                           FIELD(motion, s16, 0xA)) != 0) {
            FIELD(effect, s16, 0x26) = 1;
        }
    }
    if (FIELD(effect, s16, 0x26) == 0) {
        floor_height = func_800BCB04(check_x, check_y,
                              (s16)((u16)FIELD(motion, s16, 0xA) - 0x20));
        if (floor_height >= 0x200 || floor_height > FIELD(motion, s16, 0xA) + 0x20 ||
            floor_height < FIELD(motion, s16, 0xA)) {
            FIELD(effect, s16, 0x26) = 1;
        }
    }

checks_done:
    if (FIELD(effect, s16, 0x26) == 1) {
        FIELD(effect, s16, 0x16) = 10;
        FIELD(effect, s16, 0x1E) = 0;
        FIELD(motion, s32, 0x10) = 0;
        FIELD(motion, s32, 0xC) = 0;
        object = FIELD(effect, void *, 0x30);
        if (object == 0) {
            goto end;
        }
        object_data = (u8 *)object + 0x20;
        display = FIELD(object, void *, 0xC);
        transform = FIELD(object, void *, 8);
        cleanup_mask = 0xFFEFFFFF;
        ASM_KEEP4_NV(cleanup_mask, cleanup_mask, cleanup_mask, cleanup_mask);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
        FIELD(object_data, u32, 0x14) &= cleanup_mask;
        goto cleanup_object;
    }

    if (FIELD(effect, void *, 0x2C) == 0) {
        new_object = func_801748FC(owner,
                    (u16)(s8)FIELD(effect, u8, 0x4C),
                    (u16)(s8)FIELD(effect, u8, 0x4D),
                    FIELD(motion, s16, 0xA));
        FIELD(effect, void *, 0x2C) = new_object;
        if (new_object == 0) {
            goto secondary_object;
        }
        object = new_object;
        object_data = (u8 *)object + 0x20;
        display = FIELD(object, void *, 0xC);
        FIELD(object_data, u32, 0x14) |= 0x100000;
        func_8009A3D0(FIELD(display, u8, 0x24), FIELD(display, u8, 0x25),
                      (FIELD(object_data, u32, 0x1C) & 0x2000) ? 0x300 : 0x3000);
    }

object_common:
    if (FIELD(effect, void *, 0x2C) == 0) {
        goto secondary_object;
    }
    object = FIELD(effect, void *, 0x2C);
    display = FIELD(object, void *, 0xC);
    transform = FIELD(object, void *, 8);
    object_data = (u8 *)object + 0x20;
    if ((FIELD(display, volatile u8, 0x24) << 6) + 0x20 !=
        FIELD(transform, s16, 2)) {
        goto rollback_object;
    }
    if ((FIELD(display, volatile u8, 0x25) << 6) + 0x20 !=
        FIELD(transform, s16, 6)) {
        goto rollback_object;
    }

    func_8009A350(FIELD(display, u8, 0x24), FIELD(display, u8, 0x25),
                  FIELD(effect, s16, 0x1C), &collision_flags);
    coord_base = (s32)D_8017610C;
    step_coord = FIELD(effect, s16, 0x1C);
    object_tile = FIELD(display, u8, 0x24);
    collision_coord = collision_flags;
    step_coord <<= 2;
    step_coord += coord_base;
    collision_coord &= 0x8400;
    step_coord = FIELD((void *)step_coord, u8, 0);
    blocked = collision_coord != 0;
    object_tile += step_coord;
    FIELD(display, u8, 0x24) = object_tile;
    step_coord = FIELD(effect, s16, 0x1C);
    object_tile = FIELD(display, u8, 0x25);
    collision_coord = FIELD(display, u8, 0x24);
    step_coord <<= 2;
    step_coord += coord_base;
    step_coord = FIELD((void *)step_coord, u8, 2);
    ASM_KEEP_DEP_NV(collision_coord, step_coord);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    collision_coord <<= 6;
    ASM_KEEP_NV(collision_coord);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    object_tile += step_coord;
    FIELD(display, u8, 0x25) = object_tile;
    coord_base = collision_coord + 0x20;
    object_x = coord_base & 0xFFFF;
    object_y = (FIELD(display, volatile u8, 0x25) << 6) + 0x20;

    if (!blocked) {
        if ((func_800A45D8((u16)object_x, (u16)object_y,
                           FIELD(transform, s16, 0xA)) << 16) != 0) {
            blocked = 1;
        }
    }
    if (!blocked) {
        if (func_80174A00(owner, FIELD(display, u8, 0x24),
                           FIELD(display, u8, 0x25),
                           FIELD(motion, s16, 0xA)) != 0) {
            blocked = 1;
        }
    }
    if (!blocked) {
        floor_height = func_800BCB04((u16)object_x, (u16)object_y,
                              (s16)((u16)FIELD(object_data, s16, 0x88) - 0x20));
        if (floor_height >= 0x200 || floor_height > FIELD(object_data, s16, 0x88) + 0x20 ||
            floor_height < FIELD(object_data, s16, 0x88)) {
            blocked = 1;
        }
    }

    if (func_801748FC(object_data, FIELD(display, u8, 0x24),
                      FIELD(display, u8, 0x25), FIELD(object_data, s16, 0x88)) != 0) {
        blocked = 1;
    }
    if (blocked != 1) {
        goto rollback_object;
    }

    stop_mask = 0xFFEFFFFF;
    FIELD(object_data, u32, 0x14) &= stop_mask;
    FIELD(display, u8, 0x24) -=
        (u8)D_8017610C[FIELD(effect, s16, 0x1C)].x;
    FIELD(display, u8, 0x25) -=
        (u8)D_8017610C[FIELD(effect, s16, 0x1C)].y;
    func_800A2B04(transform, FIELD(display, u8, 0x24), FIELD(display, volatile u8, 0x25));
    func_8009A21C(FIELD(display, u8, 0x24), FIELD(display, u8, 0x25),
                  (FIELD(object_data, u32, 0x1C) & 0x2000) ? 0x300 : 0x3000);
    func_800AA53C(object_data);
    FIELD(effect, s16, 0x16) = 10;
    FIELD(effect, s16, 0x1E) = 0;
    FIELD(motion, s32, 0x10) = 0;
    FIELD(motion, s32, 0xC) = 0;
    func_8009CE1C(object_data, 7, FIELD(owner, u8, 0x11), 10,
                  FIELD(owner, s16, 0x2A), (u32)owner | 0xA0000000, 2);

    new_object = FIELD(effect, void *, 0x30);
    if (new_object == 0) {
        goto end;
    }
    object = new_object;
    object_data = (u8 *)object + 0x20;
    display = FIELD(object, void *, 0xC);
    transform = FIELD(object, void *, 8);
    FIELD(object_data, u32, 0x14) &= stop_mask;

cleanup_object:
    func_800A2B04(transform, FIELD(display, u8, 0x24), FIELD(display, u8, 0x25));
    func_8009A21C(FIELD(display, u8, 0x24), FIELD(display, u8, 0x25),
                  (FIELD(object_data, u32, 0x1C) & 0x2000) ? 0x300 : 0x3000);
    func_800AA53C(object_data);
    goto end;

rollback_object:
    object_tile_x = FIELD(display, u8, 0x24);
    if ((object_tile_x - D_8017610C[FIELD(effect, s16, 0x1C)].x) * 64 + 0x20 !=
            FIELD(transform, s16, 2) ||
        (FIELD(display, u8, 0x25) - D_8017610C[FIELD(effect, s16, 0x1C)].y) * 64 + 0x20 !=
            FIELD(transform, s16, 6)) {
        floor_height = func_800BCB04((object_tile_x << 6) | 0x20,
                              (FIELD(display, u8, 0x25) << 6) | 0x20,
                              FIELD(object_data, s16, 0x88));
        if (FIELD(transform, s16, 0xA) < floor_height) {
            FIELD(transform, u16, 0xA) += 0x10;
            FIELD(object_data, s16, 0x88) = floor_height;
        }
    }
    FIELD(transform, s32, 0) += FIELD(motion, s32, 0xC);
    FIELD(transform, s32, 4) += FIELD(motion, s32, 0x10);

secondary_object:
    new_object = FIELD(effect, void *, 0x30);
    if (new_object != 0) {
        object = new_object;
        display = FIELD(object, void *, 0xC);
        transform = FIELD(object, void *, 8);
        object_data = (u8 *)object + 0x20;
        if ((FIELD(display, u8, 0x24) << 6) + 0x20 == FIELD(transform, s16, 2) &&
            (FIELD(display, u8, 0x25) << 6) + 0x20 == FIELD(transform, s16, 6)) {
            FIELD(display, u8, 0x24) +=
                (u8)D_8017610C[FIELD(effect, s16, 0x1C)].x;
            FIELD(display, u8, 0x25) +=
                (u8)D_8017610C[FIELD(effect, s16, 0x1C)].y;
        } else {
            floor_height = func_800BCB04((FIELD(display, u8, 0x24) << 6) | 0x20,
                                  (FIELD(display, u8, 0x25) << 6) | 0x20,
                                  FIELD(object_data, s16, 0x88));
            if (FIELD(transform, s16, 0xA) < floor_height) {
                FIELD(transform, u16, 0xA) += 0x10;
                FIELD(object_data, s16, 0x88) = floor_height;
            }
        }
        FIELD(transform, s32, 0) += FIELD(motion, s32, 0xC);
        FIELD(transform, s32, 4) += FIELD(motion, s32, 0x10);
    }

    tile_x = FIELD(effect, s8, 0x4C);
    if ((tile_x - D_8017610C[FIELD(effect, s16, 0x1C)].x) * 64 + 0x20 !=
            FIELD(motion, s16, 2) ||
        (FIELD(effect, s8, 0x4D) - D_8017610C[FIELD(effect, s16, 0x1C)].y) * 64 + 0x20 !=
            FIELD(motion, s16, 6)) {
        world_coord = tile_x << 6;
        ASM_KEEP_NV(world_coord);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        coord_base = world_coord + 0x20;
        floor_x = coord_base & 0xFFE0;
        world_coord = FIELD(effect, s8, 0x4D) << 6;
        world_coord += 0x20;
        floor_y = world_coord & 0xFFE0;
        floor_height = func_800BCB04(floor_x, floor_y, FIELD(motion, s16, 0xA));
        if (FIELD(motion, s16, 0xA) < floor_height) {
            FIELD(motion, u16, 0xA) += 0x10;
        }
    }
    FIELD(motion, s32, 0) += FIELD(motion, s32, 0xC);
    FIELD(motion, s32, 4) += FIELD(motion, s32, 0x10);
    goto end;

state_10:
    for (burst_index = 0; burst_index < 16; burst_index++) {
        func_801744DC(effect, motion, sprite);
    }
    for (burst_index = 0; burst_index < 16; burst_index++) {
        func_801746EC(effect, motion, sprite);
    }
    func_800A56E0(0x80B);
    FIELD(effect, u16, 0x1E) = 0;
    FIELD(effect, u16, 0x16)++;
    FIELD(sprite, u16, 0x14) |= 0x80;

state_11:
    timer = FIELD(effect, u16, 0x1E) + 1;
    FIELD(effect, u16, 0x1E) = timer;
    delay_pending = (s16)timer < 10;
    if (delay_pending) {
        goto end;
    }
    FIELD(effect, u16, 0x1E) = 0;
    FIELD(effect, u16, 0x16)++;
    goto end;

state_12:
    FIELD(effect_owner, u8, 0xAC) = 0x4D;
    FIELD(effect, u16, -2) |= 0x8000;
    D_800814A0 |= 0x8000;

end:
    return;
}
