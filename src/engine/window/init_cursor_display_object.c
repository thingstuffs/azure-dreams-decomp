#include "common.h"

#include "common.h"
#include "engine/window.h"
#include "shared/entity.h"

typedef struct S_80036ED4_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} S_80036ED4_0;   /* arg0 in init_cursor_display_object */

extern void update_blinking_cursor_with_bright_idle(void *input, ObjectPosition *unused, void *output);

/* Initialize the display object and update its initial appearance. */
void init_cursor_display_object(void *object_arg, void *display, s32 *data, s16 data_index,
                   s16 table_offset, void *list_head) {
    S_80036ED4_0 *object = object_arg;

    create_blinking_cursor_object(object, display, data, data_index, table_offset, list_head);
    update_blinking_cursor_with_bright_idle((s8 *)object + 0x20,
                  object->unk_08,
                  object->unk_0C);
}
