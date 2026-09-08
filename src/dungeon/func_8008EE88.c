#include "common.h"

typedef struct __attribute__((packed)) {
    u8 pad0000[0x248];
    u32 copy_src;
    u8 pad024c[0x21E8 - 0x24C];
    u32 copy_dst;
} Global1004C;

typedef struct {
    u32 word[35];
} Blob140;

extern s32 D_800E3DF0[];
extern u8 D_800E3E48[];

extern void func_800422DC(void *, void *);
extern s8 func_800422A8(s32, void *, s32, s32);
extern s32 func_80042900(void *, s32);
extern void func_800A9160(u16);

void func_800945E8(void *arg0) {
    void *arg;

    arg = arg0;
    func_800422DC((void *)0x80012194, arg);

    {
        s32 counter;
        s32 index;
        u8 flags;
        register u8 *entry ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        register u8 *data ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        s32 *table;
        u8 *copy_base;
        Blob140 *copy_src;
        Blob140 *copy_dst;
        u8 *temp;
        unsigned long offset;
        s32 *store_slot;

        counter = 0x13;
        temp = (u8 *)0x800E0000;
        ASM_KEEP_NV(temp);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        table = (s32 *)(temp + 0x3DF0);
        temp = (u8 *)0x800E0000;
        ASM_KEEP_NV(temp);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        copy_base = temp + 0x3E48;
        entry = (u8 *)0x8001024B;
        do {
        if (entry[-2] == 0x13) {
            flags = entry[0];
            if ((flags & 0x20) != 0) {
                index = flags & 0x1F;
                data = (u8 *)table[index];
                if ((func_80042900(data, 0xA) << 0x10) != 0) {
                    data[0x13] = data[0xA8];
                }
                offset = index * 0x8C;
                copy_dst = (Blob140 *)(offset + (unsigned long)copy_base);
                copy_src = (Blob140 *)data;
                ASM_KEEP_NV(copy_dst);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                ASM_KEEP_NV(copy_src);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
                {
                    u32 *copy_src_cursor = copy_src->word;
                    volatile u32 *copy_dst_cursor = copy_dst->word;
                    u32 *copy_end = copy_src_cursor + 32;

                    do {
                        u32 copy_word0 = copy_src_cursor[0];
                        u32 copy_word1 = copy_src_cursor[1];
                        u32 copy_word2 = copy_src_cursor[2];
                        u32 copy_word3 = copy_src_cursor[3];

                        copy_dst_cursor[0] = copy_word0;
                        copy_dst_cursor[1] = copy_word1;
                        copy_dst_cursor[2] = copy_word2;
                        copy_dst_cursor[3] = copy_word3;
                        ASM_MEM_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                        copy_src_cursor += 4;
                        copy_dst_cursor += 4;
                    } while (copy_src_cursor != copy_end);

                    {
                        u32 copy_word0 = copy_src_cursor[0];
                        u32 copy_word1 = copy_src_cursor[1];
                        u32 copy_word2 = copy_src_cursor[2];

                        copy_dst_cursor[0] = copy_word0;
                        copy_dst_cursor[1] = copy_word1;
                        copy_dst_cursor[2] = copy_word2;
                    }
                }
                ASM_KEEP(index);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                store_slot = (s32 *)((index << 2) + (unsigned long)table);
                offset = index * 0x8C;
                ASM_KEEP_NV(store_slot);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                *store_slot = (s32)(offset + (unsigned long)copy_base);
            }
        }
        ASM_KEEP(counter);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        ASM_KEEP(entry);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        counter -= 1;
        entry += 4;
        } while (counter >= 0);
    }

    {
        s32 counter;
        register s32 *index_ptr ASM_REG("$21");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        u8 *source;
        register u8 *destination ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
        register u8 *output ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        Global1004C *block;
        register u8 *page ASM_REG("$23");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        Blob140 *copy_src;
        Blob140 *copy_dst;
        u8 *temp;
        s32 call_arg;
        void *call_base;
        s32 call_size;
        s32 call_count;

        counter = 0x13;
        output = (u8 *)0x80010013;
        temp = (u8 *)0x800E0000;
        ASM_KEEP_NV(temp);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        temp += 0x3DF0;
        ASM_KEEP_NV(temp);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        index_ptr = (s32 *)temp + 0x13;
        page = (u8 *)0x800E0000;
        ASM_KEEP_NV(page);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
        temp = page + 0x3E48;
        ASM_KEEP_NV(temp);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        source = temp + 0xA64;
        destination = (u8 *)0x80010A64;
        block = (Global1004C *)0x8001004C;
        do {
        block->copy_dst = block->copy_src;
        ASM_SET(call_base);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        call_base = (void *)0x80010248;
        call_size = 4;
        call_arg = *(s32 *)((u8 *)block + 0x29C);
        call_count = 0x14;
        output[0x2238] = func_800422A8(call_arg, call_base, call_size, call_count);
        copy_dst = (Blob140 *)(destination + 0x2260);
        copy_src = (Blob140 *)source;
        ASM_KEEP_NV(copy_dst);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        {
            u32 *copy_src_cursor = copy_src->word;
            volatile u32 *copy_dst_cursor = copy_dst->word;
            u32 *copy_end = (u32 *)(source + 0x80);

            do {
                u32 copy_word0 = copy_src_cursor[0];
                u32 copy_word1 = copy_src_cursor[1];
                u32 copy_word2 = copy_src_cursor[2];
                u32 copy_word3 = copy_src_cursor[3];

                copy_dst_cursor[0] = copy_word0;
                copy_dst_cursor[1] = copy_word1;
                copy_dst_cursor[2] = copy_word2;
                copy_dst_cursor[3] = copy_word3;
                ASM_MEM_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                copy_src_cursor += 4;
                copy_dst_cursor += 4;
            } while (copy_src_cursor != copy_end);

            {
                u32 copy_word0 = copy_src_cursor[0];
                u32 copy_word1 = copy_src_cursor[1];
                u32 copy_word2 = copy_src_cursor[2];

                copy_dst_cursor[0] = copy_word0;
                copy_dst_cursor[1] = copy_word1;
                copy_dst_cursor[2] = copy_word2;
            }
        }
        ASM_KEEP(page);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        ASM_KEEP(counter);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        ASM_KEEP(index_ptr);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        ASM_KEEP(source);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        ASM_KEEP(destination);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        ASM_KEEP(block);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        call_base = page + 0x3E48;
        call_size = 0x8C;
        call_count = 0x14;
        call_arg = *index_ptr;
        ASM_KEEP4_NV(call_arg, call_base, call_size, call_count);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        index_ptr -= 1;
        source -= 0x8C;
        destination -= 0x8C;
        block = (Global1004C *)((u8 *)block - 4);
        counter -= 1;
        output[0x224C] = func_800422A8(call_arg, call_base, call_size, call_count);
        ASM_KEEP(output);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        output -= 1;
        } while (counter >= 0);
    }

    {
        register s32 counter ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        register u8 *source ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        u8 *output;
        s32 call_arg;
        void *call_base;
        s32 call_size;
        s32 call_count;

        counter = 1;
        output = (u8 *)0x80010000;
        ASM_KEEP(arg);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
        source = (u8 *)arg + 4;
        do {
        call_base = (void *)0x80010248;
        call_size = 4;
        call_count = 0x14;
        call_arg = *(s32 *)(source + 0xD0);
        ASM_KEEP4_NV(call_arg, call_base, call_size, call_count);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        source -= 4;
        output[counter + 0x2D52] = func_800422A8(call_arg, call_base, call_size, call_count);
        counter -= 1;
        } while (counter >= 0);
    }

    {
        u8 *global;
        u32 value;
        u32 saved_b;

        global = (u8 *)0x80010000;
        value = *(u16 *)(global + 0x3626);
        saved_b = *(u16 *)(global + 0x209E);
        *(u16 *)(global + 0x3624) = value;
        *(u16 *)(global + 0x209C) = saved_b;
        value = *(u16 *)((u8 *)arg + 0xF8);
        *(u16 *)(global + 0x2D50) = value;
        value = *(s32 *)((u8 *)arg + 0xFC);
        *(s32 *)(global + 0x2D58) = value;
        value = ((u8 *)arg)[0xFA];
        global[0x2D6C] = value;
        value = ((u8 *)arg)[0xFB];
        global[0x2D6D] = value;
        func_800A9160(saved_b);
    }
}
