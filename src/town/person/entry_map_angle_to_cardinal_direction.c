#include "common.h"
#include "shared/object_node.h"
#include "shared/object_index_slots.h"
#include "town/person/person_object_lifecycle_g00659.h"

typedef struct {
    s32 unk0;
    void *unk4;
} Entry;

extern s32 runtime_script_state[];



extern s32 map_angle_to_cardinal_direction(s32, void *); /* Unprototyped: retail call passes more arguments than the callee reads */

/* anyone_now_ang_get: store the selected object's current angle in the script result. */
void anyone_now_ang_get(s32 object_slot) {
    s32 *script_values = runtime_script_state;
    void *entry;
    u8 *data;
    s32 angle;
    u16 angle_raw;

    if (object_slot != 0) {
        entry = object_index_slots[object_slot].object;
        if (entry != 0) {
            data = NODE_BODY(entry);
            if (object_slot == 1) {
                void *kind = *(void **)((u8 *)entry + 0x10);

                if (kind != update_object_position_or_cleanup && kind != update_object_motion_and_flags) {
                    angle_raw = *(u16 *)(data + 0x10);
                } else {
                    angle_raw = *(u16 *)(data + 0x72);
                }
            } else {
                angle_raw = *(u16 *)(data + 0x72);
            }
            angle = (s32)angle_raw << 16;
            script_values[0x12] = map_angle_to_cardinal_direction(angle >> 16, data);
        }
    }
}
