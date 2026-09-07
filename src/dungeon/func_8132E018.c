#include "common.h"

typedef struct S_80165018_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_80165018_0;   /* obj in func_80165018 */

typedef struct S_80165018_1 {
    u8 pad_00[0x8];
    void * unk_08;
} S_80165018_1;   /* arg0 in func_80165018 */

typedef struct S_80165018_2 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_80165018_2;   /* state in func_80165018 */

typedef struct S_80165018_3 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80165018_3;   /* pos in func_80165018 */

typedef struct S_80165018_4 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x26];
    s16 unk_32;
    s16 unk_34;
} S_80165018_4;   /* tail in func_80165018 */

typedef struct S_80165018_5 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80165018_5;   /* ((S_80165018_1 *)arg0)->unk_08 in func_80165018 */

typedef struct S_80165018_6 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_80165018_6;   /* ((S_80165018_0 *)obj)->unk_08 in func_80165018 */

typedef struct S_80165018_7 {
    u8 pad_00[0x6];
    s16 unk_06;
    u8 pad_08[0x8];
    s16 unk_10;
} S_80165018_7;   /* ((S_80165018_0 *)obj)->unk_0C in func_80165018 */


extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern s32 rand(void);
extern u8 D_80164BC4[];
extern u8 D_80164DA4[];


void func_80165018(S_80165018_1 *arg0, s32 arg1, s16 arg2, s32 arg3, s32 arg4,
                   s32 arg5) {
    register s32 held_arg4 ASM_REG("$19") = arg4;   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    register s32 held_arg5 ASM_REG("$20") = arg5;   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    void *obj;
    S_80165018_2 *state;
    S_80165018_4 *tail;
    S_80165018_3 *pos;
    register s32 random ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    register s32 value ASM_REG("$3");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */

    obj = func_8003FD64(0x211, arg0);
    if (obj != 0) {
        ((S_80165018_0 *)obj)->unk_10 = D_80164DA4;
        random = rand() & 7;
        value = ((S_80165018_5 *)(arg0->unk_08))->unk_02 + arg3;
        value -= 3;
        value += random;
        ((S_80165018_6 *)(((S_80165018_0 *)obj)->unk_08))->unk_02 = (s16)value;
        random = rand() & 7;
        value = ((S_80165018_5 *)(arg0->unk_08))->unk_06 + held_arg4;
        value -= 3;
        value += random;
        ((S_80165018_6 *)(((S_80165018_0 *)obj)->unk_08))->unk_06 = (s16)value;
        random = rand() & 7;
        value = ((S_80165018_5 *)(arg0->unk_08))->unk_0A + held_arg5;
        value -= 3;
        value += random;
        ((S_80165018_6 *)(((S_80165018_0 *)obj)->unk_08))->unk_0A = (s16)value;
        ((S_80165018_7 *)(((S_80165018_0 *)obj)->unk_0C))->unk_06 = 0;
        state = ((S_80165018_0 *)obj)->unk_0C;
        tail = (u8 *)obj + 0x20;
        state->unk_14 = state->unk_14 | 0xC;
        ((S_80165018_7 *)(((S_80165018_0 *)obj)->unk_0C))->unk_10 = 0x20;
        pos = ((S_80165018_0 *)obj)->unk_08;
        pos->unk_14 = 0;
        pos->unk_10 = 0;
        pos->unk_0C = 0;
        tail->unk_32 = arg2;
        tail->unk_34 = arg2;
        func_8004491C(obj, D_80164BC4);
        ((S_80165018_0 *)obj)->unk_20 = arg1;
        tail->unk_08 = arg1;
    }
}

/* MECHANISM: s3/s4 stack-argument holds reproduce the 0x30 frame and seven-register save set.
   Pinned v0 RNG plus pinned v1 compound accumulation preserves all three coordinate sequences.
   One cached obj+8 pointer collapses the three zero stores to retail's single-load form. */
