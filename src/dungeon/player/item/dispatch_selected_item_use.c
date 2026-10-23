#include "shared/item_ids.h"
#include "common.h"
#include "shared/tile_object.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082EB0.h"
#include "records/Rec_func_8008ACDC_arg0.h"
#include "dungeon/player.h"


typedef struct S_80095538_4 {
    u8 pad_00[0x1];
    u8 unk_01;
} S_80095538_4;   /* ((Rec_D_80082EB0 *)(&D_80082EB0))->unk_00.as_pv in dispatch_selected_item_use */

typedef struct S_80095538_0 {
    s32 unk_00;
    s32 unk_04;
    u8 pad_08[0x5C];
    s32 unk_64;
    s32 unk_68;
} S_80095538_0;   /* Pointer addresses record offset 0x18. */

typedef struct S_80095538_1 {
    union { s32 s; void * u; } unk_00;   /* accessed as both */
    s32 unk_04;
} S_80095538_1;   /* &D_80082EB0 in dispatch_selected_item_use */

void equip_item_and_update_status();              /* extern */
void change_equipped_item_and_notify();              /* extern */
s32 select_item_record_pointer();                             /* extern */

/* Dispatches an item effect or equipment update according to the item type. */
s32 dispatch_selected_item_use(Rec_func_8008ACDC_arg0 *actor, s16 item_id, s16 other_item_id) {
    s32 saved_x;
    s32 saved_y;
    s16 result;
    u8 item_type;
    void *actor_base;
    void *equipment_item;
    void *accessory_item;

    actor_base = actor;
    saved_x = ((S_80095538_0 *)((u8 *)actor_base - 0x18))->unk_00;
    saved_y = ((S_80095538_0 *)((u8 *)actor_base - 0x18))->unk_04;
    result = 1;
    ((S_80095538_1 *)(&reference_tile_object.selected_item))->unk_00.s = select_item_record_pointer(item_id);
    if (other_item_id != 0) {
        reference_tile_object.secondary_item = select_item_record_pointer(other_item_id);
    } else {
        reference_tile_object.secondary_item = 0;
    }
    item_type = ((S_80095538_4 *)(((Rec_D_80082EB0 *)(&reference_tile_object.selected_item))->unk_00.as_pv))->unk_01;
    switch (item_type) {
    case ITEM_KIND_SWORD:
    case ITEM_KIND_WAND:
        equipment_item = NULL;
        if (((S_80095538_1 *)(&reference_tile_object.selected_item))->unk_00.u != ((S_80095538_0 *)((u8 *)actor_base - 0x18))->unk_64) {
            equipment_item = ((S_80095538_1 *)(&reference_tile_object.selected_item))->unk_00.u;
        }
        equip_item_and_update_status(actor_base, equipment_item);
        break;
    case ITEM_KIND_SHIELD:
        accessory_item = NULL;
        if (((S_80095538_1 *)(&reference_tile_object.selected_item))->unk_00.u != ((S_80095538_0 *)((u8 *)actor_base - 0x18))->unk_68) {
            accessory_item = ((S_80095538_1 *)(&reference_tile_object.selected_item))->unk_00.u;
        }
        change_equipped_item_and_notify(actor_base, accessory_item);
        break;
    case ITEM_KIND_HERB:
    case ITEM_KIND_FRUIT:
    case ITEM_KIND_SEED:
    case ITEM_KIND_BALL:
    case ITEM_KIND_SCROLL:
    case ITEM_KIND_CRYSTAL:
    case ITEM_KIND_BELL:
    case ITEM_KIND_GLASSES:
    case ITEM_KIND_LOUPE:
    case ITEM_KIND_SAND:
    case 11:
    case 12:
    case 13:
    case ITEM_KIND_COIN:
        result = dispatch_dungeon_category_action(actor_base, ((S_80095538_1 *)(&reference_tile_object.selected_item))->unk_00.u, 3, 0);
        break;
    case ITEM_KIND_EGG:
        actor->unk_BC = (void *) ((S_80095538_1 *)(&reference_tile_object.selected_item))->unk_00.u;
        begin_target_flagged_action(actor, saved_x, saved_y, actor_base);
        break;
    case ITEM_KIND_FAMILIAR:
    case ITEM_KIND_ELEVATOR:
    case ITEM_KIND_TRAP:
    default:
        break;
    }
    return result;
}
