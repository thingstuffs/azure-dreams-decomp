#include "common.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"


typedef s32 M2C_UNK;

typedef struct S_80170884_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80170884_0;   /* object in func_80170884 */

typedef struct S_80170884_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_80170884_1;   /* work in func_80170884 */

typedef struct S_80170884_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80170884_2;   /* part_a in func_80170884 */

typedef struct S_80170884_3 {
    u8 pad_00[0x24];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} S_80170884_3;   /* part_b in func_80170884 */

typedef struct S_80170884_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_80170884_4;   /* actor in func_80170884 */


extern void *func_8003FD64();
extern void func_8004491C();
extern s32 func_800A6D30(void);
extern void func_800A48F0();
extern void func_800A9C18();
extern void func_800AA36C();
extern void func_80170E70(void);
extern void func_80172654(void);

extern u8 D_80170A58[];
extern u8 D_80174820[];
extern u8 D_80174860[];
extern M2C_UNK D_80170E84;

extern void *func_80170800(s32, s8, s8, s16);
extern void *func_80170884(s16, s16, s16, s16);
extern void *func_8016B24C(void);
extern void *func_8016B278(void);
extern void *func_8016B1F8(void);
extern void *func_8016B1C0(void);
extern void *func_8016B23C(void);
extern void *func_8016C9EC(void);
extern void *func_8016C9E4(void);
extern void *func_8016C9DC(void);
extern void *func_8016C9F4(void);
extern void *func_8016C99C(void);
extern void *func_8016C994(void);
extern void *func_8016C98C(void);

static const u32 func_80170800_prefix[33] __asm__("func_80170800")
__attribute__((section(".text.func_80170800"), aligned(4))) = {
    (u32)func_80170884,
    (u32)D_80170A58,
    (u32)((u8 *)func_80170E70 + 0x3DC),
    (u32)((u8 *)func_80170E70 + 0x3DC),
    (u32)((u8 *)func_80170E70 + 0x3DC),
    (u32)((u8 *)func_80170E70 + 0x408),
    (u32)((u8 *)func_80170E70 + 0x388),
    (u32)((u8 *)func_80170E70 + 0x388),
    (u32)((u8 *)func_80170E70 + 0x388),
    (u32)((u8 *)func_80170E70 + 0x350),
    (u32)((u8 *)func_80170E70 + 0x350),
    (u32)((u8 *)func_80170E70 + 0x408),
    (u32)((u8 *)func_80170E70 + 0x408),
    (u32)((u8 *)func_80170E70 + 0x3CC),
    0x10001000,
    0x0DAC1194,
    0x10001000,
    0x12C00D48,
    0x11300ED8,
    0x10001000,
    0x0D481388,
    0x0ED81194,
    (u32)((u8 *)func_80172654 + 0x398),
    (u32)((u8 *)func_80172654 + 0x390),
    (u32)((u8 *)func_80172654 + 0x388),
    (u32)((u8 *)func_80172654 + 0x3A0),
    (u32)((u8 *)func_80172654 + 0x348),
    (u32)((u8 *)func_80172654 + 0x340),
    (u32)((u8 *)func_80172654 + 0x338),
    0x01000340,
    0x00800040,
    0x01000340,
    0x00400040,
};
__asm__(".globl func_80170800\n"
        ".size func_80170800, 600");

void *func_80170884(s16 mask, s16 value_24_input, s16 value_25_input, s16 value_0A_input)
{
    s32 kind;
    void *object;
    S_80170884_2 *part_a;
    S_80170884_3 *part_b;
    S_80170884_1 *work;
    S_80170884_4 *actor;
    s32 value_14;
    s32 value_1C;
    s8 value_24;
    s16 value_0A;
    s8 value_25;

    work = 0;
    value_24 = value_24_input;
    value_0A = value_0A_input;
    value_25 = value_25_input;
    object = func_8003FD64(0x112, ((u8 *)(&D_80083498)));
    if (object != 0) {
        work = (u8 *)object + 0x20;
        ((S_80170884_0 *)object)->unk_10 = D_80170A58;
        work->unk_13 = 5;
        func_8004491C(object, func_80045340);

        part_a = ((S_80170884_0 *)object)->unk_08;
        part_a->unk_0A = value_0A;
        part_b = ((S_80170884_0 *)object)->unk_0C;
        kind = mask & 3;
        part_b->unk_25 = value_25;
        actor = work;
        part_b->unk_2C = D_80174820;
        part_b->unk_24 = value_24;

        if (kind == 1) {
            value_14 = work->unk_14 | 0x6000;
            value_1C = work->unk_1C | 0x6000;
            work->unk_14 = value_14;
            work->unk_1C = value_1C;
        } else if (kind >= 2) {
            value_14 = work->unk_14 | 0x2000;
            value_1C = work->unk_1C | 0x2000;
            work->unk_14 = value_14;
            work->unk_1C = value_1C;
        } else if (((mask & ~3) << 16) == 0) {
            if (!(work->unk_14 & 0x200)) {
                value_14 = func_800A6D30();
                if (value_14 & 1) {
                    work->unk_1C |= 0x200;
                    func_800A48F0(work, 1,
                                  (func_800A6D30() & 0x3F) | 0x20);
                    part_b->unk_2C = D_80174860;
                }
            }
        }
        func_800A9C18(((void *)(object)), part_a, part_b, mask);
        actor->unk_9A = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C = &D_80170E84;
        func_800AA36C(actor, part_a, part_b, work);
    }
    return work;
}
