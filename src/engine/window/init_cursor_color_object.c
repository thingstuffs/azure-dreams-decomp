#include "common.h"

#include "common.h"

typedef s8 s8_local;

typedef struct S_80037030_0 {
    u8 pad_00[0x8];
    void ** unk_08;
    void ** unk_0C;
    void ** unk_10;
} S_80037030_0;   /* arg0 in init_cursor_color_object */

typedef struct S_80037030_1 {
    u8 pad_00[0xC];
    s32 * unk_0C;
} S_80037030_1;   /* call_arg2 in init_cursor_color_object */


extern void create_blinking_cursor_object(s32, void *, s32 *, s16, s32, s32);
extern void update_blinking_cursor_with_dark_idle(void *, void *, void *);

/* Initialize the object, install its color update callback, and run it once. */
void init_cursor_color_object(void *object, void *model, s32 *data, s16 index, s16 table_index, s32 list) {
    void *state;
    void *context;
    S_80037030_1 *output;

    create_blinking_cursor_object((s32)object, model, data, index, table_index, list);
    state = (s8_local *)object + 0x20;
    context = ((S_80037030_0 *)object)->unk_08;
    output = ((S_80037030_0 *)object)->unk_0C;
    ((S_80037030_0 *)object)->unk_10 = (void *)&update_blinking_cursor_with_dark_idle;
    output->unk_0C = 0;
    update_blinking_cursor_with_dark_idle(state, context, output);
}
