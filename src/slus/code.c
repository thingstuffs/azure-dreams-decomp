/* Resident helpers for rendering, resource loading, text, menu state and sound command dispatch. */
#include "script_symbols.h"
#include "slus/resource_transition_task.h"
#include "slus/menu_count_template.h"
#include "shared/object_node.h"
#include "shared/sound_state.h"
#include "common.h"
#include "shared/sound_volume.h"
#include "shared/sprite_frame_state.h"

extern int   card_server_initialized[3];
extern short audio_voice_drain_suppressed[5];
extern short audio_command_queue[5];
extern int   audio_slot_service_word[3];

/* Initialize memory card services and disable automatic pad interrupt clearing. */
void initialize_memory_card_services(void) {
    InitCARD();
    StartCARD();
    _bu_init();
    ChangeClearPAD(0);
}

/* Clear count words starting at dst. */
void zero_words(int *dst, int count) {
    while (count != 0) {
        *dst = 0;
        count--;
        dst++;
    }
}

/* Copy count words from src to dst. */
void copy_words_forward(int *dst, int *src, int count) {
    while (count != 0) {
        *dst = *src;
        src++;
        count--;
        dst++;
    }
}

struct Elem {
    unsigned char b0;
    unsigned char pad1;
    unsigned char pad2;
    unsigned char pad3;
    int f4;
};

struct Dst {
    struct Elem *f0;
    unsigned char f4;
    unsigned char f5;
    unsigned char pad6;
    unsigned char pad7;
    int f8;
    int fc;
    int f10;
    unsigned short f14;
};

/* Select an entry and reset the state's entry flags and value. */
void select_record_entry_and_value(struct Dst *state, struct Elem *entries, short index) {
    state->f0 = entries + index;
    state->f4 = index;
    state->f5 = entries->b0;
    state->f14 &= 0x9FFF;
    state->f8 = state->f0->f4;
}

/* Swap two words. */
void swap_int_values(int *left, int *right)
{
    int saved = *left;
    *left = *right;
    *right = saved;
}

/* Set the pointed-to flag. */
void set_byte_one(unsigned char *flag)
{
    *flag = 1;
}

/* Return the supplied value. */
int identity_int(int value)
{
    return value;
}

extern int cd_cue_parameters[4];

/* Return the global status block. */
int *read_sound_stream_cue_pointer(void) {
    return cd_cue_parameters;
}

/* Return the saved global value. */
int read_sound_payload_slot(void)
{
    return sound_payload_buffer;
}

/* Store the global value. */
void set_sound_payload_slot(int value)
{
    sound_payload_buffer = value;
}

/* Wait for 512 vertical synchronization intervals. */
void wait_512_vertical_syncs(void) {
    int frames_left;
    for (frames_left = 0x200; frames_left > 0; frames_left--) {
        VSync(0);
    }
}

/* Pack a tag and 23-bit ID into a record and store its accompanying value. */
void pack_tagged_resource_descriptor(int tag, int id, int *record, int value)
{
    id &= 0x7FFFFF;
    tag <<= 23;
    id |= tag;
    record[0] = id;
    record[1] = value;
}

extern void *free_node_list_head;

/* Push a node onto the free list and clear its second word. */
void push_node_onto_free_list(ObjectNodeHeader *node)
{
    void *old_head;
    old_head = free_node_list_head;
    free_node_list_head = node;
    node->pprev = 0;
    node->next = old_head;
}

extern ObjectNodeHeader *active_node_list_head;

/* Set flag bits 0xC00 on every node in the global list. */
void mark_resource_list_flags_ten_and_eleven(void)
{
    ObjectNodeHeader *node = active_node_list_head;

    if (node != 0) {
        do {
            node->flags |= 0xC00;
            node = node->next;
        } while (node != 0);
    }
}

/* Count entries in a NULL-terminated pointer array. */
int count_null_terminated_pointers(void **entries)
{
    int count;

    count = 0;
    if (entries[0] != 0) {
        do {
            entries++;
            count++;
        } while (*entries != 0);
    }
    return count;
}

extern int *runtime_callback_write_cursor;

/* Append a value to the global word list and restore its zero terminator. */
void append_terminated_runtime_word(int value)
{
    *runtime_callback_write_cursor = value;
    runtime_callback_write_cursor++;
    *runtime_callback_write_cursor = 0;
}

/* Return the stride index relative to base, or -1 when it reaches the limit. */
short get_bounded_stride_index(unsigned int value, unsigned int base, unsigned short stride, unsigned short limit)
{
    unsigned int index = (value - base) / stride;
    if (index >= limit) {
        return -1;
    }
    return (short)index;
}

struct S_800423C0_Obj;
struct S_800423C0_Src;
extern void apply_actor_template_and_direction(struct S_800423C0_Obj *obj, s16 unused, struct S_800423C0_Src *source);
extern void update_owner_class_bits(void *a0);

