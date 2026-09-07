#include "common.h"
#include "m2c_compat.h"

typedef struct S_80BFD000_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    u8 * unk_10;
} S_80BFD000_0;   /* temp_v0 in BODY_NAME */

typedef struct S_80BFD000_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_80BFD000_1;   /* var_s0 in BODY_NAME */

typedef struct S_80BFD000_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80BFD000_2;   /* temp_s4 in BODY_NAME */

typedef struct S_80BFD000_3 {
    u8 pad_00[0x24];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    M2C_UNK * unk_2C;
} S_80BFD000_3;   /* temp_s2 in BODY_NAME */

typedef struct S_80BFD000_4 {
    u8 pad_00[0x8C];
    M2C_UNK * unk_8C;
    u8 pad_90[0x2];
    s16 unk_92;
    u8 pad_94[0x6];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_80BFD000_4;   /* actor in BODY_NAME */


static const u32 func_8015E800_bank[] __asm__("func_8015E800")
    __attribute__((section(".text.func_8015E800"), aligned(4), used)) = {
    0x8015e878, 0x00000000, 0x8015f470, 0x8015f470,
    0x8015f470, 0x8015f49c, 0x8015f41c, 0x8015f41c,
    0x8015f41c, 0x8015f3e4, 0x8015f3e4, 0x8015f49c,
    0x8015f49c, 0x8015f460, 0x801606c0, 0x801606b8,
    0x801606b0, 0x801606c8, 0x80160670, 0x80160668,
    0x80160660, 0x00000000, 0x80161d4c, 0x80161d60,
    0x80161da4, 0x80161e84, 0x80161f58, 0x801620bc,
    0x80162158, 0x801621d8,
};

__asm__(".globl func_8015E800\n.size func_8015E800, 600");

#ifdef __mips__
#define BODY_NAME func_8015E878
#else
#define BODY_NAME func_8015E800
#endif

extern u8 D_80083498[];
extern u8 D_8015EA58[];
extern u8 D_80045340[];
void *func_8003FD64();
M2C_UNK func_8004491C();
M2C_UNK func_800A48F0();
s32 func_800A6D30();
M2C_UNK func_800A9C18();
M2C_UNK func_800AA36C();
extern M2C_UNK D_8015F014;
extern M2C_UNK D_8016220C;
extern M2C_UNK D_8016225C;

__attribute__((section(".text.func_8015E800")))
void *BODY_NAME(s16 arg0, s8 arg1, s8 arg2, s16 arg3) {
    s32 unksp24;
    s32 unksp28;
    s32 temp_v1;
    S_80BFD000_1 *var_s0 = NULL;
    void *temp_v0;
    S_80BFD000_3 *temp_s2;
    S_80BFD000_2 *temp_s4;
    S_80BFD000_4 *actor;
    register s8 saved_arg1 ASM_REG("$22");   /* MATCH pin: retail schedule: same instructions, different order without it */
    s16 saved_arg3;
    register s8 saved_arg2 ASM_REG("$21");   /* MATCH pin: retail schedule: same instructions, different order without it */
    s32 left;
    s32 right;
    register void *call_a0 ASM_REG("$4");   /* MATCH pin: retail delay-slot contents depend on it */
    void *call_a1;

    saved_arg1 = arg1;
    saved_arg3 = arg3;
    saved_arg2 = arg2;
    unksp28 = (s32) *(s8 *)0x21D8;
    unksp24 = (s32) *(s8 *)-0xBA0;
    temp_v0 = func_8003FD64(0x112, D_80083498);
    if (temp_v0 != NULL) {
        var_s0 = temp_v0 + 0x20;
        actor = var_s0;
        ((S_80BFD000_0 *)temp_v0)->unk_10 = D_8015EA58;
        var_s0->unk_13 = 0x10;
        func_8004491C(temp_v0, D_80045340);
        temp_s4 = ((S_80BFD000_0 *)temp_v0)->unk_08;
        temp_s4->unk_0A = saved_arg3;
        temp_s2 = ((S_80BFD000_0 *)temp_v0)->unk_0C;
        temp_v1 = arg0 & 3;
        temp_s2->unk_25 = saved_arg2;
        temp_s2->unk_2C = &D_8016220C;
        temp_s2->unk_24 = saved_arg1;
        if (temp_v1 == 1) {
            left = var_s0->unk_14 | 0x6000;
            right = var_s0->unk_1C | 0x6000;
            goto write_kind;
        }
        if (temp_v1 < 2) {
            goto normal_path;
        }
        left = var_s0->unk_14 | 0x2000;
        right = var_s0->unk_1C | 0x2000;
write_kind:
        var_s0->unk_14 = left;
        var_s0->unk_1C = right;
        goto common_path;
normal_path:
        if (((arg0 & ~3) << 0x10) == 0) {
            call_a0 = temp_v0;
            if (!(var_s0->unk_14 & 0x200)) {
                call_a1 = temp_s4;
                temp_v1 = func_800A6D30(call_a0);
                if (temp_v1 & 1) {
                    func_800A48F0(var_s0, 1, (func_800A6D30(call_a0) & 0x3F) | 0x20);
                    temp_s2->unk_2C = &D_8016225C;
                }
            }
        }
common_path:
        func_800A9C18(temp_v0, temp_s4, temp_s2, arg0);
        actor->unk_9A = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C = &D_8015F014;
        var_s0->unk_1C = (s32) (var_s0->unk_1C | 0x40000);
        actor->unk_92 = -0x20;
        func_800AA36C(actor, temp_s4, temp_s2, var_s0);
    }
    return var_s0;
}
