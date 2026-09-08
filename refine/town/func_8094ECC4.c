#include "common.h"

extern u8 D_80016034[16];
extern u8 D_80016070[];
extern u8 D_80016128[];
extern u8 D_80016A90[];
extern u8 D_80016AF0[];
extern u8 *D_80016D08[3];

#ifdef __mips__
typedef struct OverlayInitData {
    u32 field_000;
    u8 pad_004[0x14];
    u32 field_018;
    u32 field_01C;
    u8 pad_020[0x10];
    u32 field_030;
    u32 field_034;
    u32 field_038;
    u32 field_03C;
    const void *field_040;
    u32 field_044;
    u32 field_048;
    u8 pad_04C[0x1C4];
    u32 field_210;
    u32 field_214;
    const void *field_218;
    u32 field_21C;
    u32 field_220;
    u32 field_224;
    u32 field_228;
    u32 field_22C;
    u32 field_230;
    u32 field_234;
    u32 field_238;
    u32 field_23C;
    u32 field_240;
    u32 field_244;
    u32 field_248;
    u32 field_24C;
    u8 pad_250[0xF0];
    u32 field_340;
    const void *field_344;
    u32 field_348;
    u32 field_34C;
    const void *field_350;
    u32 field_354;
} OverlayInitData;

const OverlayInitData func_8094ECC4
    __attribute__((section(".text.func_8094ECC4"))) = {
        0x8000, { 0 }, 1, 0x8000, { 0 },
        0x101, 0x3F0, 0, 0x16000, D_80016128,
        0, 0x626F2064, { 0 },
        0x14000, 1, D_80016070, 0x50, 0x02600180,
        0x14000, 1, 0, 0x66, 0x01200180,
        0x14000, 1, 0, 0x67, 0x01400140,
        0x8000, { 0 }, 0x4C070707, D_80016AF0, 1,
        0x4C070707, D_80016A90, 0x10F48,
    };
#endif

/* Initializes the first buffer pointer to D_80016034. */
void func_8094F01C(void) {
    D_80016D08[0] = D_80016034;
}

#ifdef __mips__
/* GCC 2.x does not emit ELF size metadata for C objects.  The retail symbol
 * spans this initialized block and the immediately following leaf. */
__asm__(".size func_8094ECC4, 880");
#endif
