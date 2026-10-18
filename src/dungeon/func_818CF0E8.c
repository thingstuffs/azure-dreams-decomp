#include "shared/object_node.h"
#include "modules/dungeon_ovl_18ee800.h"
#include "common.h"
#include "shared/slus_callbacks.h"
#include "shared/object_flags.h"
extern int abs(int);

   /* the 0x2 bytes before entity in update_chasing_star_effect, addressed as entity[-1] */

   /* entity in update_chasing_star_effect */

   /* pos in update_chasing_star_effect */

   /* star in update_chasing_star_effect */

   /* gfx in update_chasing_star_effect */

   /* s3 in update_chasing_star_effect */

   /* obj in update_chasing_star_effect */

   /* p in update_chasing_star_effect */

   /* env in update_chasing_star_effect */

   /* the 0x18 bytes before ((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_30 in update_chasing_star_effect, addressed as ((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_30[-1] */

   /* ((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_34 in update_chasing_star_effect */







extern B32_818CF0E8_Vec12 D_8002590C;
extern B32_818CF0E8_Vec12 D_80025918;
extern u8 D_800DE870[];
extern u8 D_800DEC00[];
extern u8 D_800E3D68[];

/* Per-frame chasing-star step: drift toward the player, steer around the map and spawn the two trailing sprites. */
void update_chasing_star_effect(void *entity, B32_818CF0E8_S_818CF0E8_1 *pos, B32_818CF0E8_S_818CF0E8_3 *gfx)
{
    u8 *star;
    B32_818CF0E8_S_818CF0E8_7 *env;
    void *obj;
    void *p;
    s32 dv;
    s32 av;
    u16 flags;
    s16 cnt;
    s32 r;
    s32 b;
    u8 *src;
    s32 w1;
    u32 hi;

    D_80025924[0] = 1;
    env = ((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_2C;
    if (((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_00.s == 0) {
        p = (void *)0;
        loop_0: {
            s32 a3v;
            s32 rv;
            rv = func_80069EF8();
            w1 = (s32)((u8 *)entity - 0x20);
            src = (u8 *)(0xC0C0C0);
            a3v = (rv & 0xFF) | 0x80;
            func_80024358((void *)w1, ((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_16, (s32)src, a3v, 0, 0, 0);
            p = (u8 *)p + 1;
        } if ((s32)p < 4) goto loop_0;
        if ((check_adjacent_tile_height_clearance(pos->unk_00.at02.v, pos->unk_04.at02.v,
                           pos->unk_08.at02.v, ((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_30) << 0x10) != 0) {
            ((B32_818CF0E8_S_818CF0E8_9 *)(((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_34))->unk_86 = 1;
            ((B32_818CF0E8_S_818CF0E8_0_pre *)entity)[-1].unk_00 |= 0x8000;
            object_flag_block.flags |= 0x8000;
            return;
        }
        if (((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_08 != 0) {
            u16 a2v;
            u16 a1v;
            star = ((B32_818CF0E8_S_818CF0E8_8_pre *)(((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_30))[-1].unk_00;
            if (pos->unk_08.at00.v < ((B32_818CF0E8_S_818CF0E8_2 *)star)->unk_08.at00.v + (s32)0xFF800000) {
                ((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_54 /= 2;
            }
            {
            s32 d;
            s32 aw;
            d = pos->unk_00.at02u.v;
            d -= ((B32_818CF0E8_S_818CF0E8_2 *)star)->unk_02.s;
            aw = d;
            aw = abs(aw);
            if (aw < 8) {
                s32 a;
                s32 lim;
                s32 x_speed;
                lim = 0x40000;
                x_speed = ((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_4C;
                a = x_speed;
                a = abs(a);
                if (a > lim) {
                    ((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_4C = x_speed / 2;
                }
            } else if (((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_4C == 0) {
                s32 nv = -0x200000;
                if (d <= 0) {
                    nv = 0x200000;
                }
                ((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_4C = nv;
            }
            }
            {
            s32 d;
            s32 aw;
            d = pos->unk_04.at02u.v;
            d -= ((B32_818CF0E8_S_818CF0E8_2 *)star)->unk_06.s;
            aw = (d >= 0) ? d : (0 - d);
            if (aw < 8) {
                s32 v;
                s32 a;
                s32 lim;
                lim = 0x40000;
                v = ((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_50;
                a = v;
                a = abs(a);
                if (a > lim) {
                    ((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_50 = v / 2;
                }
            } else if (((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_50 == 0) {
                s32 nv = -0x200000;
                if (d <= 0) {
                    nv = 0x200000;
                }
                ((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_50 = nv;
            }
            }
            {
                s32 aw;
                s32 d;
                s32 st;
                a2v = pos->unk_00.at02.v;
                d = pos->unk_00.at02u.v;
                a1v = ((B32_818CF0E8_S_818CF0E8_2 *)star)->unk_02.u;
                st = ((B32_818CF0E8_S_818CF0E8_2 *)star)->unk_02.s;
                d -= st;
                aw = (d >= 0) ? d : (0 - d);
                if (aw >= 0xC1) {
                    pos->unk_00.at00.v += ((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_4C;
                } else if (aw >= 4) {
                    pos->unk_00.at00.v += (((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_4C * aw) / 192;
                } else if (((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_38 != ((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_3C) {
                    s32 one;
                    one = 1;
                    ((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_00.s = one;
                    ((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_02.s = 0;
                }
                if (((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_38 != ((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_3C) {
                    s32 v = ((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_4C;
                    if (v > 0) {
                        if ((s32)(a1v << 0x10) <= (s32)(a2v << 0x10)) {
                            ((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_00.s = 1;
                            ((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_02.s = 0;
                        }
                    } else if (v < 0) {
                        if ((s32)(a2v << 0x10) <= (s32)(a1v << 0x10)) {
                            ((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_00.s = 1;
                            ((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_02.s = 0;
                        }
                    }
                }
            }
            {
                s32 aw;
                s32 d;
                s32 st;
                a2v = pos->unk_04.at02.v;
                d = pos->unk_04.at02u.v;
                a1v = ((B32_818CF0E8_S_818CF0E8_2 *)star)->unk_06.u;
                st = ((B32_818CF0E8_S_818CF0E8_2 *)star)->unk_06.s;
                d -= st;
                aw = (d >= 0) ? d : (0 - d);
                if (aw >= 0xC1) {
                    pos->unk_04.at00.v += ((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_50;
                } else if (aw >= 4) {
                    pos->unk_04.at00.v += (((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_50 * aw) / 192;
                } else if (((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_3A != ((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_3E) {
                    s32 one;
                    one = 1;
                    ((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_00.s = one;
                    ((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_02.s = 0;
                }
                if (((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_3A != ((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_3E) {
                    s32 v = ((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_50;
                    if (v > 0) {
                        if ((s32)(a1v << 0x10) <= (s32)(a2v << 0x10)) {
                            ((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_00.s = 1;
                            ((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_02.s = 0;
                        }
                    } else if (v < 0) {
                        if ((s32)(a2v << 0x10) <= (s32)(a1v << 0x10)) {
                            ((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_00.s = 1;
                            ((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_02.s = 0;
                        }
                    }
                }
            }
            {
                s32 aw;
                s32 d;
                s32 st;
                if (((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_4C != 0) {
                    a2v = pos->unk_00.at02.v;
                    a1v = ((B32_818CF0E8_S_818CF0E8_2 *)star)->unk_02.u;
                } else {
                    a2v = pos->unk_04.at02.v;
                    a1v = ((B32_818CF0E8_S_818CF0E8_2 *)star)->unk_06.u;
                }
                d = (s16)a2v;
                st = (s16)a1v;
                d -= st;
                aw = abs(d);
                if (aw >= 0xC1) {
                    pos->unk_08.at00.v += ((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_54;
                } else if (aw >= 4) {
                    pos->unk_08.at00.v += (((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_54 * aw) / 192;
                }
            }
        } else {
            ((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_04.s -= 1;
            pos->unk_00.at00.v += ((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_4C;
            pos->unk_04.at00.v += ((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_50;
            pos->unk_08.at00.v += ((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_54;
            if (((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_04.u <= 0) {
                ((B32_818CF0E8_S_818CF0E8_9 *)(((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_34))->unk_86 = 1;
                ((B32_818CF0E8_S_818CF0E8_0_pre *)entity)[-1].unk_00 |= 0x8000;
                object_flag_block.flags |= 0x8000;
                return;
            }
        }
    }
    if (((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_00.s == 1) {
        if (((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_02.s == 0) {
            play_sound_if_enabled(0x300);
            func_800542BC();
        }
        cnt = ((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_02.u + 1;
        ((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_02.s = cnt;
        if (cnt >= 0xF) {
            ((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_02.s = 0;
            ((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_00.u += 1;
        }
    }
    if (((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_00.s == 2) {
        ((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_02.u += 1;
        gfx->unk_1C -= 0x32;
        gfx->unk_1E -= 0x32;
        obj = func_8003FC64(0x212);
        {
            u8 *s3;
            s3 = (u8 *)obj;
            s3 += 0x20;
            if (obj != 0) {
            ((B32_818CF0E8_S_818CF0E8_4 *)s3)->unk_02 = 0x34;
            ((B32_818CF0E8_S_818CF0E8_5 *)obj)->unk_10 = func_800245C8;
            func_8004491C(obj, func_80045340);
            p = ((B32_818CF0E8_S_818CF0E8_5 *)obj)->unk_0C;
            ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_14.s |= 0xC;
            ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_10 = 0x60;
            ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_14.s |= 2;
            p = ((B32_818CF0E8_S_818CF0E8_5 *)obj)->unk_08;
            {
                s32 r2;
                s32 b2;
                r2 = func_80069EF8() & 0x1F;
                b2 = pos->unk_00.at02.v - 0x10;
                b2 += r2;
                ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_02.s = b2;
            }
            {
                s32 r2;
                s32 b2;
                r2 = func_80069EF8() & 0x1F;
                b2 = pos->unk_04.at02.v - 0x10;
                b2 += r2;
                ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_06.s = b2;
            }
            ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_08.at02.v = pos->unk_08.at02u.v;
            ((B32_818CF0E8_S_818CF0E8_4 *)s3)->unk_54 = func_80069EF8() + 0x30000;
            ((B32_818CF0E8_S_818CF0E8_4 *)s3)->unk_60 = 0x6000;
            p = ((B32_818CF0E8_S_818CF0E8_5 *)obj)->unk_0C;
            ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_1C = 0x800;
            ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_1E = 0x800;
            ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_0E = 0x80;
            ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_0D = 0x80;
            ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_0C = 0x80;
            flags = ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_14.u | 0x100;
            ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_12 = 0x7DCF;
            ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_14.s = flags;
            func_8003DB94(p, D_800DE870, 0);
            }
        }
        if ((((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_02.u & 3) == 1) {
            obj = func_8003FC64(0x212);
            {
            w1 = (s32)((u8 *)obj + 0x20);
            if (obj != 0) {
                ((B32_818CF0E8_S_818CF0E8_4 *)w1)->unk_02 = 0x14;
                ((B32_818CF0E8_S_818CF0E8_5 *)obj)->unk_10 = func_80024478;
                func_8004491C(obj, func_80045340);
                p = ((B32_818CF0E8_S_818CF0E8_5 *)obj)->unk_0C;
                flags = ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_14.s | 0xC;
                ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_10 = 0;
                ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_14.s = flags;
                p = ((B32_818CF0E8_S_818CF0E8_5 *)obj)->unk_08;
                star = ((B32_818CF0E8_S_818CF0E8_8_pre *)(((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_30))[-1].unk_00;
                {
                    s32 r2;
                    s32 b2;
                    r2 = func_80069EF8() & 0x1F;
                    b2 = ((B32_818CF0E8_S_818CF0E8_2 *)star)->unk_02.u - 0x10;
                    b2 += r2;
                ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_02.s = b2;
                }
                {
                    s32 r2;
                    s32 b2;
                    r2 = func_80069EF8() & 0x1F;
                    b2 = ((B32_818CF0E8_S_818CF0E8_2 *)star)->unk_06.u - 0x10;
                    b2 += r2;
                ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_06.s = b2;
                }
                {
                    s32 r2;
                    s32 b2;
                    r2 = (func_80069EF8() & 0x3F) + 0x20;
                    b2 = ((B32_818CF0E8_S_818CF0E8_2 *)star)->unk_08.at02.v;
                    b2 -= r2;
                    ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_08.at02u.v = b2;
                }
                p = ((B32_818CF0E8_S_818CF0E8_5 *)obj)->unk_0C;
                ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_1C = 0x800;
                ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_1E = 0x800;
                ((B32_818CF0E8_S_818CF0E8_4 *)w1)->unk_54 = func_80069EF8() + (s32)0xFFFE0000;
                ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_0E = 0x80;
                ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_0D = 0x80;
                ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_0C = 0x80;
                flags = ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_14.u | 0x100;
                ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_12 = 0x7DC0;
                ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_14.s = flags;
                func_8003DB94(p, D_800DEC00, 0);
            }
            }
        }
        if (((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_02.s >= 0x29) {
            ((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_02.s = 0;
            ((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_00.u += 1;
            if (try_trigger_target_record_effect(env->unk_60, 2, env) == 0) {
                s32 a2v;
                s32 a1v;
                s32 rr;
                rr = (generate_random_value() & 3) + 2;
                a2v = (((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_15 >> 2) + rr;
                a1v = 0x10;
                if (D_800E3D68[0] == 0xFF) {
                    a1v = 0xFF;
                }
                try_apply_confusion_status(((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_30, a1v, a2v);
            }
        }
    }
    if (((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_00.s == 3) {
        ((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_02.u += 1;
        gfx->unk_1C -= 0x32;
        gfx->unk_1E -= 0x32;
        if (((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_02.s >= 0x15) {
            ((B32_818CF0E8_S_818CF0E8_9 *)(((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_34))->unk_86 = 1;
            ((B32_818CF0E8_S_818CF0E8_0_pre *)entity)[-1].unk_00 |= 0x8000;
            object_flag_block.flags |= 0x8000;
            return;
        }
    }
    obj = func_8003FC64(0x12);
    if (obj != 0) {
        ((B32_818CF0E8_S_818CF0E8_5 *)obj)->unk_22 = 1;
        ((B32_818CF0E8_S_818CF0E8_5 *)obj)->unk_10 = update_actor_effect_sequence;
        func_8004491C(obj, func_80045340);
        p = ((B32_818CF0E8_S_818CF0E8_5 *)obj)->unk_0C;
        flags = ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_14.s | 0xC;
        ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_10 = 0x60;
        ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_14.s = flags;
        p = ((B32_818CF0E8_S_818CF0E8_5 *)obj)->unk_08;
        ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_02.u = pos->unk_00.at02.v;
        ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_06.u = pos->unk_04.at02.v;
        ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_08.at02.v = pos->unk_08.at02u.v;
        p = ((B32_818CF0E8_S_818CF0E8_5 *)obj)->unk_0C;
        ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_1E = 0x1000;
        ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_1C = 0x1000;
        ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_06.s = -1;
        ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_0C = gfx->unk_0C;
        ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_0D = gfx->unk_0D;
        ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_0E = gfx->unk_0E;
        hi = func_80069EF8() & 0xFFF;
        ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_1A = hi;
        *(B32_818CF0E8_Vec12 *)((u8 *)obj + 0x40) = D_8002590C;
        ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_08.at00.v = (u8 *)obj + 0x40;
    }
    obj = func_8003FC64(0x12);
    if (obj != 0) {
        ((B32_818CF0E8_S_818CF0E8_5 *)obj)->unk_22 = 1;
        ((B32_818CF0E8_S_818CF0E8_5 *)obj)->unk_10 = update_actor_effect_sequence;
        func_8004491C(obj, func_80045340);
        p = ((B32_818CF0E8_S_818CF0E8_5 *)obj)->unk_0C;
        flags = ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_14.s | 0xC;
        ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_10 = 0x60;
        ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_14.s = flags;
        p = ((B32_818CF0E8_S_818CF0E8_5 *)obj)->unk_08;
        ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_02.u = pos->unk_00.at02.v;
        ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_06.u = pos->unk_04.at02.v;
        ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_08.at02.v = pos->unk_08.at02u.v;
        p = ((B32_818CF0E8_S_818CF0E8_5 *)obj)->unk_0C;
        ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_1E = 0x1000;
        ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_1C = 0x1000;
        ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_06.s = -2;
        ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_0C = gfx->unk_0C;
        ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_0D = gfx->unk_0D;
        ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_0E = gfx->unk_0E;
        hi = func_80069EF8() & 0xFFF;
        ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_1A = hi;
        *(B32_818CF0E8_Vec12 *)((u8 *)obj + 0x40) = D_80025918;
        ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_08.at00.v = (u8 *)obj + 0x40;
    }
    gfx->unk_1A = func_80069EF8() & 0xFFF;
}
