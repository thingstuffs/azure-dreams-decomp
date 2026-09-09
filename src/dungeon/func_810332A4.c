#include "common.h"

typedef struct S_func_810332A4_1 {
    u8 pad_00[0x16];
    union { s16 s; u16 u; } unk_16;
    u8 pad_18[4];
    s16 unk_1C;
    union { s16 s; u16 u; } unk_1E;
    u8 pad_20[6];
    s16 unk_26;
    void *unk_28;
    void *unk_2C;
    void *unk_30;
    u8 pad_34[0x18];
    union { s8 s; u8 u; } unk_4C;
    union { s8 s; u8 u; } unk_4D;
} S_func_810332A4_1;

typedef struct S_func_810332A4_2 {
    union {
        s32 word;
        struct { u8 pad_00[2]; s16 unk_02; } half;
    } unk_00;
    union {
        s32 word;
        struct { u8 pad_04[2]; s16 unk_06; } half;
    } unk_04;
    u8 pad_08[2];
    union { s16 s; u16 u; } unk_0A;
    s32 unk_0C;
    s32 unk_10;
} S_func_810332A4_2;

typedef struct S_func_810332A4_3 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[5];
    u16 unk_14;
} S_func_810332A4_3;

typedef struct S_func_810332A4_4 {
    u8 pad_00[0x11];
    u8 unk_11;
    u8 pad_12[0x18];
    s16 unk_2A;
    u8 pad_2C[0x80];
    u8 unk_AC;
} S_func_810332A4_4;

typedef struct S_func_810332A4_5 {
    u8 pad_00[8];
    void *unk_08;
    void *unk_0C;
} S_func_810332A4_5;

typedef struct S_func_810332A4_6 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_func_810332A4_6;

typedef struct S_func_810332A4_7 {
    u8 pad_00[0x14];
    u32 unk_14;
    u8 pad_18[4];
    u32 unk_1C;
    u8 pad_20[0x68];
    s16 unk_88;
} S_func_810332A4_7;

typedef struct S_func_810332A4_8 {
    u8 unk_00;
    u8 pad_01[1];
    u8 unk_02;
} S_func_810332A4_8;

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
    S_func_810332A4_4 *owner;
    S_func_810332A4_5 *object;
    S_func_810332A4_5 *new_object;
    register S_func_810332A4_6 *display ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    register S_func_810332A4_2 *transform ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    s32 blocked;
    s32 stop_mask;
    s32 step_coord;
    s32 step_x;
    s32 cleanup_mask;
    s32 next_tile;
    s32 collision_coord;
    register s32 coord_base ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    register S_func_810332A4_7 *object_data ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
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
    S_func_810332A4_1 *held_effect;
    S_func_810332A4_2 *held_motion;
    register S_func_810332A4_3 *held_sprite ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    S_func_810332A4_4 *effect_owner;

    held_effect = effect;
    held_motion = motion;
    held_sprite = sprite;
#define effect held_effect
#define motion held_motion
#define sprite held_sprite

    effect_owner = effect->unk_28;
    state = effect->unk_16.s;
    owner = effect_owner;
    if ((u32)state >= 13U) {
        goto end;
    }
    (void)state_labels;
    goto *D_80170858[state];

state_0:
    timer = effect->unk_1E.u + 1;
    effect->unk_1E.u = timer;
    fade_value = ((s16)timer << 7) / 10;
    sprite->unk_0E = fade_value;
    sprite->unk_0D = fade_value;
    sprite->unk_0C = fade_value;
    fade_value = effect->unk_1E.s < 10;
    if (fade_value) {
        goto end;
    }
    effect->unk_1E.u = 0;
    effect->unk_16.u++;
    goto end;

state_1:
    timer = effect->unk_1E.u + 1;
    effect->unk_1E.u = timer;
    if ((s16)timer < 30) {
        goto end;
    }
    effect->unk_16.u++;
    effect->unk_1E.u = 0;
    motion->unk_0C = D_8017610C[effect->unk_1C].x << 20;
    motion->unk_10 = D_8017610C[effect->unk_1C].y << 20;
    func_800A56E0(0x808);
    goto end;

