#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/entity.h"

typedef struct DungeonState {
    u8 pad[0x1C];
    u32 flags;
} DungeonState;

typedef struct Object {
    u8 pad[3];
    u8 flags;
} Object;

extern u8 D_800E18C0[];
extern u8 D_80088CA8[];

extern s32 func_80042A80(Object *item);
extern s32 expand_text_control_codes(u8 *src, u8 *dst);
extern s32 write_text_byte_and_advance(s8 value, s8 *dest);
extern s32 append_typed_formatted_value(void *data, s32 buffer);
extern void clear_selected_item_flag_400(void *selection);

/* Processes an eligible object in two stages and returns the resulting value. */
s32 process_eligible_object_value(Object *object, s32 input_value) {
    s32 result = input_value;

    if (!(((u32)D_800E3D7C->flags1C) & 0x10)) {
        if ((object->flags & 0x80) || func_80042A80(object)) {
            result = expand_text_control_codes(
                D_800E18C0,
                append_typed_formatted_value(object, write_text_byte_and_advance(10, result)));
            object->flags &= 0x7F;
            clear_selected_item_flag_400(object);
            result = expand_text_control_codes(
                D_80088CA8,
                append_typed_formatted_value(object, result));
            clear_selected_item_flag_400(object);
        }
    }

    return result;
}
