#include "common.h"
#include "records/Rec_D_800E3D7C.h"


extern s32 func_8003F270(void);
extern void func_80047784(void *, s32, s32);
extern void *func_800A05A4(void *, u8, u8, s16, s32);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern s32 func_800A94A0(void *, u8 *, s32, void *);
extern void func_80170A44(void *, void *, void *, void *);

extern u8 D_8006DE24[];
extern void *D_800814A8;
extern s16 D_80083228;
extern s32 D_80083460;
extern s32 D_8008346C;
extern void *D_80170850[];
extern void *D_801708B0[];
extern s32 D_801714D4[];
extern u8 D_801740E0[];
extern u8 D_80174110[];
extern u8 D_80174118[];


typedef struct S_80172A48_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x2];
    s16 unk_92;
    u8 pad_94[0x2];
    union { u16 u; s16 s; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x2];
    u16 unk_9E;
    u8 pad_A0[0x2];
    s16 unk_A2;
} S_80172A48_0;   /* arg0 in func_80172A48 */

typedef struct S_80172A48_1_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80172A48_1_pre;   /* the 0x14 bytes before active in func_80172A48, addressed as active[-1] */

typedef struct S_80172A48_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80172A48_2;   /* linked in func_80172A48 */

typedef struct S_80172A48_3 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_80172A48_3;   /* arg2 in func_80172A48 */


typedef struct S_80172A48_5 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} S_80172A48_5;   /* global in func_80172A48 */

