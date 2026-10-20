#include "common.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"

typedef struct TownObject {
    void (*callback)(void);
    s8 pad_04[0x3C];
    u8 *field_40;
} TownObject;


/* Flags inactive objects; otherwise copies shared bytes and invokes the callback. */
void flag_inactive_object_or_run_callback(TownObject *object, s32 unused, u8 *output) {
    u8 *active_flag;

    active_flag = object->field_40;
    if (active_flag != 0) {
        if (*active_flag == 0) {
            ((u16 *)object)[-1] |= 0x8000;
            object_flag_block.flags |= 0x8000;
            return;
        }
    }

    output[0xC] = g_game_work.view.tint.parts.tint_r;
    output[0xD] = g_game_work.view.tint.parts.tint_g;
    output[0xE] = g_game_work.view.tint.parts.tint_b;
    object->callback();
}
