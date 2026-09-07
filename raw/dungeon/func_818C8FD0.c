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

void func_818C8FD0(void *arg0, void *arg1, void *arg2)
{
    s16 delta[3];
    s32 mode;
    register s32 mode3_value ASM_REG("$2");
    u16 angle;
    register u16 state_counter ASM_REG("$2");
    OffsetTable table;
    register u8 *state ASM_REG("$16");
    register u8 *object ASM_REG("$17");
    register u8 *base ASM_REG("$18");
    register u8 *out ASM_REG("$19");
    register u8 *position ASM_REG("$20");
    register OffsetTable *tablep ASM_REG("$21");
    register s32 one ASM_REG("$22");
    register void *part ASM_REG("$7");
    OffsetTable *source = &D_80024004;

    state = arg0;
    out = arg1;
    part = arg2;
    ASM_KEEP(state);
    ASM_KEEP(out);
    ASM_KEEP(part);
    object = FIELD(state, u8 *, 0);
    ASM_KEEP(object);
    table = *source;
    tablep = &table;
    one = 1;
    ASM_KEEP(tablep);
    ASM_KEEP(one);
    state_counter = FIELD(state, u16, 0x82);
    mode = FIELD(state, s16, 0xA);
    ASM_SCHED_BARRIER();
    base = object - 0x20;
    position = FIELD(base, u8 *, 8);
    ASM_KEEP(base);
    ASM_KEEP(position);
    state_counter++;
    FIELD(state, u16, 0x82) = state_counter;

    if (mode == one)
        goto mode1;
    if (mode < 2) {
        if (mode == 0)
            goto mode0;
        func_80024CD8();
    }
    ASM_SCHED_BARRIER();
    if (mode == 2)
        goto mode2;
    if (mode == 3) {
        mode3_value = 0x63;
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
        u8 *link;
        u16 position_z;
        register u16 final_z ASM_REG("$2");
        register u16 delta_z ASM_REG("$3");

        link = FIELD(base, u8 *, 0xC);

        if ((func_8003DF74(FIELD(link, void *, 8), link, delta, 0) != 0) ||
            (FIELD(FIELD(base, u8 *, 0xC), u16, 0x14) & 0x8000)) {
            FIELD(out, u16, 2) = FIELD(position, u16, 2);
            FIELD(out, u16, 6) = FIELD(position, u16, 6);
            position_z = FIELD(position, u16, 0xA);
            FIELD(out, u16, 0xA) = position_z;

            if (!(FIELD(FIELD(base, u8 *, 0xC), u16, 0x14) & 0x8000)) {
                FIELD(out, u16, 2) += (u16)delta[0];
                FIELD(out, u16, 6) += (u16)delta[1];
                ASM_SCHED_BARRIER();
                final_z = FIELD(out, u16, 0xA);
                delta_z = (u16)delta[2];
                final_z += delta_z;
                ASM_TAILSLOT_PIN(final_z);
                func_800249E8();
            } else {
                ASM_SCHED_BARRIER();
                final_z = position_z - 0x40;
            }
            FIELD(out, u16, 0xA) = final_z;

            if (FIELD(FIELD(state, u8 *, 4), u16, 0) & 0x80) {
                register u16 old_state ASM_REG("$2");

                old_state = FIELD(state, u16, 0xA);
                ASM_KEEP(old_state);
                FIELD(state, s16, 0x84) = 0;
                func_80024C0C();
                return;
            }
        }
        return;
    }

mode2:
    {
        register u8 *node ASM_REG("$6");

        node = func_8003FC64(0x12);
        ASM_KEEP(node);

        if (node != 0) {
            register u8 *work ASM_REG("$4");
            s32 index;
            register u8 *map ASM_REG("$5");

            work = node + 0x20;
            ASM_KEEP(work);

            {
                register s16 *entry ASM_REG("$2");

                index = FIELD(state, s16, 0x7E);
                entry = (s16 *)((u8 *)tablep + index * 4);
                FIELD(work, s32, 0x58) = (s32)entry[0] << 16;
            }
            {
                register u16 *entry ASM_REG("$2");

                index = FIELD(state, s16, 0x7E);
                entry = (u16 *)((u8 *)tablep + index * 4);
                FIELD(work, s32, 0x5C) = (s32)entry[1] << 16;
            }
            FIELD(work, void *, 0x2C) = object;
            FIELD(work, s32, 0x30) = FIELD(object, s32, 0x60);
            FIELD(work, s16, 0xA) = (FIELD(state, s16, 0x84) - 1) / 2;
            FIELD(work, u8, 0x15) = FIELD(state, u8, 9);
            FIELD(work, u16, 0x16) = FIELD(state, u16, 0x7E);

            {
                u8 *table_base = (u8 *)D_8006CCD8;

                index = FIELD(state, s16, 0x7E) * 2;
                map = FIELD(object, u8 *, -0x14);
                ASM_KEEP(map);
                FIELD(state, u8, 0xA0) =
                    FIELD(map, u8, 0x24) + table_base[index];
            }
            {
                u8 *table_base = (u8 *)D_8006CCE8;

                index = FIELD(state, s16, 0x7E) * 2;
                FIELD(state, u8, 0xA1) =
                    FIELD(map, u8, 0x25) + table_base[index];
            }

            if (FIELD(object, void *, 0x60) != 0) {
                register s32 difference ASM_REG("$2");
                s32 duration;
                register u8 *motion ASM_REG("$2");
                register u16 end_time ASM_REG("$2");

                FIELD(work, s16, 8) = one;
                if (FIELD(object, s8, 0x72) != FIELD(map, u8, 0x24)) {
                    difference = FIELD(object, s8, 0x72) - FIELD(map, u8, 0x24);
                } else {
                    difference = FIELD(object, s8, 0x73);
                    difference -= FIELD(map, u8, 0x25);
                }
                if (difference < 0) {
                    difference = -difference;
                }
                FIELD(work, s16, 2) = difference * 2;
                ASM_MEM_BARRIER();

                motion = FIELD(FIELD(object, u8 *, 0x60), u8 *, -0x18);
                duration = FIELD(work, s16, 2);
                if (duration != 0) {
                    FIELD(work, s32, 0x60) =
                        (FIELD(motion, s32, 8) - FIELD(out, s32, 8) - 0x200000) /
                        (duration - 1);
                }
                end_time = FIELD(work, u16, 2);
                end_time += 0x3C;
                ASM_TAILSLOT_PIN(end_time);
                func_80024BA0();
            } else {
                FIELD(work, s16, 2) = 0x20;
                FIELD(work, s16, 8) = 0;
                FIELD(state, s16, 0x86) = FIELD(work, s16, 2) + 0x1E;
            }

            FIELD(node, void *, 0x10) = D_80024270;
            {
                u8 *saved = FIELD(node, u8 *, 8);

                FIELD(saved, s32, 0) = FIELD(out, s32, 0);
                FIELD(saved, s32, 4) = FIELD(out, s32, 4);
                FIELD(saved, s32, 8) = FIELD(out, s32, 8);
                {
                    u8 *part = FIELD(node, u8 *, 0xC);

                    FIELD(part, u8, 0xE) = 0x80;
                    FIELD(part, u8, 0xD) = 0x80;
                    FIELD(part, u8, 0xC) = 0x80;
                    FIELD(part, s16, 0x1E) = 0x1000;
                    FIELD(part, s16, 0x1C) = 0x1000;
                }
                FIELD(state, void *, 0xA8) = node;
                FIELD(state, void *, 0xAC) = saved;
                FIELD(state, s16, 0x88) = 0x63;
            }
        }
        FIELD(state, u16, 0xA)++;
        func_80024CD8();
        return;
    }

mode3:
        if (FIELD(state, s16, 0x88) == mode3_value) {
            register u8 *node ASM_REG("$6") = FIELD(state, u8 *, 0xA8);
            register u8 *saved ASM_REG("$4") = FIELD(state, u8 *, 0xAC);

            if (FIELD(node, u16, 0x1E) & 0x8000) {
                FIELD(state, s16, 0x88) = 0;
                func_80024C74();
                return;
            }
            FIELD(out, s32, 0) = FIELD(saved, s32, 0);
            FIELD(out, s32, 4) = FIELD(saved, s32, 4);
            FIELD(out, s32, 8) = FIELD(saved, s32, 8);
        }
        goto finish;

finish:
    {
        u16 old_counter = FIELD(state, u16, 0x84);
        s16 new_counter = old_counter + 1;

        FIELD(state, u16, 0x84) = new_counter;
        if (FIELD(state, s16, 0x86) < new_counter) {
            s32 global_state = D_80024D04[0];

            FIELD(state, u16, 0x84) = old_counter;
            if (global_state == 0) {
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
