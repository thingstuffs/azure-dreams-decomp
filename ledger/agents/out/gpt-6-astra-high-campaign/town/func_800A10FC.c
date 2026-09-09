#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

typedef struct S_8009E85C_0_pre {
    M2C_UNK (*unk_00)(void *, void *, void *);
    u8 pad_04[0xC];
} S_8009E85C_0_pre;   /* the 0x10 bytes before arg0 in func_8009E85C, addressed as arg0[-1] */


typedef struct S_8009E85C_1 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_8009E85C_1;   /* arg1 in func_8009E85C */

typedef struct S_8009E85C_2 {
    u8 pad_00[0x8];
    M2C_UNK * unk_08;
    u8 pad_0C[0x4];
    volatile s16 unk_10;
    u8 pad_12[0x2];
    union { volatile u16 s; u16 u; } unk_14;   /* accessed as both */
} S_8009E85C_2;   /* arg2 in func_8009E85C */

typedef struct S_8009E85C_3 {
    u8 pad_00[0x9C8];
    volatile s32 unk_9C8;
} S_8009E85C_3;   /* active_base in func_8009E85C */

typedef struct S_8009E85C_4 {
    u8 pad_00[0x6C];
    s16 unk_6C;
} S_8009E85C_4;   /* tail_self in func_8009E85C */

typedef struct S_8009E85C_5_pre {
    M2C_UNK (*unk_00)(void *, void *, void *);
    u8 pad_04[0xC];
} S_8009E85C_5_pre;   /* the 0x10 bytes before call_a0 in func_8009E85C, addressed as call_a0[-1] */


typedef struct S_8009E85C_6 {
    u8 pad_00[0xA94];
    s32 unk_A94;
} S_8009E85C_6;

M2C_UNK D_8009E714();         /* extern */
M2C_UNK func_80033CD8();           /* extern */
M2C_UNK func_800374F4();                     /* extern */
M2C_UNK func_8009DC8C();     /* extern */
extern M2C_UNK D_80045340;
extern M2C_UNK D_8006E240;
extern s32 D_800D09C8[];

/* Initialize the entity from its table entry and invoke its callback. */
void func_8009E85C(void *entity, S_8009E85C_1 *placement, S_8009E85C_2 *state) {
    u8 *table_page = (u8 *)0x80010000;
    s32 *active_base;
    s32 active;
    s32 init_flags;
    S_8009E85C_4 *tail_entity;
    register M2C_UNK (*callback)(void *, void *, void *) ASM_REG("$3");
    void *callback_entity;
    void *callback_placement;
    void *callback_state;
    u16 flags;
    u8 entry_type;

    ((S_8009E85C_0_pre *)entity)[-1].unk_00 = D_8009E714;
    ((Rec_func_80094268_arg0 *)entity)->unk_A0 = 0xFFE00000;
    placement->unk_08 = 0xFFE00000;
    ((Rec_func_80094268_arg0 *)entity)->unk_4C = table_page[(((Rec_func_80094268_arg0 *)entity)->unk_95 * 4) + 0x980];
    entry_type = table_page[(((Rec_func_80094268_arg0 *)entity)->unk_95 * 4) + 0x981];
    ((Rec_func_80094268_arg0 *)entity)->unk_4D = entry_type;
    if (entry_type == 0x12) {
        state->unk_08 = &D_8006E240;
    } else {
        func_8009DC8C(entity, state, ((Rec_func_80094268_arg0 *)entity)->unk_4C, ((S_8009E85C_6 *)(table_page + ((table_page[(((Rec_func_80094268_arg0 *)entity)->unk_95 * 4) + 0x983] & 0x3F) * 0x54)))->unk_A94);
    }
    func_80033CD8(entity, &D_80045340);
    init_flags = 0x20;
    active_base = (s32 *)0x800D0000;
    state->unk_10 = init_flags;
    flags = state->unk_14.s;
    active = ((S_8009E85C_3 *)active_base)->unk_9C8;
    state->unk_14.u = (u16)(flags | 0x1C);
    tail_entity = entity;
    if (active == 0) {
        ((Rec_func_80094268_arg0 *)entity)->unk_6C.as_s16 = func_800374F4(0x1000);
    } else {
        tail_entity->unk_6C = 0;
    }
    callback_entity = tail_entity;
    callback_placement = placement;
    callback_state = state;
    callback = ((S_8009E85C_5_pre *)callback_entity)[-1].unk_00;
    D_800D09C8[0] = 0;
    callback(callback_entity, callback_placement, callback_state);
}
