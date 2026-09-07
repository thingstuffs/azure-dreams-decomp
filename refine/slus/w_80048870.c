#include "common.h"

/* Object header this function reads: same tile-dimension shape family as
 * func_8004878C / func_80047270 (a u16 tile-size word at 0x4, plus four
 * packed byte sub-fields at 0x8-0xB used to build a scaled tile-position
 * header on the stack). */
typedef struct {
    u8 pad0[4];
    u16 unk4;
    u8 pad1[2];
    u8 unk8;
    u8 unk9;
    u8 unkA;
    u8 unkB;
} S_80048870_hdr;

/* Second argument: a small record whose field at 0xC is a base pointer that
 * gets offset by data_offset to form the image-data pointer for the decode call. */
typedef struct {
    u8 pad0[0xC];
    void *unkC;
} S_80048870_rec;

/* Same shape as S_8004878C_hdr used by the sibling func_8004878C/func_80047270. */
typedef struct {
    s16 unk00;
    s16 unk02;
    s16 unk04;
    s16 unk06;
} S_8004878C_hdr;

extern void func_8004878C(void *a0, S_8004878C_hdr *a1);

/* Builds a scaled tile header and passes it with the image data to func_8004878C. */
void func_80048870(S_80048870_hdr *tile, S_80048870_rec *image, s32 data_offset)
{
    S_8004878C_hdr tile_header;

    tile_header.unk04 = (s16)((tile->unkA + 1) >> 1);
    tile_header.unk06 = (s16)(tile->unkB + 1);
    tile_header.unk00 = (s16)(((u32)tile->unk8 >> 1) + ((tile->unk4 << 6) & 0x3C0));
    tile_header.unk02 = (s16)(tile->unk9 + ((tile->unk4 << 4) & 0x100));
    func_8004878C((void *)((u8 *)image->unkC + data_offset), &tile_header);
}
