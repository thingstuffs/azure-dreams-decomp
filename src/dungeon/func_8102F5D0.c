#include "common.h"

typedef struct {
    u8 pad0[0xC];
    u8 r;
    u8 g;
    u8 b;
    u8 padF;
    s16 field10;
    u8 pad12[2];
    u16 field14;
    u8 pad16[6];
    s16 field1C;
    s16 field1E;
} Sub1;

typedef struct {
    u8 pad0[2];
    u16 field2;
    u8 pad4[2];
    u16 field6;
    u8 pad8[2];
    u16 fieldA;
} Sub2;

typedef struct {
    u8 pad0[8];
    Sub2 *sub2;
    Sub1 *sub1;
    u8 pad10[0x38];
    s32 field48;
} Obj;

extern void D_80045340(void);
extern void func_8004491C(void *, void (*)(void));

/* Initialize object rendering and copy the three supplied parameter fields. */
void func_8102F5D0(Obj *object, s32 state_value, Sub2 *source_params)
{
    Sub1 *render_state;
    Sub2 *dest_params;

    object->field48 = state_value;
    func_8004491C(object, D_80045340);
    render_state = object->sub1;
    render_state->field10 = 0x20;
    render_state->field14 |= 0xC;
    dest_params = object->sub2;
    dest_params->field2 = source_params->field2;
    dest_params->field6 = source_params->field6;
    dest_params->fieldA = source_params->fieldA;
    render_state = object->sub1;
    render_state->field1E = 0x1000;
    render_state->field1C = 0x1000;
    render_state->b = 0x80;
    render_state->g = 0x80;
    render_state->r = 0x80;
}
