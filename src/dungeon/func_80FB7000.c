#include "common.h"
typedef struct { u8 pad[6]; u16 count; } CountView;
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"


typedef struct S_80FB7000_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80FB7000_0;   /* obj in func_8016A8A4 */

typedef struct S_80FB7000_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_80FB7000_1;   /* work in func_8016A8A4 */

typedef struct S_80FB7000_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80FB7000_2;   /* pin_part_a in func_8016A8A4 */

typedef struct S_80FB7000_3 {
    u8 pad_00[0x8];
    u8 * unk_08;
    u8 pad_0C[0x6];
    u16 unk_12;
    u8 pad_14[0x10];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} S_80FB7000_3;   /* part_b in func_8016A8A4 */

typedef struct S_80FB7000_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
    u8 pad_9D[0x11];
    u16 unk_AE;
} S_80FB7000_4;   /* pin_actor in func_8016A8A4 */


extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern s32 func_800A6D30();
extern void func_800A48F0(void *, s32, s32);
extern void func_800A9C18(void *, void *, void *, s16);
extern void func_800AA36C(void *, void *, void *, void *);
extern void func_800673A0(s16 *, s32, s32);

extern u8 D_8016AB40[];
extern u8 D_8016AF6C[];
extern u8 D_8016F258[];
extern u8 D_8016F298[];



void *func_8016A8A4(s32 spawn_flags, s16 pos_x, s16 pos_y, s16 part_a_value)

;

/* Creates a dungeon actor and initializes its parts, flags, and image regions. */
void *func_8016A8A4(s32 spawn_flags, s16 pos_x, s16 pos_y, s16 part_a_value)
{
    void *work;
    void *obj;
    s32 object_type;
    ObjectNodeHeader *object_pool;
    S_80FB7000_3 *part_b;
    void *part_a;
    s16 saved_flags;
    s32 kind;
    s32 primary_flags;
    s32 secondary_flags;
    u32 entry_index;
    s32 entry_count;
    u16 actor_value;
    s32 twice_index;
    s16 rect[4];
    u8 *entry;
    s16 saved_part_value;
    void *pin_part_a;
    void *pin_actor;

    work = 0;
    object_type = 0x112;
    saved_part_value = part_a_value;
    object_pool = &D_80083498;
    obj = func_8003FD64(object_type, object_pool);
    saved_flags = (s16)spawn_flags;
    if (obj != 0) {
        work = (u8 *)obj + 0x20;
        ((S_80FB7000_0 *)obj)->unk_10 = D_8016AB40;
        ((S_80FB7000_1 *)work)->unk_13 = 0x27;
        func_8004491C(obj, func_80045340);

        pin_part_a = ((S_80FB7000_0 *)obj)->unk_08;
        ((S_80FB7000_2 *)pin_part_a)->unk_0A = saved_part_value;
        part_b = ((S_80FB7000_0 *)obj)->unk_0C;
        kind = spawn_flags & 3;
        part_b->unk_25 = pos_y;
        pin_actor = work;
        part_b->unk_2C = D_8016F258;
        part_b->unk_24 = pos_x;

        if (kind == 1) {
            primary_flags = ((S_80FB7000_1 *)work)->unk_14 | 0x6000;
            secondary_flags = ((S_80FB7000_1 *)work)->unk_1C | 0x6000;
            ((S_80FB7000_1 *)work)->unk_14 = primary_flags;
            ((S_80FB7000_1 *)work)->unk_1C = secondary_flags;
        } else if (kind >= 2) {
            primary_flags = ((S_80FB7000_1 *)work)->unk_14 | 0x2000;
            secondary_flags = ((S_80FB7000_1 *)work)->unk_1C | 0x2000;
            ((S_80FB7000_1 *)work)->unk_14 = primary_flags;
            ((S_80FB7000_1 *)work)->unk_1C = secondary_flags;
        } else {
            {
                s32 non_kind_mask;
                non_kind_mask = -4;
                if (((spawn_flags = (s16)(spawn_flags & non_kind_mask)) << 16) == 0) {
                    if (!(((S_80FB7000_1 *)work)->unk_14 & 0x200)) {
                        if (func_800A6D30() & 1) {
                            ((S_80FB7000_1 *)work)->unk_1C |= 0x200;
                            func_800A48F0(work, 1,
                                          (func_800A6D30() & 0x3F) |
                                          0x20);
                            part_b->unk_2C = D_8016F298;
                        }
                    }
                }
            }
        }

        func_800A9C18(obj, pin_part_a, part_b, saved_flags);

        entry_index = 0;
        actor_value = part_b->unk_12;
        ((S_80FB7000_4 *)pin_actor)->unk_9A = 0xFF;
        ((S_80FB7000_4 *)pin_actor)->unk_9C = -1;
        ((S_80FB7000_4 *)pin_actor)->unk_8C = D_8016AF6C;
        ((S_80FB7000_4 *)pin_actor)->unk_AE = actor_value;

        entry = part_b->unk_08;
        while (1) {
            twice_index = entry_index << 1;
            if (!(*entry & 0x20)) {
                break;
            }
            entry += 12;
            entry_index += 1;
        }

        entry_count = ((CountView *)(part_b->unk_08 + (twice_index + entry_index) * 4))->count >> 6;
        rect[0] = 0;
        rect[1] = entry_count;
        rect[2] = 0x100;
        rect[3] = 1;
        func_800673A0(rect, 0, entry_count - 1);

        rect[2] = 0x10;
        rect[0] = 0x30;
        rect[1] -= 1;
        do {
            {
                func_800673A0(rect, rect[0] - 0x30, rect[1]);
                rect[0] += 0x40;
            }
        } while (rect[0] < 0x100);

        func_800AA36C(pin_actor, pin_part_a, part_b, work);
    }
    return work;
}

#if 0
#endif
