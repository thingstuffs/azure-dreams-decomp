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
        register u32 kind ASM_REG("$2");
        unsigned long swi;

        kind = entry[3];
        ASM_KEEP_NV(kind);
        swi = kind - 1;
        ASM_KEEP_NV(swi);
        if (swi >= 16) {
            goto case_default;
        }
        (void)sw_keep;
        {
            register unsigned long jump ASM_REG("$2");

            jump = (unsigned long)D_80089490;
            ASM_KEEP_NV(jump);
            swi *= sizeof(void *);
            ASM_KEEP_NV(swi);
            swi += jump;
            ASM_KEEP_NV(swi);
            jump = *(unsigned long *)swi;
            ASM_KEEP_NV(jump);
            goto *(void *)jump;
        }
    }

case_4_8:
    {
        u8 *case_entry;
        u8 *loop_entry;
        u8 *table_base;
        u8 *table_row;
        register u32 index ASM_REG("$4");
        s32 i;
        register u32 masked ASM_REG("$2");

        {
            register u8 *case_base ASM_REG("$2");

            case_base = D_800D2EA4 - 0x860;
            ASM_KEEP_NV(case_base);
            index = (u8)raw_arg;
            case_entry = (u8 *)(index << 5);
            ASM_KEEP_NV(case_entry);
            case_entry = (u8 *)((u32)case_entry + (u32)case_base);
        }
        ASM_KEEP_NV(index);
        {
            u32 value;

            value = case_entry[6];
            ASM_KEEP_NV(value);
            if (value == 0) {
                goto case_default;
            }
        }
        table_base = (u8 *)0x80010000;
        i = 0;
        loop_entry = case_entry;
        ASM_KEEP_NV(loop_entry);
        do {
            masked = i & 0xFF;
            masked *= 2;
            ASM_KEEP_NV(masked);
            table_row = (u8 *)((u32)masked + (u32)table_base);
            ASM_KEEP_NV(table_row);
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
        register u8 *case_base ASM_REG("$3");
        u32 index;
        register u32 value ASM_REG("$5");

        case_base = D_800D2EA4 - 0x860;
        ASM_KEEP_NV(case_base);
        index = (u8)raw_arg;
        ASM_KEEP_NV(index);
        case_entry = (u8 *)(index << 5);
        ASM_KEEP_NV(case_entry);
        case_entry = (u8 *)((u32)case_entry + (u32)case_base);
        ASM_KEEP_NV(case_entry);
        value = case_entry[6];
        ASM_KEEP_NV(value);
        if (value == 0) {
            goto case_default;
        }
        ASM_KEEP_NV(value);
        {
            u32 global_value;

            global_value = 0x80010000;
            ASM_KEEP_NV(global_value);
            global_value = *(u8 *)(global_value + 0x33E6);
            ASM_KEEP_NV(global_value);
            if (global_value != value) {
                goto case_default;
            }
        }
        {
            u8 *second_base;
            u32 second_value;

            second_base = (u8 *)0x80010000;
            ASM_KEEP_NV(second_base);
            second_value = second_base[0x33E7];
            ASM_KEEP_NV(second_value);
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
        register u32 index ASM_REG("$4");
        register s32 i ASM_REG("$6");
        u32 masked;
        register u32 entry_offset ASM_REG("$3");
        register u32 scaled ASM_REG("$2");
        u8 first;
        register u32 second ASM_REG("$8");

        i = 0;
        table_base = (u8 *)0x80010000;
        base_temp = (u8 *)0x800D0000;
        ASM_KEEP_NV(base_temp);
        match_base = base_temp + 0x2EA4;
        index = (u8)raw_arg;
        base_temp = D_800D2644_case1;
        entry_offset = index << 5;
        ASM_KEEP_NV(entry_offset);
        case_entry = base_temp + entry_offset;
        ASM_KEEP_NV(match_base);
        do {
            masked = i & 0xFF;
            scaled = masked * 2;
            ASM_KEEP_NV(scaled);
            table_row = (u8 *)((u32)scaled + (u32)table_base);
            first = table_row[0x33A4];
            if ((first == index) ||
                (second = table_row[0x33A5], second == index)) {
                out = out_start;
                count = 0;
                goto case_default;
            }
            ASM_KEEP_NV(second);
            scaled = masked * 8;
            ASM_KEEP_NV(scaled);
            match = (u8 *)((u32)scaled + (u32)match_base);
            ASM_KEEP_NV(match);
            if (match[2] != case_entry[4])
                goto case_1_next;
            if (match[3] != case_entry[5])
                goto case_1_next;
            if (first < 0x2D)
                goto case_1_next;
            scaled = 0x30;
            ASM_KEEP_NV(scaled);
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
    ASM_KEEP_NV(raw_arg);
    return (u8)count;
}
