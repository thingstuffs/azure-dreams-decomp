#include "common.h"

#include "common.h"

typedef struct Func8003800CData Func8003800CData;
typedef struct Func8003800CState Func8003800CState;

struct Func8003800CData {
    u8 pad0[3];
    s8 field3;
    s8 field4;
    u8 pad5[0x2F];
    s32 field34;
};

struct Func8003800CState {
    u8 pad0[0x10];
    void (*callback)(Func8003800CState *);
    u8 pad14[8];
    s32 field1C;
    u8 pad20[8];
    u8 field28;
    u8 pad29[5];
    u8 field2E;
    u8 pad2F[0xD];
    u8 field3C;
    u8 pad3D[0x3F];
    void *field7C;
    Func8003800CData *field80;
};

extern u8 D_800809C4[];
extern u8 D_8002D030[];

extern s32 func_80043FB8(void *, ...);
extern s32 func_80053EF0(s32);
extern void func_800387D0(Func8003800CState *);
extern void func_80038A10(Func8003800CState *);

/* Synchronize changed data, consume the pending value, and run the state callback. */
void func_8003800C(Func8003800CState *state)
{
    func_80043FB8(D_800809C4);
    func_80043FB8(D_8002D030, func_80053EF0(4));
    func_80043FB8(D_800809C4);

    {
        Func8003800CData *data = state->field80;
        s8 current_value = data->field3;
        s8 previous_value = data->field4;
        u8 value_byte = data->field3;

        if (current_value != previous_value) {
            data->field4 = value_byte;
            state->field28 = value_byte;
        }
    }

    if (state->field80->field34 != 0) {
        if (state->callback == func_800387D0) {
            do {
                func_800387D0(state);
            } while (state->callback != func_80038A10);
        }

        {
            s32 pending_value;
            Func8003800CData *value_data;
            Func8003800CData *clear_data;

            value_data = *(Func8003800CData * volatile *)&state->field80;
            do {
                clear_data = state->field80;
            } while (0);
            pending_value = value_data->field34;

            state->callback = func_80038A10;
            state->field2E = 0;
            state->field7C = &state->field3C;
            state->field1C = pending_value;
            clear_data->field34 = 0;
        }
    }

    if (state->callback == 0) {
        state->callback = func_80038A10;
    }
    state->callback(state);
}
