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

/* Spawn this overlay's 0x112 object: fill its two sub-parts from kind_id/variant/spawn_value, apply the 0x6000 or 0x2000 flag pair the low two bits of flags select (or the random 0x20-mask variant), and run the two setup calls. */
u8 *func_8016A894(s16 flags, u8 kind_id, u16 variant, s16 spawn_value)
{
    register u8 byte_kind_id ASM_REG("$21") = kind_id;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s16 half_spawn = spawn_value;
    u8 byte_variant = variant;
    u8 *result;
    u8 *allocation;
    u8 *part_a;
    u8 *part_b;
    u8 *secondary;
    s16 saved_flags;

    saved_flags = flags;
    result = 0;
    allocation = func_8003FD64(0x112, D_80083498);
    if (allocation == 0) {
        goto done;
    }

    result = allocation;
    result += 0x20;
    result[0x13] = 14;
    func_8004491C(allocation, func_80045340);

    part_a = *(u8 **)(allocation + 8);
    *(s16 *)(part_a + 10) = half_spawn;
    part_b = *(u8 **)(allocation + 12);
    part_b[37] = byte_variant;
    secondary = result;
    part_b[36] = byte_kind_id;

    if ((flags & 3) == 1) {
        *(void (**)(void))(result + 140) = func_8016AE9C;
        *(u32 *)(result + 20) |= 0x6000;
        *(u32 *)(result + 28) |= 0x6000;
        *(void (**)(void))(part_b + 44) = func_8016EED8;
        goto common_tail;
    }

    if ((flags & 3) >= 2) {
        *(void (**)(void))(result + 140) = func_8016AE9C;
        *(u32 *)(result + 20) |= 0x2000;
        *(u32 *)(result + 28) |= 0x2000;
        *(void (**)(void))(part_b + 44) = func_8016EED8;
        goto common_tail;
    }

    if ((s16)(flags & -4) != 0) {
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
    *(void (**)(void))(allocation + 16) = func_8016AA98;
    func_800A9C18(allocation, part_a, part_b, saved_flags);

    secondary[154] = 0xFF;
    ((signed char *)secondary)[156] = -1;
    func_800AA36C(secondary, part_a, part_b, result);

done:
    return result;
}
