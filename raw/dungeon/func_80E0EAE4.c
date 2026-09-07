#include "common.h"

typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern M2C_UNK func_80047784();
extern s16 func_800A0818();
extern s32 func_800A2B5C();
extern M2C_UNK func_800A4ACC();
extern M2C_UNK func_800C77D0();
extern M2C_UNK func_800C7930();
extern s16 D_80083228;
extern u16 D_80083462;
extern u8 D_801764A0[];

void func_801722E4(void *arg0, M2C_UNK arg1, void *arg2, void *arg3) {
    M2C_UNK sp18;
    void *temp_s3;
    void *temp_v0;
    u8 *temp_tbl;
    register s8 *page_8008 ASM_REG("$2");

    M2C_FIELD(arg3, u8 *, 0x71) =
        (u8)(M2C_FIELD(arg3, u8 *, 0x71) & 0x7F);
    if (!(D_80083462 & 0x2008)) {
        temp_s3 = (s8 *)arg3 - 0x20;
        if ((func_800A2B5C(arg3) << 0x10) == 0) {
            func_800C7930(temp_s3, arg1, 8, 0x300);
            if ((func_800A2B5C(arg3) << 0x10) == 0) {
                temp_v0 = M2C_FIELD(M2C_FIELD(arg3, void **, 0x60),
                                    void **, -0x14);
                M2C_FIELD(arg3, s16 *, 0x2A) = func_800A0818(
                    M2C_FIELD(arg2, u8 *, 0x24),
                    M2C_FIELD(arg2, u8 *, 0x25),
                    M2C_FIELD(temp_v0, u8 *, 0x24),
                    M2C_FIELD(temp_v0, u8 *, 0x25),
                    &sp18);
                temp_tbl = D_801764A0;
                M2C_FIELD(arg0, s8 *, 0x9A) = 0x17;
                ASM_SCHED_BARRIER();
                page_8008 = (s8 *)0x80080000;
                ASM_KEEP(page_8008);
                M2C_FIELD(arg0, s8 *, 0x9B) = 0;
                M2C_FIELD(arg0, s32 *, 0x8C) = 0;
                M2C_FIELD(arg2, u8 **, 0x2C) = temp_tbl;
                func_80047784(
                    arg2,
                    temp_tbl[((s32)(*(s16 *)(page_8008 + 0x3228) +
                                    M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) &
                             7],
                    0);
                func_800A4ACC(arg3);
                M2C_FIELD(arg3, u8 *, 0x6D) =
                    (u8)(M2C_FIELD(arg3, u8 *, 0x6D) - 1);
                M2C_FIELD(arg0, u16 *, 0x98) =
                    (u16)(M2C_FIELD(arg0, u16 *, 0x98) | 8);
                func_800C77D0(temp_s3, arg1, 8, 0x300);
            }
        }
    }
}

/* MECHANISM: Keep the natural 56-byte frame, sibling scalar stack local, and five
   saved value roles. Materialize the table base before the 0x9A store, then fence
   and pin the 0x8008 page in v0 after it; this produces retail's la/sb/lui order. */
