#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_func_81888810_0 {
    u8 pad_00[0x8];
    void *unk_08;
    void *unk_0C;
    void *unk_10;
} S_func_81888810_0;

typedef struct S_func_81888810_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_func_81888810_1;

typedef struct S_func_81888810_2 {
    u8 pad_00[0x16];
    s16 unk_16;
    s16 unk_18;
} S_func_81888810_2;

typedef struct S_func_81888810_3 {
    u8 pad_00[0x1A];
    s16 unk_1A;
    u8 pad_1C[0x14];
    s32 unk_30;
    u16 unk_34;
    u8 pad_36[0x2];
    s32 unk_38;
    u16 unk_3C;
    u8 pad_3E[0x2];
    s32 unk_40;
    u16 unk_44;
    u8 pad_46[0x2];
    s32 unk_48;
    u16 unk_4C;
    u8 pad_4E[0x2];
    s32 unk_50;
    s32 unk_54;
} S_func_81888810_3;

typedef struct S_func_81888810_4 {
    u8 pad_00[0x632A];
    s16 unk_632A;
} S_func_81888810_4;

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
#define READ_COUNT_PAGE() (((S_func_81888810_4 *)temp_v0)->unk_632A)
#endif

void func_80026010(void) {
    Cell *base;
    register Cell *current ASM_REG("$23");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    Cell *p1;
    Cell *p2;
    Cell *p4;
    S_func_81888810_0 *obj;
    S_func_81888810_1 *motion;
    S_func_81888810_2 *angles;
    S_func_81888810_3 *dst;
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
                obj->unk_10 = (void *)temp_v0;
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
                motion = obj->unk_08;
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
                motion->unk_02 = value;
                temp_v0 = (temp_v0 + y1 + y2 + y3) >> 2;
                motion->unk_06 = temp_v0;
                next = (next + z1 + z2 + z3) >> 2;
                motion->unk_0A = next;

                motion->unk_0C = ((rand() & 0xF) - 8) << 0x10;
                motion->unk_10 = ((rand() & 0xF) - 8) << 0x10;
                motion->unk_14 = ((rand() & 0xF) - 8) << 0x10;

                angles = obj->unk_0C;
                angles->unk_16 = (rand() & 0x1FF) - 0x100;
                angles->unk_18 = (rand() & 0x1FF) - 0x100;

                dst = (S_func_81888810_3 *)((u8 *)obj + 0x20);
                dst->unk_1A = 0x20;
                dst->unk_30 = *(s32 *)current;
                dst->unk_34 = current->z;
                dst->unk_38 = *(s32 *)p4;
                dst->unk_3C = p4->z;
                dst->unk_40 = *(s32 *)&D_800264F8[i];
                dst->unk_44 = p2->z;
                dst->unk_48 = *(s32 *)((u8 *)D_800264F8 + byte_offset);
                dst->unk_4C = p1->z;

                rounded = i;
                if (i < 0) {
                    rounded = i + 0x1F;
                }
                if ((i - ((rounded >> 5) << 5)) < 0x10) {
                    *(s32 *)((u8 *)dst + 0x50) = D_80026470;
                    dst->unk_54 = D_80026474;
                } else {
                    *(s32 *)((u8 *)dst + 0x54) = D_80026470;
                    dst->unk_50 = D_80026474;
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
