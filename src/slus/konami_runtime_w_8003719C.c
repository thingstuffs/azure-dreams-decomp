#include "common.h"
#include "m2c_compat.h"

#include "common.h"
#include "records/Rec_D_80081FDC.h"

typedef struct S_8003719C_4 {
    u8 pad_00[0x20];
    void * unk_20;
} S_8003719C_4;   /* node in func_8003719C */

typedef struct S_8003719C_5 {
    u8 pad_00[0x10];
    s32 unk_10;
    s32 unk_14;
} S_8003719C_5;   /* ((S_8003719C_4 *)node)->unk_20 in func_8003719C */


typedef struct S_8003719C_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    void * unk_0C;
    M2C_UNK (*unk_10)(void *, s32, void *);
    u8 pad_14[0xC];
    void * unk_20;
} S_8003719C_0;   /* node in func_8003719C */

typedef struct S_8003719C_1 {
    u8 pad_00[0x4];
    s32 unk_04;
    s32 unk_08;
    u8 pad_0C[0x38];
    s32 * unk_44;
    s8 unk_48;
    u8 pad_49[0x1];
    s16 unk_4A;
    u8 pad_4C[0x1A];
    s16 unk_66;
} S_8003719C_1;   /* state in func_8003719C */


typedef struct S_8003719C_3 {
    s32 unk_00;
    s8 unk_04;
    s8 unk_05;
    u8 pad_06[0x2];
    M2C_UNK * unk_08;
    s32 unk_0C;
    u8 pad_10[0x4];
    u16 unk_14;
} S_8003719C_3;   /* sprite in func_8003719C */


M2C_UNK func_80033C1C();                 /* extern */
M2C_UNK func_800350B0();                 /* extern */
M2C_UNK func_80036C7C(); /* extern */
M2C_UNK func_80037394();         /* extern */
void *func_8003FF2C(); /* extern */
M2C_UNK func_8004491C();           /* extern */
extern M2C_UNK D_8006A988;
extern M2C_UNK D_8006A994;
extern M2C_UNK D_8006A9A0;
extern M2C_UNK D_8006A9AC;
extern M2C_UNK D_8006A9B8;
extern M2C_UNK D_8006A9C4;
extern M2C_UNK D_80081E90;
extern M2C_UNK D_80081EA0;
extern M2C_UNK D_80082B80;
extern M2C_UNK D_80082B90;
extern M2C_UNK D_80082BA0;
extern M2C_UNK D_80082BB0;
extern M2C_UNK D_80082BC0;
extern M2C_UNK func_80033D54;

/* Initializes a sprite node, links it to its owner, and applies its initial display state. */
void func_8003719C(s32 node_addr, Rec_D_80081FDC *transform, s32 *script_data, s16 cursor_offset, s32 sprite_base, s32 owner) {
    s32 render_data;
    S_8003719C_1 *state;
    S_8003719C_3 *sprite;
    void *node;

    node = func_8003FF2C(0x11, node_addr, 0x49, &D_80082BC0);
    ((S_8003719C_0 *)node)->unk_10 = func_80037394;
    func_8004491C(node, &func_80033D54);
    state = node + 0x20;
    render_data = ((S_8003719C_0 *)node)->unk_08;
    sprite = ((S_8003719C_0 *)node)->unk_0C;
    state->unk_44 = script_data;
    state->unk_48 = 1;
    state->unk_4A = cursor_offset;
    func_80033C1C(transform, *script_data);
    ((S_8003719C_0 *)node)->unk_20 = transform;
    transform->unk_60 = 6;
    ((S_8003719C_5 *)(((S_8003719C_4 *)node)->unk_20))->unk_10 = 0x47;
    ((S_8003719C_5 *)(((S_8003719C_4 *)node)->unk_20))->unk_14 = 2;
    state->unk_04 = 0;
    state->unk_08 = 0;
    func_800350B0(owner, state);
    sprite->unk_0C = 0xC0C0C0;
    func_80036C7C(state->unk_44 + 3, &D_8006A988, &D_80082B80);
    func_80036C7C(state->unk_44 + 3, &D_8006A994, &D_80082B90);
    func_80036C7C(state->unk_44 + 3, &D_8006A9A0, &D_80082BA0);
    func_80036C7C(state->unk_44 + 3, &D_8006A9AC, &D_80082BB0);
    func_80036C7C(state->unk_44 + 3, &D_8006A9B8, &D_80081E90);
    func_80036C7C(state->unk_44 + 3, &D_8006A9C4, &D_80081EA0);
    sprite->unk_08 = &D_80082B90;
    sprite->unk_00 = 0;
    sprite->unk_04 = 0;
    sprite->unk_05 = 0;
    sprite->unk_14 = (u16) (sprite->unk_14 | 0x1C);
    state->unk_66 = (s16) sprite_base;
    func_80037394(state, render_data, sprite);
}
