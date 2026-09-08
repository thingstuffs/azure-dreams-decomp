#include "common.h"

typedef struct {
    u8  b0;
    u8  pad1;
    u8  b2;
    u8  pad3;
    u16 h4;
    u8  b6;
    u8  pad7;
} S_80048E00_Input;

/* Builds a 0x48-byte record with two color-swapped pattern blocks and returns its base. */
void *func_80048E00(void *cursor, void *pattern_data)
{
    S_80048E00_Input *pattern = (S_80048E00_Input *)pattern_data;
    s16 span;
    s32 half_span;

    *(u8  *)((u8 *)cursor + 1) = 0x81;
    *(u16 *)((u8 *)cursor + 4) = 0x10;
    *(u16 *)((u8 *)cursor + 6) = 0;

    cursor = (u8 *)cursor + 0xC;

    *(u8  *)((u8 *)cursor + 1) = 0x3A;
    *(u32 *)((u8 *)cursor + 4) = 0x201808;
    *(u32 *)((u8 *)cursor + 0xC) = 0x602820;
    *(u32 *)((u8 *)cursor + 0x10) = 0x201808;
    *(u32 *)((u8 *)cursor + 0x14) = 0x602820;

    span = (s16)pattern->h4;
    half_span = span / 2;
    *(u8 *)((u8 *)cursor + 0xA) = (u8)half_span;
    *(u8 *)((u8 *)cursor + 0xB) = pattern->b6;
    *(u8 *)((u8 *)cursor + 2) = pattern->b0;
    *(u8 *)((u8 *)cursor + 3) = pattern->b2;

    cursor = (u8 *)cursor + 0x18;

    *(u8  *)((u8 *)cursor + 1) = 0x3A;
    *(u32 *)((u8 *)cursor + 4) = 0x602820;
    *(u32 *)((u8 *)cursor + 0xC) = 0x201808;
    *(u32 *)((u8 *)cursor + 0x10) = 0x602820;
    *(u32 *)((u8 *)cursor + 0x14) = 0x201808;
    *(u8 *)((u8 *)cursor + 0xA) = (u8)half_span;
    *(u8 *)((u8 *)cursor + 0xB) = pattern->b6;
    *(u8 *)((u8 *)cursor + 2) = (u8)(pattern->b0 + half_span);
    *(u8 *)((u8 *)cursor + 3) = pattern->b2;

    cursor = (u8 *)cursor + 0x18;

    *(u16 *)((u8 *)cursor + 6) = 1;
    *(u8  *)((u8 *)cursor + 1) = 0x81;
    *(u16 *)((u8 *)cursor + 4) = 0x10;

    return (u8 *)cursor - 0x3C;
}
