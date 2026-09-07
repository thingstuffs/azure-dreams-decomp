#include "common.h"

typedef struct {
    s16 x;
    s16 unk2;
    s16 y;
    s16 unk6;
} LocalPoint;

extern u8 D_8002004C[];
extern void *D_80020058[];
extern u8 D_800245DC[];
extern u8 D_80083780[];

extern s32 func_80064710(s32);
extern void func_800672D8(LocalPoint *, void *);
extern void func_80053DA8(s32);

#define S32(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define S16(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define U16(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define U8(p, o)  (*(u8 *)((u8 *)(p) + (o)))

void func_80020C10(void *arg0, void *arg1, void *arg2)
{
    s32 *world = (s32 *)D_80083780;
    s32 *close_page;
    s32 dx = (world[0] + (s32)0xFCA00000) >> 16;
    s32 dy = (world[1] + (s32)0xFCA00000) >> 16;
    register void *state ASM_REG("$18");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    void *other;
    register void *effect ASM_REG("$21");   /* MATCH pin: retail register colouring depends on it */
    register void *sub ASM_REG("$20");   /* MATCH pin: retail register colouring depends on it */
    s32 old_angle;
    LocalPoint point;
    s32 distance;
    s32 x2;
    s32 y2;
    s32 adx;
    s32 ady;
    s32 limit;
    register s32 step ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */
    s32 threshold;
    s32 reduced;
    s32 loop_x;
    s32 loop_mod;
    register s32 value ASM_REG("$2");   /* MATCH pin: keeps a constant in a register as retail does */
    u32 swi;
    static void *const sw_keep[] = {
        &&case0, &&case1, &&case2, &&case3,
        &&case4, &&case5, &&case6, &&case7,
    };

    state = arg0;
    other = arg1;
    ASM_KEEP_NV(other);   /* MATCH pin: load-bearing for the whole function shape */
    effect = arg2;
    sub = *(void **)state;
    old_angle = U16(effect, 0x1A);
    point = *(LocalPoint *)D_8002004C;
    x2 = dx * dx;
    y2 = dy * dy;
    distance = func_80064710(x2 + y2);
    S32(state, 0x60) = S32(other, 8);

    if (world[1] > 0x035FFFFF) {
        if (distance < 185) {
            goto close_range;
        }
    } else if (distance < 193) {
        goto close_range;
    }
    goto middle_range;

close_range:
    close_page = (s32 *)D_80083780;
    if (S16(close_page, 0xA) >= S16(other, 0xA)) {
        close_page[0] = S32(state, 4);
        close_page[1] = S32(state, 8);
    }
    S32(state, 0x58) = close_page[0];
    S32(state, 0x5C) = close_page[1];
    if (distance < 128) {
        value = (128 - distance) >> 1;
        U16(state, 0x62) = U16(state, 0x62) - value;
    }
    goto position_done;

middle_range:
    if (distance < 209) {
        s32 *mid_page;
        mid_page = (s32 *)D_80083780;
        if (S16(mid_page, 0xA) >= S16(other, 0xA)) {
            mid_page[0] = S32(state, 4);
            mid_page[1] = S32(state, 8);
        }

        adx = dx;
        if (adx < 0) {
            ASM_KEEP(adx);   /* MATCH pin: retail register colouring depends on it */
            adx = -adx;
        }
        ady = dy;
        if (ady < 0) {
            ASM_KEEP(ady);   /* MATCH pin: retail register colouring depends on it */
            ady = -ady;
        }
        if (adx > ady) {
            goto x_axis;
        }
        if (mid_page[1] > 0x033FFFFF) {
            goto y_axis;
        }
x_axis:
    S32(state, 0x5C) = mid_page[1];
    if (dx > 0) {
        S32(state, 0x58) = mid_page[0] - 0x00280000;
    } else {
        S32(state, 0x58) = mid_page[0] + 0x00280000;
    }
    goto position_done;

y_axis:
    S32(state, 0x58) = mid_page[0];
    if (dy > 0) {
        S32(state, 0x5C) = mid_page[1] - 0x00280000;
    } else {
        S32(state, 0x5C) = mid_page[1] + 0x00280000;
    }
    } else {
        S32(state, 0x58) = 0x03600000;
        S32(state, 0x5C) = 0x03600000;
        goto position_done;
    }

position_done:
    S32(state, 4) = S32(D_80083780, 0);
    S32(state, 8) = S32(D_80083780, 4);

    {
        s32 quot = S32(sub, 0x14) / ((S16(sub, 0x22) << 8) + 0x300);
        s32 term = quot + 0x40;
        limit = ((3 - S16(sub, 0x22)) << 5) + term;
    }

    swi = S16(state, 0x70);
    if (swi >= 8) {
        goto switch_done;
    }
    (void)sw_keep;
    goto *D_80020058[swi];

case0:
    value = U8(effect, 0xE);
    value += (128 - value) >> 1;
    U8(effect, 0xE) = value;
    U8(effect, 0xD) = value;
    U8(effect, 0xC) = value;
    S32(state, 0x6C) = 0x00080000;
    goto switch_done;

case1:
    step = (S16(state, 0x72) + 16) >> 4;
    value = U16(state, 0x72) + step;
    U16(state, 0x72) = value;
    if ((s16)value > limit) {
        U16(state, 0x72) = limit;
        S16(state, 0x70) = 2;
    }
    U16(effect, 0x1A) += U16(state, 0x72);
    goto switch_done;

case2:
    U16(effect, 0x1A) += limit;
    if (distance >= 161 && S32(D_80083780, 4) > 0x03600000 && S16(sub, 0x18) == 5) {
        S16(state, 0x72) = limit;
        S16(state, 0x70) = 3;
    }
    goto switch_done;

case3:
    dx = U16(effect, 0x1A) & 0x7FF;
    if (dx >= 0x6AB) {
        S16(sub, 0x24) = 0;
        goto reset_sub;
    }
    dy = 0x155;
    distance = 4;
    threshold = 0x554;
    for (; distance >= 0; distance--, threshold -= dy) {
        if (dx >= threshold) {
            break;
        }
    }
    value = distance & 1;
    if (value) {
        S16(sub, 0x24) = 1;
    } else {
        S16(sub, 0x24) = 2;
    }
reset_sub:
    S16(sub, 0x1A) = 0;

case4:
    if (S16(sub, 0x22) == 2) {
        dx = 6;
    } else {
        dx = 5;
    }
    value = S16(state, 0x72) >> dx;
    reduced = U16(state, 0x72) - value;
    U16(state, 0x72) = reduced;
    U16(effect, 0x1A) += U16(state, 0x72);
    U16(sub, 0x1A) += U16(state, 0x72);
    if (S16(state, 0x72) < (1 << dx)) {
        S16(state, 0x74) = 0;
        S16(state, 0x70) = 5;
    }
    goto switch_done;

case5:
    U16(effect, 0x1A) += U16(state, 0x72);
    U16(sub, 0x1A) += U16(state, 0x72);
    value = U16(state, 0x74) + 1;
    U16(state, 0x74) = value;
    if ((value & 3) == 0) {
        U16(state, 0x72) -= 2;
    }
    if (S16(state, 0x72) < 4) {
        S16(state, 0x70) = 0;
    }
    goto switch_done;

case6:
    S16(state, 0x70) = 7;
    S16(state, 0x72) = 0;

case7:
    dx = 0;
    sub = (void *)6;
    dy = (s32)D_800245DC;
    loop_x = 122;
case7_loop:
    {
        point.x = loop_x;
        point.y = (s32)sub;
        loop_mod = (S16(state, 0x72) >> 1) + dx;
        func_800672D8(&point, (void *)((loop_mod % 3) * 32 + dy));
        loop_x += 16;
        dx++;
    }
    if (dx < 3) {
        goto case7_loop;
    }
    value = U16(state, 0x72);
    U16(state, 0x72) = value + 1;
    if ((s16)value >= 198) {
        S16(state, 0x70) = 0;
    }

switch_done:
    value = U16(effect, 0x1A) & 0xFFF;
    U16(effect, 0x1A) = value;
    if ((old_angle >> 8) != ((u32)value >> 8)) {
        func_80053DA8(0x701);
    }
}
