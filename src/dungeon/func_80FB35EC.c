#include "common.h"
#include "shared/def_table.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"
extern int abs(int);

typedef struct S_80172DEC_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} S_80172DEC_0;   /* arg0 in func_80172DEC */

typedef struct S_80172DEC_2_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80172DEC_2_pre;   /* the 0x14 bytes before obj in func_80172DEC, addressed as obj[-1] */

typedef struct S_80172DEC_3 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80172DEC_3;   /* rec in func_80172DEC */







extern s32 func_8003F270(void);
extern void func_80047784(void *, s32, s32);
extern void *func_800A05A4(void *, u8, u8, s16, s32);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern s32 func_800A94A0(void *, u8 *, s32, void *);
extern void func_800DB2DC(void *, void *, void *, s32);

extern u8 D_80170F6C[];
extern u8 D_80175258[];

/* Advances an actor action through motion selection, execution, and recovery. */
void func_80172DEC(void *action_state, EntityRec *transform, void *sprite, EntityRec *actor)
{
    u16 saved_position[3];
    register u8 *motion ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s32 use_global_target;
    void *target;
    s32 target_x;
    s32 abs_x;
    s32 abs_y;
    s32 target_y;
    s32 ticks_left;

    use_global_target = 0;
    switch (((S_80172DEC_0 *)action_state)->unk_9B) {
    case 0:
        if (((u32)actor->flags1C) & 0x2000) {
            static void *const dispatch_labels[] = {&&sw_c, &&sw_b, &&sw_a, &&sel_none};
            extern void *const D_80170850[];
            u32 kind_index = (u32)((actor->unk_46 & 0x3FFF) - 1);

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

        switch (actor->unk_46 & 0x3FFF) {
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
            {
                s16 global_target_flag = use_global_target;

                if (global_target_flag != 0) {
                    target = D_800814A8;
                    actor->target = target;
                    target_y = ((S_80172DEC_2_pre *)target)[-1].unk_00;
                    actor->unk_72 = ((S_80172DEC_3 *)target_y)->unk_24;
                    actor->unk_73 = ((S_80172DEC_3 *)target_y)->unk_25;
                    goto do_step;
                }
            }
            if (D_8006DE24[*motion].kind == 2) {
                target = actor->target;
                if (target == 0) {
                    goto do_step;
                }
            have_obj:
                target_y = ((S_80172DEC_2_pre *)target)[-1].unk_00;
                actor->unk_72 = ((S_80172DEC_3 *)target_y)->unk_24;
                actor->unk_73 = ((S_80172DEC_3 *)target_y)->unk_25;
                goto do_step;
            }
            actor->target =
                func_800A05A4(actor, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25,
                              actor->facing, 0x10);
            abs_x = abs(actor->unk_72);
            abs_y = abs(actor->unk_73);
            actor->unk_72 = abs_x;
            actor->unk_73 = abs_y;
        do_step:
            saved_position[0] = ((u16)transform->x.w.i);
            saved_position[1] = ((u16)transform->y.w.i);
            saved_position[2] = ((u16)transform->z.w.i);
            if (func_800A94A0(actor, motion, use_global_target, (u8 *)action_state + 0x98) == 0) {
                return;
            }
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v &= 0xF7FF;
            func_800A56E0(0x703);
            func_800DB2DC(transform, sprite, actor, 0x10);
            ((S_80172DEC_0 *)action_state)->unk_9B = ((S_80172DEC_0 *)action_state)->unk_9B + 1;
            return;
        }

        transform->flags14 = 0;
        transform->unk_10 = 0;
        transform->unk_0C = 0;
        func_800A2B04(transform, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
        dungeonStatus.unk_0C = 0;
        (*(u16 *)((u8 *)&D_800814A8->unk_A4 + 2)) = (*(u16 *)((u8 *)D_800814A8 + 0xA6)) - 1;
        func_800A4ACC(actor);
        actor->unk_6D = ((u8)actor->unk_6D) - 1;
        ((S_80172DEC_0 *)action_state)->unk_8C = D_80170F6C;
        actor->unk_73 = 0;
        actor->unk_72 = 0;
        actor->unk_46 &= 0x7FFF;
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
        transform->flags14 = 0;
        transform->unk_10 = 0;
        transform->unk_0C = 0;
        func_800A2B04(transform, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
        {
            u8 *direction_table = D_80175258;

            if (((Rec_D_80082E80 *)sprite)->unk_2C.as_pu8 != direction_table) {
                (*(u8 * *)((u8 *)sprite + 0x2C)) = direction_table;
                func_80047784(sprite,
                    direction_table[((gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
                    0);
            }
        }
        if (((s32)dungeonStatus.unk_0C) != 0) {
            return;
        }
        dungeonStatus.unk_0A = ((u16)dungeonStatus.unk_0A) - 1;
        ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v &= 0xF7FF;
        ((S_80172DEC_0 *)action_state)->unk_8C = D_80170F6C;
        func_800A4ACC(actor);
        if (actor->unk_6D > 0) {
            actor->unk_6D = ((u8)actor->unk_6D) - 1;
        }
        actor->unk_73 = 0;
        actor->unk_72 = 0;
        actor->unk_46 &= 0x7FFF;
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
