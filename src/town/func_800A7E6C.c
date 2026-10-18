#include "common.h"
#include "shared/entity.h"

typedef s32 M2C_UNK;

typedef struct S_800A55CC_0_pre {
    M2C_UNK * unk_00;
    u8 pad_04[0xC];
} S_800A55CC_0_pre;   /* the 0x10 bytes before arg0 in initialize_effect_and_adjust_value, addressed as arg0[-1] */



extern void func_80033CD8(void *object, void *setup_data);
void initialize_actor_action_state(void *object, EntityRec *state, s32 initData);
extern M2C_UNK D_800903FC[];
extern u8 D_800970FC[];
extern s32 D_800D0CC0[];

/* Initialize the object and adjust its record value before final setup. */
void initialize_effect_and_adjust_value(void *object, EntityRec *record, s32 init_value) {
    s32 delta;

    ((S_800A55CC_0_pre *)object)[-1].unk_00 = D_800903FC;
    initialize_actor_action_state(object, record, init_value);
    {
        delta = 0x10000;
        init_value = record->z.v;
        record->z.v =
            (init_value + delta) - D_800D0CC0[0];
        func_80033CD8(object, D_800970FC);
    }
}
