#include "common.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800E3D7C.h"


extern s32 func_8003F270(void);
extern void func_80047784(void *, s32, s32);
extern void *func_800A05A4(void *, u8, u8, s16, s32);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern s32 func_800A94A0(void *, u8 *, s32, void *);
extern void func_800BB044(void *);

extern u8 D_8006DE24[];
extern void *D_800814A8;
extern s16 D_80083228;
extern s32 D_80083460;
extern s32 D_8008346C;
extern void *D_80170850[];
extern u8 D_80170E9C[];
extern u8 D_80174EE0[];


typedef struct S_8017293C_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} S_8017293C_0;   /* arg0 in func_8017293C */

typedef struct S_8017293C_1_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_8017293C_1_pre;   /* the 0x14 bytes before active in func_8017293C, addressed as active[-1] */

typedef struct S_8017293C_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_8017293C_2;   /* linked in func_8017293C */



typedef struct S_8017293C_5 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} S_8017293C_5;   /* global in func_8017293C */

/* Runs the actor's selected item action and handles its wait and completion phases. */
void func_8017293C(void *action, void *motion, void *sprite, void *actor)
{
    static void *const kind_keep[] = {
        &&kind_1, &&kind_2, &&kind_3, &&kind_default,
        &&kind_7, &&kind_6, &&kind_5
    };
    u8 *item_slot;
    s32 is_special;
    u8 phase;
    void *target;

    is_special = 0;
    phase = ((S_8017293C_0 *)action)->unk_9B;
    switch (phase) {
    case 0:
        goto state_0;
    case 1:
        goto state_1;
    case 2:
        goto state_2;
    default:
        goto end;
    }

state_0:
    if ((*(u32 *)((u8 *)actor + 0x1C)) & 0x2000) {
        u32 kind_index;

        kind_index = ((*(u16 *)((u8 *)actor + 0x46)) & 0x3FFF) - 1;
        if (kind_index >= 7) {
            goto kind_default;
        }
        (void)kind_keep;
        goto *D_80170850[kind_index];

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

        item_kind = (*(u16 *)((u8 *)actor + 0x46)) & 0x3FFF;
        switch (item_kind) {
        case 1:
            goto normal_kind_1;
        case 2:
            goto kind_2;
        case 3:
            goto kind_3;
        default:
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
    ((S_8017293C_0 *)action)->unk_98 &= 0xFF7F;
    ASM_KEEP(item_slot);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    {
        s16 use_special;

        use_special = is_special;
        if (use_special != 0) {
            target = D_800814A8;
            (*(void * *)((u8 *)actor + 0x60)) = target;
            goto copy_active_coords;
        }
    }

    {
        u8 item_id;

        item_id = *item_slot;
        if (D_8006DE24[item_id * 20 + 0x12] == 2) {
            target = (*(void * *)((u8 *)actor + 0x60));
            if (target != 0) {
                register u8 *target_sprite ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

copy_active_coords:
                target_sprite = ((S_8017293C_1_pre *)target)[-1].unk_00;
                (*(u8 *)((u8 *)actor + 0x72)) = ((S_8017293C_2 *)target_sprite)->unk_24;
                (*(u8 *)((u8 *)actor + 0x73)) = ((S_8017293C_2 *)target_sprite)->unk_25;
                goto invoke_item;
            }
        } else {
            s32 dx;
            s32 dy;

            target = func_800A05A4(
                actor, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25,
                (*(s16 *)((u8 *)actor + 0x2A)), 0x10);
            (*(void * volatile *)((u8 *)actor + 0x60)) = target;
            ASM_KEEP(target);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
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
    if (func_800A94A0(actor, item_slot, is_special,
                      (u8 *)action + 0x98) == 0) {
        goto end;
    }
    func_800BB044(actor);
    ((S_8017293C_0 *)action)->unk_9B++;
    goto end;

empty_selection:
    ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 = 0;
    ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = 0;
    ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = 0;
    func_800A2B04(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
    D_8008346C = 0;
    (*(u16 *)((u8 *)D_800814A8 + 0xA6))--;
    func_800A4ACC(actor);
    (*(u8 *)((u8 *)actor + 0x6D))--;
    ((S_8017293C_0 *)action)->unk_8C = D_80170E9C;
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
    ((S_8017293C_0 *)action)->unk_9B++;

state_2:
    if ((((Rec_D_80082E80 *)sprite)->unk_04.as_s8 == 3 &&
         (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x1000)) ||
        (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
        ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 0x800;
        ((S_8017293C_0 *)action)->unk_96 = 1;
        ((S_8017293C_0 *)action)->unk_98 |= 0x80;
    }
    {
        s16 wait_ticks;

        wait_ticks = ((S_8017293C_0 *)action)->unk_96 - 1;
        ((S_8017293C_0 *)action)->unk_96 = wait_ticks;
        if (wait_ticks <= 0) {
            ((S_8017293C_0 *)action)->unk_96 = 0;
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v &= 0xF7FF;
        }
    }
    if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
        goto end;
    }
    ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 = 0;
    ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = 0;
    ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = 0;
    func_800A2B04(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
    if (((Rec_D_80082E80 *)sprite)->unk_2C.as_pu8 != D_80174EE0) {
        u8 *direction_frames;
        s32 direction;

        direction_frames = D_80174EE0;
        (*(u8 * *)((u8 *)sprite + 0x2C)) = direction_frames;
        direction = ((D_80083228 + (*(s16 *)((u8 *)actor + 0x2A)) + 0x100) >> 9) & 7;
        func_80047784(sprite, direction_frames[direction], 0);
    }
    {
        u8 *action_status;

        action_status = (u8 *)&D_80083460;
        if (((S_8017293C_5 *)action_status)->unk_0C != 0) {
            goto end;
        }
        ((S_8017293C_5 *)action_status)->unk_0A--;
        ((S_8017293C_0 *)action)->unk_8C = D_80170E9C;
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
