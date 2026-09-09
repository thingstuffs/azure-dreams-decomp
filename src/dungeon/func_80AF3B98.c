#include "common.h"
#include "records/Rec_D_80082E80.h"

#ifndef NULL
#define NULL 0
#endif


typedef struct DungeonCopy3 {
    s32 x;
    s32 y;
    s32 z;
} DungeonCopy3;

typedef struct DungeonChild {
    s32 x;
    s32 y;
    s32 z;
} DungeonChild;

typedef struct DungeonTail {
    u8 pad0[0x0C];
    u32 color;
    u8 pad10[4];
    u16 flags;
    u8 pad16[6];
    u16 value1c;
    u16 value1e;
} DungeonTail;

typedef struct DungeonEffect {
    u8 pad0[8];
    DungeonChild *child;
    DungeonTail *tail;
    void *resource;
} DungeonEffect;

extern void *D_80170908[];

extern s32 D_8003E140[];
extern s32 D_8006CD58[];
extern s32 D_800814A0;
extern u8 D_80083160[];
extern s16 D_80083228;
extern u8 D_80083460[];
extern u8 *D_800DCEEC[];
extern u8 D_800DCF5C[];
extern u8 D_8014A000[200000];
extern u8 D_80174BE4[];
extern u8 D_8017526C[];
extern u8 D_801759F8[];
extern s32 D_80175A00[];
extern s16 D_80175A18;
extern u8 D_80175A80[];
extern u8 D_80175A81;
extern void *D_80175A84;

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
extern s32 func_80174F24();


typedef struct S_80175398_0_pre {
    u16 unk_00;
} S_80175398_0_pre;   /* the 0x2 bytes before arg0 in func_80175398, addressed as arg0[-1] */

typedef struct S_80175398_0 {
    u8 pad_00[0x96];
    union { u16 u; s16 s; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
    u8 pad_9C[0xC];
    union { void * p; u8 * p2; } unk_A8;   /* accessed as both */
    s16 unk_AC;
} S_80175398_0;   /* arg0 in func_80175398 */

typedef struct S_80175398_1 {
    u8 pad_00[0x13];
    u8 unk_13;
    u8 pad_14[0x16];
    union { u16 u; s16 s; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x34];
    u8 * unk_60;
    u8 pad_64[0x9];
    s8 unk_6D;
    u8 pad_6E[0x1C];
    u16 unk_8A;
} S_80175398_1;   /* arg3 in func_80175398 */

typedef struct S_80175398_2 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0x7];
    u8 * unk_0C;
    u32 unk_10;
    u16 unk_14;
    u8 pad_16[0x16];
    u8 * unk_2C;
    u8 pad_30[0x78];
    u8 unk_A8;
    u8 unk_A9;
    u8 unk_AA;
} S_80175398_2;   /* var_s0 in func_80175398 */

typedef struct S_80175398_3 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
} S_80175398_3;   /* target in func_80175398 */


typedef struct S_80175398_5_pre {
    u8 * unk_00;
    u8 pad_04[0x10];
} S_80175398_5_pre;   /* the 0x14 bytes before linked2 in func_80175398, addressed as linked2[-1] */

typedef struct S_80175398_5 {
    u8 pad_00[0x2A];
    s16 unk_2A;
} S_80175398_5;   /* linked2 in func_80175398 */

typedef struct S_80175398_6 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_80175398_6;   /* counter in func_80175398 */

typedef struct S_80175398_7 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_80175398_7;   /* ((S_80175398_1 *)arg3)->unk_60 in func_80175398 */

