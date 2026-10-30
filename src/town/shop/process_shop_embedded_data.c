#include "common.h"
#include "shared/item_menu.h"
#include "town/shop.h"

typedef struct { u8 r; u8 g; u8 b; u8 cd; } Color800497F4;
typedef struct { s32 unk0; Color800497F4 *unk4; } Struct800497F4;


typedef struct S_800B07D0_2 {
    u8 pad_00[0x74];
    s32 unk_74;
    s32 unk_78;
} S_800B07D0_2;   /* ((S_800B07D0_1 *)arg0)->unk_CC in process_shop_embedded_data */


void func_800497F4(Struct800497F4 *object, s32 stop_at_gray);
struct FrameState; s32 advance_timed_tagged_stream(struct FrameState *);                         /* extern */

   /* Process the embedded data and pass the record flag bits to its two linked handles. */
void process_shop_embedded_data(ShopEmbeddedDataObject *record) {
    advance_timed_tagged_stream(record->embedded_stream_storage + 8);
    func_800497F4(((S_800B07D0_2 *)(record->embedded_data))->unk_74, record->flags_1C & 2);
    func_800497F4(((S_800B07D0_2 *)(record->embedded_data))->unk_78, record->flags_1C & 1);
}
