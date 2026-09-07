/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

typedef struct S_80DA7000_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_80DA7000_0;   /* temp_v0 in BODY_NAME */

typedef struct S_80DA7000_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_80DA7000_1;   /* var_s0 in BODY_NAME */

typedef struct S_80DA7000_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80DA7000_2;   /* temp_s4 in BODY_NAME */

typedef struct S_80DA7000_3 {
    u8 pad_00[0x24];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    M2C_UNK * unk_2C;
} S_80DA7000_3;   /* temp_s2 in BODY_NAME */

typedef struct S_80DA7000_4 {
    u8 pad_00[0x8C];
    M2C_UNK * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_80DA7000_4;   /* temp_s5 in BODY_NAME */


#ifdef __mips__
static const u32 func_80DA7000_prefix[] __asm__("func_80DA7000")
    __attribute__((used, section(".text.func_80DA7000"), aligned(4))) = {
    0x80158874, 0x80158A3C, 0x80159208, 0x80159208,
    0x80159208, 0x80159234, 0x801591B4, 0x801591B4,
    0x801591B4, 0x80159144, 0x80159134, 0x80159234,
    0x80159234, 0x801591F8, 0x8015A98C, 0x8015A984,
    0x8015A97C, 0x8015A994, 0x8015A93C, 0x8015A934,
    0x8015A92C, 0x95824081, 0x85829382, 0x40818482,
    0x99828882, 0x8E829082, 0x93828F82, 0x93828982,
    0x35004481,
};
__asm__(".globl func_80DA7000\n"
        ".size func_80DA7000,572");
#define BODY_NAME func_80DA7074
#define BODY_ATTR __attribute__((used, section(".text.func_80DA7000")))
#else
#define BODY_NAME func_80DA7000
#define BODY_ATTR
#endif

void *func_8003FD64();
M2C_UNK func_8004491C();
M2C_UNK func_800A48F0();
s32 func_800A6D30();
M2C_UNK func_800A9C18();
M2C_UNK func_800AA36C();
void *func_80158954(void) __attribute__((noreturn));
void *func_801589C0(void) __attribute__((noreturn));
extern M2C_UNK D_80045340;
extern M2C_UNK D_80083498;
extern M2C_UNK D_80158A3C;
extern M2C_UNK D_80158E68;
extern M2C_UNK D_8015B86C;

void *BODY_NAME(s16 arg0, s8 arg1, s8 arg2, s16 arg3) BODY_ATTR;
void *BODY_NAME(s16 arg0, s8 arg1, s8 arg2, s16 arg3) {
    s32 unksp24;
    s32 sp24;
    s32 temp_v1;
    S_80DA7000_3 *temp_s2;
    S_80DA7000_2 *temp_s4;
    void *temp_v0;
    S_80DA7000_4 *temp_s5;
    S_80DA7000_1 *var_s0 = NULL;
    register s8 saved_arg1 ASM_REG("$22");   /* MATCH pin: retail schedule: same instructions, different order without it */
    register s8 saved_arg2 ASM_REG("$21");   /* MATCH pin: retail schedule: same instructions, different order without it */
    s16 saved_arg3;
    void *call_a0;
    void *call_a1;

    M2C_ERROR(/* Read from unset register $t0 */) | 0x4481;
    saved_arg1 = arg1;
    saved_arg3 = arg3;
    saved_arg2 = arg2;
    unksp24 = (s32) *(s8 *)-0x56D4;
    temp_v0 = func_8003FD64(0x112, &D_80083498);
    if (temp_v0 != NULL) {
        var_s0 = temp_v0 + 0x20;
        ((S_80DA7000_0 *)temp_v0)->unk_10 = &D_80158A3C;
        var_s0->unk_13 = 0x1A;
        func_8004491C(temp_v0, &D_80045340);
        temp_s4 = ((S_80DA7000_0 *)temp_v0)->unk_08;
        temp_s4->unk_0A = saved_arg3;
        temp_s2 = ((S_80DA7000_0 *)temp_v0)->unk_0C;
        temp_v1 = arg0 & 3;
        temp_s2->unk_25 = saved_arg2;
        temp_s5 = var_s0;
        temp_s2->unk_2C = &D_8015B86C;
        temp_s2->unk_24 = saved_arg1;
        if (temp_v1 == 1) {
            s32 flags0;
            s32 flags1;

            flags0 = var_s0->unk_14 | 0x6000;
            flags1 = var_s0->unk_1C | 0x6000;
            ASM_KEEP(flags0);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
            ASM_TAILSLOT_PIN(flags1);   /* MATCH pin: load-bearing for the whole function shape */
            return func_80158954();
        }
        if (temp_v1 >= 2) {
            var_s0->unk_14 = (s32) (var_s0->unk_14 | 0x2000);
            var_s0->unk_1C = (s32) (var_s0->unk_1C | 0x2000);
            func_801589C0();
        }
        call_a0 = temp_v0;
        if (((arg0 & ~3) << 0x10) == 0) {
            if (!(var_s0->unk_14 & 0x200)) {
                call_a1 = temp_s4;
                if (func_800A6D30() & 1) {
                    var_s0->unk_1C = (s32) (var_s0->unk_1C | 0x200);
                    func_800A48F0(var_s0, 1, (func_800A6D30() & 0x3F) | 0x20);
                }
            }
        }
        func_800A9C18(temp_v0, temp_s4, temp_s2, arg0);
        temp_s5->unk_9A = 0xFF;
        temp_s5->unk_9C = -1;
        temp_s5->unk_8C = &D_80158E68;
        func_800AA36C(temp_s5, temp_s4, temp_s2, var_s0);
    }
    return var_s0;
}
