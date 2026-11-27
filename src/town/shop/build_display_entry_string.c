#include "common.h"
#include "shared/record_ptrs.h"
#include "m2c_compat.h"
#include "sdk/libc.h"
#include "town/shop.h"
#include "town/shop/position.h"
#include "dungeon/system.h"

extern s32 D_800892C0[3];
extern char D_800892C8[];
extern char town_monster_tamer_title_label_message[];
extern char stat_text_newline[];

typedef struct {
    s32 unk0;
    s8 unk4;
    u8 pad5[0x3B];
} StackData;

/* Builds a string from fixed fragments and selected text, then passes it to set_display_entry_text_and_position. */
void build_display_entry_string(struct ActorRecord *actor, ItemMenuPart **parts) {
    StackData text_buffer;
    StackData *text;

    text = &text_buffer;
    memcpy(text, D_800892C0, 5);
    strcat(text, ((s32)primary_actor_record) + 0x34);
    strcat(text, D_800892C8);
    strcat(text, town_monster_tamer_title_label_message);
    strcat(text, stat_text_newline);
    strcat(text, select_status_text(actor));
    set_display_entry_text_and_position(parts[3], text, 0, 0x47, 0x88);
}

/* MECHANISM: A 64-byte stack object forces the 0x68 frame; s1/s2 hold args and s0 holds its address.
   The 5-byte prefix (4 chars + NUL at D_800892C0) is copied by the inline memcpy expansion:
   move_by_pieces copies the constant source address into one register, giving lw/lb 0/4($6). */
