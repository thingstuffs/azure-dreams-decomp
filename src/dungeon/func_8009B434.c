#include "common.h"

extern s32 func_8003E4FC();
extern s32 func_8003F320();
extern s32 func_8003F6D4();
extern s32 func_800A0CA4();
extern void func_800A0DA4(void) __attribute__((noreturn));
extern s32 func_800A0DA8();

extern s8 D_800E3DA0[];
extern u8 D_800E58A8[];
extern u8 D_80164800[];
extern u8 D_8016A800[];
extern u8 D_80170800[];

s32 func_800A0B94(s32 arg0, u8 *arg1, s32 arg2) {
    u8 *entry = arg1;
    s32 value = arg0;
    s32 mode = arg2;
    s32 result = 0;
    u8 *data;
    u8 *scratch;
    s32 magnitude;
    register s32 raw_magnitude ASM_REG("$2");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    register s32 first_value ASM_REG("$5");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    register s32 shifted_value ASM_REG("$2");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    s32 signed_value;
    s32 block_size;
    register s32 tile ASM_REG("$4") = arg0;   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    s32 delta;
    register s32 term ASM_REG("$2");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    register s32 index ASM_REG("$2");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    ASM_KEEP_NV(entry);   /* MATCH pin: retail schedule: same instructions, different order without it */

    if (entry[0] != 2) {
        raw_magnitude = D_800E3DA0[entry[3]];
        magnitude = raw_magnitude;
        if (raw_magnitude < 0) {
            magnitude = -magnitude;
        }
        raw_magnitude = (s16)tile;
        if ((magnitude == raw_magnitude) && (magnitude != 0x39)) {
            entry[1] = value;
        }
    }

    if (entry[1] == 0) {
        shifted_value = (u32)value << 0x10;
        first_value = shifted_value >> 0x10;
        if (first_value == 0x38) {
            s32 call_tag;
            data = D_80164800;
            call_tag = 0x56B1;
            ASM_KEEP(data);   /* MATCH pin: retail basic-block layout depends on it */
            ASM_KEEP(call_tag);   /* MATCH pin: retail schedule: same instructions, different order without it */
            return func_800A0CA4(tile, first_value, 0x24, call_tag);
        }
        if (first_value == 0x31) {
            s32 call_tag;
            data = D_8016A800;
            call_tag = 0x569C;
            ASM_KEEP(data);   /* MATCH pin: retail basic-block layout depends on it */
            ASM_KEEP(call_tag);   /* MATCH pin: retail schedule: same instructions, different order without it */
            return func_800A0CA4(tile, first_value, 0x18, call_tag);
        }

        index = entry[3];
        ASM_KEEP(index);   /* MATCH pin: load-bearing for the whole function shape */
        block_size = 0xC;
        ASM_KEEP(block_size);   /* MATCH pin: load-bearing for the whole function shape */
        tile = index * 3;
        data = D_80170800 - (tile << 13);
        delta = first_value - 1;
        term = delta * 0x54;
        ASM_KEEP(first_value);   /* MATCH pin: load-bearing for the whole function shape */
        tile = (tile << 2) + 0x4340;
        scratch = D_800E58A8;
        func_8003F6D4(block_size, data, scratch, term + tile);
        func_8003E4FC(6, scratch, 0);

        if ((mode << 0x10) != 0) {
            func_8003F320();
            if (entry[0] != 2) {
                D_800E3DA0[entry[3]] = value;
            }
            result = *(s32 *)data;
            *(s32 *)(entry + 4) = result;
            return func_800A0DA8();
        }

        if (entry[0] != 2) {
            D_800E3DA0[entry[3]] = -value;
            return func_800A0DA8();
        }
        goto done;
    }

    if (entry[0] != 2) {
        D_800E3DA0[entry[3]] = value;
    }
    signed_value = (s16)value;
    if (signed_value == 0x38) {
        data = D_80164800;
        ASM_TAILSLOT_PIN(data);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        func_800A0DA4();
    }
    if (signed_value == 0x31) {
        data = D_8016A800;
        ASM_TAILSLOT_PIN(data);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        func_800A0DA4();
    }
    data = D_80170800 - (entry[3] * 0x6000);
    result = *(s32 *)data;

done:
    return result;
}