/* Advance item use through effect activation, actor animation, and cleanup. */
void func_80172A48(void *action_in, void *motion_in, void *actor_in, void *item_in)
{
    register void *action ASM_REG("$16") = action_in;   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    void *motion = motion_in;
    register void *actor ASM_REG("$19") = actor_in; /* MATCH: retain the actor register across the shared model tail. */
    register void *item ASM_REG("$18") = item_in; /* MATCH: retain the item register across the shared model tail. */
    static void *volatile state_labels[] = {
        &&state_0, &&state_1, &&state_2, &&state_3,
        &&state_4, &&state_5, &&state_6, &&state_7,
        &&state_8, &&end, &&end, &&end,
        &&end, &&end, &&end, &&end,
        &&state_16, &&state_17, &&state_18, &&state_19,
        &&state_20, &&state_21, &&state_22, &&state_23
    };
    static void *const kind_labels[] = {
        &&kind_1, &&kind_2, &&kind_3, &&kind_default,
        &&kind_7, &&kind_6, &&kind_5
    };
    register u8 *effect_slot;
    s32 is_special;
    s32 effect_special;
    s32 next_state;
    u8 state;
    void *target;
    register u8 *model_base ASM_REG("$5"); /* MATCH: shared model setup materializes its pointer in a1. */

    ASM_KEEP(action);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */

    is_special = 0;
    state = ((S_80172A48_0 *)action)->unk_9B;
    if ((u32)state >= 24) {
        goto end;
    }
    (void)state_labels;
    goto *D_80170850[state];

state_0:
    if ((*(u32 *)((u8 *)item + 0x1C)) & 0x2000) {
        u32 kind_index;

        kind_index = ((*(u16 *)((u8 *)item + 0x46)) & 0x3FFF) - 1;
        if (kind_index >= 7) {
            goto kind_default;
        }
        (void)kind_labels;
        goto *D_801708B0[kind_index];

kind_5:
        is_special = 1;
        goto kind_3;
kind_6:
        is_special = 1;
        goto kind_2;
kind_7:
        is_special = 1;
        goto kind_1;
    }

    {
        s32 item_kind;

        item_kind = (*(u16 *)((u8 *)item + 0x46)) & 0x3FFF;
        if (item_kind == 2) {
            goto kind_2;
        }
        if (item_kind < 3) {
            effect_slot = 0;
            if (item_kind == 1) {
                goto normal_kind_1;
            }
            goto selection_ready;
        }
        if (item_kind != 3) {
            effect_slot = 0;
            goto selection_ready;
        }
    }

kind_3:
    effect_slot = (u8 *)item + 0xE;
    goto selection_ready;
kind_2:
    effect_slot = (u8 *)item + 0xB;
    goto selection_ready;
normal_kind_1:
kind_1:
    effect_slot = (u8 *)item + 8;
    goto selection_ready;
kind_default:
    effect_slot = 0;

selection_ready:
    if (*effect_slot == 0) {
        goto empty_selection;
    }
    ((S_80172A48_0 *)action)->unk_98 &= 0xFF7F;
    {
        s32 special_target;

        special_target = is_special;
        ASM_KEEP(special_target);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        if (special_target != 0) {
            target = D_800814A8;
            (*(void * *)((u8 *)item + 0x60)) = target;
            goto copy_active_coords;
        }
    }

    {
        u8 effect_id;

        effect_id = *effect_slot;
        if (D_8006DE24[effect_id * 20 + 0x12] == 2) {
            target = (*(void * *)((u8 *)item + 0x60));
            if (target != 0) {
                register u8 *target_actor ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

copy_active_coords:
                target_actor = ((S_80172A48_1_pre *)target)[-1].unk_00;
                (*(u8 *)((u8 *)item + 0x72)) = ((S_80172A48_2 *)target_actor)->unk_24;
                (*(u8 *)((u8 *)item + 0x73)) = ((S_80172A48_2 *)target_actor)->unk_25;
                goto invoke_item;
            }
        } else {
            s32 dx;
            s32 dy;

            target = func_800A05A4(
                item, ((S_80172A48_3 *)actor)->unk_24, ((S_80172A48_3 *)actor)->unk_25,
                (*(s16 *)((u8 *)item + 0x2A)), 0x10);
            (*(void * volatile *)((u8 *)item + 0x60)) = target;
            ASM_KEEP(target);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
            dx = (*(s8 *)((u8 *)item + 0x72));
            dy = (*(s8 *)((u8 *)item + 0x73));
            if (dx < 0) {
                dx = -dx;
            }
            if (dy < 0) {
                dy = -dy;
            }
            (*(u8 *)((u8 *)item + 0x72)) = dx;
            (*(u8 *)((u8 *)item + 0x73)) = dy;
        }
    }

invoke_item:
    effect_special = is_special;
    ASM_KEEP_NV(effect_special);   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
    if (func_800A94A0(item, effect_slot, effect_special, (u8 *)action + 0x98) == 0) {
        goto end;
    }
    ((S_80172A48_0 *)action)->unk_96.u = 0;
    ((S_80172A48_0 *)action)->unk_9B++;
    ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 = 0;
    ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = 0;
    ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = 0;
    if ((u32)(*effect_slot - 0x2E) >= 3) {
        goto end;
    }
    if (effect_special == 1) {
        goto end;
    }
    ((S_80172A48_0 *)action)->unk_9B = 0x10;
    return;

empty_selection:
    ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 = 0;
    ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = 0;
    ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = 0;
    func_800A2B04(motion, ((S_80172A48_3 *)actor)->unk_24, ((S_80172A48_3 *)actor)->unk_25);
    D_8008346C = 0;
    (*(u16 *)((u8 *)D_800814A8 + 0xA6))--;
    func_800A4ACC(item);
    (*(u8 *)((u8 *)item + 0x6D))--;
    ((S_80172A48_0 *)action)->unk_8C = D_801714D4;
    (*(u8 *)((u8 *)item + 0x73)) = 0;
    (*(u8 *)((u8 *)item + 0x72)) = 0;
    (*(u16 *)((u8 *)item + 0x46)) &= 0x7FFF;
    return;

state_1:
    if (func_8003F270()) {
        goto set_actor_flag;
    }
    ((S_80172A48_3 *)actor)->unk_14 &= 0xF7FF;
    ((S_80172A48_0 *)action)->unk_9B++;

state_2:
    {
        s16 timer;

        timer = ((S_80172A48_0 *)action)->unk_96.u;
        ((S_80172A48_0 *)action)->unk_96.u = timer + 1;
        if ((s16)timer < 8) {
            if (!(((S_80172A48_3 *)actor)->unk_14 & 0x8000)) {
                goto end;
            }
        }
    }
    next_state = ((S_80172A48_0 *)action)->unk_9B;
    ((S_80172A48_0 *)action)->unk_96.u = 0;
    ASM_KEEP(next_state); /* MATCH: keep each state load distinct before its delay-slot increment. */
    next_state++;
    goto store_next_state;

state_3:
    if (((S_80172A48_0 *)action)->unk_A2 != 0) {
        s16 timer;

        timer = ((S_80172A48_0 *)action)->unk_96.u;
        ((S_80172A48_0 *)action)->unk_96.u = timer + 1;
        if ((s16)timer < 15) {
            if (!(((S_80172A48_3 *)actor)->unk_14 & 0x8000)) {
                goto end;
            }
        }
    }
    ((S_80172A48_0 *)action)->unk_96.u = 0;
    ((S_80172A48_0 *)action)->unk_9B++;
    func_800A56E0(0x703);
    model_base = D_80174110;
    goto set_model;

state_4:
    func_80170A44(action, motion, actor, item);
    {
        s16 timer;

        timer = ((S_80172A48_0 *)action)->unk_96.u;
        ((S_80172A48_0 *)action)->unk_96.u = timer + 1;
        if ((s16)timer < 3) {
            if (!(((S_80172A48_3 *)actor)->unk_14 & 0xE000)) {
                goto end;
            }
        }
    }
    ((S_80172A48_3 *)actor)->unk_14 |= 0x800;
    next_state = ((S_80172A48_0 *)action)->unk_9B;
    ASM_KEEP(next_state); /* MATCH: keep each state load distinct before its delay-slot increment. */
    next_state++;
    goto store_next_state;

state_5:
    ((S_80172A48_3 *)actor)->unk_14 |= 0x800;
    {
        s16 timer;

        timer = ((S_80172A48_0 *)action)->unk_96.u;
        ((S_80172A48_0 *)action)->unk_96.u = timer + 1;
        if ((s16)timer < 10) {
            if (!(((S_80172A48_3 *)actor)->unk_14 & 0x8000)) {
                goto end;
            }
        }
    }
    ((S_80172A48_0 *)action)->unk_96.u = 0;
    ((S_80172A48_0 *)action)->unk_9B++;
    ((S_80172A48_3 *)actor)->unk_14 &= 0xF7FF;
    return;

state_6:
    ((S_80172A48_0 *)action)->unk_96.u = 0;
    ((S_80172A48_0 *)action)->unk_98 |= 0x80;
    ((S_80172A48_0 *)action)->unk_9B++;
    return;

state_7:
    if (!(((S_80172A48_3 *)actor)->unk_14 & 0xE000)) {
        goto end;
    }
    ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 = 0;
    ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = 0;
    ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = 0;
    func_800A2B04(motion, ((S_80172A48_3 *)actor)->unk_24, ((S_80172A48_3 *)actor)->unk_25);
    ((S_80172A48_0 *)action)->unk_9B++;
    if (((S_80172A48_3 *)actor)->unk_2C == D_801740E0) {
        goto end;
    }
    {
        u8 *model = D_801740E0;

        (*(void * *)((u8 *)actor + 0x2C)) = model;
        func_80047784(actor,
            model[((D_80083228 + (*(s16 *)((u8 *)item + 0x2A)) + 0x100) >> 9) & 7],
            0);
    }
    ((S_80172A48_0 *)action)->unk_9E = 0;
    ((S_80172A48_0 *)action)->unk_92 = -0x20;
    return;

state_8:
    {
        u8 *action_state;

        action_state = (u8 *)&D_80083460;
        if (((S_80172A48_5 *)action_state)->unk_0C != 0) {
            goto end;
        }
        ((S_80172A48_5 *)action_state)->unk_0A--;
        ((S_80172A48_0 *)action)->unk_8C = D_801714D4;
        func_800A4ACC(item);
        (*(u8 *)((u8 *)item + 0x73)) = 0;
        (*(u8 *)((u8 *)item + 0x72)) = 0;
        (*(u8 *)((u8 *)item + 0x6D))--;
        (*(u16 *)((u8 *)item + 0x46)) &= 0x7FFF;
        func_800A56E0(0xB4);
    }
    return;

state_16:
    if (func_8003F270()) {
set_actor_flag:
        ((S_80172A48_3 *)actor)->unk_14 |= 0x800;
        return;
    }
    ((S_80172A48_3 *)actor)->unk_14 &= 0xF7FF;
    ((S_80172A48_0 *)action)->unk_9B++;

state_17:
    {
        s16 timer;

        timer = ((S_80172A48_0 *)action)->unk_96.u;
        ((S_80172A48_0 *)action)->unk_96.u = timer + 1;
        if ((s16)timer < 8 &&
            !(((S_80172A48_3 *)actor)->unk_14 & 0x8000)) {
            goto end;
        }
    }
    next_state = ((S_80172A48_0 *)action)->unk_9B;
    ((S_80172A48_0 *)action)->unk_96.u = 0;
    ASM_KEEP(next_state); /* MATCH: keep each state load distinct before its delay-slot increment. */
    next_state++;
    goto store_next_state;

state_18:
    if (((S_80172A48_0 *)action)->unk_A2 != 0) {
        s16 timer;

        timer = ((S_80172A48_0 *)action)->unk_96.u;
        ((S_80172A48_0 *)action)->unk_96.u = timer + 1;
        if ((s16)timer < 15 &&
            !(((S_80172A48_3 *)actor)->unk_14 & 0x8000)) {
            goto end;
        }
    }
    ((S_80172A48_0 *)action)->unk_96.u = 0;
    ((S_80172A48_0 *)action)->unk_9B++;
    func_800A56E0(0x703);
    /* MATCH: the preceding eight-byte model table uses a distinct address expression in this arm. */
    model_base = (u8 *)((u32)D_80174118 - 8);
    goto set_model;

state_19:
    func_80170A44(action, motion, actor, item);
    {
        s16 timer;

        timer = ((S_80172A48_0 *)action)->unk_96.u;
        ((S_80172A48_0 *)action)->unk_96.u = timer + 1;
        if ((s16)timer < 2 &&
            !(((S_80172A48_3 *)actor)->unk_14 & 0xE000)) {
            goto end;
        }
    }
    ((S_80172A48_3 *)actor)->unk_14 |= 0x800;
    next_state = ((S_80172A48_0 *)action)->unk_9B;
    next_state++;
    goto store_next_state;

state_20:
    ((S_80172A48_3 *)actor)->unk_14 |= 0x800;
    if (((S_80172A48_0 *)action)->unk_96.s < 5) {
        func_80170A44(action, motion, actor, item);
    }
    {
        s16 timer;

        timer = ((S_80172A48_0 *)action)->unk_96.u;
        ((S_80172A48_0 *)action)->unk_96.u = timer + 1;
        if ((s16)timer < 10 &&
            !(((S_80172A48_3 *)actor)->unk_14 & 0x8000)) {
            goto end;
        }
    }
    ((S_80172A48_0 *)action)->unk_96.u = 0;
    ((S_80172A48_0 *)action)->unk_9B++;
    ((S_80172A48_3 *)actor)->unk_14 &= 0xF7FF;
    ((S_80172A48_0 *)action)->unk_98 |= 0x80;
    return;

state_21:
    if (!(((S_80172A48_3 *)actor)->unk_14 & 0xE000)) {
        goto end;
    }
    ((S_80172A48_0 *)action)->unk_96.u = 0;
    ((S_80172A48_0 *)action)->unk_9B++;
    {
        model_base = D_80174118;

set_model:

        (*(void * *)((u8 *)actor + 0x2C)) = model_base;
        func_80047784(actor,
            *((u8 *)((((D_80083228 + (*(s16 *)((u8 *)item + 0x2A)) + 0x100) >> 9) & 7) + (u32)model_base)),
            0);
    }
    return;

state_22:
    {
        s16 timer;

        timer = ((S_80172A48_0 *)action)->unk_96.u;
        ((S_80172A48_0 *)action)->unk_96.u = timer + 1;
        if ((s16)timer < 5) {
            goto end;
        }
    }
    next_state = ((S_80172A48_0 *)action)->unk_9B;
    ((S_80172A48_0 *)action)->unk_96.u = 0;
    next_state++;
    goto store_next_state;

state_23:
    next_state = 6;
    ((S_80172A48_0 *)action)->unk_96.u = 0;

store_next_state:
    ((S_80172A48_0 *)action)->unk_9B = next_state;

end:
    return;
}
