#include "common.h"

extern s32 func_80033B2C(s16);
extern u8 D_800133E6;
extern s8 D_800133E7[9];
extern void *D_80089490[];
extern u8 D_800D2644[];
extern u8 D_800D2EA4[];
extern u8 D_800D2644_case1[] __asm__("D_800D2644");
extern u8 D_80010000[];

/* CheckBuildBuildingLandNo collects eligible land slots for a building and returns their count. */
s32 CheckBuildBuildingLandNo(s32 entry_id, s8 *slots_out) {
    static void *const case_labels[] = {
        &&case_1, &&case_default, &&case_default, &&case_4_8,
        &&case_default, &&case_default, &&case_default, &&case_4_8,
        &&case_default, &&case_default, &&case_default, &&case_default,
        &&case_default, &&case_default, &&case_default, &&case_16
    };
    s8 *slot_out;
    s32 raw_entry_id;
    s8 *slots_start;
    u8 *entry;
    u8 *entry_table;
    s32 slot_count;

    slot_out = slots_out;
    raw_entry_id = entry_id;
    slot_count = 0;
    entry_table = D_800D2644;
    entry = entry_table + ((u8)raw_entry_id << 5);
    slots_start = slot_out;
    if (func_80033B2C(*(s16 *)(entry + 8)) == 0) {
        return 0;
    }

    {
        unsigned long dispatch_addr;

        entry_id = entry[3];
        dispatch_addr = entry_id - 1;
           /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        if (dispatch_addr >= 16) {
            goto case_default;
        }
        (void)case_labels;
        {
            unsigned long jump_addr;

            jump_addr = (unsigned long)D_80089490;
            dispatch_addr *= sizeof(void *);
            dispatch_addr += jump_addr;
            jump_addr = *(unsigned long *)dispatch_addr;
            goto *(void *)jump_addr;
        }
    }

case_4_8:
    {
        u8 *selected_entry;
        u8 *filter_entry;
        u8 *slot_table_base;
        u8 *slot_row;
        register u32 selected_id ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        s32 slot;
        u32 slot_offset;

        {
            register u8 *entry_base ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

            entry_base = D_800D2EA4 - 0x860;
            selected_id = (u8)raw_entry_id;
            selected_entry = (u8 *)(selected_id << 5);
            selected_entry = (u8 *)((u32)selected_entry + (u32)entry_base);
        }
        ASM_KEEP_NV(selected_id);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        {
            u32 link_id;

            do {
                link_id = selected_entry[6];
            } while (0);
            if (link_id == 0) {
                goto case_default;
            }
        }
        slot_table_base = (u8 *)0x80010000;
        slot = 0;
        filter_entry = selected_entry;
        ASM_KEEP_NV(filter_entry);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
        do {
            slot_offset = slot & 0xFF;
            slot_offset *= 2;
            slot_row = (u8 *)((u32)slot_offset + (u32)slot_table_base);
            ASM_KEEP_NV(slot_row);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            if ((slot_row[0x33A4] == filter_entry[6]) &&
                (slot_row[0x33A5] != selected_id)) {
                *slot_out++ = (u8)slot;
                slot_count++;
            }
            slot++;
        } while ((u8)slot < 0x21);
        *slot_out = 0;
        goto return_count;
    }

case_16:
    {
        u8 *selected_entry;
        register u8 *entry_base ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
        u32 selected_id;
        register u32 link_id ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

        entry_base = D_800D2EA4 - 0x860;
        selected_id = (u8)raw_entry_id;
        selected_entry = (u8 *)(selected_id << 5);
        selected_entry = (u8 *)((u32)selected_entry + (u32)entry_base);
        link_id = selected_entry[6];
        if (link_id == 0) {
            goto case_default;
        }
        {
            u32 special_link_id;

            special_link_id = 0x80010000;
            special_link_id = *(u8 *)(special_link_id + 0x33E6);
            if (special_link_id != link_id) {
                goto case_default;
            }
        }
        {
            u32 special_entry_id;

            special_entry_id = D_80010000[0x33E7];
            ASM_KEEP_NV(special_entry_id);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            if (special_entry_id == selected_id) {
                goto case_default;
            }
        }
        *slot_out++ = 0xB;
        slot_count++;
        goto case_default;
    }

case_1:
    {
        u8 *selected_entry;
        u8 *slot_data_base;
        u8 *data_base;
        u8 *slot_data;
        u8 *slot_table_base;
        u8 *slot_row;
        register u32 selected_id ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        register s32 slot ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        u32 slot_index;
        register u32 entry_offset ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
        u32 row_offset;
        u8 primary_id;
        u32 secondary_id;

        slot = 0;
        slot_table_base = (u8 *)0x80010000;
        data_base = (u8 *)0x800D0000;
        ASM_KEEP_NV(data_base);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        slot_data_base = data_base + 0x2EA4;
        selected_id = (u8)raw_entry_id;
        data_base = D_800D2644_case1;
        entry_offset = selected_id << 5;
        selected_entry = data_base + entry_offset;
        ASM_KEEP_NV(slot_data_base);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        do {
            slot_index = slot & 0xFF;
            row_offset = slot_index * 2;
            slot_row = (u8 *)((u32)row_offset + (u32)slot_table_base);
            primary_id = slot_row[0x33A4];
            if ((primary_id == selected_id) ||
                (secondary_id = slot_row[0x33A5], secondary_id == selected_id)) {
                slot_out = slots_start;
                slot_count = 0;
                goto case_default;
            }
            row_offset = slot_index * 8;
            slot_data = (u8 *)((u32)row_offset + (u32)slot_data_base);
            if (slot_data[2] != selected_entry[4])
                goto case_1_next;
            if (slot_data[3] != selected_entry[5])
                goto case_1_next;
            if (primary_id < 0x2D)
                goto case_1_next;
            row_offset = 0x30;
            if (primary_id == row_offset)
                goto case_1_next;
            if (secondary_id != 0)
                goto case_1_next;
            *slot_out++ = (u8)slot;
            slot_count++;
case_1_next:
            slot++;
        } while ((u8)slot < 0x21);
    }

case_default:
    *slot_out = 0;
return_count:
    ASM_KEEP_NV(raw_entry_id);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    return (u8)slot_count;
}
