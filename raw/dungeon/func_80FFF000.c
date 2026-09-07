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
extern u8 D_8014CA7C[];
extern u8 D_8014CEA8[];
extern u8 D_80150038[];
extern u8 D_80150088[];
extern u8 D_8014D2B8[];
extern u8 D_8014D2E4[];
extern u8 D_8014D264[];
extern u8 D_8014D1F4[];
extern u8 D_8014D1E4[];
extern u8 D_8014D2A8[];
extern u8 D_8014EAC4[];
extern u8 D_8014EABC[];
extern u8 D_8014EAB4[];
extern u8 D_8014EACC[];
extern u8 D_8014EA74[];
extern u8 D_8014EA6C[];
extern u8 D_8014EA64[];

#ifdef __mips__
extern void *func_8014C8A8(void *, s32, s32, s32);

static const u32 bank_words[] __asm__("func_8014C800")
    __attribute__((section(".text.func_8014C800"), aligned(4))) = {
    (u32)func_8014C8A8,
    (u32)D_8014CA7C,
    (u32)D_8014D2B8,
    (u32)D_8014D2B8,
    (u32)D_8014D2B8,
    (u32)D_8014D2E4,
    (u32)D_8014D264,
    (u32)D_8014D264,
    (u32)D_8014D264,
    (u32)D_8014D1F4,
    (u32)D_8014D1E4,
    (u32)D_8014D2E4,
    (u32)D_8014D2E4,
    (u32)D_8014D2A8,
    (u32)D_8014EAC4,
    (u32)D_8014EABC,
    (u32)D_8014EAB4,
    (u32)D_8014EACC,
    (u32)D_8014EA74,
    (u32)D_8014EA6C,
    (u32)D_8014EA64,
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
    0x12004481,
};
__asm__(".globl func_8014C800\n"
        ".size func_8014C800, 636");
#define BODY_NAME func_8014C8A8
#define BODY_ATTR __attribute__((section(".text.func_8014C800")))
#else
#define BODY_NAME func_8014C800
#define BODY_ATTR
#endif

void *BODY_NAME(void *arg0, s32 arg1, s32 arg2, s32 arg3) BODY_ATTR;

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
    FIELD(created, void *, 0x10) = D_8014CA7C;
    FIELD(result, s8, 0x13) = 0x28;
    func_8004491C(created, &D_80045340);

    position = FIELD(created, void *, 8);
    FIELD(position, s16, 0xA) = saved_arg3;
    part_b = FIELD(created, void *, 0xC);
    kind = saved_arg0 & 3;
    FIELD(part_b, s8, 0x25) = saved_arg2;
    actor = result;
    FIELD(part_b, void *, 0x2C) = D_80150038;
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
                FIELD(part_b, void *, 0x2C) = D_80150088;
            }
        }
    }

setup:
    func_800A9C18(created, position, part_b,
        (s16)original_arg0);
    FIELD(actor, u8, 0x9A) = 0xFF;
    FIELD(actor, s8, 0x9C) = -1;
    FIELD(actor, void *, 0x8C) = D_8014CEA8;
    func_800AA36C(actor, position, part_b, result);

done:
    return result;
}
