#include "common.h"
#include "shared/dungeon_status.h"

typedef struct {
    s8 pad[0xA];
    s16 unk0A;
    s32 unk0C;
} Struct_D_80083460;


/* Returns whether either state field at offset 0x0A or 0x0C is nonzero. */
s32 has_pending_action_or_turn_count(void) {
    s32 has_value;

    has_value = 0;
    if ((((s32)g_dungeon_status.unk_0C) != 0) || (g_dungeon_status.unk_0A != 0)) {
        has_value = 1;
    }
    return has_value;
}
