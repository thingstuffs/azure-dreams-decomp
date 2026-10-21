#ifndef FRONTEND_LIBCARD_OCCUPIED_SLOT_WINDOW_G00386_H
#define FRONTEND_LIBCARD_OCCUPIED_SLOT_WINDOW_G00386_H
/* Occupied slot window; G00386; inferred-strong; CL/PD joins as listed below, no proven or weak cut crossed */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:main/func_800105A0, CL:main/func_80010B18, CL:main/func_80010C44, CL:main/func_80010D64. */

#include "common.h"

typedef struct {
    u8 pad[8];
    s16 cmd;
    s16 arg;
} Msg80010C44;

typedef struct {
    void *data;
    Msg80010C44 *msg;
} Slot80010C44;

typedef struct {
    void *unk0;
    struct {
        s8 pad[8];
        s16 unk8;
        s16 unkA;
    } *unk4;
} UnkTarget;

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ u8 pad4[4];
    /* 0x08 */ s16 unk8;
    /* 0x0A */ u8 pad10[0x80 - 0x0A];
} EntryS80083E98;

extern s32 build_positioned_text_glyphs(void *a0, void *a1, s32 a2);
extern void func_8004E5A0(void *a0, s32 a1, void *a2);
extern void remap_flagged_string_bytes(void *a0);
extern u8 D_80078FD0[16];
extern u8 card_slot_payload[0x8000];
extern s16 D_80027F7C;
extern s16 D_800282B0;
extern void card_boot_layout_empty_slot_window(s32 *object);
extern void func_80023BE4(void *, s32, s32);
// size 0x80
extern EntryS80083E98 card_save_slot_metadata[];

extern void *decode_note_text(void *entries, u8 *text, s32 initial_octave);

/* Functions defined in this translation unit. */
void card_boot_format_occupied_slot_window(void *slot_owner);
void card_boot_layout_alternate_slot_window(void *context);
void card_boot_populate_slot_window_display(s32 *state);

#endif
