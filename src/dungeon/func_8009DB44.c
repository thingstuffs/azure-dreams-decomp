#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"


typedef struct S_800A32A4_1 {
    u8 pad_00[0x14A8];
    s32 unk_14A8;
} S_800A32A4_1;   /* page_base in func_800A32A4 */

typedef struct S_800A32A4_2 {
    u8 pad_00[0xAC];
    s32 unk_AC;
    u8 pad_B0[0x20];
    void * unk_D0;
} S_800A32A4_2;   /* temp_a0 in func_800A32A4 */

typedef struct S_800A32A4_3 {
    u8 pad_00[0x3];
    u8 unk_03;
} S_800A32A4_3;   /* temp_s2 in func_800A32A4 */

typedef struct S_800A32A4_4 {
    u8 pad_00[0xD0];
    s32 unk_D0;
} S_800A32A4_4;   /* computed_dest in func_800A32A4 */

typedef struct S_800A32A4_5 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_800A32A4_5;   /* var_a2 in func_800A32A4 */

typedef struct S_800A32A4_6 {
    u8 pad_00[0x1C];
    union { s16 s; u16 u; } unk_1C;   /* accessed as both */
} S_800A32A4_6;   /* temp_a0_2 in func_800A32A4 */

struct S_800E3E48 {
  u8 pad00[0x14];
  s32 unk14;
  u8 pad18[0x1C - 0x18];
  s32 unk1C;
  u8 pad20[0x8C - 0x20];
};
struct S_16 {
  s32 w0;
  s32 w4;
  s32 w8;
  s32 wC;
};
struct S_12 {
  s32 w0;
  s32 w4;
  s32 w8;
};
typedef struct S_800E3E48 S_800E3E48;
extern S_800E3E48 D_800E3E48[];
extern s32 D_800E3DF0[];
extern s32 D_80083460[3];
extern void func_80042B68(void *, s32);
extern M2C_UNK func_800A18E8();
extern M2C_UNK func_800A31D0();

/* Detach a record from its slot, preserve its data, and update its count and state. */
s32 func_800A32A4(void *record) {
    register M2C_UNK update_mode ASM_REG("$17");
    s32 *counter_base;
    s32 slot_offset;
    s32 record_index;
    s32 record_flags;
    register s32 state_flags ASM_REG("$3");
    s32 tail_w0;
    s32 tail_w4;
    s32 tail_w8;
    volatile s32 *tail_src;
    s32 slot_index;
    register S_800A32A4_4 *dest_base ASM_REG("$2");
    S_800A32A4_2 *slot;
    S_800A32A4_3 *entry;
    void *copy_dst;
    void *copy_src;
    u8 *page_base;
    u8 *status_page;
    register s32 flags_mask ASM_REG("$7");
    S_800E3E48 *copy_base;
    s32 *registry;
    void *copy_end;

    update_mode = 0;
    ASM_KEEP_NV(update_mode);
    entry = 0;
    func_80042B68(record, 0x1A);
    func_80042B68(record, 0x1C);
    func_80042B68(record, 0x1D);
    if (!(((Rec_D_800E3D7C *)record)->unk_14.as_s32 & 0x20000000)) {
        func_800A31D0(record);
        slot_index = 0;
        page_base = (u8 *)0x80080000;
        flags_mask = ~0x4000;
        registry = D_800E3DF0;
        copy_base = D_800E3E48;
        copy_end = record + 0x80;
scan_slots:
        slot_offset = slot_index * 4;
        slot = slot_offset + ((S_800A32A4_1 *)page_base)->unk_14A8;
        slot_index += 1;
        if (slot->unk_AC == record) {
            ((Rec_D_800E3D7C *)record)->unk_14.as_s32 = (s32)(((Rec_D_800E3D7C *)record)->unk_14.as_s32 & flags_mask);
            slot->unk_AC = 0;
            state_flags = ((Rec_D_800E3D7C *)record)->unk_1C.as_s32;
            state_flags |= 0x04000000;
            state_flags |= 0x00020000;
            ((Rec_D_800E3D7C *)record)->unk_1C.as_s32 = state_flags;
            entry = slot->unk_D0;
            entry->unk_03 = (u8)(entry->unk_03 & 0xDF);
            dest_base = (void *)((S_800A32A4_1 *)page_base)->unk_14A8;
            dest_base = (void *)((u32)slot_offset + (u32)dest_base);
            dest_base->unk_D0 = 0;
            update_mode = 3;
            copy_src = record;
            record_index = entry->unk_03 & 0x1F;
            dest_base = (void *)((record_index * sizeof(*copy_base)) + (s32)copy_base);
            copy_dst = dest_base;
            registry[record_index] = (s32)copy_dst;
            do {
                *(struct S_16 *)copy_dst = *(struct S_16 *)copy_src;
                copy_src += 0x10;
                copy_dst += 0x10;
            } while (copy_src != copy_end);
            tail_src = (volatile s32 *)copy_src;
            tail_w0 = tail_src[0];
            tail_w4 = tail_src[1];
            tail_w8 = tail_src[2];
            ((S_800A32A4_5 *)copy_dst)->unk_00 = tail_w0;
            ((S_800A32A4_5 *)copy_dst)->unk_04 = tail_w4;
            ((S_800A32A4_5 *)copy_dst)->unk_08 = tail_w8;
            goto update_count;
        }
        if (slot_index >= 4) {
            goto update_count;
        }
        goto scan_slots;
    }
update_count:
    if (update_mode == 0) {
        record_flags = ((Rec_D_800E3D7C *)record)->unk_14.as_s32;
        update_mode = 3;
        if (!(record_flags & 0x4000)) {
            status_page = (u8 *)(record_flags & 0x2000);
            if (status_page) {
                counter_base = D_80083460;
                if (((S_800A32A4_6 *)counter_base)->unk_1C.s != 0) {
                    ((S_800A32A4_6 *)counter_base)->unk_1C.s = (s16)(((S_800A32A4_6 *)counter_base)->unk_1C.u - 1);
                }
                update_mode = 2;
            } else {
                s32 *counter_base;
                counter_base = D_80083460;
                if (((S_800A32A4_6 *)counter_base)->unk_1C.s != 0) {
                    ((S_800A32A4_6 *)counter_base)->unk_1C.s = (s16)(((S_800A32A4_6 *)counter_base)->unk_1C.u - 1);
                }
                update_mode = 1;
            }
        }
    }
    if (!(((Rec_D_800E3D7C *)record)->unk_14.as_s32 & 0x20000000)) {
        func_800A18E8(((Rec_D_800E3D7C *)record)->unk_10.at03_u8.v, update_mode);
    }
    return (s32)entry;
}
