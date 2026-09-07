#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern void *D_800E3DF0[];
extern u8 D_800E0B18[16];
extern u8 D_800E0B2B[16];
extern u8 D_800E202D[16];

extern s16 func_800A1BD0(void *arg0);
extern s32 func_800A1C14(void *arg0);
extern void *func_800990FC(void);
extern s32 func_80099194(void *arg0, s32 arg1);
extern void func_80095750(void *arg0, s32 arg1);
extern void func_80095774(void *arg0, s32 arg1);
extern void func_80095828(void);
extern void func_80095838(void);
extern void func_80099290(s32 arg0);
extern void func_800A5720(s32 arg0);
extern void func_800ACB98(void *arg0, s32 arg1, s32 arg2, void *arg3);

void func_800956B8(void *arg0, s32 arg1, void *arg2, void *arg3)
{
    void *object;
    s32 index;
    s32 tail_result;
    s16 result;
    register s32 value ASM_REG("$5");

    object = D_800E3DF0[FIELD(arg3, u8, 3) & 0x1F];
    if (!(FIELD(object, u32, 0x1C) & 0x20000)) {
        result = func_800A1BD0(object);
        arg0 = func_800990FC();
        if (result >= 0) {
            value = func_80099194(D_800E0B18, (s32)arg0);
            if (result != 0) {
                register u8 *page ASM_REG("$2");

                ASM_KEEP(value);
                page = (u8 *)0x800E0000;
                ASM_KEEP(page);
                func_80095750(page + 0x5F0, value);
                return;
            } else {
                register u8 *page ASM_REG("$2");
                u8 *msg;

                ASM_KEEP(value);
                page = (u8 *)0x800E0000;
                ASM_KEEP(page);
                msg = page + 0x5E1;
                ASM_USE(msg);
                tail_result = func_80099194(msg, value);
                func_80095774(D_800E0B2B, tail_result - 3);
                return;
            }
        } else {
            u8 *msg3 = D_800E202D;

            ASM_USE(msg3);
            value = (s32)arg0;
            ASM_USE2(msg3, value);
            value = func_80099194(msg3, value);
            ASM_KEEP(value);
            func_80099290(value);
        }
        func_800A5720((s32)arg0);
        func_80095838();
        return;
    }

    index = (s16)func_800A1C14(object);
    if (index >= 0) {
        object = FIELD((u8 *)arg0 + index * 4, void *, 0xAC);
        if (FIELD(object, u32, 0x14) & 0x20000000) {
            FIELD(object, u32, 0x1C) |= 0x10000;
            func_800ACB98(object, FIELD(object, s32, -0x18),
                         FIELD(object, s32, -0x14), object);
            func_80095838();
            return;
        }
    }

    index = func_800A1BD0(object);
    if (index >= 0) {
        register void *tail_selected ASM_REG("$3");
        register s32 tail_value ASM_REG("$2");

        tail_selected = FIELD((u8 *)arg0 + index * 4, void *, 0xAC);
        tail_value = 2;
        ASM_KEEP(tail_selected);
        ASM_TAILSLOT_PIN(tail_value);
        func_80095828();
        return;
    }

    {
        register void *st ASM_REG("$3");
        register s32 two ASM_REG("$2");

        st = FIELD(arg0, void *, 0x60);
        two = 2;
        FIELD(st, u8, 0x9A) = two;
        FIELD(st, u8, 0x9B) = 0;
        FIELD(st, s32, 0x8C) = 0;
        FIELD(arg0, void *, 0x110) = arg3;
    }
}

/* MECHANISM: frame is 4 saves (s2,ra,s1,s0 at 0x18/0x1c/0x14/0x10) with arg3->s2
   and arg0->s1; the two message tails take their string address from a $v0-pinned
   page base ((u8*)0x800E0000 + 0x5F0/0x5E1, ASM_KEEP'd) so gcc splits HIGH/LO_SUM
   across two registers instead of coalescing lui+addiu into $a0.  Retail leaves
   both func_80099194 call delay slots EMPTY: the fix is to materialise every arg
   BEFORE a zero-def ASM_USE/ASM_USE2 liveness barrier (a1 pre-set into the $a1-pinned
   `value`), which fences gcc's dbr out of the slot; ASM_USE(msg3) first forces the
   $a0 la ahead of the $a1 move.  The L9 tail wants the loaded state pointer in $v1
   and the literal 2 in $v0 -- plain ASM_REG pins with NO ASM_KEEP (the keep's extra
   DEF reorders the sb/sw group and costs a load-delay nop). */
