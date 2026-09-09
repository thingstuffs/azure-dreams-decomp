#include "common.h"


extern void *jtbl_80024008[];
__asm__(".set jtbl_80024008, 0x80024008");

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

extern s32 D_8008346C[];
extern s32 D_800814A0[];
extern u8 D_8006CCD8[];
extern u8 D_8006CCE8[];
extern u8 D_800DDC40[];

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
void func_80024578(void *effect_data, void *position_data, void *render_data)
{
    S_func_80024578_1 *effect = effect_data;
    register S_func_80024578_2 *position ASM_REG("$22");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register S_func_80024578_3 *actor;
    register S_func_80024578_4 *render = render_data;
    void **state_table;
    register S_func_80024578_5 *work_base;
    S_func_80024578_6 *motion_data;
    S_func_80024578_6 *map_data;
    S_func_80024578_7 *origin_pos;
    void *target;
    s32 state;
    u16 frame;
    s32 index;
    register s32 delta_x ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 delta_y;
    s32 delta_z;
    u16 copied_z;
    u16 next_state;
    s32 x_base;
    register s32 y_base;
    u8 scratch[32];
    u16 last_tile_y;
    s16 travel_frames;
    s16 *delta_cursor;
    u32 page_base;
    register s16 final_floor ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    static void *const state_labels[] = {
        &&case_0, &&case_1_entry, &&case_7, &&case_motion_flags,
        &&case_1, &&case_10, &&case_2, &&case_3,
        &&case_4, &&case_5, &&case_6, &&case_7,
        &&case_8, &&case_9, &&case_10, &&case_11,
    };

    frame = effect->unk_10.u16;
    state = effect->unk_0A.s16;
    actor = effect->unk_00;
    position = position_data;
    effect->unk_10.u16 = (u16)(frame + 1);
    if ((u32)state >= 16U) {
        goto finish;
    }
    state_table = jtbl_80024008;
    (void)state_labels;
    goto *state_table[state];

case_0:
    effect->unk_10.u16 = 0;
    effect->unk_0A.u16 = (u16)(effect->unk_0A.u16 + 1);
    effect->unk_0E = (u16)((actor->unk_2A >> 9) & 7);
    render->unk_0C = 0x808080;
case_1_entry:
    work_base = (S_func_80024578_5 *)((u8 *)actor - 0x20);
    motion_data = work_base->unk_0C;
    if (func_8003DE58(motion_data->unk_08, motion_data, (s16 *)(scratch + 0x18), 0) == 0) {
        if ((((S_func_80024578_6 *)(work_base->unk_0C))->unk_14 & 0x8000) == 0) {
            goto finish;
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
            ASM_MEM_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
            {
                register u16 position_z ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                register u16 offset_z ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

                position_z = position->unk_08.parts_0A.unk_0A.u16;
                offset_z = (u16)DELTA(2);
                next_z = (u16)(position_z + offset_z);
            }
        } else {
            next_z = (u16)(copied_z - 64);
        }
        position->unk_08.parts_0A.unk_0A.u16 = next_z;
    }
    if ((((S_func_80024578_8 *)(effect->unk_04))->unk_00 & 0x80) == 0) {
        goto finish;
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

        delta_x = work_base->unk_00.parts_02.unk_02.s16;
        delta_x -= position->unk_00.parts_02.unk_02.s16;
        if (delta_x < 0) delta_x = -delta_x;
        DELTA(0) = (s16)delta_x;
        {
            s32 distance_y;
            register s32 position_y ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            distance_y = work_base->unk_04.parts_06.unk_06.s16;
            position_y = position->unk_04.parts_06.unk_06.s16;
            distance_y -= position_y;
            if (distance_y < 0) distance_y = -distance_y;
            DELTA(1) = (s16)distance_y;
        }
        {
            s32 distance_z;
            register s32 position_z ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            position_z = position->unk_08.parts_0A.unk_0A.s16;
            distance_z = ((S_func_80024578_3 *)(actor->unk_60))->unk_88.s16;
            ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            delta_cursor = (s16 *)(scratch + 2);
            ASM_KEEP(delta_cursor);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            distance_z -= position_z;
            if (distance_z < 0) distance_z = -distance_z;
            DELTA(2) = (s16)distance_z;
        }
        effect->unk_12 = DELTA(0);
        index = 1;
        do {
            if (((S_func_80024578_9 *)(delta_cursor))->unk_18.s16 > effect->unk_12) {
                effect->unk_12 = ((S_func_80024578_9 *)(delta_cursor))->unk_18.u16;
            }
            index++;
            delta_cursor++;
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
        next_state = (u16)(effect->unk_0A.u16 + 1);
        goto set_state;
    }

    index = 0;
    map_data = work_base->unk_0C;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    page_base = 0x80070000;
    ASM_KEEP(page_base);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    {
        s32 tile_x;
        s32 tile_y;
        register s32 last_tile_x;
        u16 tile_y_bits;
        s32 floor_x;
        register s32 floor_limit ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        s32 floor_y;
        s32 signed_tile_x;
        s32 signed_tile_y;
        s32 x_adjust;
        s32 y_adjust;
        s16 *x_adjust_table;

        tile_x = map_data->unk_24;
        tile_y = map_data->unk_25;
        last_tile_x = tile_x;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        last_tile_y = (u16)tile_y;
        do {
            signed_tile_x = (s16)tile_x;
            signed_tile_y = (s16)tile_y;
            if ((func_800A44E0((signed_tile_x << 6) & 0xFFC0, (signed_tile_y << 6) & 0xFFC0,
                               actor->unk_88.s16,
                               (s16)(effect->unk_0E << 9)) << 16) == 0) {
                s16 floor = func_800BCB04(
                    ((signed_tile_x + ((s16 *)D_8006CCD8)[(s16)effect->unk_0E]) << 6) + 0x20 & 0xFFE0,
                    ((signed_tile_y + ((s16 *)D_8006CCE8)[(s16)effect->unk_0E]) << 6) + 0x20 & 0xFFE0,
                    (s16)(actor->unk_88.s16 - 0x20));
                if ((floor < 513) && ((s16)(floor - actor->unk_88.s16) >= -63)) {
                    s32 next_tile_x;
                    register s32 next_tile_y ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */

                    index++;
                    next_tile_x = tile_x + ((u16 *)D_8006CCD8)[(s16)effect->unk_0E];
                    tile_x = next_tile_x;
                    ASM_KEEP_NV(tile_x);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                    next_tile_y = tile_y + ((u16 *)D_8006CCE8)[(s16)effect->unk_0E];
                    tile_y = next_tile_y;
                    last_tile_y = (u16)next_tile_y;
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
        floor_x = (x_base + 0x20) & 0xFFE0;
        x_adjust_table = (s16 *)D_8006CCD8;
        ASM_CLOBBER("$6");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        floor_limit = -0x400;
        index = 1;
        ASM_KEEP(index);   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
        tile_y_bits = last_tile_y;
        y_base = (s32)tile_y_bits << 16;
        y_base >>= 10;
        floor_y = y_base + 0x20;
        x_adjust = x_adjust_table[(s16)effect->unk_0E];
        work_base->unk_00.parts_02.unk_02.u16 = (u16)(x_base + ((x_adjust + 1) << 5));
        y_adjust = ((s16 *)D_8006CCE8)[(s16)effect->unk_0E];
        floor_y &= 0xFFE0;
        work_base->unk_04.parts_06.unk_06.u16 = (u16)(y_base + ((y_adjust + 1) << 5));
        final_floor = func_800BCB04(floor_x, floor_y, floor_limit);
        {
            register s32 expanded_floor ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
            s32 widened_y;
            register s32 position_y ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            s16 *delta_scan = (s16 *)(scratch + 2);

            work_base->unk_08.parts_0A.unk_0A = final_floor;
            expanded_floor = (s32)final_floor << 16;
            ASM_KEEP(expanded_floor);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
            delta_x = (s16)work_base->unk_00.parts_02.unk_02.u16 - position->unk_00.parts_02.unk_02.s16;
            if (delta_x < 0) delta_x = -delta_x;
            DELTA(0) = (s16)delta_x;
            widened_y = work_base->unk_04.parts_06.unk_06.u16;
            position_y = position->unk_04.parts_06.unk_06.s16;
            ASM_KEEP_DEP_NV(widened_y, position_y);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
            widened_y <<= 16;
            widened_y >>= 16;
            widened_y -= position_y;
            if (widened_y < 0) widened_y = -widened_y;
            DELTA(1) = (s16)widened_y;
            expanded_floor >>= 16;
            expanded_floor -= position->unk_08.parts_0A.unk_0A.s16;
            if (expanded_floor < 0) expanded_floor = -expanded_floor;
            DELTA(2) = (s16)expanded_floor;
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
    ASM_CLOBBER("$3");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    next_state = 11;
set_state:
    effect->unk_0A.u16 = next_state;
    effect->unk_10.u16 = 0;
    ASM_CLOBBER("$4");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    func_800243CC(effect, position);
    goto finish;

case_motion_flags:
    position->unk_00.s32 += position->unk_0C;
    position->unk_04.s32 += position->unk_10;
    position->unk_08.s32 += position->unk_14;
    if (effect->unk_10.s16 < effect->unk_12) {
        goto finish;
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

case_1:
    if (func_80053EF0(4) == 1) {
        goto advance_state;
    }
    goto finish;

case_2:
    ((S_func_80024578_2 *)(effect->unk_20))->unk_08.parts_0A.unk_0A.u16 =
        (u16)(((S_func_80024578_2 *)(effect->unk_20))->unk_08.parts_0A.unk_0A.u16 - effect->unk_10.u16);
    ((S_func_80024578_3 *)(effect->unk_1C))->unk_2A =
        (u16)(((S_func_80024578_3 *)(effect->unk_1C))->unk_2A + 0x200);
    if (effect->unk_10.s16 >= 28) {
        register S_func_80024578_4 *target_render ASM_REG("$2") = effect->unk_24;   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */

        target_render->unk_1A = (u16)(target_render->unk_1A + 0x800);
        goto advance_state;
    }
    goto finish;

case_3:
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
        register s32 effect_size ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        register s32 effect_id ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

        height_base = D_800DDC40;
        owner = effect->unk_1C;
        target_pos = effect->unk_20;
        height_entry = (S_func_80024578_10 *)(height_base + owner->unk_13);
        effect_size = 16;
        if (target_pos->unk_08.parts_0A.unk_0A.s16 >=
            effect->unk_16.s16 - height_entry->unk_00) {
            effect_id = 8;
            ASM_CLOBBER("$16");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
            index = 0;
            max_height = effect->unk_16.u16;
            target_pos->unk_08.parts_0A.unk_0A.u16 =
                (u16)(max_height - height_entry->unk_00);
            func_800419EC(effect_id, effect_size);
case_3_loop:
            func_80024138(effect);
            index++;
            if (index >= 8) {
                goto advance_state;
            }
            goto case_3_loop;
        }
    }
    goto finish;

case_4:
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
        goto finish;
    }
    goto advance_state;

case_5:
    if (effect->unk_10.s16 < 4) {
        goto finish;
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

case_6:
    if (effect->unk_14.s16 != 0) {
        goto finish;
    }
    D_8008346C[0] = 0;
    ((S_func_80024578_12 *)((u8 *)(effect) - 2))->unk_00 |= 0x8000;
    D_800814A0[0] |= 0x8000;
    goto finish;

case_7:
    func_800243CC(effect, position);
    if (effect->unk_10.s16 < 15) {
        goto finish;
    }
    {
        void *saved_height = ((S_func_80024578_2 *)(effect->unk_20))->unk_08.ptr;

        effect->unk_0A.u16 = (u16)(effect->unk_0A.u16 + 1);
        effect->unk_10.u16 = 0;
        effect->unk_28.ptr = saved_height;
    }
    goto finish;

case_8:
    position->unk_00.s32 += position->unk_0C;
    position->unk_04.s32 += position->unk_10;
    position->unk_08.s32 += position->unk_14;
    if (effect->unk_10.s16 < effect->unk_12) {
        goto finish;
    }
    func_800A56E0(0x300);
    func_800542BC();
    goto advance_state;

case_9:
    if (func_80053EF0(4) != 1) {
        goto finish;
    }
    goto advance_state;

case_10:
    if (effect->unk_10.s16 < 7) {
        goto finish;
    }

advance_state:
    effect->unk_0A.u16 = (u16)(effect->unk_0A.u16 + 1);
    effect->unk_10.u16 = 0;
    goto finish;

case_11:
    if (effect->unk_10.s16 >= 28) {
        func_800A56E0(116);
        effect->unk_0A.u16 = 10;
        effect->unk_10.u16 = 0;
    }
    goto finish;

finish:
    effect->unk_14.u16 = 0;
}
