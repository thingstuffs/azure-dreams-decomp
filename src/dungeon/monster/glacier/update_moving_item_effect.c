#include "common.h"
#include "shared/object_flags.h"

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

extern void cycle_map_cell_flags(s32, s32, s32);
extern void get_offset_map_cell_value_and_flags(s32, s32, s32, u16 *);
extern void update_map_cell_flags_with_item_limit(s32, s32, s32);
extern void apply_attack_power_and_element_effects();
extern void set_record_integer_tile_center(void *, s32, s32);
extern s32 check_left_tile_and_center_height(u16, u16, s16);
extern void play_sound_if_enabled(s32);
extern void refresh_actor_proximity_state(void *);
extern s16 sample_terrain_surface_height(u16, u16, s16);
extern void spawn_directional_particle();
extern void spawn_directional_effect();
extern void *find_nearby_eligible_entry(void *, s32, s32, s16);
extern s32 find_first_entry_matching_keys(void *, s32, s32, s16);

extern Pair16 D_8017610C[];

/* Update a moving effect, its pushed objects, and its collision and end animations. */
/* Moves an effect and pushed actors along tiles, checks terrain and occupants, and applies damage when
 * blocked. */
void update_moving_item_effect(S_func_810332A4_1 *effect, S_func_810332A4_2 *motion, S_func_810332A4_3 *sprite)
{
    u16 collision_flags;
    S_func_810332A4_4 *owner;
    S_func_810332A4_5 *object;
    S_func_810332A4_5 *new_object;
    S_func_810332A4_6 *display;
    S_func_810332A4_2 *transform;
    s32 blocked;
    s32 stop_mask;
    s32 step_x;
    s32 pos_y;
    s32 cleanup_mask;
    u8 next_tile;
    s32 collision_coord;
    s32 coord_base;
    s16 converted_x;
    S_func_810332A4_7 *object_data;
    s32 state;
    s32 burst_index;
    u32 check_x;
    u32 check_y;
    s32 object_y;
    s32 floor_height;
    s32 object_tile_x;
    s32 hit_state;
    s32 world_coord;
    s32 tile_x;
    s32 floor_x;
    s32 floor_y;
    s32 fade_value;
    s32 delay_pending;
    u16 timer;
    S_func_810332A4_4 *effect_owner;


    effect_owner = effect->unk_28;
    state = effect->unk_16.s;
    owner = effect_owner;
    switch (state) {
    case 0:
        timer = effect->unk_1E.u + 1;
        effect->unk_1E.u = timer;
        fade_value = ((s16)timer << 7) / 10;
        sprite->unk_0E = fade_value;
        sprite->unk_0D = fade_value;
        sprite->unk_0C = fade_value;
        fade_value = effect->unk_1E.s < 10;
        if (fade_value) {
            return;
        }
        effect->unk_1E.u = 0;
        effect->unk_16.u++;
        return;

    case 1:
        timer = effect->unk_1E.u + 1;
        effect->unk_1E.u = timer;
        if ((s16)timer < 30) {
            return;
        }
        effect->unk_16.u++;
        effect->unk_1E.u = 0;
        motion->unk_0C = D_8017610C[effect->unk_1C].x << 20;
        motion->unk_10 = D_8017610C[effect->unk_1C].y << 20;
        play_sound_if_enabled(0x808);
        return;

    case 2:
        if ((effect->unk_4C.s << 6) + 0x20 == motion->unk_00.half.unk_02) {
            if ((effect->unk_4D.s << 6) + 0x20 == motion->unk_04.half.unk_06) {
                effect->unk_26 = 0;
                get_offset_map_cell_value_and_flags(effect->unk_4C.s, effect->unk_4D.s,
                              effect->unk_1C, &collision_flags);
                if (collision_flags & 0x8400) {
                    effect->unk_26 = 1;
                }
                effect->unk_4C.u += (u8)D_8017610C[effect->unk_1C].x;
                collision_coord = effect->unk_1C << 2;
                collision_coord += (s32)D_8017610C;
                next_tile = effect->unk_4D.u;
                next_tile += ((S_func_810332A4_8 *)collision_coord)->unk_02;
                effect->unk_4D.u = next_tile;
                step_x = effect->unk_4C.s;
                pos_y = effect->unk_4D.s << 6;
                step_x <<= 6;
                hit_state = effect->unk_26;
                step_x += 0x20;
                converted_x = step_x;
                coord_base = converted_x;
                object_y = pos_y + 0x20;
                if (hit_state == 0) {
                    check_x = (u16)coord_base;
                    check_y = object_y;
                    if ((check_left_tile_and_center_height(check_x, (u16)check_y,
                                       motion->unk_0A.s) << 16) != 0) {
                        effect->unk_26 = 1;
                    }
                    if (effect->unk_26 == 0) {
                        if (find_first_entry_matching_keys(owner, (u16)(s8)effect->unk_4C.u,
                                          (u16)(s8)effect->unk_4D.u,
                                          motion->unk_0A.s) != 0) {
                            effect->unk_26 = 1;
                        }
                    }
                    if (effect->unk_26 == 0) {
                        floor_height = sample_terrain_surface_height(check_x, (u16)check_y,
                                              (s16)((u16)motion->unk_0A.s - 0x20));
                        if (floor_height >= 0x200) {
                            effect->unk_26 = 1;
                        } else if (floor_height > motion->unk_0A.s + 0x20) {
                            effect->unk_26 = 1;
                        } else if (floor_height < motion->unk_0A.s) {
                            effect->unk_26 = 1;
                        }
                    }
                }
                if (effect->unk_26 == 1) {
                    effect->unk_16.s = 10;
                    effect->unk_1E.s = 0;
                    motion->unk_10 = 0;
                    motion->unk_0C = 0;
                    object = effect->unk_30;
                    if (object == 0) {
                        return;
                    }
                    object_data = (S_func_810332A4_7 *)((u8 *)object + 0x20);
                    display = object->unk_0C;
                    transform = object->unk_08;
                    cleanup_mask = 0xFFEFFFFF;
                    state = object_data->unk_14;
                    state &= cleanup_mask;
                    object_data->unk_14 = state;
                    set_record_integer_tile_center(transform, display->unk_24, display->unk_25);
                    cycle_map_cell_flags(display->unk_24, display->unk_25,
                                  (object_data->unk_1C & 0x2000) ? 0x300 : 0x3000);
                    refresh_actor_proximity_state(object_data);
                    return;
                }

                if (effect->unk_2C == 0) {
                    new_object = find_nearby_eligible_entry(owner,
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
                    update_map_cell_flags_with_item_limit(display->unk_24, display->unk_25,
                                  (object_data->unk_1C & 0x2000) ? 0x300 : 0x3000);
                }
            }
        }
        if (effect->unk_2C != 0) {
            object = effect->unk_2C;
            display = object->unk_0C;
            transform = object->unk_08;
            object_data = (S_func_810332A4_7 *)((u8 *)object + 0x20);
            if ((((volatile S_func_810332A4_6 *)display)->unk_24 << 6) + 0x20 ==
                transform->unk_00.half.unk_02) {
                if ((((volatile S_func_810332A4_6 *)display)->unk_25 << 6) + 0x20 ==
                    transform->unk_04.half.unk_06) {
                    get_offset_map_cell_value_and_flags(display->unk_24, display->unk_25,
                                  effect->unk_1C, &collision_flags);
                    blocked = (collision_flags & 0x8400) != 0;
                    display->unk_24 += (u8)D_8017610C[effect->unk_1C].x;
                    display->unk_25 += (u8)D_8017610C[effect->unk_1C].y;
                    coord_base = (display->unk_24 << 6) + 0x20;
                    object_y = (((S_func_810332A4_6 *)display)->unk_25 << 6) + 0x20;

                    if (!blocked) {
                        if ((check_left_tile_and_center_height((u16)coord_base, (u16)object_y,
                                           transform->unk_0A.s) << 16) != 0) {
                            blocked = 1;
                        }
                    }
                    if (!blocked) {
                        if (find_first_entry_matching_keys(owner, display->unk_24,
                                          display->unk_25,
                                          motion->unk_0A.s) != 0) {
                            blocked = 1;
                        }
                    }
                    if (!blocked) {
                        floor_height = sample_terrain_surface_height((u16)coord_base, (u16)object_y,
                                              (s16)((u16)object_data->unk_88 - 0x20));
                        if (floor_height >= 0x200) {
                            blocked = 1;
                        } else if (floor_height > object_data->unk_88 + 0x20) {
                            blocked = 1;
                        } else if (floor_height < object_data->unk_88) {
                            blocked = 1;
                        }
                    }

                    if (find_nearby_eligible_entry(object_data, display->unk_24,
                                      display->unk_25, object_data->unk_88) != 0) {
                        blocked = 1;
                    }
                    if (blocked == 1) {
                        stop_mask = 0xFFEFFFFF;
                        object_data->unk_14 &= stop_mask;
                        display->unk_24 -=
                            (u8)D_8017610C[effect->unk_1C].x;
                        display->unk_25 -=
                            (u8)D_8017610C[effect->unk_1C].y;
                        set_record_integer_tile_center(transform, display->unk_24, ((S_func_810332A4_6 *)display)->unk_25);
                        cycle_map_cell_flags(display->unk_24, display->unk_25,
                                      (object_data->unk_1C & 0x2000) ? 0x300 : 0x3000);
                        refresh_actor_proximity_state(object_data);
                        effect->unk_16.s = 10;
                        effect->unk_1E.s = 0;
                        motion->unk_10 = 0;
                        motion->unk_0C = 0;
                        apply_attack_power_and_element_effects(object_data, 7, owner->unk_11, 10,
                                      owner->unk_2A, (u32)owner | 0xA0000000, 2);

                        new_object = effect->unk_30;
                        if (new_object == 0) {
                            return;
                        }
                        object = new_object;
                        object_data = (S_func_810332A4_7 *)((u8 *)object + 0x20);
                        display = object->unk_0C;
                        transform = object->unk_08;
                        object_data->unk_14 &= stop_mask;
                        set_record_integer_tile_center(transform, display->unk_24, display->unk_25);
                        cycle_map_cell_flags(display->unk_24, display->unk_25,
                                      (object_data->unk_1C & 0x2000) ? 0x300 : 0x3000);
                        refresh_actor_proximity_state(object_data);
                        return;
                    }
                }
            }
            object_tile_x = display->unk_24;
            if ((object_tile_x - D_8017610C[effect->unk_1C].x) * 64 + 0x20 !=
                transform->unk_00.half.unk_02 ||
                (display->unk_25 - D_8017610C[effect->unk_1C].y) * 64 + 0x20 !=
                transform->unk_04.half.unk_06) {
                floor_height = sample_terrain_surface_height((object_tile_x << 6) | 0x20,
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
                floor_height = sample_terrain_surface_height((display->unk_24 << 6) | 0x20,
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
            motion->unk_00.half.unk_02) {
            world_coord = tile_x << 6;
        } else {
            if ((effect->unk_4D.s - D_8017610C[effect->unk_1C].y) * 64 + 0x20 ==
                motion->unk_04.half.unk_06) {
                motion->unk_00.word += motion->unk_0C;
                motion->unk_04.word += motion->unk_10;
                return;
            }
            world_coord = tile_x << 6;
        }
        {
            coord_base = world_coord + 0x20;
            floor_x = coord_base & 0xFFE0;
            world_coord = effect->unk_4D.s << 6;
            world_coord += 0x20;
            floor_y = world_coord & 0xFFE0;
            floor_height = sample_terrain_surface_height(floor_x, floor_y, motion->unk_0A.s);
            if (motion->unk_0A.s < floor_height) {
                motion->unk_0A.u += 0x10;
            }
        }
        motion->unk_00.word += motion->unk_0C;
        motion->unk_04.word += motion->unk_10;
        return;

    case 10:
        for (burst_index = 0; burst_index < 16; burst_index++) {
            spawn_directional_particle(effect, motion, sprite);
        }
        for (burst_index = 0; burst_index < 16; burst_index++) {
            spawn_directional_effect(effect, motion, sprite);
        }
        play_sound_if_enabled(0x80B);
        effect->unk_1E.u = 0;
        effect->unk_16.u++;
        sprite->unk_14 |= 0x80;

    case 11:
        timer = effect->unk_1E.u + 1;
        effect->unk_1E.u = timer;
        delay_pending = (s16)timer < 10;
        if (delay_pending) {
            return;
        }
        effect->unk_1E.u = 0;
        effect->unk_16.u++;
        return;

    case 12:
        effect_owner->unk_AC = 0x4D;
        *(u16 *)((u8 *)effect - 2) |= 0x8000;
        object_flag_block.flags |= 0x8000;

    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    default:
        return;
    }
}
