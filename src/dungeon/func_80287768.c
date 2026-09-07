#include "common.h"

extern s32 D_8001F660;
extern s32 D_8001F664;
extern s8 D_8001F66C[];
extern u8 D_8001F6A0;
extern s8 D_8001F6A4[];
extern s8 D_8001F6E8[];
extern u8 D_8006CCD8[];
extern u8 D_8006CCE8[];

extern s32 func_8001ABC8(s16 arg0, s16 arg1);
extern s32 func_800A6D30(void);

s16 func_8001A768(u16 *arg0, s32 arg1, s32 arg2, s8 *arg3, s32 arg4, s32 arg5,
                  s32 arg6) {
    u16 start_x;
    u16 start_y;
    u16 depth_arg;
    u16 aux_arg;
    register s32 auxv ASM_REG("$8");   /* MATCH pin: retail register colouring depends on it */
    s32 limit;
    s32 depth;
    s32 shifted;
    s32 off;
    register u16 nsum ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    s32 xbase;
    s32 x;
    s32 y;
    s32 failures;
    register s32 index ASM_REG("$16");   /* MATCH pin: keeps a constant in a register as retail does */
    s8 tile;
    s32 count;
    s32 tries;
    s32 parity;
    s32 remaining;
    s32 direction;
    s32 dir;
    s32 dir_off;
    s32 turn_off;
    u16 next_x;
    u16 next_y;
    s32 tx;
    s32 ty;
    s8 *mark;
    s8 *mbase;
    s8 *moff;

    shifted = (s32)*arg0 << 16;
    xbase = (s32)D_8006CCD8;
    off = shifted >> 15;
    start_x = arg1;
    start_y = arg2;
    depth_arg = arg5;
    failures = 0;
    x = arg1 + *(u16 *)(xbase + off) * arg5;
    y = arg2 + *(u16 *)(D_8006CCE8 + off) * arg5;
    auxv = arg6;
    aux_arg = auxv;

    if (((s16)x >= 0) && ((s16)x < D_8001F660) && ((s16)y >= 0) &&
        ((s16)y < D_8001F664) && (D_8001F6A4[shifted >> 17] == 0)) {
        nsum = x + (s16)y * D_8001F660;
        index = (s16)nsum;
        tile = arg3[index];
        if (tile > 0) {
            if (func_8001ABC8(index, (s16)auxv) == 0) {
                return index;
            }
            failures = 1;
        } else if (tile < 0) {
            failures = 1;
        }
    } else {
        failures++;
    }

    if (failures != 0) {
        D_8001F6A4[((s32)*arg0 << 16) >> 17] = 1;
        if ((s16)depth_arg < (s8)D_8001F6A0) {
            D_8001F6A0 = depth_arg;
        }
    }

    if ((s16)depth_arg > (s8)D_8001F6A0) {
        limit = (s8)D_8001F6A0;
    } else {
        limit = (s16)depth_arg;
    }

    count = 1;
    if (count < (s16)depth_arg) {
        depth = (s16)depth_arg;
        do {
            tries = 2;
            if (count >= limit) {
                failures++;
                goto outer_next;
            }
        remaining = depth - count;
        parity = func_800A6D30() & 1;
        tx = (s32)D_8006CCD8;
        ty = (s32)D_8006CCE8;
        do {
            dir = *(s16 *)arg0;
            dir_off = dir * 2;
            direction = (dir + D_8001F66C[parity]) & 6;
            turn_off = direction * 2;
            next_x = start_x + *(s16 *)(dir_off + tx) * count
                             + *(s16 *)(turn_off + tx) * remaining;
            next_y = start_y + *(s16 *)(dir_off + ty) * count
                             + *(s16 *)(turn_off + ty) * remaining;
            if (((s16)next_x >= 0) && ((s16)next_x < D_8001F660) &&
                ((s16)next_y >= 0) && ((s16)next_y < D_8001F664)) {
                mbase = D_8001F6E8;
                moff = mbase + parity * 4;
                mark = moff + count;
                if (*mark == 0) {
                    nsum = next_x + (s16)next_y * D_8001F660;
                    index = (s16)nsum;
                    mbase = arg3;
                    tile = mbase[index];
                    if (tile == 0) {
                        goto next;
                    }
                    if (tile > 0) {
                        if (func_8001ABC8(index, (s16)aux_arg) == 0) {
                            goto found;
                        }
                    }
                    *mark = 1;
                }
            }
            failures++;
        next:
            parity ^= 1;
        } while (--tries > 0);
outer_next:
            count++;
        } while (count < depth);
    }

    if (failures < 3) {
        goto recurse;
    }
    return -1;
found:
    *arg0 = direction;
    return index;
recurse:
    return func_8001A768(arg0, (s16)start_x, (s16)start_y, arg3, arg4,
                         (s16)(depth_arg + 1), (s16)aux_arg);
}
