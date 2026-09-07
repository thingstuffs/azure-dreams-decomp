#include "common.h"
#include "m2c_compat.h"

void *func_8003C06C();        /* extern */
M2C_UNK func_800422DC();            /* extern */
M2C_UNK func_800423C0();      /* extern */
M2C_UNK func_80042640();               /* extern */
M2C_UNK memset(); /* extern */
s32 func_8009F970();              /* extern */
void *func_800B2344();                              /* extern */
extern M2C_UNK D_800102F0;
extern M2C_UNK D_80010324;
extern M2C_UNK D_80100A10;
typedef struct {
    s32 words[0x15];
} Record84;
extern Record84 D_80100AF8;

typedef struct Copy16 {
    s32 words[4];
} Copy16;

typedef struct Copy10 {
    s8 bytes[10];
} __attribute__((packed)) Copy10;

typedef struct S_8009FB2C_0 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 unk_03;
} S_8009FB2C_0;   /* temp_v0 in func_8009FB2C */

typedef struct S_8009FB2C_1 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 unk_03;
} S_8009FB2C_1;   /* arg1 in func_8009FB2C */

typedef struct S_8009FB2C_2 {
    u8 pad_00[0x29C];
    void * unk_29C;
    s32 unk_2A0;
} S_8009FB2C_2;   /* temp_v1 in func_8009FB2C */

/* Copies an entry into a slot, creating an associated record for type 0x13. */
void func_8009FB2C(s32 slot_index, S_8009FB2C_1 *source_entry) {
    u8 *copy_dst;
    u8 *copy_src;
    s32 unused_value;
    s32 record_index;
    u8 *copy_end;
    void *detail_dst;
    S_8009FB2C_0 *entry;
    void *detail_src;
    S_8009FB2C_2 *slot;
    void *slot_base;
    register void *stored_entry ASM_REG("$2");   /* MATCH pin: keeps a constant in a register as retail does */

    entry = func_800B2344();
    entry->unk_00 = (u8) source_entry->unk_00;
    entry->unk_01 = (u8) source_entry->unk_01;
    entry->unk_02 = (u8) source_entry->unk_02;
    entry->unk_03 = (u8) source_entry->unk_03;
    if (entry->unk_01 == 0x13) {
        memset(&D_80100A10, 0, 0x54);
        func_80042640(&D_80100A10, entry->unk_00);
        func_800423C0(&D_80100A10, entry->unk_00, 0);
        {
            register u8 *record_buffer ASM_REG("$17");   /* MATCH pin: retail register colouring depends on it */
            record_buffer = (u8 *)&D_80100AF8;
            copy_src = record_buffer;
            func_800422DC(record_buffer, &D_80100A10);
        }
        record_index = func_8009F970((void *)0x800102F0, 0x14);
        copy_dst = (record_index * 0x54) + (u8 *)0x800102F0;
        copy_end = copy_src + 0x50;
        do {
            *(Copy16 *)copy_dst = *(Copy16 *)copy_src;
            copy_src += 0x10;
            copy_dst += 0x10;
        } while (copy_src != copy_end);
        *(s32 *)copy_dst = *(s32 *)copy_src;
        ASM_MEM_BARRIER();   /* MATCH pin: retail immediate-load split depends on it */
        detail_dst = (record_index * 0x54) + (u8 *)0x80010324;
        detail_src = func_8003C06C(entry->unk_00);
        *(Copy10 *)detail_dst = *(Copy10 *)detail_src;
        entry->unk_03 = (u8) ((entry->unk_03 & 0xC0) | record_index);
        ASM_KEEP(entry);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        stored_entry = entry;
    } else {
        stored_entry = entry;
    }
    slot_base = (void *)0x80010000;
    slot = (slot_index * 4) + slot_base;
    slot->unk_29C = stored_entry;
    slot->unk_2A0 = 0;
}
