#include "shared/runtime_dispatch.h"
#include "common.h"
#include "shared/game_work.h"

/* g_game_work.view declared on its own: func_8004D0C8 / func_8004D110 form their base at 0x80083178 (as g_game_work the
 * offsets and the schedule change: cc1 listing differs). */
extern GameView D_80083178;

/* The remainder and its extracted owners use their registered TU recipes. */

struct S_80082E60 {
    char pad0[4];
    int field_4;
    char pad8[3];
    char field_B;
    char field_C;
    char field_D;
    char pad_E[0xA];
    char field_18;
};



/* Stores the value in D_80082E60 and clears its two flag bytes. */
void set_scene_phase_callback(int value) {
    struct S_80082E60 *state = ((struct S_80082E60 *)&D_80082E60);

    state->field_4 = value;
    state->field_D = 0;
    state->field_C = 0;
}

extern struct {
    int f0;
    int f1;
    int f2;
    int f3;
} D_8006CE34;

/* Stores four values in consecutive fields of D_8006CE34. */
void sound_set_cd_cue_parameters(int value_0, int value_1, int value_2, int value_3)
{
    struct { int f0; int f1; int f2; int f3; } *values = &D_8006CE34;
    values->f0 = value_0;
    values->f1 = value_1;
    values->f2 = value_2;
    values->f3 = value_3;
}

/* reset_scene_frame_callback_list */

extern int D_80083C68[8];
extern void *D_800814E0;

/* Points D_800814E0 at D_80083C68 and clears its first word. */
void reset_scene_frame_callback_list(void) {
    D_800814E0 = D_80083C68;
    D_80083C68[0] = 0;
}

/* func_8004D0C8 */

void copy_view_halfword_triplet(void);

/* Registers the state pointer and the default callback copy_view_halfword_triplet. */
void func_8004D0C8(void *state)
{
    D_80083178.slot[0].unk_24 = state;
    D_80083178.slot[0].callback = copy_view_halfword_triplet;
}

/* func_800419EC */
/* Struct at D_80083CA8 (also referenced elsewhere as D_80083CAE at offset 6):
 * offset 0: int  (rate/quotient, decremented each tick by other code)
 * offset 4: int  (accumulator, used by advance_timed_entity_motion)
 * offset 6: short (aka D_80083CAE - value copied from a1)
 * offset 8: short (countdown counter, copied from a0)
 * Declared >8 bytes so hi/lo addressing is used. */
extern struct {
    int field0;
    short pad4;
    short field6;
    short field8;
} D_80083CA8;

/* Sets the countdown, amount, and per-tick quotient in D_80083CA8. */
void func_800419EC(unsigned short countdown, unsigned int amount) {
    D_80083CA8.field8 = countdown;
    D_80083CA8.field6 = amount;
    D_80083CA8.field0 = amount / countdown;
}

/* func_8004D110 */

void copy_global_short_triplet(void);

/* Registers the state pointer and the default callback copy_global_short_triplet. */
void func_8004D110(void *state)
{
    D_80083178.slot[0].unk_04 = state;
    D_80083178.slot[0].callback = copy_global_short_triplet;
}

extern unsigned char D_8007382A[16];

/* Sets D_8007382A to 1 and returns 1. */
int audio_enable_mono_mix(void) {
    unsigned char *flag = &D_8007382A[0];
    int enabled = 1;
    *flag = enabled;
    return enabled;
}

extern int D_800869B4[3];

typedef struct {
    char pad_00[0x20];
    int field_20;
    int field_24;
    char pad_28[0x50 - 0x28];
} Struct80085FA8;

extern Struct80085FA8 D_80085FA8[];

/* Sets both value fields of every active entry in D_80085FA8. */
void audio_set_all_track_tempo_steps(int unused, int value) {
    unsigned int index;
    unsigned int count;

    index = 0;
    if (D_800869B4[0] != 0) {
        count = D_800869B4[0];
        do {
            D_80085FA8[index].field_24 = value;
            D_80085FA8[index].field_20 = value;
            index++;
        } while (index < count);
    }
}

