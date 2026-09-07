#include "common.h"

#define FIELD(p, type, offset) (*(type *)((u8 *)(p) + (offset)))

typedef s32 M2C_UNK;

extern void *func_8003FD64();
extern void func_8004491C();
extern s32 func_800A6D30();
extern void func_800A48F0();
extern void func_800A9C18();
extern void func_800AA36C();
extern void *func_8015E974() __attribute__((noreturn));
extern void *func_8015E9EC() __attribute__((noreturn));

extern s32 D_80045340;
extern u8 D_80083498[];
extern u8 D_8015EA68[];
extern M2C_UNK D_8015EE94;
extern u8 D_80162A7C[];
extern u8 D_80162AD4[];

#ifdef __mips__
static const u32 bank_words[] __asm__("func_80F45000")
    __attribute__((section(".text.func_80F45000"), aligned(4))) = {
    0x8015E894, 0x8015EA68, 0x8015F278, 0x8015F278,
    0x8015F278, 0x8015F2A4, 0x8015F224, 0x8015F224,
    0x8015F224, 0x8015F1D0, 0x8015F208, 0x8015F2A4,
    0x8015F2A4, 0x8015F268, 0x08000000, 0x00200080,
    0x00800800, 0x08000000, 0x00000080, 0x08000020,
    0x00000040, 0x00800800, 0x00000010, 0x00000080,
    0x801608B4, 0x801609BC, 0x80160A24, 0x80160AC0,
    0x80160D90, 0x80160E14, 0x80161078, 0x80161070,
    0x80161068, 0x80161080, 0x80161028, 0x80161020,
    0x80161018,
};
__asm__(".globl func_80F45000\n"
        ".size func_80F45000,616");
#define BODY_NAME func_80F45094
#else
#define BODY_NAME func_80F45000
#endif

#ifdef __mips__
void *BODY_NAME(s16 arg0, s8 arg1, s8 arg2, s16 arg3)
    __attribute__((section(".text.func_80F45000")));
#endif
void *BODY_NAME(s16 arg0, s8 arg1, s8 arg2, s16 arg3)
{
    register void *work ASM_REG("$16") = 0;
    register void *obj ASM_REG("$17");
    register void *part_a ASM_REG("$20");
    register void *part_b;
    void *actor;
    register s32 kind;
    s32 probe;
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
        FIELD(obj, void *, 0x10) = D_8015EA68;
        FIELD(work, s8, 0x13) = 0x24;
        func_8004491C(obj, &D_80045340);

        part_a = FIELD(obj, void *, 8);
        FIELD(part_a, s16, 0xA) = saved_arg3;
        part_b = FIELD(obj, void *, 0xC);
        kind = arg0 & 3;
        FIELD(part_b, s8, 0x25) = saved_arg2;
        actor = work;
        FIELD(part_b, void *, 0x2C) = D_80162A7C;
        FIELD(part_b, s8, 0x24) = saved_arg1;

        if (kind == 1) {
            register s32 left ASM_REG("$2");
            register s32 right ASM_REG("$3");

            left = FIELD(work, s32, 0x14) | 0x6000;
            right = FIELD(work, s32, 0x1C) | 0x6000;
            ASM_KEEP(left);
            ASM_TAILSLOT_PIN(right);
            return func_8015E974();
        }
        if (kind >= 2) {
            FIELD(work, s32, 0x14) |= 0x2000;
            FIELD(work, s32, 0x1C) |= 0x2000;
            return func_8015E9EC();
        }

        call_a0 = obj;
        if (((arg0 & ~3) << 16) == 0) {
            if (!(FIELD(work, s32, 0x14) & 0x200)) {
                call_a1 = part_a;
                probe = func_800A6D30();
                call_a0 = obj;
                if (!(probe & 1)) {
                    goto post_kind;
                }
                    FIELD(work, s32, 0x1C) |= 0x200;
                    func_800A48F0(work, 1,
                                  (func_800A6D30() & 0x3F) | 0x20);
                    FIELD(part_b, void *, 0x2C) = D_80162AD4;
            }
        }

post_kind:
        func_800A9C18(obj, part_a, part_b, arg0);
        FIELD(actor, u8, 0x9A) = 0xFF;
        FIELD(actor, s8, 0x9C) = -1;
        FIELD(actor, void *, 0x8C) = &D_8015EE94;
        func_800AA36C(actor, part_a, part_b, work);
    }
    return work;
}
