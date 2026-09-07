#include "common.h"


typedef struct {
    u32 word0;
    u32 word4;
    u32 word8;
} __attribute__((packed)) Copy12;

extern void *func_8003FC64(u32);
extern void func_8004491C(void *, void *);

extern u8 D_80044BB0[];
extern Copy12 D_80173B1C;
extern u8 D_801701CC[];


typedef struct S_80170298_0 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_80170298_0;   /* part1 in func_80170298 */

typedef struct S_80170298_1 {
    u8 pad_00[0x8];
    void * unk_08;
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0xD];
    s16 unk_1C;
    s16 unk_1E;
} S_80170298_1;   /* part2 in func_80170298 */

void func_80170298(void)
{
    void *obj;
    S_80170298_0 *part1;
    S_80170298_1 *part2;

    obj = func_8003FC64(0x12);
    if (obj != 0) {
        (*(void * *)((u8 *)obj + 0x10)) = D_801701CC;
        func_8004491C(obj, D_80044BB0);

        do { part1 = (*(void * *)((u8 *)obj + 8)); } while (0);
        part1->unk_0A = 0;
        part1->unk_06 = 0;
        part1->unk_02 = 0;

        part2 = (*(void * *)((u8 *)obj + 0xC));
        part2->unk_1E = 0;
        part2->unk_1C = 0;
        part2->unk_0E = 0;
        part2->unk_0D = 0;
        part2->unk_0C = 0;

        (*(Copy12 *)((u8 *)obj + 0x48)) = D_80173B1C;
        part2->unk_08 = (u8 *)obj + 0x48;
    }
}
