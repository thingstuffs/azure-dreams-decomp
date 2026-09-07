#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

extern void *func_8003FD64();
extern void func_8004491C();
extern void func_800A48F0();
extern s32 func_800A6D30();
extern void func_800A9C18();
extern void func_800AA36C();

extern s32 D_80045340;
extern u8 D_80083498[];
extern u8 D_80170A7C[];
extern u8 D_80170EA8[];
extern u8 D_80174038[];
extern u8 D_80174088[];
extern void *func_801708A8();
extern u8 D_801712B8[];
extern u8 D_801712E4[];
extern u8 D_80171264[];
extern u8 D_801711F4[];
extern u8 D_801711E4[];
extern u8 D_801712A8[];
extern u8 D_80172AC4[];
extern u8 D_80172ABC[];
extern u8 D_80172AB4[];
extern u8 D_80172ACC[];
extern u8 D_80172A74[];
extern u8 D_80172A6C[];
extern u8 D_80172A64[];

#ifdef __mips__
static const u32 bank_words[] __asm__("func_80170800")
    __attribute__((section(".text.func_80170800"), aligned(4))) = {
    (u32)func_801708A8,
    (u32)D_80170A7C,
    (u32)D_801712B8,
    (u32)D_801712B8,
    (u32)D_801712B8,
    (u32)D_801712E4,
    (u32)D_80171264,
    (u32)D_80171264,
    (u32)D_80171264,
    (u32)D_801711F4,
    (u32)D_801711E4,
    (u32)D_801712E4,
    (u32)D_801712E4,
    (u32)D_801712A8,
    (u32)D_80172AC4,
    (u32)D_80172ABC,
    (u32)D_80172AB4,
    (u32)D_80172ACC,
    (u32)D_80172A74,
    (u32)D_80172A6C,
    (u32)D_80172A64,
    0x89824081,
    0x40819382,
    0x93829082,
    0x83829982,
    0x85828882,
    0x7c818482,
    0x90829582,
    0x00004481,
    0x92824081,
    0x96828582,
    0x81828582,
    0x85828c82,
    0x40818482,
    0x94828982,
    0x40819382,
    0x92829482,
    0x85829582,
    0x90824081,
    0x97828f82,
    0x92828582,
    0xff004481,
};
__asm__(".globl func_80170800\n"
        ".size func_80170800, 636");
#define BODY_NAME func_801708A8
#else
#define BODY_NAME func_80170800
#endif

void *BODY_NAME(void *arg0, s32 arg1, s32 arg2, s32 arg3)
#ifdef __mips__
    __attribute__((section(".text.func_80170800")))
#endif
    ;

void *BODY_NAME(void *arg0, s32 arg1, s32 arg2, s32 arg3)
{
    register void *result ASM_REG("$16") = 0;
    register void *created ASM_REG("$17");
    register void *position ASM_REG("$20");
    void *part_b;
    void *actor;
    s32 left;
    s32 right;
    register s32 saved_arg1 ASM_REG("$22");
    register s32 saved_arg3 ASM_REG("$18");
    register s32 saved_arg2 ASM_REG("$21");
    register s32 saved_arg0 = (s32)arg0;
    register s32 original_arg0 ASM_REG("$23");
    register void *call_a0 ASM_REG("$4");
    register void *call_a1 ASM_REG("$5");
    s32 kind;

    saved_arg1 = arg1;
    saved_arg3 = arg3;
    saved_arg2 = arg2;
    created = func_8003FD64(0x112, D_80083498);
    original_arg0 = saved_arg0;
    if (created == 0) {
        goto done;
    }

    result = (u8 *)created + 0x20;
    FIELD(created, void *, 0x10) = D_80170A7C;
    FIELD(result, s8, 0x13) = 0x28;
    func_8004491C(created, &D_80045340);

    position = FIELD(created, void *, 8);
    FIELD(position, s16, 0xA) = saved_arg3;
    part_b = FIELD(created, void *, 0xC);
    kind = saved_arg0 & 3;
    FIELD(part_b, s8, 0x25) = saved_arg2;
    actor = result;
    FIELD(part_b, void *, 0x2C) = D_80174038;
    FIELD(part_b, s8, 0x24) = saved_arg1;

    if (kind == 1) {
        FIELD(result, u32, 0x14) |= 0x6000;
        FIELD(result, u32, 0x1C) |= 0x6000;
        goto setup;
    }
    if (kind >= 2) {
        FIELD(result, u32, 0x14) |= 0x2000;
        FIELD(result, u32, 0x1C) |= 0x2000;
        goto setup;
    }

    call_a0 = created;
    if (((saved_arg0 & ~3) << 16) == 0) {
        if (!(FIELD(result, u32, 0x14) & 0x200)) {
            call_a1 = position;
            if (func_800A6D30() & 1) {
                FIELD(result, u32, 0x1C) |= 0x200;
                func_800A48F0(result, 1,
                    (func_800A6D30() & 0x3F) | 0x20);
                FIELD(part_b, void *, 0x2C) = D_80174088;
            }
        }
    }

setup:
    func_800A9C18(created, position, part_b,
        (s16)original_arg0);
    FIELD(actor, u8, 0x9A) = 0xFF;
    FIELD(actor, s8, 0x9C) = -1;
    FIELD(actor, void *, 0x8C) = D_80170EA8;
    func_800AA36C(actor, position,
        part_b, result);

done:
    return result;
}
