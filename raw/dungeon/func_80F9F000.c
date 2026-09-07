#include "common.h"

#define FIELD(p, type, offset) (*(type *)((u8 *)(p) + (offset)))

extern void *func_8003FD64();
extern void func_8004491C();
extern s32 func_800A6D30();
extern void func_800A48F0();
extern void func_800A9C18();
extern void func_800AA36C();

extern u8 D_80045340[];
extern u8 D_80083498[];
extern u8 D_80158A70[];
extern u8 D_8015CAD4[];
extern u8 D_8015CAFC[];
extern u8 D_80159138[];

extern void *func_80158800();

#ifdef __mips__
static const u32 bank_words[] __asm__("func_80158800")
    __attribute__((section(".text.func_80158800"), aligned(4))) = {
    0x80158880, 0x80158A70, 0x8015956C, 0x8015956C,
    0x8015956C, 0x80159598, 0x80159518, 0x80159518,
    0x80159518, 0x801594E0, 0x801594C4, 0x80159598,
    0x80159598, 0x8015955C, 0x8015AB5C, 0x8015AB54,
    0x8015AB4C, 0x8015AB64, 0x8015AB0C, 0x8015AB04,
    0x8015AAFC, 0x92824081, 0x81828F82, 0x85829282,
    0x44818482, 0x00000000, 0x0C001000, 0x18001000,
    0x00001400, 0x18001000, 0x08001000, 0x30320C00,
};
__asm__(".globl func_80158800\n"
        ".size func_80158800, 624");
#define BODY_NAME func_80158880
#else
#define BODY_NAME func_80158800
#endif

void *BODY_NAME(s16, s8, s8, s16)
#ifdef __mips__
    __attribute__((section(".text.func_80158800")))
#endif
    ;

void *BODY_NAME(s16 arg0, s8 arg1, s8 arg2, s16 arg3)
{
    s32 kind;
    register void *work ASM_REG("$16") = 0;
    register void *obj ASM_REG("$17");
    register void *part_a ASM_REG("$20");
    void *part_b;
    void *actor;
    s32 left;
    s32 right;
    register s8 saved_arg1 ASM_REG("$22");
    register s16 saved_arg3 ASM_REG("$18");
    register s8 saved_arg2 ASM_REG("$21");
    register void *call_a0 ASM_REG("$4");
    register void *call_a1 ASM_REG("$5");

    saved_arg1 = arg1;
    saved_arg3 = arg3;
    saved_arg2 = arg2;
    obj = func_8003FD64(0x112, D_80083498);
    if (obj != 0) {
        work = (u8 *)obj + 0x20;
        FIELD(obj, void *, 0x10) = D_80158A70;
        FIELD(work, s8, 0x13) = 0x26;
        func_8004491C(obj, &D_80045340);

        part_a = FIELD(obj, void **, 8);
        FIELD(part_a, s16, 0xA) = saved_arg3;
        part_b = FIELD(obj, void **, 0xC);
        kind = arg0 & 3;
        FIELD(part_b, s8, 0x25) = saved_arg2;
        actor = work;
        FIELD(part_b, void *, 0x2C) = D_8015CAD4;
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
                left = func_800A6D30();
                call_a0 = obj;
                if (!(left & 1)) {
                    goto call_a1_setup;
                }
                FIELD(work, s32, 0x1C) |= 0x200;
                func_800A48F0(work, 1,
                              (func_800A6D30(obj) & 0x3F) | 0x20);
                FIELD(part_b, void *, 0x2C) = D_8015CAFC;
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
        FIELD(actor, void *, 0x8C) = D_80159138;
        FIELD(work, s32, 0x1C) |= 0x40000;
        FIELD(actor, s16, 0xA0) = 0;
        FIELD(actor, s16, 0x92) = -0x30;
        func_800AA36C(actor, part_a, part_b, work);
    }
    return work;
}
