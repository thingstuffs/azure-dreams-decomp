#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern s32 func_800A6D30(void);
extern void func_800A48F0(void *, s32, s32);
extern void func_800A9C18(void *, void *, void *, s16);
extern void func_800AA36C(void *, void *, void *, void *);

extern u8 D_80045340;
extern s32 D_80083498;
extern u8 D_80170A84[];
extern s32 D_80170E94;
extern u8 D_80175F10[];
extern u8 D_80175F28[];

void *func_801708BC(s16 arg0, s8 arg1, s8 arg2, s32 arg3)
{
    s32 kind;
    void *result;
    void *object;
    void *part0;
    void *part1;
    void *result_copy;

    result = 0;
    object = func_8003FD64(0x112, &D_80083498);
    if (object == 0) {
        goto done;
    }

    result = object;
    result = (u8 *)result + 0x20;
    FIELD(object, void *, 0x10) = D_80170A84;
    FIELD(result, s8, 0x13) = 44;
    func_8004491C(object, &D_80045340);

    {
        void *page;
        void *handler;

        page = (void *)0x80170000;
        ASM_KEEP_NV(page);
        do {
            part0 = FIELD(object, void *, 8);
        } while (0);
        handler = (u8 *)page + 0x5F10;
        FIELD(part0, s16, 0xA) = arg3;
        part1 = FIELD(object, void *, 0xC);
        kind = arg0 & 3;
        FIELD(part1, s8, 0x25) = arg2;
        result_copy = result;
        FIELD(part1, void *, 0x2C) = handler;
    }
    FIELD(part1, s8, 0x24) = arg1;

    if (kind == 1) {
        FIELD(result, s32, 0x14) |= 0x6000;
        FIELD(result, s32, 0x1C) |= 0x6000;
        goto common;
    }

    if (kind >= 2) {
        FIELD(result, s32, 0x14) |= 0x2000;
        FIELD(result, s32, 0x1C) |= 0x2000;
        goto common;
    }

    if (((arg0 & -4) << 16) != 0) {
        goto common;
    }
    if ((FIELD(result, s32, 0x14) & 0x200) != 0) {
        goto common;
    }
    if ((func_800A6D30() & 1) != 0) {
        func_800A48F0(result, 1, (func_800A6D30() & 0x3F) | 0x20);
        FIELD(part1, void *, 0x2C) = D_80175F28;
    }

common:
    func_800A9C18(object, part0, part1, arg0);
    FIELD(result_copy, u8, 0x9A) = 0xFF;
    FIELD(result_copy, s8, 0x9C) = -1;
    FIELD(result_copy, void *, 0x8C) = &D_80170E94;
    func_800AA36C(result_copy, part0, part1, result);

done:
    return result;
}

/* MECHANISM: arg3 in an ABI word reproduces the 0x38 frame and save order. The
   two-step `result = object; result = (u8 *)result + 0x20;` gives `result` the
   extra SET that wins it the first saved-register colour ($s0) -- retail's whole
   s0..s7 role assignment follows from that one allocation. The flag arms are
   ordinary `|=` statements; gcc cross-jumps their two trailing stores itself.
   The only remaining scaffold is the split 0x80170000 page base: gcc emits the
   address of D_80175F10 as one `la` macro, while retail splits %hi/%lo around
   `lw $s4,8($s1)`. ASM_KEEP_NV keeps the halves apart with no scheduling
   barrier and compiles away in the -DNON_MATCHING port build. */
