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
extern s32 rand(void);

extern u8 D_80025A58[];
extern u8 D_80025E4C[];
extern s16 D_8002632A;
extern s32 D_80026470;
extern s32 D_80026474;
extern Cell D_80026478[];
extern Cell D_800264F8[];

#ifdef NON_MATCHING
#define SET_COUNT_PAGE() (count_page = (u8 *)&D_8002632A)
#define READ_COUNT_PAGE() (*(s16 *)count_page)
#else
#define SET_COUNT_PAGE() (temp_v0 = 0x80020000)
#define READ_COUNT_PAGE() FIELD((void *)temp_v0, s16, 0x632A)
#endif

void func_80026010(void) {
    Cell *base;
    register Cell *current ASM_REG("$23");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    Cell *p1;
    Cell *p2;
    Cell *p4;
    void *obj;
    void *motion;
    void *angles;
    void *dst;
    s32 i;
    s32 block;
    register s32 next ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 byte_offset;
    s32 y1;
    s32 y2;
    s32 y3;
    register s32 value ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    s32 z1;
    s32 z2;
    s32 z3;
    register s32 temp_v0 ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    s32 rounded;
    s32 limit;
#ifdef NON_MATCHING
    u8 *count_page;
#endif

    i = 0;
    if (D_8002632A > 0) {
        base = D_80026478;
        current = base;
        do {
            obj = func_8003FC64(0x202);
            SET_COUNT_PAGE();
            if (obj != NULL) {
                value = (s32)obj;
                temp_v0 = (s32)D_80025A58;
                FIELD(obj, void *, 0x10) = (void *)temp_v0;
                func_8004491C((void *)value, D_80025E4C);

                block = i & ~0xF;
                ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                next = (i + 1) & 0xF;
                byte_offset = (block + next) * 8;
                p4 = (Cell *)((unsigned long)byte_offset + (unsigned long)base);
                p2 = (Cell *)((unsigned long)((i + 0x10) * 8) + (unsigned long)base);
                ASM_KEEP(next);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
                next += 0x10;
                p1 = (Cell *)((unsigned long)((block + next) * 8) + (unsigned long)base);

                value = current->x;
                temp_v0 = p4->x;
                next = p1->x;
                motion = FIELD(obj, void *, 8);
                y1 = p4->y;
                y2 = p2->y;
                y3 = p1->y;
                z1 = p4->z;
                z2 = p2->z;
                value += temp_v0;
                temp_v0 = p2->x;
                z3 = p1->z;
                value += temp_v0;
                value += next;
                temp_v0 = current->y;
                next = current->z;
                value >>= 2;
                FIELD(motion, s16, 2) = value;
                temp_v0 = (temp_v0 + y1 + y2 + y3) >> 2;
                FIELD(motion, s16, 6) = temp_v0;
                next = (next + z1 + z2 + z3) >> 2;
                FIELD(motion, s16, 0xA) = next;

                FIELD(motion, s32, 0xC) = ((rand() & 0xF) - 8) << 0x10;
                FIELD(motion, s32, 0x10) = ((rand() & 0xF) - 8) << 0x10;
                FIELD(motion, s32, 0x14) = ((rand() & 0xF) - 8) << 0x10;

                angles = FIELD(obj, void *, 0xC);
                FIELD(angles, s16, 0x16) = (rand() & 0x1FF) - 0x100;
                FIELD(angles, s16, 0x18) = (rand() & 0x1FF) - 0x100;

                dst = (u8 *)obj + 0x20;
                FIELD(dst, s16, 0x1A) = 0x20;
                FIELD(dst, s32, 0x30) = *(s32 *)current;
                FIELD(dst, u16, 0x34) = current->z;
                FIELD(dst, s32, 0x38) = *(s32 *)p4;
                FIELD(dst, u16, 0x3C) = p4->z;
                FIELD(dst, s32, 0x40) = *(s32 *)&D_800264F8[i];
                FIELD(dst, u16, 0x44) = p2->z;
                FIELD(dst, s32, 0x48) = *(s32 *)((u8 *)D_800264F8 + byte_offset);
                FIELD(dst, u16, 0x4C) = p1->z;

                rounded = i;
                if (i < 0) {
                    rounded = i + 0x1F;
                }
                if ((i - ((rounded >> 5) << 5)) < 0x10) {
                    FIELD(dst, s32, 0x50) = D_80026470;
                    FIELD(dst, s32, 0x54) = D_80026474;
                } else {
                    FIELD(dst, s32, 0x54) = D_80026470;
                    FIELD(dst, s32, 0x50) = D_80026474;
                }
                ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                SET_COUNT_PAGE();
            }
            limit = READ_COUNT_PAGE();
            ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            i++;
            current++;
        } while (i < limit);
    }
    *(volatile s16 *)&D_8002632A = 0;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
}
