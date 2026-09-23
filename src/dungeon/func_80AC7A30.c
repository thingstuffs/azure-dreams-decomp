#include "common.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800E3D7C.h"


typedef struct {
    u32 words[12];
} Copy48;

extern s32 func_8003DE58(void *, void *, void *, s32);
extern s32 func_8003F270(void);
extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern void func_80047784(void *, s32, s32);
extern void *func_800A05A4(void *, u8, u8, s16, s32);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern s32 func_800A94A0(void *, u8 *, s32, void *);

extern s32 D_80045340;
extern u8 D_8006DE24[];
extern void *D_800814A8;
extern s16 D_80083228;
extern s32 D_80083460;
extern s32 D_8008346C;
extern u8 D_80083498[];
extern void *D_80170850[];
extern void *D_80170868[];
extern u8 D_80171020[];
extern s32 D_80171728;
extern u8 D_80174DEC[];
extern u8 D_80174E34[];


typedef struct S_80173230_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { u16 u; s16 s; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x10];
    u16 unk_AC;
} S_80173230_0;   /* arg0 in func_80173230 */

typedef struct S_80173230_1_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80173230_1_pre;   /* the 0x14 bytes before active in func_80173230, addressed as active[-1] */

typedef struct S_80173230_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80173230_2;   /* linked in func_80173230 */



typedef struct S_80173230_5 {
    u8 pad_00[0x94];
    u16 unk_94;
    u16 unk_96;
    u8 pad_98[0x10];
    void * unk_A8;
} S_80173230_5;   /* part in func_80173230 */

typedef struct S_80173230_6 {
    u8 pad_00[0x8];
    u8 * unk_08;
    u8 * unk_0C;
    void * unk_10;
} S_80173230_6;   /* (void *)special in func_80173230 */

typedef struct S_80173230_7 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    u16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
    u8 pad_20[0xC];
    void * unk_2C;
} S_80173230_7;   /* target in func_80173230 */

typedef struct S_80173230_8 {
    u8 pad_00[0xC];
    void * unk_0C;
} S_80173230_8;   /* base in func_80173230 */

typedef struct S_80173230_9 {
    u8 pad_00[0x8];
    void * unk_08;
} S_80173230_9;   /* source in func_80173230 */

typedef struct S_80173230_10 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} S_80173230_10;   /* global in func_80173230 */

