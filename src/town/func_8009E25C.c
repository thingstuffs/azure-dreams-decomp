#include "common.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_80082D58.h"


typedef struct {
    s32 current;
    u8 pad04[0x28];
    s32 previous_owner;
} TownState;

typedef void (*DispatchFn)(void *, void *, void *, s32);


typedef struct S_8009B9BC_1 {
    u8 pad_00[0xC];
    void * unk_0C;
} S_8009B9BC_1;   /* arg1 in func_8009B9BC */


typedef struct S_8009B9BC_3 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_8009B9BC_3;   /* ((S_8009B9BC_1 *)arg1)->unk_0C in func_8009B9BC */

typedef struct S_8009B9BC_4 {
    u8 pad_00[0x8];
    s32 unk_08;
    s32 unk_0C;
    void * unk_10;
    s32 unk_14;
} S_8009B9BC_4;   /* ((Rec_D_80082D58 *)arg0)->unk_58 in func_8009B9BC */


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

/* Resolve the owner position and dispatch its handler for the current town state. */
void func_8009B9BC(void *object, S_8009B9BC_1 *owner, Rec_D_800E3D7C *resolved_pos, s32 dispatch_param)
{
    TownState *state = &D_800834B8;
    s32 *position = D_80083780;
    s32 *offset = D_800D0420;
    s32 previous_owner = state->previous_owner;
    s32 current_state;
    s32 target_z;
    s32 dispatched;
    DispatchFn handler;
    void *dispatch_object;
    void *dispatch_owner;
    void *dispatch_pos;

    resolved_pos->unk_00.at00_s32.v = D_80083780[0];
    resolved_pos->unk_04.at00_s32.v = position[1];
    resolved_pos->unk_08.at00_s32.v = position[2] + offset[2];

    func_8008F170(resolved_pos, D_800FE488);
    func_8008F294(owner, resolved_pos);
    func_8008F664(owner, resolved_pos);

    target_z = position[2] + offset[2];
    if (target_z - resolved_pos->unk_08.at00_s32.v >= 0x10) {
        resolved_pos->unk_08.at00_s32.v =
            target_z + ((S_8009B9BC_3 *)(owner->unk_0C))->unk_14;
        dispatch_pos = resolved_pos;
    }

    current_state = D_800834B8.current;
    dispatched = 1;

    if (current_state == (s32)&D_800930E4 || current_state == (s32)&D_80093250) {
        dispatch_object = object;
        dispatch_owner = owner;
        handler = (DispatchFn)((S_8009B9BC_4 *)(((Rec_D_80082D58 *)object)->unk_58))->unk_08;
        dispatch_pos = resolved_pos;
    } else if (current_state == (s32)&D_800AA5F8) {
        dispatch_object = object;
        dispatch_owner = owner;
        handler = (DispatchFn)((S_8009B9BC_4 *)(((Rec_D_80082D58 *)object)->unk_58))->unk_14;
        dispatch_pos = resolved_pos;
    } else if (current_state == (s32)&D_80093328) {
         /* MATCH: preserve the fourth argument register allocation. */
        dispatch_object = object;
        dispatch_owner = owner;
        handler = (DispatchFn)((S_8009B9BC_4 *)(((Rec_D_80082D58 *)object)->unk_58))->unk_0C;
        dispatch_pos = resolved_pos;
    } else if (current_state == (s32)&D_80093638) {
        do {
            do {
                func_8009C340(object, owner, resolved_pos, dispatch_param);
            } while (0);
        } while (0);
        goto tail;
    } else {
        if (current_state == (s32)&D_80092698 || current_state == (s32)&D_800927EC ||
            current_state == (s32)&D_80092A84 || current_state == (s32)&D_80092FF0 ||
            current_state == (s32)&D_80092CD4 || current_state == (s32)&D_80092DA8 ||
            current_state == (s32)&D_80092ECC || current_state == (s32)&D_800933FC ||
            current_state == (s32)&D_80090A6C || func_800352FC() != 0) {
            if (previous_owner == (s32)owner) {
                goto skip;
            }
        }

        dispatch_object = object;
        dispatch_owner = owner;
        handler = (DispatchFn)((S_8009B9BC_4 *)(((Rec_D_80082D58 *)object)->unk_58))->unk_10;
        dispatch_pos = resolved_pos;
    }
    handler(dispatch_object, dispatch_owner, dispatch_pos, dispatch_param);
    goto tail;

skip:
    dispatched = 0;
tail:
    if (dispatched != 0 && func_8009B120((u8 *)object + 0x4C) != 0) {
        func_800C172C();
    }
}
