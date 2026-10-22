#ifndef TOWN_PLAYER_INITIALIZE_RECORD_WITH_HANDLER_TABLE_API_H
#define TOWN_PLAYER_INITIALIZE_RECORD_WITH_HANDLER_TABLE_API_H

#include "common.h"

/* Town player dispatch record initialized by initialize_record_with_handler_table.
 * The initializer installs the common town handler table at +4. */
typedef struct {
    s32 unk0;
    void **unk4; /* handler table pointer installed from D_80097DE8 */
} Struct8009B1C8;

void initialize_record_with_handler_table(Struct8009B1C8 *, s32, s32);

#endif
