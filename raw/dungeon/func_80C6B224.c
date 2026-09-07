#include "common.h"

typedef struct {
    u8 pad00[0x8C];
    void *field8C;
    s32 position90;
    u8 pad94[2];
    s16 countdown96;
    u16 flags98;
    u8 pad9A;
    u8 state9B;
    u8 pad9C[2];
    s16 timer9E;
    s32 velocityA0;
} State;

typedef struct {
    u8 pad00[2];
    s16 x2;
    u8 pad04[2];
    s16 y6;
    u8 pad08[4];
    s32 dxC;
    s32 dy10;
    s32 dz14;
} Motion;

typedef struct {
    u8 pad00[0x14];
    u16 flags14;
    u8 pad16[0xE];
    u8 x24;
    u8 y25;
    u8 pad26[6];
    u8 *table2C;
} Actor;

typedef struct {
    u8 pad00[0x1C];
    u32 flags1C;
    u8 pad20[0xA];
    s16 direction2A;
    u8 pad2C[0x1A];
    u16 field46;
} Entity;

extern u8 D_80082E80[];
extern s16 D_80083228;
extern s32 D_80083460;
extern u8 D_80171650[];
extern u8 D_801742E0[];
extern u8 D_801742E8[];

extern void func_80047784(Actor *, u8, s32);
extern s32 func_800644B8(s32);
extern s16 func_800A0818(u8, u8, u8, u8, s32 *);
extern void func_800A2B04(Motion *, u8, u8);
extern void func_800A4ACC(Entity *);
extern void func_800A9A04(Entity *);
extern void func_800AD594(Entity *, s32);
extern s32 func_800AD9B4(Actor *, Entity *);

void func_80172A24(State *arg0, Motion *arg1, Actor *arg2, Entity *arg3)
{
    s32 scratch[2];
    s32 index;
    register u8 *table ASM_REG("$5");
    u8 state;
    u32 flags;

    state = arg0->state9B;
    switch (state) {
    case 0:
        if ((arg2->flags14 & 0x6000) == 0) {
            goto end_state;
        }
        table = D_801742E0;
        *(u8 * volatile *)((u8 *)arg2 + 0x2C) = table;
        index = (D_80083228 + arg3->direction2A + 0x100) >> 9;
        func_80047784(arg2, table[index & 7], 0);
        arg0->flags98 |= 8;
        arg3->flags1C &= 0xF7FFFFFF;
        arg0->timer9E = 5;
        arg0->velocityA0 = 0;
        arg0->state9B++;
        /* fallthrough */
    case 1:
        arg0->position90 -= arg0->velocityA0;
        if (arg0->timer9E != 0) {
            s32 x_coordinate;
            s32 x_origin;
            s32 x_velocity;
            s32 y_origin;

            x_coordinate = arg2->x24 << 6;
            x_origin = arg1->x2 - 0x20;
            x_velocity = ((x_coordinate - x_origin) << 16) /
                         arg0->timer9E;
            y_origin = arg1->y6 - 0x20;
            arg1->dxC = x_velocity;
            arg1->dy10 = (((arg2->y25 << 6) - y_origin) << 16) /
                         arg0->timer9E;
            arg0->velocityA0 = -func_800644B8(arg0->timer9E * 0x199) << 10;
        }
        arg0->position90 += arg0->velocityA0;
        arg0->timer9E--;
        if (arg0->timer9E >= 0) {
            goto state_two;
        }
        arg0->flags98 &= 0xFFF7;
        arg0->position90 = 0;
        arg3->flags1C |= 0x08000000;
        arg0->state9B++;
        /* fallthrough */
    case 2:
state_two:
        if ((arg3->flags1C & 0x08000000) == 0) {
            goto end_state;
        }
        arg0->flags98 &= 0xFFF7;
        arg1->dz14 = 0;
        arg1->dy10 = 0;
        arg1->dxC = 0;
        func_800A2B04(arg1, arg2->x24, arg2->y25);
        table = D_801742E8;
        *(u8 * volatile *)((u8 *)arg2 + 0x2C) = table;
        index = (D_80083228 + arg3->direction2A + 0x100) >> 9;
        func_80047784(arg2, table[index & 7], 0);
        arg0->state9B++;
        break;
    default:
        break;
    }

end_state:
    arg0->countdown96--;
    if (arg0->countdown96 > 0) {
        return;
    }

    arg1->dz14 = 0;
    arg1->dy10 = 0;
    arg1->dxC = 0;
    func_800A2B04(arg1, arg2->x24, arg2->y25);
    func_800AD594(arg3, 4);
    func_800A4ACC(arg3);

    {
        s32 *global = &D_80083460;

        if (*(s16 *)((u8 *)global + 8) != 0) {
            *(u16 *)((u8 *)global + 8) -= 1;
        }
    }

    flags = arg3->flags1C;
    if ((flags & 0x2000) != 0) {
        if ((arg3->field46 & 0x8000) != 0) {
            arg3->field46 &= 0x7FFF;
        }
    } else if ((flags & 0x410) == 0) {
        if ((flags & 0x20000) != 0) {
            arg3->direction2A = func_800A0818(
                arg2->x24, arg2->y25, D_80082E80[0x24],
                D_80082E80[0x25], scratch);
        }
    }

    if ((func_800AD9B4(arg2, arg3) << 16) > 0) {
        arg0->field8C = D_80171650;
        func_800A9A04(arg3);
    }
}
