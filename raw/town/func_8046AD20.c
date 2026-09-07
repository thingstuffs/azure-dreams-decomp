#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

typedef struct {
    u8 value[8];
} LocalValues;

typedef s32 (*GetIndex)(s32);
typedef void (*UseValue)(s16, s32);
typedef void (*CallPair)(s32, s32);
typedef s16 *(*GetHalfword)(s32, s32);

extern s8 D_80016000[];
extern LocalValues D_80019164;
extern u8 *D_8001E950;
extern s8 D_8001F2D4[];

extern s32 func_8001E670(s32);
extern void func_8001BC98();

s32 func_8001BD20(s32 arg0, s32 arg1) {
    LocalValues local;
    void *page;
    register s32 hold0 ASM_REG("$16");
    register s32 hold1 ASM_REG("$17");

    hold0 = arg0;
    hold1 = arg1;
    local = D_80019164;
    if (func_8001E670(0xA3) != 0) {
        if (func_8001E670(0x408) == 0) {
            D_8001E950[1] = 1;
        } else {
            D_8001E950[1] = 2;
        }
    }

    if (D_8001E950[1] == 0) {
        hold1 = 0x80010000;
        page = (void *)hold1;
        FIELD(FIELD(FIELD(page, void *, 0x6000), void *, 0x20),
            UseValue, 0x2EC)(
            FIELD(local.value, s16,
                FIELD(FIELD(FIELD(page, void *, 0x6000), void *, 0x20),
                    GetIndex, 0x2D4)(0) * 2),
            0x100);

        FIELD(FIELD(FIELD(page, void *, 0x6000), void *, 0x20),
            CallPair, 0x2F8)(0x27, 0x200);

        FIELD(FIELD(FIELD(page, void *, 0x6000), void *, 0x1C),
            void *, 0x40) = D_8001F2D4;

        if (FIELD(FIELD(FIELD(page, void *, 0x6000), void *, 0x20),
                GetIndex, 0x2D4)(0) == 2) {
            *FIELD(FIELD(FIELD(page, void *, 0x6000), void *, 0x20),
                GetHalfword, 0x314)(0xC20, 0x4A0) = 0x25;

            *FIELD(FIELD(FIELD(page, void *, 0x6000), void *, 0x20),
                GetHalfword, 0x314)(0xD20, 0x4A0) = 0x25;
        }
        return 1;
    }

    ASM_KEEP(hold0);
    ASM_KEEP(hold1);
    func_8001BC98(hold0, hold1);
    return 0;
}

/* MECHANISM: An 8-byte byte-aligned local reproduces the lwl/lwr stack copy; guarded
   s0/s1 pins preserve the argument-to-constant/page live-range reuse. One-argument
   flag calls, nested short-lived field expressions, and late literal stores close the CFG. */
