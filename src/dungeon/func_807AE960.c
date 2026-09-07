#include "common.h"
#include "m2c_compat.h"

typedef struct S_807AE960_0 {
    u8 pad_00[0x1DC];
    s32 unk_1DC;
} S_807AE960_0;   /* dungeon_data in func_807AE960 */

typedef struct S_807AE960_1 {
    union { u16 s; s16 u; } unk_00;   /* accessed as both */
    u16 unk_02;
    union { s16 s; volatile s16 u; } unk_04;   /* accessed as both */
    u8 pad_06[0x4];
    s16 unk_0A;
    union { s16 s; volatile u16 u; } unk_0C;   /* accessed as both */
    u16 unk_0E;
    s16 unk_10;
} S_807AE960_1;   /* state in func_807AE960 */

typedef struct S_807AE960_2 {
    u8 pad_00[0x1A];
    s16 unk_1A;
} S_807AE960_2;   /* target in func_807AE960 */

typedef struct S_807AE960_3 {
    u8 pad_00[0x2090];
    volatile s32 unk_2090;
} S_807AE960_3;   /* global in func_807AE960 */

typedef struct S_807AE960_4 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_807AE960_4;   /* actor in func_807AE960 */

typedef struct S_807AE960_5 {
    u8 pad_00[0x14];
    s16 unk_14;
} S_807AE960_5;   /* global_end in func_807AE960 */

typedef struct S_807AE960_6 {
    u8 pad_00[0x4];
    u16 unk_04;
} S_807AE960_6;   /* temp_v0_2 in func_807AE960 */


extern void *D_800F6000[];
M2C_UNK func_8003E4FC();
s32 func_8003F270();
void func_8003F540();
int func_800445E0();
s32 func_80053EF0();
M2C_UNK func_800A56E0();
M2C_UNK func_800F62E8() __attribute__((noreturn));
M2C_UNK func_800F635C() __attribute__((noreturn));
extern M2C_UNK D_80010000;
extern u16 D_8001371A;
extern s32 D_8006CD58;
extern u8 D_80082EA5;
extern M2C_UNK D_80083160;
extern s16 D_8008346A;

