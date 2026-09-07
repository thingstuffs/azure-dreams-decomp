#include "common.h"

extern u8 D_80083498[];

extern u8 *func_8003FD64();
extern void func_8004491C();
extern void func_80045340(void);
extern u32 func_800A6D30(void);
extern void func_800A48F0();
extern void func_800A9C18();
extern void func_800AA36C();

extern void func_8016AE9C(void);
extern void func_8016EED8(void);
extern void func_8016EF00(void);
extern void func_8016AA98(void);

u8 *func_8016A894(s32 arg0, u8 arg1, u8 arg2, s16 arg3)
{
    register s32 mode_arg ASM_REG("$18") = arg0;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register u8 byte_arg1 ASM_REG("$21") = arg1;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register s16 half_arg3 ASM_REG("$17") = arg3;   /* MATCH pin: retail schedule: same instructions, different order without it */
    register u8 byte_arg2 ASM_REG("$20") = arg2;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    u8 *result;
    u8 *allocation;
    u8 *part_a;
    u8 *part_b;
    u8 *secondary;
    s16 saved_arg0;

    ASM_KEEP_NV(mode_arg);   /* MATCH pin: retail schedule: same instructions, different order without it */
    result = 0;
    allocation = func_8003FD64(0x112, D_80083498);
    if (allocation == 0) {
        goto done;
    }

    saved_arg0 = mode_arg;
    result = allocation + 0x20;
    ASM_KEEP(result);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    result[0x13] = 14;
    func_8004491C(allocation, func_80045340);

    part_a = *(u8 **)(allocation + 8);
    *(s16 *)(part_a + 10) = half_arg3;
    part_b = *(u8 **)(allocation + 12);
    part_b[37] = byte_arg2;
    secondary = result;
    part_b[36] = byte_arg1;

    if ((mode_arg & 3) == 1) {
        *(void (**)(void))(result + 140) = func_8016AE9C;
        *(u32 *)(result + 20) |= 0x6000;
        *(u32 *)(result + 28) |= 0x6000;
        *(void (**)(void))(part_b + 44) = func_8016EED8;
        goto common_tail;
    }

    if ((mode_arg & 3) >= 2) {
        *(void (**)(void))(result + 140) = func_8016AE9C;
        *(u32 *)(result + 20) |= 0x2000;
        *(u32 *)(result + 28) |= 0x2000;
        *(void (**)(void))(part_b + 44) = func_8016EED8;
        goto common_tail;
    }

    if ((s16)(mode_arg & -4) != 0) {
        goto high_variant;
    }

    if ((*(u32 *)(result + 20) & 0x200) == 0) {
        if ((func_800A6D30() & 1) != 0) {
            func_800A48F0(result, 1,
                           (func_800A6D30() & 0x3F) | 0x20);
            *(void (**)(void))(part_b + 44) = func_8016EF00;
        }
    }
    *(void (**)(void))(secondary + 140) = func_8016AE9C;
    goto load_handler;

high_variant:
    *(void (**)(void))(result + 140) = func_8016AE9C;

load_handler:
    *(void (**)(void))(part_b + 44) = func_8016EED8;

common_tail:
    ASM_USE(mode_arg);   /* MATCH pin: load-bearing for the whole function shape */
    *(void (**)(void))(allocation + 16) = func_8016AA98;
    func_800A9C18(allocation, part_a, part_b, saved_arg0);

    secondary[154] = 0xFF;
    ((signed char *)secondary)[156] = -1;
    func_800AA36C(secondary, part_a, part_b, result);

done:
    return result;
}
