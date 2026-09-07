#include "common.h"

#define FIELD(p, t, o) (*(t *)((u8 *)(p) + (o)))

extern void *func_8003FC64();
extern void func_8004491C();
extern void func_8003DB94();
extern void func_800254C4();
extern s16 rand();

extern u8 D_80024A00[];
extern u8 D_80045340[];
extern u8 D_800DE938[];

void *func_80024A98(void *arg0)
{
    s16 angle;
    s32 i;
    void *part;
    void *coords;
    void *node;

    node = func_8003FC64(0x202);
    if (node != 0) {
        FIELD(node, void *, 0x10) = D_80024A00;
        func_8004491C(node, D_80045340);
        coords = FIELD(node, void *, 8);
        FIELD(coords, u16, 2) = FIELD(arg0, u16, 2);
        FIELD(coords, u16, 6) = FIELD(arg0, u16, 6);
        FIELD(coords, u16, 0xA) = FIELD(arg0, u16, 0xA);
        part = FIELD(node, void *, 0xC);
        FIELD(part, s16, 0x1E) = 0x1000;
        FIELD(part, s16, 0x1C) = 0x1000;
        FIELD(part, s32, 0xC) = 0x808080;
        func_8003DB94(part, D_800DE938, 0);
        FIELD(part, s16, 0x10) = 0x20;
        FIELD(part, u16, 0x14) |= 0xC;
        i = 0;
        angle = rand();
        do {
            func_800254C4(coords, angle, 0x10, 1);
            i++;
            angle += 0x100;
        } while (i < 0x10);
    }
    return node;
}
