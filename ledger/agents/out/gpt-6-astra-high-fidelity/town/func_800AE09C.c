#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80064624();                /* extern */
M2C_UNK func_80064D20();                      /* extern */
M2C_UNK func_80064D50();                      /* extern */
M2C_UNK func_80064EC0();   /* extern */
M2C_UNK func_80064EE0();   /* extern */
M2C_UNK func_80064F00();            /* extern */
M2C_UNK func_80064F20();                     /* extern */
extern M2C_UNK D_8006ADBC;
extern u8 D_80083160[];
extern u8 D_801C9E40[16];
extern u8 D_801DA714[];

typedef struct S_800AB7FC_0 {
    u8 pad_00[0x38];
    s16 unk_38;
    s16 unk_3A;
    s16 unk_3C;
    s16 unk_3E;
    s16 unk_40;
    s16 unk_42;
    s16 unk_44;
    s16 unk_46;
    s16 unk_48;
    u8 pad_4A[0xE];
    s16 unk_58;
    s16 unk_5A;
    s16 unk_5C;
    s16 unk_5E;
    s16 unk_60;
    s16 unk_62;
    s16 unk_64;
    s16 unk_66;
    s16 unk_68;
    u8 pad_6A[0xE];
    s32 unk_78;
    s32 unk_7C;
    s32 unk_80;
    s32 unk_84;
    s32 unk_88;
    u8 pad_8C[0x4];
    u8 unk_90;
    u8 unk_91;
    u8 unk_92;
} S_800AB7FC_0;   /* temp_s0 in func_800AB7FC */

typedef struct S_800AB7FC_1 {
    u8 pad_00[0x18];
    s16 unk_18;
    s16 unk_1A;
} S_800AB7FC_1;   /* temp_global_a0 in func_800AB7FC */

typedef struct S_800AB7FC_2 {
    u8 pad_00[0x18];
    s16 unk_18;
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} S_800AB7FC_2;   /* temp_s1 in func_800AB7FC */

void func_800AB7FC(void) {
    S_800AB7FC_0 *temp_s0;
    u8 *temp_s1;
    s32 temp_s2;
    void *temp_call_a0;
    S_800AB7FC_1 *temp_global_a0;
    s32 temp_v0;
    s32 temp_v1;
    s32 call_arg0;
    s32 call_arg1;
    s32 call_arg2;
    u8 *tail_base;

    temp_s1 = D_80083160;
    temp_s0 = temp_s1 + 0x18;
    temp_s2 = 0x200;
    temp_s0->unk_88 = temp_s2;
    func_80064F20(temp_s2);
    temp_s0->unk_78 = 0;
    temp_s0->unk_7C = 0;
    temp_s0->unk_80 = 0;
    func_80064EE0(0, 0, 0);
    temp_s0->unk_5A = -0x100;
    temp_s0->unk_60 = -0x100;
    temp_s0->unk_66 = -0x100;
    temp_s0->unk_5C = 0;
    temp_s0->unk_62 = 0;
    temp_s0->unk_68 = 0;
    func_80064D50(temp_s1 + 0x70);
    temp_call_a0 = temp_s1 + 0x50;
    ASM_KEEP(temp_call_a0);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    temp_v1 = -0x800;
    temp_v0 = 0x800;
    ASM_KEEP(temp_v0);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    temp_s0->unk_38 = temp_v1;
    temp_s0->unk_3C = temp_v1;
    temp_v1 = 0x800;
    temp_s0->unk_3A = temp_v0;
    temp_v0 = -0x800;
    temp_s0->unk_3E = temp_v1;
    temp_s0->unk_40 = temp_v0;
    temp_s0->unk_42 = temp_v1;
    temp_s0->unk_44 = 0;
    temp_s0->unk_46 = 0;
    temp_s0->unk_48 = 0;
    func_80064D20(temp_call_a0);
    temp_s0->unk_84 = 0x1000;
    func_80064624(0x1000, temp_s0->unk_88);
    temp_global_a0 = &D_8006ADBC;
    if ((temp_global_a0->unk_18 == 0xC) && (temp_global_a0->unk_1A != 0x34)) {
        call_arg0 = 0xA0;
        call_arg1 = call_arg0;
        call_arg2 = call_arg0;
        temp_s0->unk_58 = temp_s2;
        temp_s0->unk_5E = temp_s2;
        temp_s0->unk_64 = temp_s2;
    } else {
        call_arg0 = 0xB0;
        call_arg1 = call_arg0;
        call_arg2 = call_arg0;
        temp_s0->unk_58 = 0x3C0;
        temp_s0->unk_5E = 0x3C0;
        temp_s0->unk_64 = 0x3C0;
    }
    func_80064EC0(call_arg0, call_arg1, call_arg2);
    func_80064F00(0xA0, 0x78);
    ((S_800AB7FC_2 *)temp_s1)->unk_18 = -0xBC;
    ((S_800AB7FC_2 *)temp_s1)->unk_1A = -0x88;
    ((S_800AB7FC_2 *)temp_s1)->unk_1C = 0x172;
    ((S_800AB7FC_2 *)temp_s1)->unk_1E = 0x19A;
    temp_s0->unk_90 = 0x80;
    temp_s0->unk_91 = 0x80;
    temp_s0->unk_92 = 0x80;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    tail_base = D_801C9E40;
    tail_base[0x19] = 0;
    tail_base[0x1A] = 0;
    tail_base[0x1B] = 0;
    tail_base = D_801DA714;
    tail_base[0x19] = 0;
    tail_base[0x1A] = 0;
    tail_base[0x1B] = 0;
}
