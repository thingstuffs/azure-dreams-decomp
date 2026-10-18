#include "modules/dungeon_ovl_e0365c.h"

void func_801744B8(void *record) {
 u8 *original;
 u8 *current;
 u8 *cursor;
 cursor=append_entity_display_text(record,current=get_unused_text_buffer());
 original=current;
 current=cursor;
 func_80099290((s8 *)expand_text_control_codes(D_801745F8,current));
 display_text_with_fullwidth_adjustment((s8 *)original);
}
