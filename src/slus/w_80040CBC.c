#include "common.h"

struct S_8006CE80_ptr
{
    s32 *f0;
    s32 f1;
};
struct S_8006CE80
{
    u16 field0;
    u8 pad2[6];
    struct S_8006CE80_ptr *field8;
};
extern struct S_8006CE80 D_8006CE80[];
struct S_8006CE44
{
    s32 field0;
    s32 *field4;
};
extern struct S_8006CE44 D_8006CE44[];
extern s32 D_8006CE6C[];
struct S_80082E60
{
    s32 field_0;
    s32 field_4;
    u8 pad_8[2];
    u8 field_A;
    u8 pad_B[0x18 - 0xB];
};
extern struct S_80082E60 D_80082E60;
struct S_pad9
{
    s32 field0;
    s32 pad4;
    s32 pad8;
};
extern struct S_pad9 D_8008333C[];
extern s32 D_80080A7C;
extern s32 D_8008148C;
extern s32 D_80189394;
extern s32 D_801B8EB8;
extern s8 D_80080A86;
extern u8 D_800E6000[];
extern u8 D_80126804[];
extern void func_8003F6D4(int a0, int a1, int *a2, int a3);
extern int Control_CD(int a0, void *a1, int a2);
extern void func_8003F320(void);
extern void func_800418B4(void);
/* Loads the entry's resource data and selects its working buffer. */
void func_80040CBC(s16 entry_index)
{
    struct S_8006CE80 *entry;
    s32 resource_type;
    int request_a[2];
    int request_b[2];
    entry = &D_8006CE80[entry_index];
    resource_type = entry->field0;
    D_80080A86 = 0;
    D_8008333C[0].field0 = 0;
    if (resource_type != 0) {
        if (resource_type != 4) {
            if (D_80082E60.field_A != resource_type) {
                s32 block_count;
                s32 *resource_info;
                s32 block_offset;
                D_80082E60.field_A = resource_type;
                block_count = D_8006CE6C[resource_type];
                resource_info = D_8006CE44[resource_type].field4;
                block_offset = 0;
                if ((block_count - 0x200) > 0) {
                    u32 offset_mask;
                    int *next_request;
                    offset_mask = 0x7FFFFF;
                    next_request = request_b;
                    do {
                        func_8003F6D4(0x100, (resource_info[0] & offset_mask) + (block_offset << 11), request_a,
                            resource_info[1] + block_offset);
                        Control_CD(6, request_a, 0);
                        block_offset += 0x100;
                        func_8003F6D4(0x100, (resource_info[0] & offset_mask) + (block_offset << 11), next_request,
                            resource_info[1] + block_offset);
                        Control_CD(6, next_request, 0);
                        func_8003F320();
                        block_offset += 0x100;
                    }
                    while (block_offset < (block_count - 0x200));
                }
                {
                    u32 packed_info = resource_info[0];
                    block_count = packed_info >> 23;
                    if (block_count != 0) {
                        func_8003F6D4(block_count, (packed_info & 0x7FFFFF) + (block_offset << 11), request_a,
                            resource_info[1] + block_offset);
                        Control_CD(6, request_a, 0);
                    }
                    func_8003F320();
                }
            }
        }
        else {
            func_800418B4();
            D_801B8EB8 = *entry->field8->f0;
            D_80189394 = entry->field8->f1;
        }
    }
    {
        s32 buffer_size;
        s32 buffer_address;
        if (resource_type == 2) {
            buffer_size = 0x18800;
            buffer_address = (s32) (&D_800E6000);
            D_8008148C = buffer_address;
        }
        else {
            buffer_size = 0x38000;
            buffer_address = (s32) (&D_80126804);
            D_8008148C = buffer_address;
        }
        D_80080A7C = buffer_size;
    }
    D_80082E60.field_4 = D_8006CE44[resource_type].field0;
}
