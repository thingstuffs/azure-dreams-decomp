#include "common.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800E3D7C.h"

typedef struct S_80172834_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x8];
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} S_80172834_0;   /* arg0 in func_80172834 */

typedef struct S_80172834_1 {
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
} S_80172834_1;   /* arg3 in func_80172834 */

typedef struct S_80172834_2_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80172834_2_pre;   /* the 0x14 bytes before object in func_80172834, addressed as object[-1] */

typedef struct S_80172834_3 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80172834_3;   /* record in func_80172834 */



typedef struct S_80172834_6 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} S_80172834_6;   /* globals in func_80172834 */



extern s32 func_8003F270(void);
extern void func_80047784(void *, s32, s32);
extern void *func_800A05A4(void *, u8, u8, s16, s32);
extern void func_800A2B04(void *, s32, s32);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern s32 func_800A94A0(void *, u8 *, s32, u16 *);
extern void func_800DA840(u16 *, s32);

extern u8 D_8006DE24[];
extern void *D_800814A8;
extern s16 D_80083228;
extern s32 D_80083460;
extern s32 D_8008346C;
extern void *D_80170858[];
extern u8 D_80171058[];
extern u8 D_80174888[];

/* Starts the selected actor action, waits for completion, and resets its state. */
void func_80172834(void *action_state, void *motion, void *sprite, void *actor)
{
    static void *const switch_keep[] = {
        &&special_3, &&special_2, &&special_1, &&kind_none,
        &&kind_none, &&kind_none, &&kind_none
    };
    u8 *action_data;
    s32 phase;
    s32 is_special;
    s32 action_kind;
    void *target;
    register s32 x ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s32 y;
    u16 position[3];

    phase = ((S_80172834_0 *)action_state)->unk_9B;
    is_special = 0;
    if (phase == 1) {
        goto state_1;
    }
    if (phase < 2) {
        if (phase == 0) {
            goto state_0;
        }
        goto done;
    }
    if (phase == 2) {
        goto state_2;
    }
    goto done;

state_0:
    if (((S_80172834_1 *)actor)->unk_1C & 0x2000) {
        action_kind = (((S_80172834_1 *)actor)->unk_46 & 0x3FFF) - 1;
        if ((u32)action_kind >= 7U) {
            goto kind_none;
        }
        (void)switch_keep;
        goto *D_80170858[action_kind];

special_3:
        is_special = 1;
        goto kind_3;
special_2:
        is_special = 1;
        goto kind_2;
special_1:
        is_special = 1;
        goto kind_1;
    }

    action_kind = ((S_80172834_1 *)actor)->unk_46 & 0x3FFF;
    if (action_kind == 2) {
        goto kind_2;
    }
    if (action_kind < 3) {
        if (action_kind == 1) {
            goto kind_1;
        }
        action_data = 0;
        goto have_choice;
    }
    if (action_kind != 3) {
        action_data = 0;
        goto have_choice;
    }

kind_3:
    action_data = (u8 *)actor + 0xE;
    goto have_choice;
kind_2:
    action_data = (u8 *)actor + 0xB;
    goto have_choice;
kind_1:
    action_data = (u8 *)actor + 8;
    goto have_choice;
kind_none:
    action_data = 0;

have_choice:
    if (*action_data != 0) {
        x = ((S_80172834_0 *)action_state)->unk_98;
        x &= 0xFF7F;
        ((S_80172834_0 *)action_state)->unk_98 = x;
        x = is_special;
        if (x != 0) {
            target = D_800814A8;
            ((S_80172834_1 *)actor)->unk_60 = target;
            goto copy_existing;
        }

        if (D_8006DE24[(*action_data * 20) + 0x12] == 2) {
            target = ((S_80172834_1 *)actor)->unk_60;
            if (target == 0) {
                goto move_setup;
            }
copy_existing:
            {

                phase = ((S_80172834_2_pre *)target)[-1].unk_00;
                ((S_80172834_1 *)actor)->unk_72.s = ((S_80172834_3 *)phase)->unk_24;
                ((S_80172834_1 *)actor)->unk_73.s = ((S_80172834_3 *)phase)->unk_25;
            }
            goto apply_move;
        }

        ((S_80172834_1 *)actor)->unk_60 =
            func_800A05A4(actor,
                          ((Rec_D_80082E80 *)sprite)->unk_24,
                          ((Rec_D_80082E80 *)sprite)->unk_25,
                          ((S_80172834_1 *)actor)->unk_2A, 0x10);
        x = ((S_80172834_1 *)actor)->unk_72.u;
        y = ((S_80172834_1 *)actor)->unk_73.u;
        if (x < 0) {
            x = -x;
        }
        if (y < 0) {
            y = -y;
        }
        ((S_80172834_1 *)actor)->unk_72.s = x;
        ((S_80172834_1 *)actor)->unk_73.s = y;

move_setup:
apply_move:
        position[0] = ((Rec_D_800E3D7C *)motion)->unk_00.at02_u16.v;
        position[1] = ((Rec_D_800E3D7C *)motion)->unk_04.at02_u16.v;
        position[2] = ((Rec_D_800E3D7C *)motion)->unk_08.at02_u16.v;
        if (func_800A94A0(actor, action_data, is_special,
                          (u16 *)((u8 *)action_state + 0x98)) == 0) {
            goto done;
        }
        ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v &= 0xF7FF;
        func_800DA840(position, (s16)(((s32)*action_data - 1) % 3));
        func_800A56E0(0x703);
        ((S_80172834_0 *)action_state)->unk_9B++;
        goto done;
    }

    ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 = 0;
    ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = 0;
    ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = 0;
    func_800A2B04(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
    D_8008346C = 0;
    (*(u16 *)((u8 *)D_800814A8 + 0xA6))--;
    func_800A4ACC(actor);
    ((S_80172834_1 *)actor)->unk_6D.s--;
    ((S_80172834_0 *)action_state)->unk_8C = D_80171058;
    ((S_80172834_1 *)actor)->unk_73.s = 0;
    ((S_80172834_1 *)actor)->unk_72.s = 0;
    ((S_80172834_1 *)actor)->unk_46 &= 0x7FFF;
    goto done;

state_1:
    if (func_8003F270() != 0) {
        ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 0x800;
        goto done;
    }
    ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v &= 0xF7FF;
    ((S_80172834_0 *)action_state)->unk_9B++;

state_2:
    if ((((Rec_D_80082E80 *)sprite)->unk_04.as_s8 == 3) &&
        (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x1000)) {
        goto state_2_ready;
    }
    if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
        goto done;
    }

state_2_ready:
    ((S_80172834_0 *)action_state)->unk_98 |= 0x80;
    if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
        goto done;
    }
    ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 = 0;
    ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = 0;
    ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = 0;
    func_800A2B04(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
    if (((Rec_D_80082E80 *)sprite)->unk_2C.as_pu8 != D_80174888) {
        (*(u8 * *)((u8 *)sprite + 0x2C)) = D_80174888;
        func_80047784(
            sprite,
            D_80174888[((D_80083228 + ((S_80172834_1 *)actor)->unk_2A + 0x100) >> 9) & 7],
            0);
    }
    {
        s32 *globals = &D_80083460;

        if (((S_80172834_6 *)globals)->unk_0C != 0) {
            goto done;
        }
        ((S_80172834_6 *)globals)->unk_0A--;
    }
    ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v &= 0xF7FF;
    ((S_80172834_0 *)action_state)->unk_8C = D_80171058;
    func_800A4ACC(actor);
    if (((S_80172834_1 *)actor)->unk_6D.u > 0) {
        ((S_80172834_1 *)actor)->unk_6D.s--;
    }
    ((S_80172834_1 *)actor)->unk_73.s = 0;
    ((S_80172834_1 *)actor)->unk_72.s = 0;
    ((S_80172834_1 *)actor)->unk_46 &= 0x7FFF;
    func_800A56E0(0xB4);

done:
    return;
}

/* MECHANISM: The 0x40 frame falls naturally from four held arguments, six saved s-regs,
   and sibling u16 stack locals; pinned v0 sequences the 0x98 update before the flag test.
   Carrying the object in v0 and a scoped record pin in v1 removes the reload+nop cascade. */