/* Configure an entity with a signed halfword value and update its status. */
void apply_actor_template_and_class(void *entity, int value, void *source)
{
    apply_actor_template_and_direction(entity, (short)value, source);
    update_owner_class_bits(entity);
}

/* Return zero for any argument list. */
s32 return_zero_variadic(s32 unused, ...)
{
    return 0;
}

extern void sound_set_cd_cue_parameters(int a0, int a1, int a2, int a3);
extern short SD_Call(int a0);

/* Forward four values and trigger status event 0x300. */
void set_cd_cue_and_submit_sound_command(int first, int second, int third, int fourth)
{
    sound_set_cd_cue_parameters(first, second, third, fourth);
    SD_Call(0x300);
}

extern int *read_sound_stream_cue_pointer(void);

/* Combine the status block's low 24-bit tick value with its base adjustment. */
int read_stream_cue_start_offset(void)
{
    int *status = read_sound_stream_cue_pointer();
    int ticks = status[2] & 0xFFFFFF;
    ticks = ticks - 0x20;
    return ticks + status[1];
}

extern void draw_lit_mesh(void *a0, int a1, void *a2, short a3);

typedef struct Node46398 {
    char pad0[6];
    short field6;
    int field8;
    void *fieldC;
} Node46398;

/* Process linked objects using each node's value, record pointer, and halfword parameter. */
int draw_linked_lit_meshes(void *object, int value, void *record)
{
    void *current = object;
    Node46398 *node;

    do {
        node = (Node46398 *)record;
        draw_lit_mesh(current, value, record, node->field6);
        record = *(void **)((char *)current - 8);
        current = (char *)record + 0x20;
        if (record == 0)
            break;
        node = (Node46398 *)record;
        value = node->field8;
        record = node->fieldC;
    } while (1);

    return 0;
}

struct ObjectPosition;
struct SpriteFrameState;
extern int draw_linked_sprites(void *, struct ObjectPosition *, struct SpriteFrameState *);

/* Return the query result as a signed halfword. */
short draw_linked_sprites_and_narrow_result(void *payload, struct ObjectPosition *coords, struct SpriteFrameState *record)
{
    return (short)draw_linked_sprites(payload, coords, record);
}

extern void advance_actor_step_sequence(void *actor);
extern void upload_entry_textures(void *entry_state);

/* Run both update steps on an entity. */
void advance_sprite_animation_and_textures(void *entity)
{
    advance_actor_step_sequence(entity);
    upload_entry_textures(entity);
}

extern void bzero(void *dst, int n);
extern unsigned char sprite_resource_slots[0x30];

/* Clear the global 0x30-byte buffer. */
void clear_sprite_work_table(void)
{
    bzero(sprite_resource_slots, 0x30);
}

typedef struct {
    u8 unk[0xD000];
} Struct_800FC000;

extern Struct_800FC000 D_800FC000[];

/* Return the indexed 0xD000-byte global block. */
void *get_sprite_resource_slot_buffer(s32 index)
{
    return &D_800FC000[index];
}

/* Add 0x8000 to the supplied value. */
int get_image_palette_address(int value)
{
    return value + 0x8000;
}

extern Struct_800FC000 D_800FC000[];

/* Compute a block index from a raw address using signed division by 0xD000. */
s32 get_resource_block_index_from_address(void *address)
{
    return ((s32)address - (s32)D_800FC000) / 0xD000;
}

extern void select_sprite_entry(SpriteFrameState *a0, short a1, short a2);

/* Set entity flag 0x400 and reselect its entry. */
void select_sprite_entry_with_flag(SpriteFrameState *entity, short index, short offset) {
    entity->flags |= 0x400;
    select_sprite_entry(entity, index, offset);
}

extern int load_resource_and_mirror_palette(short a0, int a1);

/* Load the indexed entry from table zero. */
void load_default_object_palette(short index)
{
    load_resource_and_mirror_palette(index, 0);
}

extern int load_resource_and_mirror_palette(short a0, int a1);

/* Load the indexed entry from table one and return the result. */
int load_equipment_palette_for_category_sixteen(short index)
{
    return load_resource_and_mirror_palette(index, 1);
}

extern int load_resource_and_mirror_palette(short a0, int a1);

/* Load the indexed entry from table two. */
void load_equipment_change_palette(short index)
{
    load_resource_and_mirror_palette(index, 2);
}

extern int resource_load_indexed_sprite_bundle(int a0);

/* Return the result of query zero. */
int load_dungeon_sprite_bundle(void)
{
    return resource_load_indexed_sprite_bundle(0);
}

extern int resource_load_indexed_sprite_bundle(int a0);

/* Return the result of query one. */
int load_town_sprite_bundle(void)
{
    return resource_load_indexed_sprite_bundle(1);
}

extern int resource_load_indexed_sprite_bundle(int);

/* Return the result of query two. */
int load_alternate_town_sprite_bundle(void)
{
    return resource_load_indexed_sprite_bundle(2);
}

