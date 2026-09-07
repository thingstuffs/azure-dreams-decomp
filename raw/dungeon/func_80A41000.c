#include "common.h"

#define FIELD(p, type, offset) (*(type *)((u8 *)(p) + (offset)))

typedef s32 M2C_UNK;

extern void *func_8003FD64();
extern void func_8004491C();
extern s32 func_800A6D30();
extern void func_800A48F0();
extern void func_800A9C18();
extern void func_800AA36C();

extern s32 D_80045340;
extern u8 D_80083498[];
extern u8 D_8014CA58[];
extern u8 D_80150820[];
extern u8 D_80150860[];
extern M2C_UNK D_8014CE84;

/* The carved row starts with this 33-word text-local pointer/literal bank. */
extern void *func_8014C800(s32, s8, s8, s16);
extern void *func_8014C884(s16, s8, s8, s16);
extern u8 D_8014D24C[];
extern u8 D_8014D278[];
extern u8 D_8014D1F8[];
extern u8 D_8014D1C0[];
extern u8 D_8014D23C[];
extern u8 D_8014E9EC[];
extern u8 D_8014E9E4[];
extern u8 D_8014E9DC[];
extern u8 D_8014E9F4[];
extern u8 D_8014E99C[];
extern u8 D_8014E994[];
extern u8 D_8014E98C[];

/* These text-local table entries have no catalog symbols. */
__asm__(".set D_8014D24C, 0x8014D24C");
__asm__(".set D_8014D278, 0x8014D278");
__asm__(".set D_8014D1F8, 0x8014D1F8");
__asm__(".set D_8014D1C0, 0x8014D1C0");
__asm__(".set D_8014D23C, 0x8014D23C");
__asm__(".set D_8014E9EC, 0x8014E9EC");
__asm__(".set D_8014E9E4, 0x8014E9E4");
__asm__(".set D_8014E9DC, 0x8014E9DC");
__asm__(".set D_8014E9F4, 0x8014E9F4");
__asm__(".set D_8014E99C, 0x8014E99C");
__asm__(".set D_8014E994, 0x8014E994");
__asm__(".set D_8014E98C, 0x8014E98C");

static const u32 func_8016A800_prefix[33] __asm__("func_8014C800")
    __attribute__((section(".text.func_8014C800"), aligned(4))) = {
        (u32)func_8014C884,
        (u32)D_8014CA58,
        (u32)D_8014D24C,
        (u32)D_8014D24C,
        (u32)D_8014D24C,
        (u32)D_8014D278,
        (u32)D_8014D1F8,
        (u32)D_8014D1F8,
        (u32)D_8014D1F8,
        (u32)D_8014D1C0,
        (u32)D_8014D1C0,
        (u32)D_8014D278,
        (u32)D_8014D278,
        (u32)D_8014D23C,
        0x10001000,
        0x0DAC1194,
        0x10001000,
        0x12C00D48,
        0x11300ED8,
        0x10001000,
        0x0D481388,
        0x0ED81194,
        (u32)D_8014E9EC,
        (u32)D_8014E9E4,
        (u32)D_8014E9DC,
        (u32)D_8014E9F4,
        (u32)D_8014E99C,
        (u32)D_8014E994,
        (u32)D_8014E98C,
        0x01000340,
        0x00800040,
        0x01000340,
        0x00400040,
    };
__asm__(".globl func_8014C800\n"
        ".size func_8014C800, 600");

void *func_8014C884(s16 arg0, s8 arg1, s8 arg2, s16 arg3)
{
    s32 kind;
    void *obj;
    void *part_a;
    void *part_b;
    void *work;
    void *actor;
    register s32 left ASM_REG("$2");
    register s32 right ASM_REG("$3");
    register s8 saved_arg1 ASM_REG("$22");
    register s16 saved_arg3 ASM_REG("$18");
    register s8 saved_arg2 ASM_REG("$21");
    register void *call_a0 ASM_REG("$4");
    register void *call_a1 ASM_REG("$5");

    work = 0;
    saved_arg1 = arg1;
    saved_arg3 = arg3;
    saved_arg2 = arg2;
    obj = func_8003FD64(0x112, D_80083498);
    if (obj != 0) {
        work = (u8 *)obj + 0x20;
        FIELD(obj, void *, 0x10) = D_8014CA58;
        FIELD(work, s8, 0x13) = 5;
        func_8004491C(obj, &D_80045340);

        part_a = FIELD(obj, void *, 8);
        FIELD(part_a, s16, 0xA) = saved_arg3;
        part_b = FIELD(obj, void *, 0xC);
        kind = arg0 & 3;
        FIELD(part_b, s8, 0x25) = saved_arg2;
        actor = work;
        FIELD(part_b, void *, 0x2C) = D_80150820;
        FIELD(part_b, s8, 0x24) = saved_arg1;

        if (kind == 1) {
            left = FIELD(work, s32, 0x14) | 0x6000;
            right = FIELD(work, s32, 0x1C) | 0x6000;
            goto write_kind;
        }
        if (kind < 2) {
            goto normal_kind;
        }

        left = FIELD(work, s32, 0x14) | 0x2000;
        right = FIELD(work, s32, 0x1C) | 0x2000;
write_kind:
        FIELD(work, s32, 0x14) = left;
        FIELD(work, s32, 0x1C) = right;
        goto post_kind;

normal_kind:
        call_a0 = obj;
        if (((arg0 & ~3) << 16) == 0) {
            if (!(FIELD(work, s32, 0x14) & 0x200)) {
                call_a1 = part_a;
                ASM_KEEP(call_a0);
                ASM_KEEP(call_a1);
                left = func_800A6D30();
                call_a0 = obj;
                if (!(left & 1)) {
                    goto call_a1_setup;
                }
                FIELD(work, s32, 0x1C) |= 0x200;
                func_800A48F0(work, 1,
                              (func_800A6D30(obj) & 0x3F) | 0x20);
                FIELD(part_b, void *, 0x2C) = D_80150860;
                goto post_kind;
            }
        }
        goto call_a1_setup;

post_kind:
        call_a0 = obj;
call_a1_setup:
        func_800A9C18(call_a0, part_a, part_b, arg0);
        FIELD(actor, u8, 0x9A) = 0xFF;
        FIELD(actor, s8, 0x9C) = -1;
        FIELD(actor, void *, 0x8C) = &D_8014CE84;
        func_800AA36C(actor, part_a, part_b, work);
    }
    return work;
}
