#include "common.h"

extern u8 D_80080A8A;
extern u32 D_80081494;
extern u8 D_800814AC;
extern u8 D_800814A4;

/* Restores saved state when requested; otherwise saves the current state. */
void func_800439F8(void)
{
    if (D_80080A8A != 0) {
        u8 *ram_page;
        u32 state_word;
        u8 state_byte_4;
        u8 state_byte_6;
        ram_page = (u8 *)0x80010000;
        state_word = D_80081494;
        state_byte_4 = D_800814AC;
        state_byte_6 = D_800814A4;
        D_80080A8A = 0;
        *(u32 *)(ram_page + 0x3180) = state_word;
        *(u8 *)(ram_page + 0x3184) = state_byte_4;
        *(u8 *)(ram_page + 0x3186) = state_byte_6;
    } else {
        u8 *ram_page;
        u32 state_word;
        u8 state_byte_4;
        u8 state_byte_6;
        ram_page = (u8 *)0x80010000;
        state_word = *(u32 *)(ram_page + 0x3180);
        state_byte_4 = *(u8 *)(ram_page + 0x3184);
        state_byte_6 = *(u8 *)(ram_page + 0x3186);
        D_80081494 = state_word;
        D_800814AC = state_byte_4;
        D_800814A4 = state_byte_6;
    }
}
