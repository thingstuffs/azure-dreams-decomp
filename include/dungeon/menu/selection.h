#ifndef DUNGEON_OVL_1831370_H
#define DUNGEON_OVL_1831370_H
#include "common.h"
#include "m2c_compat.h"
#include "shared/game_work.h"
#include "shared/object_node.h"
#include "shared/object_flags.h"
typedef struct ovl_1831370_81811370_S_80026370_0 {
    u8 pad_00[0x4];
    void * unk_04;
} ovl_1831370_81811370_S_80026370_0;
typedef struct ovl_1831370_81811370_S_80026370_1 {
    u8 pad_00[0x4];
    void * unk_04;
} ovl_1831370_81811370_S_80026370_1;
typedef struct ovl_1831370_81811370_S_80026370_2 {
    u8 pad_00[0x8];
    s16 unk_08;
} ovl_1831370_81811370_S_80026370_2;
typedef struct ovl_1831370_818113C0_S_800263C0_0 {
    u8 pad_00[0xC];
    s32 * unk_0C;
} ovl_1831370_818113C0_S_800263C0_0;
typedef struct {
    s32 unk0;
    s32 unk4;
    s32 field8;
    s32 unkC;
    s32 field10;
} ovl_1831370_8181140C_PadState;
typedef struct {
    s32 unk0;
    s32 field4;
    s32 field8;
    s32 unkC;
    s32 field10;
    s32 pad14[23];
    s32 field70;
} ovl_1831370_8181140C_MenuState;
typedef struct ovl_1831370_81811508_S_80026508_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x4];
    s32 unk_10;
    u8 pad_14[0x5C];
    s32 unk_70;
} ovl_1831370_81811508_S_80026508_0;
typedef struct ovl_1831370_8181154C_S_8002654C_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x4];
    s32 unk_10;
    s32 unk_14;
    u8 pad_18[0x58];
    s32 unk_70;
} ovl_1831370_8181154C_S_8002654C_0;
typedef struct {
    s8 pad_00[0x10];
    s32 index;
    s32 field_14;
    u8 pad_18[0x58];
    s32 field_70;
} ovl_1831370_8181161C_Func8181161CData;
typedef struct {
    u8 unk0;
    s8 unk1;
    s8 unk2;
    s8 unk3;
    s32 unk4;
    s8 pad8[2];
    s8 unkA;
    s8 unkB;
} ovl_1831370_81811708_Packet;
typedef struct S_800491F4 S_800491F4;
typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
} ovl_1831370_818117D8_S_8002E5D8;
typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} ovl_1831370_818117D8_S_8002E5E8;
typedef struct {
    s32 unk0;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    u8 unkE;
    u8 unkF;
} ovl_1831370_818117D8_PatchRecord;
typedef struct {
    s32 unk0;
    ovl_1831370_818117D8_PatchRecord *unk4;
    ovl_1831370_818117D8_S_8002E5E8 *unk8;
} ovl_1831370_818117D8_Owner;
typedef struct {
    s32 unk0;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
} ovl_1831370_81811878_Inner;
typedef struct {
    s32 unk0;
    ovl_1831370_81811878_Inner *unk4;
} ovl_1831370_81811878_Result;
typedef struct {
    s32 index;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 word10;
    s32 word14;
    s32 unk18;
    s32 unk1C;
    s32 word20;
    s32 unk24;
    s32 unk28;
    s32 word2C;
} ovl_1831370_81811878_Source;
typedef struct {
    s32 *dst0;
    s32 **dst4;
    s32 **dst8;
    ovl_1831370_81811878_Result *dstC;
} ovl_1831370_81811878_Destinations;
typedef struct ovl_1831370_8181192C_S_8002692C_0 {
    void (*unk_00)(s32 *);
    u8 pad_04[0x18];
    s32 unk_1C;
    s32 unk_20;
    s32 unk_24;
    u8 pad_28[0x4];
    s32 unk_2C;
} ovl_1831370_8181192C_S_8002692C_0;
typedef struct ovl_1831370_818119A0_S_800269A0_0 {
    u8 pad_00[0x70];
    s32 unk_70;
} ovl_1831370_818119A0_S_800269A0_0;
typedef struct {
    s32 x;
    s32 y;
    s32 z;
} ovl_1831370_818119E8_Vec3;
typedef struct ovl_1831370_81811B44_S_80026B44_0 {
    u8 pad_00[0xC];
    s32 * unk_0C;
} ovl_1831370_81811B44_S_80026B44_0;
typedef struct {
    u8 pad[0x70];
    void *field_70;
    void *field_74;
} ovl_1831370_81811B94_CleanupData;
typedef struct {
    u8 pad_00[0x1E];
    u16 flags;
    ovl_1831370_81811B94_CleanupData cleanup;
} ovl_1831370_81811B94_CleanupObject;
typedef struct ovl_1831370_81811C20_S_80026C20_0 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u8 pad_10[0x4];
    void * unk_14;
} ovl_1831370_81811C20_S_80026C20_0;
typedef struct ovl_1831370_81811C20_S_80026C20_1 {
    u8 unk_00;
    union { u8 s; u8 u; } ovl_1831370_81811C20_unk_01;   
} ovl_1831370_81811C20_S_80026C20_1;
#define M2C_FIELD(expr, type_ptr, offset)  (*(type_ptr)((s8 *)(expr) + (offset)))
extern s32 advance_index_with_single_wrap(s32 target, s32 input_value, s32 count);
extern u8 text_editor_pair_limits[9];
s32 func_8004DC14();
extern s16 SD_Call(s32);
extern s32 memset();
extern void write_char_pair();
extern void func_8004EAC4();
extern void strcpy(s32, s32);
extern s32 text_editor_packet_payload;
S_800491F4 *build_reverse_indexed_chain(S_800491F4 **, u8 *, s32);
extern u8 menu_selection_chain_indices[5];
extern ovl_1831370_818117D8_S_8002E5D8 display_block_defaults;
extern ovl_1831370_818117D8_S_8002E5E8 display_vector_defaults;
extern s32 D_80029508[2];
extern s32 func_80048EE4(void *pool, s32 record_count);
extern void texture_set_the_field_offset_hex_8_in_each_entry_pointer_array(s32 entries, void *value, s32 count);
extern void register_node();
extern void func_8004491C();
extern void flag_object_for_removal();
extern int draw_tinted_node_sprites_scratch(void *object, int unused, void *data);
extern int func_8004CAA0(void *object, int unused, void *data);
void flag_optional_object_for_removal();
extern int D_800814A0;
extern u8 text_editor_empty_pair[12];
void set_indexed_object_field(ovl_1831370_81811370_S_80026370_0 *object, s32 index);
s32 adjust_selection_by_item_count(s32 input_value, s32 target, s32 lookup_index);
void inventory_set_object_entry_address(ovl_1831370_818113C0_S_800263C0_0 *object, M2C_UNK source);
void update_menu_selection_from_input(ovl_1831370_8181140C_MenuState *menu);
void update_embedded_state_from_table(s32 object_addr);
void clear_object_buffer_and_state(s32 objectAddress);
void write_text_and_advance_selection(s32 objectAddress, s32 updateValue);
void apply_step_and_reset_after_five(s32 *step);
void *initialize_variant_packet(ovl_1831370_81811708_Packet *packet, s32 variant);
void set_descriptor_fields_and_flag(void *descriptor);
S_800491F4 *forward_value_to_shared_helper(S_800491F4 **value);
void initialize_owner_defaults(void *unused, ovl_1831370_818117D8_Owner *owner, ovl_1831370_818117D8_S_8002E5D8 *patch_data,
                   ovl_1831370_818117D8_S_8002E5E8 *aux_data);
void initialize_object_destination_fields(ovl_1831370_81811878_Source *src, ovl_1831370_81811878_Destinations *dst);
void initialize_object_phase_data(void *recordFields, s32 recordValue2C, s32 typeCode, s32 recordValue24);
void initialize_embedded_object_state(void *state, s32 parent, s32 type, s32 config);
s32 get_and_position_object_handle(void *object);
void *allocate_initialized_child_object(s32 parent_object, s32 type_code, s32 config_value);
void release_object_handle(ovl_1831370_81811B44_S_80026B44_0 *owner);
void cleanup_object_resources(ovl_1831370_81811B94_CleanupObject *object);
u32 has_available_object(void *object);
s32 check_object_byte_pairs_content(s32 object_addr);
void forward_menu_object_to_selection_updater(ovl_1831370_8181140C_MenuState *menu);
#endif
