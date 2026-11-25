#include "dungeon/menu_cache.h"
#include "dungeon/menu_cache_paged.h"
#include "engine/item.h"
#include "sdk/memory.h"
#include "shared/actor_property_flags.h"
#include "shared/actor_status_flags.h"

s32 menu_has_familiar(void)
{
    s32 active = 0;

    if (primary_actor_record->unk_AC.address != 0 ||
        primary_actor_record->unk_B0.address != 0) {
        active = 1;
    }
    return active;
}

enum CachedItemOption {
    OPTION_USE = 1,
    OPTION_HOLD = 2,
    OPTION_DETAILS = 3,
    OPTION_CHANGE_FAMILIAR_SLOT = 4,
    OPTION_DEPLOY_TOWN_FAMILIAR = 5,
    OPTION_DEPLOY_DUNGEON_FAMILIAR = 6,
    OPTION_OPEN_PARTY_MENU = 8,
    OPTION_OPEN_LINKED_ACTORS = 9,
    OPTION_EQUIP = 10,
    OPTION_UNEQUIP = 11,
    OPTION_USE_WITH_TARGET = 12,
    OPTION_FAMILIAR_CONFIRMATION = 13,
    OPTION_REGISTER_SOURCE_TWO = 14,
    OPTION_REGISTER_SOURCE_ONE = 15,
    OPTION_USE_MARKED = 16,
    OPTION_SELECT_FAMILIAR_TARGET = 17,
    OPTION_USE_SIMPLE = 18,
};

/* Populate the available actions for the current item and its source. */
void build_item_action_options(CachedPagedMenu *menu)
{
    s32 index = 0;
    s32 format = itemCategoryTable[menu->item->kind].name_format;

    bzero(menu->entry_ids, sizeof(menu->entry_ids));
    if (format == 0) {
        const ItemRecord *records;
        if (menu->source_mode == 2) {
            menu->entry_ids[index++] = OPTION_REGISTER_SOURCE_TWO;
        } else if (menu->source_mode == 1) {
            menu->entry_ids[index++] = OPTION_REGISTER_SOURCE_ONE;
        }
        records = itemCategoryTable[menu->item->kind].records;
        if (records[menu->item->unk_00].flags & 0x800) {
            menu->entry_ids[index++] = OPTION_USE_MARKED;
        } else {
            menu->entry_ids[index++] = OPTION_USE;
        }
        if (menu->source_mode != 1) {
            menu->entry_ids[index++] = OPTION_HOLD;
        }
        if (read_item_category_flag_ten(menu->item)) {
            menu->entry_ids[index++] = OPTION_DETAILS;
        }
        if (menu_has_familiar()) {
            menu->entry_ids[index++] = OPTION_SELECT_FAMILIAR_TARGET;
        }
    } else if (format == 1) {
        if (menu->source_mode == 2) {
            menu->entry_ids[index++] = OPTION_REGISTER_SOURCE_TWO;
        } else if (menu->source_mode == 1) {
            menu->entry_ids[index++] = OPTION_REGISTER_SOURCE_ONE;
        }
        menu->entry_ids[index++] = (menu->item->unk_03 & 0x20) ? OPTION_UNEQUIP : OPTION_EQUIP;
        if (menu->source_mode != 1) {
            menu->entry_ids[index++] = OPTION_HOLD;
        }
        if (menu_has_familiar()) {
            menu->entry_ids[index++] = OPTION_SELECT_FAMILIAR_TARGET;
        }
    } else if (format == 2) {
        if (menu->source_mode == 2) {
            menu->entry_ids[index++] = OPTION_REGISTER_SOURCE_TWO;
        } else if (menu->source_mode == 1) {
            menu->entry_ids[index++] = OPTION_REGISTER_SOURCE_ONE;
        }
        if (menu->source_mode == 0) {
            menu->entry_ids[index++] = OPTION_USE_WITH_TARGET;
        }
        if (menu->source_mode != 1) {
            menu->entry_ids[index++] = OPTION_HOLD;
        }
        if (read_item_category_flag_ten(menu->item)) {
            menu->entry_ids[index++] = OPTION_DETAILS;
        }
        if (menu_has_familiar()) {
            menu->entry_ids[index++] = OPTION_SELECT_FAMILIAR_TARGET;
        }
    } else if (format == 3) {
        if (menu->source_mode == 0) {
            ActorRecord *actor = (ActorRecord *)(unsigned long)(u32)resolve_item_record_slot_value(menu->item);
            if (menu->owner_action == 1) {
                menu->entry_ids[index++] = OPTION_CHANGE_FAMILIAR_SLOT;
            } else {
                menu->entry_ids[index++] = OPTION_FAMILIAR_CONFIRMATION;
            }
            menu->entry_ids[index++] = actor->town_monster_slot >= 65 ? OPTION_DEPLOY_DUNGEON_FAMILIAR : OPTION_DEPLOY_TOWN_FAMILIAR;
            if (actor->flags14 & ACTOR_PARTY_MEMBER) {
                menu->entry_ids[index++] = OPTION_OPEN_PARTY_MENU;
                if (actor->flags1C & ACTOR_PLAYER_AWARE) {
                    menu->entry_ids[index++] = OPTION_OPEN_LINKED_ACTORS;
                }
            }
            menu->entry_ids[index++] = OPTION_DETAILS;
        }
    } else if (format == 4) {
        menu->entry_ids[0] = OPTION_USE_SIMPLE;
        index = 1;
    }
    menu->entry_count = index;
}

const char *get_paged_item_action_label(s32 action)
{
    return cached_paged_item_action_labels[action];
}