state_2:
    if ((effect->unk_4C.s << 6) + 0x20 != motion->unk_00.half.unk_02) {
        goto object_common;
    }
    if ((effect->unk_4D.s << 6) + 0x20 != motion->unk_04.half.unk_06) {
        goto object_common;
    }

    effect->unk_26 = 0;
    func_8009A350(effect->unk_4C.s, effect->unk_4D.s,
                  effect->unk_1C, &collision_flags);
    if (collision_flags & 0x8400) {
        effect->unk_26 = 1;
    }
    coord_base = (s32)D_8017610C;
    step_x = effect->unk_1C;
    ASM_KEEP_NV(effect);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    next_tile = effect->unk_4C.u;
    step_x <<= 2;
    step_x += (s32)coord_base;
    step_x = ((S_func_810332A4_8 *)step_x)->unk_00;
    next_tile += step_x;
    effect->unk_4C.u = next_tile;
    collision_coord = effect->unk_1C;
    collision_coord <<= 2;
    collision_coord += (s32)coord_base;
    ASM_KEEP_NV(effect);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    step_coord = effect->unk_4C.s;
    next_tile = effect->unk_4D.u;
    collision_coord = ((S_func_810332A4_8 *)collision_coord)->unk_02;
    ASM_KEEP_DEP_NV(step_coord, next_tile);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP_DEP_NV(step_coord, collision_coord);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    next_tile += collision_coord;
    effect->unk_4D.u = next_tile;
    step_coord <<= 6;
    ASM_KEEP_NV(step_coord);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    target_x = step_coord + 0x20;
    target_y = (effect->unk_4D.s << 6) + 0x20;
    collision_coord = effect->unk_26;
    if (collision_coord != 0) {
        goto checks_done;
    }
    ASM_KEEP_NV(target_y);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    check_x = (u16)target_x;
    check_y = (u16)target_y;
    if ((func_800A45D8(check_x, check_y,
                       motion->unk_0A.s) << 16) != 0) {
        effect->unk_26 = 1;
    }
    if (effect->unk_26 == 0) {
        if (func_80174A00(owner, (u16)(s8)effect->unk_4C.u,
                           (u16)(s8)effect->unk_4D.u,
                           motion->unk_0A.s) != 0) {
            effect->unk_26 = 1;
        }
    }
    if (effect->unk_26 == 0) {
        floor_height = func_800BCB04(check_x, check_y,
                              (s16)((u16)motion->unk_0A.s - 0x20));
        if (floor_height >= 0x200 || floor_height > motion->unk_0A.s + 0x20 ||
            floor_height < motion->unk_0A.s) {
            effect->unk_26 = 1;
        }
    }

checks_done:
    if (effect->unk_26 == 1) {
        effect->unk_16.s = 10;
        effect->unk_1E.s = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        object = effect->unk_30;
        if (object == 0) {
            goto end;
        }
        object_data = (S_func_810332A4_7 *)((u8 *)object + 0x20);
        display = object->unk_0C;
        transform = object->unk_08;
        cleanup_mask = 0xFFEFFFFF;
        ASM_KEEP4_NV(cleanup_mask, cleanup_mask, cleanup_mask, cleanup_mask);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
        object_data->unk_14 &= cleanup_mask;
        goto cleanup_object;
    }

    if (effect->unk_2C == 0) {
        new_object = func_801748FC(owner,
                    (u16)(s8)effect->unk_4C.u,
                    (u16)(s8)effect->unk_4D.u,
                    motion->unk_0A.s);
        effect->unk_2C = new_object;
        if (new_object == 0) {
            goto secondary_object;
        }
        object = new_object;
        object_data = (S_func_810332A4_7 *)((u8 *)object + 0x20);
        display = object->unk_0C;
        object_data->unk_14 |= 0x100000;
        func_8009A3D0(display->unk_24, display->unk_25,
                      (object_data->unk_1C & 0x2000) ? 0x300 : 0x3000);
    }