/* Return the indexed global table value. */
int read_display_spacing_word(int index)
{
    return D_80071250[index];
}

/* Read the indexed byte from the volatile global table. */
unsigned char read_display_spacing_byte(int index) {
    volatile unsigned char *values = D_80071298;
    return values[index];
}

/* Count nonzero entries up to the supplied limit. */
s32 count_nonzero_word_prefix(s32 *entries, s32 limit)
{
    s32 count = 0;

    if (limit > 0) {
        do {
            if (*entries == 0) {
                break;
            }
            count++;
            entries++;
        } while (count < limit);
    }
    return count;
}

typedef struct Struct_C_next Struct_C_next;
struct Struct_C_next {
    unsigned char pad[0xC];
    Struct_C_next *next;
};

/* Append a node to the end of a linked list. */
void append_linked_chain(Struct_C_next *tail, Struct_C_next *node) {
    while (tail->next != 0) {
        tail = tail->next;
    }
    tail->next = node;
}

/* Test whether the type equals 0x14. */
int is_type_twenty(int type)
{
    return type == 0x14;
}

extern int is_type_twenty(int type);

typedef struct {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 unk3;
} Struct8004928C;

/* Test whether the record's low five type bits equal 0x14. */
int record_has_type_twenty(Struct8004928C *record)
{
    return is_type_twenty(record->unk3 & 0x1F);
}

extern int item_name_text_table[4]; /* >8B forces hi/lo addressing (matches target's lui/addiu) */

extern int get_item_name_text(void *a0, int *a1);

/* Process an object using the fixed global table. */
int get_item_name_with_shared_text_table(void *object) {
    return get_item_name_text(object, item_name_text_table);
}

struct S_80042A80_Item;
extern s32 get_item_category_flags(struct S_80042A80_Item *item);

/* Return flag bit 0x400 from the status query. */
int read_item_category_flag_ten(void *item) {
    return get_item_category_flags(item) & 0x400;
}

/* Map the first set low flag bit to priority 0, 1, or 2, defaulting to 3. */
int get_low_flag_priority(int flags) {
    int priority = 3;

    if (flags & 1) {
        priority = 0;
    } else if (flags & 2) {
        priority = 1;
    } else if (flags & 4) {
        priority = 2;
    }

    return priority;
}

extern int get_low_flag_priority(int a0);

typedef struct {
    unsigned char pad[0x13];
    unsigned char unk13;
    int unk14;
} Struct80049984;

/* Return the record's flag priority, or 3 when its enabling byte is clear. */
int get_enabled_record_flag_priority(Struct80049984 *record)
{
    int priority = 3;

    if (record->unk13 != 0) {
        priority = get_low_flag_priority(record->unk14);
    }

    return priority;
}

/* Set the pointed-to flag and return one. */
int set_flag_and_return_success(int *flag)
{
    *flag = 1;
    return 1;
}

extern void init_paired_packet_records(void *packets, void *record);

/* Calls init_paired_packet_records with packets, record. */
void initialize_packet_pair_from_record(void *packets, void *record)
{
    init_paired_packet_records(packets, record);
}

/* Advance an index by delta and correct a single wrap in either direction. */
int advance_index_with_single_wrap(int index, int delta, int limit) {
    index = index + delta;
    if (delta > 0) {
        if (index < limit) {
        } else {
            index = index - limit;
        }
    } else {
        index = (index >= 0) ? index : (limit + index);
    }
    return index;
}

/* Read the indexed word from the volatile global table. */
int get_menu_count_template(int count)
{
    volatile int *values = D_800712B4;
    return values[count];
}

extern int get_scaled_byte_value(void *a1);

/* Forward the second argument to the object query. */
int read_second_argument_scaled_byte(void *unused, void *object) {
    return get_scaled_byte_value(object);
}

extern s32 calc_item_value(u8 *item, s32 flag);

/* file_load_com: process the item with mode one. */
s32 get_item_sell_money(void *item)
{
    return calc_item_value(item, 1);
}

/* func_koya_mon_talk_pal_ld: process the item with mode zero. */
s32 get_item_buy_money(void *item)
{
    return calc_item_value(item, 0);
}

extern void bzero(void *ptr, int len);

/* Clear the 0x50-byte table at address 0x80013564. */
void clear_floor_resource_state_table(void) {
    bzero((void *)0x80013564, 0x50);
}

/* Compare two signed words by subtraction. */
int subtract_pointed_int_values(int *left, int *right)
{
    return *left - *right;
}

/* Count entries in a NULL-terminated pointer array. */
s32 count_pointer_list_entries(void **entries)
{
    void **list;
    s32 count;

    list = entries;
    count = 0;
    if (*list != 0) {
        do {
            list++;
            count++;
        } while (*list != 0);
    }
    return count;
}

extern unsigned char *current_sort_rank_table;

