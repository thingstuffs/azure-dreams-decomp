#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_8008ACDC_arg0.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_80082E80.h"

void func_80048A44(void *, u8, s32, s32);
s32 func_8004CAE8(s32, s32);
void func_80091934(void *, s32, void *, void *);
s32 func_800990FC(void);
s32 func_80099194(void *, s32);
void func_80099290(s32);
s32 func_8009929C(s32, s32);
s32 func_80099368(s32, s32);
s32 func_8009965C(s32, s32);
s32 func_80099734(void *, s32);
void func_800A56E0(s32);
void func_800A5720(s32);
void *func_800A8608(void *, s32, s32, s32, s32);
extern s32 D_80081484;
extern s16 D_80083160[];
extern s32 D_8008ACDC;
extern s32 D_8008D470;
extern u8 D_800DD100[];
extern u8 D_800E06E3[];
extern u8 D_800E06EB[];


typedef struct S_8009255C_1 {
    u8 pad_00[0xC8];
    s16 unk_C8;
} S_8009255C_1;   /* base in func_8009255C */


typedef struct S_8009255C_3 {
    u8 pad_00[0x2C];
    u8 * unk_2C;
} S_8009255C_3;   /* call_arg in func_8009255C */


typedef struct S_8009255C_5 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x4];
    s32 unk_10;
} S_8009255C_5;   /* temp_v0 in func_8009255C */

typedef struct S_8009255C_6 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_8009255C_6;   /* temp_v1_2 in func_8009255C */

typedef struct S_8009255C_7 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    void * unk_90;
    u8 pad_94[0x8];
    void * unk_9C;
    u8 pad_A0[0x8];
    s16 unk_A8;
    s16 unk_AA;
} S_8009255C_7;   /* temp_v1_3 in func_8009255C */

/* Turn the actor, spawn the action object and message, and handle completion. */
void func_8009255C(void *controller, s32 action_id, Rec_D_80082E80 *actor, Rec_D_800E3D7C *transform) {
    s32 text_start;
    s32 text_cursor;
    s32 state;
    void *spawned;
    S_8009255C_6 *position;
    S_8009255C_7 *spawned_state;
    void *globals_page;
    volatile s16 *view_data;
    S_8009255C_3 *animation_actor;
    u8 *animation_entry;
    u8 *animation_table;

    state = ((Rec_func_8008ACDC_arg0 *)controller)->unk_9B.as_u8;
    if (state == 1) {
        goto state_1;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_0;
        }
        goto end;
    }
    if (state == 2) {
        goto state_2;
    }
    goto end;

state_0:
    globals_page = (void *)0x80080000;
    ASM_KEEP(globals_page);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    view_data = (volatile s16 *)(globals_page + 0x3160);
    if ((((((S_8009255C_1 *)view_data)->unk_C8 +
             transform->unk_2A.as_s16 + 0x100) >> 9) & 7) == 2) {
        animation_actor = actor;
        ASM_KEEP(animation_actor);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        animation_table = D_800DD100;
        animation_actor->unk_2C = animation_table;
        animation_entry = (u8 *)((s32)(((((S_8009255C_1 *)view_data)->unk_C8 +
                                transform->unk_2A.as_s16 + 0x100) >> 9) &
                              7) +
                       (s32)animation_table);
        func_80048A44(
            animation_actor,
            *animation_entry,
            0,
            1);
        goto increment;
    }
    transform->unk_2A.as_s16 =
        (u16)transform->unk_2A.as_s16 + 0x200;
    goto end;

state_1:
    if (func_8004CAE8(actor->unk_08, 0) == 0) {
        goto end;
    }
    if (((Rec_func_8008ACDC_arg0 *)controller)->unk_110 == (s32)&D_80081484) {
        ((Rec_func_8008ACDC_arg0 *)controller)->unk_124 = 0;
        ((Rec_func_8008ACDC_arg0 *)controller)->unk_1C &= 0xFFEFFFFF;
    }
    spawned = func_800A8608(
        controller - 0x20, ((Rec_func_8008ACDC_arg0 *)controller)->unk_110, 0, 0, 0);
    if (spawned != NULL) {
        ((S_8009255C_5 *)spawned)->unk_10 = (s32)&D_8008D470;
        position = ((S_8009255C_5 *)spawned)->unk_08;
        position->unk_02 =
            (actor->unk_24 << 6) + 0x20;
        position->unk_06 =
            (actor->unk_25 << 6) + 0x20;
        position->unk_0A =
            transform->unk_88.as_u16 - 0x30;
        spawned_state = spawned + 0x20;
        spawned_state->unk_A8 = 0x1E;
        spawned_state->unk_AA = 2;
        spawned_state->unk_90 = actor;
        spawned_state->unk_8C = action_id;
        spawned_state->unk_9C = controller + 0x108;
        text_cursor = func_800990FC();
        text_start = text_cursor;
        text_cursor = func_8009929C(8, text_cursor);
        text_cursor = func_80099734(transform, text_cursor);
        text_cursor = func_80099194(D_800E06E3, text_cursor);
        text_cursor = func_80099368(
            ((Rec_func_8008ACDC_arg0 *)controller)->unk_110, text_cursor);
        text_cursor = func_80099194(D_800E06EB, text_cursor);
        text_cursor = func_8009965C(
            ((Rec_func_8008ACDC_arg0 *)controller)->unk_110, text_cursor);
        func_80099290(text_cursor);
        func_800A5720(text_start);
        func_800A56E0(0x509);
    }

increment:
    ((Rec_func_8008ACDC_arg0 *)controller)->unk_9B.as_u8++;
    goto end;

state_2:
    if ((actor->unk_14.at00_u16.v & 0xE000) == 0) {
        goto end;
    }
    if (((Rec_func_8008ACDC_arg0 *)controller)->unk_110 != 0) {
        func_80091934(controller, action_id, actor, transform);
        goto end;
    }
    ((Rec_func_8008ACDC_arg0 *)controller)->unk_8C.as_s32 = (s32)&D_8008ACDC;

end:
    return;
}

/* MECHANISM: True-space local joins restore retail block order and the increment path.
   A volatile held 0x80083160 base reproduces both loads; short-lived a0/v1 roles
   plus index-first entry arithmetic preserve the final addu destination. */
