#include "common.h"

/* extern */
extern s32 map_fallback_handler_address;

typedef struct S_800A54FC_0 {
    u8 pad_00[0x4];
    s16 unk_04;
    u8 pad_06[0x16];
    s32 * unk_1C;
} S_800A54FC_0;   /* arg0 in initialize_object_when_inactive */


s32 service_script_controller(void);
/* Initialize the object value and handler when service_script_controller returns zero. */
void initialize_object_when_inactive(S_800A54FC_0 *object, s32 value_1, s32 value_2, s32 value_3) {
    if (service_script_controller() == 0) {
        object->unk_04 = 0x400;
        object->unk_1C = &map_fallback_handler_address;
    }
}
