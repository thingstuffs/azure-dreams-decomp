#include "common.h"
#include "records/Rec_func_800AA258_arg2.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_800814A8.h"

typedef struct S_80174788_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x2];
    u16 unk_92;
    u8 pad_94[0x7];
    u8 unk_9B;
    u8 pad_9C[0x2];
    s16 unk_9E;
    u8 pad_A0[0x2];
    u16 unk_A2;
} S_80174788_0;   /* arg0 in func_80174788 */


typedef struct S_80174788_2 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_80174788_2;   /* counter_base in func_80174788 */


typedef struct S_80174788_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x6];
    u16 unk_0A;
} S_80174788_4;   /* global_base in func_80174788 */


typedef struct S_80174788_6 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_80174788_6;   /* counter_base2 in func_80174788 */



extern void func_80047784();
extern s32 func_8009A180();
extern s32 func_800A2C34();
extern void func_800A9A04();
extern void func_800A9A0C();
extern void func_800AA258();
extern s32 func_800AA6B4();
extern void func_800AA888();
extern void func_80174A68();

extern void *D_800814A8;
extern s16 D_80083228;
extern s32 D_80083460;
extern u8 D_800E2428[];
extern u8 D_800E2430[];
extern u8 D_80171A80[];

/* Advance an actor action through animation completion and status checks. */
void func_80174788(void *action, s32 actor_index, void *sprite, void *actor)
{
    s32 action_state;
    u16 reset_offset;
    u16 value_before_reset;
    s32 actor_flags;
    u8 *shared_state;

    action_state = ((S_80174788_0 *)action)->unk_9B;
    if (action_state == 1) {
        goto state_one;
    }
    if ((s32)action_state < 2) {
        if (action_state == 0) {
            goto state_zero;
        }
        goto done;
    }
    if (action_state == 2) {
        goto state_two;
    }
    goto done;

state_zero:
    if (!(((Rec_func_800AA258_arg2 *)sprite)->unk_14 & 0xE000)) {
        goto done;
    }
    {
        u8 *animation_counters;

        animation_counters = (u8 *)&D_80083460;
        ((S_80174788_2 *)animation_counters)->unk_0A--;
    }
    (*(void * *)((u8 *)sprite + 0x2C)) = D_800E2428;
    func_80047784(sprite,
                  D_800E2428[((D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9) & 7],
                  0);
    goto increment_state;

state_one:
    shared_state = (u8 *)&D_80083460;
    if (((S_80174788_4 *)shared_state)->unk_02 & 0x1000) {
        goto done;
    }
    if (((Rec_D_800E3D7C *)actor)->unk_64.as_s16 != 0) {
        if (func_800AA6B4(action, actor_index, sprite, 0) != 0) {
            goto done;
        }
    }
    if ((func_800A2C34(actor) << 16) != 0) {
        goto done;
    }
    actor_flags = ((Rec_D_800E3D7C *)actor)->unk_1C.as_s32;
    if (actor_flags & 0x100) {
        func_800AA258(action, actor_index, sprite, actor);
        goto done;
    }
    if (actor_flags & 0x80000) {
        func_800AA888(action, actor_index, sprite, actor);
        value_before_reset = ((S_80174788_0 *)action)->unk_92;
        reset_offset = ((S_80174788_0 *)action)->unk_A2;
        ((S_80174788_0 *)action)->unk_A2 = 0;
        ((S_80174788_0 *)action)->unk_9E = 0;
        ((S_80174788_0 *)action)->unk_92 = value_before_reset - reset_offset;
        func_80174A68(action, actor_index, sprite, actor);
        goto done;
    }
    if (((Rec_D_800E3D7C *)actor)->unk_6D.as_s8 == 0) {
        goto done;
    }
    if ((func_800A2C34(actor) << 16) != 0) {
        if ((func_8009A180(actor, ((Rec_D_800814A8 *)D_800814A8)->unk_58.as_s32 + 0x20) << 16) != 0) {
            goto done;
        }
    }
    func_800A9A0C(actor);
    func_800A9A04(actor);
    if (((Rec_D_800E3D7C *)actor)->unk_24.at01_u8.v == 0) {
        goto done;
    }
    (*(void * *)((u8 *)sprite + 0x2C)) = D_800E2430;
    func_80047784(sprite,
                  D_800E2430[((D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9) & 7],
                  0);
    ((Rec_D_800E3D7C *)actor)->unk_1C.as_s32 |= 0x40000;
    ((S_80174788_4 *)shared_state)->unk_0A++;

increment_state:
    ((S_80174788_0 *)action)->unk_9B++;
    goto done;

state_two:
    if (!(((Rec_func_800AA258_arg2 *)sprite)->unk_14 & 0xE000)) {
        goto done;
    }
    {
        u8 *animation_counters;

        animation_counters = (u8 *)&D_80083460;
        ((S_80174788_6 *)animation_counters)->unk_0A--;
    }
    ((Rec_D_800E3D7C *)actor)->unk_1C.as_s32 &= ~8;
    ((S_80174788_0 *)action)->unk_8C = D_80171A80;

done:
    return;
}
