#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80067014();                     /* extern */
M2C_UNK func_800672D8();                  /* extern */
extern s16 D_80083D78[];


typedef struct S_800B5B20_0 {
    u8 pad_00[0x4];
    u16 unk_04;
    u16 unk_06;
    u8 unk_08;
    u8 unk_09;
    u8 unk_0A;
    u8 unk_0B;
} S_800B5B20_0;   /* temp_s0 in func_800B5B20 */

void func_800B5B20(void *arg0) {
    s32 table_index;
    volatile s16 sp10;
    volatile s16 sp12;
    volatile s16 sp14;
    volatile s16 sp16;
    void *temp_s1 = arg0;
    void *temp_s0;
    s16 *table_a0;

    
    if ((*(s32 *)((u8 *)temp_s1 + 0xD4)) != 0) {
        func_80067014(0);
        table_a0 = D_80083D78;
        table_index = (*(s16 *)((u8 *)temp_s1 + 8));
        temp_s0 = (*(void * volatile *)((u8 *)temp_s1 + 0x14));
        (*(s32 *)((u8 *)temp_s1 + 0xD0)) = 0;
        (*(s32 *)((u8 *)temp_s1 + 0xD4)) = 0;
        table_a0[table_index * 2] = (*(u16 *)((u8 *)temp_s1 + 0xA));
        table_a0[((*(s16 *)((u8 *)temp_s1 + 8)) * 2) + 1] = (*(u16 *)((u8 *)temp_s1 + 0x10));
        
        sp10 = ((u8) ((S_800B5B20_0 *)temp_s0)->unk_08 >> 2) + ((((S_800B5B20_0 *)temp_s0)->unk_04 << 6) & 0x3C0);
        sp12 = ((S_800B5B20_0 *)temp_s0)->unk_09 + (((*(u16 *)((u8 *)temp_s0 + 4)) * 0x10) & 0x100);
        sp14 = (s16) ((u8) ((S_800B5B20_0 *)temp_s0)->unk_0A >> 2);
        sp16 = (s16) ((S_800B5B20_0 *)temp_s0)->unk_0B;
        func_800672D8(&sp10, (*(s32 *)((u8 *)temp_s1 + 0xE0)));
        if ((*(s16 *)((u8 *)temp_s1 + 8)) != 0) {
            volatile s16 *sp10_a0 = &sp10;
            u16 temp_v1;
            s32 offset_a1;
            s32 base_v0;

            
            sp10 = (((S_800B5B20_0 *)temp_s0)->unk_06 & 0x3F) * 0x10;
            temp_v1 = (*(u16 *)((u8 *)temp_s0 + 6));
            sp14 = 0x10;
            sp16 = 1;
            temp_v1 >>= 6;
            sp12 = (s16) temp_v1;
            
            offset_a1 = (*(s32 *)((u8 *)temp_s1 + 0x10));
            base_v0 = (*(s32 *)((u8 *)temp_s1 + 0xE0));
            offset_a1 <<= 5;
            offset_a1 += 0x200;
            
            func_800672D8(sp10_a0, base_v0 + offset_a1);
        }
        func_80067014(0);
    }
    (*(s32 *)((u8 *)temp_s1 + 0xE0)) = 0;
}

/* MECHANISM: Four volatile s16 frame objects preserve the 0x28 frame and all sibling stores.
   arg0 stays pinned in s1 while the cross-call nested pointer allocates naturally to s0.
   Pinned table/a0 and split v1/a1 live ranges reproduce the table, branch-slot, and tail order. */
