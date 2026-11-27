#include "common.h"
#include "town/scene.h"
#include "town/scene/motion.h"

extern u8 *D_80017D4C;
extern s32 home_leading_component_values[];

u8 *prepare_stored_value_block(void)
{
    u8 **stored_value = &D_80017D4C;

    copy_callback_value_to_destination(*stored_value, home_leading_component_values);
    return *stored_value;
}
