#include "shared/entity_height_offsets.h"
#include "common.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
extern int abs(int);


extern s32 func_8003DE58(void *, void *, s16 *, s32);
extern s32 func_800A44E0(s32, s32, s16, s32);
extern s16 func_800BCB04(s32, s32, s16);
extern void func_80024138(void *);
extern void func_800243CC(void *, void *);
extern void func_800419EC(u16, u16);
extern s32 func_80053EF0(s32);
extern void func_800542BC(void);
extern void func_8009CE1C(void *, s32, u8, s32, s32, void *, s32);
extern void func_800A56E0(s32);


typedef struct {
    s32 x;
    s32 y;
    s32 z;
} Coord;

typedef struct S_func_80024578_1 {
    void *unk_00;
    void *unk_04;
    u8 pad_08[0x1];
    u8 unk_09;
    union {
        s16 s16;
        u16 u16;
    } unk_0A;
    u8 pad_0C[0x2];
    u16 unk_0E;
    union {
        s16 s16;
        u16 u16;
    } unk_10;
    s16 unk_12;
    union {
        s16 s16;
        u16 u16;
    } unk_14;
    union {
        s16 s16;
        u16 u16;
    } unk_16;
    u16 unk_18;
    union {
        s16 s16;
        u16 u16;
    } unk_1A;
    void *unk_1C;
    void *unk_20;
    void *unk_24;
    union {
        s32 s32;
        void *ptr;
    } unk_28;
} S_func_80024578_1;

typedef struct S_func_80024578_2 {
    union {
        s32 s32;
        struct {
            u8 pad_00[0x2];
            union {
                s16 s16;
                u16 u16;
            } unk_02;
        } parts_02;
    } unk_00;
    union {
        s32 s32;
        struct {
            u8 pad_04[0x2];
            union {
                s16 s16;
                u16 u16;
            } unk_06;
        } parts_06;
    } unk_04;
    union {
        s32 s32;
        void *ptr;
        struct {
            u8 pad_08[0x2];
            union {
                s16 s16;
                u16 u16;
            } unk_0A;
        } parts_0A;
    } unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_func_80024578_2;

typedef struct S_func_80024578_3 {
    u8 pad_00[0x13];
    u8 unk_13;
    s32 unk_14;
    u8 pad_18[0x12];
    u16 unk_2A;
    u8 pad_2C[0x34];
    void *unk_60;
    u8 pad_64[0x24];
    union {
        s16 s16;
        u16 u16;
    } unk_88;
} S_func_80024578_3;

typedef struct S_func_80024578_4 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u8 pad_10[0xA];
    u16 unk_1A;
} S_func_80024578_4;

typedef struct S_func_80024578_5 {
    union {
        s32 s32;
        struct {
            u8 pad_00[0x2];
            union {
                s16 s16;
                u16 u16;
            } unk_02;
        } parts_02;
    } unk_00;
    union {
        s32 s32;
        struct {
            u8 pad_04[0x2];
            union {
                s16 s16;
                u16 u16;
            } unk_06;
        } parts_06;
    } unk_04;
    union {
        s32 s32;
        void *ptr;
        struct {
            u8 pad_08[0x2];
            s16 unk_0A;
        } parts_0A;
    } unk_08;
    void *unk_0C;
} S_func_80024578_5;

