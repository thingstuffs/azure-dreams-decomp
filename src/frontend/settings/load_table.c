#include "modules/main_title_callbacks.h"
#include "common.h"
#include "shared/object_flags.h"
#include "frontend/settings.h"

extern s32 volume_slider_levels[];

typedef struct MainTitleValueEntry {
    /* 0x00 */ char pad0[4];
    /* 0x04 */ void *unk04;
    /* 0x08 */ char pad08[0x18 - 0x08];
    /* 0x18 */ s32 unk18;
} EntA;

/* Load a table value divided by four and propagate the source flag. */
void load_table(EntA *entry)
{
    unsigned short *scaled_value = (unsigned short *)((char *)entry + 0x10);
    *(short *)scaled_value = (s16)(volume_slider_levels[entry->unk18] >> 2);
    if (*(short *)((char *)entry->unk04 + 0x16) & 0x8000) {
        *(unsigned short *)((char *)entry - 2) |= 0x8000;
        object_flag_block.flags |= 0x8000;
    }
}
