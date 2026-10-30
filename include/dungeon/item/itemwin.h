#ifndef DUNGEON_OVL_1830850_H
#define DUNGEON_OVL_1830850_H
#include "common.h"
#include "shared/game_work.h"
#include "m2c_compat.h"
#include "records/Rec_func_80025850_arg0.h"
#include "records/Rec_func_80025D28_arg0.h"
#include "shared/object_node.h"
#include "shared/object_flags.h"
typedef void (*DispatchFunc)(void *context, void *self);
typedef struct ovl_1830850_81810888_S_80025888_0 {
    u8 pad_00[0x4];
    void * unk_04;
    void * unk_08;
} ovl_1830850_81810888_S_80025888_0;
typedef struct ovl_1830850_81810888_S_80025888_1 {
    u8 pad_00[0x4];
    void * unk_04;
} ovl_1830850_81810888_S_80025888_1;
typedef struct ovl_1830850_81810888_S_80025888_2 {
    u8 pad_00[0x4];
    void * unk_04;
} ovl_1830850_81810888_S_80025888_2;
typedef struct ovl_1830850_81810888_S_80025888_3 {
    u8 pad_00[0xA];
    s16 unk_0A;
} ovl_1830850_81810888_S_80025888_3;
typedef struct ovl_1830850_81810888_S_80025888_4 {
    u8 pad_00[0xA];
    s16 unk_0A;
} ovl_1830850_81810888_S_80025888_4;
typedef struct {
    u8 pad0[0xC];
    s32 value;
    u8 pad10[4];
} ovl_1830850_818108B8_ItemRecord;
typedef struct {
    u8 pad0[0xC];
    ovl_1830850_818108B8_ItemRecord *records;
    u8 pad10[4];
} ovl_1830850_818108B8_ItemCategory;
typedef struct {
    u8 pad0[8];
    s32 value;
    u8 padC[0x10];
    s32 index;
} ovl_1830850_818108B8_Subobject;
typedef struct {
    u8 pad0[0xC];
    s32 category;
    u8 pad10[4];
    void *subobject_base;
    u8 pad18[0x60];
    u8 fallback_arg[0x10];
    s32 fallback_value;
} ovl_1830850_818108B8_Object;
typedef struct ovl_1830850_818108B8_S_800258B8_0 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u8 pad_10[0x4];
    s32 unk_14;
    u8 pad_18[0x70];
    s32 unk_88;
} ovl_1830850_818108B8_S_800258B8_0;
typedef struct ovl_1830850_818108B8_S_800258B8_1 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x10];
    s32 unk_1C;
} ovl_1830850_818108B8_S_800258B8_1;
typedef struct ovl_1830850_818109CC_S_800259CC_2 {
    u8 pad_00[0x28];
    s32 unk_28;
} ovl_1830850_818109CC_S_800259CC_2;
typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    u8 pad18[0x3C];
    s32 unk54;
} ovl_1830850_81810A0C_DungeonArg;
typedef struct ovl_1830850_81810BF4_Entity {
    s32 state;
    u8 pad_04[0x44];
    void *object;
} ovl_1830850_81810BF4_Entity;
typedef struct ovl_1830850_81810C4C_S_80025C4C_0 {
    u8 pad_00[0x4];
    s32 * unk_04;
} ovl_1830850_81810C4C_S_80025C4C_0;
typedef struct ovl_1830850_81810C58_S_80025C58_0 {
    u8 pad_00[0x4];
    u8 ** unk_04;
} ovl_1830850_81810C58_S_80025C58_0;
typedef struct {
    u8 f0;
    u8 f1;
    u8 f2;
    s8 f3;
    s32 f4;
    u8 pad[2];
    u8 f10;
    u8 f11;
} ovl_1830850_81810C6C_Entry;
typedef struct ovl_1830850_81810CD8_S_80025CD8_0 {
    u8 unk_00;
    s8 unk_01;
    s8 unk_02;
    s8 unk_03;
    s32 unk_04;
    u8 pad_08[0x2];
    s8 unk_0A;
    s8 unk_0B;
} ovl_1830850_81810CD8_S_80025CD8_0;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
typedef struct S_800491F4 S_800491F4;
typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
} ovl_1830850_81810D9C_S_8002E5D8;
typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} ovl_1830850_81810D9C_S_8002E5E8;
typedef struct {
    s32 unk0;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    u8 unkE;
    u8 unkF;
} ovl_1830850_81810D9C_PatchRecord;
typedef struct {
    s32 unk0;
    ovl_1830850_81810D9C_PatchRecord *unk4;
    ovl_1830850_81810D9C_S_8002E5E8 *unk8;
} ovl_1830850_81810D9C_Owner;
typedef struct {
    u32 unk0;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
} ovl_1830850_81810E3C_PatchRecord;
typedef struct {
    void *unk0;
    ovl_1830850_81810E3C_PatchRecord *unk4;
} ovl_1830850_81810E3C_Owner;
typedef struct {
    u8 pad0[0x74];
    u8 *unk74;
} ovl_1830850_81810E3C_Source;
typedef struct {
    u8 pad00[0x38];
    s32 unk38[3];
    u8 pad44[0x54 - 0x44];
    s32 unk54;
    s32 unk58[7];
    s32 unk74;
} ovl_1830850_818110CC_Unk818110CC;
typedef struct ovl_1830850_81811168_DungeonSub81811168 {
    u8 pad00[0x50];
    s32 value50;
    s32 value54;
} ovl_1830850_81811168_DungeonSub81811168;
typedef struct ovl_1830850_81811168_DungeonObj81811168 {
    u8 pad00[0xC];
    void *field0C;
    u8 pad10[0xE];
    u16 flags1E;
    ovl_1830850_81811168_DungeonSub81811168 sub20;
} ovl_1830850_81811168_DungeonObj81811168;
typedef struct ovl_1830850_81811250_S_80026250_0 {
    u8 pad_00[0x14];
    s32 * unk_14;
} ovl_1830850_81811250_S_80026250_0;
typedef struct ovl_1830850_818112EC_S_800262EC_0 {
    u8 pad_00[0x10];
    s32 unk_10;
    u8 pad_14[0x40];
    s32 unk_54;
} ovl_1830850_818112EC_S_800262EC_0;
typedef struct ovl_1830850_81811314_S_80026314_0 {
    u8 pad_00[0x10];
    s32 unk_10;
    u8 pad_14[0x40];
    s32 unk_54;
} ovl_1830850_81811314_S_80026314_0;
typedef struct ovl_1830850_81811340_S_80026340_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x48];
    s32 unk_54;
} ovl_1830850_81811340_S_80026340_0;
extern DispatchFunc inventory_menu_handlers[];
extern ovl_1830850_818108B8_ItemCategory item_category_groups[];
extern void free_item_data_slot(int first_value, int second_value);
extern void func_8004A7D8(int first_value, int second_value);
extern void strcpy();
extern s32 check_object_byte_pairs_content(s32);
extern u8 inventory_default_entry_data[];
extern void SD_Call(s32 value);
extern s32 set_object_data_pointer(s32 unk14);
extern s32 advance_index_with_single_wrap(s32 selection_step, s32 unk8, s32 value);
extern u8 D_800789B8[9];
extern s32 inventory_shared_entry_value;
S_800491F4 *build_reverse_indexed_chain(S_800491F4 **, u8 *, s32);
extern u8 item_window_chain_indices[13];
extern ovl_1830850_81810D9C_S_8002E5D8 display_block_defaults;
extern ovl_1830850_81810D9C_S_8002E5E8 display_vector_defaults;
extern u8 D_80078C10[9];
extern u8 D_8007795C[9];
extern u8 D_80029474[9];
extern void *func_8004DC14(void *, s32);
extern s32 func_80049004(s32 *buffer_slot, s32 entry_count, s32 clear_words);
extern s32 allocate_and_append_callback_payload(s32 *values, s32 lookup_key);
extern void texture_set_the_field_offset_hex_8_in_each_entry_pointer_array(s32 entries, s32 *value, s32 count);
extern void register_node(ovl_1830850_81811168_DungeonObj81811168 *, void *);
extern void func_8004491C(ovl_1830850_81811168_DungeonObj81811168 *, void *);
extern void release_null_terminated_entries(void *);
extern void func_8004B248(void *);
extern int func_8004CAA0(void *object, int unused, void *data);
void flag_optional_object_for_removal();
void inventory_dispatch_indexed_handler(void *context, s32 handler_index);
void inventory_set_paired_index_offset(ovl_1830850_81810888_S_80025888_0 *pair, s32 index);
s32 inventory_menu_returns_zero(void *menu);
void restore_item_text_before_edit(void *item_object);
void inventory_select_null_or_default_data(void *object);
s32 inventory_check_type_four_linked_object(Rec_func_80025850_arg0 *context);
void inventory_handle_menu_actions_and_repeat(ovl_1830850_81810A0C_DungeonArg *menu);
void update_inventory_menu(void *menu);
void inventory_apply_step_and_reset_after_five(ovl_1830850_81810BF4_Entity *entity);
void inventory_clear_entry_value(ovl_1830850_81810C4C_S_80025C4C_0 *entry);
void set_destination_byte_pointer(ovl_1830850_81810C58_S_80025C58_0 *dest);
void *inventory_initialize_five_shared_entries(void *entryBuffer);
void inventory_initialize_packet_and_set_flag(ovl_1830850_81810CD8_S_80025CD8_0 *packet);
void initialize_inventory_packet(Rec_func_80025D28_arg0 *packet);
S_800491F4 *inventory_create_context_entry_13(S_800491F4 **context);
void inventory_initialize_owner_patch_and_state(void *unused, ovl_1830850_81810D9C_Owner *owner, ovl_1830850_81810D9C_S_8002E5D8 *patch,
                   ovl_1830850_81810D9C_S_8002E5E8 *state);
void inventory_initialize_owner_pointers_and_offsets(ovl_1830850_81810E3C_Source *source, ovl_1830850_81810E3C_Owner **owners);
void initialize_text_editor_context(void *object, s32 range_start, s32 initial_value, s32 text_addr);
void inventory_initialize_object_from_embedded_data(void *object, s32 init_value, s32 init_value_2, s32 init_value_3);
s32 inventory_copy_state_vector_after_buffers(ovl_1830850_818110CC_Unk818110CC *state, s32 input);
void inventory_clear_referenced_handle(ovl_1830850_81811250_S_80026250_0 *context);
void inventory_set_embedded_state_one(s32 object_addr);
#endif
