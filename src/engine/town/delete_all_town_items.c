#include "common.h"

#include "common.h"
#include "engine/town.h"

void del_t_item_w_ptr(s32 item_ptr);
extern s32 town_item_list;

/* Process the global value repeatedly until it becomes zero. */
void delete_all_town_items(void) {
    if (town_item_list != 0) {
        do {
            del_t_item_w_ptr(*(s32 *)0x8001029C);
        } while (*(s32 *)0x8001029C != 0);
    }
}
