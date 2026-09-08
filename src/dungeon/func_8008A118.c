#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80016000.h"

s32 func_8004CAE8();                    /* extern */
M2C_UNK func_80099F04();                         /* extern */
M2C_UNK func_80099F70();                         /* extern */
M2C_UNK func_8009A350();          /* extern */
M2C_UNK func_800A56E0();                     /* extern */
extern M2C_UNK D_80081484;
extern M2C_UNK D_80083460;
extern M2C_UNK D_8008ACDC;
extern M2C_UNK D_800DD25C;
extern s32 D_800E3540;


typedef struct S_8008F878_0 {
    u8 pad_00[0x8C];
    M2C_UNK * unk_8C;
    u8 pad_90[0xB];
    u8 unk_9B;
    u8 pad_9C[0x88];
    void * unk_124;
} S_8008F878_0;   /* arg0 in func_8008F878 */

typedef struct S_8008F878_1 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x8];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_8008F878_1;   /* arg2 in func_8008F878 */

typedef struct S_8008F878_2 {
    union { void * p; s32 i; } unk_00;   /* accessed as both */
} S_8008F878_2;   /* &D_800DD25C in func_8008F878 */

typedef struct S_8008F878_3 {
    u8 pad_00[0x13];
    s8 unk_13;
} S_8008F878_3;   /* temp_v0 in func_8008F878 */

typedef struct S_8008F878_4 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_8008F878_4;   /* temp_v1_2 in func_8008F878 */

typedef struct S_8008F878_5 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    u16 unk_2A;
    u8 pad_2C[0x30];
    s32 unk_5C;
} S_8008F878_5;   /* arg3 in func_8008F878 */


typedef struct S_8008F878_7 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x6];
    u16 unk_0A;
} S_8008F878_7;   /* temp_s0 in func_8008F878 */

typedef struct S_8008F878_8 {
    u8 pad_00[0x6D];
    s8 unk_6D;
} S_8008F878_8;   /* ((S_8008F878_2 *)(&D_800DD25C))->unk_00.p in func_8008F878 */

/* Initializes an actor action and completes it when the action flags are set. */
void func_8008F878(S_8008F878_0 *action, void *unused, S_8008F878_1 *action_data, S_8008F878_5 *actor) {
    u16 query_flags;
    M2C_UNK event_id;
    s32 state;
    s32 saved_value;
    S_8008F878_3 *target;
    S_8008F878_4 *target_flags;
    S_8008F878_7 *shared_state;

    state = action->unk_9B;
    if (state == 1) {
        goto state_1;
    }
    if (state >= 2) {
        goto done;
    }
    if (state != 0) {
        goto done;
    }
    if (func_8004CAE8(action_data->unk_08, 0) == 0) {
        target = action->unk_124;
        ((S_8008F878_2 *)(&D_800DD25C))->unk_00.p = target;
        if (target->unk_13 <= 0) {
            ((S_8008F878_2 *)(&D_800DD25C))->unk_00.i = 0;
        }
        target_flags = action->unk_124;
        target_flags->unk_1C = (s32) (target_flags->unk_1C & 0xFFF7FFFF);
        actor->unk_1C = (s32) (actor->unk_1C & 0xFFEFFFFF);
        func_8009A350(action_data->unk_24, action_data->unk_25, ((u16) actor->unk_2A >> 9) & 7, &query_flags);
        event_id = 0x50C;
        if (query_flags & 0x400) {
            event_id = 0x517;
        }
        func_800A56E0(event_id);
        saved_value = ((Rec_D_80016000 *)(&D_80081484))->unk_00.at00_s32.v;
        ((Rec_D_80016000 *)(&D_80081484))->unk_00.at00_s32.v = 0;
        D_800E3540 = saved_value;
        action->unk_9B++;
        return;
    }
    return;
state_1:
    if (action_data->unk_14 & 0x6000) {
        action->unk_9B = 2U;
        shared_state = &D_80083460;
        shared_state->unk_02 = (u16) (shared_state->unk_02 | 0x412);
        func_80099F70(actor->unk_5C);
        func_80099F04(actor->unk_5C);
        if (((S_8008F878_2 *)(&D_800DD25C))->unk_00.p != NULL) {
            ((S_8008F878_8 *)(((S_8008F878_2 *)(&D_800DD25C))->unk_00.p))->unk_6D = 0;
        }
        action->unk_8C = &D_8008ACDC;
        shared_state->unk_0A = (u16) (shared_state->unk_0A - 1);
    }
done:
    return;
}
