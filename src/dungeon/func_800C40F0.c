#include "common.h"

#define FLD(p, t, o) (*(t *)((u8 *)(p) + (o)))

extern void *D_80083498;
extern u8 D_80083160[];
extern u8 D_8006CCF8[];
extern s32 D_800E0334[];
extern u8 D_800C9AAC;
extern u8 D_800C9F34;
extern u8 D_80045340;

typedef struct {
    s32 f0;
    s32 f4;
    s16 f8;
    s8 fA;
} D80089430_t;
extern D80089430_t D_80089430;

extern void *func_8003FD64(s32 a0, void *a1);
extern u8 func_8009FB34(u8 a0, u8 a1);
extern void func_800A2B04(void *a0, u8 a1, u8 a2);
extern s16 func_800BCB04(u16 a0, u16 a1, s16 a2);
extern void func_8003DB94(void *a0, s32 a1, s32 a2);
extern void func_80099FDC(void *a0);
extern void func_800CB4C0(void *a0, s32 a1, s32 a2);
extern void func_8004491C(void *a0, void *a1);
extern void func_800A48F0(void *a0, s32 a1, s32 a2);

void *func_800C9850(u8 arg0, u8 arg1, u16 arg2) {
    register u16 arg2_s1 ASM_REG("$17") = arg2;   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    register u8 arg0_s4 ASM_REG("$20") = arg0;   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    register u8 arg1_s5 ASM_REG("$21") = arg1;   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    void *ent;  /* s3 */
    void *sub;  /* s2 = ent + 0x20, return value */
    void *ea;   /* s0 (ent->f8) */
    void *eb;   /* s1 (ent->fC) */
    u8 *base;   /* s0 (&D_80083160) */
    register void *tail ASM_REG("$16");  /* s0 (tail object stores) */
    register s32 idx ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register u8 *result_page ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register D80089430_t *result_base ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s32 result0 ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 result4 ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    register s32 result8 ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 flags;
    register void *call_ent ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    register s32 call_zero ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

    ASM_KEEP_NV(arg2_s1);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP_NV(arg0_s4);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP_NV(arg1_s5);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    sub = 0;
    ent = func_8003FD64(0x112, &D_80083498);
    if (ent != 0) {
        sub = (u8 *)ent + 0x20;
        FLD(ent, void *, 0x10) = &D_800C9AAC;
        FLD(sub, s8, 0x13) = 0x2f;
        ea = FLD(ent, void *, 8);
        FLD(ea, u16, 0xA) = arg2_s1;
        eb = FLD(ent, void *, 0xC);
        FLD(eb, u8, 0x24) = arg0_s4;
        FLD(eb, u8, 0x25) = arg1_s5;
        FLD(eb, u8, 0x26) = func_8009FB34(FLD(eb, u8, 0x24), FLD(eb, u8, 0x25));
        func_800A2B04(ea, FLD(eb, u8, 0x24), FLD(eb, u8, 0x25));
        FLD(sub, s16, 0x88) =
            func_800BCB04(FLD(ea, u16, 2), FLD(ea, u16, 6), (s16)(FLD(ea, u16, 0xA) - 0x20));
        FLD(eb, s16, 0x1E) = 0x1000;
        FLD(eb, s16, 0x1C) = 0x1000;
        FLD(eb, s32, 0xC) = 0x2c808080;
        FLD(sub, void *, 0xA4) = D_800E0334;
        FLD(eb, void *, 0x2C) = D_800E0334;
        base = D_80083160;
        idx = ((FLD(base, s16, 0xC8) + FLD(sub, s16, 0x2A) + 0x100) >> 7) & 0x1C;
        idx += (s32)FLD(sub, void *, 0xA4);
        func_8003DB94(eb, FLD((void *)idx, s32, 0), 0);
        func_80099FDC(ent);
#ifdef NON_MATCHING
        result_base = &D_80089430;
#else
        result_page = (u8 *)0x80090000;
        ASM_KEEP_NV(result_page);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        result_base = (D80089430_t *)(result_page - 0x6BD0);
#endif
        ASM_KEEP_NV(result_base);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        result0 = result_base->f0;
        result4 = result_base->f4;
        result8 = result_base->f8;
        FLD(ent, s32, 0x54) = result0;
        FLD(ent, s32, 0x58) = result4;
        FLD(ent, s16, 0x5C) = result8;
        {
            register s32 resultA ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            resultA = result_base->fA;
            FLD(ent, s8, 0x5E) = resultA;
        }
        FLD(sub, s32, 0x1C) |= 0x40000000;
        FLD(sub, s8, 0x71) = 0;
        idx = ((FLD(base, s16, 0xC8) + FLD(sub, s16, 0x2A) + 0x100) >> 9) & 7;
        tail = sub;
        {
            u32 rv;
            if (D_8006CCF8[idx] != 0) {
                rv = FLD(eb, u16, 0x14) | 1;
            } else {
                rv = FLD(eb, u16, 0x14) & 0xFFFE;
            }
            FLD(eb, u16, 0x14) = rv;
        }
        ASM_MEM_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        flags = 0x404040;
        call_ent = ent;
        call_zero = 0;
        ASM_KEEP4(flags, call_ent, call_zero, sub);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
        FLD(tail, u8, 0x9A) = 0xFF;
        FLD(tail, s8, 0x9C) = -1;
        FLD(tail, void *, 0x8C) = &D_800C9F34;
        FLD(tail, s16, 0xB6) = 0x10;
        FLD(sub, s32, 0x1C) |= 0x40000;
        FLD(tail, s16, 0x92) = -0x20;
        FLD(tail, s32, 0xAC) = flags;
        func_800CB4C0(call_ent, call_zero, flags);
        func_8004491C(ent, &D_80045340);
        func_800A48F0(sub, 0x1B, 0);
    }
    return sub;
}
