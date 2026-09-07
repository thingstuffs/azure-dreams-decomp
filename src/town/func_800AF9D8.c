#include "common.h"


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


typedef struct S_800AD138_0 {
    u8 pad_00[0x14];
    s16 unk_14;
    s16 unk_16;
    s16 unk_18;
    s16 unk_1A;
} S_800AD138_0;   /* record in func_800AD138 */

typedef struct S_800AD138_1 {
    u8 * unk_00;
    u16 unk_04;
    u8 pad_06[0xA2];
    s32 unk_A8;
    u8 pad_AC[0x130];
    u16 * unk_1DC;
} S_800AD138_1;   /* state in func_800AD138 */

typedef struct S_800AD138_2_pre {
    s8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 unk_03;
} S_800AD138_2_pre;   /* the 0x4 bytes before packet_use in func_800AD138, addressed as packet_use[-1] */

typedef struct S_800AD138_2 {
    u8 pad_00[0x5];
    u8 unk_05;
    s8 unk_06;
    u8 pad_07[0x6];
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x6];
    u8 unk_15;
    s8 unk_16;
    u8 pad_17[0x6];
    s8 unk_1D;
    s8 unk_1E;
} S_800AD138_2;   /* packet_use in func_800AD138 */

typedef struct S_800AD138_3 {
    s32 unk_00;
} S_800AD138_3;   /* (u8 *)list in func_800AD138 */

typedef struct S_800AD138_4 {
    s32 unk_00;
} S_800AD138_4;   /* (void *)(*(s32 *)((u8 *)scratch + 0xBC)) in func_800AD138 */

