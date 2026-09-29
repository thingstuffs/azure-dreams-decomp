#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/game_work.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082EB0.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern void *D_8008ACDC[];
extern void *D_8008EAC8[];
extern s32 D_80082EB0[];
extern s16 D_800DCE66[5];
extern s32 D_800E4940[];
extern u8 D_8004F5F4[];
M2C_UNK func_8004DD2C();                     /* extern */
s32 func_8009074C();                /* extern */
s32 func_8009402C(); /* extern */
s32 func_80094208();                         /* extern */
M2C_UNK func_800997FC();                   /* extern */
M2C_UNK func_8009F644();   /* extern */
M2C_UNK func_800A56E0();                     /* extern */
M2C_UNK func_800B0F50();                      /* extern */
s32 func_800B9964();                          /* extern */
M2C_UNK func_800BA810();                 /* extern */
M2C_UNK func_800C77D0();   /* extern */
extern u8 D_80012D6D;
extern M2C_UNK D_8001EF2C;
extern M2C_UNK D_80023C58;
extern M2C_UNK D_80088904;
extern M2C_UNK D_80088934;
extern M2C_UNK D_80088970;
extern M2C_UNK D_800E0040;
extern M2C_UNK D_800E2004;


typedef struct S_80091430_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x4];
    s32 unk_10;
} S_80091430_0;   /* dungeon_state in func_80091430 */

typedef struct S_80091430_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x6A];
    s16 unk_8A;
} S_80091430_1;   /* actor in func_80091430 */

typedef struct S_80091430_2_pre {
    s32 unk_00;
    u8 pad_04[0x14];
} S_80091430_2_pre;   /* the 0x18 bytes before temp_t0 in func_80091430, addressed as temp_t0[-1] */


typedef struct S_80091430_4 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_80091430_4;   /* temp_a0 in func_80091430 */

typedef struct S_80091430_5 {
    u8 pad_00[0x46];
    u16 unk_46;
} S_80091430_5;   /* temp_a0_2 in func_80091430 */

typedef struct S_80091430_6 {
    u8 pad_00[0x46];
    u16 unk_46;
} S_80091430_6;   /* temp_v1_2 in func_80091430 */

typedef struct S_80091430_7 {
    u8 pad_00[0x2A];
    s16 unk_2A;
} S_80091430_7;   /* (*(void **)((u8 *)arg0 + 0x104)) in func_80091430 */

