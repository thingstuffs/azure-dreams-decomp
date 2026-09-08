#include "common.h"

extern s32 func_80033B2C(s16);
extern u8 D_800133E6;
extern s8 D_800133E7[9];
extern void *D_80089490[];
extern u8 D_800D2644[];
extern u8 D_800D2EA4[];
extern u8 D_800D2644_case1[] __asm__("D_800D2644");

s32 func_800B85E8(s32 arg0, s8 *arg1) {
    static void *const sw_keep[] = {
        &&case_1, &&case_default, &&case_default, &&case_4_8,
        &&case_default, &&case_default, &&case_default, &&case_4_8,
        &&case_default, &&case_default, &&case_default, &&case_default,
        &&case_default, &&case_default, &&case_default, &&case_16
    };
    s8 *out;
    s32 raw_arg;
    s8 *out_start;
    u8 *entry;
    u8 *base;
    s32 count;

    out = arg1;
    raw_arg = arg0;
    count = 0;
    base = D_800D2644;
    entry = base + ((u8)raw_arg << 5);
    out_start = out;
    if (func_80033B2C(*(s16 *)(entry + 8)) == 0) {
        return 0;
    }

    {
        register u32 kind ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        unsigned long swi;

        kind = entry[3];
        swi = kind - 1;
        ASM_KEEP_NV(swi);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        if (swi >= 16) {
            goto case_default;
        }
        (void)sw_keep;
        {
            unsigned long jump;

            jump = (unsigned long)D_80089490;
            swi *= sizeof(void *);
            swi += jump;
            jump = *(unsigned long *)swi;
            goto *(void *)jump;
        }
    }

case_4_8:
    {
        u8 *case_entry;
        u8 *loop_entry;
        u8 *table_base;
        u8 *table_row;
        register u32 index ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        s32 i;
        u32 masked;

        {
            register u8 *case_base ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

            case_base = D_800D2EA4 - 0x860;
            index = (u8)raw_arg;
            case_entry = (u8 *)(index << 5);
            case_entry = (u8 *)((u32)case_entry + (u32)case_base);
        }
        ASM_KEEP_NV(index);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        {
            u32 value;

            value = case_entry[6];
            ASM_KEEP_NV(value);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            if (value == 0) {
                goto case_default;
            }
        }
        table_base = (u8 *)0x80010000;
        i = 0;
        loop_entry = case_entry;
        ASM_KEEP_NV(loop_entry);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
        do {
            masked = i & 0xFF;
            masked *= 2;
            table_row = (u8 *)((u32)masked + (u32)table_base);
            ASM_KEEP_NV(table_row);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            if ((table_row[0x33A4] == loop_entry[6]) &&
                (table_row[0x33A5] != index)) {
                *out++ = (u8)i;
                count++;
            }
            i++;
        } while ((u8)i < 0x21);
        *out = 0;
        goto return_count;
    }

case_16:
    {
        u8 *case_entry;
        register u8 *case_base ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
        u32 index;
        register u32 value ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

        case_base = D_800D2EA4 - 0x860;
        index = (u8)raw_arg;
        case_entry = (u8 *)(index << 5);
        case_entry = (u8 *)((u32)case_entry + (u32)case_base);
        value = case_entry[6];
        if (value == 0) {
            goto case_default;
        }
        {
            u32 global_value;

            global_value = 0x80010000;
            global_value = *(u8 *)(global_value + 0x33E6);
            if (global_value != value) {
                goto case_default;
            }
        }
        {
            u8 *second_base;
            u32 second_value;

            second_base = (u8 *)0x80010000;
            ASM_KEEP_NV(second_base);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
            second_value = second_base[0x33E7];
            ASM_KEEP_NV(second_value);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            if (second_value == index) {
                goto case_default;
            }
        }
        *out++ = 0xB;
        count++;
        goto case_default;
    }

case_1:
    {
        u8 *case_entry;
        u8 *match_base;
        u8 *base_temp;
        u8 *match;
        u8 *table_base;
        u8 *table_row;
        register u32 index ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        register s32 i ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        u32 masked;
        register u32 entry_offset ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
        u32 scaled;
        u8 first;
        u32 second;

        i = 0;
        table_base = (u8 *)0x80010000;
        base_temp = (u8 *)0x800D0000;
        ASM_KEEP_NV(base_temp);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        match_base = base_temp + 0x2EA4;
        index = (u8)raw_arg;
        base_temp = D_800D2644_case1;
        entry_offset = index << 5;
        case_entry = base_temp + entry_offset;
        ASM_KEEP_NV(match_base);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        do {
            masked = i & 0xFF;
            scaled = masked * 2;
            table_row = (u8 *)((u32)scaled + (u32)table_base);
            first = table_row[0x33A4];
            if ((first == index) ||
                (second = table_row[0x33A5], second == index)) {
                out = out_start;
                count = 0;
                goto case_default;
            }
            scaled = masked * 8;
            match = (u8 *)((u32)scaled + (u32)match_base);
            if (match[2] != case_entry[4])
                goto case_1_next;
            if (match[3] != case_entry[5])
                goto case_1_next;
            if (first < 0x2D)
                goto case_1_next;
            scaled = 0x30;
            if (first == scaled)
                goto case_1_next;
            if (second != 0)
                goto case_1_next;
            *out++ = (u8)i;
            count++;
case_1_next:
            i++;
        } while ((u8)i < 0x21);
    }

case_default:
    *out = 0;
return_count:
    ASM_KEEP_NV(raw_arg);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    return (u8)count;
}
