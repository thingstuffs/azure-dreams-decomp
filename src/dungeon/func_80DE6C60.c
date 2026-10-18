#include "modules/dungeon_ovl_e0365c.h"

void func_80174460(void *record) {
 u8 *original;
 u8 *current;
 u8 *cursor;
 cursor=append_entity_display_text(record,current=get_unused_text_buffer());
 original=current;
 current=cursor;
 func_80099290((s8 *)expand_text_control_codes(D_801745CC,current));
 display_text_with_fullwidth_adjustment((s8 *)original);
}
