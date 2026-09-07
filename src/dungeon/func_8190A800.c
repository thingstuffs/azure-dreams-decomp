#include "common.h"

#ifdef __mips__
/* Proven 43-word literal/pointer prefix; this is row data, not C code. */
static const u32 bank_words[] __asm__("func_8190A800")
    __attribute__((section(".text.func_8190A800"), aligned(4))) = {
    0x80024AD0, 0x93826681, 0x8C824081, 0x96828582,
    0x8C828582, 0x84824081, 0x84828982, 0x66818E82,
    0x40819482, 0x85828482, 0x92828382, 0x81828582,
    0x85829382, 0x00004481, 0x01000340, 0x00580060,
    0x01000340, 0x00020002, 0x80024764, 0x80024820,
    0x80024880, 0x800248A4, 0x800248C8, 0x80024904,
    0x800249E4, 0x00000020, 0x00200020, 0x00200000,
    0x0020FFE0, 0x0000FFE0, 0xFFE0FFE0, 0xFFE00000,
    0xFFE00020, 0x00000000, 0x80024BE4, 0x80024C58,
    0x80024F08, 0x80025148, 0x80025308, 0x8002552C,
    0x800255F0, 0x800255F0, 0x8002558C,
};
__asm__(".globl func_8190A800\n"
        ".type func_8190A800,@function\n"
        ".size func_8190A800,340\n");
#define BODY_NAME composite_body
#define BODY_STORAGE static
#define BODY_ATTR __attribute__((used, section(".text.func_8190A800")))
#else
#define BODY_NAME func_8190A800
#define BODY_STORAGE
#define BODY_ATTR
#endif

extern s32 func_8009D218(void *arg0, s32 arg1);
extern s32 func_800A6DA4(s32 mode, s32 value);
extern s32 func_800A2424(void *arg0, s32 arg1);
extern void func_80099844(void *arg0, void *arg1);
extern void func_800B4C7C(s32 mode, void *arg0, s32 arg2, s32 arg3);
extern u8 D_80024004[];

BODY_STORAGE void BODY_NAME(void *arg0, s32 arg1) BODY_ATTR;

BODY_STORAGE void BODY_NAME(void *arg0, s32 arg1) {
    s32 index;
    s32 limit;

    if (func_8009D218(arg0, 4) != 0) {
        return;
    }

    index = (s16)(func_800A6DA4(0, ((u8 *)arg0)[3]) - 16);
    limit = arg1 & 0xFF;
    if (index < limit) {
        if (func_800A2424(arg0, 1) != 0) {
            return;
        }
    } else if (limit == 0xFF) {
        if (func_800A2424(arg0, 1) != 0) {
            return;
        }
    }

    func_80099844(arg0, D_80024004);
    func_800B4C7C(0x53, arg0, -1, 1);
}
