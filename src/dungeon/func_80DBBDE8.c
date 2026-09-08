#include "common.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800E3D7C.h"


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
extern u8 D_80171E20[];
extern s32 D_8008346C[];
extern s16 D_80083228[5];
extern void func_8009C12C(void *, void *, s16, s32);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);
extern void func_80047784(void *, u8, s32);
extern u8 D_801753E4[];

typedef struct S_801735E8_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
} S_801735E8_0;   /* base0 in func_801735E8 */



typedef struct S_801735E8_3 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_801735E8_3;   /* arg1 in func_801735E8 */

/* Advances the actor's staged animation sequence and handles completion. */
void func_801735E8(void *action_data, S_801735E8_3 *motion, Rec_D_80082E80 *animation, Rec_D_800E3D7C *actor) {
    S_801735E8_0 *action;
    u16 phase_value;
    u16 elapsed_ticks;
    s32 phase;
    action = action_data;

    phase = action->unk_9B;
    if (phase == 1) {
        goto state1;
    }
    if (phase < 2) {
        if (phase == 0) {
            goto state0;
        }
        goto done;
    }
    if (phase == 2) {
        goto state2;
    }
    if (phase == 3) {
        goto state3;
    }
    goto done;

state0:
    if (animation->unk_14.at00_u16.v & 0x8000) {
        action->unk_9B = 3U;
        animation->unk_14.at00_u16.v = (u16) (animation->unk_14.at00_u16.v | 0x6000);
        func_8009C12C(actor, animation, actor->unk_2A.as_s16, 1);
        goto done;
    }
    motion->unk_14 = 0;
    motion->unk_10 = 0;
    motion->unk_0C = 0;
    phase_value = action->unk_9B;
    action->unk_96 = 0U;
    action->unk_9B = (u8) (phase_value + 1);
    goto done;

state1:
    elapsed_ticks = action->unk_96 + 1;
    action->unk_96 = elapsed_ticks;
    if ((s16) elapsed_ticks != 4 && !(animation->unk_14.at00_u16.v & 0xE000)) {
        goto done;
    }
    animation->unk_2C.as_pm = &D_801753E4;
    func_80047784(animation, D_801753E4[(((s32) (*D_80083228 + actor->unk_2A.as_s16 + 0x100) >> 9) & 7)], 0);
    func_800A56E0(0x808);
    phase_value = action->unk_9B;
    action->unk_96 = 0U;
    action->unk_9B = (u8) (phase_value + 1);
    goto done;

state2:
    phase_value = action->unk_96 + 1;
    action->unk_96 = phase_value;
    if ((s16) phase_value != 4 && !(animation->unk_14.at00_u16.v & 0xE000)) {
        goto done;
    }
    func_8009C12C(actor, animation, actor->unk_2A.as_s16, 1);
    phase_value = action->unk_9B;
    action->unk_96 = 0U;
    action->unk_9B = (u8) (phase_value + 1);
    goto done;

state3:
    if (animation->unk_14.at00_u16.v & 0xE000) {
        func_800AD594(actor, 0x100);
        action->unk_8C = D_80171E20;
        *D_8008346C = 0;
        func_800A4ACC(actor);
        actor->unk_44.at02_u16.v = (u16) (actor->unk_44.at02_u16.v & 0x7FFF);
    }

done:
    return;
}