typedef struct S_800AD138_5 {
    u8 pad_00[0x8D0];
    s32 * unk_8D0;
} S_800AD138_5;   /* ((S_800AD138_1 *)state)->unk_00 in func_800AD138 */

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

    (*(s16 *)((u8 *)scratch + 0x180)) = -0x1000;

    state = D_80083160;
    record = state + 0x1DC;
    (*(s16 *)((u8 *)scratch + 0x17C)) = 0;
    (*(s16 *)((u8 *)scratch + 0x17E)) = 0;
    substate = *(u8 **)D_80083160;
    x_shift = ((S_800AD138_0 *)record)->unk_14;
    pair_init = 0x01000100;
    y_shift = ((S_800AD138_0 *)record)->unk_16;
    bcval = (s32)(substate + 0x8AC);
    (*(s32 *)((u8 *)scratch + 0x0BC)) = bcval;
    (*(s32 *)((u8 *)scratch + 0x128)) = y_shift;
    (*(s32 *)((u8 *)scratch + 0x124)) = x_shift;
    (*(s32 *)((u8 *)scratch + 0x114)) = 0x40 << x_shift;
    bound_x = ((S_800AD138_0 *)record)->unk_18;
    bound_y = ((S_800AD138_0 *)record)->unk_1A;
    c1 = (((S_800AD138_1 *)state)->unk_04 >> 1) & 0x3F;
    y_shifted = 0x40 << y_shift;
    (*(s32 *)((u8 *)scratch + 0x118)) = y_shifted;
    (*(s32 *)((u8 *)scratch + 0x11C)) = bound_x;
    (*(s32 *)((u8 *)scratch + 0x120)) = bound_y;
    (*(u16 *)((u8 *)scratch + 0x20C)) = c1;

    list = (*(s32 * *)((u8 *)substate + 0x8D0));
    (*(s32 *)((u8 *)scratch + 0)) = ((S_800AD138_1 *)state)->unk_A8;
    sp_pair[0] = 0;
    sp_pair[1] = pair_init;
    table = ((S_800AD138_1 *)state)->unk_1DC;
    func_80067F20(list, (s32)packet2, zero_arg, 0x20, sp_pair);
    func_8006658C((void *)(*(s32 *)((u8 *)scratch + 0xBC)), list);
    list += 3;
    (*(u16 *)((u8 *)scratch + 0x170)) = 4;
    argp = (s16 *)(state + 0x20);
    packet2 = scratch;
    packet2 = (u8 *)((u32)packet2 | 0x1C);
    zero_arg = (s32)scratch;
    zero_arg |= 0x170;
    (*(s32 *)((u8 *)scratch + 0x0C)) =
        func_80046C20(argp,
                      (s32 *)packet2,
                      (u16 *)zero_arg);

    if ((*(u16 *)((u8 *)scratch + 0x170)) != 0) {
        one = 1;
        gte_input = scratch;
        gte_input = (u8 *)((u32)gte_input | 0xE0);
        mask24 = 0x00FFFFFF;
        mask_hi = 0xFF000000;
        do {
            i = 3;
            do {
                if (((*(s32 *)((u8 *)scratch + 0x38 + i * 0x28)) == 0) &&
                    ((*(s32 *)((u8 *)scratch + 0x34 + i * 0x28)) <= (*(s32 *)((u8 *)scratch + 0x0C)))) {
                    (*(s32 *)((u8 *)scratch + 0x38 + i * 0x28)) = one;
                }
                i--;
            } while (i >= 0);

            i = 3;
            (*(s32 *)((u8 *)scratch + 0x14)) = 0x7FFF;
            (*(s32 *)((u8 *)scratch + 0x18)) = -0x7FFF;
            do {
                if ((*(s32 *)((u8 *)scratch + 0x38 + i * 0x28)) > 0) {
                    x = (*(s32 *)((u8 *)scratch + 0x1C + i * 0x28));
                    (*(s32 *)((u8 *)scratch + 8)) = x;
                    if (x < (*(s32 *)((u8 *)scratch + 0x14))) {
                        (*(s32 *)((u8 *)scratch + 0x14)) = x;
                    }
                    x = (*(s32 *)((u8 *)scratch + 8));
                    if ((*(s32 *)((u8 *)scratch + 0x18)) < x) {
                        (*(s32 *)((u8 *)scratch + 0x18)) = x;
                    }
                    temp = (*(s32 *)((u8 *)scratch + 0x2C + i * 0x28)) + (*(s32 *)((u8 *)scratch + 0x24 + i * 0x28));
                    (*(s32 *)((u8 *)scratch + 0x2C + i * 0x28)) = temp;
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
                    x = (*(s32 *)((u8 *)scratch + 0x1C + i * 0x28));
                    (*(s32 *)((u8 *)scratch + 8)) = x;
                    if (x < (*(s32 *)((u8 *)scratch + 0x14))) {
                        (*(s32 *)((u8 *)scratch + 0x14)) = x;
                    }
                    x = (*(s32 *)((u8 *)scratch + 8));
                    if ((*(s32 *)((u8 *)scratch + 0x18)) < x) {
                        (*(s32 *)((u8 *)scratch + 0x18)) = x;
                    }
                }
                i--;
            } while (i >= 0);

            (*(s32 *)((u8 *)scratch + 0x14)) =
                ((*(s32 *)((u8 *)scratch + 0x14)) - 0x20) & ~0x3F;
            (*(s32 *)((u8 *)scratch + 0x18)) =
                ((*(s32 *)((u8 *)scratch + 0x18)) + 0x20) & ~0x3F;
            min_y = (*(s32 *)((u8 *)scratch + 0x14));
            if (min_y < 0) {
                min_y += 0x3F;
            }
            row = (*(s32 *)((u8 *)scratch + 0x0C));
            (*(s32 *)((u8 *)scratch + 0x134)) = min_y >> 6;
            if (row < 0) {
                row += 0x3F;
            }
            row >>= 6;
            (*(s32 *)((u8 *)scratch + 0x138)) = row;
            if (row < 0) {
                (*(s32 *)((u8 *)scratch + 0x138)) = 0;
                goto row_ready;
            }
            row_bound = (*(s32 *)((u8 *)scratch + 0x120));
            if (row < row_bound) {
                goto row_in_range;
            }
            row_base = row_bound << (*(s32 *)((u8 *)scratch + 0x124));
            goto store_row_base;
    row_in_range:
            row_base = row << (*(s32 *)((u8 *)scratch + 0x124));
    store_row_base:
            (*(s32 *)((u8 *)scratch + 0x138)) = row_base;
    row_ready:

            i = 3;
            if ((*(s32 *)((u8 *)scratch + 0x14)) <= (*(s32 *)((u8 *)scratch + 0x18))) {
                do {
                    packet_use = (u8 *)list + 7;
                    value = (*(s32 *)((u8 *)scratch + 0x134));
                    if (value < 0) {
                        av = (*(s32 *)((u8 *)scratch + 0x138));
                        value &= 3;
                        av += value;
                        (*(s32 *)((u8 *)scratch + 0x144)) = av;
                    } else {
                        col = (*(s32 *)((u8 *)scratch + 0x11C));
                        if (value >= col) {
                            av = (*(s32 *)((u8 *)scratch + 0x138));
                            value &= 3;
                            av += col;
                            av += value;
                            av -= 3;
                            (*(s32 *)((u8 *)scratch + 0x144)) = av;
                        } else {
                            av = (*(s32 *)((u8 *)scratch + 0x138));
                            av += value;
                            (*(s32 *)((u8 *)scratch + 0x144)) = av;
                        }
                    }
                    width = table[(*(s32 *)((u8 *)scratch + 0x144))];
                    (*(s32 *)((u8 *)scratch + 0x0C0)) = width;
                    if (width == 0) {
                        width = (*(u16 *)((u8 *)scratch + 0x14));
                        depth = (*(u16 *)((u8 *)scratch + 0x0C));
                        (*(u16 *)((u8 *)scratch + 0x0FC)) = 0;
                        (*(u16 *)((u8 *)scratch + 0x0F4)) = 0;
                        (*(u16 *)((u8 *)scratch + 0x0EC)) = 0;
                        (*(u16 *)((u8 *)scratch + 0x0E4)) = 0;
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
                        (*(u16 *)((u8 *)scratch + 0x0F0)) = width;
                        (*(u16 *)((u8 *)scratch + 0x0E0)) = width;
                        width += 0x40;
                        y40 += 0x40;
                        (*(u16 *)((u8 *)scratch + 0x0F8)) = width;
                        (*(u16 *)((u8 *)scratch + 0x0E8)) = width;
                        (*(u16 *)((u8 *)scratch + 0x0FA)) = y40;
                        (*(u16 *)((u8 *)scratch + 0x0F2)) = y40;
                        (*(u16 *)((u8 *)scratch + 0x0EA)) = depth;
                        (*(u16 *)((u8 *)scratch + 0x0E2)) = depth;

                        gte_ldv3(gte_input, scratch + 0xE8, scratch + 0xF0);
                        gte_rtpt();
                        gte_nclip();
                        gte_stopz(scratch + 0xDC);
                        if ((*(s32 *)((u8 *)scratch + 0x0DC)) > 0) {
                            gte_stsxy3_g3(list);
                            gte_stdp(scratch + 0xC0);
                            gte_avsz3();
                            gte_stotz(scratch + 0xC8);
                            gte_ldv0(scratch + 0xF8);
                            gte_rtps();
                            gte_stsxy((u8 *)list + 0x20);
                            gte_stdp(scratch + 0xC4);
                            gte_stszotz(scratch + 0xD4);

                            av = (*(s32 *)((u8 *)scratch + 0x0C8));
                            bv = (*(s32 *)((u8 *)scratch + 0x0D4));
                            av_shift = av << 1;
                            (*(s32 *)((u8 *)scratch + 0x0C8)) =
                                (av + av_shift + bv + 3) >> 2;
                            if ((u32)(*(s32 *)((u8 *)scratch + 0x0C8)) >= 0x1E0U) {
                                (*(s32 *)((u8 *)scratch + 0x0C8)) = 0x1DF;
                            }
                            av = (*(s32 *)((u8 *)scratch + 0x0C0));
                            bv = (*(s32 *)((u8 *)scratch + 0x0C4));
                            av_shift = av << 1;
                            (*(s32 *)((u8 *)scratch + 0x0C0)) =
                                (av + av_shift + bv) >> 2;

                            gte_ldv0(scratch + 0x17C);
                            gte_ldrgb(scratch);
                            vz = (*(u16 *)((u8 *)scratch + 0x0FC));
                            vz = (s16)vz;
                            ir0 = 0;
                            if (vz > 0) {
                                ir0 = vz << 2;
                            }
                            gte_ldir0(ir0);
                            ((S_800AD138_2_pre *)packet_use)[-1].unk_00 = 9;
                            gte_ncds_nn();
                            gte_strgb((u8 *)list + 4);

                            c1b = (*(u8 *)((u8 *)scratch + 0x20C));
                            ((S_800AD138_2 *)packet_use)->unk_15 = c1b;
                            ((S_800AD138_2 *)packet_use)->unk_05 = c1b;
                            c2 = (*(u8 *)((u8 *)scratch + 0x20C)) + 0x3F;
                            ((S_800AD138_2 *)packet_use)->unk_1D = c2;
                            ((S_800AD138_2 *)packet_use)->unk_0D = c2;
                            c3 = -(s32)(*(u8 *)((u8 *)scratch + 0x20C));
                            b2 = ((S_800AD138_2_pre *)packet_use)[-1].unk_01;
                            ((S_800AD138_2 *)packet_use)->unk_0E = c3;
                            ((S_800AD138_2 *)packet_use)->unk_06 = c3;
                            c4 = (*(u8 *)((u8 *)scratch + 0x20C));
                            (*(s16 *)((u8 *)packet_use + 0x0F)) = 0x2D;
                            (*(s16 *)((u8 *)packet_use + 7)) = 0x75C1;
                            ((S_800AD138_2_pre *)packet_use)[-1].unk_01 = b2 >> 1;
                            ((S_800AD138_2_pre *)packet_use)[-1].unk_02 >>= 1;
                            value2 = 0x3F - c4;
                            ((S_800AD138_2 *)packet_use)->unk_1E = value2;
                            ((S_800AD138_2 *)packet_use)->unk_16 = value2;
                            ((S_800AD138_2_pre *)packet_use)[-1].unk_03 >>= 1;
                            bcv = ((S_800AD138_4 *)((void *)(*(s32 *)((u8 *)scratch + 0xBC))))->unk_00;
                            av2 = ((S_800AD138_3 *)((u8 *)list))->unk_00;
                            ((S_800AD138_3 *)((u8 *)list))->unk_00 =
                                (av2 & mask_hi) |
                                (bcv & mask24);
                            value3 = (s32)list & mask24;
                            list += 10;
                            ((S_800AD138_4 *)((void *)(*(s32 *)((u8 *)scratch + 0xBC))))->unk_00 =
                                (((S_800AD138_4 *)((void *)(*(s32 *)((u8 *)scratch + 0xBC))))->unk_00 & mask_hi) |
                                value3;
                            if (arg0 < (u32)list) {
                                goto done;
                            }
                        }
                    }
                    (*(s32 *)((u8 *)scratch + 0x134)) += 1;
                    t5 = (*(s32 *)((u8 *)scratch + 0x14)) + 0x40;
                    (*(s32 *)((u8 *)scratch + 0x14)) = t5;
                    if ((*(s32 *)((u8 *)scratch + 0x18)) < t5) {
                        break;
                    }
                } while (1);
            }

            i = 3;
            neg1 = -1;
            (*(s32 *)((u8 *)scratch + 0x0C)) += 0x40;
            do {
                if ((*(s32 *)((u8 *)scratch + 0x38 + i * 0x28)) > 0) {
                    t4 = (*(s32 *)((u8 *)scratch + 0x28 + i * 0x28)) - 0x40;
                    (*(s32 *)((u8 *)scratch + 0x28 + i * 0x28)) = t4;
                    if (t4 <= 0) {
                        (*(s32 *)((u8 *)scratch + 0x38 + i * 0x28)) = neg1;
                        (*(u16 *)((u8 *)scratch + 0x170)) -= 1;
                    }
                }
                i--;
            } while (i >= 0);
            i = 3;
        } while ((*(u16 *)((u8 *)scratch + 0x170)) != 0);
    }

done:
    sp_pair[1] = 0x400040;
    sp_pair[0] = 0;
    func_80067F20(list, 0, 0, 0x20, sp_pair);
    func_8006658C((void *)(*(s32 *)((u8 *)scratch + 0xBC)), list);
    list += 3;
    ((S_800AD138_5 *)(((S_800AD138_1 *)state)->unk_00))->unk_8D0 = list;
    return;
}
