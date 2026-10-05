#include "common.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"


typedef s32 M2C_UNK;

typedef struct S_FUNC_80A23000_BODY_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_FUNC_80A23000_BODY_0;   /* object in FUNC_80A23000_BODY */

typedef struct S_FUNC_80A23000_BODY_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_FUNC_80A23000_BODY_1;   /* work in FUNC_80A23000_BODY */

typedef struct S_FUNC_80A23000_BODY_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_FUNC_80A23000_BODY_2;   /* part_a in FUNC_80A23000_BODY */

typedef struct S_FUNC_80A23000_BODY_3 {
    u8 pad_00[0x24];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} S_FUNC_80A23000_BODY_3;   /* part_b in FUNC_80A23000_BODY */

typedef struct S_FUNC_80A23000_BODY_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_FUNC_80A23000_BODY_4;   /* actor in FUNC_80A23000_BODY */


extern void *func_8003FD64();
extern void func_8004491C();
extern s32 func_800A6D30(void);
extern void func_800A48F0();
extern void func_800A9C18();
extern void func_800AA36C();

extern u8 D_8016AA58[];
extern u8 D_8016E820[];
extern u8 D_8016E860[];
extern M2C_UNK D_8016AE84;

#ifdef __mips__
/* The carved row starts with this 33-word text-local pointer/literal bank. */
extern void *func_8016A800(s16 spawn_flags, s16 attr_a, s16 attr_b, s16 attr_c);
extern void *func_8016A884(s16, s16, s16, s16);
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

static const u32 func_8016A800_prefix[33] __asm__("func_8016A800")
__attribute__((section(".text.func_8016A800"), aligned(4))) = {
    (u32)func_8016A884,
    (u32)D_8016AA58,
    (u32)func_8016B24C,
    (u32)func_8016B24C,
    (u32)func_8016B24C,
    (u32)func_8016B278,
    (u32)func_8016B1F8,
    (u32)func_8016B1F8,
    (u32)func_8016B1F8,
    (u32)func_8016B1C0,
    (u32)func_8016B1C0,
    (u32)func_8016B278,
    (u32)func_8016B278,
    (u32)func_8016B23C,
    0x10001000,
    0x0DAC1194,
    0x10001000,
    0x12C00D48,
    0x11300ED8,
    0x10001000,
    0x0D481388,
    0x0ED81194,
    (u32)func_8016C9EC,
    (u32)func_8016C9E4,
    (u32)func_8016C9DC,
    (u32)func_8016C9F4,
    (u32)func_8016C99C,
    (u32)func_8016C994,
    (u32)func_8016C98C,
    0x01000340,
    0x00800040,
    0x01000340,
    0x00400040,
};
__asm__(".globl func_8016A800\n"
        ".size func_8016A800, 600");

#define FUNC_80A23000_BODY func_8016A884
#else
#define FUNC_80A23000_BODY func_80A23000
#endif

void *FUNC_80A23000_BODY(s16 mask, s16 value_24_input, s16 value_25_input, s16 value_0A_input)
{
    s32 kind;
    void *object;
    S_FUNC_80A23000_BODY_2 *part_a;
    S_FUNC_80A23000_BODY_3 *part_b;
    S_FUNC_80A23000_BODY_1 *work;
    S_FUNC_80A23000_BODY_4 *actor;
    s32 value_14;
    s32 value_1C;
    s16 value_0A;

    work = 0;
    value_0A = value_0A_input;
    object = func_8003FD64(0x112, ((u8 *)(&D_80083498)));
    if (object != 0) {
        work = (u8 *)object + 0x20;
        ((S_FUNC_80A23000_BODY_0 *)object)->unk_10 = D_8016AA58;
        work->unk_13 = 5;
        func_8004491C(object, func_80045340);

        part_a = ((S_FUNC_80A23000_BODY_0 *)object)->unk_08;
        part_a->unk_0A = value_0A;
        part_b = ((S_FUNC_80A23000_BODY_0 *)object)->unk_0C;
        kind = mask & 3;
        part_b->unk_25 = value_25_input;
        actor = work;
        part_b->unk_2C = D_8016E820;
        part_b->unk_24 = value_24_input;

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
                    part_b->unk_2C = D_8016E860;
                }
            }
        }
        func_800A9C18(((void *)(object)), part_a, part_b, mask);
        actor->unk_9A = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C = &D_8016AE84;
        func_800AA36C(actor, part_a, part_b, work);
    }
    return work;
}
