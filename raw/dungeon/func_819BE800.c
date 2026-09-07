#include "common.h"

extern u8 D_8008333C[32];
extern s32 func_800BCE7C(void *);

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

#ifdef __mips__
static const u32 bank_words[] __asm__("func_80024000")
    __attribute__((section(".text.func_80024000"), aligned(4))) = {
    0x80026418, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0001, 0x0000FFFF,
    0x00000000, 0x00000001, 0x0001FFFF, 0x00010000, 0x00010001,
    0x00000001, 0x00010001, 0x00010000, 0x0001FFFF, 0x0000FFFF,
    0xFFFFFFFF, 0xFFFF0000, 0xFFFF0001, 0x800264FC, 0x8002659C,
    0x800265D0, 0x800267B8, 0x800267C8, 0x80026820, 0x800268B4,
};
__asm__(".size func_80024000, 920");
#define FUNC_80024000_BODY func_80024000_body
#else
#define FUNC_80024000_BODY func_80024000
#endif

void *FUNC_80024000_BODY(s32 arg0, s32 arg1, s16 arg2) {
    u8 *scratch;
    u8 *current;
    u8 *vertices;
    u8 *planes;
    u8 *best;
    u8 *map_entry;
    u8 *copy_vertex;
    u8 *dot_vertex;
    u8 *pshift;
    u8 *plane_ptr;
    s16 cell;
    s32 value;
    u16 x;
    u16 y;

    scratch = (u8 *)0x1F800000;
    FIELD(scratch, s32, 0x148) = 0x400;
    FIELD(scratch, s16, 0x140) = arg0 & 0x3F;
    FIELD(scratch, s16, 0x142) = arg1 & 0x3F;
    FIELD(scratch, s32, 0x14C) = arg2;

    cell = (u16)arg0 >> 6;
    FIELD(scratch, s16, 0x150) = cell;
    pshift = D_8008333C;
    cell += ((u16)arg1 >> 6) << FIELD(pshift, s16, 0x14);
    FIELD(scratch, s16, 0x150) = cell;
    map_entry = (u8 *)((long)cell * 6 +
                       (unsigned long)*(u8 **)D_8008333C);
    vertices = FIELD(pshift, u8 *, 8);
    planes = FIELD(pshift, u8 *, 0xC);
    best = 0;
    if (FIELD(map_entry, u16, 0) != 0) {
        FIELD(scratch, s16, 0x152) = -FIELD(map_entry, u16, 2);
        best = FIELD(FIELD(pshift, u8 **, 4), u8 *,
                     FIELD(map_entry, u16, 0) * 4);
        current = best;
        if (FIELD(planes + FIELD(best, u16, 0x10) * 8, s16, 4) < -0x7FF) {
            do {
                if ((FIELD(current, u8, 0x17) & 1) == 0) {
                    x = FIELD(scratch, u16, 0x140);
                    y = FIELD(scratch, u16, 0x142);

                    copy_vertex =
                        (u8 *)((unsigned long)FIELD(current, u16, 0) * 8 +
                               (unsigned long)vertices);
                    FIELD(scratch, u32, 0x154) =
                        FIELD(copy_vertex, u32, 0);
                    FIELD(scratch, s16, 0x154) =
                        FIELD(scratch, u16, 0x154) - x;
                    FIELD(scratch, s16, 0x156) =
                        FIELD(scratch, u16, 0x156) - y;

                    copy_vertex =
                        (u8 *)((unsigned long)FIELD(current, u16, 2) * 8 +
                               (unsigned long)vertices);
                    FIELD(scratch, u32, 0x158) =
                        FIELD(copy_vertex, u32, 0);
                    FIELD(scratch, s16, 0x158) =
                        FIELD(scratch, u16, 0x158) - x;
                    FIELD(scratch, s16, 0x15A) =
                        FIELD(scratch, u16, 0x15A) - y;

                    copy_vertex =
                        (u8 *)((unsigned long)FIELD(current, u16, 6) * 8 +
                               (unsigned long)vertices);
                    FIELD(scratch, u32, 0x15C) =
                        FIELD(copy_vertex, u32, 0);
                    FIELD(scratch, s16, 0x15C) =
                        FIELD(scratch, u16, 0x15C) - x;
                    FIELD(scratch, s16, 0x15E) =
                        FIELD(scratch, u16, 0x15E) - y;

                    copy_vertex =
                        (u8 *)((unsigned long)FIELD(current, u16, 4) * 8 +
                               (unsigned long)vertices);
                    FIELD(scratch, u32, 0x160) =
                        FIELD(copy_vertex, u32, 0);
                    FIELD(scratch, s16, 0x160) =
                        FIELD(scratch, u16, 0x160) - x;
                    FIELD(scratch, s16, 0x162) =
                        FIELD(scratch, u16, 0x162) - y;

                    if (func_800BCE7C(scratch) != 0) {
                        plane_ptr =
                            (u8 *)((unsigned long)FIELD(current, u16, 0x10) *
                                       8 +
                                   (unsigned long)planes);
                        dot_vertex =
                            (u8 *)((unsigned long)FIELD(current, u16, 0) * 8 +
                                   (unsigned long)vertices);
                        value =
                            (FIELD(plane_ptr, s16, 0) *
                                 (FIELD(dot_vertex, s16, 0) -
                                  (s16)FIELD(scratch, u16, 0x140)) +
                             FIELD(plane_ptr, s16, 2) *
                                 (FIELD(dot_vertex, s16, 2) -
                                  (s16)FIELD(scratch, u16, 0x142)) +
                             FIELD(plane_ptr, s16, 4) *
                                 FIELD(dot_vertex, s16, 4)) /
                            FIELD(plane_ptr, s16, 4);
                        FIELD(scratch, s32, 0x144) = value;
                        value += (s16)FIELD(scratch, u16, 0x152);
                        FIELD(scratch, s32, 0x144) = value;
                        if (value >= FIELD(scratch, s32, 0x14C) &&
                            value < FIELD(scratch, s32, 0x148)) {
                            best = current;
                            FIELD(scratch, s32, 0x148) = value;
                        }
                    }
                }

                if ((FIELD(current, u8, 0x16) & 0xF) == 1) {
                    if (FIELD(current, s8, 0x17) < 0) {
                        break;
                    }
                    if ((FIELD(current, u8, 0x16) & 0xF0) != 0) {
                        current +=
                            ((FIELD(current, u8, 0x16) >> 4) * 3) * 8 + 0x18;
                        continue;
                    }
                }
                current += 0x18;
            } while (FIELD(planes + FIELD(current, u16, 0x10) * 8, s16, 4) <
                     -0x7FF);
        }
    }

    return best;
}
