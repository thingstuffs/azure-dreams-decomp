#include "common.h"
#include "m2c_compat.h"

typedef struct S_800CA444_0 {
    u8 pad_00[0x24];
    union { struct { u8 v; } at00; struct { u16 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_24;   /* overlapping accesses */
    s8 unk_26;
} S_800CA444_0;   /* arg2 in func_800CA444 */

typedef struct S_800CA444_1 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x25];
    union { u8 u; s8 s; } unk_6D;   /* accessed as both */
    u8 pad_6E[0x3];
    u8 unk_71;
    u8 pad_72[0x16];
    u16 unk_88;
} S_800CA444_1;   /* arg3 in func_800CA444 */

typedef struct S_800CA444_2 {
    u8 pad_00[0x98];
    u16 unk_98;
    u8 pad_9A[0x2];
    s8 unk_9C;
} S_800CA444_2;   /* arg0 in func_800CA444 */

typedef struct S_800CA444_3 {
    s16 unk_00;
} S_800CA444_3;   /* ((s32) (var_s1 << 0x10) >> 0xF) + (u32) temp_s4 in func_800CA444 */

typedef struct S_800CA444_4 {
    u8 pad_00[0x58];
    s32 unk_58;
} S_800CA444_4;   /* *D_800814A8 in func_800CA444 */

typedef struct S_800CA444_5 {
    u8 pad_00[0x74];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
} S_800CA444_5;   /* (arg3 + (((S_800CA444_1 *)arg3)->unk_71 & 0x7F)) in func_800CA444 */


extern u16 D_80083462[5];
typedef struct {
    u8 pad_00[0xC];
    u16 flags;
    u8 pad_0E[6];
} DungeonTableEntry;

extern DungeonTableEntry D_800E2970[];
extern s16 D_8006CD00[];
extern u16 D_80082E80[];
extern u16 D_80083460[];
extern int D_800814A8[4];
extern u8 D_8006CCD8[];
extern u8 D_8006CCE8[];
M2C_UNK func_800A0E6C();
M2C_UNK func_800A19E4();
M2C_UNK func_800A9A0C();
s32 func_8009A180();
s16 func_800BCB04();
s32 func_800CA1E0();
M2C_UNK func_800CA598();

