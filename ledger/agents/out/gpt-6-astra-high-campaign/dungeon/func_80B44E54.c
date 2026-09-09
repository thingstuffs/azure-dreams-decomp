#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_80172654_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { u16 s; s16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    union { u8 s; volatile u8 u; } unk_9B;   /* accessed as both */
} S_80172654_0;   /* arg0 in func_80172654 */

typedef struct S_80172654_1 {
    u8 pad_00[0x2A];
    union { u16 s; s16 u; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x25];
    s8 unk_6D;
} S_80172654_1;   /* arg3 in func_80172654 */


typedef struct S_80172654_3 {
    u8 pad_00[0x2A];
    s16 unk_2A;
} S_80172654_3;   /* call_a0 in func_80172654 */

typedef struct S_80172654_4 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    u8 pad_08[0x2];
    u16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80172654_4;   /* arg1 in func_80172654 */

typedef struct S_80172654_5 {
    u8 pad_00[0x10];
    void * unk_10;
    u8 pad_14[0xC];
    u16 unk_20;
} S_80172654_5;   /* obj in func_80172654 */

typedef struct S_80172654_6 {
    u8 pad_00[0x2];
    u16 unk_02;
    u16 unk_04;
    u8 pad_06[0x2];
    s32 unk_08;
    u8 pad_0C[0x2];
    u16 unk_0E;
    u16 unk_10;
    u16 unk_12;
} S_80172654_6;   /* tail in func_80172654 */

/* m2c compatibility helpers used by the validated warm seed. */

s32 func_8003DE58(s32, void *, s16 *, s16);
void *func_8003FD64(s32, void *);
void func_8004491C(void *, void *);
void func_80047784(void *, u8, s32);
void func_8009C12C(void *, void *, s16, s32);
void func_800A2B04(void *, u8, u8);
void func_800A4ACC(void *);
void func_800A56E0(s32);
void func_800AD594(void *, s32);
s32 func_800BCB04(s32, s32, s16);
extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s16 D_80083228;
extern s32 D_8008346C;
extern u8 D_80083498[];
extern void *D_800E3DE8;
extern u8 D_80170E70;
extern u8 D_80173F38[];
extern u8 D_80173FDC[];
extern u8 D_80175A4C[];
extern u8 D_80175A8C[];

