#include "common.h"
#include "town/scene.h"
#include "town/scene/motion.h"

extern s32 D_80017D4C;
extern s32 D_80017AAC;

/* Process and return the stored value. */
s32 prepare_stored_value_block(void) {
    s32 *stored_value = &D_80017D4C;

    copy_callback_value_to_destination(*stored_value, &D_80017AAC);
    return *stored_value;
}
