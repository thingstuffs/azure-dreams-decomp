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
extern void *D_80170838[];
extern u8 D_80170F20[];
extern u8 D_801762C0[];


typedef struct S_80172798_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} S_80172798_0;   /* arg0 in func_80172798 */

typedef struct S_80172798_1_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80172798_1_pre;   /* the 0x14 bytes before active in func_80172798, addressed as active[-1] */

typedef struct S_80172798_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80172798_2;   /* linked in func_80172798 */



typedef struct S_80172798_5 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} S_80172798_5;   /* global in func_80172798 */

/* Advances the selected item action and resets movement when it ends. */
void func_80172798(void *action, void *motion, void *sprite, void *actor)
{
    static void *const kind_keep[] = {
        &&kind_1, &&kind_2, &&kind_3, &&kind_default,
        &&kind_7, &&kind_6, &&kind_5
    };
    u8 *selection;
    s32 special;
    u8 state;
    void *active;

    special = 0;
    state = ((S_80172798_0 *)action)->unk_9B;
    switch (state) {
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
        goto *D_80170838[kind_index];

kind_5:
        special = 1;
        goto kind_3;
kind_6:
        special = 1;
        goto kind_2;
kind_7:
        special = 1;
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
            selection = 0;
            goto selection_ready;
        }
    }

kind_3:
    selection = (u8 *)actor + 0xE;
    goto selection_ready;
kind_2:
    selection = (u8 *)actor + 0xB;
    goto selection_ready;
normal_kind_1:
kind_1:
    selection = (u8 *)actor + 8;
    goto selection_ready;
kind_default:
    selection = 0;

selection_ready:
    if (*selection == 0) {
        goto empty_selection;
    }
    ((S_80172798_0 *)action)->unk_98 &= 0xFF7F;
    ASM_KEEP(selection);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    {
        s16 special_test;

        special_test = special;
        if (special_test != 0) {
            active = D_800814A8;
            (*(void * *)((u8 *)actor + 0x60)) = active;
            goto copy_active_coords;
        }
    }

    {
        u8 item_id;

        item_id = *selection;
        if (D_8006DE24[item_id * 20 + 0x12] == 2) {
            active = (*(void * *)((u8 *)actor + 0x60));
            if (active != 0) {
                register u8 *linked ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

copy_active_coords:
                linked = ((S_80172798_1_pre *)active)[-1].unk_00;
                (*(u8 *)((u8 *)actor + 0x72)) = ((S_80172798_2 *)linked)->unk_24;
                (*(u8 *)((u8 *)actor + 0x73)) = ((S_80172798_2 *)linked)->unk_25;
                goto invoke_item;
            }
        } else {
            s32 dx;
            s32 dy;

            active = func_800A05A4(
                actor, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25,
                (*(s16 *)((u8 *)actor + 0x2A)), 0x10);
            (*(void * volatile *)((u8 *)actor + 0x60)) = active;
            ASM_KEEP(active);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
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
    if (func_800A94A0(actor, selection, special,
                      (u8 *)action + 0x98) == 0) {
        goto end;
    }
    func_800BB044(actor);
    ((S_80172798_0 *)action)->unk_9B++;
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
    ((S_80172798_0 *)action)->unk_8C = D_80170F20;
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
    ((S_80172798_0 *)action)->unk_9B++;

state_2:
    if ((((Rec_D_80082E80 *)sprite)->unk_04.as_s8 == 7 &&
         (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x1000)) ||
        (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
        ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 0x800;
        ((S_80172798_0 *)action)->unk_96 = 1;
        ((S_80172798_0 *)action)->unk_98 |= 0x80;
    }
    {
        s16 timer;

        timer = ((S_80172798_0 *)action)->unk_96 - 1;
        ((S_80172798_0 *)action)->unk_96 = timer;
        if (timer <= 0) {
            ((S_80172798_0 *)action)->unk_96 = 0;
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
    if (((Rec_D_80082E80 *)sprite)->unk_2C.as_pu8 != D_801762C0) {
        u8 *anim_table;
        s32 direction;

        anim_table = D_801762C0;
        (*(u8 * *)((u8 *)sprite + 0x2C)) = anim_table;
        direction = ((D_80083228 + (*(s16 *)((u8 *)actor + 0x2A)) + 0x100) >> 9) & 7;
        func_80047784(sprite, anim_table[direction], 0);
    }
    {
        u8 *action_status;

        action_status = (u8 *)&D_80083460;
        if (((S_80172798_5 *)action_status)->unk_0C != 0) {
            goto end;
        }
        ((S_80172798_5 *)action_status)->unk_0A--;
        ((S_80172798_0 *)action)->unk_8C = D_80170F20;
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
