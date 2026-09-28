#include "common.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"

typedef struct TownObject {
    void (*callback)(void);
    s8 pad_04[0x3C];
    u8 *field_40;
} TownObject;


/* Flags inactive objects; otherwise copies shared bytes and invokes the callback. */
void func_800A2338(TownObject *object, s32 unused, u8 *output) {
    u8 *active_flag;

    active_flag = object->field_40;
    if (active_flag != 0) {
        if (*active_flag == 0) {
            ((u16 *)object)[-1] |= 0x8000;
            objectFlagBlock.flags |= 0x8000;
            return;
        }
    }

    output[0xC] = gameWork.view.unk_090;
    output[0xD] = gameWork.view.unk_091;
    output[0xE] = gameWork.view.unk_092;
    object->callback();
}
