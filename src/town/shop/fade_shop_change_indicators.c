#include "common.h"
#include "engine/graphics.h"
#include "shared/item_menu.h"
#include "town/shop.h"

typedef struct { u8 r; u8 g; u8 b; u8 cd; } Color800497F4;
typedef struct { s32 unk0; Color800497F4 *unk4; } Struct800497F4;


typedef struct S_800B07D0_2 {
    u8 pad_00[0x74];
    s32 unk_74;
    s32 unk_78;
} S_800B07D0_2;   /* ((S_800B07D0_1 *)arg0)->unk_CC in fade_shop_change_indicators */


void fade_color_to_gray(Struct800497F4 *object, s32 stop_at_gray);

   /* Process the embedded data and pass the record flag bits to its two linked handles. */
void fade_shop_change_indicators(ShopEmbeddedDataObject *record) {
    advance_timed_tagged_stream(record->embedded_stream_storage + 8);
    fade_color_to_gray(((S_800B07D0_2 *)(record->embedded_data))->unk_74, record->flags_1C & 2);
    fade_color_to_gray(((S_800B07D0_2 *)(record->embedded_data))->unk_78, record->flags_1C & 1);
}
