#include "common.h"

#include "common.h"
#include "engine/window.h"
#include "slus.h"

typedef struct Func37534State Func37534State;

/* Forwards the value to func_800478B8 when unlink_cursor_when_finished returns zero. */
void update_cursor_callback(s32 unused_0, s32 unused_1, s32 value) {
    if (unlink_cursor_when_finished((Func37534State *)unused_0) == 0) {
        func_800478B8(value);
    }
}