/* --- wave-60 (gcc 2.8.1) --- */

typedef struct {
    u8 pad[0x18];
    s32 unk18;
    s32 unk1C;
} Struct_80050F74;

/* Stores the value at offsets 0x38 and 0x3C of the object. */
void func_80050F74(void *object, s32 value) {
    Struct_80050F74 *fields = (Struct_80050F74 *)((u8 *)object + 0x20);
    fields->unk1C = value;
    fields->unk18 = value;
}

/* extern data: force %hi/%lo addressing (not $gp-relative) by giving it size > 8 bytes */
extern short D_800847F6[8];

/* Sets D_800847F6 to -1 and returns -1. */
int func_800542AC(void) {
    short *flag = &D_800847F6[0];
    int disabled;
    disabled = -1;
    *flag = disabled;
    return disabled;
}

typedef struct {
    short a;
    short pad0;
    short b;
    short pad1;
    short c;
    short pad2;
    short d;
} D_80083D78_t;

extern D_80083D78_t D_80083D78;

/* Resets the four short fields of D_80083D78 to -1. */
void func_800499BC(void) {
    D_80083D78.a = -1;
    D_80083D78.b = -1;
    D_80083D78.c = -1;
    D_80083D78.d = -1;
}

/* D_8007359C: a pointer-sized global that (per the target's lui/lw access pattern) is
 * itself a pointer stored inside a larger (>8 byte) data object, forcing gcc to emit
 * a %hi/%lo access rather than a $gp-relative one. It points to an array of 0x14 (20)
 * byte structs; this function indexes that array and returns the word at offset 4. */

typedef struct {
    int unk0;
    int unk4;
    int unk8;
    int unkC;
    int unk10;
} Entry8007359C; /* size 0x14 */

/* declared as a small array (size > 8 bytes) purely to force hi/lo addressing for
 * element 0, matching the target's lui/lw access to the pointer value itself. */
extern Entry8007359C *D_8007359C[4];

/* Returns the word at offset 4 of the indexed D_8007359C entry. */
int monster_get_species_name_text(int index)
{
    Entry8007359C *entries = D_8007359C[0];
    return entries[index].unk4;
}

extern int D_80082EC0[128];

/* Clears all 128 words of D_80082EC0 in reverse order. */
void clear_runtime_slot_word_table(void) {
    s32 index;

    for (index = 0x7F; index >= 0; index--) {
        D_80082EC0[index] = 0;
    }
}

/* --- v6 (LEAD 1: maspsx un-fills jr-delay sp-restore at 2+ callee-saved) --- */
typedef struct { short unk0, unk2, flags4, id6; } D8Elem;
extern D8Elem D_80083D08[6];
extern int find_sprite_resource_slot_by_id(short);

struct Target_827C { char pad[0x28]; void *entry; };
struct Source_827C { char pad[0xC]; struct Target_827C *target; };

/* Assigns the resolved D_80083D08 entry to the source target and returns the source. */
struct Source_827C *bind_sprite_resource_slot_record(struct Source_827C *source, short entry_id) {
    source->target->entry = &D_80083D08[find_sprite_resource_slot_by_id(entry_id)];
    return source;
}

/* --- v6 (maspsx LEAD 2 %lo-fold) --- */

typedef struct { short a, b; } TableValuePair;
extern TableValuePair D_80013564[];
extern int find_item_data_slot(int first_value, int second_value);

/* Clears both shorts of the selected D_80013564 entry when its index is below 20. */
void item_clear_recorded_category_pair(int first_value, int second_value)
{
    int index = find_item_data_slot(first_value, second_value);
    if (index < 0x14) {
        /* Keep the fixed table page separate from the scaled entry offset. */
        u32 table_page = 0x80010000;
        s32 offset = index * 4;
        ((TableValuePair *)(table_page + offset + 0x3564))->a = 0;
        ((TableValuePair *)(table_page + offset + 0x3564))->b = 0;
    }
}

