#include "common.h"


typedef struct {
    s32 current;
    u8 pad04[0x28];
    s32 previous_owner;
} TownState;

typedef void (*DispatchFn)(void *, void *, void *, s32);

typedef struct S_7FFFE25C_0 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_7FFFE25C_0;   /* arg2 in func_7FFFE25C */

typedef struct S_7FFFE25C_1 {
    u8 pad_00[0xC];
    void * unk_0C;
} S_7FFFE25C_1;   /* arg1 in func_7FFFE25C */

typedef struct S_7FFFE25C_2 {
    u8 pad_00[0x58];
    void * unk_58;
} S_7FFFE25C_2;   /* arg0 in func_7FFFE25C */

typedef struct S_7FFFE25C_3 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_7FFFE25C_3;   /* ((S_7FFFE25C_1 *)arg1)->unk_0C in func_7FFFE25C */

typedef struct S_7FFFE25C_4 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    void * unk_14;
} S_7FFFE25C_4;   /* ((S_7FFFE25C_2 *)arg0)->unk_58 in func_7FFFE25C */


extern TownState D_800834B8;
extern s32 D_80083780[];
extern s32 D_800D0420[];
extern u8 D_800FE488[];

extern s32 D_80090A6C;
extern s32 D_80092698;
extern s32 D_800927EC;
extern s32 D_80092A84;
extern s32 D_80092CD4;
extern s32 D_80092DA8;
extern s32 D_80092ECC;
extern s32 D_80092FF0;
extern s32 D_800930E4;
extern s32 D_80093250;
extern s32 D_80093328;
extern s32 D_800933FC;
extern s32 D_80093638;
extern s32 D_800AA5F8;

extern void func_8008F170(void *, void *);
extern void func_8008F294(void *, void *);
extern void func_8008F664(void *, void *);
extern s32 func_800352FC();
extern s32 func_8009B120(void *);
extern void func_8009C340(void *, void *, void *, s32);
extern void func_800C172C(void);

/* Adjusts the position and dispatches the current state handler for the owner. */
void func_7FFFE25C(void *context, S_7FFFE25C_1 *owner, S_7FFFE25C_0 *adjusted_pos, s32 dispatch_param)
{
    TownState *state = &D_800834B8;
    s32 *position = D_80083780;
    s32 *offset = D_800D0420;
    s32 previous_owner = state->previous_owner;
    s32 current;
    s32 target_z;
    s32 dispatched;

    adjusted_pos->unk_00 = D_80083780[0];
    adjusted_pos->unk_04 = position[1];
    adjusted_pos->unk_08 = position[2] + offset[2];

    func_8008F170(adjusted_pos, D_800FE488);
    func_8008F294(owner, adjusted_pos);
    func_8008F664(owner, adjusted_pos);

    target_z = position[2] + offset[2];
    if (target_z - adjusted_pos->unk_08 >= 0x10) {
        adjusted_pos->unk_08 =
            target_z + ((S_7FFFE25C_3 *)(owner->unk_0C))->unk_14;
    }

    current = D_800834B8.current;
    dispatched = 1;

    {
        void *dispatch_context;
        void *dispatch_owner;
        void *dispatch_pos;
        void *handler;

        if (current == (s32)&D_800930E4 || current == (s32)&D_80093250) {
            dispatch_context = context;
            dispatch_owner = owner;
            handler = ((S_7FFFE25C_4 *)(((S_7FFFE25C_2 *)context)->unk_58))->unk_08;
            dispatch_pos = adjusted_pos;
            goto dispatch;
        }

        if (current == (s32)&D_800AA5F8) {
            dispatch_context = context;
            dispatch_owner = owner;
            handler = ((S_7FFFE25C_4 *)(((S_7FFFE25C_2 *)context)->unk_58))->unk_14;
            dispatch_pos = adjusted_pos;
            goto dispatch;
        }

        if (current == (s32)&D_80093328) {
            ASM_USE2(dispatch_param, dispatch_param);   /* MATCH pin: retail immediate-load split depends on it */
            dispatch_context = context;
            dispatch_owner = owner;
            handler = ((S_7FFFE25C_4 *)(((S_7FFFE25C_2 *)context)->unk_58))->unk_0C;
            dispatch_pos = adjusted_pos;
            goto dispatch;
        }

        if (current == (s32)&D_80093638) {
            func_8009C340(context, owner, adjusted_pos, dispatch_param);
            goto check_result;
        }

        if (current == (s32)&D_80092698 || current == (s32)&D_800927EC ||
            current == (s32)&D_80092A84 || current == (s32)&D_80092FF0 ||
            current == (s32)&D_80092CD4 || current == (s32)&D_80092DA8 ||
            current == (s32)&D_80092ECC || current == (s32)&D_800933FC ||
            current == (s32)&D_80090A6C || func_800352FC() != 0) {
            if (previous_owner == (s32)owner) {
                goto skip_dispatch;
            }
        }

        dispatch_context = context;
        dispatch_owner = owner;
        handler = ((S_7FFFE25C_4 *)(((S_7FFFE25C_2 *)context)->unk_58))->unk_10;
        dispatch_pos = adjusted_pos;
dispatch:
        ((DispatchFn)handler)(dispatch_context, dispatch_owner, dispatch_pos, dispatch_param);
        goto check_result;
    }

skip_dispatch:
    dispatched = 0;
check_result:
    if (dispatched != 0 && func_8009B120((u8 *)context + 0x4C) != 0) {
        func_800C172C();
    }
}
