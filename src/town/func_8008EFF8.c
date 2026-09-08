#include "common.h"

typedef struct { s32 x; s32 y; s32 z; } Vec3i;
typedef struct { s32 x; s32 y; s32 z; s32 pad; } Vec4i;
typedef struct { Vec3i work; s32 unused[3]; s32 item; } WorkArea;

extern s32 func_8008C3B8();
extern s32 func_8008CF48();

s16 func_8008C758(Vec3i *origin, Vec4i *items, s32 count, s32 *best_item,
                  u16 best_value, s32 initial_item)
{
    WorkArea local;
    s32 initial;
    Vec4i *cur;
    s32 bias;
    s32 i;
    s32 radius;
    s32 x;
    s32 xv;
    s32 yv;
    s32 zv;
    s32 neg_x;
    s32 neg_y;
    s32 product_x;
    s32 correction;
    s32 var_s4;
    s16 *itm;
    s32 i0;
    s32 i1;

    initial = initial_item;
    var_s4 = best_value;
    i = 0;
    *best_item = initial;
    if (count > 0) {
        bias = 0xFFFF;
        cur = items;
loop:
        if (func_8008C3B8(items, i, initial) >= 0) {
            local.work.x = origin->x + cur->x;
            local.work.y = origin->y + cur->y;
            xv = cur->x;
            yv = cur->y;
            radius = xv;
            if (xv < 0) {
                ASM_KEEP_NV(radius);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                radius = -radius;
            }
            if (yv < 0) yv = -yv;
            ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            if (radius < yv) radius = yv;
            local.work.z = origin->z - (radius * 2);
            func_8008CF48(&local.work, &local.item, radius);
            if (func_8008C3B8(items, i, local.item) < 0) {
                itm = (s16 *)local.item;
                xv = cur->x;
                neg_x = -xv;
                i0 = itm[0];
                if (neg_x < 0) neg_x += bias;
                product_x = i0 * (neg_x >> 16);
                i1 = itm[1];
                neg_y = -cur->y;
                if (neg_y < 0) neg_y += bias;
                {
                    s32 sum;
                    sum = product_x + i1 * (neg_y >> 16);
                    correction = sum / itm[2];
                }
            } else {
                correction = 0;
            }
            do {
                do {
                    do {
                            s32 wz;
                            wz = origin->z;
                            wz += cur->z;
                            wz += correction << 16;
                            local.work.z = wz;
                            x = func_8008CF48(&local.work, &local.item);
                    } while (0);
                } while (0);
            } while (0);
            if ((s16)x != 0x7FFF) {
                zv = cur->z;
                if (zv < 0) zv += bias;
                zv >>= 16;
                zv += correction;
                x -= zv;
            }
            if ((x << 16) < (var_s4 << 16)) {
                s32 sel;
                sel = local.item;
                var_s4 = x;
                *best_item = sel;
            }
        }
        i++;
        cur++;
        if (i < count) goto loop;
    }
    return (s16)var_s4;
}
