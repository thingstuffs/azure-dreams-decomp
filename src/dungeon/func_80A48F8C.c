#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800E3D7C.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern u8 D_8017140C[];
extern s32 D_8008346C[];
extern void *D_800E3DE8[];
extern u8 D_8017587C;
extern s16 D_80083228[5];
extern s32 func_8009C12C(void *, void *, s16, s32);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A4ACC(void *);
extern void func_800A56E0(u32);
extern void func_800AD594(void *, s32);
extern void func_80047784(void *, u8, s32);

typedef struct S_8017278C_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
} S_8017278C_0;   /* arg0 in func_8017278C */




/* Advances an actor action through animation setup, delay, and completion. */
void func_8017278C(S_8017278C_0 *action, Rec_D_800E3D7C *motion, Rec_D_80082E80 *sprite, void *actor) {
    u16 ticks_left;
    s32 initial_state;
    s32 state;
    u8 *direction_frames;

    initial_state = 1;
    state = action->unk_9B;
    if (state == initial_state) {
        goto state_1;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_0_set;
        }
        goto cleanup;
    } else {
        if (state == 2) {
            goto state_2;
        }
        if (state != 3) {
            goto cleanup;
        }
        goto state_3;
    }

state_0_set:
    action->unk_9B = initial_state;

state_1:
    if (sprite->unk_14.at00_u16.v & 0x8000) {
        action->unk_9B = 3U;
        sprite->unk_14.at00_u16.v = (u16) (sprite->unk_14.at00_u16.v | 0x6000);
        func_8009C12C(actor, sprite, ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16, 1);
        goto cleanup;
    }

state_0:
    direction_frames = &D_8017587C;
    motion->unk_14.as_s32 = 0;
    motion->unk_10.at00_s32.v = 0;
    motion->unk_0C.as_s32 = 0;
    sprite->unk_2C.as_pu8 = direction_frames;
    func_80047784(sprite, direction_frames[((s32) (*D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9) & 7], 0);
    action->unk_96 = 9;
    action->unk_9B++;
    goto cleanup;

state_2:
    ticks_left = action->unk_96 - 1;
    action->unk_96 = ticks_left;
    if ((ticks_left << 0x10) > 0) {
        goto cleanup;
    }
    func_800A56E0(0x804);
    func_8009C12C(actor, sprite, ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16, 1);
    action->unk_9B++;
    goto cleanup;

state_3:
    if (sprite->unk_14.at00_u16.v & 0xE000) {
        func_800A2B04(motion, sprite->unk_24, sprite->unk_25);
        func_800AD594(actor, 0x100);
        action->unk_8C = D_8017140C;
        *D_8008346C = 0;
        func_800A4ACC(actor);
        if (((Rec_D_800E3D7C *)actor)->unk_6D.as_s8 == 0) {
            ((Rec_D_800E3D7C *)actor)->unk_44.at02_u16.v = (u16) (((Rec_D_800E3D7C *)actor)->unk_44.at02_u16.v & 0x7FFF);
        } else {
            *D_800E3DE8 = actor - 0x20;
        }
    }

cleanup:
    return;
}