/* Updates an actor action, spawning an effect and returning the actor to its tile. */
void func_80172654(void *action, void *motion, void *entity, void *actor) {
    s16 effect_offset[3];
    s32 dir_x;
    s32 dir_y;
    s32 dir_offset;
    s32 state;
    s32 timer;
    u8 next_state;
    s32 shifted_timer;
    void *action_actor;
    void *effect;
    u8 *effect_data;

    state = ((S_80172654_0 *)action)->unk_9B.s;
    dir_offset = (((S_80172654_1 *)actor)->unk_2A.s >> 8) & 0xE;
    dir_x = *(s16 *)((u8 *)&D_8006CCD8 + dir_offset);
    dir_y = *(s16 *)((u8 *)&D_8006CCE8 + dir_offset);
    timer = ((S_80172654_0 *)action)->unk_96.s - 1;
    ((S_80172654_0 *)action)->unk_96.s = timer;

    if (state == 2) goto state_2;
    if (state < 3) {
        if (state == 0) goto state_0;
        if (state == 1) {
            shifted_timer = timer << 16;
            goto state_1;
        }
        ASM_SCHED_BARRIER(); /* MATCH: preserve the state-1 branch and shared epilogue jump. */
        goto done;
    }
    if (state == 4) goto state_4;
    if (state < 4) goto state_3;
    if (state == 0xFF) goto state_255;
    goto done;

state_0:
    action_actor = actor;
    if (((Rec_D_80082E80 *)entity)->unk_14.at00_u16.v & 0x8000) {
        ((S_80172654_0 *)action)->unk_9B.s = 0xFF;
        ((Rec_D_80082E80 *)entity)->unk_14.at00_u16.v |= 0x6000;
        func_8009C12C(action_actor, entity, ((S_80172654_3 *)action_actor)->unk_2A, 1);
        goto done;
    }
    ((S_80172654_4 *)motion)->unk_0C = (-dir_x) << 17;
    ((S_80172654_4 *)motion)->unk_10 = (-dir_y) << 17;
    ((S_80172654_4 *)motion)->unk_14 = 0;
    (*(void **)((u8 *)entity + 0x2C)) = D_80175A4C;
    func_80047784(entity,
        D_80175A4C[((D_80083228 + ((S_80172654_1 *)actor)->unk_2A.u + 0x100) >> 9) & 7],
        0);
    next_state = ((S_80172654_0 *)action)->unk_9B.u;
    timer = 8;
    ((S_80172654_0 *)action)->unk_96.s = timer;
    goto store_next_state;

state_1:
    if (shifted_timer > 0) goto done;
    ((S_80172654_4 *)motion)->unk_10 = 0;
    ((S_80172654_4 *)motion)->unk_0C = 0;
    (*(void **)((u8 *)entity + 0x2C)) = D_80175A8C;
    func_80047784(entity,
        D_80175A8C[((D_80083228 + ((S_80172654_1 *)actor)->unk_2A.u + 0x100) >> 9) & 7],
        0);
    goto increment_state;

state_2:
    if (((((Rec_D_80082E80 *)entity)->unk_04.as_s8 == 4) &&
         (((Rec_D_80082E80 *)entity)->unk_14.at00_u16.v & 0x1000)) ||
        (((Rec_D_80082E80 *)entity)->unk_14.at00_u16.v & 0x8000)) {
        ((Rec_D_80082E80 *)entity)->unk_14.at00_u16.v |= 0x800;
        ((S_80172654_0 *)action)->unk_96.s = 0x10;
        if (func_8003DE58(((Rec_D_80082E80 *)entity)->unk_08, entity, effect_offset, 0) == 0) {
            effect_offset[2] = 0;
            effect_offset[1] = 0;
            effect_offset[0] = 0;
        }
        effect = func_8003FD64(0x12, D_80083498);
        if (effect != NULL) {
            func_8004491C(effect, D_80173FDC);
            ((S_80172654_5 *)effect)->unk_10 = D_80173F38;
            ((S_80172654_5 *)effect)->unk_20 = ((S_80172654_4 *)motion)->unk_00.at02.v + effect_offset[0];
            effect_data = (u8 *)effect + 0x20;
            ((S_80172654_6 *)effect_data)->unk_02 = ((S_80172654_4 *)motion)->unk_04.at02.v + effect_offset[1];
            ((S_80172654_6 *)effect_data)->unk_04 = ((S_80172654_4 *)motion)->unk_0A + effect_offset[2];
            ((S_80172654_6 *)effect_data)->unk_08 = 0xC0C0C0;
            ((S_80172654_6 *)effect_data)->unk_0E = 8;
            ((S_80172654_6 *)effect_data)->unk_12 =
                func_800BCB04(((((Rec_D_80082E80 *)entity)->unk_24 + dir_x) << 6) & 0xFFC0,
                              ((((Rec_D_80082E80 *)entity)->unk_25 + dir_y) << 6) & 0xFFC0,
                              (s16)(((S_80172654_4 *)motion)->unk_0A - 0x80)) -
                ((S_80172654_4 *)motion)->unk_0A;
            ((S_80172654_6 *)effect_data)->unk_10 = ((S_80172654_1 *)actor)->unk_2A.s;
            goto increment_state;
        }
        goto increment_state;
    }
    goto done;

state_3:
    if ((s16)timer == 0xA) {
        func_8009C12C(actor, entity, ((S_80172654_1 *)actor)->unk_2A.u, 1);
        func_800A56E0(0x813);
    }
    if (((S_80172654_0 *)action)->unk_96.u > 0) goto done;
    ((S_80172654_0 *)action)->unk_96.s = 8;
    ((Rec_D_80082E80 *)entity)->unk_14.at00_u16.v &= 0xF7FF;
    goto increment_state;

increment_state:
    next_state = ((S_80172654_0 *)action)->unk_9B.u;
store_next_state:
    next_state += 1;
    ((S_80172654_0 *)action)->unk_9B.s = next_state;
    goto done;

state_4:
    if ((timer << 16) > 0) goto done;
    (*(void **)((u8 *)entity + 0x2C)) = D_80175A4C;
    func_80047784(entity,
        D_80175A4C[((D_80083228 + ((S_80172654_1 *)actor)->unk_2A.u + 0x100) >> 9) & 7],
        0);
    ((S_80172654_0 *)action)->unk_96.s = state;
    ((S_80172654_0 *)action)->unk_9B.s = 0xFF;
    goto done;

state_255:
    ((S_80172654_4 *)motion)->unk_0C =
        (s32)((((((Rec_D_80082E80 *)entity)->unk_24 << 6) + 0x20) << 16) -
              ((S_80172654_4 *)motion)->unk_00.at00.v) >> 1;
    ((S_80172654_4 *)motion)->unk_10 =
        (s32)((((((Rec_D_80082E80 *)entity)->unk_25 << 6) + 0x20) << 16) -
              ((S_80172654_4 *)motion)->unk_04.at00.v) >> 1;
    if ((((Rec_D_80082E80 *)entity)->unk_14.at00_u16.v & 0xE000) ||
        (((S_80172654_0 *)action)->unk_96.u <= 0)) {
        ((S_80172654_4 *)motion)->unk_14 = 0;
        ((S_80172654_4 *)motion)->unk_10 = 0;
        ((S_80172654_4 *)motion)->unk_0C = 0;
        func_800A2B04(motion, ((Rec_D_80082E80 *)entity)->unk_24,
                     ((Rec_D_80082E80 *)entity)->unk_25);
        func_800AD594(actor, 0x100);
        ((S_80172654_0 *)action)->unk_8C = &D_80170E70;
        D_8008346C = 0;
        func_800A4ACC(actor);
        if (((S_80172654_1 *)actor)->unk_6D == 0) {
            ((S_80172654_1 *)actor)->unk_46 &= 0x7FFF;
            goto done;
        }
        D_800E3DE8 = (u8 *)actor - 0x20;
    }

done:
    return;
}
