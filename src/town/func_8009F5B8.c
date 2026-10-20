#include "town/menu/window.h"

/* Initializes an object with default transform and global state values. */
void initialize_object_transform_and_state(s32 slot_id, void *object, s32 object_id)
{

    *(s16 *)((u8 *)object + 0x20) = 0x1000;
    *(s16 *)((u8 *)object + 0x1E) = 0x1000;
    *(s16 *)((u8 *)object + 0x1C) = 0x1000;
    *(s16 *)((u8 *)object + 0x12) = 0;
    *(s16 *)((u8 *)object + 0x14) = 0;
    *(s16 *)((u8 *)object + 0x10) = 0;
    *(u8 *)((u8 *)object + 0xC) = g_game_work.view.unk_090;
    *(u8 *)((u8 *)object + 0xD) = g_game_work.view.unk_091;
    *(u8 *)((u8 *)object + 0xE) = g_game_work.view.unk_092;
    *(s16 *)((u8 *)object + 0x14) = 0;
    *(s16 *)((u8 *)object + 0x1A) = 0;
    *(s16 *)((u8 *)object + 0x18) = 0;
    *(s16 *)((u8 *)object + 0x16) = 0;
    *(s32 *)((u8 *)object + 0) = 0;
    *(s8 *)((u8 *)object + 4) = 0;
    *(s8 *)((u8 *)object + 5) = 0;
    register_node(slot_id - 0x20, D_80046398);
    *(s32 *)((u8 *)object + 8) = object_id;
}
