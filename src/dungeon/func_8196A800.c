#include "common.h"

#ifdef __mips__
/* Proven 31-word literal/pointer prefix; this is row data, not C code. */
static const u32 bank_words[] __asm__("func_8196A800")
    __attribute__((section(".text.func_8196A800"), aligned(4))) = {
    0x80025D68, 0x00000001, 0x00010001, 0x00010000,
    0x0001FFFF, 0x0000FFFF, 0xFFFFFFFF, 0xFFFF0000,
    0xFFFF0001, 0x01400340, 0x00400040, 0x01800340,
    0x00400040, 0x01C00340, 0x00400040, 0x01000380,
    0x00400040, 0x01400380, 0x00400040, 0x01800380,
    0x00400040, 0x01C00380, 0x00400040, 0x01000340,
    0x00400040, 0x00000000, 0x80025E58, 0x80025E90,
    0x80025F18, 0x800262CC, 0x800268F4,
};
__asm__(".globl func_8196A800\n"
        ".type func_8196A800,@function\n"
        ".size func_8196A800,292\n");
#define BODY_NAME composite_body
#define BODY_STORAGE static
#define BODY_ATTR __attribute__((used, section(".text.func_8196A800")))
#else
#define BODY_NAME func_8196A800
#define BODY_STORAGE
#define BODY_ATTR
#endif

extern s16 D_800269B4;
extern s32 D_800814A0;

BODY_STORAGE void BODY_NAME(void *state, void *unused, void *visual) BODY_ATTR;

/* Updates a countdown-driven visual and clears its owner slot when the countdown expires. */
BODY_STORAGE void BODY_NAME(void *state, void *unused, void *visual) {
    s32 remaining_ratio;
    u16 ticks_left;

    ticks_left = *(u16 *)((u8 *)state + 0x2C) - 1;
    remaining_ratio = (s32)((s32)(ticks_left << 16) >> 9) /
               (s16)*(u16 *)((u8 *)state + 0x2E);
    D_800269B4 = 1;
    *(u16 *)((u8 *)state + 0x2C) = ticks_left;
    *(u8 *)((u8 *)visual + 0x0E) += 4;
    *(s8 *)((u8 *)visual + 0x0D) = (s8)remaining_ratio;
    *(s8 *)((u8 *)visual + 0x0C) = (s8)remaining_ratio;
    if (*(s16 *)((u8 *)visual + 6) >= -6) {
        *(s16 *)((u8 *)visual + 6) -= 2;
    }
    if (*(s16 *)((u8 *)state + 0x2C) <= 0) {
        s16 *owner_slot;
        s32 slot_offset;
        s32 owner_addr;

        slot_offset = *(s16 *)((u8 *)state + 0x50) * 2;
        owner_addr = *(s32 *)((u8 *)state + 0x7C);
        owner_slot = (s16 *)(slot_offset + owner_addr + 0x64);
        *owner_slot = 0;
        *(u16 *)((u8 *)state - 2) |= 0x8000;
        D_800814A0 = D_800814A0 | 0x8000;
    }
}
