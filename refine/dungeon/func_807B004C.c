#include "common.h"



typedef s32 M2C_UNK;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

typedef struct Pair {
    s32 first;
    s32 second;
} Pair;

extern void *func_8003FD64();
extern void func_8004491C();
extern void func_800B835C();
extern u8 D_80045340[12];
extern u8 D_800F75EC[12];
extern u8 D_800FBE30[12];
extern u8 D_800FBE3C[12];

typedef struct S_807B004C_0 {
    u8 pad_00[0xC];
    void * unk_0C;
    u8 * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
} S_807B004C_0;   /* temp_v0 in func_807B004C */

typedef struct S_807B004C_1 {
    u8 pad_00[0x8];
    u8 * unk_08;
    u8 pad_0C[0x10];
    s16 unk_1C;
    s16 unk_1E;
} S_807B004C_1;   /* temp_v1 in func_807B004C */

typedef struct S_807B004C_2 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s16 unk_0C;
} S_807B004C_2;   /* temp_v1_2 in func_807B004C */

typedef struct S_807B004C_3 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_807B004C_3;   /* arg0 in func_807B004C */

/* Creates a child object, initializes its state, and loads its graphics. */
void func_807B004C(void *parent_data) {
    Pair texture_rect;
    s32 rect_origin;
    s32 rect_size;
    Pair *rect_ptr;
    void *child;
    S_807B004C_1 *render_state;
    S_807B004C_2 *child_data;

    child = func_8003FD64(2, (u8 *)parent_data - 0x20);
    if (child != 0) {
        ((S_807B004C_0 *)child)->unk_10 = D_800F75EC;
        func_8004491C(child, D_80045340);
        rect_origin = 0x01000340;
        rect_size = 0x200020;
        rect_ptr = &texture_rect;
        render_state = ((S_807B004C_0 *)child)->unk_0C;
        render_state->unk_08 = D_800FBE30;
        render_state->unk_1C = 0x1000;
        render_state->unk_1E = 0x800;
        child_data = (u8 *)child + 0x20;
        ((S_807B004C_0 *)child)->unk_20 = parent_data;
        child_data->unk_0A = ((S_807B004C_3 *)parent_data)->unk_2A;
        child_data->unk_0C = 0x30;
        texture_rect.second = rect_size;
        texture_rect.first = rect_origin;
        func_800B835C(D_800FBE3C, rect_ptr, 1, 0);
    }
}
