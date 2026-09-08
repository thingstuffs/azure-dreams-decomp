/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

typedef struct S_80FF3000_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_80FF3000_0;   /* temp_v0 in BODY_NAME */

typedef struct S_80FF3000_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_80FF3000_1;   /* var_s0 in BODY_NAME */

typedef struct S_80FF3000_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80FF3000_2;   /* temp_s4 in BODY_NAME */

typedef struct S_80FF3000_3 {
    u8 pad_00[0x24];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    M2C_UNK * unk_2C;
} S_80FF3000_3;   /* temp_s2 in BODY_NAME */

typedef struct S_80FF3000_4 {
    u8 pad_00[0x8C];
    M2C_UNK * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_80FF3000_4;   /* temp_s5 in BODY_NAME */


void *func_8003FD64();
M2C_UNK func_8004491C();
M2C_UNK func_800A48F0();
s32 func_800A6D30();
M2C_UNK func_800A9C18();
M2C_UNK func_800AA36C();
extern void func_80158988(void) __attribute__((noreturn));
extern void func_80158A00(void) __attribute__((noreturn));
extern M2C_UNK D_80045340;
extern M2C_UNK D_80083498;
extern M2C_UNK D_80158A7C;
extern M2C_UNK D_80158EA8;
extern M2C_UNK D_8015C038;
extern M2C_UNK D_8015C088;

#ifdef __mips__
static const u32 bank_words[] __asm__("func_80FF3000")
    __attribute__((section(".text.func_80FF3000"), aligned(4))) = {
    0x801588a8, 0x80158a7c, 0x801592b8, 0x801592b8,
    0x801592b8, 0x801592e4, 0x80159264, 0x80159264,
    0x80159264, 0x801591f4, 0x801591e4, 0x801592e4,
    0x801592e4, 0x801592a8, 0x8015aac4, 0x8015aabc,
    0x8015aab4, 0x8015aacc, 0x8015aa74, 0x8015aa6c,
    0x8015aa64, 0x89824081, 0x40819382, 0x93829082,
    0x83829982, 0x85828882, 0x7c818482, 0x90829582,
    0x00004481, 0x92824081, 0x96828582, 0x81828582,
    0x85828c82, 0x40818482, 0x94828982, 0x40819382,
    0x92829482, 0x85829582, 0x90824081, 0x97828f82,
    0x92828582, 0x65004481,
};
__asm__(".globl func_80FF3000\n"
        ".size func_80FF3000, 636");
#define BODY_NAME func_80FF30A8
#else
#define BODY_NAME func_80FF3000
#endif

void *BODY_NAME(s32, s8, s8, s16)
#ifdef __mips__
    __attribute__((section(".text.func_80FF3000")))
#endif
    ;

void *BODY_NAME(s32 arg0, s8 arg1, s8 arg2, s16 arg3) {
    S_80FF3000_1 *var_s0;
    void *temp_v0;
    register s16 saved_arg3 ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    register s32 saved_arg0 ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    S_80FF3000_2 *temp_s4;
    register s8 saved_arg2 ASM_REG("$21");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    register s8 saved_arg1 ASM_REG("$22");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    s32 final_arg0;
    s32 temp_v1;
    s32 high_arg0;
    S_80FF3000_3 *temp_s2;
    S_80FF3000_4 *temp_s5;

    saved_arg0 = arg0;
    var_s0 = NULL;
    ASM_KEEP_NV(var_s0);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    ASM_KEEP_NV(saved_arg0);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    saved_arg1 = arg1;
    saved_arg3 = arg3;
    saved_arg2 = arg2;
    temp_v0 = func_8003FD64(0x112, &D_80083498);
    if (temp_v0 != NULL) {
        final_arg0 = saved_arg0;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        var_s0 = temp_v0 + 0x20;
        ((S_80FF3000_0 *)temp_v0)->unk_10 = &D_80158A7C;
        var_s0->unk_13 = 0x28;
        func_8004491C(temp_v0, &D_80045340);
        high_arg0 = (s32) &D_8015C038;
        temp_s4 = ((S_80FF3000_0 *)temp_v0)->unk_08;
        temp_s4->unk_0A = saved_arg3;
        temp_s2 = ((S_80FF3000_0 *)temp_v0)->unk_0C;
        temp_v1 = saved_arg0 & 3;
        temp_s2->unk_25 = saved_arg2;
        temp_s5 = var_s0;
        temp_s2->unk_2C = (void *) high_arg0;
        temp_s2->unk_24 = saved_arg1;
        if (temp_v1 == 1) {
            high_arg0 = var_s0->unk_14;
            temp_v1 = var_s0->unk_1C;
            high_arg0 |= 0x6000;
            temp_v1 |= 0x6000;
            ASM_TAILSLOT_PIN(temp_v1);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            ASM_KEEP(high_arg0);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
            func_80158988();
        }
        high_arg0 = temp_v1 < 2;
        if (!high_arg0) {
            high_arg0 = var_s0->unk_14;
            temp_v1 = var_s0->unk_1C;
            high_arg0 |= 0x2000;
            temp_v1 |= 0x2000;
            var_s0->unk_14 = high_arg0;
            var_s0->unk_1C = temp_v1;
            func_80158A00();
        }
        high_arg0 = saved_arg0 & ~3;
        if ((high_arg0 << 0x10) == 0) {
            if (!(var_s0->unk_14 & 0x200)) {
                if (func_800A6D30() & 1) {
                    var_s0->unk_1C = (s32) (var_s0->unk_1C | 0x200);
                    func_800A48F0(var_s0, 1, (func_800A6D30() & 0x3F) | 0x20);
                    temp_s2->unk_2C = &D_8015C088;
                }
            }
        }
        func_800A9C18(temp_v0, temp_s4, temp_s2, (s16)(s32) final_arg0);
        temp_s5->unk_9A = 0xFF;
        temp_s5->unk_9C = -1;
        temp_s5->unk_8C = &D_80158EA8;
        func_800AA36C(temp_s5, temp_s4, temp_s2, var_s0);
        return var_s0;
    }
    return var_s0;
}