/* Compare strings by their first characters' translated ordering values. */
int compare_mapped_leading_bytes(unsigned char **left, unsigned char **right)
{
    unsigned char *left_text = *left;
    unsigned char *right_text = *right;

    return current_sort_rank_table[*left_text] - current_sort_rank_table[*right_text];
}

extern void selection_sort_elements(u8 *base, s32 count, s32 size, s32 (*compar)(u8 *, u8 *));

/* Sort the supplied elements using their comparator. */
void forward_selection_sort_request(u8 *base, s32 count, s32 size, s32 (*compar)(u8 *, u8 *))
{
    selection_sort_elements(base, count, size, compar);
}

extern void create_callback_pair_payload(int a0, int a1, void *a2);

/* Forward an object with fixed leading arguments zero and one. */
void create_single_callback_payload(void *object) {
    create_callback_pair_payload(0, 1, object);
}

/* Find the target node in the global linked list. */
ObjectNodeHeader *find_active_list_node(ObjectNodeHeader *target)
{
    ObjectNodeHeader *node = active_node_list_head;

    while (node != 0) {
        if (node == target) {
            break;
        }
        node = node->next;
    }

    return node;
}

typedef struct {
    /* 0x0 */ unsigned char unk0;
    /* 0x1 */ unsigned char pad[11];
} Unk8004B4DC; /* size 0xC */

/* Count 12-byte records through the first record with bit 0x80 set. */
int count_tagged_records(Unk8004B4DC *record) {
    int count = 0;

    do {
        count++;
    } while ((record++->unk0 & 0x80) == 0);

    return count;
}

extern int global_cd_command_six_payload;
/* Process the fixed global record with command six. */
void submit_global_cd_command_six(void)
{
    Control_CD(6, &global_cd_command_six_payload, 0);
}

extern void submit_global_cd_command_six(void);

/* jyotyu_set_reserve_nyul: process the fixed reserve record. */
void load_bin_nametwin(void)
{
    submit_global_cd_command_six();
}

extern int create_item_view_for_entry(int a0, int a1, int a2);

/* Forward an object and value with a zero event parameter. */
int create_item_view_without_event(int object, int value)
{
    return create_item_view_for_entry(object, value, 0);
}

extern unsigned char animation_tick_scale;

struct S8004CBFC_a1 {
    unsigned short f0;
    unsigned short pad2;
    int f4;
};

struct S8004CBFC_a0 {
    int f0;
    int *f4;
    struct S8004CBFC_a1 *f8;
};

/* Initialize entry state, compute its rate, and optionally copy its value to the cursor. */
void initialize_scaled_entry_cursor(struct S8004CBFC_a0 *state, struct S8004CBFC_a1 *entry, int *cursor) {
    state->f8 = entry;
    state->f0 = entry->f0 / animation_tick_scale;
    state->f4 = cursor;
    if (cursor != 0) {
        *cursor = entry->f4;
    }
}

/* Select the embedded record at offset 0x18 for type 0x30, or 0xC otherwise. */
void *advance_packed_record_by_type(void *object) {
    unsigned char type = *((unsigned char *)object + 1) & 0xF0;

    switch (type) {
    case 0x30:
        object = (char *)object + 0x18;
        break;
    case 0x20:
    default:
        object = (char *)object + 0xC;
        break;
    }
    return object;
}

/* Encode the value's nibbles and fixed dimensions into a four-byte record. */
void decode_glyph_id_to_byte_rectangle(u32 value, u8 *record) {
    record[0] = (value & 0xF) << 3;
    record[1] = (value & 0xF0) - 0x20;
    record[2] = 8;
    record[3] = 0x10;
}

/* Compute and store byte coordinates from dimensions and grid position. */
void set_descriptor_grid_byte_coordinates(signed char *record, int width, int height, int column, int row)
{
    int x_offset = (width * column) / 2 - 0x80;
    record[2] = width * 4 + x_offset;
    record[3] = height * (row + 0x10) - 0x80;
}

/* Store the global value. */
void set_message_mode(int value)
{
    message_handler_mode = value;
}

/* Clear both global values. */
void clear_message_command_words(void)
{
    message_command_write_index = 0;
    message_command_start_index = 0;
}

extern void clear_resident_bitmap_bit(int);

/* Invoke clear_resident_bitmap_bit with mode two. */
void clear_resident_bitmap_bit_two(void) {
    clear_resident_bitmap_bit(sn_win_sw0);
}

/* Encode the low five index bits into the record's halfword at offset six. */
void set_glyph_style_index(void *record, int index)
{
    short packed = (index & 0xF) + 0x7C80;
    packed = packed + ((index & 0x10) << 3);
    *(short *)((char *)record + 6) = packed;
}

/* Decode one decimal character and advance the text pointer. */
unsigned char *read_decimal_digit_value(unsigned char *text, int *digit) {
    *digit = *text - 0x30;
    return text + 1;
}

extern void format_reversed_unsigned_decimal(int value, unsigned short width, char *buf, int pad);

