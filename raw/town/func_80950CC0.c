#include "common.h"

extern u8 D_80016034[16];
extern u8 D_8001606C[];
extern u8 D_80016124[];
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
    u8 pad_044[0x1D4];
    u32 field_218;
    u32 field_21C;
    const void *field_220;
    u32 field_224;
    u32 field_228;
    u32 field_22C;
    u32 field_230;
    u32 field_234;
    u32 field_238;
    u32 field_23C;
    u32 field_240;
    u8 pad_244[0x100];
    u32 field_344;
    const void *field_348;
    u32 field_34C;
    u32 field_350;
    const void *field_354;
    u32 field_358;
} OverlayInitData;

static const OverlayInitData s_overlay_init __asm__("func_80950CC0")
    __attribute__((section(".text.func_80950CC0"))) = {
        0x8000, { 0 }, 1, 0x8000, { 0 },
        0x101, 0x3F0, 0, 0x16000, D_80016124, { 0 },
        0x14000, 1, D_8001606C, 0x50, 0x01A000E0,
        0x14000, 1, 0, 9, 0x01200180,
        0x8000, { 0 }, 0x4C070707, D_80016AF0, 1,
        0x4C070707, D_80016A90, 0x10F48,
    };
#endif

void func_8095101C(void) {
    D_80016D08[0] = D_80016034;
}

#ifdef __mips__
/* GCC 2.x does not emit ELF size metadata for C objects.  The retail symbol
 * spans this initialized block and the immediately following leaf. */
__asm__(".globl func_80950CC0\n"
        ".size func_80950CC0, 884");
#endif
