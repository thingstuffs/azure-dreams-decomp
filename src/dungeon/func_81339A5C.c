#include "common.h"

#ifndef NULL
#define NULL 0
#endif

#define FIELD(expr, type_ptr, offset) (*(type_ptr)((u8 *)(expr) + (offset)))

extern void *func_8003FD64();
extern void func_8004491C();
extern s32 D_80045340;
extern s32 D_8006E240;
extern s32 D_8017085C;
extern void *D_80175D50;
extern void *D_80175D68;

void func_80170A5C(void)
{
    u16 temp_a0_u;
    u16 temp_a1;
    u16 temp_v0_u;
    void *temp_s1;
    register void *temp_s2 ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    void *temp_s3;
    void *temp_v0;
    void *temp_v1;
    void *temp_v1_2;
    void *temp_v1_3;

    temp_s1 = FIELD(D_80175D50, void **, 8);
    temp_s3 = D_80175D50 + 0x20;
    temp_v0 = func_8003FD64(0x12, D_80175D50);
    if (temp_v0 != NULL) {
        FIELD(temp_v0, void **, 0x10) = &D_8017085C;
        func_8004491C(temp_v0, &D_80045340);
        temp_v1 = FIELD(temp_v0, void **, 0xC);
        temp_s2 = temp_v0 + 0x20;
        FIELD(temp_v1, u16 *, 0x14) =
            (u16)(FIELD(temp_v1, u16 *, 0x14) & 0xFFF3);
        FIELD(temp_s2, void **, 0x24) = temp_s3;
        temp_v1_2 = FIELD(temp_v0, void **, 8);
        FIELD(temp_v1_2, u16 *, 2) = FIELD(temp_s1, u16 *, 2);
        FIELD(temp_v1_2, u16 *, 6) = FIELD(temp_s1, u16 *, 6);
        FIELD(temp_v1_2, volatile u16 *, 0xA) =
            FIELD(temp_s1, volatile u16 *, 0xA);
        temp_a1 = FIELD(temp_s1, volatile u16 *, 0xA);
        temp_v0_u = FIELD(temp_v1_2, volatile u16 *, 6);
        temp_a0_u = FIELD(temp_v1_2, volatile u16 *, 0xA);
        FIELD(temp_v1_2, u16 *, 6) = (u16)(temp_v0_u - 0x140);
        FIELD(temp_v1_2, u16 *, 0x16) = temp_a1;
        FIELD(temp_v1_2, u16 *, 0xA) = (u16)(temp_a0_u - 0x20);
        temp_v1_3 = FIELD(temp_v0, void **, 0xC);
        FIELD(temp_v1_3, s16 *, 0x1E) = 0x1000;
        FIELD(temp_v1_3, s16 *, 0x1C) = 0x1000;
        FIELD(temp_v1_3, s16 *, 6) = 6;
        FIELD(temp_s2, s8 *, 0x58) =
            (FIELD(temp_s1, s16 *, 2) - 0x20) / 0x40;
        FIELD(temp_s2, s8 *, 0x59) =
            (FIELD(temp_s1, s16 *, 6) - 0x20) / 0x40;
        FIELD(temp_v1_3, u8 *, 0xE) = 0x80;
        FIELD(temp_v1_3, u8 *, 0xD) = 0x80;
        FIELD(temp_v1_3, u8 *, 0xC) = 0x80;
        FIELD(temp_v1_3, void **, 8) = &D_8006E240;
        D_80175D68 = temp_v0;
    }
}

/* MECHANISM: A guarded s2 object-base pin preserves the 40-byte ra/s3/s2/s1/s0 frame contract.
   Volatile halfword copy/read locals retain the retail reload and load-delay nop sequence.
   Direct signed /0x40 coordinate expressions coalesce each result into retail's v0 web. */
