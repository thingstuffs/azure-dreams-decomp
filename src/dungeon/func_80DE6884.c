#include "common.h"
typedef s32 M2C_UNK;

typedef struct S_80DE6884_0 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_80DE6884_0;   /* setup_arg1 in func_80DE6884 */

typedef struct S_80DE6884_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_80DE6884_1;   /* temp_v0 in func_80DE6884 */

typedef struct S_80DE6884_2 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x1];
    u16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x4];
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} S_80DE6884_2;   /* temp_s0 in func_80DE6884 */

typedef struct S_80DE6884_3 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80DE6884_3;   /* held_arg1 in func_80DE6884 */

typedef struct S_80DE6884_4 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; struct { u8 pad[0x2]; volatile u16 v; } at02u; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
    s32 unk_0C;
    s32 unk_10;
    union { volatile s32 s; s32 u; } unk_14;   /* accessed as both */
} S_80DE6884_4;   /* temp_s0_2 in func_80DE6884 */

typedef struct S_80DE6884_5 {
    u8 pad_00[0x2A];
    s16 unk_2A;
} S_80DE6884_5;   /* held_arg0 in func_80DE6884 */

typedef struct {
    s32 words[6];
} Copy24;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define NULL 0

M2C_UNK func_8003DB94();
s32 func_8003DE58(s32, void *, s16 *, s32);
void *func_8003FC64();
M2C_UNK func_8004491C();
M2C_UNK func_800478B8();
s32 func_800644B8();
s32 func_80064584(s32, s32);
s32 rand();
extern M2C_UNK D_80045340[3];
extern M2C_UNK D_800DEA68[3];
extern M2C_UNK D_80173F8C[3];

void func_80DE6884(void *arg0, void *arg1, void *arg2) {
    u16 offsets[3];
    s32 copy0;
    s32 copy1;
    s32 copy2;
    s32 copy3;
    s32 copy4;
    s32 copy5;
    s32 temp_v1;
    s32 var_s2;
    s32 var_v0;
    register S_80DE6884_3 *held_arg1 ASM_REG("$21") = arg1;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    S_80DE6884_5 *held_arg0;
    M2C_UNK *temp_s4;
    u32 temp_v0_addr;
    register S_80DE6884_0 *setup_arg1 ASM_REG("$5");   /* MATCH pin: keeps a statement from moving across a call/branch */
    s16 *setup_arg2;
    void *db_arg1;
    S_80DE6884_2 *temp_s0;
    S_80DE6884_4 *temp_s0_2;
    S_80DE6884_1 *temp_v0;

    setup_arg1 = arg2;
    setup_arg2 = (s16 *)offsets;
    var_s2 = 0;
    offsets[2] = 0;
    offsets[1] = 0;
    offsets[0] = 0;
    held_arg0 = arg0;
    ASM_KEEP(setup_arg2);   /* MATCH pin: retail schedule: same instructions, different order without it */
    func_8003DE58(setup_arg1->unk_08, setup_arg1, setup_arg2, var_s2);
    temp_v0_addr = 0x80170000;
    ASM_KEEP(temp_v0_addr);   /* MATCH pin: keeps a statement from moving across a call/branch */
    temp_s4 = (M2C_UNK *)(temp_v0_addr + 0x3F8C);
    do {
        temp_v0 = func_8003FC64(0x212);
        if (temp_v0 != NULL) {
            db_arg1 = &D_800DEA68;
            temp_s0 = temp_v0->unk_0C;
            temp_v0->unk_10 = temp_s4;
            temp_s0->unk_0E = 0x60;
            temp_s0->unk_0D = 0x60;
            temp_s0->unk_0C = 0x60;
            temp_s0->unk_14 = (u16)(temp_s0->unk_14 | 0xC);
            temp_s0->unk_10 = (u16)(temp_s0->unk_10 | 0x20);
            func_8003DB94(temp_s0, db_arg1, 0);
            func_800478B8(temp_s0);
            var_v0 = rand();
            temp_v1 = var_v0;
            if (temp_v1 < 0) {
                var_v0 = temp_v1 + 0xFFF;
            }
            temp_s0->unk_1A = (s16)(temp_v1 - ((var_v0 >> 0xC) << 0xC));
            temp_s0->unk_1E = 0x1000;
            temp_s0->unk_1C = 0x1000;
            func_8004491C(temp_v0, &D_80045340);
            temp_s0_2 = temp_v0->unk_08;
            copy0 = held_arg1->unk_00;
            copy1 = held_arg1->unk_04;
            copy2 = held_arg1->unk_08;
            copy3 = held_arg1->unk_0C;
            temp_s0_2->unk_00.at00.v = copy0;
            temp_s0_2->unk_04.at00.v = copy1;
            temp_s0_2->unk_08.at00.v = copy2;
            temp_s0_2->unk_0C = copy3;
            copy4 = held_arg1->unk_10;
            copy5 = held_arg1->unk_14;
            temp_s0_2->unk_10 = copy4;
            temp_s0_2->unk_14.s = copy5;
            temp_s0_2->unk_00.at02.v = (u16)(temp_s0_2->unk_00.at02u.v + offsets[0]);
            temp_s0_2->unk_04.at02.v = (u16)(temp_s0_2->unk_04.at02.v + offsets[1]);
            temp_s0_2->unk_08.at02.v = (u16)(temp_s0_2->unk_08.at02.v + offsets[2]);
            temp_s0_2->unk_0C = (s32)((func_80064584(
                held_arg0->unk_2A,
                copy3) >> 4) << 0xB);
            temp_s0_2->unk_10 = (s32)((func_800644B8(held_arg0->unk_2A) >> 4) << 0xB);
            temp_s0_2->unk_14.u = 0x9C40;
        }
        var_s2 += 1;
    } while (var_s2 < 4);
}

/* MECHANISM: One aliased three-halfword stack object and held s2-s5 roles reproduce the 0x38 frame.
   A grouped 24-byte scalar copy keeps its fourth word live in a1 for the two-argument callee ABI.
   Split v0-to-s4 page formation plus paired volatile store/read ordering closes the final rotations. */