/* Format a value right-justified with space padding. */
void format_reversed_decimal_space_padded(int value, unsigned short width, char *buf)
{
    format_reversed_unsigned_decimal(value, width, buf, ' ');
}

/* Return without performing any work. */
void noop_release_notification(void) {
}

extern void flag_object_for_removal(void *a0);

/* Update the object when its pointer is non-NULL. */
void flag_optional_object_for_removal(void *object)
{
    if (object != 0) {
        flag_object_for_removal(object);
    }
}

extern void flag_object_for_removal(void *object);

/* Update the object when its pointer is non-NULL. */
void flag_optional_object_for_removal_b(void *object) {
    if (object != 0) {
        flag_object_for_removal(object);
    }
}

/* Return without performing any work. */
void noop_display_setup_hook(void) {
}

/* Clear the first word of the global state. */
void clear_vram_callback_state(void) {
    card_server_initialized[0] = 0;
}

extern void *scene_create_resource_transition(void *owner, int task_context);

/* Create an object task with mode zero. */
void create_resource_transition_for_descriptor_check(void *object)
{
    scene_create_resource_transition(object, 0);
}

extern void *scene_create_resource_transition(void *owner, int task_context);

/* Create an object task with mode one. */
void create_resource_transition_card(int object) {
    scene_create_resource_transition(object, 1);
}

extern void *scene_create_resource_transition(void *owner, int task_context);

/* Create an object task with mode two and return it. */
void *create_resource_transition_task(void *owner)
{
    return scene_create_resource_transition(owner, 2);
}

extern void init_object_header_a(void *a0);
extern void init_object_header_b(void *a0);
extern void init_object_header_c(void *a0);
extern void init_tpage_prims(void *a0);
extern void layout_menu_backdrop_display_entries(void *a0);

/* Initialize four embedded records and then the containing object. */
void build_menu_backdrop_display_buffers(void *object)
{
    init_object_header_a((char *)object + 0x8);
    init_object_header_b((char *)object + 0x80);
    init_object_header_c((char *)object + 0xF8);
    init_tpage_prims((char *)object + 0x170);
    layout_menu_backdrop_display_entries(object);
}

extern unsigned char menu_backdrop_link_indices[16];

extern void build_reverse_indexed_chain(void *a0, void *a1, int a2);

/* Link entries using the fixed index table and limit seven. */
void link_menu_backdrop_display_nodes(void *entries)
{
    build_reverse_indexed_chain(entries, menu_backdrop_link_indices, 7);
}

/* Store a word through the supplied pointer. */
void set_menu_backdrop_initial_value(int *dst, int value)
{
    *dst = value;
}

/* Return without performing any work. */
void noop_selection_menu_animation_idle(void) {
}

typedef struct {
    char pad0[0xC];
    short val;
} Level3;

typedef struct {
    char pad0[0x4];
    Level3 *l3;
} Level2;

typedef struct {
    char pad0[0xC];
    Level2 *l2;
} Level1;

typedef struct {
    Level1 *l1;
} Level0;

/* Compare the signed halfwords reached through two pointer chains. */
int compare_selection_menu_entry_order(Level0 *left, Level0 *right) {
    return left->l1->l2->l3->val - right->l1->l2->l3->val;
}

typedef struct {
    u8 pad[0x10];
    u8 unk10[0x14]; /* sub-object passed by address to func_80021448 */
    s32 unk24;
} Struct_8004FC68;

extern s32 func_80021448(void *embedded_record);

/* Store the query result for the object's embedded record. */
void initialize_menu_record_value(Struct_8004FC68 *object) {
    object->unk24 = func_80021448(&object->unk10);
}

/* Return the selected word from the embedded record's value array. */
int read_selected_menu_entry_word(char *object)
{
    int index;
    object = object + 0x20;
    index = *(int *)(object + 0x30);
    return *(int *)(object + index * 4 + 0x10);
}

extern int read_selected_menu_entry_word(char *a0);
extern void func_80021300(int a0);

/* Pass the object's selected value to func_80021300. */
void resolve_selected_menu_entry(char *object)
{
    func_80021300(read_selected_menu_entry_word(object));
}

extern void handle_object_input(void *a0);

/* Calls handle_object_input with object. */
void forward_object_input_handler(void *object)
{
    handle_object_input(object);
}

struct VtableObj {
    void (*func)();
};

/* Invoke the object's leading function pointer with the object itself. */
void invoke_leading_object_callback(struct VtableObj *object)
{
    object->func(object);
}

extern unsigned char selection_menu_link_indices[16];

extern void build_reverse_indexed_chain(void *a0, void *a1, int a2);

/* Link entries using the fixed index table and limit 0x11. */
void link_seventeen_indexed_entries(void *entries)
{
    build_reverse_indexed_chain(entries, selection_menu_link_indices, 0x11);
}

extern int saved_value_output_enabled;
extern int selection_menu_saved_value;
extern void create_gauge_with_selection_menu(int a0);

