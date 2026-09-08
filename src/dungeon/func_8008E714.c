#include "common.h"
#include "m2c_compat.h"

typedef struct S_80093E74_7 {
    u8 pad_00[0xD0];
    union { void * s; s32 u; } unk_D0;   /* accessed as both */
} S_80093E74_7;   /* ((arg3->unk_8A * 4) + arg0) in func_80093E74 */


typedef struct S_80093E74_0 {
    u8 pad_00[0x60];
    void * unk_60;
    u8 pad_64[0x26];
    s16 unk_8A;
} S_80093E74_0;   /* arg3 in func_80093E74 */

typedef struct S_80093E74_1 {
    u8 pad_00[0x3];
    u8 unk_03;
} S_80093E74_1;   /* temp_a0 in func_80093E74 */

typedef struct S_80093E74_2 {
    u8 pad_00[0x13];
    u8 unk_13;
    u8 pad_14[0x94];
    u8 unk_A8;
} S_80093E74_2;   /* temp_s1 in func_80093E74 */

typedef struct S_80093E74_3 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_80093E74_3;   /* temp_a0_2 in func_80093E74 */

typedef struct S_80093E74_4 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_80093E74_4;   /* temp_a0_3 in func_80093E74 */

typedef struct S_80093E74_5 {
    void * unk_00;
    u8 pad_04[0x2C];
    s32 unk_30;
} S_80093E74_5;   /* temp_v1 in func_80093E74; pointer addresses record offset 0x14 */

typedef struct S_80093E74_6 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80093E74_6;   /* temp_v1_2 in func_80093E74 */


#define M2C_BREAK() ((void)0)
#define M2C_SYNC() ((void)0)

typedef struct {
    s32 words[4];
} Copy16;

typedef struct {
    s32 words[3];
} Copy12;

typedef struct {
    s32 words[35];
} Copy140;

s32 func_80042900();                 /* extern */
void func_8009A3D0(u8, u8, s32);     /* extern */
M2C_UNK func_800A56E0();                     /* extern */
extern void *D_800E3DF0[];
extern u8 D_800E3E48[];

/* Copy the indexed record into storage, clear its owner slot, and trigger an effect. */
void func_80093E74(s32 slot_table, void *unused_arg1, void *unused_arg2, S_80093E74_0 *owner) {
    M2C_UNK effect_mask;
    u8 effect_x;
    u8 effect_y;
    s32 record_index;
    register s32 record_slot_addr ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    register s32 saved_index ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    void **record_table;
    void **record_slot;
    S_80093E74_3 *stored_record;
    S_80093E74_4 *owner_state;
    S_80093E74_2 *source_record;
    void *unused_ptr;
    void *record_storage;
    void *owner_record;
    S_80093E74_6 *position;
    void *unused_ptr2;
    void *unused_ptr3;

    {
        s32 cleared_flags;
        register s32 flags_index ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
        register S_80093E74_1 *slot_entry ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        void **source_table;
        u8 index_byte;

        slot_entry = ((S_80093E74_7 *)(((owner->unk_8A * 4) + slot_table)))->unk_D0.s;
        flags_index = slot_entry->unk_03;
        cleared_flags = flags_index & 0xDF;
        flags_index &= 0x1F;
        ASM_KEEP(flags_index);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        index_byte = (u8)flags_index;
        saved_index = index_byte;
        record_index = saved_index;
        ASM_KEEP(record_index);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
        source_table = D_800E3DF0;
        slot_entry->unk_03 = (u8) cleared_flags;
        record_slot = source_table + record_index;
        source_record = *record_slot;
    }
    if ((func_80042900(source_record, 0xA) << 0x10) != 0) {
        source_record->unk_13 = (u8) source_record->unk_A8;
    }
    record_storage = &D_800E3E48[((((record_index * 8) + record_index) * 4) - record_index) * 4];
    *record_slot = record_storage;
    *(Copy140 *) record_storage = *(Copy140 *) source_record;
    record_table = D_800E3DF0;
    ASM_KEEP(record_table);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    record_slot_addr = saved_index << 2;
    record_slot_addr += (s32)record_table;
    stored_record = *(void **)record_slot_addr;
    stored_record->unk_14 = (s32) (stored_record->unk_14 & ~0x4000);
    ((S_80093E74_7 *)(((owner->unk_8A * 4) + slot_table)))->unk_D0.u = 0;
    owner_state = owner->unk_60;
    owner_state->unk_1C = (s32) (owner_state->unk_1C | 0x400000);
    owner_record = owner->unk_60;
    position = ((S_80093E74_5 *)((u8 *)owner_record - 0x14))->unk_00;
    effect_x = position->unk_24;
    effect_y = position->unk_25;
    effect_mask = 0x3000;
    if (((S_80093E74_5 *)((u8 *)owner_record - 0x14))->unk_30 & 0x2000) {
        effect_mask = 0x300;
    }
    func_8009A3D0(effect_x, effect_y, effect_mask);
    func_800A56E0(0x704);
}
