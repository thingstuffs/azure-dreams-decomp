/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

typedef struct S_8001A200_0 {
    u8 pad_00[0x20];
    void * unk_20;
} S_8001A200_0;   /* D_80016000[0] in func_8001A200 */

typedef struct S_8001A200_1 {
    u8 pad_00[0x2D4];
    s32 (*unk_2D4)(M2C_UNK);
} S_8001A200_1;   /* temp_v0 in func_8001A200 */

typedef struct S_8001A200_2 {
    u8 pad_00[0x1];
    u8 unk_01;
} S_8001A200_2;   /* var_s0 in func_8001A200 */


M2C_UNK func_8001A188();     /* extern */
extern void *D_80016000[3];
extern u8 D_8001791C[96];

/* Dispatches each record to the first matching kind-table entry. */
void func_8001A200(void *records, s32 *value_sets) {
    u8 *kind_entry;
    s32 record_kind;
    s32 values_base;
    s32 table_kind;
    void *context;
    s32 value_addr;
    s32 slot_index;
    register u8 *kind_table ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    u8 *status_ptr;
    register void *record ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register u8 *table_page ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 next_status;
    register s32 end_mask ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

    record = records;
    context = ((S_8001A200_0 *)(D_80016000[0]))->unk_20;
    status_ptr = (u8 *)value_sets;
    values_base = *((((S_8001A200_1 *)context)->unk_2D4(0)) + (s32 *)status_ptr);
    if ((((S_8001A200_2 *)record)->unk_01 & 0xC0) != 0x80) {
        table_page = (u8 *)0x80010000;
        ASM_KEEP(table_page);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        kind_table = table_page + 0x791C;
        status_ptr = record + 1;
next_record:
        slot_index = 1;
        value_addr = values_base + 4;
        kind_entry = kind_table + 0xC;
next_kind:
        table_kind = *(s32 *)kind_entry;
        record_kind = (*(s32 *)((u8 *)status_ptr + 0xB));
        if ((table_kind == record_kind) || ((table_kind == 6) && (record_kind == 0x64))) {
            func_8001A188(record, value_addr, kind_entry, slot_index);
        } else {
            value_addr += 4;
            slot_index += 1;
            kind_entry += 0xC;
            if (slot_index < 8) {
                goto next_kind;
            }
        }
        status_ptr += 0x14;
        record += 0x14;
        next_status = *status_ptr;
        end_mask = 0x80;
        if ((next_status & 0xC0) == end_mask) {
        } else {
            goto next_record;
        }
    }
}
