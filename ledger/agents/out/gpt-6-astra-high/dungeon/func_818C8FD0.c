#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

typedef struct OffsetTable {
    u8 value[32];
} OffsetTable;

extern OffsetTable D_80024004;
extern void D_80024270(void);
extern s16 D_80024D04[5];
extern s8 D_8006CCD8[9];
extern s8 D_8006CCE8[9];
extern s32 D_800814A0[3];
extern s32 D_8008346C[3];
extern u8 D_800DEC00[];

extern void func_8003DB94(void *, void *, s32);
extern void *func_8003DF74(void *, void *, void *, s32);
extern void *func_8003FC64(s32);

extern void func_80024C74(void) __attribute__((noreturn));

extern void func_80024C0C(void) __attribute__((noreturn));

extern void func_800249E8(void) __attribute__((noreturn));

extern void func_80024BA0(void) __attribute__((noreturn));

extern void func_80024CD8(void) __attribute__((noreturn));

extern void func_80024CD8(void) __attribute__((noreturn));

/* Updates an effect through attachment, motion, and timed cleanup. */
void func_818C8FD0(void *state_arg, void *position_arg, void *part_arg)
{
    s16 delta[3];
    s32 mode;
    register s32 active_marker ASM_REG("$2");   /* MATCH pin: retail register colouring depends on it */
    u16 angle;
    u16 frame_count;
    OffsetTable offsets;
    u8 *state;
    u8 *object;
    u8 *owner_node;
    register u8 *output_pos ASM_REG("$19");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    u8 *owner_pos;
    OffsetTable *offset_table;   /* MATCH pin: retail register colouring depends on it */
    s32 one;
    void *part;
    OffsetTable *offset_source = &D_80024004;

    state = state_arg;
    output_pos = position_arg;
    part = part_arg;
    ASM_KEEP(state);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ASM_KEEP(output_pos);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    ASM_KEEP(part);   /* MATCH pin: retail schedule: same instructions, different order without it */
    object = FIELD(state, u8 *, 0);
    offsets = *offset_source;
    offset_table = &offsets;
    one = 1;
    frame_count = FIELD(state, u16, 0x82);
    mode = FIELD(state, s16, 0xA);
    owner_node = object - 0x20;
    owner_pos = FIELD(owner_node, u8 *, 8);
    frame_count++;
    FIELD(state, u16, 0x82) = frame_count;

    if (mode == one)
        goto mode1;
    if (mode < 2) {
        if (mode == 0)
            goto mode0;
        func_80024CD8();
    }
    ASM_SCHED_BARRIER();   /* MATCH pin: retail immediate-load split depends on it */
    if (mode == 2)
        goto mode2;
    if (mode == 3) {
        active_marker = 0x63;
        goto mode3;
    }
    func_80024CD8();

mode0:
    FIELD(part, u32, 0xC) = 0x00808080;
    FIELD(part, s16, 0x1E) = 0x1000;
    FIELD(part, s16, 0x1C) = 0x1000;
    func_8003DB94(part, D_800DEC00, 0);
    angle = FIELD(object, u16, 0x2A);
    D_80024D04[0] = one;
    FIELD(state, s16, 0x7E) = (angle >> 9) & 7;
    (*(volatile u16 *)((u8 *)state + 0xA))++;

mode1:
    {
        u8 *owner_part;
        u16 position_z;
        u16 final_z;
        u16 delta_z;

        owner_part = FIELD(owner_node, u8 *, 0xC);

        if ((func_8003DF74(FIELD(owner_part, void *, 8), owner_part, delta, 0) != 0) ||
            (FIELD(FIELD(owner_node, u8 *, 0xC), u16, 0x14) & 0x8000)) {
            FIELD(output_pos, u16, 2) = FIELD(owner_pos, u16, 2);
            FIELD(output_pos, u16, 6) = FIELD(owner_pos, u16, 6);
            position_z = FIELD(owner_pos, u16, 0xA);
            FIELD(output_pos, u16, 0xA) = position_z;

            if (!(FIELD(FIELD(owner_node, u8 *, 0xC), u16, 0x14) & 0x8000)) {
                FIELD(output_pos, u16, 2) += (u16)delta[0];
                FIELD(output_pos, u16, 6) += (u16)delta[1];
                ASM_SCHED_BARRIER();   /* MATCH pin: retail immediate-load split depends on it */
                final_z = FIELD(output_pos, u16, 0xA);
                delta_z = (u16)delta[2];
                final_z += delta_z;
                ASM_TAILSLOT_PIN(final_z);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
                func_800249E8();
            } else {
                ASM_SCHED_BARRIER();   /* MATCH pin: retail immediate-load split depends on it */
                final_z = position_z - 0x40;
            }
            FIELD(output_pos, u16, 0xA) = final_z;

            if (FIELD(FIELD(state, u8 *, 4), u16, 0) & 0x80) {
                u16 old_mode;

                old_mode = FIELD(state, u16, 0xA);
                ASM_KEEP(old_mode);   /* MATCH pin: retail basic-block layout depends on it */
                FIELD(state, s16, 0x84) = 0;
                func_80024C0C();
                return;
            }
        }
        return;
    }

mode2:
    {
        u8 *effect_node;

        effect_node = func_8003FC64(0x12);

        if (effect_node != 0) {
            u8 *effect;
            s32 direction_index;
            u8 *tile;

            effect = effect_node + 0x20;

            {
                s16 *direction_offset;

                direction_index = FIELD(state, s16, 0x7E);
                direction_offset = (s16 *)((u8 *)offset_table + direction_index * 4);
                FIELD(effect, s32, 0x58) = (s32)direction_offset[0] << 16;
            }
            {
                u16 *direction_offset;   /* MATCH pin: retail register colouring depends on it */

                direction_index = FIELD(state, s16, 0x7E);
                direction_offset = (u16 *)((u8 *)offset_table + direction_index * 4);
                FIELD(effect, s32, 0x5C) = (s32)direction_offset[1] << 16;
            }
            FIELD(effect, void *, 0x2C) = object;
            FIELD(effect, s32, 0x30) = FIELD(object, s32, 0x60);
            FIELD(effect, s16, 0xA) = (FIELD(state, s16, 0x84) - 1) / 2;
            FIELD(effect, u8, 0x15) = FIELD(state, u8, 9);
            FIELD(effect, u16, 0x16) = FIELD(state, u16, 0x7E);

            {
                u8 *table_base = (u8 *)D_8006CCD8;

                direction_index = FIELD(state, s16, 0x7E) * 2;
                tile = FIELD(object, u8 *, -0x14);
                FIELD(state, u8, 0xA0) =
                    FIELD(tile, u8, 0x24) + table_base[direction_index];
            }
            {
                u8 *table_base = (u8 *)D_8006CCE8;

                direction_index = FIELD(state, s16, 0x7E) * 2;
                FIELD(state, u8, 0xA1) =
                    FIELD(tile, u8, 0x25) + table_base[direction_index];
            }

            if (FIELD(object, void *, 0x60) != 0) {
                register s32 tile_distance ASM_REG("$2");   /* MATCH pin: retail register colouring depends on it */
                s32 duration;
                u8 *target_pos;
                u16 end_time;

                FIELD(effect, s16, 8) = one;
                if (FIELD(object, s8, 0x72) != FIELD(tile, u8, 0x24)) {
                    tile_distance = FIELD(object, s8, 0x72) - FIELD(tile, u8, 0x24);
                } else {
                    tile_distance = FIELD(object, s8, 0x73);
                    tile_distance -= FIELD(tile, u8, 0x25);
                }
                if (tile_distance < 0) {
                    tile_distance = -tile_distance;
                }
                FIELD(effect, s16, 2) = tile_distance * 2;
                ASM_MEM_BARRIER();   /* MATCH pin: retail delay-slot fill depends on it */

                target_pos = FIELD(FIELD(object, u8 *, 0x60), u8 *, -0x18);
                duration = FIELD(effect, s16, 2);
                if (duration != 0) {
                    FIELD(effect, s32, 0x60) =
                        (FIELD(target_pos, s32, 8) - FIELD(output_pos, s32, 8) - 0x200000) /
                        (duration - 1);
                }
                end_time = FIELD(effect, u16, 2);
                end_time += 0x3C;
                ASM_TAILSLOT_PIN(end_time);   /* MATCH pin: retail delay-slot fill depends on it */
                func_80024BA0();
            } else {
                FIELD(effect, s16, 2) = 0x20;
                FIELD(effect, s16, 8) = 0;
                FIELD(state, s16, 0x86) = FIELD(effect, s16, 2) + 0x1E;
            }

            FIELD(effect_node, void *, 0x10) = D_80024270;
            {
                u8 *effect_pos = FIELD(effect_node, u8 *, 8);

                FIELD(effect_pos, s32, 0) = FIELD(output_pos, s32, 0);
                FIELD(effect_pos, s32, 4) = FIELD(output_pos, s32, 4);
                FIELD(effect_pos, s32, 8) = FIELD(output_pos, s32, 8);
                {
                    u8 *effect_part = FIELD(effect_node, u8 *, 0xC);

                    FIELD(effect_part, u8, 0xE) = 0x80;
                    FIELD(effect_part, u8, 0xD) = 0x80;
                    FIELD(effect_part, u8, 0xC) = 0x80;
                    FIELD(effect_part, s16, 0x1E) = 0x1000;
                    FIELD(effect_part, s16, 0x1C) = 0x1000;
                }
                FIELD(state, void *, 0xA8) = effect_node;
                FIELD(state, void *, 0xAC) = effect_pos;
                FIELD(state, s16, 0x88) = 0x63;
            }
        }
        FIELD(state, u16, 0xA)++;
        func_80024CD8();
        return;
    }

mode3:
    if (FIELD(state, s16, 0x88) == active_marker) {
        register u8 *effect_node ASM_REG("$6") = FIELD(state, u8 *, 0xA8);   /* MATCH pin: load-bearing for the whole function shape */
        register u8 *effect_pos ASM_REG("$4") = FIELD(state, u8 *, 0xAC);   /* MATCH pin: retail register colouring depends on it */

        if (FIELD(effect_node, u16, 0x1E) & 0x8000) {
            FIELD(state, s16, 0x88) = 0;
            func_80024C74();
            return;
        }
        FIELD(output_pos, s32, 0) = FIELD(effect_pos, s32, 0);
        FIELD(output_pos, s32, 4) = FIELD(effect_pos, s32, 4);
        FIELD(output_pos, s32, 8) = FIELD(effect_pos, s32, 8);
    }
    goto finish;

finish:
    {
        u16 old_timer = FIELD(state, u16, 0x84);
        s16 timer = old_timer + 1;

        FIELD(state, u16, 0x84) = timer;
        if (FIELD(state, s16, 0x86) < timer) {
            s32 active_flag = D_80024D04[0];

            FIELD(state, u16, 0x84) = old_timer;
            if (active_flag == 0) {
                D_8008346C[0] = 0;
                FIELD(state, u16, -2) |= 0x8000;
                D_800814A0[0] |= 0x8000;
                func_80024CD8();
                return;
            } else {
                D_80024D04[0] = 0;
            }
        }
    }
}
