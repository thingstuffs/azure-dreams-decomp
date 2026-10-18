#include "common.h"
#include "shared/object_node.h"
#include "shared/dungeon_status.h"


#ifndef NULL
#define NULL 0
#endif


void *func_8003FD64();
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

typedef struct S_800C4D78_1 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800C4D78_1;   /* counter_base in create_view_color_flash */

/* Creates an object with the supplied payload, optionally triggers an event, and increments the counter. */
void create_view_color_flash(s32 payload, s16 trigger_event) {
    S_800C4D78_0 *object;
    s16 held_event = trigger_event;

    object = func_8003FD64(0x200, ((s32 *)&D_80083498.next));
    if (object != NULL) {
        object->unk_26 = 0x20;
        object->unk_10 = &tick_view_color_flash;
        object->unk_20 = payload;
        if ((held_event << 0x10) != 0) {
            play_sound_if_enabled(0x501);
        }
        g_dungeon_status.unk_0A =
            (u16)(((u16)g_dungeon_status.unk_0A) + 1);
    }
}

/* MECHANISM: A short-lived D_80083460 base preserves the retail lui/addiu/lhu form.
   Pinned arg roles reproduce s1=payload and s0=trigger_event across the allocator call.
   Tail keepalives force sw-before-sll while leaving the retail prologue schedule intact. */
