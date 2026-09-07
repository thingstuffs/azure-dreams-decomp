#include "common.h"

#define FIELD(ptr, type, off) (*(type *)((u8 *)(ptr) + (off)))

extern void func_8003DB94();
extern void func_80042B68();
extern void bzero();
extern void func_80094E34();
extern void *func_800D86E8();

extern s16 D_80083228;
extern s32 D_80083460;
extern u8 D_800D8728[];
extern u8 D_800D8C64[];
extern void *D_800E262C[];
extern u8 *D_800E3D7C;

void *func_800D8590(void *arg0)
{
    register u8 *child ASM_REG("$18");
    register u8 *map ASM_REG("$2");
    register u8 map_index ASM_REG("$3");
    register u16 flags ASM_REG("$2");
    register void *result ASM_REG("$2");
    u8 *root;
    s32 *global;
    u8 *parent;
    u8 *object;
    u16 masked_flags;
    s32 index;

    root = arg0;
    global = &D_80083460;
    parent = root - 0x20;
    if ((u8 *)global[4] == parent) {
        global[4] = (s32)parent & 0x7FFFFFFF;
    }

    child = FIELD(parent, u8 *, 0xC);
    if (FIELD(root, u8, 0x13) == 0) {
        func_80094E34();
        return func_800D86E8();
    }

    if (FIELD(root, u8, 0x13) == 0x2B) {
        func_80042B68(root, 0x1A);
    }

    if ((FIELD(root, u8, 0x13) == 0x15) &&
        (FIELD(root, u8, 0xA7) != 0) &&
        (FIELD(root, u8, 0xA8) != 0)) {
        map = *(u8 * volatile *)&D_800E3D7C;
        map_index = *(volatile u8 *)(root + 0xA8);
        map += map_index;
        map[0xF9] = 1;
    }
    bzero(parent + 0xAC, 0x24);

    object = parent + 0x20;
    FIELD(object, s32, 0xAC) = FIELD(parent, s32, 0x10);
    FIELD(parent, s32, 0x10) = (s32)D_800D8728 & 0x7FFFFFFF;
    FIELD(object, s16, 0xA8) = FIELD(root, u8, 0x13);
    FIELD(root, u8, 0x13) = 0x2E;
    FIELD(object, u8, 0x9A) = 0xFF;
    FIELD(object, s8, 0x9C) = -1;
    FIELD(object, u8 *, 0x8C) = D_800D8C64;
    FIELD(child, void **, 0x2C) = D_800E262C;

    index = (D_80083228 + FIELD(root, s16, 0x2A) + 0x100) >> 7;
    func_8003DB94(child,
                  *(void **)((u8 *)D_800E262C + (index & 0x1C)), 0);
    FIELD(object, s16, 0xA0) = 0x14;

    flags = FIELD(child, u16, 0x14);
    FIELD(child, s16, 0x12) = 0;
    flags |= 0x8000;
    ASM_KEEP(flags);
    FIELD(child, u16, 0x14) = flags;
    ASM_SCHED_BARRIER();
    masked_flags = flags;
    result = root;
    *(volatile u16 *)(child + 0x14) = masked_flags & 0xFFF3;
    ASM_KEEP(child);
    return result;
}

/* MECHANISM: Held D_80083460 plus split root/child/object lifetimes produce the
   retail 0x28 frame and s3/s2/s0 roles; byte-offset indexing keeps sra 7/andi 0x1c.
   Ordered volatile map reads restore the missing lbu, and a zero-operand schedule
   barrier after the first flag store places the v0-to-v1 copy exactly. */
