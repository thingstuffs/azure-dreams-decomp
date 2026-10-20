#include "common.h"
#include "records/Rec_func_800AF254_arg1.h"


typedef struct S_800AFD00_1 {
    u8 pad_00[0x98];
    s32 unk_98;
    s32 unk_9C;
} S_800AFD00_1;   /* ((Rec_func_800AF254_arg1 *)arg0)->unk_A8.as_pv in reset_item_menu_entity_state */
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
s32 advance_timed_tagged_stream();                         /* extern */
void update_item_menu_selection();                      /* extern */


/* Reset the entity sub-object and its two linked handles, then finalize the update. */
void reset_item_menu_entity_state(void *entity) {
    advance_timed_tagged_stream(entity + 0x1C);
    fade_color_to_gray(((S_800AFD00_1 *)(((Rec_func_800AF254_arg1 *)entity)->unk_A8.as_pv))->unk_98, 0);
    fade_color_to_gray(((S_800AFD00_1 *)(((Rec_func_800AF254_arg1 *)entity)->unk_A8.as_pv))->unk_9C, 0);
    update_item_menu_selection(entity);
}
