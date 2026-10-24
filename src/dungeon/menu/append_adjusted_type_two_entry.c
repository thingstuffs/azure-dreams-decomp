#include "common.h"
#include "dungeon/menu.h"
#include "shared/game_work.h"

typedef struct Inner {
    u8 unk0[3];
    u8 type;
    s32 val4;
    s16 val8;
    s16 valA;
} Inner;

typedef struct State {
    u8 pad[0x8D0];
    Inner *next;
} State;

extern u8 upper_draw_context[16];
extern void AddPrim(void *submission_target, void *entry);

// Appends a type-2 entry with adjusted coordinates and submits it for processing.
void append_adjusted_type_two_entry(s32 x, s32 y, void *color_data, void *submissionTarget)
{
    s32 *entryValue = color_data;
    s32 maskedY = y & 0xFFFF;
    s32 adjustedY = maskedY + 0xC0;
    State *state = g_game_work.draw_buffer;
    Inner *entry = state->next;
    s32 adjustedX = x + 0x300;

    state->next = entry + 1;
    entry->type = 2;
    entry->val8 = (s16)adjustedX;
    if (state != (State *)upper_draw_context) {
        adjustedY = maskedY - 0x20;
    }
    entry->valA = (s16)adjustedY;
    entry->val4 = *entryValue;
    AddPrim(submissionTarget, entry);
}
