#include "common.h"

typedef struct {
    u8 pad0[0x10];
    void *field10;
} FuncArg;

typedef struct {
    u8 pad0[0x14];
    u8 field14;
} FuncData;

/* Returns whether the record has attached state with type 1 or 3. */
s32 get_whether_has_attached_state_type_n_1_n_3(FuncArg *record) {
    FuncData *state;

    state = record->field10;
    if (state == 0) {
        return 0;
    }
    if ((state->field14 == 1) || (state->field14 == 3)) {
        return 1;
    }
    return 0;
}
