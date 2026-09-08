#include "common.h"
#include "records/Rec_D_800814A8.h"

typedef struct S_80173D4C_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xB];
    u8 unk_9B;
} S_80173D4C_0;   /* arg0 in func_80173D4C */

typedef struct S_80173D4C_1 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0x10];
    s8 unk_26;
} S_80173D4C_1;   /* arg2 in func_80173D4C */

typedef struct S_80173D4C_2 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x5];
    u8 unk_25;
    u8 pad_26[0x4];
    s16 unk_2A;
    u8 pad_2C[0x38];
    s16 unk_64;
    u8 pad_66[0x7];
    s8 unk_6D;
} S_80173D4C_2;   /* arg3 in func_80173D4C */

typedef struct S_80173D4C_3 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_80173D4C_3;   /* counter_base in func_80173D4C */

typedef struct S_80173D4C_4 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_80173D4C_4;   /* status in func_80173D4C */


typedef struct S_80173D4C_6 {
    u8 pad_00[0x26];
    s8 unk_26;
} S_80173D4C_6;   /* origin in func_80173D4C */



extern s32 func_80042900(void *, s32);
extern void func_80042B68(void *, s32);
extern void func_80047784(void *, s32, s32);
extern s32 func_8009A180(void *, void *);
extern s16 func_8009FD40(void *, void *);
extern s32 func_800A2C34(void *);
extern s32 func_800A6D30(void *);
extern void func_800A9A04(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern s32 func_800AA6B4(void *, void *, void *, void *);
extern void func_800AA79C(void *, void *, void *, void *);
extern void func_800AA888(void *, void *, void *, void *);
extern void func_801743E8(void *, void *, void *, void *);

extern void *D_800814A8;
extern u8 D_80082E80[];
extern s16 D_80083228;
extern s32 D_80083460;
extern s32 D_80171728;
extern u8 D_80174E4C[];
extern u8 D_80174E54[];

/* Advances the actor action state and updates its directional animation. */
void func_80173D4C(void *action_in, void *context_in, void *sprite_in, void *actor_in)
{
    void *action;
    register void *context ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    register void *sprite ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    void *actor;
    s32 state;
    register u8 *direction_table ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register void *actor_to_check ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    u8 *status;
    s32 actor_flags;

    action = action_in;
    context = context_in;
    sprite = sprite_in;
    state = ((S_80173D4C_0 *)action)->unk_9B;
    actor = actor_in;
    if (state == 1) {
        goto active;
    }
    if (state >= 2) {
        goto state_ge_two;
    }
    if (state == 0) {
        goto state_zero;
    }
    goto done;

state_ge_two:
    if (state == 2) {
        goto state_two;
    }
    goto done;

state_zero:
    if (!(((S_80173D4C_1 *)sprite)->unk_14 & 0xE000)) {
        goto done;
    }
    direction_table = D_80174E4C;
    (*(void * *)((u8 *)sprite + 0x2C)) = direction_table;
    func_80047784(sprite,
        direction_table[((D_80083228 + ((S_80173D4C_2 *)actor)->unk_2A + 0x100) >> 9) & 7],
        0);
    {
        u8 *counter_base;

        counter_base = (u8 *)&D_80083460;
        ((S_80173D4C_3 *)counter_base)->unk_0A =
            ((S_80173D4C_3 *)counter_base)->unk_0A - 1;
    }
    goto increment_state;

active:
    if ((func_80042900(actor, 1) << 16) == 0) {
        goto update_table;
    }
    status = (u8 *)&D_80083460;
    if (((S_80173D4C_4 *)status)->unk_02 & 0x1000) {
        goto done;
    }
    if (((S_80173D4C_2 *)actor)->unk_64 != 0) {
        if (func_800AA6B4(action, context, sprite, 0) != 0) {
            goto done;
        }
    }
    if (((S_80173D4C_2 *)actor)->unk_25 == 0) {
        if (((S_80173D4C_4 *)status)->unk_02 & 0x2008) {
            goto done;
        }
        func_800AA79C(action, context, sprite, actor);
        goto done;
    }
    if ((func_800A2C34(actor) << 16) != 0) {
        goto done;
    }
    actor_flags = ((S_80173D4C_2 *)actor)->unk_1C;
    if (actor_flags & 0x100) {
        func_800AA258(action, context, sprite, actor);
        goto done;
    }
    if (actor_flags & 0x80000) {
        func_800AA888(action, context, sprite, actor);
        func_801743E8(action, context, sprite, actor);
        goto done;
    }
    if (((S_80173D4C_2 *)actor)->unk_6D == 0) {
        goto done;
    }
    if ((func_800A2C34(actor) << 16) != 0) {
        if ((func_8009A180(actor,
                (u8 *)((Rec_D_800814A8 *)D_800814A8)->unk_58.as_pv + 0x20) << 16) != 0) {
            goto done;
        }
    }
    func_800A9A0C(actor);
    func_800A9A04(actor);
    if ((func_80042900(actor, 1) << 16) != 0) {
        s8 coordinate = ((S_80173D4C_1 *)sprite)->unk_26;
        u8 *origin = D_80082E80;

        if ((coordinate != ((S_80173D4C_6 *)origin)->unk_26) || (coordinate < 0)) {
            if (func_8009FD40(origin, sprite) >= 2) {
                actor_to_check = actor;
                goto final_check_call;
            }
            if (!(func_800A6D30(actor) & 7)) {
                func_80042B68(actor, 1);
            }
        } else {
            if (!(func_800A6D30(origin) & 7)) {
                func_80042B68(actor, 1);
            }
        }
    }

    actor_to_check = actor;
final_check_call:
    if ((func_80042900(actor_to_check, 1) << 16) != 0) {
        goto done;
    }

update_table:
    direction_table = D_80174E54;
    (*(void * *)((u8 *)sprite + 0x2C)) = direction_table;
    func_80047784(sprite,
        direction_table[((D_80083228 + ((S_80173D4C_2 *)actor)->unk_2A + 0x100) >> 9) & 7],
        0);
    if (((S_80173D4C_1 *)sprite)->unk_14 & 0x8000) {
        goto assign_owner;
    }
    {
        register u8 *counter_base ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */

        counter_base = (u8 *)&D_80083460;
        ((S_80173D4C_3 *)counter_base)->unk_0A++;
    }

increment_state:
    ((S_80173D4C_0 *)action)->unk_9B++;
    goto done;

state_two:
    if (!(((S_80173D4C_1 *)sprite)->unk_14 & 0xE000)) {
        goto done;
    }
    {
        register u8 *counter_base ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */

        counter_base = (u8 *)&D_80083460;
        ((S_80173D4C_3 *)counter_base)->unk_0A--;
    }

assign_owner:
    ((S_80173D4C_0 *)action)->unk_8C = &D_80171728;

done:
    return;
}

/* MECHANISM: Removing value-rewriting arg/table keeps recovered the 40-byte frame,
   retail save order, and v0-destination symbolic indexing. Nonvolatile counter RMW
   lets sh fill the jump delay; duplicated A6D30 paths merge with predecessor-held a0.
   A pinned $a0 final-check local exposes the call-only label needed by word 160. */
