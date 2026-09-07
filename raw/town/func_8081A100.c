#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct Vec3i {
    s32 x;
    s32 y;
    s32 z;
} Vec3i;

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern Vec3i D_80020090;
extern Vec3i D_800200A8;
extern s32 D_800243D8;
extern s32 D_80024954;
extern s32 D_800249A0;
extern s32 D_80024A30;
extern s32 D_80053858[4];
extern s32 D_80053A88;
extern u8 D_80083498[];

extern void func_80033B9C(s32);
extern void func_8003E188(s32, void *);
extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern void func_80048568(s32);
extern s32 rand(void);
extern void func_800C15C0(s32, s32);

s32 func_80024100(void)
{
    Vec3i first;
    Vec3i second;
    register void *root ASM_REG("$18");
    void *obj;
    void *part;
    void *callback;
    register void *final_callback ASM_REG("$5");
    void *link;
    s32 i;
    register s32 coord ASM_REG("$19");
    s32 value;
    register u16 flags ASM_REG("$3");

    root = NULL;
    first = D_80020090;
    second = D_800200A8;

    func_800C15C0(0x24, 0x200);
    func_80033B9C(0x552);
    func_80033B9C(0xA4);
    func_80033B9C(0xA5);
    func_80048568(7);
    func_8003E188(0x3F, root);

    obj = func_8003FD64(0x136, D_80083498);
    if (obj != NULL) {
        root = (u8 *)obj + 0x20;
        FIELD(obj, void *, 0x10) = &D_800243D8;
        FIELD(root, s16, 0xA) = 0x1E;
        value = rand();
        FIELD(root, s16, 4) = value & 3;
        FIELD(root, u16, 0xC) |= 4;
    }

    i = 2;
    callback = &D_80024954;
    coord = 0xD0;
    do {
        obj = func_8003FD64(1, D_80083498);
        part = (u8 *)obj + 0x20;
        if (obj != NULL) {
            FIELD(obj, void *, 0x10) = callback;
            func_8004491C(obj, D_80053858);
            FIELD(part, s16, 0x16) = 0xB4;
            FIELD(part, s16, 0x18) = 3;
            FIELD(part, s16, 0x1A) = 0x7C80;
            FIELD(part, s16, 0x14) = coord;
            FIELD(part, s32, 0x10) = 0x808080;
            FIELD(part, s32, 4) = ((s32 *)&first)[i];
            FIELD(part, void *, 0xC) = root;
        }
        i--;
        coord -= 0x58;
    } while (i >= 0);

    i = 2;
    callback = &D_800249A0;
    coord = 0xD8;
    do {
        obj = func_8003FD64(1, D_80083498);
        part = (u8 *)obj + 0x20;
        if (obj != NULL) {
            FIELD(obj, void *, 0x10) = callback;
            func_8004491C(obj, D_80053858);
            FIELD(part, s16, 0x16) = 0xC4;
            FIELD(part, s16, 0x18) = 3;
            FIELD(part, s16, 0x1A) = 0x7C80;
            FIELD(part, s16, 0x14) = coord;
            FIELD(part, s32, 0x10) = 0x808080;
            FIELD(part, s32, 4) = ((s32 *)&second)[i];
            switch (i) {
            case 0:
                link = (u8 *)root + 6;
                break;
            case 1:
                link = (u8 *)root + 8;
                break;
            case 2:
                link = (u8 *)root + 0xA;
                break;
            default:
                FIELD(part, void *, 0xC) = root;
                goto second_continue;
            }
            FIELD(part, void *, 8) = link;
            FIELD(part, void *, 0xC) = root;
        }
second_continue:
        i--;
        coord -= 0x58;
    } while (i >= 0);

    i = 2;
    callback = &D_80024A30;
    coord = 0xCC;
    do {
        obj = func_8003FD64(1, D_80083498);
        if (obj != NULL) {
            final_callback = &D_80053A88;
            ASM_KEEP(final_callback);
            part = (u8 *)obj + 0x20;
            FIELD(obj, void *, 0x10) = callback;
            func_8004491C(obj, final_callback);
            flags = FIELD(part, u16, 0x16);
            FIELD(part, s16, 0xE) = 0xB0;
            FIELD(part, s16, 0x10) = 0x50;
            FIELD(part, s16, 0x12) = 0x20;
            FIELD(part, s16, 0xC) = coord;
            FIELD(part, s16, 0x14) = 2;
            FIELD(part, s32, 8) = 0x404040;
            FIELD(part, void *, 4) = root;
            flags |= 1;
            FIELD(part, u16, 0x16) = flags;
            ASM_KEEP(flags);
        }
        i--;
        coord -= 0x58;
    } while (i >= 0);

    ASM_KEEP(root);
    ASM_KEEP(coord);
    return 0;
}
