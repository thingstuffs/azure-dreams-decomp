#include "common.h"

extern u8 D_80080A8A[12];
extern u32 D_80081494[3];
extern u8 D_800814AC[12];
extern u8 D_800814A4[12];

/* Restores saved state when requested; otherwise saves the current state. */
void func_800439F8(void)
{
    if (D_80080A8A[0] != 0) {
        u8 *ram_page;
        register u32 state_word ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        u8 state_byte_4;
        register u8 state_byte_6 ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        ram_page = (u8 *)0x80010000;
        state_word = D_80081494[0];
        state_byte_4 = D_800814AC[0];
        state_byte_6 = D_800814A4[0];
        D_80080A8A[0] = 0;
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
        D_80081494[0] = state_word;
        D_800814AC[0] = state_byte_4;
        D_800814A4[0] = state_byte_6;
    }
}
