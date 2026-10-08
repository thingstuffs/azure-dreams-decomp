/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
typedef struct { u8 pad[6]; u16 count; } CountView;
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"

typedef struct S_80FC9000_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80FC9000_0;   /* obj in BODY_NAME */

typedef struct S_80FC9000_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_80FC9000_1;   /* work in BODY_NAME */

typedef struct S_80FC9000_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80FC9000_2;   /* pin_part_a in BODY_NAME */

typedef struct S_80FC9000_3 {
    u8 pad_00[0x8];
    u8 * unk_08;
    u8 pad_0C[0x6];
    u16 unk_12;
    u8 pad_14[0x10];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} S_80FC9000_3;   /* part_b in BODY_NAME */

typedef struct S_80FC9000_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
    u8 pad_9D[0x11];
    u16 unk_AE;
} S_80FC9000_4;   /* pin_actor in BODY_NAME */


extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern void func_800673A0(s16 *, s32, s32);
extern void func_800A48F0(void *, s32, s32);
extern s32 func_800A6D30(void);
extern void func_800A9C18(void *, void *, void *, s16);
extern void func_800AA36C(void *, void *, void *, void *);
extern u8 D_80158B40[];
extern u8 D_80158F6C[];
extern u8 D_8015D258[];
extern u8 D_8015D298[];


#ifdef __mips__
extern void *func_801588A4(s32, s16, s16, s16);
static const u32 bank_words[] __asm__("func_80158800")
__attribute__((section(".text.func_80158800"), aligned(4))) = {
    (u32)func_801588A4, (u32)D_80158B40, 0x8015912C, 0x80159198,
    0x8015926C, 0x801593FC, 0x80159444, 0x00000000,
    0x80159794, 0x80159794, 0x80159794, 0x801597C0,
    0x80159740, 0x80159740, 0x80159740, 0x801596D8,
    0x801596D8, 0x801597C0, 0x801597C0, 0x80159784,
    0x8015AF08, 0x8015AF00, 0x8015AEF8, 0x8015AF10,
    0x8015AEB8, 0x8015AEB0, 0x8015AEA8, 0x01000340,
    0x00800040, 0x8C824081, 0x84828582, 0x81824081,
    0x8D824081, 0x92828582, 0x99829282, 0x84824081,
    0x8E828182, 0x85828382, 0x00004481, 0x01000340,
    0x00400040,
};
__asm__(".globl func_80158800\n"
        ".size func_80158800, 832");
#define BODY_NAME func_801588A4
#else
#define BODY_NAME func_80158800
#endif

void *BODY_NAME(s32 input_value, s16 part_b_value, s16 part_b_value2, s16 part_a_value)
#ifdef __mips__
__attribute__((section(".text.func_80158800")))
#endif
;

void *BODY_NAME(s32 input_value, s16 part_b_value, s16 part_b_value2, s16 part_a_value)
{
    void *work;
    void *obj;
    s32 call_id;
    ObjectNodeHeader *call_target;
    S_80FC9000_3 *part_b;
    void *part_a;
    s16 saved_arg0;
    s32 kind;
    s32 left;
    s32 right;
    s32 index;
    s32 count;
    u16 actor_value;
    s32 double_index;
    s16 values[4];
    u8 *entry;
    s16 pin_arg1;
    s16 pin_arg3;
    void *pin_part_a;
    void *pin_actor;

    work = 0;
    call_id = 0x112;
    pin_arg1 = part_b_value;
    pin_arg3 = part_a_value;
    call_target = &D_80083498;
    obj = func_8003FD64(call_id, call_target);
    saved_arg0 = (s16)input_value;
    if (obj != 0) {
        work = (u8 *)obj + 0x20;
        ((S_80FC9000_0 *)obj)->unk_10 = D_80158B40;
        ((S_80FC9000_1 *)work)->unk_13 = 0x27;
        func_8004491C(obj, func_80045340);

        pin_part_a = ((S_80FC9000_0 *)obj)->unk_08;
        ((S_80FC9000_2 *)pin_part_a)->unk_0A = pin_arg3;
        part_b = ((S_80FC9000_0 *)obj)->unk_0C;
        kind = input_value & 3;
        part_b->unk_25 = part_b_value2;
        pin_actor = work;
        part_b->unk_2C = D_8015D258;
        part_b->unk_24 = pin_arg1;
        if (kind == 1) {
            left = ((S_80FC9000_1 *)work)->unk_14 | 0x6000;
            right = ((S_80FC9000_1 *)work)->unk_1C | 0x6000;
            ((S_80FC9000_1 *)work)->unk_14 = left;
            ((S_80FC9000_1 *)work)->unk_1C = right;
        } else if (kind >= 2) {
            left = ((S_80FC9000_1 *)work)->unk_14 | 0x2000;
            right = ((S_80FC9000_1 *)work)->unk_1C | 0x2000;
            ((S_80FC9000_1 *)work)->unk_14 = left;
            ((S_80FC9000_1 *)work)->unk_1C = right;
        } else {
            if (((input_value = (s16)(input_value & ~3)) << 16) == 0) {
                if (!(((S_80FC9000_1 *)work)->unk_14 & 0x200)) {
                    if (func_800A6D30() & 1) {
                        ((S_80FC9000_1 *)work)->unk_1C |= 0x200;
                        func_800A48F0(work, 1,
                                      (func_800A6D30() & 0x3F) |
                                      0x20);
                        part_b->unk_2C = D_8015D298;
                    }
                }
            }
        }
        func_800A9C18(obj, pin_part_a, part_b, saved_arg0);
        index = 0;
        actor_value = part_b->unk_12;
        ((S_80FC9000_4 *)pin_actor)->unk_9A = 0xFF;
        ((S_80FC9000_4 *)pin_actor)->unk_9C = -1;
        ((S_80FC9000_4 *)pin_actor)->unk_8C = D_80158F6C;
        ((S_80FC9000_4 *)pin_actor)->unk_AE = actor_value;

        entry = part_b->unk_08;
        do {
            double_index = index << 1;
            if (*entry & 0x20) {
                entry += 12;
                index += 1;
            } else {
                break;
            }
        } while (1);
        count = ((CountView *)(part_b->unk_08 + (double_index + index) * 4))->count >> 6;
        values[0] = 0;
        values[1] = count;
        values[2] = 0x100;
        values[3] = 1;
        func_800673A0(values, 0, count - 1);

        values[2] = 0x10;
        values[0] = 0x30;
        values[1] -= 1;
        do {
            func_800673A0(values, values[0] - 0x30, values[1]);
            values[0] += 0x40;
        } while (values[0] < 0x100);

        func_800AA36C(pin_actor, pin_part_a, part_b, work);
    }
    return work;
}
