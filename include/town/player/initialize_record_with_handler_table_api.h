#ifndef TOWN_PLAYER_INITIALIZE_RECORD_WITH_HANDLER_TABLE_API_H
#define TOWN_PLAYER_INITIALIZE_RECORD_WITH_HANDLER_TABLE_API_H
struct ObjectPosition;
struct SpriteFrameState;

#include "common.h"

/* Town player dispatch record initialized by initialize_record_with_handler_table.
 * The initializer installs the common town handler table at +4. */
typedef struct {
    s32 unk0;
    void **unk4; /* handler table pointer installed from D_80097DE8 */
} Struct8009B1C8;


void initialize_record_with_handler_table(void *record_arg, struct ObjectPosition *setup_value, struct SpriteFrameState *sprite);

#endif
