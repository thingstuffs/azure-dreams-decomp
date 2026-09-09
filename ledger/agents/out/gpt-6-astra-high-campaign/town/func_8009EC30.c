#include "common.h"



#ifndef NULL
#define NULL 0
#endif

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern void *func_8003FC64();
extern s32 func_8003FD64();

typedef struct S_8009C390_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    s32 unk_10;
} S_8009C390_0;   /* temp_v0 in func_8009C390 */

typedef struct S_8009C390_1 {
    u8 pad_00[0x50];
    s32 unk_50;
    u8 pad_54[0x48];
    s32 unk_9C;
} S_8009C390_1;   /* temp_a0 in func_8009C390 */

typedef struct S_8009C390_2 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_8009C390_2;   /* temp_a1 in func_8009C390 */

typedef struct S_8009C390_3 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_8009C390_3;   /* arg1 in func_8009C390 */

typedef struct S_8009C390_4 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u8 pad_10[0xC];
    s16 unk_1C;
    s16 unk_1E;
} S_8009C390_4;   /* temp_a2 in func_8009C390 */

/* Creates a type 0x116 object with an optional parent and position, and initializes its rendering. */
void *func_8009C390(s32 parent, S_8009C390_3 *position, s32 object_value, s32 state_value) {
    S_8009C390_1 *state;
    S_8009C390_2 *object_position;
    S_8009C390_4 *render;
    void *object;

    if (parent != 0) {
        object = (void *)func_8003FD64(0x116, parent);
        state = object + 0x20;
    } else {
        object = func_8003FC64(0x116);
        state = object + 0x20;
    }
    if (object == NULL) {
        return NULL;
    }
    object_position = ((S_8009C390_0 *)object)->unk_08;
    render = ((S_8009C390_0 *)object)->unk_0C;
    ((S_8009C390_0 *)object)->unk_10 = object_value;
    state->unk_50 = state_value;
    if (parent != 0) {
        state->unk_9C = (s32)(parent + 0x20);
    }
    if (position != NULL) {
        object_position->unk_00 = position->unk_00;
        object_position->unk_04 = position->unk_04;
        object_position->unk_08 = position->unk_08;
    }
    render->unk_1E = 0x1000;
    render->unk_1C = 0x1000;
    render->unk_0C = 0x808080;
    return object;
}
