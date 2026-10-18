#include "shared/runtime_dispatch.h"
#include "common.h"

typedef struct MainMemoryPage {
    u8 pad_0000[0x20A];
    u16 status_020A;
    u8 pad_020C[0x2D5C - 0x20C];
    s32 word_2D5C;
    u8 pad_2D60[0x2D6C - 0x2D60];
    u8 red_collar_status;
    u8 pad_2D6D[0x3714 - 0x2D6D];
    u16 flags_3714;
} MainMemoryPage;

extern void clear_town_movie_object_field(void *object);
extern void initialize_circular_list_head(void);
extern void initialize_pointer_table_self_links(void);
extern void clear_entry_table(void);
extern void obj_disp23_cancel_sw_set(s32 value);
extern void func_8003B42C(s32 value);
extern void func_8003B988(void);
extern void func_8003B92C(void);
extern s32 test_resident_bitmap_bit(s32 bit_id);
extern void func_8003BA60(void);
extern void func_8003BA9C(void);
extern void func_8003B9B8(void);
extern void chg_map_second_house_sel(void);
extern void func_8003BA24(void);
extern void reserve_twch_load(s32 load_selector);
extern void reserve_tw_mon_load(s32 load_selector);
extern void file_load_com(void *file_data);
extern void func_800434E4(void);
extern void copy_record_tail_bytes(void);
extern void change_map(void *map_data);
extern void process_state_entries_and_referenced_objects(void);
extern void load_resource_data(void);
extern void process_enabled_entries(void);
extern void town_sd_se_load_init(void);

extern u8 D_800717D0[0x18];
extern u8 D_800717E8[0x18];
extern s32 D_8006ADBC[3];
extern u8 D_8006AEC4[12];
extern u32 D_80080EA0;


/* Handles change_map / chg_map_second_house_sel setup and clears the handled runtime flags. */
void dispatch_town_transition(void)
{
    u16 runtime_flags;
    MainMemoryPage *page;

    clear_town_movie_object_field(D_800717D0);
    clear_town_movie_object_field(D_800717E8);
    initialize_circular_list_head();
    initialize_pointer_table_self_links();
    clear_entry_table();
    D_8006ADBC[0] = 0;
    obj_disp23_cancel_sw_set(0);

    runtime_flags = D_80082E60.flags16;
    if (runtime_flags & 0x4000) {
        func_8003B42C(0);
        func_8003B988();
        chg_map_second_house_sel();
        reserve_twch_load(1);
        reserve_tw_mon_load(1);
        file_load_com(&D_80080EA0);
    } else if (runtime_flags & 0x8000) {
        func_8003B42C(1);
        func_8003B92C();
        if ((test_resident_bitmap_bit(0x1391) == 0) ||
            (test_resident_bitmap_bit(0xA2) != 0)) {
            func_8003BA60();
        } else if (test_resident_bitmap_bit(0xA3) == 0) {
            func_8003BA9C();
        } else {
            chg_map_second_house_sel();
        }
        reserve_twch_load(1);
        reserve_tw_mon_load(1);
        file_load_com(&D_80080EA0);
    } else if (runtime_flags & 4) {
        chg_map_second_house_sel();
        reserve_twch_load(1);
        reserve_tw_mon_load(1);
        file_load_com(&D_80080EA0);
    } else {
        page = (MainMemoryPage *)0x80010000;
        if (runtime_flags & 2) {
            page->flags_3714 &= 0xFFFD;
            if (page->status_020A != 0) {
                func_8003B42C(1);
                page->status_020A = 0;
                func_8003B9B8();
                chg_map_second_house_sel();
            } else {
                func_8003BA24();
            }
            reserve_twch_load(1);
            reserve_tw_mon_load(1);
            file_load_com(&D_80080EA0);
        } else {
            func_800434E4();
            page->red_collar_status = 1;
            copy_record_tail_bytes();
            page->word_2D5C = 0;
            change_map(D_8006AEC4);
            reserve_twch_load(0);
            reserve_tw_mon_load(0);
        }
    }

    D_80082E60.flags16 &= 0x3FF9;
    process_state_entries_and_referenced_objects();
    load_resource_data();
    process_enabled_entries();
    town_sd_se_load_init();
}
