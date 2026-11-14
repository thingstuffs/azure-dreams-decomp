#include "common.h"
#include "engine/script.h"
#include "town/map/object.h"
#include "shared/object_node.h"
#include "town/map/object_callbacks_api.h"

/* extern */


typedef struct S_800A54FC_0 {
    u8 pad_00[0x4];
    s16 unk_04;
    u8 pad_06[0x16];
    s32 * unk_1C;
} S_800A54FC_0;   /* arg0 in select_title_handler_when_script_idle */

/* Initialize the object value and handler when service_script_controller returns zero. */
void select_title_handler_when_script_idle(S_800A54FC_0 *object, ObjectNodeHeader *value_1, s32 value_2, s32 value_3) {
    if (service_script_controller() == 0) {
        object->unk_04 = 0x400;
        object->unk_1C = select_title_object_handler;
    }
}
