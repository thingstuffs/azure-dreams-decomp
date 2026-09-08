#include "common.h"

#define U8(o, p)  (*(u8 *)((u8 *)(p) + (o)))
#define S8(o, p)  (*(s8 *)((u8 *)(p) + (o)))
#define U16(o, p) (*(u16 *)((u8 *)(p) + (o)))
#define S32(o, p) (*(s32 *)((u8 *)(p) + (o)))

extern s16 func_80042900(void *, s32);

/* Apply entity effects to scale, stats, and status flags. */
void func_80041E70(void *entity)
{
    s32 effect_flags;
    s32 boosted_stat;

    {
        s32 scale;
        s32 scale_flags;

        U16(0x6E, entity) = 0x100;
        scale_flags = S32(0x54, entity);
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the compiled object of the TU; the source shape that makes it unnecessary has not been found */
        scale = 0x10;
        U8(0x87, entity) = scale;
        if (scale_flags & 1) {
            s32 base_scale;

            base_scale = U16(0x6E, entity);
            ASM_KEEP_NV(scale);   /* UNRESOLVED C shape (pin): removing it changes the compiled object of the TU; the source shape that makes it unnecessary has not been found */
            scale *= 2;
            U8(0x87, entity) = scale;
            U16(0x6E, entity) = base_scale * 2;
        }
    }

    {
        register s32 scale_adjustment ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the compiled object of the TU; the source shape that makes it unnecessary has not been found */

        scale_adjustment = func_80042900(entity, 7);
        scale_adjustment = (s16)scale_adjustment;
        if (scale_adjustment > 0) {
            U16(0x6E, entity) = U16(0x6E, entity) * 2;
            U8(0x87, entity) = U8(0x87, entity) * 2;
        } else if (scale_adjustment < 0) {
            U16(0x6E, entity) = (s32)(U16(0x6E, entity) << 16) >> 17;
            U8(0x87, entity) = U8(0x87, entity) >> 1;
        }
    }

    if (S32(0x54, entity) & 2) {
        boosted_stat = U8(5, entity) * 2;
        if (boosted_stat >= 0x100) {
            boosted_stat = 0xFF;
        }
        U8(0x29, entity) = boosted_stat;
    } else {
        U8(0x29, entity) = U8(5, entity);
    }

    if (S32(0x54, entity) & 4) {
        boosted_stat = U8(4, entity) * 2;
        if (boosted_stat >= 0x100) {
            boosted_stat = 0xFF;
        }
        U8(0x66, entity) = boosted_stat;
    } else {
        U8(0x66, entity) = U8(4, entity);
    }

    if (S32(0x54, entity) & 8) {
        boosted_stat = U8(0, entity) * 2;
        if (boosted_stat >= 0x100) {
            boosted_stat = 0xFF;
        }
        U8(0x68, entity) = boosted_stat;
    } else {
        U8(0x68, entity) = U8(0, entity);
    }

    if (S32(0x54, entity) & 0x10) {
        boosted_stat = U8(1, entity) * 2;
        if (boosted_stat >= 0x100) {
            boosted_stat = 0xFF;
        }
        U8(0x69, entity) = boosted_stat;
    } else {
        U8(0x69, entity) = U8(1, entity);
    }

    {
        s32 slot_index = 2;
        register u8 *slot ASM_REG("$4") = (u8 *)entity + 6;   /* UNRESOLVED C shape (pin): removing it changes the compiled object of the TU; the source shape that makes it unnecessary has not been found */

        do {
            if (slot[8] != 0) {
                if (S32(0x54, entity) & 0x80) {
                    boosted_stat = slot[0xA] * 2;
                    if (boosted_stat >= 0x64) {
                        boosted_stat = 0x63;
                    }
                    slot[9] = boosted_stat;
                } else {
                    slot[9] = slot[0xA];
                }
            }
            slot_index--;
            slot -= 3;
        } while (slot_index >= 0);
    }

    if (S32(0x54, entity) & 0x04000000) {
        S32(0x14, entity) |= 0x400;
        S32(0x1C, entity) &= ~0x400;
    }

    if (S32(0x54, entity) & 0x02000000) {
        S32(0x14, entity) |= 0x200;
        S32(0x1C, entity) &= ~0x200;
    } else {
        S32(0x14, entity) &= ~0x200;
    }

    if (S32(0x54, entity) & 0x08000000) {
        S32(0x14, entity) |= 0x10;
        S32(0x1C, entity) &= ~0x10;
    } else {
        S32(0x14, entity) &= ~0x10;
    }

    if (S32(0x54, entity) & 0x10000000) {
        S32(0x14, entity) |= 0x20;
        S32(0x1C, entity) &= ~0x20;
    } else {
        S32(0x14, entity) &= ~0x20;
    }

    if (S32(0x54, entity) & 0x20000000) {
        S32(0x14, entity) |= 0x40;
        S32(0x1C, entity) &= ~0x40;
    } else {
        S32(0x14, entity) &= ~0x40;
    }

    if (S32(0x54, entity) & 0x40000000) {
        S32(0x14, entity) |= 0x80;
        S32(0x1C, entity) &= ~0x80;
    } else {
        S32(0x14, entity) &= ~0x80;
    }

    if (S32(0x54, entity) & 0x200000) {
        S32(0x1C, entity) |= 0x1000;
        S32(0x14, entity) &= ~0x1000;
    }

    effect_flags = S32(0x54, entity);
    if ((effect_flags & 0x800000) && ((u32)(U8(0x13, entity) - 3) < 0x2B) && (U8(0x48, entity) != 4)) {
        S32(0x54, entity) = effect_flags & 0xFF7FFFFF;
    }
}
