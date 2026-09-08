#include "common.h"

typedef struct { s32 x; s32 y; s32 z; } Vec3i;
typedef struct { s32 x; s32 y; s32 z; s32 pad; } Vec4i;
typedef struct { Vec3i work; s32 unused[3]; s32 item; } WorkArea;

extern s32 func_8008C3B8();
extern s32 func_8008CF48();

/* Selects the item with the smallest corrected probe value across the offsets. */
s16 func_8008C758(Vec3i *origin, Vec4i *items, s32 count, s32 *best_item,
                  u16 best_value, s32 initial_item)
{
    WorkArea probe;
    s32 seed_item;
    Vec4i *offset;
    s32 trunc_bias;
    s32 item_index;
    s32 radius;
    s32 value;
    s32 offset_x;
    s32 offset_y;
    s32 adjusted_z;
    s32 neg_x;
    s32 neg_y;
    s32 product_x;
    s32 correction;
    s32 min_value;
    s16 *coeffs;
    s32 coeff_x;
    s32 coeff_y;

    seed_item = initial_item;
    min_value = best_value;
    item_index = 0;
    *best_item = seed_item;
    if (count > 0) {
        trunc_bias = 0xFFFF;
        offset = items;
loop:
        if (func_8008C3B8(items, item_index, seed_item) >= 0) {
            probe.work.x = origin->x + offset->x;
            probe.work.y = origin->y + offset->y;
            offset_x = offset->x;
            offset_y = offset->y;
            radius = offset_x;
            if (offset_x < 0) {
                ASM_KEEP_NV(radius);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                radius = -radius;
            }
            if (offset_y < 0) offset_y = -offset_y;
            ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            if (radius < offset_y) radius = offset_y;
            probe.work.z = origin->z - (radius * 2);
            func_8008CF48(&probe.work, &probe.item, radius);
            if (func_8008C3B8(items, item_index, probe.item) < 0) {
                coeffs = (s16 *)probe.item;
                offset_x = offset->x;
                neg_x = -offset_x;
                coeff_x = coeffs[0];
                if (neg_x < 0) neg_x += trunc_bias;
                product_x = coeff_x * (neg_x >> 16);
                coeff_y = coeffs[1];
                neg_y = -offset->y;
                if (neg_y < 0) neg_y += trunc_bias;
                {
                    s32 dot_xy;
                    dot_xy = product_x + coeff_y * (neg_y >> 16);
                    correction = dot_xy / coeffs[2];
                }
            } else {
                correction = 0;
            }
            do {
                do {
                    do {
                        s32 probe_z;
                        probe_z = origin->z;
                        probe_z += offset->z;
                        probe_z += correction << 16;
                        probe.work.z = probe_z;
                        value = func_8008CF48(&probe.work, &probe.item);
                    } while (0);
                } while (0);
            } while (0);
            if ((s16)value != 0x7FFF) {
                adjusted_z = offset->z;
                if (adjusted_z < 0) adjusted_z += trunc_bias;
                adjusted_z >>= 16;
                adjusted_z += correction;
                value -= adjusted_z;
            }
            if ((value << 16) < (min_value << 16)) {
                s32 selected_item;
                selected_item = probe.item;
                min_value = value;
                *best_item = selected_item;
            }
        }
        item_index++;
        offset++;
        if (item_index < count) goto loop;
    }
    return (s16)min_value;
}
