#include "common.h"

typedef struct S_8016BE20_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    union { u8 n; volatile u8 v; } unk_9B;   /* accessed as both */
} S_8016BE20_0;   /* state in func_8016BE20 */

typedef struct S_8016BE20_1 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_8016BE20_1;   /* work in func_8016BE20 */

typedef struct S_8016BE20_2 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x18];
    void * unk_60;
    u8 pad_64[0x9];
    u8 unk_6D;
} S_8016BE20_2;   /* ctx in func_8016BE20 */

typedef struct S_8016BE20_3 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0x16];
    u8 * unk_2C;
} S_8016BE20_3;   /* actor in func_8016BE20 */

typedef struct S_8016BE20_4 {
    u8 pad_00[0x28];
    u8 unk_28;
} S_8016BE20_4;   /* world in func_8016BE20 */

typedef struct S_8016BE20_5 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} S_8016BE20_5;   /* control in func_8016BE20 */

typedef struct S_8016BE20_6 {
    u8 pad_00[0x10];
    u32 unk_10;
} S_8016BE20_6;   /* header in func_8016BE20 */



extern void func_800353F4(void *, void *);
extern void func_80047784(void *, u8, s32);
extern void func_8009C12C(void *, void *, s16, s32);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern void func_80164BA4(void *);

extern u16 D_80013714;
extern s16 D_80083228;
extern s32 D_80083460;
extern s32 D_8008346C;
extern u8 D_800E3D7C[];
extern u8 D_8016A36C[];
extern u8 D_801739B8[];
extern u8 D_80173A40[];
extern u8 D_80175392[];
extern u8 D_80175DC0;
extern u8 D_80175DC1;
extern void *D_80164948[];

/* Advances the actor sequence, then resets its state and updates world objects. */
void func_8016BE20(void *state_arg, void *work_arg, void *actor_arg, void *ctx_arg)
{
    void *state = state_arg;
    void *work = work_arg;
    void *actor = actor_arg;
    void *ctx = ctx_arg;
    u8 *world;
    u8 *anim_table;
    u8 *control;
    u8 *object_header;
    void *object;
    register void *setup_data ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    u32 object_flag;
    s32 object_index;
    u16 timer;
    u16 global_flags;
    u16 control_count;
    u8 state_index;

    static void *const state_labels[] = {
        &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5
    };

    (void)state_labels;
    state_index = ((S_8016BE20_0 *)state)->unk_9B.n;
    if ((u32)state_index >= 6) {
        return;
    }
    goto *D_80164948[(u32)state_index];

jt_c0:
        ((S_8016BE20_1 *)work)->unk_14 = 0;
        ((S_8016BE20_1 *)work)->unk_10 = 0;
        ((S_8016BE20_1 *)work)->unk_0C = 0;
        ((S_8016BE20_0 *)state)->unk_96.s = 0;
        ((S_8016BE20_0 *)state)->unk_9B.n++;
        D_80175DC1 = 0;
        return;

jt_c1:
    {
        register u8 *anim_table ASM_REG("$5"); /* MATCH: keep the merged anim_table address in a1 across both arms. */
        if (D_80175DC1 == 0) {
            ((S_8016BE20_0 *)state)->unk_96.s = 0;
            ((S_8016BE20_0 *)state)->unk_9B.n++;
            anim_table = D_80173A40;
        } else {
            if (D_80175DC0 == 0) {
                return;
            }
            ((S_8016BE20_0 *)state)->unk_96.s = 0;
            ((S_8016BE20_0 *)state)->unk_9B.n++;
            func_800A56E0(0x300);
            anim_table = D_80173A40;
        }
        (*(u8 * *)((u8 *)actor + 0x2C)) = anim_table;
        func_80047784(actor,
            *(u8 *)((((D_80083228 + ((S_8016BE20_2 *)ctx)->unk_2A + 0x100) >> 9) & 7) + (u32)anim_table),
            0);
        return;
    }

jt_c2:
        timer = ((S_8016BE20_0 *)state)->unk_96.u + 1;
        ((S_8016BE20_0 *)state)->unk_96.u = timer;
        if ((s16)timer == 0x11) {
            func_8009C12C(ctx, actor, ((S_8016BE20_2 *)ctx)->unk_2A, 1);
            ((S_8016BE20_0 *)state)->unk_96.s = 0;
            ((S_8016BE20_0 *)state)->unk_9B.n++;
        }
        if (((S_8016BE20_0 *)state)->unk_96.s != 0xF) {
            return;
        }
        func_800A56E0(0x804);
        return;

jt_c3:
        if (!(((S_8016BE20_3 *)actor)->unk_14 & 0xE000)) {
            return;
        }
        anim_table = D_801739B8;
        if (((S_8016BE20_3 *)actor)->unk_2C != anim_table) {
            (*(u8 * *)((u8 *)actor + 0x2C)) = anim_table;
            func_80047784(actor,
                anim_table[((D_80083228 + ((S_8016BE20_2 *)ctx)->unk_2A + 0x100) >> 9) & 7],
                0);
        }
        if (D_80175DC1 != 0) {
            state_index = ((S_8016BE20_0 *)state)->unk_9B.v;
            ((S_8016BE20_0 *)state)->unk_96.s = 0;
            goto increment_state;
        }
        ((S_8016BE20_0 *)state)->unk_9B.n += 2;
        return;

jt_c4:
        timer = ((S_8016BE20_0 *)state)->unk_96.u + 1;
        ((S_8016BE20_0 *)state)->unk_96.u = timer;
        if ((s16)timer < 0x28) {
            return;
        }
        state_index = ((S_8016BE20_0 *)state)->unk_9B.n;
increment_state:
        ((S_8016BE20_0 *)state)->unk_9B.n = state_index + 1;
        return;

jt_c5:
        world = *(u8 **)D_800E3D7C;
        if (((S_8016BE20_4 *)world)->unk_28 >= 2) {
            goto case5_failure;
        }
        if (((S_8016BE20_2 *)ctx)->unk_60 != world) {
            goto case5_failure;
        }

        setup_data = D_80175392;
        ((S_8016BE20_0 *)state)->unk_8C = D_8016A36C;
        control = (u8 *)&D_80083460;
        control_count = ((S_8016BE20_5 *)control)->unk_0A;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        object_index = 0;
        ((S_8016BE20_5 *)control)->unk_0C = 0;
        control_count++;
        ((S_8016BE20_5 *)control)->unk_0A = control_count;
        ((S_8016BE20_2 *)ctx)->unk_46 &= 0x7FFF;
        global_flags = D_80013714;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        object_flag = 0x80000000;
        ASM_USE(object_flag);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        D_80013714 = global_flags | 8;
        func_800353F4(setup_data, work);
        ((S_8016BE20_2 *)ctx)->unk_6D = 0;
        ((S_8016BE20_0 *)state)->unk_9B.n = 0;

        for (;;) {
            object = (*(void * *)((u8 *)(*(u8 **)D_800E3D7C) + 0xAC + object_index * 4));
            if (object != 0) {
                func_80164BA4(object);
                object_header = (u8 *)(*(void * *)((u8 *)(*(u8 **)D_800E3D7C) + 0xAC + object_index * 4)) - 0x20;
                ((S_8016BE20_6 *)object_header)->unk_10 |= object_flag;
            }
            object_index++;
            if (object_index >= 2) {
                return;
            }
        }

case5_failure:
        ((S_8016BE20_0 *)state)->unk_8C = D_8016A36C;
        D_8008346C = 0;
        func_800A4ACC(ctx);
        ((S_8016BE20_2 *)ctx)->unk_46 &= 0x7FFF;
        return;
}
