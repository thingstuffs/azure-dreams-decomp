#include "common.h"

#ifndef NULL
#define NULL 0
#endif

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

extern volatile u16 D_800135C0;
extern u8 D_80022B80[];
extern s16 D_800272A0[];
extern u8 D_80045340[];
extern s32 D_800814A0;
extern u8 D_80083160[];
extern u8 D_80083498[];
extern void *D_800834B8;
extern u8 D_80083780[];
extern s32 D_800D0428;
extern u8 D_80092698[];
extern u8 D_800927EC[];
extern u8 D_80092A84[];
extern u8 D_800F2DC0[];
extern u8 D_800F2E08[];
extern u8 D_800F2E50[];
extern u8 D_800F2E98[];
extern u8 D_800F2EE0[];
extern u8 D_800F2F28[];
extern u8 D_800F2F80[];
extern u8 D_800F2FE0[];
extern u8 D_800F3020[];

extern void func_80033B78(s32);
extern void func_80033B9C(s32);
extern void func_8003DB94(void *, void *, s32);
extern void func_8003F540(s32, s32, s32, s32);
extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern void func_800478B8(void *);
extern void func_80053DA8(s32);
extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);
extern void func_8008F134(void *);
extern void func_8009539C(void *);
extern s32 func_800C2AE8(void *);

