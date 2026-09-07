#include "common.h"

#define FIELD(p, type, offset) (*(type *)((u8 *)(p) + (offset)))

extern void *func_8003FD64();
extern void func_8004491C();
extern s32 func_800A6D30();
extern void func_800A48F0();
extern void func_800A9C18();
extern void func_800AA36C();

extern s32 D_80045340;
extern u8 D_80083498[];
extern u8 D_8016AA7C[];
extern u8 D_8016E038[];
extern u8 D_8016E088[];
extern u8 D_8016AEA8[];

#ifdef __mips__
extern void *func_8016A8A8(s16, s8, s8, s16);
extern void *func_8016B2B8(void);
extern void *func_8016B2E4(void);
extern void *func_8016B264(void);
extern void *func_8016B1F4(void);
extern void *func_8016B1E4(void);
extern void *func_8016B2A8(void);
extern void *func_8016CAC4(void);
extern void *func_8016CABC(void);
extern void *func_8016CAB4(void);
extern void *func_8016CACC(void);
extern void *func_8016CA74(void);
extern void *func_8016CA6C(void);
extern void *func_8016CA64(void);

static const u32 func_8016A800_prefix[42] __asm__("func_8016A800")
    __attribute__((section(".text.func_8016A800"), aligned(4))) = {
        (u32)func_8016A8A8,
        (u32)D_8016AA7C,
        (u32)func_8016B2B8,
        (u32)func_8016B2B8,
        (u32)func_8016B2B8,
        (u32)func_8016B2E4,
        (u32)func_8016B264,
        (u32)func_8016B264,
        (u32)func_8016B264,
        (u32)func_8016B1F4,
        (u32)func_8016B1E4,
        (u32)func_8016B2E4,
        (u32)func_8016B2E4,
        (u32)func_8016B2A8,
        (u32)func_8016CAC4,
        (u32)func_8016CABC,
        (u32)func_8016CAB4,
        (u32)func_8016CACC,
        (u32)func_8016CA74,
        (u32)func_8016CA6C,
        (u32)func_8016CA64,
        0x89824081,
        0x40819382,
        0x93829082,
        0x83829982,
        0x85828882,
        0x7C818482,
        0x90829582,
        0x00004481,
        0x92824081,
        0x96828582,
        0x81828582,
        0x85828C82,
        0x40818482,
        0x94828982,
        0x40819382,
        0x92829482,
        0x85829582,
        0x90824081,
        0x97828F82,
        0x92828582,
        0x00004481,
    };
__asm__(".globl func_8016A800\n"
        ".size func_8016A800, 636");
#define BODY_NAME func_8016A8A8
#else
#define BODY_NAME func_8016A800
#endif

void *BODY_NAME(s16 arg0, s8 arg1, s8 arg2, s16 arg3)
{
    s32 kind;
    register void *obj ASM_REG("$17");
    register void *part_a ASM_REG("$20");
    void *part_b;
    register void *work ASM_REG("$16");
    void *actor;
    register s32 left ASM_REG("$2");
    register s32 right ASM_REG("$3");
    register s8 saved_arg1 ASM_REG("$22");
    register s16 saved_arg3 ASM_REG("$18");
    register s8 saved_arg2 ASM_REG("$21");
    register s16 call_arg0 ASM_REG("$23");
    register void *call_a0 ASM_REG("$4");
    register void *call_a1 ASM_REG("$5");

    work = 0;
    saved_arg1 = arg1;
    saved_arg3 = arg3;
    saved_arg2 = arg2;
    obj = func_8003FD64(0x112, D_80083498);
    if (obj != 0) {
        call_arg0 = arg0;
        ASM_KEEP(call_arg0);
        work = (u8 *)obj + 0x20;
        FIELD(obj, void *, 0x10) = D_8016AA7C;
        FIELD(work, s8, 0x13) = 0x28;
        func_8004491C(obj, &D_80045340);

        part_a = FIELD(obj, void *, 8);
        FIELD(part_a, s16, 0xA) = saved_arg3;
        part_b = FIELD(obj, void *, 0xC);
        kind = arg0 & 3;
        FIELD(part_b, s8, 0x25) = saved_arg2;
        actor = work;
        FIELD(part_b, void *, 0x2C) = D_8016E038;
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
        if (((arg0 & ~3) << 16) != 0) {
            goto call_a1_setup;
        }
        call_a1 = part_a;
        if (FIELD(work, s32, 0x14) & 0x200) {
            goto call_a2_setup;
        }
        left = func_800A6D30(call_a0, call_a1);
        call_a0 = obj;
        if (!(left & 1)) {
            goto call_a1_setup;
        }
        FIELD(work, s32, 0x1C) |= 0x200;
        func_800A48F0(work, 1,
                      (func_800A6D30(obj) & 0x3F) | 0x20);
        FIELD(part_b, void *, 0x2C) = D_8016E088;
        goto post_kind;

post_kind:
        call_a0 = obj;
call_a1_setup:
        call_a1 = part_a;
call_a2_setup:
        func_800A9C18(call_a0, call_a1, part_b, call_arg0);
        FIELD(actor, u8, 0x9A) = 0xFF;
        FIELD(actor, s8, 0x9C) = -1;
        FIELD(actor, void *, 0x8C) = &D_8016AEA8;
        func_800AA36C(actor, part_a, part_b, work);
    }
    return work;
}
