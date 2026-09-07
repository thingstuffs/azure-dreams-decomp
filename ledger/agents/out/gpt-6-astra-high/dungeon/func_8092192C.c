#include "common.h"
#include "m2c_compat.h"

typedef struct S_8092192C_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_8092192C_0;   /* temp_v0 in func_8092192C */

typedef struct S_8092192C_1 {
    u8 pad_00[0x6];
    s16 unk_06;
    u8 pad_08[0x8];
    s16 unk_10;
    u8 pad_12[0x2];
    union { u16 s; volatile u16 u; } unk_14;   /* accessed as both */
} S_8092192C_1;   /* temp_a0 in func_8092192C */

typedef struct S_8092192C_2 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_8092192C_2;   /* arg0 in func_8092192C */

typedef struct S_8092192C_3 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; volatile u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { volatile s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
} S_8092192C_3;   /* temp_v1 in func_8092192C */

typedef struct S_8092192C_4 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0xD];
    s16 unk_1C;
    s16 unk_1E;
} S_8092192C_4;   /* temp_a0_2 in func_8092192C */


extern u8 D_80045340[];
extern u8 D_800DEC70[];
void *func_8003FC64();
s32 func_8004491C();
void func_8003DB94();
extern M2C_UNK D_800F68AC;

/* Creates and initializes an object at the supplied position plus coordinate offsets. */
void func_8092192C(S_8092192C_2 *base_pos, s32 offset_x, s32 offset_y, s32 offset_z) {
    u16 flags;
    S_8092192C_1 *render_state;
    S_8092192C_4 *sprite;
    S_8092192C_0 *object;
    register S_8092192C_3 *position ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */
    u32 sprite_data_addr;
    s32 base_x;
    s32 base_y;
    s32 base_z;

    object = func_8003FC64(0x212);
    if (object != NULL) {
        object->unk_10 = &D_800F68AC;
        func_8004491C(object, D_80045340);
        render_state = object->unk_0C;
        render_state->unk_10 = 0x20;
        render_state->unk_06 = 6;
        flags = render_state->unk_14.s;
        flags = flags | 0xC;
        render_state->unk_14.u = flags;
        ASM_KEEP(flags);   /* MATCH pin: load-bearing for the whole function shape */
        flags = flags | 2;
        render_state->unk_14.u = flags;
        position = object->unk_08;
        base_x = (s32) base_pos->unk_00;
        sprite_data_addr = 0x800E0000;
        position->unk_00.at00.v = base_x;
        base_y = (s32) base_pos->unk_04;
        ASM_KEEP_DEP_NV(sprite_data_addr, base_y);   /* MATCH pin: load-bearing for the whole function shape */
        sprite_data_addr -= 5008;
        ASM_KEEP(sprite_data_addr);   /* MATCH pin: load-bearing for the whole function shape */
        position->unk_04.at00.v = base_y;
        base_z = (s32) base_pos->unk_08;
        position->unk_00.at02.v = (u16) (position->unk_00.at02.v + offset_x);
        position->unk_08.at00.v = base_z;
        position->unk_04.at02.v = (u16) (position->unk_04.at02.v + offset_y);
        position->unk_08.at02.v = (u16) (position->unk_08.at02.v + offset_z);
        sprite = object->unk_0C;
        sprite->unk_1E = 0x800;
        sprite->unk_1C = 0x800;
        sprite->unk_0E = 0x80;
        sprite->unk_0D = 0x80;
        sprite->unk_0C = 0x80;
        func_8003DB94(sprite, (void *) sprite_data_addr, 0);
    }
}
