#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern u8 D_80083160[];
extern s16 func_80046C20(s16 *, s32 *, u16 *);
extern void func_8006658C(void *, void *);
extern void func_80067F20(void *, s32, s32, s32, void *);

typedef struct Slot800AF9D8 {
    u8 pad00[0x1C];
    s32 position;
    s32 decrement;
    u8 pad24[8];
    s32 remaining;
    s32 increment;
    u8 pad34[8];
    s32 phase;
} Slot800AF9D8;

void func_800AD138(u32 arg0)
{
    u8 *scratch;
    u8 *state;
    u8 *record;
    u8 *substate;
    u8 *scan_slot;
    u8 *active_slot;
    u8 *dec_slot;
    u8 *packet2;
    u8 *packet_use;
    u16 *table;
    u32 mask24;
    u32 mask_hi;
    s32 one;
    u8 *gte_input;
    s32 pair_init;
    s32 zero_arg;
    s32 sp_pair[2];
    s32 x_shift;
    s32 y_shift;
    s32 y_shifted;
    s32 bound_x;
    s32 bound_y;
    s32 i;
    s32 value;
    s32 value2;
    s32 value3;
    s32 min_y;
    s32 max_y;
    s32 x;
    s32 y;
    s32 row;
    s32 row_bound;
    s32 row_base;
    s32 bv3;
    s32 col;
    s32 temp;
    s32 ir0;
    s32 inc;
    s32 dec;
    u8 *inner;
    Slot800AF9D8 *inner_slot;
    s32 av;
    s32 av_shift;
    s32 bv;
    u16 y40;
    s32 t4;
    s32 c1;
    s32 c1b;
    s32 c2;
    s32 c3;
    s32 c4;
    s32 t5;
    u32 b2;
    s16 *argp;
    s32 vz;
    s32 code;
    s32 depth;
    s32 t;
    u16 width;
    s32 *list;
    s32 neg1;
    s32 bcval;
    s32 av2;
    s32 bcv;

    packet2 = (u8 *)0;
    zero_arg = (s32)packet2;
    scratch = (u8 *)0x1F800000;

    FIELD(scratch, s16, 0x180) = -0x1000;

    state = D_80083160;
    record = state + 0x1DC;
    FIELD(scratch, s16, 0x17C) = 0;
    FIELD(scratch, s16, 0x17E) = 0;
    substate = *(u8 **)D_80083160;
    x_shift = FIELD(record, s16, 0x14);
    pair_init = 0x01000100;
    y_shift = FIELD(record, s16, 0x16);
    bcval = (s32)(substate + 0x8AC);
    FIELD(scratch, s32, 0x0BC) = bcval;
    FIELD(scratch, s32, 0x128) = y_shift;
    FIELD(scratch, s32, 0x124) = x_shift;
    FIELD(scratch, s32, 0x114) = 0x40 << x_shift;
    bound_x = FIELD(record, s16, 0x18);
    bound_y = FIELD(record, s16, 0x1A);
    c1 = (FIELD(state, u16, 4) >> 1) & 0x3F;
    y_shifted = 0x40 << y_shift;
    FIELD(scratch, s32, 0x118) = y_shifted;
    FIELD(scratch, s32, 0x11C) = bound_x;
    FIELD(scratch, s32, 0x120) = bound_y;
    FIELD(scratch, u16, 0x20C) = c1;

    list = FIELD(substate, s32 *, 0x8D0);
    FIELD(scratch, s32, 0) = FIELD(state, s32, 0xA8);
    sp_pair[0] = 0;
    sp_pair[1] = pair_init;
    table = FIELD(state, u16 *, 0x1DC);
    func_80067F20(list, (s32)packet2, zero_arg, 0x20, sp_pair);
    func_8006658C((void *)FIELD(scratch, s32, 0xBC), list);
    list += 3;
    FIELD(scratch, u16, 0x170) = 4;
    argp = (s16 *)(state + 0x20);
    packet2 = scratch;
    packet2 = (u8 *)((u32)packet2 | 0x1C);
    zero_arg = (s32)scratch;
    zero_arg |= 0x170;
    FIELD(scratch, s32, 0x0C) =
        func_80046C20(argp,
                      (s32 *)packet2,
                      (u16 *)zero_arg);

    if (FIELD(scratch, u16, 0x170) != 0) {
        one = 1;
        gte_input = scratch;
        gte_input = (u8 *)((u32)gte_input | 0xE0);
        mask24 = 0x00FFFFFF;
        mask_hi = 0xFF000000;
        do {
            i = 3;
            do {
                if ((FIELD(scratch, s32, 0x38 + i * 0x28) == 0) &&
                    (FIELD(scratch, s32, 0x34 + i * 0x28) <= FIELD(scratch, s32, 0x0C))) {
                    FIELD(scratch, s32, 0x38 + i * 0x28) = one;
                }
                i--;
            } while (i >= 0);

            i = 3;
            FIELD(scratch, s32, 0x14) = 0x7FFF;
            FIELD(scratch, s32, 0x18) = -0x7FFF;
            do {
                if (FIELD(scratch, s32, 0x38 + i * 0x28) > 0) {
                    x = FIELD(scratch, s32, 0x1C + i * 0x28);
                    FIELD(scratch, s32, 8) = x;
                    if (x < FIELD(scratch, s32, 0x14)) {
                        FIELD(scratch, s32, 0x14) = x;
                    }
                    x = FIELD(scratch, s32, 8);
                    if (FIELD(scratch, s32, 0x18) < x) {
                        FIELD(scratch, s32, 0x18) = x;
                    }
                    temp = FIELD(scratch, s32, 0x2C + i * 0x28) + FIELD(scratch, s32, 0x24 + i * 0x28);
                    FIELD(scratch, s32, 0x2C + i * 0x28) = temp;
                    if (temp >= 0) {
                        s32 t3;
                        s32 temp2;
                        s32 tmp1c;

                        inner = scratch + i * 0x28;
                        inner_slot = (Slot800AF9D8 *)inner;
                        inc = inner_slot->increment;
                        dec = inner_slot->decrement;
                        do {
                            inner_slot->position += inc;
                            inner_slot->phase -= 0x40;
                            inner_slot->remaining -= dec;
                        } while ((inner_slot->phase > 0) &&
                                 (inner_slot->remaining >= 0));
                    }
                    x = FIELD(scratch, s32, 0x1C + i * 0x28);
                    FIELD(scratch, s32, 8) = x;
                    if (x < FIELD(scratch, s32, 0x14)) {
                        FIELD(scratch, s32, 0x14) = x;
                    }
                    x = FIELD(scratch, s32, 8);
                    if (FIELD(scratch, s32, 0x18) < x) {
                        FIELD(scratch, s32, 0x18) = x;
                    }
                }
                i--;
            } while (i >= 0);

            FIELD(scratch, s32, 0x14) =
                (FIELD(scratch, s32, 0x14) - 0x20) & ~0x3F;
            FIELD(scratch, s32, 0x18) =
                (FIELD(scratch, s32, 0x18) + 0x20) & ~0x3F;
            min_y = FIELD(scratch, s32, 0x14);
            if (min_y < 0) {
                min_y += 0x3F;
            }
            row = FIELD(scratch, s32, 0x0C);
            FIELD(scratch, s32, 0x134) = min_y >> 6;
            if (row < 0) {
                row += 0x3F;
            }
            row >>= 6;
            FIELD(scratch, s32, 0x138) = row;
            if (row < 0) {
                FIELD(scratch, s32, 0x138) = 0;
                goto row_ready;
            }
            row_bound = FIELD(scratch, s32, 0x120);
            if (row < row_bound) {
                goto row_in_range;
            }
            row_base = row_bound << FIELD(scratch, s32, 0x124);
            goto store_row_base;
    row_in_range:
            row_base = row << FIELD(scratch, s32, 0x124);
    store_row_base:
            FIELD(scratch, s32, 0x138) = row_base;
    row_ready:

            i = 3;
            if (FIELD(scratch, s32, 0x14) <= FIELD(scratch, s32, 0x18)) {
                do {
                    packet_use = (u8 *)list + 7;
                    value = FIELD(scratch, s32, 0x134);
                    if (value < 0) {
                        av = FIELD(scratch, s32, 0x138);
                        value &= 3;
                        av += value;
                        FIELD(scratch, s32, 0x144) = av;
                    } else {
                        col = FIELD(scratch, s32, 0x11C);
                        if (value >= col) {
                            av = FIELD(scratch, s32, 0x138);
                            value &= 3;
                            av += col;
                            av += value;
                            av -= 3;
                            FIELD(scratch, s32, 0x144) = av;
                        } else {
                            av = FIELD(scratch, s32, 0x138);
                            av += value;
                            FIELD(scratch, s32, 0x144) = av;
                        }
                    }
                    width = table[FIELD(scratch, s32, 0x144)];
                    FIELD(scratch, s32, 0x0C0) = width;
                    if (width == 0) {
                        width = FIELD(scratch, u16, 0x14);
                        depth = FIELD(scratch, u16, 0x0C);
                        FIELD(scratch, u16, 0x0FC) = 0;
                        FIELD(scratch, u16, 0x0F4) = 0;
                        FIELD(scratch, u16, 0x0EC) = 0;
                        FIELD(scratch, u16, 0x0E4) = 0;
                        y40 = depth;
                        t = depth;
                        depth = t;
                        depth = t;
                        depth = t;
                        t = width;
                        width = t;
                        width = t;
                        width = t;
                        t = 0;
                        FIELD(scratch, u16, 0x0F0) = width;
                        FIELD(scratch, u16, 0x0E0) = width;
                        width += 0x40;
                        y40 += 0x40;
                        FIELD(scratch, u16, 0x0F8) = width;
                        FIELD(scratch, u16, 0x0E8) = width;
                        FIELD(scratch, u16, 0x0FA) = y40;
                        FIELD(scratch, u16, 0x0F2) = y40;
                        FIELD(scratch, u16, 0x0EA) = depth;
                        FIELD(scratch, u16, 0x0E2) = depth;

                        gte_ldv3(gte_input, scratch + 0xE8, scratch + 0xF0);
                        gte_rtpt();
                        gte_nclip();
                        gte_stopz(scratch + 0xDC);
                        if (FIELD(scratch, s32, 0x0DC) > 0) {
                            gte_stsxy3_g3(list);
                            gte_stdp(scratch + 0xC0);
                            gte_avsz3();
                            gte_stotz(scratch + 0xC8);
                            gte_ldv0(scratch + 0xF8);
                            gte_rtps();
                            gte_stsxy((u8 *)list + 0x20);
                            gte_stdp(scratch + 0xC4);
                            gte_stszotz(scratch + 0xD4);

                            av = FIELD(scratch, s32, 0x0C8);
                            bv = FIELD(scratch, s32, 0x0D4);
                            av_shift = av << 1;
                            FIELD(scratch, s32, 0x0C8) =
                                (av + av_shift + bv + 3) >> 2;
                            if ((u32)FIELD(scratch, s32, 0x0C8) >= 0x1E0U) {
                                FIELD(scratch, s32, 0x0C8) = 0x1DF;
                            }
                            av = FIELD(scratch, s32, 0x0C0);
                            bv = FIELD(scratch, s32, 0x0C4);
                            av_shift = av << 1;
                            FIELD(scratch, s32, 0x0C0) =
                                (av + av_shift + bv) >> 2;

                            gte_ldv0(scratch + 0x17C);
                            gte_ldrgb(scratch);
                            vz = FIELD(scratch, u16, 0x0FC);
                            vz = (s16)vz;
                            ir0 = 0;
                            if (vz > 0) {
                                ir0 = vz << 2;
                            }
                            gte_ldir0(ir0);
                            FIELD(packet_use, s8, -4) = 9;
                            gte_ncds_nn();
                            gte_strgb((u8 *)list + 4);

                            c1b = FIELD(scratch, u8, 0x20C);
                            FIELD(packet_use, u8, 0x15) = c1b;
                            FIELD(packet_use, u8, 5) = c1b;
                            c2 = FIELD(scratch, u8, 0x20C) + 0x3F;
                            FIELD(packet_use, s8, 0x1D) = c2;
                            FIELD(packet_use, s8, 0x0D) = c2;
                            c3 = -(s32)FIELD(scratch, u8, 0x20C);
                            b2 = FIELD(packet_use, u8, -3);
                            FIELD(packet_use, s8, 0x0E) = c3;
                            FIELD(packet_use, s8, 6) = c3;
                            c4 = FIELD(scratch, u8, 0x20C);
                            FIELD(packet_use, s16, 0x0F) = 0x2D;
                            FIELD(packet_use, s16, 7) = 0x75C1;
                            FIELD(packet_use, u8, -3) = b2 >> 1;
                            FIELD(packet_use, u8, -2) >>= 1;
                            value2 = 0x3F - c4;
                            FIELD(packet_use, s8, 0x1E) = value2;
                            FIELD(packet_use, s8, 0x16) = value2;
                            FIELD(packet_use, u8, -1) >>= 1;
                            bcv = FIELD((void *)FIELD(scratch, s32, 0xBC), s32, 0);
                            av2 = FIELD((u8 *)list, s32, 0);
                            FIELD((u8 *)list, s32, 0) =
                                (av2 & mask_hi) |
                                (bcv & mask24);
                            value3 = (s32)list & mask24;
                            list += 10;
                            FIELD((void *)FIELD(scratch, s32, 0xBC), s32, 0) =
                                (FIELD((void *)FIELD(scratch, s32, 0xBC), s32, 0) & mask_hi) |
                                value3;
                            if (arg0 < (u32)list) {
                                goto done;
                            }
                        }
                    }
                    FIELD(scratch, s32, 0x134) += 1;
                    t5 = FIELD(scratch, s32, 0x14) + 0x40;
                    FIELD(scratch, s32, 0x14) = t5;
                    if (FIELD(scratch, s32, 0x18) < t5) {
                        break;
                    }
                } while (1);
            }

            i = 3;
            neg1 = -1;
            FIELD(scratch, s32, 0x0C) += 0x40;
            do {
                if (FIELD(scratch, s32, 0x38 + i * 0x28) > 0) {
                    t4 = FIELD(scratch, s32, 0x28 + i * 0x28) - 0x40;
                    FIELD(scratch, s32, 0x28 + i * 0x28) = t4;
                    if (t4 <= 0) {
                        FIELD(scratch, s32, 0x38 + i * 0x28) = neg1;
                        FIELD(scratch, u16, 0x170) -= 1;
                    }
                }
                i--;
            } while (i >= 0);
            i = 3;
        } while (FIELD(scratch, u16, 0x170) != 0);
    }

done:
    sp_pair[1] = 0x400040;
    sp_pair[0] = 0;
    func_80067F20(list, 0, 0, 0x20, sp_pair);
    func_8006658C((void *)FIELD(scratch, s32, 0xBC), list);
    list += 3;
    FIELD(FIELD(state, u8 *, 0), s32 *, 0x8D0) = list;
    return;
}
