#include "common.h"


typedef s32 M2C_UNK;

typedef struct S_FUNC_80A23000_BODY_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_FUNC_80A23000_BODY_0;   /* obj in FUNC_80A23000_BODY */

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

extern s32 D_80045340;
extern u8 D_80083498[];
extern u8 D_8016AA58[];
extern u8 D_8016E820[];
extern u8 D_8016E860[];
extern M2C_UNK D_8016AE84;

#ifdef __mips__
/* The carved row starts with this 33-word text-local pointer/literal bank. */
extern void *func_8016A800(s32, s8, s8, s16);
extern void *func_8016A884(s16, s8, s8, s16);
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

void *FUNC_80A23000_BODY(s16 arg0, s8 arg1, s8 arg2, s16 arg3)
{
    s32 kind;
    void *obj;
    S_FUNC_80A23000_BODY_2 *part_a;
    S_FUNC_80A23000_BODY_3 *part_b;
    S_FUNC_80A23000_BODY_1 *work;
    S_FUNC_80A23000_BODY_4 *actor;
    s32 left;
    s32 right;
    register s8 saved_arg1 ASM_REG("$22");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    s16 saved_arg3;
    register s8 saved_arg2 ASM_REG("$21");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    void *call_a0;
    void *call_a1;

    work = 0;
    saved_arg1 = arg1;
    saved_arg3 = arg3;
    saved_arg2 = arg2;
    obj = func_8003FD64(0x112, D_80083498);
    if (obj != 0) {
        work = (u8 *)obj + 0x20;
        ((S_FUNC_80A23000_BODY_0 *)obj)->unk_10 = D_8016AA58;
        work->unk_13 = 5;
        func_8004491C(obj, &D_80045340);

        part_a = ((S_FUNC_80A23000_BODY_0 *)obj)->unk_08;
        part_a->unk_0A = saved_arg3;
        part_b = ((S_FUNC_80A23000_BODY_0 *)obj)->unk_0C;
        kind = arg0 & 3;
        part_b->unk_25 = saved_arg2;
        actor = work;
        part_b->unk_2C = D_8016E820;
        part_b->unk_24 = saved_arg1;

        if (kind == 1) {
            left = work->unk_14 | 0x6000;
            right = work->unk_1C | 0x6000;
            goto write_kind;
        }
        if (kind < 2) {
            goto normal_kind;
        }

        left = work->unk_14 | 0x2000;
        right = work->unk_1C | 0x2000;
write_kind:
        work->unk_14 = left;
        work->unk_1C = right;
        goto post_kind;

normal_kind:
        call_a0 = obj;
        if (((arg0 & ~3) << 16) == 0) {
            if (!(work->unk_14 & 0x200)) {
                call_a1 = part_a;
                ASM_KEEP(call_a0);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
                left = func_800A6D30();
                call_a0 = obj;
                if (!(left & 1)) {
                    goto call_a1_setup;
                }
                work->unk_1C |= 0x200;
                func_800A48F0(work, 1,
                              (func_800A6D30() & 0x3F) | 0x20);
                part_b->unk_2C = D_8016E860;
                goto post_kind;
            }
        }
        goto call_a1_setup;

post_kind:
        call_a0 = obj;
call_a1_setup:
        func_800A9C18(call_a0, part_a, part_b, arg0);
        actor->unk_9A = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C = &D_8016AE84;
        func_800AA36C(actor, part_a, part_b, work);
    }
    return work;
}
