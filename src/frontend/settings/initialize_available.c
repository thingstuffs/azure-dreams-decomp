#include "common.h"
#include "engine/node.h"
#include "engine/scene.h"
#include "frontend/settings.h"
#include "main/data.h"

typedef struct { s32 words[10]; } RecordData;

/* Initializes an available record with a value and 40 bytes of data, then submits it for processing. */
void initialize_available(s32 value, void *data) {
    s32 *record;

    record = func_8003FC64(1);
    if (record != 0) {
        *(RecordData *)(record + 8) = *(RecordData *)data;
        record[4] = value;
        register_node(record, &display_registration_tag);
    }
}
