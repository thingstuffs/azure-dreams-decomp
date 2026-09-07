#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_80020DF0_0 {
    u8 pad_00[0x15];
    s8 unk_15;
    u8 pad_16[0x52];
    union { s16 s; u16 u; } unk_68;   /* accessed as both */
    u8 pad_6A[0x2];
    union { u16 s; s16 u; } unk_6C;   /* accessed as both */
    u8 pad_6E[0x3A];
    s32 unk_A8;
    void * unk_AC;
} S_80020DF0_0;   /* arg0 in func_80020DF0 */

typedef struct S_80020DF0_1 {
    s32 unk_00;
    u8 pad_04[0x26];
    u16 unk_2A;
    union { s16 s; u16 u; } unk_2C;   /* accessed as both */
    u16 unk_2E;
    u8 pad_30[0x4];
    s16 unk_34;
    s16 unk_36;
} S_80020DF0_1;   /* actor in func_80020DF0 */

typedef struct S_80020DF0_2 {
    s32 unk_00;
    s32 unk_04;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_08;   /* overlapping accesses */
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80020DF0_2;   /* arg1 in func_80020DF0 */

typedef struct S_80020DF0_3 {
    u8 pad_00[0xC];
    union { s32 s; u32 u; } unk_0C;   /* accessed as both */
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
} S_80020DF0_3;   /* arg2 in func_80020DF0 */

typedef struct S_80020DF0_4 {
    s32 unk_00;
    s32 unk_04;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_08;   /* overlapping accesses */
} S_80020DF0_4;   /* target in func_80020DF0 */

typedef struct S_80020DF0_5 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_80020DF0_5;   /* world in func_80020DF0 */

typedef struct S_80020DF0_6 {
    u8 pad_00[0xC];
    void * unk_0C;
    void * unk_10;
} S_80020DF0_6;   /* particle in func_80020DF0 */

typedef struct S_80020DF0_7 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u8 pad_10[0xC];
    s16 unk_1C;
    s16 unk_1E;
} S_80020DF0_7;   /* part in func_80020DF0 */

