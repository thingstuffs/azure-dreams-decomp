#include "modules/town_map_props.h"
#include "common.h"

typedef struct TownPropAnimationActor {
    char pad0[0x68];
    s16 state;   /* 0x68 */
    char pad6A[0xA0 - 0x6A];
    s32 fieldA0; /* 0xA0 */
    s32 fieldA4; /* 0xA4 */
    s32 fieldA8; /* 0xA8 */
} S0;

typedef struct TownPropAnimationDestination {
    char pad0[0x14];
    u16 field14; /* 0x14 */
} S1;


void copy_record_state_to_destination(S0 *self, s32 unused_value, S1 *destination) {
    S0 *obj = self;
    S1 *dst = destination;
    s32 state;
    s32 callValue;

    func_800478B8(dst);
    state = obj->state;
    switch (state) {
    case 0:
        if (service_script_controller() && check_transform_identifier_and_hook(obj)) {
            callValue = obj->fieldA4;
            func_8003DB94(dst, callValue, 0);
            obj->state = (u16)obj->state + 1;
            return;
        }
        return;
    case 1:
        if (dst->field14 & 0x6000) {
            callValue = obj->fieldA8;
            func_8003DB94(dst, callValue, 0);
            obj->state = (u16)obj->state + 1;
            return;
        }
        return;
    case 2:
        if (service_script_controller() && check_transform_identifier_and_hook(obj)) {
            return;
        }
        obj->state = (u16)obj->state + 1;
        return;
    case 3:
        if (!(service_script_controller() && check_transform_identifier_and_hook(obj))) {
            return;
        }
        callValue = obj->fieldA0;
        func_8003DB94(dst, callValue, 0);
        obj->state = (u16)obj->state + 1;
        return;
    case 4:
        if (service_script_controller()) {
            if (check_transform_identifier_and_hook(obj)) {
                return;
            }
        }
        obj->state = 0;
    }
}
