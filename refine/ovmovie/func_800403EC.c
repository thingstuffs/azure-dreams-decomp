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

extern unsigned long long func_80176C7C(s32, void *, s32);
extern s32 D_801781E0[3];
extern void *D_80189390[3];

/* Initializes movie buffer pointers and frame rectangles for the current mode. */
s32 func_800403EC(Struct800403EC *movie, s32 frame_x, s32 frame_y, s32 next_frame_x, s32 next_frame_y) {
    Struct800403EC *state = movie;
    s32 x = frame_x;
    s32 y = frame_y;
    register s32 buffer_offset ASM_REG("$4") = 0x15A40;   /* MATCH pin: retail address form (%hi/%lo vs buffer_base+offset) depends on it */
    s32 next_buffer_offset = 0x22AB0;
    register s32 work_offset ASM_REG("$6") = 0x10040;   /* MATCH pin: retail immediate-load split depends on it */
    register u8 *buffer_base ASM_REG("$3") = D_80189390[0];   /* MATCH pin: load-bearing for the whole function shape */
    s32 movie_flags = D_801781E0[0];
    void *next_buffer;

    state->unk08 = 0;
    state->unk20 = 0;
    state->unk2C = 0;
    state->unk00 = buffer_base + buffer_offset;
    next_buffer = buffer_base + next_buffer_offset;
    state->unk04 = next_buffer;
    state->unk0C = buffer_base + work_offset;
    if (movie_flags & 1) {
        register s32 wide_width ASM_REG("$2") = 0x1E0;   /* MATCH pin: retail schedule: same instructions, different order without it */
        s32 frame_height = 0xF0;

        state->unk14 = wide_width;
        state->unk1C = wide_width;
        ASM_KEEP(frame_height);   /* MATCH pin: keeps a statement from moving across a call/branch */
        func_80176C7C(next_frame_y, next_buffer, work_offset);
        return 0x18;
    }
    state->unk14 = 0x140;
    state->unk1C = 0x140;
    state->unk10 = x;
    state->unk12 = y;
    state->unk16 = 0xF0;
    state->unk18 = next_frame_x;
    state->unk1A = (s16) next_frame_y;
    state->unk1E = 0xF0;
    state->unk24 = x;
    state->unk26 = y;
    state->unk28 = 0x10;
    state->unk2A = 0xF0;
}
