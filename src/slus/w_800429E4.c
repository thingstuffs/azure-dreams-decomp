#include "common.h"

#include "common.h"

typedef struct {
    u8 pad[0x14];
    s32 flags;
} InitialStats;

typedef struct {
    u8 pad[0x13];
    u8 id;
    s32 flags;
} Entity;

extern volatile InitialStats initialStatsTable[1];
extern u8 D_8006D160[9];

/* Returns the entity class from shared initial-stat flags or its lowest class flag. */
s32 func_800429E4(Entity *entity)
{
    s32 flags = entity->flags;
    s32 class_id = 0;

    if (flags & 0x2000) {
        s32 entity_id = entity->id;
        s32 stats_offset = entity_id << 1;
        s32 shared_flags;
        s32 class_bits;

        stats_offset += entity_id;
        stats_offset <<= 3;
        shared_flags = ((volatile InitialStats *)((volatile u8 *)initialStatsTable + stats_offset))->flags & flags;
        class_bits = shared_flags & 7;

        if (class_bits != 0) {
            u8 *class_table = D_8006D160;
            class_id = class_table[class_bits];
            goto done_alt;
        }

        if (flags & 1) {
            class_id = 1;
            goto done;
        }
        if (flags & 2) {
            class_id = 2;
            goto done;
        }
        if (flags & 4) {
            class_id = 3;
        }
    }

done:
    return class_id;

done_alt:
    return class_id;
}
