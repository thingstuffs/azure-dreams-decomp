#include "common.h"
#include "engine/graphics.h"
#include "town/shop.h"

typedef struct {
    u8 r;
    u8 g;
    u8 b;
    u8 cd;
} Color800497F4;
typedef struct {
    s32 unk0;         /* flag/counter; function is a no-op when 0 */
    Color800497F4 *unk4; /* pointer to the object's color */
} Struct800497F4;
void fade_color_to_gray(Struct800497F4 *object, s32 stop_at_gray);                /* extern */

/* Resets the object substate and its two referenced resources. */
void fade_menu_side_indicators(ShopRecordResetObject *object) {
    advance_timed_tagged_stream(&object->stream_state);
    fade_color_to_gray((Struct800497F4 *)object->record_resources[38], 0);
    fade_color_to_gray((Struct800497F4 *)object->record_resources[39], 0);
}
