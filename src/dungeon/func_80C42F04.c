#include "common.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_80082E80.h"

#ifndef NULL
#define NULL 0
#endif


extern void *D_80170858[];

extern s32 D_8003E140[];
extern s32 D_8006CD58[];
extern s32 D_800814A0[];
extern u8 D_80083160[];
extern s16 D_80083228[];
extern s32 D_80083460[];
extern u8 *D_800DCEEC[];
extern u8 D_800DCF5C[];
extern u8 D_8014A000[200000];
extern u8 D_80173F68[];
extern u8 D_801745D8[];
extern u8 D_80174E24[];
extern s32 D_80174E2C[];
extern s16 D_80174E38[];
extern s32 D_80174E3C[];
extern u8 D_80174E3D[];
extern void *D_80174E40[];

extern void func_8003DB94();
extern s32 Control_CD();
extern void func_8003F540();
extern void *func_8003FC64();
extern s32 func_80041588();
extern s32 func_800445E0();
extern s32 func_8004491C();
extern void func_80047738();
extern s32 func_800498A0();
extern s32 func_80069EF8();
extern s32 func_8009A028();
extern s32 func_8009A3D0();
extern s32 func_800A18E8();
extern void *func_800A504C();
extern s32 func_800A56E0();
extern s32 func_800ADC4C();
extern s32 func_800C77D0();
extern void func_80174374();


typedef struct S_80174704_0_pre {
    u16 unk_00;
} S_80174704_0_pre;   /* the 0x2 bytes before arg0 in func_80174704, addressed as arg0[-1] */

typedef struct S_80174704_0 {
    u8 pad_00[0x96];
    union { u16 u; s16 s; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
    u8 pad_9C[0x10];
    union { void * p; u8 * p2; } unk_AC;   /* accessed as both */
    union { s16 s; u16 u; } unk_B0;   /* accessed as both */
} S_80174704_0;   /* arg0 in func_80174704 */

typedef struct S_80174704_1 {
    u8 pad_00[0x13];
    u8 unk_13;
    u8 pad_14[0x8];
    u32 unk_1C;
    u8 pad_20[0xA];
    union { u16 u; s16 s; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x34];
    u8 * unk_60;
    u8 pad_64[0x9];
    s8 unk_6D;
    u8 pad_6E[0x1C];
    u16 unk_8A;
} S_80174704_1;   /* arg3 in func_80174704 */

typedef struct S_80174704_2 {
    u8 unk_00;
} S_80174704_2;   /* D_80174E3C in func_80174704 */

typedef struct S_80174704_3 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0x3];
    void * unk_08;
    union { u8 * p; s32 i; } unk_0C;   /* accessed as both */
    union { void * p; u32 i; } unk_10;   /* accessed as both */
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0xC];
    u8 * unk_2C;
    u8 pad_30[0x78];
    u8 unk_A8;
    u8 unk_A9;
    u8 unk_AA;
} S_80174704_3;   /* var_s0 in func_80174704 */

typedef struct S_80174704_4 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
} S_80174704_4;   /* target in func_80174704 */


typedef struct S_80174704_6 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_80174704_6;   /* repeat_dst in func_80174704 */


typedef struct S_80174704_8_pre {
    u8 * unk_00;
    u8 pad_04[0x10];
} S_80174704_8_pre;   /* the 0x14 bytes before linked2 in func_80174704, addressed as linked2[-1] */

typedef struct S_80174704_8 {
    u8 pad_00[0x2A];
    s16 unk_2A;
} S_80174704_8;   /* linked2 in func_80174704 */

typedef struct S_80174704_9 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_80174704_9;   /* block in func_80174704 */

typedef struct S_80174704_10 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_80174704_10;   /* ((S_80174704_3 *)var_s0)->unk_08 in func_80174704 */

typedef struct S_80174704_11 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_80174704_11;   /* ((S_80174704_1 *)arg3)->unk_60 in func_80174704 */

