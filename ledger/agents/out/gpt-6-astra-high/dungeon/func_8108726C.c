#include "common.h"

typedef struct S_80174A6C_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80174A6C_0;   /* obj in func_80174A6C */

typedef struct S_80174A6C_1 {
    u8 pad_00[0x6];
    u16 unk_06;
    u8 pad_08[0x4];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    u16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0x8];
    s32 unk_28;
} S_80174A6C_1;   /* prim in func_80174A6C */

typedef struct S_80174A6C_2 {
    u8 pad_00[0x28];
    s32 unk_28;
} S_80174A6C_2;   /* arg2 in func_80174A6C */

typedef struct S_80174A6C_3 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80174A6C_3;   /* arg1 in func_80174A6C */

typedef struct S_80174A6C_4 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80174A6C_4;   /* dst in func_80174A6C */

typedef struct S_80174A6C_5 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_80174A6C_5;   /* query_arg in func_80174A6C */



extern void *func_8003FC64(s32);
extern void func_8004491C(void *, void *);
extern void func_80047784(void *, s32, s32);
extern s32 func_8003DE58(s32, void *, u16 *, s32);

extern u8 D_80045340[9];
extern u8 D_80174A00[9];

/* Creates an object, initializes its primitive, copies state, and applies queried offsets. */
s32 func_80174A6C(void *unused, S_80174A6C_3 *src_state, S_80174A6C_2 *source)
{
    u16 offsets[3];
    S_80174A6C_0 *obj;
    S_80174A6C_4 *dst_state;
    S_80174A6C_1 *prim;

    obj = func_8003FC64(0x312);
    if (obj != 0) {
        obj->unk_10 = D_80174A00;
        func_8004491C(obj, D_80045340);

        prim = obj->unk_0C;
        prim->unk_28 = source->unk_28;
        prim->unk_0E = 0x80;
        prim->unk_0D = 0x80;
        prim->unk_0C = 0x80;
        prim->unk_1E = 0x2000;
        prim->unk_1C = 0x2000;
        prim->unk_06 = 1;
        prim->unk_14 |= 0xC;
        prim->unk_10 |= 0x20;
        func_80047784(prim, 0x39, 0);

        {
            S_80174A6C_5 *query_arg = source;
            u16 *query_out;
            register s32 copy_word_0 ASM_REG("$2");   /* MATCH pin: retail register colouring depends on it */
            register s32 copy_word_1 ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */
            s32 copy_word_2;
            s32 copy_word_3;

            ASM_KEEP(query_arg);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
            dst_state = obj->unk_08;
            ASM_KEEP(dst_state);   /* MATCH pin: retail schedule: same instructions, different order without it */
            query_out = offsets;
            ASM_KEEP(query_out);   /* MATCH pin: load-bearing for the whole function shape */

            copy_word_0 = src_state->unk_00;
            copy_word_1 = src_state->unk_04;
            copy_word_2 = src_state->unk_08;
            copy_word_3 = src_state->unk_0C;
            dst_state->unk_00.at00.v = copy_word_0;
            dst_state->unk_04.at00.v = copy_word_1;
            dst_state->unk_08.at00.v = copy_word_2;
            dst_state->unk_0C = copy_word_3;
            copy_word_0 = src_state->unk_10;
            copy_word_1 = src_state->unk_14;
            dst_state->unk_10 = copy_word_0;
            dst_state->unk_14 = copy_word_1;

            offsets[2] = 0;
            offsets[1] = 0;
            offsets[0] = 0;
            if (func_8003DE58(query_arg->unk_08, query_arg,
                              query_out, 0) != 0) {
                dst_state->unk_00.at02.v += offsets[0];
                dst_state->unk_04.at02.v += offsets[1];
                dst_state->unk_08.at02.v += offsets[2];
            }
        }
        return (s32)obj;
    }
    return 0;
}