/* Advances the actor transition, updating effects and restoring the linked actor's facing. */
void func_80175398(void *transition, void *position, Rec_D_80082E80 *record, void *actor) {
    static void *const state_labels[] = {
        &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4,
        &&jt_c5, &&jt_c6, &&jt_c7, &&jt_c8
    };
    u8 *object_data = D_80083160;
    u8 state;
    u32 next_state;

    state = ((S_80175398_0 *)transition)->unk_9B;
    if (state >= 9U) {
        goto done;
    }
    (void)state_labels;
    goto *D_80170908[state];

jt_c0:
    next_state = ((S_80175398_0 *)transition)->unk_9B + 1;
    goto store_next_state;

jt_c1:
    func_80041588(D_801759F8, D_80175A80, 0);
    ((S_80175398_0 *)transition)->unk_AC = 0;
    ((S_80175398_0 *)transition)->unk_9B++;
    ((S_80175398_1 *)actor)->unk_8A = ((S_80175398_1 *)actor)->unk_2A.u;

jt_c2:
    {
        s32 direction;
        u16 angle;

        direction = ((D_80083228 + ((S_80175398_1 *)actor)->unk_2A.s + 0x100) >> 9) & 7;
        angle = ((S_80175398_1 *)actor)->unk_2A.u;
        if (D_80175A80[0] == 0) {
            goto direction_not_ready;
        }
        if (direction == 2) {
            goto direction_ready;
        }
direction_not_ready:
        if (direction == 2) {
            goto done;
        }
        ((S_80175398_1 *)actor)->unk_2A.u = angle + 0x200;
        return;

direction_ready:
        func_80041588(D_801759F8, D_80175A80, 1);
        func_8003F540(0, D_8006CD58[0], 0x04000AD4, 0x05000CC4);
        Control_CD(0x15, func_800445E0(), 0);
        D_80175A81 = 0;
        Control_CD(0xFF, D_8003E140, &D_80175A81);
        func_800C77D0((u8 *)actor - 0x20, position, 8, 0x300);
        ((S_80175398_0 *)transition)->unk_96.u = 0x10;
        ((S_80175398_0 *)transition)->unk_9B++;
    }

jt_c3:
    {
        u16 old_timer = ((S_80175398_0 *)transition)->unk_96.u;
        u16 timer = old_timer - 1;
        u8 *target_color;

        ((S_80175398_0 *)transition)->unk_96.u = timer;
        if ((s32)(timer << 16) <= 0) {
            u8 cd_finished = D_80175A81;
            ((S_80175398_0 *)transition)->unk_96.u = old_timer;
            if (cd_finished == 0) {
                goto done;
            }
            ((S_80175398_0 *)transition)->unk_9B++;
            func_800A56E0(0x300);
            return;
        }

        target_color = D_800DCEEC[func_800498A0(actor)];
        ((S_80175398_2 *)object_data)->unk_A8 +=
            (((S_80175398_3 *)target_color)->unk_00 - ((S_80175398_2 *)object_data)->unk_A8) /
            ((S_80175398_0 *)transition)->unk_96.s;
        ((S_80175398_2 *)object_data)->unk_A9 +=
            (((S_80175398_3 *)target_color)->unk_01 - ((S_80175398_2 *)object_data)->unk_A9) /
            ((S_80175398_0 *)transition)->unk_96.s;
        ((S_80175398_2 *)object_data)->unk_AA +=
            (((S_80175398_3 *)target_color)->unk_02 - ((S_80175398_2 *)object_data)->unk_AA) /
            ((S_80175398_0 *)transition)->unk_96.s;
        return;
    }

jt_c4:
    object_data = func_8003FC64(0x12);
    if (object_data == NULL) {
        goto done;
    }
    {
        DungeonEffect *effect = (DungeonEffect *)object_data;

        effect->resource = D_8017526C;
        func_8004491C(effect, D_80174BE4);
        ((S_80175398_0 *)transition)->unk_A8.p = effect;
        effect->child->x = ((DungeonCopy3 *)position)->x;
        effect->child->y = ((DungeonCopy3 *)position)->y;
        D_80175A18 = -2;
        effect->child->z = ((DungeonCopy3 *)position)->z;
        object_data = (u8 *)effect->tail;
        ((DungeonTail *)object_data)->value1e = 0x1000;
        ((DungeonTail *)object_data)->value1c = 0x1000;
        ((DungeonTail *)object_data)->color = 0x00808080;
    }
    {
        s16 resource_index = func_800498A0(actor) - 1;

        if (resource_index < 0) {
            s32 random_value = func_80069EF8();

            resource_index = random_value % 3;
        }
        func_8003DB94(object_data, D_8014A000 + D_80175A00[resource_index], 0);
    }
    record->unk_14.at00_u16.v |= 0x80;
    ((S_80175398_0 *)transition)->unk_96.u = 0;
    next_state = ((S_80175398_0 *)transition)->unk_9B + 1;
store_next_state:
    ((S_80175398_0 *)transition)->unk_9B = next_state;
    return;

jt_c5:
    {
        u16 old_timer = ((S_80175398_0 *)transition)->unk_96.u;
        ((S_80175398_0 *)transition)->unk_96.u = old_timer + 1;
        if ((s16)old_timer < 30) {
            s16 update_count = 0;
            do {
                func_80174F24(transition, position, record, actor);
                update_count++;
            } while (update_count < 8);
        }
    }
    object_data = ((S_80175398_0 *)transition)->unk_A8.p2;
    object_data = ((S_80175398_2 *)object_data)->unk_0C;
    if (((S_80175398_2 *)object_data)->unk_14 & 0xE000) {
        ((S_80175398_0 *)transition)->unk_9B++;
    }

jt_c6:
    if (((S_80175398_0 *)transition)->unk_9B != 6) {
        goto done;
    }
    if (func_800ADC4C(position, D_80175A84, D_80175A18, D_800DCF5C) == 0) {
        goto done;
    }
    ((S_80175398_0 *)transition)->unk_96.u = 0x10;
    ((S_80175398_0 *)transition)->unk_9B++;
    func_800A18E8(((S_80175398_1 *)actor)->unk_13, 3);
    func_8009A3D0(record->unk_24, record->unk_25, 0x300);
    func_8009A028(actor);
    object_data = (u8 *)actor - 0x20;
    ((S_80175398_2 *)object_data)->unk_10 |= 0x80000000;
    return;

jt_c7:
    {
        u8 *linked_actor = func_800A504C(record, actor);
        ((S_80175398_1 *)actor)->unk_60 = linked_actor;
        if (linked_actor == NULL) {
            goto done;
        }
        ((S_80175398_0 *)transition)->unk_96.u = 0x10;
        ((S_80175398_0 *)transition)->unk_9B++;
        ((S_80175398_7 *)(((S_80175398_1 *)actor)->unk_60))->unk_2A = ((S_80175398_1 *)actor)->unk_2A.u;
        {
            u8 *linked_state = ((S_80175398_1 *)actor)->unk_60;
            s32 direction;
            u8 *direction_frames;

            object_data = ((S_80175398_5_pre *)linked_state)[-1].unk_00;
            direction = ((D_80083228 + ((S_80175398_5 *)linked_state)->unk_2A + 0x100) >> 9) & 7;
            direction_frames = ((S_80175398_2 *)object_data)->unk_2C;
            func_80047738(object_data, direction_frames[direction], ((S_80175398_2 *)object_data)->unk_04);
        }
        ((S_80175398_2 *)object_data)->unk_14 &= 0xFFFE;
    }

jt_c8:
    {
        u16 timer = ((S_80175398_0 *)transition)->unk_96.u - 1;
        ((S_80175398_0 *)transition)->unk_96.u = timer;
        if ((s32)(timer << 16) > 0) {
            goto done;
        }
        {
            register u8 *counters;

            ((S_80175398_7 *)(((S_80175398_1 *)actor)->unk_60))->unk_2A = ((S_80175398_1 *)actor)->unk_8A;
            ((S_80175398_0_pre *)transition)[-1].unk_00 |= 0x8000;
            D_800814A0 |= 0x8000;
            counters = D_80083460;
            ((S_80175398_6 *)counters)->unk_0A--;
        }
    }
    ((S_80175398_1 *)actor)->unk_6D = 0;

done:
    return;
}
