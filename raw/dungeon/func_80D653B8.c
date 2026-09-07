#include "common.h"

#ifndef NULL
#define NULL 0
#endif

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

typedef struct {
    s32 word0;
    s32 word1;
    s32 word2;
    s32 word3;
} Block16;

extern void *func_8003FD64();
extern void func_8004491C();
extern void func_80045340(void);
extern void func_80047784();

extern s16 D_80083228[];
extern u8 D_80083498[];
extern u8 D_800D6FEC[];
extern u8 D_800E23D0[];

void func_80D653B8(void *arg0, void *arg1, Block16 *arg2,
                   void *arg3, s32 arg4)
{
    Block16 *end;
    void *linked;
    void *object_data;
    Block16 *dst;
    Block16 *src;
    void *position;
    void *work;

    (void)arg0;
    linked = func_8003FD64(0x112, D_80083498);
    if (linked != NULL) {
        src = arg2;
        work = (u8 *)linked + 0x20;
        FIELD(work, s16, 0x96) = arg4;
        FIELD(work, s16, 0xAA) = arg4;
        FIELD(linked, void *, 0x10) = D_800D6FEC;
        FIELD(work, void *, 0xB0) = arg1;
        object_data = FIELD(linked, void *, 0xC);
        end = src + 3;
        dst = (Block16 *)object_data;
        do {
            *dst = *src;
            src++;
            dst++;
        } while (src != end);

        FIELD(object_data, s16, 0x1E) = 0x1000;
        FIELD(object_data, s16, 0x1C) = 0x1000;
        FIELD(object_data, u8, 0xE) = 0x80;
        FIELD(object_data, u8, 0xD) = 0x80;
        FIELD(object_data, u8, 0xC) = 0x80;
        FIELD(object_data, s16, 0x10) = 0x20;
        FIELD(object_data, u16, 0x12) = 0xFF80;
        FIELD(object_data, s16, 0x6) = -6;
        FIELD(object_data, u16, 0x14) |= 0xC;
        func_8004491C(linked, func_80045340, src, dst);

        {
            u8 *table = D_800E23D0;

            FIELD(object_data, void *, 0x2C) = table;
            func_80047784(object_data,
                table[((D_80083228[0] + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
                0);
        }

        position = FIELD(linked, void *, 0x8);
        FIELD(position, u16, 0x2) = FIELD(arg1, u16, 0x2);
        FIELD(position, u16, 0x6) = FIELD(arg1, u16, 0x6);
        FIELD(position, u16, 0xA) =
            FIELD(arg1, u16, 0xA) + FIELD(arg1, u16, 0x16);
    }
}