void func_800CA444(void *input0, s32 arg1, void *input2, void *input3) {
    register void *arg0 ASM_REG("$21");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    S_800CA444_0 *arg2;
    void *arg3;
    register s16 temp_s0 ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s16 temp_v0;
    register s32 temp_v1 ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 table_value;
    register s32 state_idx ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s16 next_s1 ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s16 var_s1 ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    M2C_UNK temp_a0_2;
    s8 temp_a0;
    s16 *temp_s4;
    u16 *temp_s6;
    void *tail_arg;
    unsigned long first_dir;
    u32 hit_counter;
    s32 remaining;

    arg0 = input0;
    arg2 = input2;
    arg3 = input3;

    if (*D_80083462 & 0x4000) {
        func_800A9A0C(arg3);
        goto done;
    }
    if (!(*D_80083462 & 0x2000)) {
        goto done;
    }
    func_800A19E4(arg2, arg3, 3, 6, arg0 + 0x9C);
    temp_a0 = arg2->unk_26;
    if (temp_a0 < 0) {
        goto scan_start;
    }
    tail_arg = arg2;
    if (!(D_800E2970[temp_a0].flags & 2)) {
        goto scan_start;
    }
    ASM_KEEP(tail_arg);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
    func_800CA598(tail_arg);
    goto done;

write_hit:
    ((S_800CA444_1 *)arg3)->unk_2A = temp_s0;
    ((S_800CA444_5 *)((arg3 + (((S_800CA444_1 *)arg3)->unk_71 & 0x7F))))->unk_74 = (u8) arg2->unk_24.at00.v;
    ((S_800CA444_5 *)((arg3 + (((S_800CA444_1 *)arg3)->unk_71 & 0x7F))))->unk_7C = (u8) arg2->unk_24.at01.v;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    first_dir = (unsigned long) D_8006CCD8;
    hit_counter = ((S_800CA444_1 *)arg3)->unk_71;
    temp_a0_2 = ((u16) ((S_800CA444_1 *)arg3)->unk_2A >> 8) & 0xE;
    hit_counter++;
    first_dir = temp_a0_2 + first_dir;
    ((S_800CA444_1 *)arg3)->unk_71 = (u8) hit_counter;
    arg2->unk_24.at00.v = (u8) (arg2->unk_24.at00.v + *(u8 *) first_dir);
    arg2->unk_24.at01.v = (u8) (arg2->unk_24.at01.v + D_8006CCE8[temp_a0_2]);
    goto state_done;

scan_start:
    if (((S_800CA444_1 *)arg3)->unk_46 & 0x8000) {
        var_s1 = 0;
    } else {
        func_800A0E6C(arg2, ((S_800CA444_2 *)arg0)->unk_9C, arg3, arg0 + 0x98);
        var_s1 = 0;
    }
    temp_s4 = D_8006CD00;
    temp_s6 = D_80082E80;
scan_loop:
    temp_v1 = ((S_800CA444_1 *)arg3)->unk_2A;
    if (((S_800CA444_2 *)arg0)->unk_98 & 2) {
        table_value = ((S_800CA444_3 *)(((s32) (var_s1 << 0x10) >> 0xF) + (u32) temp_s4))->unk_00;
        temp_s0 = temp_v1 - table_value;
        goto calc_call;
    }
    table_value = ((S_800CA444_3 *)(((s32) (var_s1 << 0x10) >> 0xF) + (u32) temp_s4))->unk_00;
    temp_s0 = temp_v1 + table_value;
    goto calc_call;
calc_call:
    if ((func_800CA1E0(temp_s0, arg2, arg3, 0x20) << 0x10) > 0) {
        goto write_hit;
    }
    if (var_s1 != 0) {
        next_s1 = var_s1 + 1;
        goto scan_increment;
    }
    if (temp_s6[0x12] == arg2->unk_24.at00u.v) {
        next_s1 = var_s1 + 1;
        goto scan_increment;
    }
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    if ((func_8009A180(arg3, ((S_800CA444_4 *)(*D_800814A8))->unk_58 + 0x20) << 0x10) != 0) {
        goto done;
    }
    next_s1 = var_s1 + 1;
scan_increment:
    var_s1 = next_s1;
    if (next_s1 < 8) {
        goto scan_loop;
    }
    goto state_done;

state_done:
    state_idx = ((s32) (var_s1 << 0x10)) >> 0x10;
    if (state_idx < 8) {
        goto state_long;
    }
    ((S_800CA444_1 *)arg3)->unk_71 = (u8) (((S_800CA444_1 *)arg3)->unk_71 & 0x7F);
    ((S_800CA444_1 *)arg3)->unk_46 = (u16) (((S_800CA444_1 *)arg3)->unk_46 & 0x7FFF);
    func_800A9A0C(arg3);
    goto done;

state_long:
    ((S_800CA444_1 *)arg3)->unk_46 = (u16) (((S_800CA444_1 *)arg3)->unk_46 & 0x7FFF);
    ((S_800CA444_2 *)arg0)->unk_9C = (s8) (u8) arg2->unk_26;
    ((S_800CA444_1 *)arg3)->unk_6D.u = (u8) (((S_800CA444_1 *)arg3)->unk_6D.u - 1);
    D_80083460[4] = (u16) (D_80083460[4] + 1);
    remaining = ((S_800CA444_1 *)arg3)->unk_6D.s;
    if (remaining == 0) {
        ((S_800CA444_1 *)arg3)->unk_71 = (u8) (((S_800CA444_1 *)arg3)->unk_71 & 0x7F);
        goto done;
    }
    var_s1 = func_800BCB04((arg2->unk_24.at00.v << 6) | 0x20, (arg2->unk_24.at01.v << 6) | 0x20, (s16) (((S_800CA444_1 *)arg3)->unk_88 - 0x20));
    temp_v0 = (s16) (((s32) var_s1 << 0x10) >> 0x10);
    if (temp_v0 < 0x200) {
        ((S_800CA444_1 *)arg3)->unk_88 = (u16) var_s1;
    }

done:
    return;
}