/* Pass the saved value when enabled, or zero otherwise. */
void submit_enabled_saved_display_value(void) {
    int value = 0;
    if (saved_value_output_enabled != 0) {
        value = selection_menu_saved_value;
    }
    create_gauge_with_selection_menu(value);
}

extern void run_deferred_callbacks(void *a0);
extern unsigned char town_movie_callback_list[16];

/* Calls run_deferred_callbacks with & town_movie_callback_list. */
void run_town_movie_callbacks(void)
{
    run_deferred_callbacks(&town_movie_callback_list);
}

extern void run_deferred_callbacks(void *a0);

extern char town_transition_callback_list[12];

/* Calls run_deferred_callbacks with town_transition_callback_list. */
void run_town_transition_callbacks(void)
{
    run_deferred_callbacks(town_transition_callback_list);
}

extern char direct_load_resource_descriptor;
extern void file_load_com(void *arg);

/* Calls file_load_com with & direct_load_resource_descriptor. */
void load_direct_resource_descriptor(void)
{
    file_load_com(&direct_load_resource_descriptor);
}

extern void update_staged_motion_effect(void);

typedef struct {
    unsigned char pad0[0x10];
    void (*func)(void);
    unsigned char pad1[0x2C - 0x14];
    short field2C;
} Struct_80051528;

/* Mark the object when its callback is update_staged_motion_effect. */
void mark_staged_motion_effect_complete(Struct_80051528 *object) {
    if (object->func == update_staged_motion_effect) {
        object->field2C = 1;
    }
}

extern void update_sine_motion_effect(void);

typedef struct {
    char pad_00[0x10];
    void (*update_func)(void);
    char pad_14[0x2C - 0x14];
    unsigned short flag_2C;
} Entity;

/* Mark the entity when its callback is update_sine_motion_effect. */
void mark_sine_motion_effect_complete(Entity *entity)
{
    if (entity->update_func == update_sine_motion_effect) {
        entity->flag_2C = 1;
    }
}

extern void update_fade_in_out_effect(void);

typedef struct {
    unsigned char pad_00[0x10];
    void (*update_func)(void);
    unsigned char pad_14[0x2C - 0x14];
    short field_2C;
} Obj;

/* Mark the object when its callback is update_fade_in_out_effect. */
void mark_fade_in_out_effect_complete(Obj *object) {
    if (object->update_func == update_fade_in_out_effect) {
        object->field_2C = 1;
    }
}

typedef struct {
    char pad0[0x10];
    void (*update_func)(void);
    char pad1[0x2C - 0x14];
    short flag_2C;
} Obj80051F38;

extern void update_color_fade_effect(void);

/* Mark the object when its callback is update_color_fade_effect. */
void mark_color_fade_effect_complete(Obj80051F38 *object)
{
    if (object->update_func == update_color_fade_effect) {
        object->flag_2C = 1;
    }
}

typedef void (*StateFunc)(void *);

typedef struct {
    u8 pad_00[0x10];
    StateFunc unk10;
    u8 pad_14[0x2A - 0x14];
    u16 unk2A;
} Entity1;

extern void play_timed_animation_sequence(void *a0);

/* Mark the entity when its callback is play_timed_animation_sequence. */
void mark_timed_animation_sequence_complete(Entity1 *entity) {
    if (entity->unk10 == play_timed_animation_sequence) {
        entity->unk2A = 1;
    }
}

extern int Control_CD(int a0, void *a1, int a2);
extern void drain_cd_command_queue(void);

/* Process a record with command six and finish the update. */
void submit_cd_command_six_and_drain(void *record)
{
    Control_CD(6, record, 0);
    drain_cd_command_queue();
}

extern int enqueue_audio_command(unsigned short a0);

/* Pass the low 16 flag bits to the event handler and return its signed halfword result. */
short SD_Call(int flags)
{
    return enqueue_audio_command((unsigned short)flags);
}

/* Stores the CD playback scale in g_volume_scale[2] and reapplies the scaled stream volume. */
void sound_set_cd_playback_volume_scale(short value)
{
    g_volume_scale[2] = value;
    apply_scaled_cd_stream_volume();
}

/* Stores the signed 16-bit value in g_volume_scale[0] for primary voice gain scaling. */
void sound_set_voice_gain_scale(short value)
{
    g_volume_scale[0] = value;
}

/* Return zero. */
int func_800542A4(void)
{
    return 0;
}

/* Return 0x5F for mode one and 0x7F otherwise. */
int select_audio_mode_attenuation(int mode)
{
    if (mode == 1) {
        return 0x5F;
    }
    return 0x7F;
}

/* Return without performing any work. */
void func_800555FC(void) {
}

/* Return without performing any work. */
void func_80055604(void) {
}

extern void audio_stop_matching_effect_voices(s32 packed_key, s32 packed_channel);

/* Stops the voices selected by the incoming packed key and channel. */
void stop_matching_effect_voices(s32 packed_key, s32 packed_channel)
{
    audio_stop_matching_effect_voices(packed_key, packed_channel);
}

