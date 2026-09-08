#include "common.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_800814A8.h"

typedef struct S_80172DEC_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} S_80172DEC_0;   /* arg0 in func_80172DEC */

typedef struct S_80172DEC_1 {
    u8 pad_00[0x1C];
    u32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x18];
    void * unk_60;
    u8 pad_64[0x9];
    union { u8 s; s8 u; } unk_6D;   /* accessed as both */
    u8 pad_6E[0x4];
    union { u8 s; s8 u; } unk_72;   /* accessed as both */
    union { u8 s; s8 u; } unk_73;   /* accessed as both */
} S_80172DEC_1;   /* arg3 in func_80172DEC */

typedef struct S_80172DEC_2_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80172DEC_2_pre;   /* the 0x14 bytes before obj in func_80172DEC, addressed as obj[-1] */

typedef struct S_80172DEC_3 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80172DEC_3;   /* rec in func_80172DEC */




typedef struct S_80172DEC_7 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} S_80172DEC_7;   /* block in func_80172DEC */



typedef struct {
    u8 pad0[0x12];
    u8 kind;
    u8 pad13;
} MotionEntry;

extern s32 func_8003F270(void);
extern void func_80047784(void *, s32, s32);
extern void *func_800A05A4(void *, u8, u8, s16, s32);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern s32 func_800A94A0(void *, u8 *, s32, void *);
extern void func_800DB2DC(void *, void *, void *, s32);

extern u8 D_8006DE24[];
extern void *D_800814A8;
extern s16 D_80083228;
extern s32 D_80083460;
extern s32 D_8008346C;
extern u8 D_80170F6C[];
extern u8 D_80175258[];

