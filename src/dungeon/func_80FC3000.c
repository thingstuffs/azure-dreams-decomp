/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"

typedef struct S_8015E8A4_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_8015E8A4_0;   /* obj in func_8015E8A4 */

typedef struct S_8015E8A4_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_8015E8A4_1;   /* work in func_8015E8A4 */

typedef struct S_8015E8A4_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_8015E8A4_2;   /* pin_part_a in func_8015E8A4 */

typedef struct S_8015E8A4_3 {
    u8 pad_00[0x8];
    u8 * unk_08;
    u8 pad_0C[0x6];
    u16 unk_12;
    u8 pad_14[0x10];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} S_8015E8A4_3;   /* part_b in func_8015E8A4 */

typedef struct S_8015E8A4_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
    u8 pad_9D[0x11];
    u16 unk_AE;
} S_8015E8A4_4;   /* pin_actor in func_8015E8A4 */


extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern void func_800673A0(s16 *, s32, s32);
extern void func_800A48F0(void *, s32, s32);
extern s32 func_800A6D30();
extern void func_800A9C18(void *, void *, void *, s16);
extern void func_800AA36C(void *, void *, void *, void *);
extern u8 D_8015EB40[];
extern u8 D_8015EF6C[];
extern u8 D_80163258[];
extern u8 D_80163298[];


extern void *func_8015E8A4(s16, s16, s16, s16);
static const u32 bank_words[] __asm__("func_8015E800")
__attribute__((section(".text.func_8015E800"), aligned(4))) = {
    (u32)func_8015E8A4, (u32)D_8015EB40, 0x8015F12C, 0x8015F198,
    0x8015F26C, 0x8015F3FC, 0x8015F444, 0x00000000,
    0x8015F794, 0x8015F794, 0x8015F794, 0x8015F7C0,
    0x8015F740, 0x8015F740, 0x8015F740, 0x8015F6D8,
    0x8015F6D8, 0x8015F7C0, 0x8015F7C0, 0x8015F784,
    0x80160F08, 0x80160F00, 0x80160EF8, 0x80160F10,
    0x80160EB8, 0x80160EB0, 0x80160EA8, 0x01000340,
    0x00800040, 0x8C824081, 0x84828582, 0x81824081,
    0x8D824081, 0x92828582, 0x99829282, 0x84824081,
    0x8E828182, 0x85828382, 0x00004481, 0x01000340,
    0x00400040,
};
__asm__(".globl func_8015E800\n"
        ".size func_8015E800, 832");

void *func_8015E8A4(s16 flags, s16 kind_id, s16 variant, s16 spawn_value)
__attribute__((section(".text.func_8015E800")));

typedef void (*Callback)(void);
typedef struct { s16 x, y, w, h; } Rect;

typedef struct S_80FB1000_0 {
    u8 pad_00[0x13];
    u8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_80FB1000_0;   

typedef struct S_80FB1000_1 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80FB1000_1;   

typedef struct S_80FB1000_2 {
    u8 pad_00[0x6];
    u16 unk_06;
} S_80FB1000_2;   

void *func_8015E8A4(s16 arg0, s16 arg1, s16 arg2, s16 arg3)
{
    s16 arg0_copy;
    s16 arg1_role;
    s8 arg2_role;
    s16 arg3_role;
    void *created;
    u8 *work = 0;
    u8 *position;
    u8 *monster;
    u8 *actor;
    s32 kind;
    Rect rect;

    arg1_role = arg1;
    arg3_role = arg3;
    arg2_role = arg2;
    arg1 = 0x112;
    created = func_8003FD64(arg1, ((u8 *)(&D_80083498)));
    arg0_copy = (s32)arg0;
    if (created != 0) {
        void *init_arg0;
        s32 flags0;
        s32 flags1;
        s32 value;
        u8 *entry;
        s32 i;
        s32 scale;

        work = (u8 *)created + 0x20;
        (*(Callback *)((u8 *)created + 0x10)) = D_8015EB40;
        ((S_80FB1000_0 *)work)->unk_13 = 0x27;
        func_8004491C(created, func_80045340);

        position = (*(u8 * *)((u8 *)created + 8));
        ((S_80FB1000_1 *)position)->unk_0A = arg3_role;
        monster = (*(u8 * *)((u8 *)created + 0xC));
        (*(u8 *)((u8 *)monster + 0x25)) = arg2_role;
        actor = work;
        (*(Callback *)((u8 *)monster + 0x2C)) = D_80163258;
        (*(u8 *)((u8 *)monster + 0x24)) = arg1_role;

        kind = (s32)arg0 & 3;
        if (kind == 1) {
            flags0 = ((S_80FB1000_0 *)work)->unk_14 | 0x6000;
            flags1 = ((S_80FB1000_0 *)work)->unk_1C | 0x6000;
        } else {
            if (kind < 2) {
                goto special;
            }
            flags0 = ((S_80FB1000_0 *)work)->unk_14 | 0x2000;
            flags1 = ((S_80FB1000_0 *)work)->unk_1C | 0x2000;
        }
        ((S_80FB1000_0 *)work)->unk_14 = flags0;
        ((S_80FB1000_0 *)work)->unk_1C = flags1;
        goto initialize;

special:
        {
            if ((s16)((s32)arg0 & -4) == 0 &&
                !(((S_80FB1000_0 *)work)->unk_14 & 0x200)) {
                value = func_800A6D30();
                init_arg0 = created;
                if (!(value & 1)) {
                    goto initialize_after_a0;
                }
                ((S_80FB1000_0 *)work)->unk_1C |= 0x200;
                value = func_800A6D30();
                func_800A48F0(work, 1, (value & 0x3F) | 0x20);
                (*(Callback *)((u8 *)monster + 0x2C)) = D_80163298;
            }
        }

initialize:
        init_arg0 = created;
initialize_after_a0:
        func_800A9C18(init_arg0, position, monster, (s16)arg0_copy);
        i = 0;
        value = (*(u16 *)((u8 *)monster + 0x12));
        (*(u8 *)((u8 *)actor + 0x9A)) = 0xFF;
        (*(s8 *)((u8 *)actor + 0x9C)) = -1;
        (*(Callback *)((u8 *)actor + 0x8C)) = D_8015EF6C;
        (*(s16 *)((u8 *)actor + 0xAE)) = value;

        entry = (*(u8 * *)((u8 *)monster + 8));
loop_test:
        scale = i << 1;
        if (entry[0] & 0x20) {
            entry += 12;
            i++;
            goto loop_test;
        }
        value = ((S_80FB1000_2 *)((*(u8 * *)((u8 *)monster + 8)) + (scale + i) * 4))->unk_06 >> 6;
        rect.x = 0;
        rect.y = value;
        rect.w = 0x100;
        rect.h = 1;
        func_800673A0(&rect, 0, value - 1);

        rect.w = 0x10;
        rect.x = 0x30;
        rect.y--;
        do {
            func_800673A0(&rect, rect.x - 0x30, rect.y);
            rect.x += 0x40;
        } while (rect.x < 0x100);

        func_800AA36C(actor, position, monster, work);
    }
    return work;
}
