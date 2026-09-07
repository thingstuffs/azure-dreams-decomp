#include "common.h"

#define FIELD(expr, type, offset) (*(type *)((s8 *)(expr) + (offset)))

extern void func_80025590(void) __attribute__((noreturn));
extern void *func_8003FC64();
extern s32 func_8004491C();
extern s32 rand();
extern s32 D_800250E8[3];
extern s32 D_800252E0[3];

s32 func_800254C4(void *arg0, s16 arg1, s16 arg2, s16 arg3) {
    register void *source = arg0;
    register s16 value1 ASM_REG("$20") = arg1;
    register s16 value2 ASM_REG("$21") = arg2;
    register s16 mode = arg3;
    register void *node;

    node = func_8003FC64(0x202);
    if (node != 0) {
        register s16 savedMode ASM_REG("$19") = mode;
        s32 modeTest;

        ASM_KEEP(savedMode);
        FIELD(node, s32 *, 0x10) = D_800250E8;
        func_8004491C(node, D_800252E0);
        modeTest = mode << 0x10;
        {
            register void *payload ASM_REG("$16") = FIELD(node, void *, 8);

            if (modeTest == 0) {
            FIELD(payload, u16, 2) =
                (u16)((FIELD(source, u16, 2) + (rand() & 0x1F)) - 0x10);
            FIELD(payload, u16, 6) =
                (u16)((FIELD(source, u16, 6) + (rand() & 0x1F)) - 0x10);
            {
                register s32 tailValue ASM_REG("$2") =
                    FIELD(source, u16, 0xA) - 0x50;

                ASM_TAILSLOT_PIN(tailValue);
                func_80025590();
            }
            }
            FIELD(payload, u16, 2) = FIELD(source, u16, 2);
            FIELD(payload, u16, 6) = FIELD(source, u16, 6);
            FIELD(payload, u16, 0xA) = FIELD(source, u16, 0xA);
        }
        FIELD(FIELD(node, void *, 0xC), u8, 0xC) = 0xF0;
        {
            void *fields = node + 0x20;

            FIELD(fields, s16, 0x1A) = value1;
            FIELD(fields, s16, 0x1C) = value2;
            FIELD(fields, s16, 0x26) = savedMode;
        }
    }
}

/* MECHANISM: Retail's six saved roles come from the pinned argument/payload lifetimes;
   keeping savedMode at the branch places move s3,s0 in its delay slot.
   A noreturn dispatcher plus a pinned $v0 tail value forms lhu;j;addiu, and the
   final color byte is unsigned so 0xF0 materializes as 240 rather than -16. */
