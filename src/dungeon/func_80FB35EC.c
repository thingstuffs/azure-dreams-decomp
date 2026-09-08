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

/* Advances an actor action through motion selection, execution, and recovery. */
void func_80172DEC(void *action_state, void *transform, void *sprite, void *actor)
{
    u16 saved_position[3];
    register u8 *motion ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register s32 use_global_target ASM_REG("$21");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    void *target;
    register void *target_record ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 target_x;
    s32 target_y;
    s32 ticks_left;
    u8 *action_status;

    use_global_target = 0;
    switch (((S_80172DEC_0 *)action_state)->unk_9B) {
    case 0:
        if (((S_80172DEC_1 *)actor)->unk_1C & 0x2000) {
            static void *const dispatch_labels[] = {&&sw_c, &&sw_b, &&sw_a, &&sel_none};
            extern void *const D_80170850[];
            u32 kind_index = (u32)((((S_80172DEC_1 *)actor)->unk_46 & 0x3FFF) - 1);

            if (kind_index >= 7) {
                goto sel_none;
            }
            (void)dispatch_labels;
            goto *D_80170850[kind_index];
        sw_c:
            use_global_target = 1;
            goto kind_c;
        sw_b:
            use_global_target = 1;
            goto kind_b;
        sw_a:
            use_global_target = 1;
            goto kind_a;
        }

        switch (((S_80172DEC_1 *)actor)->unk_46 & 0x3FFF) {
        case 3:
        kind_c:
            motion = (u8 *)actor + 0xE;
            break;
        case 2:
        kind_b:
            motion = (u8 *)actor + 0xB;
            break;
        case 1:
        kind_a:
            motion = (u8 *)actor + 8;
            break;
        default:
        sel_none:
            motion = (u8 *)0;
            break;
        }

        if (*motion != 0) {
            ((S_80172DEC_0 *)action_state)->unk_98 &= 0xFF7F;
            ASM_KEEP(motion);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
            {
                s32 global_target_flag = use_global_target;

                ASM_KEEP(global_target_flag);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                if (global_target_flag != 0) {
                    target = D_800814A8;
                    ((S_80172DEC_1 *)actor)->unk_60 = target;
                    goto have_obj;
                }
            }
            if (((MotionEntry *)D_8006DE24)[*motion].kind == 2) {
                target = ((S_80172DEC_1 *)actor)->unk_60;
                if (target == 0) {
                    goto do_step;
                }
            have_obj:
                target_record = ((S_80172DEC_2_pre *)target)[-1].unk_00;
                ((S_80172DEC_1 *)actor)->unk_72.s = ((S_80172DEC_3 *)target_record)->unk_24;
                ((S_80172DEC_1 *)actor)->unk_73.s = ((S_80172DEC_3 *)target_record)->unk_25;
                goto do_step;
            }
            ((S_80172DEC_1 *)actor)->unk_60 =
                func_800A05A4(actor, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25,
                              ((S_80172DEC_1 *)actor)->unk_2A, 0x10);
            ASM_KEEP(actor);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
            target_x = ((S_80172DEC_1 *)actor)->unk_72.u;
            target_y = ((S_80172DEC_1 *)actor)->unk_73.u;
            if (target_x < 0) {
                target_x = -target_x;
            }
            if (target_y < 0) {
                target_y = -target_y;
            }
            ((S_80172DEC_1 *)actor)->unk_72.s = target_x;
            ((S_80172DEC_1 *)actor)->unk_73.s = target_y;
        do_step:
            saved_position[0] = ((Rec_D_800E3D7C *)transform)->unk_00.at02_u16.v;
            saved_position[1] = ((Rec_D_800E3D7C *)transform)->unk_04.at02_u16.v;
            saved_position[2] = ((Rec_D_800E3D7C *)transform)->unk_08.at02_u16.v;
            if (func_800A94A0(actor, motion, use_global_target, (u8 *)action_state + 0x98) == 0) {
                return;
            }
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v &= 0xF7FF;
            func_800A56E0(0x703);
            func_800DB2DC(transform, sprite, actor, 0x10);
            ((S_80172DEC_0 *)action_state)->unk_9B = ((S_80172DEC_0 *)action_state)->unk_9B + 1;
            return;
        }

        ((Rec_D_800E3D7C *)transform)->unk_14.as_s32 = 0;
        ((Rec_D_800E3D7C *)transform)->unk_10.at00_s32.v = 0;
        ((Rec_D_800E3D7C *)transform)->unk_0C.as_s32 = 0;
        func_800A2B04(transform, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
        D_8008346C = 0;
        ((Rec_D_800814A8 *)D_800814A8)->unk_A6 = (*(u16 *)((u8 *)D_800814A8 + 0xA6)) - 1;
        func_800A4ACC(actor);
        ((S_80172DEC_1 *)actor)->unk_6D.s = ((S_80172DEC_1 *)actor)->unk_6D.s - 1;
        ((S_80172DEC_0 *)action_state)->unk_8C = D_80170F6C;
        ((S_80172DEC_1 *)actor)->unk_73.s = 0;
        ((S_80172DEC_1 *)actor)->unk_72.s = 0;
        ((S_80172DEC_1 *)actor)->unk_46 &= 0x7FFF;
        return;

    case 1:
        if (func_8003F270() != 0) {
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 0x800;
            return;
        }
        ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v &= 0xF7FF;
        ((S_80172DEC_0 *)action_state)->unk_9B = ((S_80172DEC_0 *)action_state)->unk_9B + 1;
        /* fallthrough */
    case 2:
        if ((((Rec_D_80082E80 *)sprite)->unk_04.as_s8 == 3 && (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x1000)) ||
            (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 0x800;
            ((S_80172DEC_0 *)action_state)->unk_96 = 0xE;
            ((S_80172DEC_0 *)action_state)->unk_98 |= 0x80;
        }
        ticks_left = ((S_80172DEC_0 *)action_state)->unk_96 - 1;
        ((S_80172DEC_0 *)action_state)->unk_96 = ticks_left;
        if ((s16)ticks_left <= 0) {
            ((S_80172DEC_0 *)action_state)->unk_96 = 0;
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v &= 0xF7FF;
        }
        if ((((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000) == 0) {
            return;
        }
        ((Rec_D_800E3D7C *)transform)->unk_14.as_s32 = 0;
        ((Rec_D_800E3D7C *)transform)->unk_10.at00_s32.v = 0;
        ((Rec_D_800E3D7C *)transform)->unk_0C.as_s32 = 0;
        func_800A2B04(transform, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
        {
            u8 *direction_table = D_80175258;

            if (((Rec_D_80082E80 *)sprite)->unk_2C.as_pu8 != direction_table) {
                (*(u8 * *)((u8 *)sprite + 0x2C)) = direction_table;
                func_80047784(sprite,
                    direction_table[((D_80083228 + ((S_80172DEC_1 *)actor)->unk_2A + 0x100) >> 9) & 7],
                    0);
            }
        }
        action_status = (u8 *)&D_80083460;
        if (((S_80172DEC_7 *)action_status)->unk_0C != 0) {
            return;
        }
        ((S_80172DEC_7 *)action_status)->unk_0A = ((S_80172DEC_7 *)action_status)->unk_0A - 1;
        ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v &= 0xF7FF;
        ((S_80172DEC_0 *)action_state)->unk_8C = D_80170F6C;
        func_800A4ACC(actor);
        if (((S_80172DEC_1 *)actor)->unk_6D.u > 0) {
            ((S_80172DEC_1 *)actor)->unk_6D.s = ((S_80172DEC_1 *)actor)->unk_6D.s - 1;
        }
        ((S_80172DEC_1 *)actor)->unk_73.s = 0;
        ((S_80172DEC_1 *)actor)->unk_72.s = 0;
        ((S_80172DEC_1 *)actor)->unk_46 &= 0x7FFF;
        func_800A56E0(0xB4);
        break;
    }
}

/* MECHANISM: ROWBASE rebuild. Defined under the TRUE-space name func_80172DEC so
   every retail `j 0x8017xxxx` is INTRA-function control flow (goto / switch /
   case-fallthrough), not the prior run's phantom noreturn externs -- that alone
   lets gcc's delayed-branch pass fill the three direction_table-arm `j` slots with
   `addiu $s5,1` (the prior wall at word 48). Two natural switches (state 0/1/2,
   kind 1/2/3) give gcc's balanced compare tree with the shared `li $a0,1`; the
   out-of-row direction_table is the extern-direction_table dispatch idiom (keepalive + goto
   *D_80170850[kind_index]) whose arms cross-jump into the kind-switch case bodies, and
   `sel_none` is BOTH the bounds-fail target and the switch default.
   Frame objects: plain (non-volatile) u16 saved_position[3] gives the three 0x18(sp)
   stores AND lets the last one fill the jal delay slot; ((MotionEntry *)
   D_8006DE24)[*motion].kind keeps retail's `lbu 0x12(reg)` instead of folding +18
   into the %lo; `action_status = &D_80083460` is the held base for +0xa/+0xc.
   Residue closers: motion/$16 + use_global_target/$21 pins fix the callee-saved priority
   permutation; ASM_KEEP(actor) after the 0x60 store is a SCHEDULER FENCE that
   stops sched1 hoisting the 0x72/0x73 lb pair above the store (that hoist is
   what pushed target_x,target_y off $v0/$v1 and sank the store into the bgez delay slot);
   ASM_KEEP(motion) fences the 0x98 RMW from the `global_target_flag = use_global_target` copy so the copy
   stays after the `sh` in $v0 (retail's extra `move $v0,$s5`) instead of being
   hoisted and sunk into the earlier beqz delay slot; target_record/$3 keeps target in $v0. */