object_common:
    if (effect->unk_2C == 0) {
        goto secondary_object;
    }
    object = effect->unk_2C;
    display = object->unk_0C;
    transform = object->unk_08;
    object_data = (S_func_810332A4_7 *)((u8 *)object + 0x20);
    if ((((volatile S_func_810332A4_6 *)display)->unk_24 << 6) + 0x20 !=
        transform->unk_00.half.unk_02) {
        goto rollback_object;
    }
    if ((((volatile S_func_810332A4_6 *)display)->unk_25 << 6) + 0x20 !=
        transform->unk_04.half.unk_06) {
        goto rollback_object;
    }

    func_8009A350(display->unk_24, display->unk_25,
                  effect->unk_1C, &collision_flags);
    coord_base = (s32)D_8017610C;
    step_coord = effect->unk_1C;
    object_tile = display->unk_24;
    collision_coord = collision_flags;
    step_coord <<= 2;
    step_coord += coord_base;
    collision_coord &= 0x8400;
    step_coord = ((S_func_810332A4_8 *)step_coord)->unk_00;
    blocked = collision_coord != 0;
    object_tile += step_coord;
    display->unk_24 = object_tile;
    step_coord = effect->unk_1C;
    object_tile = display->unk_25;
    collision_coord = display->unk_24;
    step_coord <<= 2;
    step_coord += coord_base;
    step_coord = ((S_func_810332A4_8 *)step_coord)->unk_02;
    ASM_KEEP_DEP_NV(collision_coord, step_coord);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    collision_coord <<= 6;
    ASM_KEEP_NV(collision_coord);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    object_tile += step_coord;
    display->unk_25 = object_tile;
    coord_base = collision_coord + 0x20;
    object_x = coord_base & 0xFFFF;
    object_y = (((volatile S_func_810332A4_6 *)display)->unk_25 << 6) + 0x20;

    if (!blocked) {
        if ((func_800A45D8((u16)object_x, (u16)object_y,
                           transform->unk_0A.s) << 16) != 0) {
            blocked = 1;
        }
    }
    if (!blocked) {
        if (func_80174A00(owner, display->unk_24,
                           display->unk_25,
                           motion->unk_0A.s) != 0) {
            blocked = 1;
        }
    }
    if (!blocked) {
        floor_height = func_800BCB04((u16)object_x, (u16)object_y,
                              (s16)((u16)object_data->unk_88 - 0x20));
        if (floor_height >= 0x200 || floor_height > object_data->unk_88 + 0x20 ||
            floor_height < object_data->unk_88) {
            blocked = 1;
        }
    }

    if (func_801748FC(object_data, display->unk_24,
                      display->unk_25, object_data->unk_88) != 0) {
        blocked = 1;
    }
    if (blocked != 1) {
        goto rollback_object;
    }

    stop_mask = 0xFFEFFFFF;
    object_data->unk_14 &= stop_mask;
    display->unk_24 -=
        (u8)D_8017610C[effect->unk_1C].x;
    display->unk_25 -=
        (u8)D_8017610C[effect->unk_1C].y;
    func_800A2B04(transform, display->unk_24, ((volatile S_func_810332A4_6 *)display)->unk_25);
    func_8009A21C(display->unk_24, display->unk_25,
                  (object_data->unk_1C & 0x2000) ? 0x300 : 0x3000);
    func_800AA53C(object_data);
    effect->unk_16.s = 10;
    effect->unk_1E.s = 0;
    motion->unk_10 = 0;
    motion->unk_0C = 0;
    func_8009CE1C(object_data, 7, owner->unk_11, 10,
                  owner->unk_2A, (u32)owner | 0xA0000000, 2);

    new_object = effect->unk_30;
    if (new_object == 0) {
        goto end;
    }
    object = new_object;
    object_data = (S_func_810332A4_7 *)((u8 *)object + 0x20);
    display = object->unk_0C;
    transform = object->unk_08;
    object_data->unk_14 &= stop_mask;

