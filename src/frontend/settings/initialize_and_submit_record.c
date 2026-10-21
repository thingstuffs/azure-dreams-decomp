#include "common.h"
#include "engine/node.h"
#include "engine/scene.h"
#include "frontend/settings.h"
#include "main/data.h"

/* >8B so address-of uses %hi/%lo (not $gp) */

typedef struct {
    s32 w0;
    s32 w1;
    s32 w2;
    s32 w3;
} Blk16;

/* Initializes a record with a value and 48 bytes of data, then submits it. */
void initialize_and_submit_record(s32 value, void *data) {
    s32 *record;
    Blk16 *dst;
    Blk16 *src;
    Blk16 *end;

    record = allocate_flagged_object_node(1);
    dst = (Blk16 *)(record + 8); /* +0x20 bytes */
    if (record != 0) {
        src = (Blk16 *)data;
        end = src + 3; /* 0x30 bytes */
        do {
            *dst = *src;
            src++;
            dst++;
        } while (src != end);
        record[4] = value;
        register_node(record, &D_80053858);
    }
}
