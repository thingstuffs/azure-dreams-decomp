#ifndef DUNGEON_OVL_D54C_H
#define DUNGEON_OVL_D54C_H
#include "common.h"
#include "sdk/memory.h"
#include "engine/resource.h"
#include "m2c_compat.h"
typedef struct ovl_d54c_7FFED588_Entry {
    s32 a;
    s32 b;
} ovl_d54c_7FFED588_Entry;
typedef struct {
    u8 b0;
    u8 b1;
    u16 h2;
    s32 w4;
} ovl_d54c_7FFED630_Record;
typedef struct {
    s8 field_0;
    s8 field_1;
    s16 field_2;
    s32 field_4;
} ovl_d54c_7FFED6EC_DungeonEntry;
typedef struct {
    u8 pad_0[0x2C];
    s32 field_2C;
} ovl_d54c_7FFED6EC_DungeonState;
typedef struct ovl_d54c_7FFED7CC_S_8008AF2C_0 {
    u8 pad_00[0x4];
    s32 unk_04;
} ovl_d54c_7FFED7CC_S_8008AF2C_0;
typedef struct ovl_d54c_7FFED850_S_8008AFB0_0 {
    u8 pad_00[0x1];
    s8 unk_01;
    s16 unk_02;
    s32 unk_04;
} ovl_d54c_7FFED850_S_8008AFB0_0;
typedef struct {
    u8 pad0[8];
    u32 flags0;
    u32 flags1;
} ovl_d54c_7FFED9F8_Item;
typedef struct {
    u8 pad0[0x48];
    s32 value48;
    u8 pad4C[0x14];
    s32 value60;
    u8 pad64[0x34];
    ovl_d54c_7FFED9F8_Item *item98;
} ovl_d54c_7FFED9F8_Object;
typedef struct {
    s32 value0;
    s32 value4;
    s32 value8;
    s32 valueC;
    s32 value10;
    s32 value14;
} ovl_d54c_7FFED9F8_TownState;
typedef struct ovl_d54c_7FFEDADC_S_8008B23C_0 {
    u32 unk_00;
    s32 unk_04;
} ovl_d54c_7FFEDADC_S_8008B23C_0;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
extern ovl_d54c_7FFED6EC_DungeonEntry resource_cache_records[];
typedef struct {
    s32 value0, value4, value8, valueC, value10, value14;
    u8 pad18[0x14];
    u8 *field_2C;
} DungeonCacheState;
extern DungeonCacheState town_resource_context;
extern u32 *D_801131EC;
extern void start_cd_read(u32 *, s32);
extern void func_80053CFC(u32 *, s32);
extern s32 func_8008AC84(s32);
extern s32 town_resource_buffer[3];
extern void call_script(void *); /* Unprototyped: uses the value as a pointer where the definition has an integer (or the reverse) */
extern void func_80035208(void *);
void copy_words_backward_from_offset(s32 dest_addr, s32 src_addr, s32 byte_count);
s32 sum_resource_bytes(s32 entry_count);
s32 find_resource_index_by_key(s32 first_byte, s32 second_byte, s32 halfword_value);
void shift_resource_entries_and_data(s32 record_count, s32 data_offset);
void move_resource_to_front(s32 entry_index);
u32 *find_packed_resource_descriptor(s32 key_flag, s32 key_high, s32 key_low);
s32 install_resource_descriptor_at_front(s32 resource_kind, s32 resource_group, s32 resource_id, s32 entry_index);
void ensure_resource_at_front(s32 resource_flag, s32 resource_group, s32 resource_id);
void submit_object_resource_data(ovl_d54c_7FFED9F8_Object *object);
void ensure_packed_resource_list(u8 *entries_in);
#endif
