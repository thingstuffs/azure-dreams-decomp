#include "common.h"



typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern M2C_UNK func_800A56E0();
extern M2C_UNK func_800AD058();
extern M2C_UNK func_80174D48();
extern s16 D_8008346A[];

typedef struct S_801736EC_0 {
    u8 pad_00[0x96];
    s16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
} S_801736EC_0;   /* arg0 in func_801736EC */

typedef struct S_801736EC_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x28];
    s8 unk_48;
    u8 unk_49;
} S_801736EC_1;   /* arg3 in func_801736EC */

typedef struct S_801736EC_2 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s16 unk_10;
    u16 unk_12;
    u16 unk_14;
} S_801736EC_2;   /* arg2 in func_801736EC */

/* Initializes the visual effect and advances its action state. */
void func_801736EC(S_801736EC_0 *action, M2C_UNK context, S_801736EC_2 *visual, S_801736EC_1 *entity) {
    M2C_UNK one;
    M2C_UNK color;
    M2C_UNK phase;

    phase = action->unk_9B;
    one = 1;
    if (phase == one) {
        goto initialize;
    }
    if (phase >= 2) {
        goto check_update;
    }
    if (phase == 0) {
        goto wait_ready;
    }
    goto done;

check_update:
    if (phase == 2) {
        goto update;
    }
    goto done;

wait_ready:
    if (D_8008346A[0] != 0) {
        goto done;
    }
    action->unk_9B = (u8)one;

initialize:
    if (entity->unk_49 != 0) {
        func_80174D48(context, visual, entity);
        entity->unk_48 = 0;
        entity->unk_49 = 0U;
    }
    color = 0x808080;
    ASM_KEEP(color);   /* MATCH pin: retail immediate-load split depends on it */
    visual->unk_10 = 0x20;
    visual->unk_12 = (u16)(visual->unk_12 - 0x80);
    visual->unk_14 = (u16)(visual->unk_14 | 0xC);
    entity->unk_1C = entity->unk_1C | 0x10000000;
    visual->unk_0C = color;
    action->unk_96 = 0x10;
    action->unk_9B = (u8)(action->unk_9B + 1);
    func_800A56E0(0x805, color);
    goto done;

update:
    func_800AD058(action, context, visual, entity);

done:
    return;
}