/* Clear the global halfword. */
void clear_audio_command_queue(void) {
    audio_command_queue[0] = 0;
}

/* Initialize the state record's values and two counters. */
void initialize_audio_ramp_defaults(SoundTask *state) {
    state->unk_10 = 0x80;
    state->unk_0C = 3;
    state->unk_04 = 0;
    state->unk_16 = 0xA;
    state->unk_18 = 0xA;
}

/* Return without performing any work. */
void func_80055CEC(void) {
}

/* Return without performing any work. */
void func_80055E6C(void) {
}

/* Return without performing any work. */
void noop_voice_start_notification(void) {
}

/* Return without performing any work. */
void noop_channel_control_notification(void) {
}

/* Return without performing any work. */
void func_80056D3C(void) {
}

/* Return without performing any work. */
void noop_midi_a0(void) {
}

/* Return without performing any work. */
void noop_midi_d0(void) {
}

extern int audio_sequence_active[4];
extern void audio_tick_sequence_tracks(void);

/* Invoke audio_tick_sequence_tracks when the global flag is set. */
void tick_enabled_sequence_tracks(void) {
    if (audio_sequence_active[0]) {
        audio_tick_sequence_tracks();
    }
}

/* Return without performing any work. */
void func_800587F8(void) {
}

/* Pack the low bytes of four values into a word, most significant byte first. */
unsigned int pack_big_endian_word(int byte_3, int byte_2, int byte_1, int byte_0)
{
    unsigned int packed;

    packed = byte_3 & 0xFF;
    packed = packed << 8;
    packed = packed + (byte_2 & 0xFF);
    packed = packed << 8;
    packed = packed + (byte_1 & 0xFF);
    packed = packed << 8;
    packed = packed | (byte_0 & 0xFF);
    return packed;
}

/* Pack two low bytes into a halfword value. */
int pack_big_endian_halfword(int high, int low)
{
    return ((high & 0xFF) << 8) | (low & 0xFF);
}

/* Add delta to the pointed-to counter and return its new value. */
int add_to_sequence_counter(int *counter, int delta)
{
    *counter += delta;
    return *counter;
}

/* Return without performing any work (an empty hook: its one caller, w_8005947C, passes the masked status byte in $a0). */
void noop_sequence_status_hook(u8 status) {
}

extern void service_audio_timer(void);

/* Invokes service_audio_timer with no arguments. */
void service_audio_timer_callback(void)
{
    service_audio_timer();
}

/* Store the first word of the global state. */
void set_audio_timer_state(int value) {
    audio_slot_service_word[0] = value;
}

extern s32 audio_timer_update_enabled[4];

extern void sound_run_guarded_sequence_update(void);

/* Invoke sound_run_guarded_sequence_update when the global value is nonzero. */
void run_enabled_sound_sequence_update(void)
{
    if (audio_timer_update_enabled[0]) {
        sound_run_guarded_sequence_update();
    }
}

extern unsigned char audio_force_center_pan[16];

/* Clear the global byte flag. */
void clear_cd_audio_mix_mode(void) {
    audio_force_center_pan[0] = 0;
}

/* Return without performing any work. */
void noop_audio_init_hook(void) {
}

extern void audio_reset_all_voices(void);
extern void reset_sound_slots(void);
extern void SpuQuit(void);

/* Run the three initialization routines in order. */
void reset_voices_slots_and_stop_spu_service(void)
{
    audio_reset_all_voices();
    reset_sound_slots();
    SpuQuit();
}

/* Store the global halfword value. */
void set_sound_flag_update_suppression(short value) {
    audio_voice_drain_suppressed[0] = value;
}

extern void drain_ready_sound_voice_flags(void);

/* Invokes drain_ready_sound_voice_flags with no arguments. */
void flush_pending_sound_voice_flags(void)
{
    drain_ready_sound_voice_flags();
}

extern void SpuReserveReverbWorkArea(int a0);
extern void SpuSetReverb(int a0);

/* Run both setup routines with mode one. */
void enable_available_spu_reverb(void) {
    SpuReserveReverbWorkArea(1);
    SpuSetReverb(1);
}

extern int SpuSetReverbModeParam(void *arg);

struct Msg8005B3D8 {
    int type;   /* 0x00 */
    int f4;     /* 0x04 */
    short x;    /* 0x08 */
    short y;    /* 0x0A */
    int fc;     /* 0x0C */
    int f10;    /* 0x10 */
    int f14;    /* 0x14 */
};

/* Send a type-six message with coordinates scaled by 256. */
int submit_shifted_stereo_sound_parameters(short x, short y) {
    struct Msg8005B3D8 msg;
    int scaled_x = x;
    int scaled_y = y;

    msg.type = 6;
    scaled_x = scaled_x << 8;
    scaled_y = scaled_y << 8;
    msg.x = scaled_x;
    msg.y = scaled_y;
    return SpuSetReverbModeParam(&msg);
}

