#include "common.h"
#include "shared/game_state.h"
#include "dungeon/item.h"
#include "dungeon/data.h"

typedef struct S_8009F9E8_0 {
    u8 unk_00;
    u8 unk_01;
} S_8009F9E8_0;   /* p in find_matching_action_record */

/* Scan backward through special entry kinds for a matching kind and flag bit. */
void *find_matching_action_record(s32 wanted_kind, s32 wanted_flag) {
    s32 entry_index;
    s32 kind_group;
    s32 group_70;
    s32 group_78;
    s32 group_80;
    s32 group_90;
    u8 *entries;
    S_8009F9E8_0 *entry;

    entry_index = GAME_STATE->log.head.length - 1;
    entries = GAME_STATE->log_data;
    if (entry_index >= 0) {
        group_70 = 0x70;
        group_78 = 0x78;
        group_80 = 0x80;
        group_90 = 0x90;
        wanted_kind &= 0xFF;
        wanted_flag &= 0xFF;
        do {
            entry = (S_8009F9E8_0 *)(entries + entry_index * 2);
            kind_group = entry->unk_01 & 0xF8;
            if (kind_group == group_70 || kind_group == group_78 || kind_group == group_80 || kind_group == group_90) {
                if (entry->unk_01 == wanted_kind
                    && (entry->unk_00 & 0x20) == wanted_flag) {
                    return entry;
                }
            } else {
                return (GAME_STATE->log.head.length * 2) + entries;
            }
            entry_index--;
        } while (entry_index >= 0);
    }
    return entries;
}
