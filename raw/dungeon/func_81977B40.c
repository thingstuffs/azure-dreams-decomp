#include "common.h"

#ifndef NULL
#define NULL 0
#endif

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern void *func_8003FD64();
extern void func_8004491C();
extern s32 rand();

extern u8 D_80024D84[9];
extern u8 D_800251E8[9];
extern u8 D_80083498[9];

void func_81977B40(void *arg0)
{
    s16 angle;
    s32 random;
    s32 random2;
    s32 parent;
    s32 i;
    void *object;
    u8 *base;
    register u8 *new_base ASM_REG("$2");

    base = arg0;
    object = func_8003FD64(0x212, D_80083498);
    i = 0;
    if (object != NULL) {
        do { FIELD(object, void *, 0x10) = D_800251E8; } while (0);
        new_base = (u8 *)object + 0x20;
        ASM_KEEP(new_base);
        parent = FIELD(base, s32, 0x20);
        base = new_base;
        FIELD(object, s32, 0x20) = parent;
        FIELD(base, s16, 4) = 0;
        FIELD(base, s16, 6) = 0;
        FIELD(base, s16, 8) = 0;
        do {
            FIELD(base, s16, 0xA) = 0;
            random = rand();
            angle = ((i % 6) * 0x2AA) + (random % 33) - 0x10;
            FIELD(base, s16, 0x46) = angle;
            random2 = rand();
            i++;
            FIELD(base, s16, 0x82) = (random2 % 9) - 4;
            base += 2;
        } while (i < 0x1E);
        func_8004491C(object, D_80024D84);
    }
}
