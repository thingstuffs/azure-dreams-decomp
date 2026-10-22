#include "common.h"
#include "shared/object_node.h"
#include "shared/dungeon_status.h"
#include "dungeon/item.h"

#ifndef NULL
#define NULL 0
#endif

void *allocate_list_node();
s32 play_sound_if_enabled();
void tick_view_color_flash(void *fade);

typedef struct S_800C4D78_0 {
    u8 pad_00[0x10];
    s32 * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
    u8 pad_24[0x2];
    s16 unk_26;
} S_800C4D78_0;

/* Creates an object with the supplied payload, optionally triggers an event, and increments the counter. */
void create_view_color_flash(s32 payload, s16 trigger_event) {
    S_800C4D78_0 *object;
    s16 held_event = trigger_event;

    object = allocate_list_node(0x200, ((s32 *)&scene_object_list_anchor.next));
    if (object != NULL) {
        object->unk_26 = 0x20;
        object->unk_10 = &tick_view_color_flash;
        object->unk_20 = payload;
        if ((held_event << 0x10) != 0) {
            play_sound_if_enabled(0x501);
        }
        g_dungeon_status.activity_counts.parts.pending_action_count =
            (u16)(((u16)g_dungeon_status.activity_counts.parts.pending_action_count) + 1);
    }
}

/* MECHANISM: A short-lived D_80083460 base preserves the retail lui/addiu/lhu form. Tail keepalives
   force sw-before-sll while leaving the retail prologue schedule intact. */