void func_807AE960(void *arg0, void *arg1, void *arg2) {
    static void *const jt_keep[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5, &&jt_c6, &&jt_c7, &&jt_c8, &&jt_c9, &&jt_c10, &&jt_c11, &&jt_c12, &&jt_c13, &&jt_c14, &&jt_c15, &&jt_c16, &&jt_c17, &&jt_c18, &&jt_c19 };
    s16 temp_a0;
    s32 dispatch_index;
    s16 temp_v1_2;
    s32 countdown;
    u16 countdown_u;
    s32 actor_pos;
    u8 *state = arg0;
    register u8 *actor ASM_REG("$20") = arg1;   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    u8 *target = arg2;
    register u8 *global ASM_REG("$16");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register s32 temp_s2 ASM_REG("$18");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    register s32 temp_s5 ASM_REG("$21");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    register u8 *global_end ASM_REG("$22");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    u8 *dungeon_data;
    S_807AE960_6 *temp_v0_2;

    dungeon_data = (u8 *)&D_80083160;
    global_end = dungeon_data + 0x1DC;
    temp_s5 = ((S_807AE960_0 *)dungeon_data)->unk_1DC;
    dispatch_index = (s16)(((S_807AE960_1 *)state)->unk_00.s - 1);
    if ((u32) dispatch_index >= 0x14U) {
        goto block_28;
    }
    (void)jt_keep; goto *D_800F6000[(u32)dispatch_index];
jt_c0:
jt_c1:
    if (func_8003F270(dispatch_index) != 0) {
        goto block_37;
    }
    if (((S_807AE960_1 *)state)->unk_10 != 0) {
        goto block_5;
    }
    func_800A56E0(0x300);
block_5:
    ((S_807AE960_1 *)state)->unk_00.u = 3;
    func_800F635C();
    return;
jt_c16:
    ((S_807AE960_1 *)state)->unk_0A = 0x400;
    func_800F62E8();
    return;
jt_c2:
    temp_a0 = ((S_807AE960_1 *)state)->unk_04.s;
    if (temp_a0 <= 0) {
        goto block_11;
    }
    ((S_807AE960_2 *)target)->unk_1A = (s16) ((u16) ((S_807AE960_2 *)target)->unk_1A + ((s32) (((S_807AE960_1 *)state)->unk_0A - ((S_807AE960_2 *)target)->unk_1A) / temp_a0));
block_11:
    temp_v1_2 = (u16) ((S_807AE960_1 *)state)->unk_04.s - 1;
    ((S_807AE960_1 *)state)->unk_04.u = temp_v1_2;
    ASM_SCHED_BARRIER();   /* MATCH pin: retail basic-block layout depends on it */
    global = (u8 *)0x80010000;
    if ((u16) D_8001371A >= 4U) {
        goto block_15;
    }
    if (temp_v1_2 >= 0) {
        goto block_28;
    }
block_13:
    ((S_807AE960_1 *)state)->unk_04.s = 0;
    func_800F635C();
    return;
block_15:
    if (((S_807AE960_3 *)global)->unk_2090 != 1) {
        goto block_17;
    }
    D_8008346A = 1;
block_17:
    if (((S_807AE960_1 *)state)->unk_04.s > 0) {
        goto block_28;
    }
    temp_s2 = ((S_807AE960_3 *)global)->unk_2090;
    if (temp_s2 != 1) {
        goto block_22;
    }
    if (func_80053EF0(4) != 0) {
        goto block_13;
    }
    if (((S_807AE960_3 *)global)->unk_2090 != temp_s2) {
        goto block_22;
    }
    D_8008346A = 0;
block_22:
    ((S_807AE960_2 *)target)->unk_1A = (s16) (u16) ((S_807AE960_1 *)state)->unk_0A;
    ((S_807AE960_1 *)state)->unk_00.u = 0;
    func_800F635C();
    return;
jt_c3:
    if (((S_807AE960_1 *)state)->unk_10 != 0) {
        goto block_26;
    }
    func_8003F540(0, D_8006CD58, 0x0600065E, 0x030008B6);
    func_8003E4FC(0x15, func_800445E0(), 0);
block_26:
    ((S_807AE960_1 *)state)->unk_04.s = 0x60;
    ((S_807AE960_1 *)state)->unk_0C.s = 0x60;
jt_c19:
    ((S_807AE960_1 *)state)->unk_00.s = 2U;
    ((S_807AE960_1 *)state)->unk_0A = (s16) ((S_807AE960_1 *)state)->unk_02;
jt_c4:
jt_c5:
jt_c6:
jt_c7:
jt_c8:
jt_c9:
jt_c10:
jt_c11:
jt_c12:
jt_c13:
jt_c14:
jt_c15:
jt_c17:
jt_c18:
block_28:
    countdown = ((S_807AE960_1 *)state)->unk_0C.s;
    countdown_u = ((S_807AE960_1 *)state)->unk_0C.u;
    if (countdown == 0) {
        goto block_33;
    }
    countdown = countdown_u - 1;
    ((S_807AE960_1 *)state)->unk_0C.s = countdown;
    actor_pos = ((S_807AE960_4 *)actor)->unk_0A;
    if (countdown & 1) {
        countdown = actor_pos + 1;
    } else {
        countdown = actor_pos - 1;
    }
block_31:
    ((S_807AE960_4 *)actor)->unk_0A = countdown;
    if (((S_807AE960_1 *)state)->unk_0C.s != 0) {
        goto block_33;
    }
    ((S_807AE960_4 *)actor)->unk_0A = (s16) ((S_807AE960_1 *)state)->unk_0E;
block_33:
    if (((S_807AE960_1 *)state)->unk_00.u != 0) {
        goto block_37;
    }
    if ((u8) D_80082EA5 >= 0x3DU) {
        goto block_37;
    }
    if (((S_807AE960_1 *)state)->unk_0A == (s16) ((S_807AE960_1 *)state)->unk_02) {
        goto block_37;
    }
    ((S_807AE960_1 *)state)->unk_00.s = 4U;
    temp_v0_2 = ((0x3E << ((S_807AE960_5 *)global_end)->unk_14) * 6) + temp_s5 + 0xBA;
    temp_v0_2->unk_04 = (u16) (temp_v0_2->unk_04 | 0x8000);
block_37:
    return;
}
