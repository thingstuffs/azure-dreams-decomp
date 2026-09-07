#include "common.h"

#ifndef NULL
#define NULL 0
#endif

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

typedef struct {
    s16 x;
    s16 y;
    s16 z;
    s16 pad;
} Cell;

extern void *func_8003FC64(s32);
extern void func_8004491C(void *, void *);
extern s32 func_80069EF8(void);

extern u8 D_800255E8[];
extern u8 D_800259DC[];
extern s16 D_80026476;
extern s32 D_800265C0;
extern s32 D_800265C4;
extern Cell D_800265C8[];
extern Cell D_80026648[];

#ifdef NON_MATCHING
#define SET_COUNT_PAGE() (count_page = (u8 *)&D_80026476)
#define READ_COUNT_PAGE() (*(s16 *)count_page)
#else
#define SET_COUNT_PAGE() (addr_or_coord = 0x80020000)
#define READ_COUNT_PAGE() FIELD((void *)addr_or_coord, s16, 0x6476)
#endif

/* Spawn quad effects at cell centers with randomized motion, then clear the pending count. */
void func_80025BA0(void) {
    Cell *vertices;
    register Cell *corner ASM_REG("$23");   /* MATCH pin: keeps a constant in a register as retail does */
    Cell *diagonal;
    Cell *below;
    Cell *right;
    void *effect;
    void *motion;
    void *angles;
    void *quad_data;
    s32 quad_index;
    s32 row_start;
    register s32 index_or_coord ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */
    s32 right_offset;
    s32 right_y;
    s32 below_y;
    s32 diagonal_y;
    register s32 effect_or_x ASM_REG("$4");   /* MATCH pin: retail schedule: same instructions, different order without it */
    s32 right_z;
    s32 below_z;
    s32 diagonal_z;
    register s32 addr_or_coord ASM_REG("$2");   /* MATCH pin: keeps a constant in a register as retail does */
    s32 rounded_index;
    s32 quad_count;
#ifdef NON_MATCHING
    u8 *count_page;
#endif

    quad_index = 0;
    if (D_80026476 > 0) {
        vertices = D_800265C8;
        corner = vertices;
        do {
            effect = func_8003FC64(0x202);
            SET_COUNT_PAGE();
            if (effect != NULL) {
                effect_or_x = (s32)effect;
                addr_or_coord = (s32)D_800255E8;
                FIELD(effect, void *, 0x10) = (void *)addr_or_coord;
                func_8004491C((void *)effect_or_x, D_800259DC);

                row_start = quad_index & ~0xF;
                ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
                index_or_coord = (quad_index + 1) & 0xF;
                right_offset = (row_start + index_or_coord) * 8;
                right = (Cell *)((unsigned long)right_offset + (unsigned long)vertices);
                below = (Cell *)((unsigned long)((quad_index + 0x10) * 8) + (unsigned long)vertices);
                ASM_KEEP(index_or_coord);   /* MATCH pin: keeps a statement from moving across a call/branch */
                index_or_coord += 0x10;
                diagonal = (Cell *)((unsigned long)((row_start + index_or_coord) * 8) + (unsigned long)vertices);

                effect_or_x = corner->x;
                addr_or_coord = right->x;
                index_or_coord = diagonal->x;
                motion = FIELD(effect, void *, 8);
                right_y = right->y;
                below_y = below->y;
                diagonal_y = diagonal->y;
                right_z = right->z;
                below_z = below->z;
                effect_or_x += addr_or_coord;
                addr_or_coord = below->x;
                diagonal_z = diagonal->z;
                effect_or_x += addr_or_coord;
                effect_or_x += index_or_coord;
                addr_or_coord = corner->y;
                index_or_coord = corner->z;
                effect_or_x >>= 2;
                FIELD(motion, s16, 2) = effect_or_x;
                addr_or_coord = (addr_or_coord + right_y + below_y + diagonal_y) >> 2;
                FIELD(motion, s16, 6) = addr_or_coord;
                index_or_coord = (index_or_coord + right_z + below_z + diagonal_z) >> 2;
                FIELD(motion, s16, 0xA) = index_or_coord;

                FIELD(motion, s32, 0xC) = ((func_80069EF8() & 0xF) - 8) << 0x10;
                FIELD(motion, s32, 0x10) = ((func_80069EF8() & 0xF) - 8) << 0x10;
                FIELD(motion, s32, 0x14) = ((func_80069EF8() & 0xF) - 8) << 0x10;

                angles = FIELD(effect, void *, 0xC);
                FIELD(angles, s16, 0x16) = (func_80069EF8() & 0x1FF) - 0x100;
                FIELD(angles, s16, 0x18) = (func_80069EF8() & 0x1FF) - 0x100;

                quad_data = (u8 *)effect + 0x20;
                FIELD(quad_data, s16, 0x1A) = 0x20;
                FIELD(quad_data, s32, 0x34) = *(s32 *)corner;
                FIELD(quad_data, u16, 0x38) = corner->z;
                FIELD(quad_data, s32, 0x3C) = *(s32 *)right;
                FIELD(quad_data, u16, 0x40) = right->z;
                FIELD(quad_data, s32, 0x44) = *(s32 *)&D_80026648[quad_index];
                FIELD(quad_data, u16, 0x48) = below->z;
                FIELD(quad_data, s32, 0x4C) = *(s32 *)((u8 *)D_80026648 + right_offset);
                FIELD(quad_data, u16, 0x50) = diagonal->z;

                rounded_index = quad_index;
                if (quad_index < 0) {
                    rounded_index = quad_index + 0x1F;
                }
                if ((quad_index - ((rounded_index >> 5) << 5)) < 0x10) {
                    FIELD(quad_data, s32, 0x54) = D_800265C0;
                    FIELD(quad_data, s32, 0x58) = D_800265C4;
                } else {
                    FIELD(quad_data, s32, 0x58) = D_800265C0;
                    FIELD(quad_data, s32, 0x54) = D_800265C4;
                }
                SET_COUNT_PAGE();
            }
            quad_count = READ_COUNT_PAGE();
            ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
            quad_index++;
            corner++;
        } while (quad_index < quad_count);
    }
    *(volatile s16 *)&D_80026476 = 0;
    ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
}
