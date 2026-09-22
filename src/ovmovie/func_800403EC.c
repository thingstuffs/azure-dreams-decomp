#include "common.h"

typedef struct {
    /* 0x00 */ void *unk00;
    /* 0x04 */ void *unk04;
    /* 0x08 */ s32 unk08;
    /* 0x0C */ void *unk0C;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ s16 unk16;
    /* 0x18 */ s16 unk18;
    /* 0x1A */ s16 unk1A;
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ s32 unk20;
    /* 0x24 */ s16 unk24;
    /* 0x26 */ s16 unk26;
    /* 0x28 */ s16 unk28;
    /* 0x2A */ s16 unk2A;
    /* 0x2C */ s32 unk2C;
} Struct800403EC;

extern s32 D_801781E0[3];
extern void *D_80189390[3];

/* Initializes movie buffer pointers and frame rectangles for the current mode. */
void func_800403EC(Struct800403EC *movie, s32 frame_x, s32 frame_y, s32 next_frame_x, s32 next_frame_y) {
    s32 buffer_offset = 0x15A40;
    s32 next_buffer_offset = 0x22AB0;
    s32 work_offset = 0x10040;
    u8 *buffer_base = (u8 *)D_80189390[0];
    s32 movie_flags = *(s32 *)((u8 *)D_801781E0 + 0);   /* read through a plain pointer: the array spelling sets MEM_IN_STRUCT_P and reschedules the two global loads */

    movie->unk08 = 0;
    movie->unk20 = 0;
    movie->unk2C = 0;
    movie->unk00 = buffer_base + buffer_offset;
    movie->unk04 = buffer_base + next_buffer_offset;
    movie->unk0C = buffer_base + work_offset;
    if (movie_flags & 1) {
        movie->unk14 = 0x1E0;
        movie->unk1C = 0x1E0;
        movie->unk10 = frame_x;
        movie->unk12 = frame_y;
        movie->unk16 = 0xF0;
        movie->unk18 = next_frame_x;
        movie->unk1A = next_frame_y;
        movie->unk1E = 0xF0;
        movie->unk24 = frame_x;
        movie->unk26 = frame_y;
        movie->unk28 = 0x18;
        movie->unk2A = 0xF0;
    } else {
        movie->unk14 = 0x140;
        movie->unk1C = 0x140;
        movie->unk10 = frame_x;
        movie->unk12 = frame_y;
        movie->unk16 = 0xF0;
        movie->unk18 = next_frame_x;
        movie->unk1A = next_frame_y;
        movie->unk1E = 0xF0;
        movie->unk24 = frame_x;
        movie->unk26 = frame_y;
        movie->unk28 = 0x10;
        movie->unk2A = 0xF0;
    }
}
