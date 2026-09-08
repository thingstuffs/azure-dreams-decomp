#include "common.h"

typedef void (*retfn)(void);

typedef struct S_80FB7000_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80FB7000_0;   /* obj in BODY_NAME */

typedef struct S_80FB7000_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_80FB7000_1;   /* work in BODY_NAME */

typedef struct S_80FB7000_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80FB7000_2;   /* pin_part_a in BODY_NAME */

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
} S_80FB7000_3;   /* part_b in BODY_NAME */

typedef struct S_80FB7000_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
    u8 pad_9D[0x11];
    u16 unk_AE;
} S_80FB7000_4;   /* pin_actor in BODY_NAME */


extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern s32 func_800A6D30();
extern void func_800A48F0(void *, s32, s32);
extern void func_800A9C18(void *, void *, void *, s16);
extern void func_800AA36C(void *, void *, void *, void *);
extern void func_800673A0(s16 *, s32, s32);
extern void func_8016A984(void) __attribute__((noreturn));
extern void func_8016A9FC(void) __attribute__((noreturn));
extern void func_8016AA40(void);

extern u8 D_80045340[];
extern u8 D_80083498[];
extern u8 D_8016AB40[];
extern u8 D_8016AF6C[];
extern u8 D_8016F258[];
extern u8 D_8016F298[];

#ifdef __mips__
static const u32 bank_words[41] __asm__("func_80FB7000")
    __attribute__((section(".text.func_80FB7000"), aligned(4))) = {
    0x8016A8A4, (u32)D_8016AB40,
    0x8016B12C, 0x8016B198, 0x8016B26C, 0x8016B3FC,
    0x8016B444, 0x00000000,
    0x8016B794, 0x8016B794, 0x8016B794, 0x8016B7C0,
    0x8016B740, 0x8016B740, 0x8016B740, 0x8016B6D8,
    0x8016B6D8, 0x8016B7C0, 0x8016B7C0, 0x8016B784,
    0x8016CF08, 0x8016CF00, 0x8016CEF8, 0x8016CF10,
    0x8016CEB8, 0x8016CEB0, 0x8016CEA8,
    0x01000340, 0x00800040, 0x8C824081, 0x84828582,
    0x81824081, 0x8D824081, 0x92828582, 0x99829282,
    0x84824081, 0x8E828182, 0x85828382, 0x00004481,
    0x01000340, 0x00400040,
};
__asm__(".globl func_80FB7000\n"
        ".size func_80FB7000, 832");
#define BODY_NAME func_80FB70A4
#else
#define BODY_NAME func_80FB7000
#endif

void *BODY_NAME(s32 spawn_flags, s8 pos_x, s8 pos_y, s16 part_a_value)
#ifdef __mips__
    __attribute__((section(".text.func_80FB7000")))
#endif
    ;

/* Creates a dungeon actor and initializes its parts, flags, and image regions. */
void *BODY_NAME(s32 spawn_flags, s8 pos_x, s8 pos_y, s16 part_a_value)
{
    register void *work ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    void *obj;
    register s32 object_type ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    register void *object_pool ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    S_80FB7000_3 *part_b;
    void *part_a;
    s16 saved_flags;
    s32 kind;
    s32 primary_flags;
    s32 secondary_flags;
    register s32 entry_index ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    s32 entry_count;
    u16 actor_value;
    register s32 twice_index ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 entry_offset ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    u8 *selected_entry;
    s16 *rect_ptr;
    s16 rect[4];
    u8 *entry;
    register s8 saved_x ASM_REG("$21");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s16 saved_part_value;
    void *pin_part_a;
    register void *pin_actor ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

    work = 0;
    object_type = 0x112;
    ASM_USE_NV(object_type);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    saved_x = pos_x;
    saved_part_value = part_a_value;
    object_pool = D_80083498;
    ASM_USE2_NV(saved_part_value, object_pool);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    obj = func_8003FD64(object_type, object_pool);
    saved_flags = (s16)spawn_flags;
    if (obj != 0) {
        work = (u8 *)obj + 0x20;
        ((S_80FB7000_0 *)obj)->unk_10 = D_8016AB40;
        ((S_80FB7000_1 *)work)->unk_13 = 0x27;
        func_8004491C(obj, &D_80045340);

        pin_part_a = ((S_80FB7000_0 *)obj)->unk_08;
        ((S_80FB7000_2 *)pin_part_a)->unk_0A = saved_part_value;
        part_b = ((S_80FB7000_0 *)obj)->unk_0C;
        kind = spawn_flags & 3;
        part_b->unk_25 = pos_y;
        pin_actor = work;
        part_b->unk_2C = D_8016F258;
        part_b->unk_24 = saved_x;

        if (kind == 1) {
            primary_flags = ((S_80FB7000_1 *)work)->unk_14 | 0x6000;
            secondary_flags = ((S_80FB7000_1 *)work)->unk_1C | 0x6000;
            ASM_KEEP(primary_flags);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            ASM_TAILSLOT_PIN(secondary_flags);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            func_8016A984();
        }
        if (kind < 2) {
            goto normal_kind;
        }
        primary_flags = ((S_80FB7000_1 *)work)->unk_14 | 0x2000;
        secondary_flags = ((S_80FB7000_1 *)work)->unk_1C | 0x2000;

write_kind:
        ((S_80FB7000_1 *)work)->unk_14 = primary_flags;
        ((S_80FB7000_1 *)work)->unk_1C = secondary_flags;
        func_8016A9FC();

normal_kind:
        {
            s32 non_kind_mask;
            non_kind_mask = -4;
            if (((spawn_flags & non_kind_mask) << 16) != 0) {
                goto normal_kind_nonzero;
            }
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

normal_kind_nonzero:

post_kind:
        func_800A9C18(obj, pin_part_a, part_b, saved_flags);

        entry_index = 0;
        ASM_USE_NV(entry_index);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        actor_value = part_b->unk_12;
        ((S_80FB7000_4 *)pin_actor)->unk_9A = 0xFF;
        ((S_80FB7000_4 *)pin_actor)->unk_9C = -1;
        ((S_80FB7000_4 *)pin_actor)->unk_8C = D_8016AF6C;
        ((S_80FB7000_4 *)pin_actor)->unk_AE = actor_value;

        entry = part_b->unk_08;
    scan_entries:
        ASM_CLOBBER("$5");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
        twice_index = entry_index << 1;
        if (!(*entry & 0x20)) {
            goto scan_done;
        }
        entry += 12;
        entry_index += 1;
        ASM_KEEP(entry);   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
        ASM_TAILSLOT_PIN(entry_index);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
        func_8016AA40();
scan_done:

        rect_ptr = rect;
        ASM_KEEP(rect_ptr);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        entry_offset = twice_index + entry_index;
        entry_offset <<= 2;
        selected_entry =
            (u8 *)(entry_offset + (s32)part_b->unk_08);
        entry_count = (*(u16 *)(selected_entry + 6)) >> 6;
        rect[2] = 0x100;
        rect[0] = 0;
        rect[3] = 1;
        rect[1] = entry_count;
        func_800673A0(rect_ptr, 0, entry_count - 1);

        rect[2] = 0x10;
        rect[0] = 0x30;
        rect[1] -= 1;
        do {
            func_800673A0(rect, rect[0] - 0x30, rect[1]);
            rect[0] += 0x40;
        } while (rect[0] < 0x100);

        func_800AA36C(pin_actor, pin_part_a, part_b, work);
    }
    return work;
}

extern void func_8016A9FC(void) __attribute__((noreturn));
#if 0
extern void func_8016AA40(void) __attribute__((noreturn));
#endif