void func_80172DEC(void *arg0, void *arg1, void *arg2, void *arg3)
{
    u16 pending[3];
    register u8 *sel ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register s32 special ASM_REG("$21");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    void *obj;
    register void *rec ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 x;
    s32 y;
    s32 counter;
    u8 *block;

    special = 0;
    switch (((S_80172DEC_0 *)arg0)->unk_9B) {
    case 0:
        if (((S_80172DEC_1 *)arg3)->unk_1C & 0x2000) {
            static void *const sw_keep[] = {&&sw_c, &&sw_b, &&sw_a, &&sel_none};
            extern void *const D_80170850[];
            u32 swi = (u32)((((S_80172DEC_1 *)arg3)->unk_46 & 0x3FFF) - 1);

            if (swi >= 7) {
                goto sel_none;
            }
            (void)sw_keep;
            goto *D_80170850[swi];
        sw_c:
            special = 1;
            goto kind_c;
        sw_b:
            special = 1;
            goto kind_b;
        sw_a:
            special = 1;
            goto kind_a;
        }

        switch (((S_80172DEC_1 *)arg3)->unk_46 & 0x3FFF) {
        case 3:
        kind_c:
            sel = (u8 *)arg3 + 0xE;
            break;
        case 2:
        kind_b:
            sel = (u8 *)arg3 + 0xB;
            break;
        case 1:
        kind_a:
            sel = (u8 *)arg3 + 8;
            break;
        default:
        sel_none:
            sel = (u8 *)0;
            break;
        }

        if (*sel != 0) {
            ((S_80172DEC_0 *)arg0)->unk_98 &= 0xFF7F;
            ASM_KEEP(sel);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
            {
                s32 flag = special;

                ASM_KEEP(flag);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                if (flag != 0) {
                    obj = D_800814A8;
                    ((S_80172DEC_1 *)arg3)->unk_60 = obj;
                    goto have_obj;
                }
            }
            if (((MotionEntry *)D_8006DE24)[*sel].kind == 2) {
                obj = ((S_80172DEC_1 *)arg3)->unk_60;
                if (obj == 0) {
                    goto do_step;
                }
            have_obj:
                rec = ((S_80172DEC_2_pre *)obj)[-1].unk_00;
                ((S_80172DEC_1 *)arg3)->unk_72.s = ((S_80172DEC_3 *)rec)->unk_24;
                ((S_80172DEC_1 *)arg3)->unk_73.s = ((S_80172DEC_3 *)rec)->unk_25;
                goto do_step;
            }
            ((S_80172DEC_1 *)arg3)->unk_60 =
                func_800A05A4(arg3, ((Rec_D_80082E80 *)arg2)->unk_24, ((Rec_D_80082E80 *)arg2)->unk_25,
                              ((S_80172DEC_1 *)arg3)->unk_2A, 0x10);
            ASM_KEEP(arg3);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
            x = ((S_80172DEC_1 *)arg3)->unk_72.u;
            y = ((S_80172DEC_1 *)arg3)->unk_73.u;
            if (x < 0) {
                x = -x;
            }
            if (y < 0) {
                y = -y;
            }
            ((S_80172DEC_1 *)arg3)->unk_72.s = x;
            ((S_80172DEC_1 *)arg3)->unk_73.s = y;
        do_step:
            pending[0] = ((Rec_D_800E3D7C *)arg1)->unk_00.at02_u16.v;
            pending[1] = ((Rec_D_800E3D7C *)arg1)->unk_04.at02_u16.v;
            pending[2] = ((Rec_D_800E3D7C *)arg1)->unk_08.at02_u16.v;
            if (func_800A94A0(arg3, sel, special, (u8 *)arg0 + 0x98) == 0) {
                return;
            }
            ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v &= 0xF7FF;
            func_800A56E0(0x703);
            func_800DB2DC(arg1, arg2, arg3, 0x10);
            ((S_80172DEC_0 *)arg0)->unk_9B = ((S_80172DEC_0 *)arg0)->unk_9B + 1;
            return;
        }

        ((Rec_D_800E3D7C *)arg1)->unk_14.as_s32 = 0;
        ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v = 0;
        ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 = 0;
        func_800A2B04(arg1, ((Rec_D_80082E80 *)arg2)->unk_24, ((Rec_D_80082E80 *)arg2)->unk_25);
        D_8008346C = 0;
        ((Rec_D_800814A8 *)D_800814A8)->unk_A6 = (*(u16 *)((u8 *)D_800814A8 + 0xA6)) - 1;
        func_800A4ACC(arg3);
        ((S_80172DEC_1 *)arg3)->unk_6D.s = ((S_80172DEC_1 *)arg3)->unk_6D.s - 1;
        ((S_80172DEC_0 *)arg0)->unk_8C = D_80170F6C;
        ((S_80172DEC_1 *)arg3)->unk_73.s = 0;
        ((S_80172DEC_1 *)arg3)->unk_72.s = 0;
        ((S_80172DEC_1 *)arg3)->unk_46 &= 0x7FFF;
        return;

    case 1:
        if (func_8003F270() != 0) {
            ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v |= 0x800;
            return;
        }
        ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v &= 0xF7FF;
        ((S_80172DEC_0 *)arg0)->unk_9B = ((S_80172DEC_0 *)arg0)->unk_9B + 1;
        /* fallthrough */
    case 2:
        if ((((Rec_D_80082E80 *)arg2)->unk_04.as_s8 == 3 && (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0x1000)) ||
            (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0xE000)) {
            ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v |= 0x800;
            ((S_80172DEC_0 *)arg0)->unk_96 = 0xE;
            ((S_80172DEC_0 *)arg0)->unk_98 |= 0x80;
        }
        counter = ((S_80172DEC_0 *)arg0)->unk_96 - 1;
        ((S_80172DEC_0 *)arg0)->unk_96 = counter;
        if ((s16)counter <= 0) {
            ((S_80172DEC_0 *)arg0)->unk_96 = 0;
            ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v &= 0xF7FF;
        }
        if ((((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0xE000) == 0) {
            return;
        }
        ((Rec_D_800E3D7C *)arg1)->unk_14.as_s32 = 0;
        ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v = 0;
        ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 = 0;
        func_800A2B04(arg1, ((Rec_D_80082E80 *)arg2)->unk_24, ((Rec_D_80082E80 *)arg2)->unk_25);
        {
            u8 *table = D_80175258;

            if (((Rec_D_80082E80 *)arg2)->unk_2C.as_pu8 != table) {
                (*(u8 * *)((u8 *)arg2 + 0x2C)) = table;
                func_80047784(arg2,
                    table[((D_80083228 + ((S_80172DEC_1 *)arg3)->unk_2A + 0x100) >> 9) & 7],
                    0);
            }
        }
        block = (u8 *)&D_80083460;
        if (((S_80172DEC_7 *)block)->unk_0C != 0) {
            return;
        }
        ((S_80172DEC_7 *)block)->unk_0A = ((S_80172DEC_7 *)block)->unk_0A - 1;
        ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v &= 0xF7FF;
        ((S_80172DEC_0 *)arg0)->unk_8C = D_80170F6C;
        func_800A4ACC(arg3);
        if (((S_80172DEC_1 *)arg3)->unk_6D.u > 0) {
            ((S_80172DEC_1 *)arg3)->unk_6D.s = ((S_80172DEC_1 *)arg3)->unk_6D.s - 1;
        }
        ((S_80172DEC_1 *)arg3)->unk_73.s = 0;
        ((S_80172DEC_1 *)arg3)->unk_72.s = 0;
        ((S_80172DEC_1 *)arg3)->unk_46 &= 0x7FFF;
        func_800A56E0(0xB4);
        break;
    }
}

/* MECHANISM: ROWBASE rebuild. Defined under the TRUE-space name func_80172DEC so
   every retail `j 0x8017xxxx` is INTRA-function control flow (goto / switch /
   case-fallthrough), not the prior run's phantom noreturn externs -- that alone
   lets gcc's delayed-branch pass fill the three table-arm `j` slots with
   `addiu $s5,1` (the prior wall at word 48). Two natural switches (state 0/1/2,
   kind 1/2/3) give gcc's balanced compare tree with the shared `li $a0,1`; the
   out-of-row table is the extern-table dispatch idiom (keepalive + goto
   *D_80170850[swi]) whose arms cross-jump into the kind-switch case bodies, and
   `sel_none` is BOTH the bounds-fail target and the switch default.
   Frame objects: plain (non-volatile) u16 pending[3] gives the three 0x18(sp)
   stores AND lets the last one fill the jal delay slot; ((MotionEntry *)
   D_8006DE24)[*sel].kind keeps retail's `lbu 0x12(reg)` instead of folding +18
   into the %lo; `block = &D_80083460` is the held base for +0xa/+0xc.
   Residue closers: sel/$16 + special/$21 pins fix the callee-saved priority
   permutation; ASM_KEEP(arg3) after the 0x60 store is a SCHEDULER FENCE that
   stops sched1 hoisting the 0x72/0x73 lb pair above the store (that hoist is
   what pushed x,y off $v0/$v1 and sank the store into the bgez delay slot);
   ASM_KEEP(sel) fences the 0x98 RMW from the `flag = special` copy so the copy
   stays after the `sh` in $v0 (retail's extra `move $v0,$s5`) instead of being
   hoisted and sunk into the earlier beqz delay slot; rec/$3 keeps obj in $v0. */
