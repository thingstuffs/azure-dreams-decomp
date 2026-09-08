#include "common.h"
#include "m2c_compat.h"

typedef struct {
    s32 words[3];
} TableEntry;

extern s32 func_8003DE58();
extern void *func_8003FD64();
extern s32 func_8004491C();

extern s32 D_80026680[3];
extern TableEntry D_80028820[];
extern s32 D_80083498[3];
extern s32 D_800CEEFC[3];
extern u8 D_800DDC40[9];

typedef struct S_80026C88_0 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_80026C88_0;   /* callee_arg in func_80026C88 */

typedef struct S_80026C88_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    s32 * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
} S_80026C88_1;   /* temp_v0 in func_80026C88 */

typedef struct S_80026C88_2 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0xE];
    s16 unk_1A;
    u8 pad_1C[0x2];
    s16 unk_1E;
    u8 pad_20[0x2];
    s16 unk_22;
    u8 pad_24[0x42];
    s16 unk_66;
    u8 pad_68[0x6];
    s16 unk_6E;
} S_80026C88_2;   /* temp_a3 in func_80026C88 */

typedef struct S_80026C88_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    u8 pad_0C[0x2];
    u16 unk_0E;
    u8 pad_10[0x2];
    u16 unk_12;
    u8 pad_14[0x2];
    u16 unk_16;
} S_80026C88_3;   /* temp_a2 in func_80026C88 */

typedef struct S_80026C88_4 {
    u8 pad_00[0x8];
    TableEntry * unk_08;
    u8 pad_0C[0x8];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_80026C88_4;   /* temp_a0 in func_80026C88 */

typedef struct S_80026C88_5 {
    u8 pad_00[0x24];
    u16 unk_24;
    u16 unk_26;
    u16 unk_28;
} S_80026C88_5;   /* var_a1 in func_80026C88 */

void *func_80026C88(u16 arg0, u16 arg1, s32 arg2, void *arg3)
{
    u16 position[3];
    s32 *callback;
    TableEntry *var_s2;
    s32 var_s1;
    register S_80026C88_4 *temp_a0 ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    S_80026C88_3 *temp_a2;
    void *temp_v0;
    register void *var_a1 ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    S_80026C88_0 *callee_arg;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    u16 *position_arg;
    register s32 held_arg2 ASM_REG("$21");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    void *var_s6;

    held_arg2 = arg2;
    var_s6 = NULL;
    callee_arg = arg3;
    position_arg = position;
    position[0] = position[1] = 0;
    if (func_8003DE58(callee_arg->unk_08, callee_arg, position_arg, 0) == 0) {
        position[2] = (0 - D_800DDC40[0]) + 0x10;
    }
    callback = D_80026680;
    var_s1 = 0;
    do { var_s2 = D_80028820; } while (0);
    do {
        temp_v0 = func_8003FD64(0x212, D_80083498);
        if (temp_v0 != NULL) {
            s32 var_t0;
            S_80026C88_2 *temp_a3;
            void *self_link;

            ((S_80026C88_1 *)temp_v0)->unk_10 = callback;
            func_8004491C(temp_v0, D_800CEEFC);
            temp_a3 = temp_v0 + 0x20;
            temp_a3->unk_1A = (s16) (arg0 + position[0]);
            temp_a3->unk_1E = (s16) (arg1 + position[1]);
            var_t0 = 0;
            temp_a3->unk_22 = (s16) (held_arg2 + position[2]);
            temp_a2 = ((S_80026C88_1 *)temp_v0)->unk_08;
            temp_a2->unk_02 = arg0;
            temp_a2->unk_0E = arg0;
            temp_a2->unk_06 = arg1;
            temp_a2->unk_12 = arg1;
            temp_a2->unk_0A = held_arg2 - 0x100;
            temp_a2->unk_16 = held_arg2 - 0x100;
            temp_a0 = ((S_80026C88_1 *)temp_v0)->unk_0C;
            var_a1 = temp_a3;
            temp_a0->unk_1E = 0x1000;
            temp_a0->unk_1C = 0x1000;
            self_link = temp_v0 + 0x38;
            temp_a0->unk_08 = var_s2;
            temp_a0->unk_14 = (u16) (temp_a0->unk_14 | 0xC);
            ((S_80026C88_1 *)temp_v0)->unk_20 = self_link;
            temp_a3->unk_66 = 0x20;
            temp_a3->unk_6E = var_s1;
            do {
                ((S_80026C88_5 *)var_a1)->unk_24 = (u16) temp_a2->unk_02;
                ((S_80026C88_5 *)var_a1)->unk_26 = (u16) temp_a2->unk_06;
                var_t0 += 1;
                ((S_80026C88_5 *)var_a1)->unk_28 = (u16) temp_a2->unk_0A;
                var_a1 += 8;
            } while (var_t0 < 8);
            temp_a3->unk_08 = var_s6;
            var_s6 = temp_v0;
        }
        var_s1 += 1;
        var_s2 += 1;
    } while (var_s1 < 6);
    ASM_KEEP(held_arg2);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    return temp_v0;
}

/* MECHANISM: position[3] owns the three halfword stack slots; s5/s6 hold arg2/list head.
   Guarded ABI/block pins preserve a1/a2 call setup and a3/t0/a0/a1 copy-loop roles.
   A split self_link computation and direct arg2-0x100 stores prevent unwanted hoisting. */
