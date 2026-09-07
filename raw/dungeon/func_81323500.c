#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

typedef struct {
    u32 word0;
    u32 word4;
    u32 word8;
} __attribute__((packed)) Copy12;

extern void *func_8003FC64(u32);
extern void func_8004491C(void *, void *);

extern u8 D_80044BB0[];
extern Copy12 D_80077818;
extern u8 D_8016ABC8[];

void func_8016AD00(void)
{
    void *obj;
    void *part1;
    void *part2;

    obj = func_8003FC64(0x12);
    if (obj != 0) {
        FIELD(obj, void *, 0x10) = D_8016ABC8;
        func_8004491C(obj, D_80044BB0);

        do { part1 = FIELD(obj, void *, 8); } while (0);
        FIELD(part1, s16, 0xA) = 0;
        FIELD(part1, s16, 6) = 0;
        FIELD(part1, s16, 2) = 0;

        part2 = FIELD(obj, void *, 0xC);
        FIELD(part2, s16, 0x1E) = 0;
        FIELD(part2, s16, 0x1C) = 0;
        FIELD(part2, s8, 0xE) = 0;
        FIELD(part2, s8, 0xD) = 0;
        FIELD(part2, s8, 0xC) = 0;

        FIELD(obj, Copy12, 0x4C) = D_80077818;
        FIELD(part2, void *, 8) = (u8 *)obj + 0x4C;
    }
}