typedef struct S_80020DF0_8 {
    u8 pad_00[0x2];
    s16 unk_02;
    void * unk_04;
} S_80020DF0_8;   /* link in func_80020DF0 */



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
    if (((S_80020DF0_0 *)arg0)->unk_68.s < 0xFF) {
        s32 actor_state;

        actor = ((S_80020DF0_0 *)arg0)->unk_AC;
        actor_state = ((S_80020DF0_1 *)actor)->unk_36;
        if (actor_state == 0xFF) {
            ((S_80020DF0_0 *)arg0)->unk_68.s = actor_state;
        }
    }
    func_8009539C(arg1);
    if (((S_80020DF0_2 *)arg1)->unk_08.at02.v >= limit) {
        ((S_80020DF0_2 *)arg1)->unk_08.at02.v = limit;
    }
    func_800478B8(arg2);

    state = ((S_80020DF0_0 *)arg0)->unk_68.s;
    state_u = ((S_80020DF0_0 *)arg0)->unk_68.u;
    switch (state) {
    case 0:
        ((S_80020DF0_2 *)arg1)->unk_00 = 0x03A00000;
        ((S_80020DF0_2 *)arg1)->unk_04 = 0x01E00000;
        ((S_80020DF0_2 *)arg1)->unk_08.at02.v = func_800C2AE8(arg1);
        ((S_80020DF0_0 *)arg0)->unk_15 = 0;
        ((S_80020DF0_0 *)arg0)->unk_6C.s = 0x40;
        ((S_80020DF0_0 *)arg0)->unk_68.s = 1;
        /* fall through */

    case 1:
        if (((S_80020DF0_3 *)arg2)->unk_14 & 0x6000) {
            ((S_80020DF0_2 *)arg1)->unk_10 = 0x80000;
            effect = D_800F2DC0;
        }
        if (((S_80020DF0_0 *)arg0)->unk_A8 & 1) {
            u16 timer;

            timer = ((S_80020DF0_0 *)arg0)->unk_6C.s - 1;
            ((S_80020DF0_0 *)arg0)->unk_6C.s = timer;
            if ((s16)timer >= 0) {
                ((S_80020DF0_2 *)arg1)->unk_00 =
                    (func_800644B8((s16)timer << 7) << 7) + 0x03A00000;
            }
        }
        if (((S_80020DF0_2 *)arg1)->unk_04 > 0x0477FFFF) {
            effect = D_800F2E08;
            ((S_80020DF0_3 *)arg2)->unk_14 |= 1;
            ((S_80020DF0_2 *)arg1)->unk_0C = 0x80000;
            ((S_80020DF0_0 *)arg0)->unk_68.s = 2;
        }
        goto cleanup;

    case 2:
        if (((S_80020DF0_3 *)arg2)->unk_14 & 0x6000) {
            effect = D_800F2E98;
        }
        if (((S_80020DF0_2 *)arg1)->unk_04 > 0x048FFFFF) {
            effect = D_800F2E50;
            ((S_80020DF0_2 *)arg1)->unk_10 = 0;
            ((S_80020DF0_0 *)arg0)->unk_68.s = 3;
        }
        goto cleanup;

    case 3:
        if (((S_80020DF0_3 *)arg2)->unk_14 & 0x6000) {
            effect = D_800F2E98;
        }
        if (((S_80020DF0_2 *)arg1)->unk_00 > 0x03DFFFFF) {
            effect = D_800F2F28;
            ((S_80020DF0_2 *)arg1)->unk_14 = -0x100000;
            ((S_80020DF0_0 *)arg0)->unk_68.s = 4;
        }
        goto cleanup;

    case 4:
        {
            s32 x;

            x = ((S_80020DF0_2 *)arg1)->unk_00;
            ((S_80020DF0_2 *)arg1)->unk_14 += 0x48000;
            if (x > 0x041FFFFF) {
                ((S_80020DF0_2 *)arg1)->unk_14 = 0;
                ((S_80020DF0_2 *)arg1)->unk_0C = 0;
                ((S_80020DF0_0 *)arg0)->unk_15 = 1;
                ((S_80020DF0_0 *)arg0)->unk_68.s = 5;
            }
        }
        goto cleanup;

    case 5:
        if (*music == D_80092698) {
            ((S_80020DF0_0 *)arg0)->unk_6C.s = 7;
            *music = D_800927EC;
            ((S_80020DF0_0 *)arg0)->unk_15 = 0;
            ((S_80020DF0_0 *)arg0)->unk_68.s = 6;
        }
        goto cleanup;

    case 6:
        {
            u8 *target;
            s32 sum;
            s32 base_h;

            target = D_80083780;
            (*(s32 *)((u8 *)arg1 + 0xC)) =
                (((S_80020DF0_4 *)target)->unk_00 - ((S_80020DF0_2 *)arg1)->unk_00) >> 1;
            (*(s32 *)((u8 *)arg1 + 0x10)) =
                (((S_80020DF0_4 *)target)->unk_04 - ((S_80020DF0_2 *)arg1)->unk_04) >> 1;
            sum = ((S_80020DF0_4 *)target)->unk_08.at00.v + D_800D0428;
            base_h = ((S_80020DF0_2 *)arg1)->unk_08.at00.v + 0x80000;
            ((S_80020DF0_2 *)arg1)->unk_14 = (sum - base_h) >> 1;
            func_8009539C(arg1);
            *music = D_800927EC;
            (*(u16 *)((u8 *)arg0 + 0x6C))--;
            if ((s16)((S_80020DF0_0 *)arg0)->unk_6C.s <= 0) {
                *music = D_800927EC;
                ((S_80020DF0_2 *)arg1)->unk_14 = 0;
                ((S_80020DF0_2 *)arg1)->unk_10 = 0;
                ((S_80020DF0_2 *)arg1)->unk_0C = 0;
                ((S_80020DF0_0 *)arg0)->unk_68.s = 7;
            }
        }
        goto cleanup;

    case 7:
    case 8:
    case 9:
        {
            u8 *target;

            target = D_80083780;
            (*(s32 *)((u8 *)arg1 + 0)) = ((S_80020DF0_4 *)target)->unk_00;
            (*(s32 *)((u8 *)arg1 + 4)) = ((S_80020DF0_4 *)target)->unk_04;
            (*(s32 *)((u8 *)arg1 + 8)) =
                ((S_80020DF0_4 *)target)->unk_08.at00.v + D_800D0428 - 0x80000;
            if (((S_80020DF0_5 *)world)->unk_10 & 0x40) {
                if (((S_80020DF0_4 *)target)->unk_08.at02.v == 0) {
                    if (((S_80020DF0_0 *)arg0)->unk_68.s == 9) {
                        ((S_80020DF0_1 *)actor)->unk_00 = 0x100000;
                        effect = D_800F2FE0;
                    } else {
                        *music = D_80092A84;
                        ((S_80020DF0_2 *)arg1)->unk_14 = 0x100000;
                    }
                    ((S_80020DF0_1 *)actor)->unk_2A &= 0xFFFB;
                    ((S_80020DF0_0 *)arg0)->unk_68.u++;
                } else {
                    *music = D_800927EC;
                }
                if (((S_80020DF0_0 *)arg0)->unk_68.s == 0xA) {
                    func_80053DA8(0x700);
                }
            }
        }
        goto cleanup;

    case 10:
        {
            s32 velocity;
            s32 x;

            ((S_80020DF0_2 *)arg1)->unk_0C =
                (((S_80020DF0_1 *)actor)->unk_00 >> 12) *
                func_800644B8(((S_80020DF0_1 *)actor)->unk_2C.s);
            velocity = ((-((S_80020DF0_1 *)actor)->unk_00) >> 12) *
                func_80064584(((S_80020DF0_1 *)actor)->unk_2C.s);
            ((S_80020DF0_2 *)arg1)->unk_10 = velocity;
            if (velocity > -0x40000) {
                ((S_80020DF0_2 *)arg1)->unk_10 = -0x40000;
            }
            ((S_80020DF0_1 *)actor)->unk_2C.s =
                ((S_80020DF0_1 *)actor)->unk_2C.u - ((s16)((S_80020DF0_1 *)actor)->unk_2E >> 4);

            if (((S_80020DF0_2 *)arg1)->unk_08.at00.v > 0) {
                u16 flags;

                flags = ((S_80020DF0_1 *)actor)->unk_2A;
                if (!(flags & 4)) {
                    ((S_80020DF0_1 *)actor)->unk_2A = flags | 4;
                    func_80053DA8(0x701);
                }
                x = ((S_80020DF0_2 *)arg1)->unk_00;
                ((S_80020DF0_2 *)arg1)->unk_08.at00.v = 0x200000;
                if (x <= 0x041FFFFF) {
                    if (x <= 0x03BFFFFF) {
                        if (x <= 0x03800000) {
                            ((S_80020DF0_2 *)arg1)->unk_00 = 0x03880000;
                        }
                    } else {
                        ((S_80020DF0_2 *)arg1)->unk_00 = 0x03B80000;
                    }
                } else {
                    if (x > 0x04BFFFFF) {
                        ((S_80020DF0_2 *)arg1)->unk_00 = 0x04B80000;
                    } else if (x <= 0x04800000) {
                        ((S_80020DF0_2 *)arg1)->unk_00 = 0x04880000;
                    }
                }
                ((S_80020DF0_1 *)actor)->unk_2C.s = -((S_80020DF0_1 *)actor)->unk_2C.s >> 1;
            }

            if (((S_80020DF0_2 *)arg1)->unk_04 <= 0x01E00000) {
                s32 terrain;

                func_80053DA8(0x1700);
                func_80053DA8(0x1701);
                terrain = D_800272A0[((S_80020DF0_1 *)actor)->unk_34];
                if (terrain == 8) {
                    s32 scale;
                    u8 *particle_data;

                    func_80053DA8(0x505);
                    i = 1;
                    scale = 0x1000;
                    particle_data = D_80022B80;
                    ((S_80020DF0_0 *)arg0)->unk_A8 |= 1;
                    do {
                        void *particle;

                        particle = func_8003FD64(0x136, D_80083498);
                        if (particle != NULL) {
                            void *part;
                            void *link;

                            part = ((S_80020DF0_6 *)particle)->unk_0C;
                            func_8004491C(particle, D_80045340);
                            link = (u8 *)particle + 0x20;
                            ((S_80020DF0_7 *)part)->unk_0C = 0x00808080;
                            ((S_80020DF0_7 *)part)->unk_1E = scale;
                            ((S_80020DF0_7 *)part)->unk_1C = scale;
                            ((S_80020DF0_8 *)link)->unk_04 = arg1;
                            ((S_80020DF0_8 *)link)->unk_02 = 0x78;
                            ((S_80020DF0_6 *)particle)->unk_10 = particle_data;
                            func_8003DB94(part, D_800F3020, (s16)(i * 4));
                        }
                        i--;
                    } while (i >= 0);
                } else {
                    ((S_80020DF0_0 *)arg0)->unk_A8 &= -2;
                }
                effect = D_800F2F80;
                ((S_80020DF0_2 *)arg1)->unk_14 = 0;
                ((S_80020DF0_2 *)arg1)->unk_10 = 0;
                ((S_80020DF0_2 *)arg1)->unk_0C = 0;
                ((S_80020DF0_0 *)arg0)->unk_6C.s = 0x14;
                ((S_80020DF0_0 *)arg0)->unk_68.s = 0xB;
            }
        }
        goto cleanup;

    case 11:
        {
            u16 flags;
            s32 y;
            s32 x;

            flags = ((S_80020DF0_3 *)arg2)->unk_14;
            if ((flags & 0x6000) && ((S_80020DF0_0 *)arg0)->unk_6C.u > 0) {
                effect = D_800F2DC0;
                ((S_80020DF0_3 *)arg2)->unk_14 = flags | 0x800;
            }
            if (((S_80020DF0_2 *)arg1)->unk_00 > 0x03A00000) {
                ((S_80020DF0_3 *)arg2)->unk_14 &= 0xFFFE;
            } else {
                ((S_80020DF0_3 *)arg2)->unk_14 |= 1;
            }
            y = ((S_80020DF0_2 *)arg1)->unk_04;
            ((S_80020DF0_2 *)arg1)->unk_04 = y + ((0x01E00000 - y) >> 1);
            {
                s16 t68 = ((S_80020DF0_0 *)arg0)->unk_6C.s - 1;

                ((S_80020DF0_0 *)arg0)->unk_6C.u = t68;
                if (t68 == 0) {
                s32 x;

                ((S_80020DF0_3 *)arg2)->unk_14 &= 0xF7FF;
                x = ((S_80020DF0_2 *)arg1)->unk_00;
                if (x > 0x03A80000) {
                    ((S_80020DF0_2 *)arg1)->unk_0C = -0x80000;
                } else if (x <= 0x0397FFFF) {
                    ((S_80020DF0_2 *)arg1)->unk_0C = 0x80000;
                } else {
                    effect = D_800F2E50;
                    ((S_80020DF0_2 *)arg1)->unk_0C = 0;
                    ((S_80020DF0_2 *)arg1)->unk_00 = 0x03A00000;
                }
                }
            }
            if ((u32)(((S_80020DF0_2 *)arg1)->unk_00 - 0x03BC0000) <= 0xC80000) {
                ((S_80020DF0_2 *)arg1)->unk_08.at00.v = 0;
            } else {
                ((S_80020DF0_2 *)arg1)->unk_08.at00.v = 0x200000;
            }
            {
                register s32 ax ASM_REG("$2");   /* MATCH pin: retail register colouring depends on it */

                ax = ((S_80020DF0_2 *)arg1)->unk_00;
                ax = ax - 0x03A00000;
                if (ax < 0) {
                    ax = -ax;
                }
                ASM_KEEP(ax);   /* MATCH pin: retail basic-block layout depends on it */
                if (ax <= 0x80000 && ((S_80020DF0_0 *)arg0)->unk_6C.u < 0) {
                    ((S_80020DF0_1 *)actor)->unk_2A |= 2;
                    ((S_80020DF0_2 *)arg1)->unk_14 = 0;
                    ((S_80020DF0_2 *)arg1)->unk_10 = 0;
                    ((S_80020DF0_2 *)arg1)->unk_0C = 0;
                    ((S_80020DF0_0 *)arg0)->unk_68.s = 0;
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
            ((S_80020DF0_2 *)arg1)->unk_10 = 0x80000;
            ((S_80020DF0_0 *)arg0)->unk_6C.s = 0x1E;
            ((S_80020DF0_0 *)arg0)->unk_68.u++;
        }
        /* fall through */

    case 0x100:
    case 0x102:
        ((S_80020DF0_0 *)arg0)->unk_6C.s--;
        if ((s16)((S_80020DF0_0 *)arg0)->unk_6C.s <= 0) {
            ((S_80020DF0_2 *)arg1)->unk_10 = 0;
            ((S_80020DF0_2 *)arg1)->unk_14 = -0x100000;
            goto increment_state;
        }
        goto cleanup;

    case 0x101:
    case 0x103:
        {
            s32 height;

            height = ((S_80020DF0_2 *)arg1)->unk_08.at00.v;
            ((S_80020DF0_2 *)arg1)->unk_14 += 0x20000;
            if (height > 0x1FFFFF) {
                ((S_80020DF0_2 *)arg1)->unk_08.at00.v = 0x200000;
                ((S_80020DF0_2 *)arg1)->unk_14 = 0;
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
        ((S_80020DF0_0 *)arg0)->unk_68.s = state_u + 1;
        goto cleanup;

    case 0x107:
        ((S_80020DF0_2 *)arg1)->unk_10 = -0x80000;
        ((S_80020DF0_3 *)arg2)->unk_10 = 0x60;
        ((S_80020DF0_3 *)arg2)->unk_0C.s = 0x00C0C0C0;
        ((S_80020DF0_3 *)arg2)->unk_14 |= 0xC;
        effect = D_800F2EE0;
        ((S_80020DF0_0 *)arg0)->unk_68.u++;
        goto cleanup;

    case 0x108:
        ((S_80020DF0_3 *)arg2)->unk_0C.s += -0x80808;
        if ((u8)((S_80020DF0_3 *)arg2)->unk_0C.u < 0x11) {
            goto increment_state;
        }
        goto cleanup;

increment_state:
        ((S_80020DF0_0 *)arg0)->unk_68.u++;
        goto cleanup;

    case 0x109:
        func_8008F134(arg0);
        (*(u16 *)((u8 *)arg0 + -2)) |= 0x8000;
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