/* Advances item use, its visual effect, and the actor's recovery animation. */
void func_80173230(void *action_in, void *motion_in, void *sprite, void *actor)
{
    static void *const state_labels[] = {
        &&state_0, &&state_1, &&state_2, &&state_3, &&state_4
    };
    static void *const kind_labels[] = {
        &&kind_1, &&kind_2, &&kind_3, &&kind_default,
        &&kind_7, &&kind_6, &&kind_5
    };
    u8 *effect_state;
    s32 effect_handle;
    s16 special_or_effect;
    u16 effect_offset[4];
    u8 *item_slot;
    u8 *action_object;
    s32 next_state;
    u8 state;
    void *item_target;

    special_or_effect = 0;
    action_object = (u8 *)action_in - 0x20;
    state = ((S_80173230_0 *)action_in)->unk_9B;
    if ((u32)state >= 5) {
        goto end;
    }
    (void)state_labels;
    goto *D_80170850[state];

state_0:
    if ((*(u32 *)((u8 *)actor + 0x1C)) & 0x2000) {
        u32 kind_index;

        kind_index = ((*(u16 *)((u8 *)actor + 0x46)) & 0x3FFF) - 1;
        if (kind_index >= 7) {
            goto kind_default;
        }
        (void)kind_labels;
        goto *D_80170868[kind_index];

kind_5:
        special_or_effect = 1;
        goto kind_3;
kind_6:
        special_or_effect = 1;
        goto kind_2;
kind_7:
        special_or_effect = 1;
        goto kind_1;
    }

    {
        s32 item_kind;

        item_kind = (*(u16 *)((u8 *)actor + 0x46)) & 0x3FFF;
        if (item_kind == 2) {
            goto kind_2;
        }
        if (item_kind < 3) {
            item_slot = 0;
            if (item_kind == 1) {
                goto normal_kind_1;
            }
            goto selection_ready;
        }
        if (item_kind != 3) {
            item_slot = 0;
            goto selection_ready;
        }
    }

kind_3:
    item_slot = (u8 *)actor + 0xE;
    goto selection_ready;
kind_2:
    item_slot = (u8 *)actor + 0xB;
    goto selection_ready;
normal_kind_1:
kind_1:
    item_slot = (u8 *)actor + 8;
    goto selection_ready;
kind_default:
    item_slot = 0;

selection_ready:
    if (*item_slot == 0) {
        goto empty_selection;
    }
    ((S_80173230_0 *)action_in)->unk_98 &= 0xFF7F;
    {
        s16 is_special;

        is_special = special_or_effect;
        if (is_special != 0) {
            item_target = D_800814A8;
            (*(void * *)((u8 *)actor + 0x60)) = item_target;
            goto copy_active_coords;
        }
    }

    {
        u8 item_id;
        u8 *item_defs;

        item_id = *item_slot;
        item_defs = D_8006DE24;
        if (item_defs[item_id * 20 + 0x12] == 2) {
            item_target = (*(void * *)((u8 *)actor + 0x60));
            if (item_target != 0) {

copy_active_coords:
                effect_state = ((S_80173230_1_pre *)item_target)[-1].unk_00;
                (*(u8 *)((u8 *)actor + 0x72)) = ((S_80173230_2 *)effect_state)->unk_24;
                (*(u8 *)((u8 *)actor + 0x73)) = ((S_80173230_2 *)effect_state)->unk_25;
                goto invoke_item;
            }
        } else {
            s32 dx;
            s32 dy;

            dx = (s32)func_800A05A4(
                actor, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25,
                (*(s16 *)((u8 *)actor + 0x2A)), 0x10);
            (*(void * volatile *)((u8 *)actor + 0x60)) = (void *)dx;
            dx = (*(s8 *)((u8 *)actor + 0x72));
            dy = (*(s8 *)((u8 *)actor + 0x73));
            if (dx < 0) {
                dx = -dx;
            }
            if (dy < 0) {
                dy = -dy;
            }
            (*(u8 *)((u8 *)actor + 0x72)) = dx;
            (*(u8 *)((u8 *)actor + 0x73)) = dy;
        }
    }

invoke_item:
    if (func_800A94A0(actor, item_slot, special_or_effect, (u8 *)action_in + 0x98) == 0) {
        return;
    }
    ((S_80173230_0 *)action_in)->unk_96.u = 0x11;
    ((S_80173230_0 *)action_in)->unk_9B++;
    return;

empty_selection:
    ((Rec_D_800E3D7C *)motion_in)->unk_14.as_s32 = 0;
    ((Rec_D_800E3D7C *)motion_in)->unk_10.at00_s32.v = 0;
    ((Rec_D_800E3D7C *)motion_in)->unk_0C.as_s32 = 0;
    func_800A2B04(motion_in, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
    D_8008346C = 0;
    (*(u16 *)((u8 *)D_800814A8 + 0xA6))--;
    func_800A4ACC(actor);
    (*(u8 *)((u8 *)actor + 0x6D))--;
    ((S_80173230_0 *)action_in)->unk_8C = &D_80171728;
    (*(u8 *)((u8 *)actor + 0x73)) = 0;
    (*(u8 *)((u8 *)actor + 0x72)) = 0;
    (*(u16 *)((u8 *)actor + 0x46)) &= 0x7FFF;
    goto end;

state_1:
    if (func_8003F270()) {
        ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 0x800;
        goto end;
    }
    ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v &= 0xF7FF;
    ((S_80173230_0 *)action_in)->unk_9B++;
    func_800A56E0(0x703);

state_2:
    {
        s16 timer;

        timer = ((S_80173230_0 *)action_in)->unk_96.u - 1;
        ((S_80173230_0 *)action_in)->unk_96.u = timer;
        if (timer == 0xB || (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
            effect_handle = (s32)func_8003FD64(0x112, D_80083498);
            if (effect_handle != 0) {
                void *actor_model;
                u8 animation_id;

                effect_state = (u8 *)effect_handle + 0x20;
                ((S_80173230_5 *)effect_state)->unk_96 = 9;
                ((S_80173230_6 *)((void *)effect_handle))->unk_10 = D_80171020;
                ((S_80173230_5 *)effect_state)->unk_A8 = motion_in;
                ((S_80173230_5 *)effect_state)->unk_94 = (*(u16 *)((u8 *)actor + 0x2A));
                item_slot = ((S_80173230_6 *)((void *)effect_handle))->unk_0C;
                *(Copy48 *)item_slot = *(Copy48 *)sprite;
                ((S_80173230_7 *)item_slot)->unk_1E = 0x1000;
                ((S_80173230_7 *)item_slot)->unk_1C = 0x1000;
                ((S_80173230_7 *)item_slot)->unk_0E = 0x80;
                ((S_80173230_7 *)item_slot)->unk_0D = 0x80;
                ((S_80173230_7 *)item_slot)->unk_0C = 0x80;
                func_8004491C((void *)effect_handle, &D_80045340);
                animation_id = D_80174E34[0];
                ((S_80173230_7 *)item_slot)->unk_2C = D_80174E34;
                func_80047784(item_slot, animation_id, 0);
                ((S_80173230_7 *)item_slot)->unk_10 = 0x20;
                ((S_80173230_7 *)item_slot)->unk_12 = 0xFF80;
                ((S_80173230_7 *)item_slot)->unk_14 |= 0x0C;

                actor_model = ((S_80173230_8 *)action_object)->unk_0C;
                item_slot = ((S_80173230_6 *)((void *)effect_handle))->unk_08;
                if (func_8003DE58(
                        ((S_80173230_9 *)actor_model)->unk_08, actor_model, effect_offset, 1) != 0) {
                    ((S_80173230_7 *)item_slot)->unk_02 = ((Rec_D_800E3D7C *)motion_in)->unk_00.at02_u16.v;
                    ((S_80173230_7 *)item_slot)->unk_06 = ((Rec_D_800E3D7C *)motion_in)->unk_04.at02_u16.v;
                    ((S_80173230_7 *)item_slot)->unk_0A = ((Rec_D_800E3D7C *)motion_in)->unk_08.at02_u16.v;
                    ((S_80173230_7 *)item_slot)->unk_02 += effect_offset[0];
                    ((S_80173230_7 *)item_slot)->unk_06 += effect_offset[1];
                    ((S_80173230_7 *)item_slot)->unk_0A += effect_offset[2];
                }
            }
        }

        if (((S_80173230_0 *)action_in)->unk_96.s == 0xB ||
            (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 0x800;
        }
        if (((S_80173230_0 *)action_in)->unk_96.s == 0 ||
            (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v &= 0xF7FF;
        }
        if (((S_80173230_0 *)action_in)->unk_96.s <= 0 ||
            (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
            next_state = ((S_80173230_0 *)action_in)->unk_9B + 1;
            goto store_next_state;
        }
    }
    goto end;

store_next_state:
    ((S_80173230_0 *)action_in)->unk_9B = next_state;
    goto end;

state_3:
    if ((((Rec_D_80082E80 *)sprite)->unk_04.as_s8 == 3 &&
         (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x1000)) ||
        (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000)) {
        ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 0x800;
        ((S_80173230_0 *)action_in)->unk_96.u = 0x14;
        ((S_80173230_0 *)action_in)->unk_98 |= 0x80;
        ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 0x100;
        ((S_80173230_0 *)action_in)->unk_AC = ((Rec_D_80082E80 *)sprite)->unk_12.at00_u16.v;
        ((Rec_D_80082E80 *)sprite)->unk_12.at00_u16.v = 0x7E80;
        ((S_80173230_0 *)action_in)->unk_9B++;
    }

state_4:
    {
        u8 *action_status;
        s16 timer;

        action_status = (u8 *)&D_80083460;
        if (((S_80173230_10 *)action_status)->unk_0C == 0) {
            ((S_80173230_0 *)action_in)->unk_96.u = 0;
        }
        timer = ((S_80173230_0 *)action_in)->unk_96.u - 1;
        ((S_80173230_0 *)action_in)->unk_96.u = timer;
        if (timer <= 0) {
            ((S_80173230_0 *)action_in)->unk_96.u = 0;
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v &= 0xF7FF;
        }
        if (((S_80173230_0 *)action_in)->unk_96.s == 0x12) {
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v &= 0xFEFF;
            ((Rec_D_80082E80 *)sprite)->unk_12.at00_u16.v = ((S_80173230_0 *)action_in)->unk_AC;
        }
        if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
            goto end;
        }

        ((Rec_D_800E3D7C *)motion_in)->unk_14.as_s32 = 0;
        ((Rec_D_800E3D7C *)motion_in)->unk_10.at00_s32.v = 0;
        ((Rec_D_800E3D7C *)motion_in)->unk_0C.as_s32 = 0;
        func_800A2B04(motion_in, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
        ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v &= 0xFEFF;
        ((Rec_D_80082E80 *)sprite)->unk_12.at00_u16.v = ((S_80173230_0 *)action_in)->unk_AC;

        if (((Rec_D_80082E80 *)sprite)->unk_2C.as_pu8 != D_80174DEC) {
            u8 *animations;
            s32 direction;

            animations = D_80174DEC;
            (*(u8 * *)((u8 *)sprite + 0x2C)) = animations;
            direction = ((D_80083228 + (*(s16 *)((u8 *)actor + 0x2A)) + 0x100) >> 9) & 7;
            func_80047784(sprite, animations[direction], 0);
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v &= 0xF7FF;
        }
        if (((S_80173230_10 *)action_status)->unk_0C != 0) {
            goto end;
        }
        ((S_80173230_10 *)action_status)->unk_0A--;
        ((S_80173230_0 *)action_in)->unk_8C = &D_80171728;
        func_800A4ACC(actor);
        (*(u8 *)((u8 *)actor + 0x73)) = 0;
        (*(u8 *)((u8 *)actor + 0x72)) = 0;
        (*(u8 *)((u8 *)actor + 0x6D))--;
        (*(u16 *)((u8 *)actor + 0x46)) &= 0x7FFF;
        func_800A56E0(0xB4);
    }

end:
    return;
}
