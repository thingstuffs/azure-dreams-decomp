#ifndef TOWN_SHOP_ITEM_UPDATE_ITEM_MENU_RECORD_G01150_H
#define TOWN_SHOP_ITEM_UPDATE_ITEM_MENU_RECORD_G01150_H
/* update item menu record g01150. Shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-weak - group G01150 - CL:town/func_800B2100, CL:town/func_800B2150, CL:town/func_800B2264. */

#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800AF254_arg1.h"
#include "shared/game_work.h"
#include "shared/item_menu.h"

/* extern */
struct S_800AF674_0;

typedef struct S_800AF8B0_2 {
    u8 pad_00[0x18];
    s32 unk_18;
    u8 pad_1C[0x4];
    s32 unk_20;
} S_800AF8B0_2;

typedef struct S_800AF96C_1 {
    void * unk_00;
} S_800AF96C_1;

/* arg0 in store_item_menu_check_result */
typedef struct S_800AF96C_2 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_800AF96C_2;

/* ((S_800AF96C_1 *)arg0)->unk_00 in store_item_menu_check_result */
typedef struct S_800AF96C_0 {
    s32 unk_00;
    u8 pad_04[0x10];
    s32 unk_14;
} S_800AF96C_0;

typedef struct TownState {
    u8 pad00[8];
    s32 input;
    u8 pad0C[4];
    s32 flags;
} TownState;

typedef struct TownInner {
    u8 pad00[4];
    s32 handle;
    u8 pad08[8];
    s32 band;
    u8 pad14[4];
    s32 position;
    s32 limit;
    s32 *table;
} TownInner;

typedef struct TownObject {
    TownInner *inner;
    s32 old_state;
    u8 pad08[4];
    s32 counter;
    s32 enabled;
    u8 pad14[4];
    s32 resource;
    u8 pad1C[0xA8 - 0x1C];
    ItemMenuPart **parts;
} TownObject;

typedef struct S_800AFD00_1 {
    u8 pad_00[0x98];
    s32 unk_98;
    s32 unk_9C;
} S_800AFD00_1;

/* ((Rec_func_800AF254_arg1 *)arg0)->unk_A8.as_pv in reset_item_menu_entity_state */
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

/* extern */
struct FrameState;

/* extern */
struct TownObject;

typedef struct S_800AFD5C_2 {
    u8 pad_00[0x6];
    s16 unk_06;
} S_800AFD5C_2;

/* ((Rec_func_800AF254_arg1 *)arg0)->unk_9C in advance_item_menu_step */
typedef struct S_800AFD5C_0 {
    s32 * unk_00;
    u8 pad_04[0x14];
    s32 unk_18;
} S_800AFD5C_0;

void populate_item_menu_page_entries(s32, void * *);
/* extern */
void populate_item_menu_lower_entries(Rec_func_800AF254_arg1 *);
void populate_current_item_menu_page(struct S_800AF674_0 *);
/* extern */
void update_item_menu_page_bounds();
/* extern */
void item_menu_no_op();
/* ((Rec_func_800AF254_arg1 *)arg0)->unk_00 in place_selected_item_menu_entry */
void * create_item_menu_display_controller(s32, s32, s32, s32, s32);
extern s32 D_800891F4;
extern u8 D_800AF96C[];
extern s32 advance_index_with_directional_clamp(s32, s32, s32);
extern void get_item_name_with_shared_text_table(s32);
extern void sort_entries_by_category(void *);
extern void SD_Call(s32);
extern void set_item_menu_data_pointer(s32);
extern void set_item_menu_entry_coordinates(TownObject *);
void fade_color_to_gray(Struct800497F4 *object, s32 stop_at_gray);
s32 advance_timed_tagged_stream(struct FrameState *);
extern s32 item_menu_record_callback[];

/* Functions defined in this translation unit. */
void update_item_menu_record(Rec_func_800AF254_arg1 *record);
s32 place_selected_item_menu_entry(Rec_func_800AF254_arg1 *entry);
void store_item_menu_check_result(void *record_data);
void update_item_menu_selection(TownObject *obj);
void reset_item_menu_entity_state(void *entity);
void advance_item_menu_step(void *object);

#endif
