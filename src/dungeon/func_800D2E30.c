#include "common.h"

typedef struct S_800D8590_0 {
    u8 pad_00[0xC];
    u8 * unk_0C;
    s32 unk_10;
} S_800D8590_0;   /* parent in func_800D8590 */

typedef struct S_800D8590_1 {
    u8 pad_00[0x13];
    u8 unk_13;
    u8 pad_14[0x16];
    s16 unk_2A;
    u8 pad_2C[0x7B];
    u8 unk_A7;
    u8 unk_A8;
} S_800D8590_1;   /* root in func_800D8590 */

typedef struct S_800D8590_2 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
    u8 pad_9D[0x3];
    s16 unk_A0;
    u8 pad_A2[0x6];
    s16 unk_A8;
    u8 pad_AA[0x2];
    s32 unk_AC;
} S_800D8590_2;   /* object in func_800D8590 */

typedef struct S_800D8590_3 {
    u8 pad_00[0x12];
    s16 unk_12;
    u16 unk_14;
} S_800D8590_3;   /* child in func_800D8590 */



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
    register u8 *child ASM_REG("$18");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    u8 *map;
    register u8 map_index ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */
    register u16 flags ASM_REG("$2");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    register void *result ASM_REG("$2");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
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

    child = ((S_800D8590_0 *)parent)->unk_0C;
    if (((S_800D8590_1 *)root)->unk_13 == 0) {
        func_80094E34();
        return func_800D86E8();
    }

    if (((S_800D8590_1 *)root)->unk_13 == 0x2B) {
        func_80042B68(root, 0x1A);
    }

    if ((((S_800D8590_1 *)root)->unk_13 == 0x15) &&
        (((S_800D8590_1 *)root)->unk_A7 != 0) &&
        (((S_800D8590_1 *)root)->unk_A8 != 0)) {
        map = *(u8 * volatile *)&D_800E3D7C;
        map_index = *(volatile u8 *)(root + 0xA8);
        map += map_index;
        map[0xF9] = 1;
    }
    bzero(parent + 0xAC, 0x24);

    object = parent + 0x20;
    ((S_800D8590_2 *)object)->unk_AC = ((S_800D8590_0 *)parent)->unk_10;
    ((S_800D8590_0 *)parent)->unk_10 = (s32)D_800D8728 & 0x7FFFFFFF;
    ((S_800D8590_2 *)object)->unk_A8 = ((S_800D8590_1 *)root)->unk_13;
    ((S_800D8590_1 *)root)->unk_13 = 0x2E;
    ((S_800D8590_2 *)object)->unk_9A = 0xFF;
    ((S_800D8590_2 *)object)->unk_9C = -1;
    ((S_800D8590_2 *)object)->unk_8C = D_800D8C64;
    (*(void ** *)((u8 *)child + 0x2C)) = D_800E262C;

    index = (D_80083228 + ((S_800D8590_1 *)root)->unk_2A + 0x100) >> 7;
    func_8003DB94(child,
                  *(void **)((u8 *)D_800E262C + (index & 0x1C)), 0);
    ((S_800D8590_2 *)object)->unk_A0 = 0x14;

    flags = ((S_800D8590_3 *)child)->unk_14;
    ((S_800D8590_3 *)child)->unk_12 = 0;
    flags |= 0x8000;
    ASM_KEEP(flags);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    ((S_800D8590_3 *)child)->unk_14 = flags;
    ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
    masked_flags = flags;
    result = root;
    *(volatile u16 *)(child + 0x14) = masked_flags & 0xFFF3;
    return result;
}

/* MECHANISM: Held D_80083460 plus split root/child/object lifetimes produce the
   retail 0x28 frame and s3/s2/s0 roles; byte-offset indexing keeps sra 7/andi 0x1c.
   Ordered volatile map reads restore the missing lbu, and a zero-operand schedule
   barrier after the first flag store places the v0-to-v1 copy exactly. */