/* shared D_80084960 table (0x9C stride) */
typedef struct {
    int unk00;
    int unk04;
    char pad08[4];
    int unk0C;
    char pad10[0xC];
    int unk1C;
    char pad20[0x9C - 0x20];
} Entry80084960;
extern Entry80084960 D_80084960[];

extern void activate_scene_resource_and_clear_view_callbacks(void);

/* Copies field_B into field_18 of D_80082E60, then calls activate_scene_resource_and_clear_view_callbacks. */
void scene_save_previous_mode_and_reset_callbacks(void)
{
    D_80082E60.field_18 = ((signed char)D_80082E60.field_B);
    activate_scene_resource_and_clear_view_callbacks();
}

extern u8 D_80080B18[16];
extern u8 D_80080B1B;
extern u8 D_80080B1C;

/* Updates two byte counters from count and returns the indexed D_80080B18 byte. */
u8 func_80048DA0(s32 index, s32 count)
{
    u8 *table;

    D_80080B1B = count + 5;
    table = D_80080B18;
    D_80080B1C = (count * 2) + 5;
    return table[index];
}

extern char D_8006ADC0[16]; /* >8B forces hi/lo addressing (pointer stored at offset 0) */
extern char D_800812C8[16]; /* >8B forces hi/lo addressing (address-of target) */

extern void resource_load_current_optional_descriptor(void);

/* Stores the address of D_800812C8 in D_8006ADC0, then calls resource_load_current_optional_descriptor. */
void func_80053CA4(void)
{
    char **pointer_slot = (char **)D_8006ADC0;
    *pointer_slot = D_800812C8;
    resource_load_current_optional_descriptor();
}

/* Ring buffer of 32 history entries, each 0x18 (24) bytes; only offset 0 is
 * accessed here so the rest of the layout is left as padding. */
typedef struct {
    u8 unk00;
    u8 pad[0x17];
} Struct80083968;

extern u8 D_800814D0;
extern Struct80083968 D_80083968[32];

/* Returns the previous history entry byte, wrapping the ring index modulo 32. */
u8 get_previous_cd_command_byte(void) {
    return D_80083968[(D_800814D0 + 0x1F) & 0x1F].unk00;
}

extern unsigned char D_8007382B[9];

extern void func_8005D88C(int value);
extern void func_8005E450(int value);

/* Clears D_8007382B and calls both reset routines with zero. */
void audio_disable_reverb(void)
{
    D_8007382B[0] = 0;
    func_8005D88C(0);
    func_8005E450(0);
}

/* Returns the word at offset 4 of the indexed D_80084960 entry. */
int audio_get_channel_pan(int unused, short index)
{
    return D_80084960[index].unk04;
}

/* Returns the word at offset 0x1C of the indexed D_80084960 entry. */
int audio_get_channel_pitch_bend(int unused, short index) {
    return D_80084960[index].unk1C;
}

/* D_80084960 is an array of structs, each 0x9C (156) bytes; offset 0x1C
   holds a 32-bit field (getter audio_get_channel_pitch_bend does a plain lw from +0x1C). */

/* Stores the low seven bits of value in the indexed D_80084960 entry. */
void audio_set_channel_pitch_bend_value(s32 unused, s16 index, s32 value) {
    D_80084960[index].unk1C = value & 0x7F;
}

/* D_8006ADBC is a 3-word global; splat separately names word[1] as
   D_8006ADC0 elsewhere, but this function addresses it via D_8006ADBC+4
   directly (single base materialised, +4 literal offset), so treat it here
   as one >8B struct so gcc emits %hi/%lo (not $gp-rel). */
typedef struct {
    s32 field0;
    s32 field4;
    s32 field8;
} StructADBC;

extern StructADBC D_8006ADBC;

extern void func_80053C3C(s32 a0);

/* Copies field4 to field0 of D_8006ADBC and forwards nonzero values to func_80053C3C. */
void resource_load_current_optional_descriptor(void) {
    s32 value = D_8006ADBC.field4;

    D_8006ADBC.field0 = value;
    if (value != 0) {
        func_80053C3C(value);
    }
}