typedef struct S_func_80024578_6 {
    u8 pad_00[0x8];
    void *unk_08;
    u8 pad_0C[0x8];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_func_80024578_6;

typedef struct S_func_80024578_7 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_func_80024578_7;

typedef struct S_func_80024578_8 {
    u16 unk_00;
} S_func_80024578_8;

typedef struct S_func_80024578_9 {
    u8 pad_00[0x18];
    union {
        s16 s16;
        u16 u16;
    } unk_18;
} S_func_80024578_9;

typedef struct S_func_80024578_10 {
    u8 unk_00;
} S_func_80024578_10;

typedef struct S_func_80024578_11 {
    u8 pad_00[0x8];
    void *unk_08;
    void *unk_0C;
} S_func_80024578_11;

typedef struct S_func_80024578_12 {
    u16 unk_00;
} S_func_80024578_12;

typedef struct S_func_80024578_13 {
    u8 pad_00[0x18];
    s16 unk_18[3];
} S_func_80024578_13;

#define DELTA(i) (((S_func_80024578_13 *)scratch)->unk_18[(i)])

/* Updates effect movement, target spinning, and completion across animation states. */
void func_80024578(S_func_80024578_1 *effect, S_func_80024578_2 *position, void *render_data)
{
    register S_func_80024578_3 *actor;
    register S_func_80024578_4 *render = render_data;
    register S_func_80024578_5 *work_base;
    S_func_80024578_6 *motion_data;
    S_func_80024578_6 *map_data;
    S_func_80024578_7 *origin_pos;
    void *target;
    s32 state;
    u16 frame;
    s32 index;
    s32 delta_x;
    s32 abs_delta_x;
    s32 abs_delta_x_2;
    s32 delta_y;
    s32 delta_z;
    u16 copied_z;

    s32 x_base;
    register s32 y_base;
    u8 scratch[32];
    u16 last_tile_y;
    s16 travel_frames;
    s16 *delta_cursor;
    u32 page_base;
    s16 final_floor;
    s32 expanded_floor;
    S_func_80024578_4 *finished_render;

    frame = effect->unk_10.u16;
    state = effect->unk_0A.s16;
    actor = effect->unk_00;
    effect->unk_10.u16 = (u16)(frame + 1);
    switch (state) {
    case 0:
        effect->unk_10.u16 = 0;
        effect->unk_0A.u16 = (u16)(effect->unk_0A.u16 + 1);
        effect->unk_0E = (u16)((actor->unk_2A >> 9) & 7);
        render->unk_0C = 0x808080;
    case 1:
        work_base = (S_func_80024578_5 *)((u8 *)actor - 0x20);
        motion_data = work_base->unk_0C;
        if (func_8003DE58(motion_data->unk_08, motion_data, (s16 *)(scratch + 0x18), 0) == 0) {
            if ((((S_func_80024578_6 *)(work_base->unk_0C))->unk_14 & 0x8000) == 0) {
                break;
            }
        }
        origin_pos = work_base->unk_08.ptr;
        position->unk_00.parts_02.unk_02.u16 = origin_pos->unk_02;
        position->unk_04.parts_06.unk_06.u16 = origin_pos->unk_06;
        copied_z = origin_pos->unk_0A;
        position->unk_08.parts_0A.unk_0A.u16 = copied_z;
        {
            u16 next_z;

            if ((((S_func_80024578_6 *)(work_base->unk_0C))->unk_14 & 0x8000) == 0) {
                position->unk_00.parts_02.unk_02.u16 = (u16)(position->unk_00.parts_02.unk_02.u16 + DELTA(0));
                position->unk_04.parts_06.unk_06.u16 = (u16)(position->unk_04.parts_06.unk_06.u16 + DELTA(1));
                {
                    u16 position_z;
                    s32 offset_z;

                    position_z = position->unk_08.parts_0A.unk_0A.u16;
                    offset_z = (u16)DELTA(2);
                    next_z = (u16)(position_z + offset_z);
                }
                position->unk_08.parts_0A.unk_0A.u16 = next_z;
            } else {
                next_z = (u16)(copied_z - 64);
                position->unk_08.parts_0A.unk_0A.u16 = next_z;
            }
        }
        if ((((S_func_80024578_8 *)(effect->unk_04))->unk_00 & 0x80) == 0) {
            break;
        }
        target = actor->unk_60;
        index = 1;
        if (target != 0) {
            work_base = ((S_func_80024578_11 *)((u8 *)(actor->unk_60) - 0x20))->unk_08;
            effect->unk_20 = work_base;
            effect->unk_1C = actor->unk_60;
            effect->unk_24 =
                ((S_func_80024578_11 *)((u8 *)(actor->unk_60) - 0x20))->unk_0C;
            effect->unk_16.u16 = ((S_func_80024578_3 *)(effect->unk_1C))->unk_88.u16;
            effect->unk_18 = ((S_func_80024578_3 *)(effect->unk_1C))->unk_2A;

            abs_delta_x = abs((work_base->unk_00.parts_02.unk_02.s16) - (position->unk_00.parts_02.unk_02.s16));
            DELTA(0) = (s16)abs_delta_x;
            {
                s32 distance_y;
                s32 position_y;
                distance_y = work_base->unk_04.parts_06.unk_06.s16;
                position_y = position->unk_04.parts_06.unk_06.s16;
                distance_y -= position_y;
                distance_y = abs(distance_y);
                DELTA(1) = (s16)distance_y;
            }
            {
                s32 distance_z;
                s32 position_z;
                position_z = position->unk_08.parts_0A.unk_0A.s16;
                distance_z = ((S_func_80024578_3 *)(actor->unk_60))->unk_88.s16;

                delta_cursor = (s16 *)(scratch + 2);
                distance_z -= position_z;
                distance_z = abs(distance_z);
                DELTA(2) = (s16)distance_z;
            }
            effect->unk_12 = DELTA(0);
            index = 1;
            do {
                {
                    if (((S_func_80024578_9 *)(delta_cursor))->unk_18.s16 > effect->unk_12) {
                        effect->unk_12 = ((S_func_80024578_9 *)(delta_cursor))->unk_18.u16;
                    }
                    index++;
                    delta_cursor++;
                }
            } while (index < 3);
            travel_frames = (s16)(((u16)effect->unk_12 << 16) >> 20);
            effect->unk_12 = travel_frames;
            if (travel_frames == 0) {
                effect->unk_12 = 1;
            }
            position->unk_0C =
                (work_base->unk_00.s32 - position->unk_00.s32) / effect->unk_12;
            position->unk_10 =
                (work_base->unk_04.s32 - position->unk_04.s32) / effect->unk_12;
            position->unk_14 =
                (((s32)((S_func_80024578_3 *)(actor->unk_60))->unk_88.s16 << 16) -
                 position->unk_08.s32) / effect->unk_12;
            effect->unk_0A.u16 = (u16)(effect->unk_0A.u16 + 1);
            goto set_state;
        }

        index = 0;
        map_data = (*(void **)((u8 *)work_base + 0xC));
        page_base = 0x80070000;
        {
            u16 tile_x;
            s32 tile_y;
            u16 last_tile_x;
            u16 tile_y_bits;
            s32 floor_x;
            s32 floor_limit;
            s32 floor_y;
            s32 signed_tile_x;
            s32 signed_tile_y;
            s32 x_adjust;
            s32 y_adjust;
            s16 *x_adjust_table;

            tile_y = map_data->unk_25;
            tile_x = map_data->unk_24;
            last_tile_y = (u16)tile_y;
            last_tile_x = tile_x;
            do {
                signed_tile_x = (s16)tile_x;
                signed_tile_y = (s16)tile_y;
                if ((func_800A44E0((signed_tile_x << 6) & 0xFFC0, (signed_tile_y << 6) & 0xFFC0,
                                   actor->unk_88.s16,
                                   (s16)(effect->unk_0E << 9)) << 16) == 0) {
                    s16 floor = func_800BCB04(
                        ((signed_tile_x + ((s16 *)((u8 *)dirStepX))[(s16)effect->unk_0E]) << 6) + 0x20 & 0xFFE0,
                        ((signed_tile_y + ((s16 *)((u8 *)dirStepY))[(s16)effect->unk_0E]) << 6) + 0x20 & 0xFFE0,
                        (s16)(actor->unk_88.s16 - 0x20));
                    if ((floor < 513) && ((s16)(floor - actor->unk_88.s16) >= -63)) {
                        u16 next_tile_x;
                        s32 next_tile_y;

                        index++;
                        next_tile_x = tile_x + ((u16 *)((u8 *)dirStepX))[(s16)effect->unk_0E];
                        tile_x = next_tile_x;
                        next_tile_y = tile_y + ((u16 *)((u8 *)dirStepY))[(s16)effect->unk_0E];
                        last_tile_y = (u16)next_tile_y;
                        tile_y = next_tile_y;
                        last_tile_x = next_tile_x;
                        if (index < 8) {
                            continue;
                        }
                    }
                }
                break;
            } while (index < 8);

            work_base = (S_func_80024578_5 *)scratch;
            x_base = (last_tile_x << 16) >> 10;
            floor_x = (x_base + 0x20);
            floor_x &= 0xFFE0;
            x_adjust_table = (s16 *)((u8 *)dirStepX);
            floor_limit = -0x400;

            tile_y_bits = last_tile_y;
            y_base = (s32)tile_y_bits << 16;
            y_base >>= 10;
            floor_y = y_base + 0x20;
            x_adjust = x_adjust_table[(s16)effect->unk_0E];
            work_base->unk_00.parts_02.unk_02.u16 = (u16)(x_base + ((x_adjust + 1) << 5));
            y_adjust = ((s16 *)((u8 *)dirStepY))[(s16)effect->unk_0E];
            floor_y &= 0xFFE0;
            work_base->unk_04.parts_06.unk_06.u16 = (u16)(y_base + ((y_adjust + 1) << 5));
            final_floor = func_800BCB04(floor_x, floor_y, floor_limit);
            index = 1;
            {
                s32 widened_y;
                s32 position_y;
                s16 *delta_scan = (s16 *)(scratch + 2);

                work_base->unk_08.parts_0A.unk_0A = final_floor;
                expanded_floor = (s32)final_floor << 16;
                abs_delta_x_2 = abs((s16)work_base->unk_00.parts_02.unk_02.u16 - position->unk_00.parts_02.unk_02.s16);
                DELTA(0) = (s16)abs_delta_x_2;
                widened_y = work_base->unk_04.parts_06.unk_06.u16;
                position_y = position->unk_04.parts_06.unk_06.s16;
                widened_y <<= 16;
                widened_y >>= 16;
                widened_y -= position_y;
                widened_y = abs(widened_y);
                DELTA(1) = (s16)widened_y;
                expanded_floor >>= 16;
                expanded_floor -= position->unk_08.parts_0A.unk_0A.s16;
                DELTA(2) = (s16)(abs(expanded_floor));
                effect->unk_12 = DELTA(0);
                do {
                    if (((S_func_80024578_9 *)(delta_scan))->unk_18.s16 > effect->unk_12) {
                        effect->unk_12 = ((S_func_80024578_9 *)(delta_scan))->unk_18.s16;
                    }
                    index++;
                    delta_scan++;
                } while (index < 3);
            }
        }
        travel_frames = (s16)(((u16)effect->unk_12 << 16) >> 20);
        effect->unk_12 = travel_frames;
        if (travel_frames == 0) {
            effect->unk_12 = 1;
        }
        position->unk_0C =
            (work_base->unk_00.s32 - position->unk_00.s32) / effect->unk_12;
        position->unk_10 =
            (work_base->unk_04.s32 - position->unk_04.s32) / effect->unk_12;
        position->unk_14 =
            (work_base->unk_08.s32 - position->unk_08.s32) / effect->unk_12;

        effect->unk_0A.u16 = 11;
set_state:
        effect->unk_10.u16 = 0;

        func_800243CC(effect, position);
        break;

    case 3:
        position->unk_00.s32 += position->unk_0C;
        position->unk_04.s32 += position->unk_10;
        position->unk_08.s32 += position->unk_14;
        if (effect->unk_10.s16 < effect->unk_12) {
            break;
        }
        func_800A56E0(0x300);
        func_800542BC();
        {
            S_func_80024578_3 *owner = effect->unk_1C;
            s32 flags;

            effect->unk_1A.u16 = 0;
            flags = owner->unk_14;
            if ((flags & 0x100000) != 0) {
                goto advance_state;
            }
            owner->unk_14 = flags | 0x100000;
            effect->unk_1A.u16 = 1;
        }
        goto advance_state;

    case 4:
        if (func_80053EF0(4) == 1) {
            goto advance_state;
        }
        break;

    case 6:
        ((S_func_80024578_2 *)(effect->unk_20))->unk_08.parts_0A.unk_0A.u16 =
            (u16)(((S_func_80024578_2 *)(effect->unk_20))->unk_08.parts_0A.unk_0A.u16 - effect->unk_10.u16);
        ((S_func_80024578_3 *)(effect->unk_1C))->unk_2A =
            (u16)(((S_func_80024578_3 *)(effect->unk_1C))->unk_2A + 0x200);
        if (effect->unk_10.s16 >= 28) {
            finished_render = effect->unk_24;

            state = finished_render->unk_1A;
            state += 0x800;
            finished_render->unk_1A = state;
            goto advance_state;
        }
        break;

    case 7:
        ((S_func_80024578_2 *)(effect->unk_20))->unk_08.parts_0A.unk_0A.u16 =
            (u16)(((S_func_80024578_2 *)(effect->unk_20))->unk_08.parts_0A.unk_0A.u16 + effect->unk_10.s16 * 4);
        ((S_func_80024578_3 *)(effect->unk_1C))->unk_2A =
            (u16)(((S_func_80024578_3 *)(effect->unk_1C))->unk_2A + 0x200);
        {
            u8 *height_base;
            S_func_80024578_2 *target_pos;
            S_func_80024578_10 *height_entry;
            u16 max_height;
            S_func_80024578_3 *owner;
            s32 effect_size;

            height_base = D_800DDC40;
            owner = effect->unk_1C;
            target_pos = effect->unk_20;
            height_entry = (S_func_80024578_10 *)(height_base + owner->unk_13);
            effect_size = 16;
            if (target_pos->unk_08.parts_0A.unk_0A.s16 >=
                effect->unk_16.s16 - height_entry->unk_00) {
                delta_x = 8;
                max_height = effect->unk_16.u16;
                target_pos->unk_08.parts_0A.unk_0A.u16 =
                    (u16)(max_height - height_entry->unk_00);
                func_800419EC(delta_x, effect_size);
                index = 0;
case_3_loop:
                func_80024138(effect);
                index++;
                if (index >= 8) {
                    goto advance_state;
                }
                goto case_3_loop;
            }
        }
        break;

    case 8:
        ((S_func_80024578_3 *)(effect->unk_1C))->unk_2A =
            (u16)(((S_func_80024578_3 *)(effect->unk_1C))->unk_2A + 0x200);
        index = 0;
        if (effect->unk_10.s16 == 2) {
            do {
                func_80024138(effect);
                index++;
            } while (index < 8);
        }
        if (effect->unk_10.s16 < 12) {
            break;
        }
        goto advance_state;

    case 9:
        if (effect->unk_10.s16 < 4) {
            break;
        }
        ((S_func_80024578_2 *)(effect->unk_20))->unk_08.s32 = effect->unk_28.s32;
        ((S_func_80024578_3 *)(effect->unk_1C))->unk_2A = effect->unk_18;
        if (effect->unk_1A.s16 != 0) {
            ((S_func_80024578_3 *)(effect->unk_1C))->unk_14 &= 0xFFEFFFFF;
        }
        ((S_func_80024578_4 *)(effect->unk_24))->unk_1A -= 0x800;
        func_8009CE1C(actor->unk_60, 24, effect->unk_09, 4,
                      (s16)(effect->unk_0E << 9), actor, 1);
        goto advance_state;

    case 10:
        if (effect->unk_14.s16 != 0) {
            break;
        }
        dungeonStatus.unk_0C = 0;
        ((S_func_80024578_12 *)((u8 *)(effect) - 2))->unk_00 |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
        break;

    case 2:
    case 11:
        func_800243CC(effect, position);
        if (effect->unk_10.s16 < 15) {
            break;
        }
        {
            void *saved_height = ((S_func_80024578_2 *)(effect->unk_20))->unk_08.ptr;

            effect->unk_0A.u16 = (u16)(effect->unk_0A.u16 + 1);
            effect->unk_10.u16 = 0;
            effect->unk_28.ptr = saved_height;
        }
        break;

    case 12:
        position->unk_00.s32 += position->unk_0C;
        position->unk_04.s32 += position->unk_10;
        position->unk_08.s32 += position->unk_14;
        if (effect->unk_10.s16 < effect->unk_12) {
            break;
        }
        func_800A56E0(0x300);
        func_800542BC();
        goto advance_state;

    case 13:
        if (func_80053EF0(4) != 1) {
            break;
        }
        goto advance_state;

    case 5:
    case 14:
        if (effect->unk_10.s16 < 7) {
            break;
        }

advance_state:
        effect->unk_0A.u16 = (u16)(effect->unk_0A.u16 + 1);
        effect->unk_10.u16 = 0;
        break;

    case 15:
        if (effect->unk_10.s16 >= 28) {
            func_800A56E0(116);
            effect->unk_0A.u16 = 10;
            effect->unk_10.u16 = 0;
        }
        break;
    }

    effect->unk_14.u16 = 0;
}
