#include "common.h"

#define FIELD(p, t, o) (*(t *)((u8 *)(p) + (o)))
#define LOCAL(t, o) FIELD(scratch, t, o)
#define DELTA(i) FIELD(scratch, s16, 0x18 + ((i) * 2))

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

/* Updates effect movement, target spinning, and completion across animation states. */
void func_80024578(void *effect_data, void *position_data, void *render_data)
{
    void *effect = effect_data;
    register void *position ASM_REG("$22");
    register void *actor;
    register void *render = render_data;
    void **state_table;
    register void *work_base;
    void *motion_data;
    void *map_data;
    void *origin_pos;
    void *target;
    s32 state;
    u16 frame;
    s32 index;
    register s32 delta_x ASM_REG("$4");
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
    register s16 final_floor ASM_REG("$2");
    static void *const state_labels[] = {
        &&case_0, &&case_1_entry, &&case_7, &&case_motion_flags,
        &&case_1, &&case_10, &&case_2, &&case_3,
        &&case_4, &&case_5, &&case_6, &&case_7,
        &&case_8, &&case_9, &&case_10, &&case_11,
    };

    frame = FIELD(effect, u16, 0x10);
    state = FIELD(effect, s16, 0xA);
    actor = FIELD(effect, void *, 0);
    position = position_data;
    FIELD(effect, u16, 0x10) = (u16)(frame + 1);
    if ((u32)state >= 16U) {
        goto finish;
    }
    state_table = jtbl_80024008;
    (void)state_labels;
    goto *state_table[state];

case_0:
    FIELD(effect, u16, 0x10) = 0;
    FIELD(effect, u16, 0xA) = (u16)(FIELD(effect, u16, 0xA) + 1);
    FIELD(effect, u16, 0xE) = (u16)((FIELD(actor, u16, 0x2A) >> 9) & 7);
    FIELD(render, s32, 0xC) = 0x808080;
case_1_entry:
    work_base = (u8 *)actor - 0x20;
    motion_data = FIELD(work_base, void *, 0xC);
    if (func_8003DE58(FIELD(motion_data, void *, 8), motion_data, (s16 *)(scratch + 0x18), 0) == 0) {
        if ((FIELD(FIELD(work_base, void *, 0xC), u16, 0x14) & 0x8000) == 0) {
            goto finish;
        }
    }
    origin_pos = FIELD(work_base, void *, 8);
    FIELD(position, u16, 2) = FIELD(origin_pos, u16, 2);
    FIELD(position, u16, 6) = FIELD(origin_pos, u16, 6);
    copied_z = FIELD(origin_pos, u16, 0xA);
    FIELD(position, u16, 0xA) = copied_z;
    {
        u16 next_z;

        if ((FIELD(FIELD(work_base, void *, 0xC), u16, 0x14) & 0x8000) == 0) {
            FIELD(position, u16, 2) = (u16)(FIELD(position, u16, 2) + DELTA(0));
            FIELD(position, u16, 6) = (u16)(FIELD(position, u16, 6) + DELTA(1));
            ASM_MEM_BARRIER();
            {
                register u16 position_z ASM_REG("$2");
                register u16 offset_z ASM_REG("$3");

                position_z = FIELD(position, u16, 0xA);
                offset_z = (u16)DELTA(2);
                next_z = (u16)(position_z + offset_z);
            }
        } else {
            next_z = (u16)(copied_z - 64);
        }
        FIELD(position, u16, 0xA) = next_z;
    }
    if ((FIELD(FIELD(effect, void *, 4), u16, 0) & 0x80) == 0) {
        goto finish;
    }
    target = FIELD(actor, void *, 0x60);
    index = 1;
    if (target != 0) {
        work_base = FIELD(FIELD(actor, void *, 0x60), void *, -0x18);
        FIELD(effect, void *, 0x20) = work_base;
        FIELD(effect, void *, 0x1C) = FIELD(actor, void *, 0x60);
        FIELD(effect, void *, 0x24) =
            FIELD(FIELD(actor, void *, 0x60), void *, -0x14);
        FIELD(effect, u16, 0x16) = FIELD(FIELD(effect, void *, 0x1C), u16, 0x88);
        FIELD(effect, u16, 0x18) = FIELD(FIELD(effect, void *, 0x1C), u16, 0x2A);

        delta_x = FIELD(work_base, s16, 2);
        delta_x -= FIELD(position, s16, 2);
        if (delta_x < 0) delta_x = -delta_x;
        DELTA(0) = (s16)delta_x;
        {
            s32 distance_y;
            register s32 position_y ASM_REG("$3");
            distance_y = FIELD(work_base, s16, 6);
            position_y = FIELD(position, s16, 6);
            distance_y -= position_y;
            if (distance_y < 0) distance_y = -distance_y;
            DELTA(1) = (s16)distance_y;
        }
        {
            s32 distance_z;
            register s32 position_z ASM_REG("$3");
            position_z = FIELD(position, s16, 0xA);
            distance_z = FIELD(FIELD(actor, void *, 0x60), s16, 0x88);
            ASM_SCHED_BARRIER();
            delta_cursor = (s16 *)(scratch + 2);
            ASM_KEEP(delta_cursor);
            distance_z -= position_z;
            if (distance_z < 0) distance_z = -distance_z;
            DELTA(2) = (s16)distance_z;
        }
        FIELD(effect, s16, 0x12) = DELTA(0);
        index = 1;
        do {
            if (FIELD(delta_cursor, s16, 0x18) > FIELD(effect, s16, 0x12)) {
                FIELD(effect, s16, 0x12) = FIELD(delta_cursor, u16, 0x18);
            }
            index++;
            delta_cursor++;
        } while (index < 3);
        travel_frames = (s16)(((u16)FIELD(effect, s16, 0x12) << 16) >> 20);
        FIELD(effect, s16, 0x12) = travel_frames;
        if (travel_frames == 0) {
            FIELD(effect, s16, 0x12) = 1;
        }
        FIELD(position, s32, 0xC) =
            (FIELD(work_base, s32, 0) - FIELD(position, s32, 0)) / FIELD(effect, s16, 0x12);
        FIELD(position, s32, 0x10) =
            (FIELD(work_base, s32, 4) - FIELD(position, s32, 4)) / FIELD(effect, s16, 0x12);
        FIELD(position, s32, 0x14) =
            (((s32)FIELD(FIELD(actor, void *, 0x60), s16, 0x88) << 16) -
             FIELD(position, s32, 8)) / FIELD(effect, s16, 0x12);
        next_state = (u16)(FIELD(effect, u16, 0xA) + 1);
        goto set_state;
    }

    index = 0;
    map_data = FIELD(work_base, void *, 0xC);
    ASM_SCHED_BARRIER();
    page_base = 0x80070000;
    ASM_KEEP(page_base);
    {
        s32 tile_x;
        s32 tile_y;
        register s32 last_tile_x;
        u16 tile_y_bits;
        s32 floor_x;
        register s32 floor_limit ASM_REG("$6");
        s32 floor_y;
        s32 signed_tile_x;
        s32 signed_tile_y;
        s32 x_adjust;
        s32 y_adjust;
        s16 *x_adjust_table;

        tile_x = FIELD(map_data, u8, 0x24);
        tile_y = FIELD(map_data, u8, 0x25);
        last_tile_x = tile_x;
        ASM_SCHED_BARRIER();
        last_tile_y = (u16)tile_y;
        do {
            signed_tile_x = (s16)tile_x;
            signed_tile_y = (s16)tile_y;
            if ((func_800A44E0((signed_tile_x << 6) & 0xFFC0, (signed_tile_y << 6) & 0xFFC0,
                               FIELD(actor, s16, 0x88),
                               (s16)(FIELD(effect, u16, 0xE) << 9)) << 16) == 0) {
                s16 floor = func_800BCB04(
                    ((signed_tile_x + ((s16 *)D_8006CCD8)[(s16)FIELD(effect, u16, 0xE)]) << 6) + 0x20 & 0xFFE0,
                    ((signed_tile_y + ((s16 *)D_8006CCE8)[(s16)FIELD(effect, u16, 0xE)]) << 6) + 0x20 & 0xFFE0,
                    (s16)(FIELD(actor, s16, 0x88) - 0x20));
                if ((floor < 513) && ((s16)(floor - FIELD(actor, s16, 0x88)) >= -63)) {
                    s32 next_tile_x;
                    register s32 next_tile_y ASM_REG("$2");

                    index++;
                    next_tile_x = tile_x + ((u16 *)D_8006CCD8)[(s16)FIELD(effect, u16, 0xE)];
                    tile_x = next_tile_x;
                    ASM_KEEP_NV(tile_x);
                    next_tile_y = tile_y + ((u16 *)D_8006CCE8)[(s16)FIELD(effect, u16, 0xE)];
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

        work_base = scratch;
        x_base = (last_tile_x << 16) >> 10;
        floor_x = (x_base + 0x20) & 0xFFE0;
        x_adjust_table = (s16 *)D_8006CCD8;
        ASM_CLOBBER("$6");
        floor_limit = -0x400;
        index = 1;
        ASM_KEEP(index);
        tile_y_bits = last_tile_y;
        y_base = (s32)tile_y_bits << 16;
        y_base >>= 10;
        floor_y = y_base + 0x20;
        x_adjust = x_adjust_table[(s16)FIELD(effect, u16, 0xE)];
        FIELD(work_base, u16, 2) = (u16)(x_base + ((x_adjust + 1) << 5));
        y_adjust = ((s16 *)D_8006CCE8)[(s16)FIELD(effect, u16, 0xE)];
        floor_y &= 0xFFE0;
        FIELD(work_base, u16, 6) = (u16)(y_base + ((y_adjust + 1) << 5));
        final_floor = func_800BCB04(floor_x, floor_y, floor_limit);
        {
            register s32 expanded_floor ASM_REG("$2");
            s32 widened_y;
            register s32 position_y ASM_REG("$5");
            s16 *delta_scan = (s16 *)(scratch + 2);

            FIELD(work_base, s16, 0xA) = final_floor;
            expanded_floor = (s32)final_floor << 16;
            ASM_KEEP(expanded_floor);
            delta_x = (s16)FIELD(work_base, u16, 2) - FIELD(position, s16, 2);
            if (delta_x < 0) delta_x = -delta_x;
            DELTA(0) = (s16)delta_x;
            widened_y = FIELD(work_base, u16, 6);
            position_y = FIELD(position, s16, 6);
            ASM_KEEP_DEP_NV(widened_y, position_y);
            widened_y <<= 16;
            widened_y >>= 16;
            widened_y -= position_y;
            if (widened_y < 0) widened_y = -widened_y;
            DELTA(1) = (s16)widened_y;
            expanded_floor >>= 16;
            expanded_floor -= FIELD(position, s16, 0xA);
            if (expanded_floor < 0) expanded_floor = -expanded_floor;
            DELTA(2) = (s16)expanded_floor;
            FIELD(effect, s16, 0x12) = DELTA(0);
            do {
                if (FIELD(delta_scan, s16, 0x18) > FIELD(effect, s16, 0x12)) {
                    FIELD(effect, s16, 0x12) = FIELD(delta_scan, s16, 0x18);
                }
                index++;
                delta_scan++;
            } while (index < 3);
        }
    }
    travel_frames = (s16)(((u16)FIELD(effect, s16, 0x12) << 16) >> 20);
    FIELD(effect, s16, 0x12) = travel_frames;
    if (travel_frames == 0) {
        FIELD(effect, s16, 0x12) = 1;
    }
    FIELD(position, s32, 0xC) =
        (FIELD(work_base, s32, 0) - FIELD(position, s32, 0)) / FIELD(effect, s16, 0x12);
    FIELD(position, s32, 0x10) =
        (FIELD(work_base, s32, 4) - FIELD(position, s32, 4)) / FIELD(effect, s16, 0x12);
    FIELD(position, s32, 0x14) =
        (FIELD(work_base, s32, 8) - FIELD(position, s32, 8)) / FIELD(effect, s16, 0x12);
    ASM_CLOBBER("$3");
    next_state = 11;
set_state:
    FIELD(effect, u16, 0xA) = next_state;
    FIELD(effect, u16, 0x10) = 0;
    ASM_CLOBBER("$4");
    func_800243CC(effect, position);
    goto finish;

case_motion_flags:
    FIELD(position, s32, 0) += FIELD(position, s32, 0xC);
    FIELD(position, s32, 4) += FIELD(position, s32, 0x10);
    FIELD(position, s32, 8) += FIELD(position, s32, 0x14);
    if (FIELD(effect, s16, 0x10) < FIELD(effect, s16, 0x12)) {
        goto finish;
    }
    func_800A56E0(0x300);
    func_800542BC();
    {
        void *owner = FIELD(effect, void *, 0x1C);
        s32 flags;

        FIELD(effect, u16, 0x1A) = 0;
        flags = FIELD(owner, s32, 0x14);
        if ((flags & 0x100000) != 0) {
            goto advance_state;
        }
        FIELD(owner, s32, 0x14) = flags | 0x100000;
        FIELD(effect, u16, 0x1A) = 1;
    }
    goto advance_state;

case_1:
    if (func_80053EF0(4) == 1) {
        goto advance_state;
    }
    goto finish;

case_2:
    FIELD(FIELD(effect, void *, 0x20), u16, 0xA) =
        (u16)(FIELD(FIELD(effect, void *, 0x20), u16, 0xA) - FIELD(effect, u16, 0x10));
    FIELD(FIELD(effect, void *, 0x1C), u16, 0x2A) =
        (u16)(FIELD(FIELD(effect, void *, 0x1C), u16, 0x2A) + 0x200);
    if (FIELD(effect, s16, 0x10) >= 28) {
        register void *target_render ASM_REG("$2") = FIELD(effect, void *, 0x24);

        FIELD(target_render, u16, 0x1A) = (u16)(FIELD(target_render, u16, 0x1A) + 0x800);
        goto advance_state;
    }
    goto finish;

case_3:
    FIELD(FIELD(effect, void *, 0x20), u16, 0xA) =
        (u16)(FIELD(FIELD(effect, void *, 0x20), u16, 0xA) + FIELD(effect, s16, 0x10) * 4);
    FIELD(FIELD(effect, void *, 0x1C), u16, 0x2A) =
        (u16)(FIELD(FIELD(effect, void *, 0x1C), u16, 0x2A) + 0x200);
    {
        u8 *height_base;
        void *target_pos;
        u8 *height_entry;
        u16 max_height;
        void *owner;
        register s32 effect_size ASM_REG("$5");
        register s32 effect_id ASM_REG("$4");

        height_base = D_800DDC40;
        owner = FIELD(effect, void *, 0x1C);
        target_pos = FIELD(effect, void *, 0x20);
        height_entry = height_base + FIELD(owner, u8, 0x13);
        effect_size = 16;
        if (FIELD(target_pos, s16, 0xA) >=
            FIELD(effect, s16, 0x16) - FIELD(height_entry, u8, 0)) {
            effect_id = 8;
            ASM_CLOBBER("$16");
            index = 0;
            max_height = FIELD(effect, u16, 0x16);
            FIELD(target_pos, u16, 0xA) =
                (u16)(max_height - FIELD(height_entry, u8, 0));
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
    FIELD(FIELD(effect, void *, 0x1C), u16, 0x2A) =
        (u16)(FIELD(FIELD(effect, void *, 0x1C), u16, 0x2A) + 0x200);
    index = 0;
    if (FIELD(effect, s16, 0x10) == 2) {
        do {
            func_80024138(effect);
            index++;
        } while (index < 8);
    }
    if (FIELD(effect, s16, 0x10) < 12) {
        goto finish;
    }
    goto advance_state;

case_5:
    if (FIELD(effect, s16, 0x10) < 4) {
        goto finish;
    }
    FIELD(FIELD(effect, void *, 0x20), s32, 8) = FIELD(effect, s32, 0x28);
    FIELD(FIELD(effect, void *, 0x1C), u16, 0x2A) = FIELD(effect, u16, 0x18);
    if (FIELD(effect, s16, 0x1A) != 0) {
        FIELD(FIELD(effect, void *, 0x1C), s32, 0x14) &= 0xFFEFFFFF;
    }
    FIELD(FIELD(effect, void *, 0x24), u16, 0x1A) -= 0x800;
    func_8009CE1C(FIELD(actor, void *, 0x60), 24, FIELD(effect, u8, 9), 4,
                  (s16)(FIELD(effect, u16, 0xE) << 9), actor, 1);
    goto advance_state;

case_6:
    if (FIELD(effect, s16, 0x14) != 0) {
        goto finish;
    }
    D_8008346C[0] = 0;
    FIELD(effect, u16, -2) |= 0x8000;
    D_800814A0[0] |= 0x8000;
    goto finish;

case_7:
    func_800243CC(effect, position);
    if (FIELD(effect, s16, 0x10) < 15) {
        goto finish;
    }
    {
        void *saved_height = FIELD(FIELD(effect, void *, 0x20), void *, 8);

        FIELD(effect, u16, 0xA) = (u16)(FIELD(effect, u16, 0xA) + 1);
        FIELD(effect, u16, 0x10) = 0;
        FIELD(effect, void *, 0x28) = saved_height;
    }
    goto finish;

case_8:
    FIELD(position, s32, 0) += FIELD(position, s32, 0xC);
    FIELD(position, s32, 4) += FIELD(position, s32, 0x10);
    FIELD(position, s32, 8) += FIELD(position, s32, 0x14);
    if (FIELD(effect, s16, 0x10) < FIELD(effect, s16, 0x12)) {
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
    if (FIELD(effect, s16, 0x10) < 7) {
        goto finish;
    }

advance_state:
    FIELD(effect, u16, 0xA) = (u16)(FIELD(effect, u16, 0xA) + 1);
    FIELD(effect, u16, 0x10) = 0;
    goto finish;

case_11:
    if (FIELD(effect, s16, 0x10) >= 28) {
        func_800A56E0(116);
        FIELD(effect, u16, 0xA) = 10;
        FIELD(effect, u16, 0x10) = 0;
    }
    goto finish;

finish:
    FIELD(effect, u16, 0x14) = 0;
}
