#include "common.h"
#include "engine/cd.h"
#include "engine/item.h"
#include "engine/scene.h"
#include "engine/util.h"
#include "slus/data.h"

/* Item-category table entry: kind at 0x0 selects 12-byte vs 20-byte record
 * layout; records pointer at 0xC. Only the byte at offset 0x1 is read here as a
 * per-category bit-flag byte. Established layout from src/w_8004A658.c. */


/* External words used to select item categories. */
extern s32 dungeon_mode_state;

extern void save_or_restore_random_seed(s32 a0);
extern void restore_dungeon_random_seed(s32 a0);

/* Shuffles item pointers in enabled categories and restores item-effect links. */
void shuffle_enabled_item_category_pointers(void)
{
    s32 category_id;
    ItemCategory *category;

    queue_mode_selected_resource_table();
    drain_cd_command_queue();
    save_or_restore_random_seed(1);
    restore_dungeon_random_seed(D_80013628);

    category = itemCategoryTable;
    for (category_id = 0; category_id < 20; category_id++, category++) {
        if (((s32)category->flags >> dungeon_mode_state) & 1) {
            shuffle_category_item_data(category_id);
        }
    }

    table_handle_assign_consecutive_n_19_byte_data_blocks_items_selected_category_index();
    save_or_restore_random_seed(0);
}