extern int sequence_tempo_step[4];

/* Return the first word of the global state. */
int read_sequence_tempo_step(void) {
    return sequence_tempo_step[0];
}

extern void audio_apply_channel_control(short a0, int a1, int a2);

/* Send command seven for the indexed entity with a seven-bit value. */
void set_audio_channel_volume_control(int unused, short index, int value)
{
    audio_apply_channel_control(index, 7, value & 0x7F);
}

extern void audio_apply_channel_control(short a0, int a1, int a2);

/* Send command ten for the indexed entity with a seven-bit value. */
void set_audio_channel_pan_control(int unused, short index, int value)
{
    audio_apply_channel_control(index, 10, value & 0x7F);
}

/* Return without performing any work. */
void func_8005C980(void) {
}

/* Return without performing any work. */
void func_8005C988(void) {
}

/* Return without performing any work. */
void func_8005C990(void) {
}

/* Return without performing any work. */
void func_8005C998(void) {
}

/* Return without performing any work. */
void func_8005C9A0(void) {
}

extern void sound_set_spu_master_volume(s16 left_volume, s16 right_volume);

/* Forward two signed halfword values to sound_set_spu_master_volume. */
void set_spu_master_volume_pair(s16 first, s16 second) {
    sound_set_spu_master_volume(first, second);
}

extern void audio_reset_and_release_sequence_banks(void);

/* Invokes audio_reset_and_release_sequence_banks with no arguments. */
void reset_and_release_audio_sequence_banks(void)
{
    audio_reset_and_release_sequence_banks();
}

extern void submit_tagged_driver_byte(u8 a0, u8 a1, u8 a2);

/* Forward the low bytes of three values to submit_tagged_driver_byte. */
void submit_audio_driver_byte_command(s32 first, s32 second, s32 third)
{
    submit_tagged_driver_byte(first, second, third);
}

extern void submit_scaled_driver_halfword_pair(unsigned char a0, short a1, short a2);

/* Forward a byte code and two signed halfword values to submit_scaled_driver_halfword_pair. */
void submit_audio_driver_scaled_pair(unsigned char code, short first, short second)
{
    submit_scaled_driver_halfword_pair(code, first, second);
}

extern void dispatch_combined_driver_flags(s16 flags);

/* Forward the value as a signed halfword to dispatch_combined_driver_flags. */
void dispatch_audio_driver_halfword_flags(s32 value)
{
    dispatch_combined_driver_flags((s16)value);
}

extern void _SpuInit(int channel);

/* Calls _SpuInit with 0. */
void reset_audio_sequence_state_default(void)
{
    _SpuInit(0);
}

extern int *D_8007996C[4];

/* Clear bits 0x0F000000 and set bit 0x20000000 in the global target word. */
void _spu_FsetDelayW(void)
{
    volatile int *flags = D_8007996C[0];

    *flags = (*flags & 0xF0FFFFFF) | 0x20000000;
}

extern int *D_8007996C[4];

/* Clear bits 0x0F000000 and set bits 0x22000000 in the global target word. */
void _spu_FsetDelayR(void)
{
    volatile int *flags = D_8007996C[0];

    *flags = (*flags & 0xF0FFFFFF) | 0x22000000;
}

extern void DMACallback(int a0, int a1);

/* Install the callback for DMA channel four. */
void set_dma_channel_4_callback(int callback)
{
    DMACallback(4, callback);
}

typedef struct {
    u8 pad[0x1AA];
    u16 field_1AA;
} TargetStruct;

typedef struct {
    TargetStruct *ptr;
    u32 pad2[2]; /* keep total size > 8 bytes so hi/lo addressing (not gp_rel) is used */
} D_80079958_t;

extern D_80079958_t spu_registers;

/* Test bit 0x80 in the global target's halfword at offset 0x1AA. */
s32 is_tone_parameter_flag_set(void) {
    if (spu_registers.ptr->field_1AA & 0x80)
        return 1;
    return 0;
}

extern s32 modify_spu_register_bit_pair(s32 a0, s32 a1, s32 a2, s32 a3);

/* Forward two values with fixed trailing arguments 0xCC and 0xCD. */
s32 update_spu_register_pair_cc_cd(s32 first, s32 second) {
    return modify_spu_register_bit_pair(first, second, 0xCC, 0xCD);
}

extern void read_spu_register_pair(int a0, int a1);

/* Invoke read_spu_register_pair with values 0xCC and 0xCD. */
void read_spu_register_pair_cc_cd(void)
{
    read_spu_register_pair(0xCC, 0xCD);
}

extern void apply_spu_voice_attributes(void *a0);
extern void SpuSetKey(int a0, int a1);

/* Update an object and pass its first word to the mode-one handler. */
void apply_voice_attributes_and_key_on(void *object)
{
    void *current = object;

    apply_spu_voice_attributes(object);
    SpuSetKey(1, *(int *)current);
}

