#ifndef DUNGEON_OVL_1831CD8_H
#define DUNGEON_OVL_1831CD8_H
#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80026CF0_arg0.h"
#include "records/Rec_func_80027328_arg0.h"
#include "shared/game_work.h"
#include "records/Rec_func_80027AD0_arg0.h"
#include "shared/object_node.h"
#include "shared/object_flags.h"
typedef struct ovl_1831cd8_81811CD8_S_80026CD8_0 {
    u8 pad_00[0xC];
    s32 * unk_0C;
    s32 * unk_10;
} ovl_1831cd8_81811CD8_S_80026CD8_0;
typedef struct ovl_1831cd8_81811D0C_S_80026D0C_0 {
    u8 pad_00[0xC];
    void * unk_0C;
    void * unk_10;
} ovl_1831cd8_81811D0C_S_80026D0C_0;
typedef struct ovl_1831cd8_81811D0C_S_80026D0C_1 {
    void * unk_00;
    void * unk_04;
    s16 unk_08;
} ovl_1831cd8_81811D0C_S_80026D0C_1;
typedef struct ovl_1831cd8_81811D0C_S_80026D0C_2 {
    void * unk_00;
    void * unk_04;
} ovl_1831cd8_81811D0C_S_80026D0C_2;
typedef struct ovl_1831cd8_81811D0C_S_80026D0C_3 {
    u8 pad_00[0x4];
    void * unk_04;
} ovl_1831cd8_81811D0C_S_80026D0C_3;
typedef struct ovl_1831cd8_81811D0C_S_80026D0C_4 {
    u8 pad_00[0xA];
    u8 unk_0A;
} ovl_1831cd8_81811D0C_S_80026D0C_4;
typedef struct ovl_1831cd8_81811D0C_S_80026D0C_5 {
    u8 pad_00[0xA];
    s16 unk_0A;
} ovl_1831cd8_81811D0C_S_80026D0C_5;
typedef struct ovl_1831cd8_81811D0C_S_80026D0C_6 {
    u8 pad_00[0xB];
    u8 unk_0B;
} ovl_1831cd8_81811D0C_S_80026D0C_6;
typedef struct ovl_1831cd8_81811D0C_S_80026D0C_7 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
} ovl_1831cd8_81811D0C_S_80026D0C_7;
typedef struct ovl_1831cd8_81811F04_S_func_80026F04_0 {
    u8 pad_00[0x57D2];
    u8 unk_57D2;
} ovl_1831cd8_81811F04_S_func_80026F04_0;
typedef struct {
    u8 bytes[0x13];
} ovl_1831cd8_81812008_Entry19;
typedef struct ovl_1831cd8_818123E4_S_800273E4_0 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} ovl_1831cd8_818123E4_S_800273E4_0;
typedef struct ovl_1831cd8_818124A8_S_800274A8_0 {
    void (*unk_00)(s32 *);
    u8 pad_04[0xC];
    s32 unk_10;
    s32 unk_14;
    u8 pad_18[0x3C];
    s32 unk_54;
} ovl_1831cd8_818124A8_S_800274A8_0;
typedef struct ovl_1831cd8_818124F0_S_8003E2D8 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
} ovl_1831cd8_818124F0_S_8003E2D8;
typedef struct ovl_1831cd8_818124F0_S_800274F0_Nested {
    u8 pad[0x28];
    s32 unk28;
} ovl_1831cd8_818124F0_S_800274F0_Nested;
typedef struct ovl_1831cd8_818124F0_S_800274F0_Arg {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    u8 pad18[0x10];
    void *unk28;
    u8 pad2C[0x0C];
    u8 unk38;
    u8 pad39[3];
    s32 unk3C;
    u8 *unk40;
    void *unk44;
    ovl_1831cd8_818124F0_S_800274F0_Nested *unk48;
    u8 pad4C[0x3C];
    void *unk88;
} ovl_1831cd8_818124F0_S_800274F0_Arg;
typedef struct ovl_1831cd8_818127A8_S_800277A8_1_pre {
    void (*unk_00)(s32 *);
    u8 pad_04[0xC];
} ovl_1831cd8_818127A8_S_800277A8_1_pre;
typedef struct ovl_1831cd8_818127A8_S_800277A8_1 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    u8 pad_10[0x4];
    s32 unk_14;
    u8 pad_18[0x10];
    s32 unk_28;
    u8 pad_2C[0x10];
    s32 unk_3C;
    s32 unk_40;
    s32 unk_44;
    u8 pad_48[0x40];
    s32 unk_88;
} ovl_1831cd8_818127A8_S_800277A8_1;
typedef struct ovl_1831cd8_81812A88_S_80027A88_0 {
    void (*unk_00)(s32 *);
    u8 pad_04[0xC];
    s32 unk_10;
} ovl_1831cd8_81812A88_S_80027A88_0;
typedef struct {
    s16 x;
    s16 y;
    s16 w;
    s16 h;
} ovl_1831cd8_81812AD0_RECT;
typedef struct ovl_1831cd8_81812B44_S_80027B44_0 {
    u8 pad_00[0x4];
    void * unk_04;
} ovl_1831cd8_81812B44_S_80027B44_0;
typedef struct ovl_1831cd8_81812B44_S_80027B44_1 {
    u8 pad_00[0x4];
    void * unk_04;
} ovl_1831cd8_81812B44_S_80027B44_1;
typedef struct ovl_1831cd8_81812B44_S_80027B44_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} ovl_1831cd8_81812B44_S_80027B44_2;
typedef struct {
    s32 unk0;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
} ovl_1831cd8_81812BBC_Inner;
typedef struct {
    s32 *unk0;
    ovl_1831cd8_81812BBC_Inner *unk4;
} ovl_1831cd8_81812BBC_Entry;
typedef struct {
    s32 unk0;
    u8 pad4[0x1C];
} ovl_1831cd8_81812BBC_Work;
typedef struct ovl_1831cd8_81812C94_S_80027C94_0 {
    s32 unk_00;
    s32 unk_04;
    u8 pad_08[0x38];
    s32 unk_40;
    u8 pad_44[0x44];
    s32 unk_88;
} ovl_1831cd8_81812C94_S_80027C94_0;
typedef struct {
    s32 current, maximum;
    u8 pad08[0x24];
    u8 cursor[0x14];
    void *resource_names;
    u8 pad44[0x44];
    void *entries;
} ovl_1831cd8_81812D08_ProgressState;
typedef struct ovl_1831cd8_81812F34_S_80027F34_1 {
    u8 pad_00[0x80];
    void * unk_80;
} ovl_1831cd8_81812F34_S_80027F34_1;
typedef struct ovl_1831cd8_81812F34_S_80027F34_2 {
    u8 pad_00[0x2];
    s16 unk_02;
} ovl_1831cd8_81812F34_S_80027F34_2;
typedef struct ovl_1831cd8_81812F34_S_80027F34_0 {
    void (*unk_00)(s32 *);
    u8 pad_04[0xC];
    s32 unk_10;
    s32 unk_14;
} ovl_1831cd8_81812F34_S_80027F34_0;
typedef struct S_800491F4 S_800491F4;
typedef struct ListNode ListNode;
typedef struct UnalignedBlock12 UnalignedBlock12;



