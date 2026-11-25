#ifndef DUNGEON_MENU_CACHE_FUSION_H
#define DUNGEON_MENU_CACHE_FUSION_H

#include "common.h"
#include "shared/object_node.h"
#include "town/shop/storage_menu.h"

extern char *cached_fusion_need_two_message;
extern char *fusion_invalid_pair_message;
extern char *cached_fusion_confirm_message;

ObjectNodeHeader *create_cached_fusion_menu(ObjectNodeHeader *owner, s32 index);
void show_fusion_need_two(void);
void show_fusion_invalid_pair(void);
void show_fusion_confirmation(void);
void check_fusion_close_signal(void *body);
void schedule_fusion_close(ObjectNodeHeader *node);
void poll_fusion_cancel(void *body);

typedef struct CachedFusionResult {
    StorageDisplayBlock blocks[4];
    DisplayPositionWords vectors[4];
    ItemMenuPart parts[4];
    s32 phase;
    s32 tick;
} CachedFusionResult;

extern s32 card_selection_display_data[];

void shade_fusion_result(CachedFusionResult *result);
void update_fusion_result(CachedFusionResult *result);
s32 initialize_fusion_result_parts(CachedFusionResult *result, s32 count);
void position_fusion_result(CachedFusionResult *result);
void poll_fusion_confirmation(void *body);
void schedule_fusion_cleanup(ObjectNodeHeader *node);

ObjectNodeHeader *create_fusion_result(void);

#endif
