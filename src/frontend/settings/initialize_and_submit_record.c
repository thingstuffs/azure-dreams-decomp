#include "shared/object_node.h"
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

/* Initializes a node with its callback address and 48 bytes of data, then submits it. */
void initialize_and_submit_record(void *callback_address, void *data) {
    ObjectNodeHeader *record;
    Blk16 *dst;
    Blk16 *src;
    Blk16 *end;

    record = allocate_flagged_object_node(1);
    dst = (Blk16 *)(record + 1);
    if (record != 0) {
        src = data;
        end = src + 3; /* 0x30 bytes */
        do {
            *dst = *src;
            src++;
            dst++;
        } while (src != end);
        record->update_callback = callback_address;
        register_node(record, &text_sprite_builder_address);
    }
}