cleanup_object:
    func_800A2B04(transform, display->unk_24, display->unk_25);
    func_8009A21C(display->unk_24, display->unk_25,
                  (object_data->unk_1C & 0x2000) ? 0x300 : 0x3000);
    func_800AA53C(object_data);
    goto end;

rollback_object:
    object_tile_x = display->unk_24;
    if ((object_tile_x - D_8017610C[effect->unk_1C].x) * 64 + 0x20 !=
            transform->unk_00.half.unk_02 ||
        (display->unk_25 - D_8017610C[effect->unk_1C].y) * 64 + 0x20 !=
            transform->unk_04.half.unk_06) {
        floor_height = func_800BCB04((object_tile_x << 6) | 0x20,
                              (display->unk_25 << 6) | 0x20,
                              object_data->unk_88);
        if (transform->unk_0A.s < floor_height) {
            transform->unk_0A.u += 0x10;
            object_data->unk_88 = floor_height;
        }
    }
    transform->unk_00.word += motion->unk_0C;
    transform->unk_04.word += motion->unk_10;

secondary_object:
    new_object = effect->unk_30;
    if (new_object != 0) {
        object = new_object;
        display = object->unk_0C;
        transform = object->unk_08;
        object_data = (S_func_810332A4_7 *)((u8 *)object + 0x20);
        if ((display->unk_24 << 6) + 0x20 == transform->unk_00.half.unk_02 &&
            (display->unk_25 << 6) + 0x20 == transform->unk_04.half.unk_06) {
            display->unk_24 +=
                (u8)D_8017610C[effect->unk_1C].x;
            display->unk_25 +=
                (u8)D_8017610C[effect->unk_1C].y;
        } else {
            floor_height = func_800BCB04((display->unk_24 << 6) | 0x20,
                                  (display->unk_25 << 6) | 0x20,
                                  object_data->unk_88);
            if (transform->unk_0A.s < floor_height) {
                transform->unk_0A.u += 0x10;
                object_data->unk_88 = floor_height;
            }
        }
        transform->unk_00.word += motion->unk_0C;
        transform->unk_04.word += motion->unk_10;
    }

    tile_x = effect->unk_4C.s;
    if ((tile_x - D_8017610C[effect->unk_1C].x) * 64 + 0x20 !=
            motion->unk_00.half.unk_02 ||
        (effect->unk_4D.s - D_8017610C[effect->unk_1C].y) * 64 + 0x20 !=
            motion->unk_04.half.unk_06) {
        world_coord = tile_x << 6;
        ASM_KEEP_NV(world_coord);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        coord_base = world_coord + 0x20;
        floor_x = coord_base & 0xFFE0;
        world_coord = effect->unk_4D.s << 6;
        world_coord += 0x20;
        floor_y = world_coord & 0xFFE0;
        floor_height = func_800BCB04(floor_x, floor_y, motion->unk_0A.s);
        if (motion->unk_0A.s < floor_height) {
            motion->unk_0A.u += 0x10;
        }
    }
    motion->unk_00.word += motion->unk_0C;
    motion->unk_04.word += motion->unk_10;
    goto end;

state_10:
    for (burst_index = 0; burst_index < 16; burst_index++) {
        func_801744DC(effect, motion, sprite);
    }
    for (burst_index = 0; burst_index < 16; burst_index++) {
        func_801746EC(effect, motion, sprite);
    }
    func_800A56E0(0x80B);
    effect->unk_1E.u = 0;
    effect->unk_16.u++;
    sprite->unk_14 |= 0x80;

state_11:
    timer = effect->unk_1E.u + 1;
    effect->unk_1E.u = timer;
    delay_pending = (s16)timer < 10;
    if (delay_pending) {
        goto end;
    }
    effect->unk_1E.u = 0;
    effect->unk_16.u++;
    goto end;

state_12:
    effect_owner->unk_AC = 0x4D;
    *(u16 *)((u8 *)effect - 2) |= 0x8000;
    D_800814A0 |= 0x8000;

end:
    return;
}