/* Updates the selection, handles dungeon input, and restores the actor callback on exit. */
void func_80091430(void *state, M2C_UNK context_a, M2C_UNK context_b, void *actor_ptr) {
    S_80091430_1 *actor = actor_ptr;
    GameWork *dungeon_state = &gameWork;
    s16 action_id;
    s16 action_arg;
    s16 selection_code;
    s16 slot_index;
    s32 selection_result;
    s32 selection_ready;
    s32 candidate_flags;
    s32 phase;
    void **candidate_slot;
    S_80091430_4 *candidate;
    S_80091430_5 *preview;
    void *selection_data;
    S_80091430_6 *selection;

    phase = (*(u8 *)((u8 *)state + 0x9B));
    switch (phase) {
    case 0:
        selection_ready = func_800B9964(state + 0x104);
        (*(s32 *)((u8 *)state + 0xC8)) = selection_ready;
        if (selection_ready == 0) {
            return;
        }
        func_8004DCE0(2);
        func_8004DCEC();
        if ((*(s16 *)((u8 *)state + 0x120)) == 0) {
            if (D_80012D6D == 0) {
                func_8004DD2C(&D_80088904);
            } else {
                func_8004DD2C(&D_80088934);
            }
        } else {
            func_8004DD2C(&D_80088970);
        }
        (*(u8 *)((u8 *)state + 0x9B)) = (u8) ((*(u8 *)((u8 *)state + 0x9B)) + 1);
    case 1:
        selection_result = func_8009074C((*(s16 *)((u8 *)state + 0x9E)), state + 0xA2, (*(void **)((u8 *)state
            + 0x104)) + 0x2A);
        selection_code = (s16) selection_result;
        if (selection_code != 0xFFF) {
            ((S_80091430_7 *)((*(void **)((u8 *)state + 0x104))))->unk_2A = selection_result;
            func_8009F644(actor, 0x70, (s32) (*(void **)((u8 *)state + 0x104)) == (*(s32 *)((u8 *)state + 0xB0)),
                (selection_result << 0x10 >> 0x19) & 7);
        }
        if ((*(s16 *)((u8 *)state + 0x120)) == 0) {
            selection_data = (*(void **)((u8 *)state + 0x104));
            if (selection_data != NULL && (((s32)dungeon_state->unk_010) & 0x80)) {
                if ((func_80094208(0) == 0) && !(actor->unk_1C & 0x100000)) {
                    actor->unk_8A = (s16) ((s32) (*(void **)((u8 *)state + 0x104)) != (*(s32 *)((u8 *)state + 0xAC)));
                    D_80082EB0[0] = 0;
                    if ((func_8009402C(state, context_a, context_b, &action_id, &action_arg, D_80082EB0[0]) << 0x10)
                        != 0) {
                        func_800997FC(&D_800E2004);
                    } else {
                        func_8004E130();
                    }
                    (*(s32 *)((u8 *)state + 0xC8)) = 0;
                    func_8008DB0C(state, context_a, context_b, action_id, (s32) action_arg);
                    {
                        s32 tail_flags = D_800E296C;

                        (*(void **)((u8 *)state + 0x104)) = NULL;
                        D_800E296C = tail_flags & ~0x2000;
                    }
                    return;
                }
            } else {
                if (selection_data != NULL) {
                    if (((s32)dungeon_state->unk_010) & 0x10) {
                        func_800C77D0(selection_data - 0x20, ((S_80091430_2_pre *)selection_data)[-1].unk_00, 8,
                            *D_800DCE66);
                        slot_index = (s32) (*(void **)((u8 *)state + 0x104)) != (*(s32 *)((u8 *)state + 0xAC));
                        actor->unk_8A = slot_index;
                        *D_800E4940 = (s32) slot_index;
                        func_8008CF6C(state, context_a, context_b, &D_8001EF2C);
                        ((Rec_D_80082EB0 *)D_80082EB0)->unk_00.as_s32 = 0;
                        (*(s32 *)((u8 *)state + 0xC8)) = 0;
                        (*(void **)((u8 *)state + 0x104)) = NULL;
                        func_8004E130();
                        return;
                    }
                    if (((s32)dungeon_state->unk_010) & 0x20) {
                        slot_index = (s32) (*(void **)((u8 *)state + 0x104)) != (*(s32 *)((u8 *)state + 0xAC));
                        actor->unk_8A = slot_index;
                        *D_800E4940 = (s32) slot_index;
                        func_8008CF6C(state, context_a, context_b, &D_80023C58);
                        ((Rec_D_80082EB0 *)D_80082EB0)->unk_00.as_s32 = 0;
                        (*(s32 *)((u8 *)state + 0xC8)) = 0;
                        (*(void **)((u8 *)state + 0x104)) = NULL;
                        func_8004E130();
                        return;
                    }
                    if (((s32)dungeon_state->unk_010) & 0x40) {
                        func_800C77D0(selection_data - 0x20, ((S_80091430_2_pre *)selection_data)[-1].unk_00, 8,
                            *D_800DCE66);
                        slot_index = (s32) (*(void **)((u8 *)state + 0x104)) != (*(s32 *)((u8 *)state + 0xAC));
                        actor->unk_8A = slot_index;
                        *D_800E4940 = (s32) slot_index;
                        func_8008CF6C(state, context_a, context_b, D_8004F5F4);
                        ((Rec_D_80082EB0 *)D_80082EB0)->unk_00.as_s32 = 0;
                        (*(s32 *)((u8 *)state + 0xC8)) = 0;
                        (*(void **)((u8 *)state + 0x104)) = NULL;
                        func_8004E130();
                        return;
                    }
                }
                selection = (*(void **)((u8 *)state + 0x104));
                if ((selection == (*(s32 *)((u8 *)state + 0xAC)))
                    ? !(dungeon_state->buttons & 2)
                    : ((selection != (*(s32 *)((u8 *)state + 0xB0))) || !(dungeon_state->buttons & 1))) {
                    if (dungeon_state->buttons & 3) {
                        candidate_slot = state + 0xAC;
                        if (!(dungeon_state->buttons & 2)) {
                            candidate_slot = state + 0xB0;
                        }
                        candidate = *candidate_slot;
                        if ((candidate != NULL) && ((*(void **)((u8 *)state + 0x104)) != candidate)) {
                            candidate_flags = candidate->unk_1C;
                            if (candidate_flags & 0x20000) {
                                if (!(candidate_flags & 0x80000)) {
                                    (*(void **)((u8 *)state + 0x104)) = candidate;
                                    func_800B0F50(candidate);
                                    return;
                                }
                            }
                        }
                    } else {
                        (*(void **)((u8 *)state + 0x104)) = NULL;
                        (*(u8 *)((u8 *)state + 0x9B)) = (u8) ((*(u8 *)((u8 *)state + 0x9B)) + 1);
                        return;
                    }
                }
            }
        } else {
            preview = (*(void **)((u8 *)state + 0x104));
            func_800BA810(preview, preview->unk_46);
            if (((s32)dungeon_state->unk_010) & 0x60) {
                if (((s32)dungeon_state->unk_010) & 0x20) {
                    func_800A56E0(0x515);
                    selection = (*(void **)((u8 *)state + 0x104));
                    selection->unk_46 &= 0x7FFF;
                } else {
                    func_800A56E0(0x503);
                }
                (*(void **)((u8 *)state + 0x104)) = NULL;
                func_8004E130();
                D_800E296C &= ~0x2000;
                {
                    void *callback;
                    if (actor->unk_1C & 0x100000) {
                        callback = D_8008EAC8;
                    } else {
                        callback = D_8008ACDC;
                    }
                    (*(void **)((u8 *)state + 0x8C)) = callback;
                }
                func_800BA810(NULL, 0U);
                return;
            }
        }
        return;
    case 2:
        (*(s32 *)((u8 *)state + 0xC8)) = 0;
        func_8004E130();
        D_800E296C &= ~0x2000;
        {
            void *callback;
            if (actor->unk_1C & 0x100000) {
                callback = D_8008EAC8;
            } else {
                callback = D_8008ACDC;
            }
            (*(void **)((u8 *)state + 0x8C)) = callback;
        }
        return;
    default:
        return;
    }
}
