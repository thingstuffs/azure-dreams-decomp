#include "common.h"

#ifndef NULL
#define NULL 0
#endif

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern s32 func_800A6D30(void);
extern void func_800A48F0(void *, s32, s32);
extern void func_800A9C18(void *, void *, void *, s16);
extern void func_800AA36C(void *, void *, void *, void *);

extern u8 D_80045340[];
extern u8 D_80083498[];
extern u8 D_8016AA58[];
extern u8 D_8016AE5C[];
extern u8 D_8016E510[];
extern u8 D_8016E538[];

void *func_8016A800(s32, s32, s32, s32);

#ifdef __mips__
extern void func_8016B2A0(void);
extern void func_8016B2CC(void);
extern void func_8016B24C(void);
extern void func_8016B198(void);
extern void func_8016B1D0(void);
extern void func_8016B290(void);
extern void func_8016CB74(void);
extern void func_8016CB6C(void);
extern void func_8016CB64(void);
extern void func_8016CB7C(void);
extern void func_8016CB24(void);
extern void func_8016CB1C(void);
extern void func_8016CB14(void);

static void (*const func_8016A800_table[])(void)
    __attribute__((section(".text.func_8016A800"))) = {
        (void (*)(void))func_8016A800,
        0,
        func_8016B2A0,
        func_8016B2A0,
        func_8016B2A0,
        func_8016B2CC,
        func_8016B24C,
        func_8016B24C,
        func_8016B24C,
        func_8016B198,
        func_8016B1D0,
        func_8016B2CC,
        func_8016B2CC,
        func_8016B290,
        func_8016CB74,
        func_8016CB6C,
        func_8016CB64,
        func_8016CB7C,
        func_8016CB24,
        func_8016CB1C,
        func_8016CB14,
    };
#endif

void *func_8016A800(s32 arg0, s32 arg1, s32 arg2, s32 arg3)
{
    register void *result ASM_REG("$16") = NULL;
    register s32 arg1_role ASM_REG("$21");
    register void *root ASM_REG("$19");
    register void *position ASM_REG("$22");
    register s32 saved_arg0 ASM_REG("$23");
    register s32 opcode ASM_REG("$4");
    register void *factory ASM_REG("$5");
    s32 kind;

    {
    register void *arg3_part ASM_REG("$17");
    register void *arg2_work ASM_REG("$20");

    opcode = 0x112;
    arg1_role = arg1;
    factory = D_80083498;
    arg3_part = (void *)arg3;
    arg2_work = (void *)arg2;
    ASM_KEEP_DEP_NV(arg1_role, opcode);
    ASM_KEEP_DEP_NV(factory, arg1_role);
    ASM_KEEP_DEP_NV(arg3_part, factory);
    ASM_KEEP_DEP_NV(arg2_work, arg3_part);
    root = func_8003FD64(opcode, factory);
    if (root != NULL) {
        saved_arg0 = arg0;
        ASM_USE_NV(saved_arg0);
        result = (u8 *)root + 0x20;
        FIELD(result, s8, 0x13) = 0x1C;
        func_8004491C(root, D_80045340);

        position = FIELD(root, void *, 8);
        kind = arg0 & 3;
        FIELD(position, s16, 0xA) = (s16)(s32)arg3_part;
        arg3_part = FIELD(root, void *, 0xC);
        FIELD(arg3_part, s8, 0x25) = (s8)(s32)arg2_work;
        arg2_work = result;
        FIELD(arg3_part, s8, 0x24) = (s8)arg1_role;

        if (kind == 1) {
            FIELD(result, void *, 0x8C) = D_8016AE5C;
            FIELD(result, u32, 0x14) |= 0x6000;
            FIELD(result, u32, 0x1C) |= 0x6000;
            FIELD(arg3_part, void *, 0x2C) = D_8016E510;
            goto after_state;
        }
        if (kind >= 2) {
            FIELD(result, void *, 0x8C) = D_8016AE5C;
            FIELD(result, u32, 0x14) |= 0x2000;
            FIELD(result, u32, 0x1C) |= 0x2000;
            FIELD(arg3_part, void *, 0x2C) = D_8016E510;
            goto after_state;
        }

        if ((s16)(arg0 & ~3) == 0) {
            if (!(FIELD(result, u32, 0x14) & 0x200) &&
                    (func_800A6D30() & 1)) {
                func_800A48F0(result, 1, (func_800A6D30() & 0x3F) | 0x20);
                FIELD(arg3_part, void *, 0x2C) = D_8016E538;
            }
            FIELD((void *)arg2_work, void *, 0x8C) = D_8016AE5C;
        } else {
            FIELD(result, void *, 0x8C) = D_8016AE5C;
        }

        ASM_KEEP(arg0);
        FIELD(arg3_part, void *, 0x2C) = D_8016E510;
after_state:
        FIELD(root, void *, 0x10) = D_8016AA58;
        func_800A9C18(root, position, arg3_part, (s16)saved_arg0);
        FIELD((void *)arg2_work, u8, 0x9A) = 0xFF;
        FIELD((void *)arg2_work, s8, 0x9C) = -1;
        func_800AA36C(arg2_work, position, arg3_part, result);
    }
    }
    ASM_KEEP(result);
    return result;
}