/* Updates an actor transition through turning, color fading, effects, and replacement. */
void func_80174704(void *action, Rec_D_800E3D7C *position, Rec_D_80082E80 *entity, void *actor) {
    static void *const state_labels[] = {
        &&start, &&init_turn, &&wait_turn, &&fade_color, &&create_effect,
        &&animate_effect, &&wait_motion, &&create_replacement, &&finish_transition
    };
    u8 *object = D_80083160;
    u32 color;
    u8 state;
    s32 next_state;

    state = ((S_80174704_0 *)action)->unk_9B;
    if (state >= 9U) {
        goto done;
    }
    (void)state_labels;
    goto *D_80170858[state];

start:
    {
        next_state = ((S_80174704_0 *)action)->unk_9B + 1;
        goto store_next_state;
    }

init_turn:
    func_80041588(D_80174E24, D_80174E3C, 0);
    ((S_80174704_0 *)action)->unk_B0.s = 0;
    ((S_80174704_0 *)action)->unk_9B++;
    ((S_80174704_1 *)actor)->unk_8A = ((S_80174704_1 *)actor)->unk_2A.u;
    ((S_80174704_1 *)actor)->unk_1C &= 0xFFFBFFFF;

wait_turn:
    {
        s32 direction;
        u16 angle;

        direction = ((D_80083228[0] + ((S_80174704_1 *)actor)->unk_2A.s + 0x100) >> 9) & 7;
        angle = ((S_80174704_1 *)actor)->unk_2A.u;
        if (((S_80174704_2 *)D_80174E3C)->unk_00 == 0) {
            goto direction_not_ready;
        }
        if (direction == 2) {
            goto direction_ready;
        }
direction_not_ready:
        if (direction == 2) {
            goto done;
        }
        ((S_80174704_1 *)actor)->unk_2A.u = angle + 0x200;
        return;

direction_ready:
        func_80041588(D_80174E24, D_80174E3C, 1);
        func_8003F540(0, D_8006CD58[0], 0x04000AD4, 0x05000CC4);
        Control_CD(0x15, func_800445E0(), 0);
        D_80174E3D[0] = 0;
        Control_CD(0xFF, D_8003E140, D_80174E3D);
        func_800C77D0((u8 *)actor - 0x20, position, 8, 0x300);
        ((S_80174704_0 *)action)->unk_96.u = 0x10;
        ((S_80174704_0 *)action)->unk_9B++;
    }

fade_color:
    {
        u16 old_timer = ((S_80174704_0 *)action)->unk_96.u;
        u16 timer = old_timer - 1;
        u8 *target_color;

        ((S_80174704_0 *)action)->unk_96.u = timer;
        if ((s32)(timer << 16) <= 0) {
            u8 cd_done = D_80174E3D[0];
            ((S_80174704_0 *)action)->unk_96.u = old_timer;
            if (cd_done == 0) {
                goto done;
            }
            ((S_80174704_0 *)action)->unk_9B++;
            func_800A56E0(0x300);
            return;
        }

        target_color = D_800DCEEC[func_800498A0(actor)];
        ((S_80174704_3 *)object)->unk_A8 +=
            (((S_80174704_4 *)target_color)->unk_00 - ((S_80174704_3 *)object)->unk_A8) /
            ((S_80174704_0 *)action)->unk_96.s;
        ((S_80174704_3 *)object)->unk_A9 +=
            (((S_80174704_4 *)target_color)->unk_01 - ((S_80174704_3 *)object)->unk_A9) /
            ((S_80174704_0 *)action)->unk_96.s;
        ((S_80174704_3 *)object)->unk_AA +=
            (((S_80174704_4 *)target_color)->unk_02 - ((S_80174704_3 *)object)->unk_AA) /
            ((S_80174704_0 *)action)->unk_96.s;
        return;
    }

create_effect:
    object = func_8003FC64(0x12);
    if (object == NULL) {
        goto done;
    }
    ((S_80174704_3 *)object)->unk_10.p = D_801745D8;
    func_8004491C(object, D_80173F68);
    color = 0x00808080;
    ((S_80174704_0 *)action)->unk_AC.p = object;
    ((S_80174704_10 *)(((S_80174704_3 *)object)->unk_08))->unk_00 = position->unk_00.at00_s32.v;
    ((S_80174704_10 *)(((S_80174704_3 *)object)->unk_08))->unk_04 = position->unk_04.at00_s32.v;
    ((S_80174704_10 *)(((S_80174704_3 *)object)->unk_08))->unk_08 = position->unk_08.at00_s32.v;
    {
        S_80174704_6 *effect_pos = ((S_80174704_3 *)object)->unk_08;
        s32 pos_z = position->unk_08.at00_s32.v;

        D_80174E38[0] = -0x10;
        effect_pos->unk_08 = pos_z;
    }
    object = ((S_80174704_3 *)object)->unk_0C.p;
    ((S_80174704_3 *)object)->unk_1E = 0x1000;
    ((S_80174704_3 *)object)->unk_1C = 0x1000;
    ((S_80174704_3 *)object)->unk_0C.i = color;
    {
        s16 effect_index = func_800498A0(actor) - 1;

        if (effect_index < 0) {
            effect_index = func_80069EF8() % 3;
        }
        func_8003DB94(object, D_8014A000 + D_80174E2C[effect_index], 0);
    }
    entity->unk_14.at00_u16.v |= 0x80;
    ((S_80174704_0 *)action)->unk_96.u = 0;
    next_state = ((S_80174704_0 *)action)->unk_9B + 1;
store_next_state:
    ((S_80174704_0 *)action)->unk_9B = next_state;
    return;

animate_effect:
    {
        u16 old_timer = ((S_80174704_0 *)action)->unk_96.u;
        ((S_80174704_0 *)action)->unk_96.u = old_timer + 1;
        if ((s16)old_timer < 30) {
            s32 angle_step = ((S_80174704_0 *)action)->unk_B0.s;

            func_80174374(action, position, entity, actor,
                         (s16)(angle_step << 7), 0);
            ((S_80174704_0 *)action)->unk_B0.u++;
        }
    }
    object = ((S_80174704_0 *)action)->unk_AC.p2;
    object = ((S_80174704_3 *)object)->unk_0C.p;
    if (((S_80174704_3 *)object)->unk_14 & 0xE000) {
        ((S_80174704_0 *)action)->unk_96.u = 0x10;
        ((S_80174704_0 *)action)->unk_9B++;
        func_800A18E8(((S_80174704_1 *)actor)->unk_13, 3);
        func_8009A3D0(entity->unk_24, entity->unk_25, 0x300);
        func_8009A028(actor);
        object = (u8 *)actor - 0x20;
        ((S_80174704_3 *)object)->unk_10.i |= 0x80000000;
    }

wait_motion:
    if (((S_80174704_0 *)action)->unk_9B != 6) {
        goto done;
    }
    if (func_800ADC4C(position, D_80174E40[0], D_80174E38[0], D_800DCF5C) == 0) {
        goto done;
    }
    ((S_80174704_0 *)action)->unk_96.u = 0x10;
    ((S_80174704_0 *)action)->unk_9B++;
    func_800A18E8(((S_80174704_1 *)actor)->unk_13, 3);
    func_8009A3D0(entity->unk_24, entity->unk_25, 0x300);
    func_8009A028(actor);
    object = (u8 *)actor - 0x20;
    ((S_80174704_3 *)object)->unk_10.i |= 0x80000000;
    return;

create_replacement:
    {
        u8 *replacement = func_800A504C(entity, actor);
        ((S_80174704_1 *)actor)->unk_60 = replacement;
        if (replacement == NULL) {
            goto done;
        }
        ((S_80174704_0 *)action)->unk_96.u = 0x10;
        ((S_80174704_0 *)action)->unk_9B++;
        ((S_80174704_11 *)(((S_80174704_1 *)actor)->unk_60))->unk_2A = ((S_80174704_1 *)actor)->unk_2A.u;
        {
            u8 *replacement_actor = ((S_80174704_1 *)actor)->unk_60;
            s32 direction;
            u8 *direction_frames;

            object = ((S_80174704_8_pre *)replacement_actor)[-1].unk_00;
            direction = ((D_80083228[0] + ((S_80174704_8 *)replacement_actor)->unk_2A + 0x100) >> 9) & 7;
            direction_frames = ((S_80174704_3 *)object)->unk_2C;
            func_80047738(object, direction_frames[direction], ((S_80174704_3 *)object)->unk_04);
        }
        ((S_80174704_3 *)object)->unk_14 &= 0xFFFE;
    }

finish_transition:
    {
        u16 timer = ((S_80174704_0 *)action)->unk_96.u - 1;
        ((S_80174704_0 *)action)->unk_96.u = timer;
        if ((s32)(timer << 16) > 0) {
            goto done;
        }
    }
    {
        u8 *actor_counts;

        ((S_80174704_11 *)(((S_80174704_1 *)actor)->unk_60))->unk_2A = ((S_80174704_1 *)actor)->unk_8A;
        ((S_80174704_0_pre *)action)[-1].unk_00 |= 0x8000;
        D_800814A0[0] |= 0x8000;
        actor_counts = (u8 *)D_80083460;
        ((S_80174704_9 *)actor_counts)->unk_0A--;
        ((S_80174704_1 *)actor)->unk_6D = 0;
    }

done:
    return;
}
