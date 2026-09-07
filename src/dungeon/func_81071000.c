/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

typedef struct S_FUNC_81071000_BODY_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_FUNC_81071000_BODY_0;   /* temp_v0 in FUNC_81071000_BODY */

typedef struct S_FUNC_81071000_BODY_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0x78];
    u16 unk_98;
} S_FUNC_81071000_BODY_1;   /* var_s0 in FUNC_81071000_BODY */

typedef struct S_FUNC_81071000_BODY_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_FUNC_81071000_BODY_2;   /* temp_s4 in FUNC_81071000_BODY */

typedef struct S_FUNC_81071000_BODY_3 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    M2C_UNK * unk_2C;
} S_FUNC_81071000_BODY_3;   /* temp_s2 in FUNC_81071000_BODY */

typedef struct S_FUNC_81071000_BODY_4 {
    u8 pad_00[0x8C];
    M2C_UNK * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
    u8 pad_9D[0xD];
    s16 unk_AA;
} S_FUNC_81071000_BODY_4;   /* temp_s5 in FUNC_81071000_BODY */

void *func_8003FD64();
M2C_UNK func_8004491C();
M2C_UNK func_800A48F0();
s32 func_800A6D30();
M2C_UNK func_800A9C18();
M2C_UNK func_800AA36C();
void func_80158A10(void) __attribute__((noreturn));
extern M2C_UNK D_80045340;
extern M2C_UNK D_80083498;
extern M2C_UNK D_80158AA4;
extern M2C_UNK D_80158F68;
extern M2C_UNK D_8015BFB8;
extern M2C_UNK D_8015C000;

#ifdef __mips__
static const u32 func_81071000_prefix_a[] __asm__("func_81071000")
    __attribute__((used, section(".text.func_81071000"), aligned(4))) = {
    0x80158898, 0x80158AA4, 0x80159394, 0x80159394,
    0x80159394, 0x801593C0, 0x80159340, 0x80159340,
    0x80159340, 0x801592EC, 0x80159324, 0x801593C0,
    0x801593C0, 0x80159384, 0x8015AAF0, 0x8015AAE8,
    0x8015AAE0, 0x8015AAF8, 0x8015AAA0, 0x8015AA98,
    0x8015AA90,
};
static const u32 func_81071000_prefix_b[]
    __attribute__((used, section(".text.func_81071000"), aligned(4))) = {
    0x97824081, 0x8E828582, 0x40819482, 0x85828282,
    0x93829282, 0x92828582, 0x44818B82, 0,
    0,
};
static const u32 func_81071000_prefix_c[]
    __attribute__((used, section(".text.func_81071000"), aligned(4))) = {
    0x8015BCBC, 0x8015BD60, 0x8015BDD8, 0x8015BE10,
    0x8015BCBC, 0x8015BD60, 0x8015BDD8, 0x8015BE70,
};
__asm__(".globl func_81071000\n"
        ".type func_81071000,@function\n"
        ".size func_81071000,676");
#define FUNC_81071000_BODY func_81071000_body
#define FUNC_81071000_ATTR __attribute__((used, section(".text.func_81071000")))
#else
#define FUNC_81071000_BODY func_81071000
#define FUNC_81071000_ATTR
#endif

FUNC_81071000_ATTR void *FUNC_81071000_BODY(s16 arg0, s8 arg1, s8 arg2, s16 arg3) {
    S_FUNC_81071000_BODY_1 *var_s0;
    s32 temp_v1;
    u16 flags98;
    S_FUNC_81071000_BODY_3 *temp_s2;
    S_FUNC_81071000_BODY_2 *temp_s4;
    S_FUNC_81071000_BODY_4 *temp_s5;
    void *temp_v0;
    register s8 saved_arg1 ASM_REG("$22");   /* MATCH pin: retail schedule: same instructions, different order without it */
    s16 saved_arg3;
    register s8 saved_arg2 ASM_REG("$21");   /* MATCH pin: retail schedule: same instructions, different order without it */
    void *call_a0;
    void *call_a1;

    var_s0 = NULL;
    saved_arg1 = arg1;
    saved_arg3 = arg3;
    saved_arg2 = arg2;
    temp_v0 = func_8003FD64(0x112, &D_80083498);
    if (temp_v0 == NULL) {
        goto done;
    }
    {
        var_s0 = temp_v0 + 0x20;
        ((S_FUNC_81071000_BODY_0 *)temp_v0)->unk_10 = &D_80158AA4;
        var_s0->unk_13 = 0x2B;
        func_8004491C(temp_v0, &D_80045340);
        temp_s4 = ((S_FUNC_81071000_BODY_0 *)temp_v0)->unk_08;
        temp_s4->unk_0A = saved_arg3;
        temp_s2 = ((S_FUNC_81071000_BODY_0 *)temp_v0)->unk_0C;
        temp_v1 = arg0 & 3;
        temp_s2->unk_25 = saved_arg2;
        temp_s5 = var_s0;
        temp_s2->unk_2C = &D_8015BFB8;
        temp_s2->unk_24 = saved_arg1;
        if (temp_v1 == 1) {
            flags98 = var_s0->unk_98;
            var_s0->unk_14 = (s32) (var_s0->unk_14 | 0x6000);
            var_s0->unk_98 = (u16) (flags98 | 0x4000);
            var_s0->unk_1C = (s32) (var_s0->unk_1C | 0x6000);
            func_80158A10();
        }
        if (temp_v1 >= 2) {
            flags98 = var_s0->unk_98;
            var_s0->unk_14 = (s32) (var_s0->unk_14 | 0x2000);
            var_s0->unk_98 = (u16) (flags98 | 0x4000);
            var_s0->unk_1C = (s32) (var_s0->unk_1C | 0x2000);
            func_80158A10();
        }
        call_a0 = temp_v0;
        if (((arg0 & ~3) << 0x10) == 0) {
            if (!(var_s0->unk_14 & 0x200)) {
                call_a1 = temp_s4;
                temp_v1 = func_800A6D30();
                call_a0 = temp_v0;
                if (!(temp_v1 & 1)) {
                    goto call_a1_setup;
                }
                var_s0->unk_1C = (s32) (var_s0->unk_1C | 0x200);
                func_800A48F0(var_s0, 1, (func_800A6D30() & 0x3F) | 0x20);
                temp_s2->unk_2C = &D_8015C000;
                goto post_a6d30;
            }
        }
        goto call_a1_setup;
post_a6d30:
        call_a0 = temp_v0;
call_a1_setup:
        func_800A9C18(call_a0, temp_s4, temp_s2, arg0);
        temp_s5->unk_9A = 0xFF;
        temp_s5->unk_9C = -1;
        temp_s5->unk_8C = &D_80158F68;
        temp_s2->unk_14 = (u16) (temp_s2->unk_14 | 0xC);
        temp_s5->unk_AA = (s16) ((u16) var_s0->unk_14 & 7);
        func_800AA36C(temp_s5, temp_s4, temp_s2, var_s0);
    }
done:
    return var_s0;
}
