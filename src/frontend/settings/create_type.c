#include "common.h"

typedef struct RegistrationNode RegistrationNode;

typedef struct S_7FDD3A2C_3 {
    u8 pad_00[0x8];
    void * unk_08;
} S_7FDD3A2C_3;

typedef struct S_7FDD3A2C_4 {
    s32 unk_00;
    s32 unk_04;
} S_7FDD3A2C_4;


void *func_8003FC64();                       /* extern */
s32 register_node(RegistrationNode *entry, s32 registration_id);
extern s32 D_80044BB0[3];

typedef struct S_7FDD3A2C_0 {
    u8 pad_00[0xC];
    void * unk_0C;
    s32 unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_7FDD3A2C_0;

typedef struct S_7FDD3A2C_1 {
    s32 unk_00;
    s32 unk_04;
} S_7FDD3A2C_1;   /* arg0 in create_type */

typedef struct S_7FDD3A2C_2 {
    u8 pad_00[0x8];
    s32 unk_08;
    s32 unk_0C;
    u8 pad_10[0xC];
    s16 unk_1C;
    s16 unk_1E;
} S_7FDD3A2C_2;

/* Creates a type 0x136 object and initializes its position and rendering state. */
void *create_type(S_7FDD3A2C_1 *position, s32 object_value, s32 render_value, s32 extra_value) {
    S_7FDD3A2C_0 *object;
    S_7FDD3A2C_2 *render_state;

    object = func_8003FC64(0x136);
    if (object != 0) {
        object->unk_10 = object_value;
        ((S_7FDD3A2C_4 *)(((S_7FDD3A2C_3 *)object)->unk_08))->unk_00 = (s32) position->unk_00;
        ((S_7FDD3A2C_4 *)(((S_7FDD3A2C_3 *)object)->unk_08))->unk_04 = (s32) position->unk_04;
        register_node(object, &D_80044BB0);
        render_state = object->unk_0C;
        render_state->unk_1E = 0x1000;
        render_state->unk_1C = 0x1000;
        render_state->unk_08 = render_value;
        render_state->unk_0C = 0x808080;
        object->unk_20 = extra_value;
    }
    return object;
}
