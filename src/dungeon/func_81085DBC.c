#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"


extern void func_80047784(void *, s32, s32);
extern void func_8009C12C(void *attacker_in, void *tile_in, s16 direction, s16 distance);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);
extern s32 func_8017589C(void *, void *, void *);

extern M2C_UNK D_80170E94;
extern u8 D_80175F10[8];
extern u8 D_80175F40[8];
extern u8 D_80175F68[8];


typedef struct S_801735BC_0 {
    u8 pad_00[0x96];
    u16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
    u8 pad_9C[0x12];
    u8 unk_AE;
    u8 pad_AF[0x1];
    s32 unk_B0;
} S_801735BC_0;   /* state_work in func_801735BC */

typedef struct S_801735BC_1 {
    u8 pad_00[0x14];
    u32 unk_14;
    u8 pad_18[0x12];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
} S_801735BC_1;   /* actor in func_801735BC */


void func_801735BC(void *incoming_state_work, void *incoming_entity, void *incoming_object, void *incoming_actor)
{
        /* MATCH: the local state join must retain state_work in retail's s2. */
    void *state_work = incoming_state_work;
    EntityRec *entity = incoming_entity;
    void *object = incoming_object;
    void *actor = incoming_actor;
    u8 state;
    u16 flags;
    u16 flags3;
    u16 timer;
    s32 gate;

    state = ((S_801735BC_0 *)state_work)->unk_9B;
    switch (state) {

    case 0:
        do {
            timer = ((S_801735BC_0 *)state_work)->unk_96 - 1;
        } while (0);
        ((S_801735BC_0 *)state_work)->unk_96 = timer;
        if ((s16)timer > 0) {
            return;
        }
        (*(u8 * *)((u8 *)object + (0x2C))) = D_80175F40;
        func_80047784(object,
            D_80175F40[((gameWork.view.viewAngle + ((S_801735BC_1 *)actor)->unk_2A + 0x100) >> 9) & 7],
            0);
        entity->flags14 = 0;
        entity->unk_10 = 0;
        entity->unk_0C = 0;
        goto Ladvance;

    case 1:
        flags = ((Rec_D_80082E80 *)object)->unk_14.at00_u16.v;
        if (flags & 0x8000) {
            ((S_801735BC_0 *)state_work)->unk_9B = 4;
            ((Rec_D_80082E80 *)object)->unk_14.at00_u16.v |= 0x6000;
            if (((S_801735BC_0 *)state_work)->unk_AE != 2) {
                return;
            }
            func_8009C12C(actor, object, ((S_801735BC_1 *)actor)->unk_2A, 1);
            return;
        }
        if (((Rec_D_80082E80 *)object)->unk_04.as_s8 != 2) {
            return;
        }
        if (!(flags & 0x1000)) {
            return;
        }
        func_800A56E0(0x808);
        ((S_801735BC_0 *)state_work)->unk_B0 = func_8017589C(state_work, entity, object);
        ((S_801735BC_0 *)state_work)->unk_9B++;
        return;

    case 2:
        if (!(((Rec_D_80082E80 *)object)->unk_14.at00_u16.v & 0xE000)) {
            return;
        }
        (*(u8 * *)((u8 *)object + (0x2C))) = D_80175F68;
        func_80047784(object,
            D_80175F68[((gameWork.view.viewAngle + ((S_801735BC_1 *)actor)->unk_2A + 0x100) >> 9) & 7],
            0);
        ((Rec_D_80082E80 *)object)->unk_14.at00_u16.v |= 0x0800;
Ladvance:
        ((S_801735BC_0 *)state_work)->unk_9B++;
        return;

    case 3:
        flags3 = ((Rec_D_80082E80 *)object)->unk_14.at00_u16.v;
        if (flags3 & 0x8000) {
            (*(u8 * *)((u8 *)object + (0x2C))) = D_80175F68;
            func_80047784(object,
                D_80175F68[((gameWork.view.viewAngle + ((S_801735BC_1 *)actor)->unk_2A + 0x100) >> 9) & 7],
                0);
            ((Rec_D_80082E80 *)object)->unk_14.at00_u16.v |= 0x0800;
            return;
        }
        gate = flags3 & 0x6000;
        goto Lgate;

    case 4:
        gate = ((Rec_D_80082E80 *)object)->unk_14.at00_u16.v & 0xE000;
Lgate:
        if (gate == 0) {
            return;
        }
        (*(u8 * *)((u8 *)object + (0x2C))) = D_80175F10;
        func_80047784(object,
            D_80175F10[((gameWork.view.viewAngle + ((S_801735BC_1 *)actor)->unk_2A + 0x100) >> 9) & 7],
            0);
        ((S_801735BC_0 *)state_work)->unk_AE = 0;
        ((S_801735BC_1 *)actor)->unk_14 &= ~0x40000000;
        entity->flags14 = 0;
        entity->unk_10 = 0;
        entity->unk_0C = 0;
        func_800A2B04(entity, ((Rec_D_80082E80 *)object)->unk_24, ((Rec_D_80082E80 *)object)->unk_25);
        func_800AD594(actor, 0x800);
        ((S_801735BC_1 *)actor)->unk_46 &= 0x7FFF;
        (*(M2C_UNK * *)((u8 *)state_work + (0x8C))) = &D_80170E94;
        dungeonStatus.unk_0C = 0;
        break;
    default:
        return;
    }
}

/* MECHANISM: two edits closed this from the prior aligned-3 plateau.
   (1) LOCAL JOIN, not a phantom noreturn sibcall: retail's `j 0x801737F0` out of
   case 3 lands on the SHARED `beqz` of case 4, so the `andi v0,v1,0x6000` in that
   j-delay is a live gate value, not dead code — written as `gate = flags3 & 0x6000;
   goto Lgate;` with `Lgate:` between case 4's mask and the shared test.
   (2) SPLIT (one name per live range): case 1 and case 3 must NOT share one `flags`
   local — case 1's copy is live across `lb $v1,4($s0)`, so the shared pseudo inherits
   that $v1 conflict and case 3's load colors $a0 instead of retail's $v1.
   Frame unchanged; dispatch is now a real switch (own .rdata table),
   args (state_work,entity,object,incoming_actor) -> s2,s3,s0,s1, tail joins via noreturn func_80173768/894. */
