#include "modules/ovmovie_game.h"

/* Initializes movie buffer pointers and frame rectangles for the current mode. */
void initialize_movie_frame_buffers(MovieBuffer *movie, s32 frame_x, s32 frame_y, s32 next_frame_x, s32 next_frame_y) {
    s32 buffer_offset = 0x15A40;
    s32 next_buffer_offset = 0x22AB0;
    s32 work_offset = 0x10040;
    u8 *buffer_base = (u8 *)D_80189390;
    s32 movie_flags = *(s32 *)((u8 *)&D_801781E0 + 0);   /* read through a plain pointer: the array spelling sets MEM_IN_STRUCT_P and reschedules the two global loads */

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