void func_80020DF0(void *arg0, void *arg1, void *arg2)
{
    u8 *effect;
    void *actor;
    s32 limit;
    s16 state;
    u16 state_u;
    u8 *world;
    void **music;
    s32 i;

    effect = NULL;
    actor = NULL;
    world = D_80083160;
    music = &D_800834B8;

    limit = (s16)func_800C2AE8(arg1);
    if (FIELD(arg0, s16, 0x68) < 0xFF) {
        s32 actor_state;

        actor = FIELD(arg0, void *, 0xAC);
        actor_state = FIELD(actor, s16, 0x36);
        if (actor_state == 0xFF) {
            FIELD(arg0, s16, 0x68) = actor_state;
        }
    }
    func_8009539C(arg1);
    if (FIELD(arg1, s16, 0xA) >= limit) {
        FIELD(arg1, s16, 0xA) = limit;
    }
    func_800478B8(arg2);

    state = FIELD(arg0, s16, 0x68);
    state_u = FIELD(arg0, u16, 0x68);
    switch (state) {
    case 0:
        FIELD(arg1, s32, 0) = 0x03A00000;
        FIELD(arg1, s32, 4) = 0x01E00000;
        FIELD(arg1, s16, 0xA) = func_800C2AE8(arg1);
        FIELD(arg0, s8, 0x15) = 0;
        FIELD(arg0, u16, 0x6C) = 0x40;
        FIELD(arg0, s16, 0x68) = 1;
        /* fall through */

    case 1:
        if (FIELD(arg2, u16, 0x14) & 0x6000) {
            FIELD(arg1, s32, 0x10) = 0x80000;
            effect = D_800F2DC0;
        }
        if (FIELD(arg0, s32, 0xA8) & 1) {
            u16 timer;

            timer = FIELD(arg0, u16, 0x6C) - 1;
            FIELD(arg0, u16, 0x6C) = timer;
            if ((s16)timer >= 0) {
                FIELD(arg1, s32, 0) =
                    (func_800644B8((s16)timer << 7) << 7) + 0x03A00000;
            }
        }
        if (FIELD(arg1, s32, 4) > 0x0477FFFF) {
            effect = D_800F2E08;
            FIELD(arg2, u16, 0x14) |= 1;
            FIELD(arg1, s32, 0xC) = 0x80000;
            FIELD(arg0, s16, 0x68) = 2;
        }
        goto cleanup;

    case 2:
        if (FIELD(arg2, u16, 0x14) & 0x6000) {
            effect = D_800F2E98;
        }
        if (FIELD(arg1, s32, 4) > 0x048FFFFF) {
            effect = D_800F2E50;
            FIELD(arg1, s32, 0x10) = 0;
            FIELD(arg0, s16, 0x68) = 3;
        }
        goto cleanup;

    case 3:
        if (FIELD(arg2, u16, 0x14) & 0x6000) {
            effect = D_800F2E98;
        }
        if (FIELD(arg1, s32, 0) > 0x03DFFFFF) {
            effect = D_800F2F28;
            FIELD(arg1, s32, 0x14) = -0x100000;
            FIELD(arg0, s16, 0x68) = 4;
        }
        goto cleanup;

    case 4:
        {
            s32 x;

            x = FIELD(arg1, s32, 0);
            FIELD(arg1, s32, 0x14) += 0x48000;
            if (x > 0x041FFFFF) {
                FIELD(arg1, s32, 0x14) = 0;
                FIELD(arg1, s32, 0xC) = 0;
                FIELD(arg0, s8, 0x15) = 1;
                FIELD(arg0, s16, 0x68) = 5;
            }
        }
        goto cleanup;

    case 5:
        if (*music == D_80092698) {
            FIELD(arg0, u16, 0x6C) = 7;
            *music = D_800927EC;
            FIELD(arg0, s8, 0x15) = 0;
            FIELD(arg0, s16, 0x68) = 6;
        }
        goto cleanup;

    case 6:
        {
            u8 *target;
            s32 sum;
            s32 base_h;

            target = D_80083780;
            FIELD(arg1, s32, 0xC) =
                (FIELD(target, s32, 0) - FIELD(arg1, s32, 0)) >> 1;
            FIELD(arg1, s32, 0x10) =
                (FIELD(target, s32, 4) - FIELD(arg1, s32, 4)) >> 1;
            sum = FIELD(target, s32, 8) + D_800D0428;
            base_h = FIELD(arg1, s32, 8) + 0x80000;
            FIELD(arg1, s32, 0x14) = (sum - base_h) >> 1;
            func_8009539C(arg1);
            *music = D_800927EC;
            FIELD(arg0, u16, 0x6C)--;
            if ((s16)FIELD(arg0, u16, 0x6C) <= 0) {
                *music = D_800927EC;
                FIELD(arg1, s32, 0x14) = 0;
                FIELD(arg1, s32, 0x10) = 0;
                FIELD(arg1, s32, 0xC) = 0;
                FIELD(arg0, s16, 0x68) = 7;
            }
        }
        goto cleanup;

    case 7:
    case 8:
    case 9:
        {
            u8 *target;

            target = D_80083780;
            FIELD(arg1, s32, 0) = FIELD(target, s32, 0);
            FIELD(arg1, s32, 4) = FIELD(target, s32, 4);
            FIELD(arg1, s32, 8) =
                FIELD(target, s32, 8) + D_800D0428 - 0x80000;
            if (FIELD(world, s32, 0x10) & 0x40) {
                if (FIELD(target, s16, 0xA) == 0) {
                    if (FIELD(arg0, s16, 0x68) == 9) {
                        FIELD(actor, s32, 0) = 0x100000;
                        effect = D_800F2FE0;
                    } else {
                        *music = D_80092A84;
                        FIELD(arg1, s32, 0x14) = 0x100000;
                    }
                    FIELD(actor, u16, 0x2A) &= 0xFFFB;
                    FIELD(arg0, u16, 0x68)++;
                } else {
                    *music = D_800927EC;
                }
                if (FIELD(arg0, s16, 0x68) == 0xA) {
                    func_80053DA8(0x700);
                }
            }
        }
        goto cleanup;

    case 10:
        {
            s32 velocity;
            s32 x;

            FIELD(arg1, s32, 0xC) =
                (FIELD(actor, s32, 0) >> 12) *
                func_800644B8(FIELD(actor, s16, 0x2C));
            velocity = ((-FIELD(actor, s32, 0)) >> 12) *
                func_80064584(FIELD(actor, s16, 0x2C));
            FIELD(arg1, s32, 0x10) = velocity;
            if (velocity > -0x40000) {
                FIELD(arg1, s32, 0x10) = -0x40000;
            }
            FIELD(actor, s16, 0x2C) =
                FIELD(actor, u16, 0x2C) - ((s16)FIELD(actor, u16, 0x2E) >> 4);

            if (FIELD(arg1, s32, 8) > 0) {
                u16 flags;

                flags = FIELD(actor, u16, 0x2A);
                if (!(flags & 4)) {
                    FIELD(actor, u16, 0x2A) = flags | 4;
                    func_80053DA8(0x701);
                }
                x = FIELD(arg1, s32, 0);
                FIELD(arg1, s32, 8) = 0x200000;
                if (x <= 0x041FFFFF) {
                    if (x <= 0x03BFFFFF) {
                        if (x <= 0x03800000) {
                            FIELD(arg1, s32, 0) = 0x03880000;
                        }
                    } else {
                        FIELD(arg1, s32, 0) = 0x03B80000;
                    }
                } else {
                    if (x > 0x04BFFFFF) {
                        FIELD(arg1, s32, 0) = 0x04B80000;
                    } else if (x <= 0x04800000) {
                        FIELD(arg1, s32, 0) = 0x04880000;
                    }
                }
                FIELD(actor, s16, 0x2C) = -FIELD(actor, s16, 0x2C) >> 1;
            }

            if (FIELD(arg1, s32, 4) <= 0x01E00000) {
                s32 terrain;

                func_80053DA8(0x1700);
                func_80053DA8(0x1701);
                terrain = D_800272A0[FIELD(actor, s16, 0x34)];
                if (terrain == 8) {
                    s32 scale;
                    u8 *particle_data;

                    func_80053DA8(0x505);
                    i = 1;
                    scale = 0x1000;
                    particle_data = D_80022B80;
                    FIELD(arg0, s32, 0xA8) |= 1;
                    do {
                        void *particle;

                        particle = func_8003FD64(0x136, D_80083498);
                        if (particle != NULL) {
                            void *part;
                            void *link;

                            part = FIELD(particle, void *, 0xC);
                            func_8004491C(particle, D_80045340);
                            link = (u8 *)particle + 0x20;
                            FIELD(part, s32, 0xC) = 0x00808080;
                            FIELD(part, s16, 0x1E) = scale;
                            FIELD(part, s16, 0x1C) = scale;
                            FIELD(link, void *, 4) = arg1;
                            FIELD(link, s16, 2) = 0x78;
                            FIELD(particle, void *, 0x10) = particle_data;
                            func_8003DB94(part, D_800F3020, (s16)(i * 4));
                        }
                        i--;
                    } while (i >= 0);
                } else {
                    FIELD(arg0, s32, 0xA8) &= -2;
                }
                effect = D_800F2F80;
                FIELD(arg1, s32, 0x14) = 0;
                FIELD(arg1, s32, 0x10) = 0;
                FIELD(arg1, s32, 0xC) = 0;
                FIELD(arg0, u16, 0x6C) = 0x14;
                FIELD(arg0, s16, 0x68) = 0xB;
            }
        }
        goto cleanup;

    case 11:
        {
            u16 flags;
            s32 y;
            s32 x;

            flags = FIELD(arg2, u16, 0x14);
            if ((flags & 0x6000) && FIELD(arg0, s16, 0x6C) > 0) {
                effect = D_800F2DC0;
                FIELD(arg2, u16, 0x14) = flags | 0x800;
            }
            if (FIELD(arg1, s32, 0) > 0x03A00000) {
                FIELD(arg2, u16, 0x14) &= 0xFFFE;
            } else {
                FIELD(arg2, u16, 0x14) |= 1;
            }
            y = FIELD(arg1, s32, 4);
            FIELD(arg1, s32, 4) = y + ((0x01E00000 - y) >> 1);
            {
                s16 t68 = FIELD(arg0, u16, 0x6C) - 1;

                FIELD(arg0, s16, 0x6C) = t68;
                if (t68 == 0) {
                s32 x;

                FIELD(arg2, u16, 0x14) &= 0xF7FF;
                x = FIELD(arg1, s32, 0);
                if (x > 0x03A80000) {
                    FIELD(arg1, s32, 0xC) = -0x80000;
                } else if (x <= 0x0397FFFF) {
                    FIELD(arg1, s32, 0xC) = 0x80000;
                } else {
                    effect = D_800F2E50;
                    FIELD(arg1, s32, 0xC) = 0;
                    FIELD(arg1, s32, 0) = 0x03A00000;
                }
                }
            }
            if ((u32)(FIELD(arg1, s32, 0) - 0x03BC0000) <= 0xC80000) {
                FIELD(arg1, s32, 8) = 0;
            } else {
                FIELD(arg1, s32, 8) = 0x200000;
            }
            {
                register s32 ax ASM_REG("$2");

                ax = FIELD(arg1, s32, 0);
                ax = ax - 0x03A00000;
                if (ax < 0) {
                    ax = -ax;
                }
                ASM_KEEP(ax);
                if (ax <= 0x80000 && FIELD(arg0, s16, 0x6C) < 0) {
                    FIELD(actor, u16, 0x2A) |= 2;
                    FIELD(arg1, s32, 0x14) = 0;
                    FIELD(arg1, s32, 0x10) = 0;
                    FIELD(arg1, s32, 0xC) = 0;
                    FIELD(arg0, s16, 0x68) = 0;
                }
            }
        }
        goto cleanup;

    case 0xFF:
        {
            s32 total;
            s16 *table;
            s16 *entry;

            total = 0;
            i = 7;
            table = D_800272A0;
            entry = table + 7;
            do {
                total += *entry;
                entry--;
                i--;
            } while (i >= 0);

            {
                s16 cur = D_800135C0;
                s32 z = 0;

                if (cur < total || total == 0x40) {
                    func_8003F540(z, 0x2C3D, 0x01000001, 0x01000271);
                    func_80053DA8(0x300);
                    D_800135C0 = total;
                    func_80033B9C(0x5DA);
                } else {
                    func_8003F540(z, 0x2C3D, z, 0x01000290);
                    func_80053DA8(0x300);
                    func_80033B78(0x5DA);
                }
            }
            effect = D_800F2DC0;
            FIELD(arg1, s32, 0x10) = 0x80000;
            FIELD(arg0, u16, 0x6C) = 0x1E;
            FIELD(arg0, u16, 0x68)++;
        }
        /* fall through */

    case 0x100:
    case 0x102:
        FIELD(arg0, u16, 0x6C)--;
        if ((s16)FIELD(arg0, u16, 0x6C) <= 0) {
            FIELD(arg1, s32, 0x10) = 0;
            FIELD(arg1, s32, 0x14) = -0x100000;
            goto increment_state;
        }
        goto cleanup;

    case 0x101:
    case 0x103:
        {
            s32 height;

            height = FIELD(arg1, s32, 8);
            FIELD(arg1, s32, 0x14) += 0x20000;
            if (height > 0x1FFFFF) {
                FIELD(arg1, s32, 8) = 0x200000;
                FIELD(arg1, s32, 0x14) = 0;
                goto increment_state;
            }
        }
        goto cleanup;

    case 0x104:
        effect = D_800F2E08;
        goto effect_increment;

    case 0x105:
        effect = D_800F2E50;
        goto effect_increment;

    case 0x106:
        effect = D_800F2E98;

effect_increment:
        FIELD(arg0, s16, 0x68) = state_u + 1;
        goto cleanup;

    case 0x107:
        FIELD(arg1, s32, 0x10) = -0x80000;
        FIELD(arg2, s16, 0x10) = 0x60;
        FIELD(arg2, s32, 0xC) = 0x00C0C0C0;
        FIELD(arg2, u16, 0x14) |= 0xC;
        effect = D_800F2EE0;
        FIELD(arg0, u16, 0x68)++;
        goto cleanup;

    case 0x108:
        FIELD(arg2, s32, 0xC) += -0x80808;
        if ((u8)FIELD(arg2, u32, 0xC) < 0x11) {
            goto increment_state;
        }
        goto cleanup;

increment_state:
        FIELD(arg0, u16, 0x68)++;
        goto cleanup;

    case 0x109:
        func_8008F134(arg0);
        FIELD(arg0, u16, -2) |= 0x8000;
        D_800814A0 |= 0x8000;
        goto done;

    default:
        goto cleanup;
    }

cleanup:
    if (effect != NULL) {
        func_8003DB94(arg2, effect, 0);
    }

done:
    return;
}