typedef struct ovl_1831cd8_81812FF4_S_80027FF4_0 {
    u8 pad_00[0x2];
    s8 unk_02;
    u8 pad_03[0x7];
    s8 unk_0A;
    u8 pad_0B[0x3];
    s8 unk_0E;
    u8 pad_0F[0x7];
    s8 unk_16;
} ovl_1831cd8_81812FF4_S_80027FF4_0;
typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
} ovl_1831cd8_81813050_Template0;
typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} ovl_1831cd8_81813050_Template1;
typedef struct {
    s32 unk0;
    s32 unk4;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    u8 unkE;
    u8 unkF;
} ovl_1831cd8_81813050_Record0;
typedef struct {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s32 unk8;
} ovl_1831cd8_81813050_Record1;
typedef struct {
    s32 unk0;
    ovl_1831cd8_81813050_Record0 *unk4;
    ovl_1831cd8_81813050_Record1 *unk8;
} ovl_1831cd8_81813050_Header;
typedef struct ovl_1831cd8_818130FC_S_800280FC_4 {
    u8 pad_00[0x10];
    void * unk_10;
    u8 pad_14[0x24];
    void * unk_38;
} ovl_1831cd8_818130FC_S_800280FC_4;
typedef struct ovl_1831cd8_818130FC_S_800280FC_5 {
    u8 pad_00[0x4];
    void * unk_04;
} ovl_1831cd8_818130FC_S_800280FC_5;
typedef struct ovl_1831cd8_818130FC_S_800280FC_6 {
    s32 unk_00;
    void * unk_04;
} ovl_1831cd8_818130FC_S_800280FC_6;
typedef struct ovl_1831cd8_818130FC_S_800280FC_7 {
    u8 pad_00[0x8];
    s16 unk_08;
} ovl_1831cd8_818130FC_S_800280FC_7;
typedef struct ovl_1831cd8_818130FC_S_800280FC_8 {
    s32 unk_00;
    void * unk_04;
} ovl_1831cd8_818130FC_S_800280FC_8;
typedef struct ovl_1831cd8_818130FC_S_800280FC_9 {
    u8 pad_00[0x8];
    s16 unk_08;
} ovl_1831cd8_818130FC_S_800280FC_9;
typedef struct ovl_1831cd8_818130FC_S_800280FC_10 {
    u8 pad_00[0x8];
    s16 unk_08;
} ovl_1831cd8_818130FC_S_800280FC_10;
typedef struct ovl_1831cd8_818130FC_S_800280FC_0 {
    M2C_UNK ** unk_00;
    M2C_UNK ** unk_04;
    s32 unk_08;
    s32 * unk_0C;
    u8 pad_10[0x4];
    s32 * unk_14;
} ovl_1831cd8_818130FC_S_800280FC_0;
typedef struct ovl_1831cd8_818130FC_S_800280FC_1 {
    u8 pad_00[0x4C];
    s32 unk_4C;
} ovl_1831cd8_818130FC_S_800280FC_1;
typedef struct ovl_1831cd8_818130FC_S_800280FC_2 {
    s32 unk_00;
    void * unk_04;
} ovl_1831cd8_818130FC_S_800280FC_2;
typedef struct ovl_1831cd8_818130FC_S_800280FC_3 {
    u8 pad_00[0xA];
    s16 unk_0A;
} ovl_1831cd8_818130FC_S_800280FC_3;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
typedef struct {
    u8 pad00[0x4C];
    s32 unk4C;
    u8 pad50[0x6C - 0x50];
    s32 unk6C[3];
    u8 pad78[0x88 - 0x78];
    s32 unk88;
    s32 unk8C[7];
} ovl_1831cd8_81813284_Unk818110CC;
typedef struct ovl_1831cd8_81813320_S_80028320_1 {
    u8 pad_00[0x80];
    void * unk_80;
} ovl_1831cd8_81813320_S_80028320_1;
typedef struct ovl_1831cd8_81813320_S_80028320_2 {
    u8 pad_00[0x2];
    s16 unk_02;
} ovl_1831cd8_81813320_S_80028320_2;
typedef struct ovl_1831cd8_81813320_S_80028320_0 {
    void (*unk_00)(s32 *);
    u8 pad_04[0x14];
    s32 unk_18;
    u8 pad_1C[0x8];
    s32 unk_24;
    u8 pad_28[0x10];
    s32 unk_38;
    u8 pad_3C[0xC];
    s32 unk_48;
    u8 pad_4C[0x10];
    s32 unk_5C;
    u8 pad_60[0x34];
    s32 unk_94;
    s32 unk_98;
} ovl_1831cd8_81813320_S_80028320_0;
typedef struct ovl_1831cd8_818133B4_S_800283B4_0_pre {
    s32 * unk_00;
    u8 pad_04[0xC];
} ovl_1831cd8_818133B4_S_800283B4_0_pre;
typedef struct ovl_1831cd8_818133B4_S_800283B4_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x8];
    s32 unk_14;
    s32 unk_18;
    u8 pad_1C[0xC];
    s32 unk_28;
    u8 pad_2C[0xC];
    s32 unk_38;
    u8 pad_3C[0xC];
    void * unk_48;
    s32 unk_4C;
    u8 pad_50[0x30];
    void * unk_80;
    s32 unk_84;
    s32 unk_88;
} ovl_1831cd8_818133B4_S_800283B4_0;
typedef struct ovl_1831cd8_818133B4_S_800283B4_1 {
    u8 pad_00[0x2];
    s16 unk_02;
} ovl_1831cd8_818133B4_S_800283B4_1;
typedef struct ovl_1831cd8_818133B4_S_800283B4_2 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} ovl_1831cd8_818133B4_S_800283B4_2;
typedef struct {
    u8 pad00[0x84];
    s32 field84;
    s32 field88;
} ovl_1831cd8_8181345C_Sub8181345C;
typedef struct {
    u8 pad00[0x0C];
    void *field0C;
    u8 pad10[0x0E];
    u16 flags;
    ovl_1831cd8_8181345C_Sub8181345C sub;
} ovl_1831cd8_8181345C_Obj8181345C;
typedef struct ovl_1831cd8_81813620_S_80028620_0 {
    u8 pad_00[0x20];
    s32 unk_20;
    u8 pad_24[0x64];
    s32 unk_88;
} ovl_1831cd8_81813620_S_80028620_0;
typedef struct { u8 pad[0x40]; s32 ready; } ovl_1831cd8_81813648_ReadyState;
typedef struct {
    s32 words[3];
} __attribute__((packed)) ovl_1831cd8_81813774_UnalignedBlock12;
typedef struct {
    ovl_1831cd8_81813774_UnalignedBlock12 chunks[2];
} ovl_1831cd8_81813774_UnalignedBlock24;
extern M2C_UNK D_800789B8;
M2C_UNK func_80025040();
s32 create_callback_pair_default();
void * func_8004B404(int value);
extern void strncpy();
extern u8 D_800287EC[];
char * func_80069E88();
u32 get_half_byte_length(s32 string_index);
void flag_object_for_removal();
void reset_object_to_default_data();
extern s16 SD_Call(s32 command, ...);
extern void *get_second_work_value(void *);
extern void forward_stored_object_value(void *);
extern void write_text_and_advance_selection(void *, void *);
extern s32 has_available_object(s32);
extern void (*menu_enabled_callbacks[2])(void *);
extern void (*menu_update_callbacks[2])(void *);
extern void (*menu_countdown_callbacks[2])(void *);
extern void (*menu_page_countdown_callbacks[2])(void *);
s32 advance_timed_tagged_stream();
extern s32 build_tinted_gradient_rect();
extern void * func_800499E8(u8 *cmd, u8 *rect, u8 *tint);
extern ovl_1831cd8_81812AD0_RECT D_80025034[2];
extern s8 shared_primitive_color[];
extern void strncat(void *, void *, s32);
extern s32 func_8004DC14(void *, s32);
extern void flag_optional_object_for_removal(void *);
extern s32 D_8002503C;
S_800491F4 *build_reverse_indexed_chain(S_800491F4 **, u8 *, s32);
extern u8 menu_context_chain_indices[16];
extern u8 menu_entry_chain_indices[4];
extern ovl_1831cd8_81813050_Template0 display_block_defaults;
extern ovl_1831cd8_81813050_Template1 display_vector_defaults;
extern void initialize_scaled_entry_cursor();
extern M2C_UNK D_80078AB4;
extern M2C_UNK D_80078AD8;
struct S8004CBFC_a1; extern struct S8004CBFC_a1 D_80079324;
extern s32 func_80049004(s32 *buffer_slot, s32 entry_count, s32 clear_words);
extern s32 allocate_and_append_callback_payload(s32 *values, s32 lookup_key);
extern void texture_set_the_field_offset_hex_8_in_each_entry_pointer_array(s32 entries, s32 *value, s32 count);
extern void register_node(void *, void *);
extern void func_8004491C(void *, void *);
extern void release_null_terminated_entries(void *);
extern void func_8004B248(void *);
extern int draw_tinted_node_sprites_scratch(void *object, int unused, void *data);
extern int func_8004CAA0(void *object, int unused, void *data);
extern u32 D_80029548;
extern u32 D_8002954C;
extern ovl_1831cd8_81813774_UnalignedBlock24 menu_record_template;
void clear_menu_state_values(ovl_1831cd8_81811CD8_S_80026CD8_0 *state);
void set_entry_destination_and_value(Rec_func_80026CF0_arg0 *record, s32 value);
void position_menu_grid_entries(ovl_1831cd8_81811D0C_S_80026D0C_0 *display, s32 cell_index);
s32 configure_menu_resource(s32 setup_value, s32 setup_data);
s32 count_menu_entry_matches(s32 target_value);
s32 count_menu_entry_pair_matches(s32 target_value, s32 prefix_value);
s32 find_menu_entry_occurrence(s32 target_value, s32 target_occurrence);
s32 find_menu_entry_from_index(s32 target_value, s32 start_index);
s32 find_menu_entry_pair_occurrence(s32 target_value, s32 prefix_value, s32 target_occurrence);
s32 find_menu_entry_by_pair_from_index(s32 match_byte_2, s32 match_byte_1, s32 start_index);
s32 pack_selected_menu_entries(s32 held_entry_set, s32 position, s32 entry_count);
void *get_mapped_menu_table_entry(s32 row_id, s32 entry_index);
s32 build_menu_text_page(s32 context, s32 scroll_y, s32 entry_count, s32 list_type);
void *refresh_menu_record_resource(Rec_func_80027328_arg0 *record, s32 resource_arg);
void *rebuild_menu_resource(Rec_func_80027328_arg0 *record, s32 resource_arg);
void *refresh_menu_derived_value(ovl_1831cd8_818123E4_S_800273E4_0 *state, s32 replacementInput, s32 calculationInput);
void dispatch_menu_state_update(s32 *state, s32 mode, s32 value, s32 extra_value);
void reset_menu_object_state_2(void *record);
void handle_menu_grid_input(ovl_1831cd8_818124F0_S_800274F0_Arg *menu);
void handle_menu_button_input(void *menu);
void invoke_enabled_menu_callback(s32 *record);
void update_enabled_menu_callback(s32 *record);
void handle_menu_record_check(void *record);
void draw_menu_progress_bar(void *context, s32 currentValue, s32 maxValue);
void store_scaled_menu_ratio(ovl_1831cd8_81812B44_S_80027B44_0 *object, s32 numerator, s32 denominator);
void position_scaled_entries(s32 object_table, s32 scale_numerator, s32 scale_denominator);
void refresh_menu_entry_resources(void *entry_table, void *resource_names);
void update_menu_object_data(void *object);
void update_menu_progress_bar(ovl_1831cd8_81812D08_ProgressState *state);
void dispatch_menu_update_callback(s32 *state);
void tick_menu_countdown(s32 *countdownState);
void run_menu_countdown_callback(s32 *state);
void advance_menu_value_fade(void *state);
S_800491F4 *link_menu_record_nodes(S_800491F4 **nodes);
S_800491F4 *build_menu_entry_chain(S_800491F4 **nodes);
void *initialize_menu_mode_one_fields(ovl_1831cd8_81812FF4_S_80027FF4_0 *object, s32 mode);
void initialize_menu_header_records(void *unused, ovl_1831cd8_81813050_Header *header, ovl_1831cd8_81813050_Template0 *record_a, ovl_1831cd8_81813050_Record1 *record_b);
void initialize_menu_panel_rows(void *panel, void *widgets);
void initialize_menu_record_range(void *record, s32 range_start, s32 value);
void initialize_menu_object_from_data(void *object, s32 init_value, s32 init_value_2);
s32 allocate_menu_object_buffers(ovl_1831cd8_81813284_Unk818110CC *object, s32 buffer_param);
void install_menu_object_handler(s32 object_addr);
void *create_menu_child_object(s32 parent_obj, s32 descriptor_value);
void clear_menu_value_objects(void *state);
void clear_menu_embedded_state(s32 object_addr);
void mark_menu_object_ready(ovl_1831cd8_81813648_ReadyState *state);
void *build_menu_draw_packets(void *packet, void *coords);
ovl_1831cd8_81813774_UnalignedBlock12 *copy_menu_record_template(ovl_1831cd8_81813774_UnalignedBlock12 *dest);
#endif
