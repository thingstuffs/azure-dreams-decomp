#include "common.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800E3D7C.h"


typedef struct {
    u32 words[4];
} Copy16;

extern s32 func_8003DE58(void *, void *, void *, s32);
extern s32 func_8003F270(void);
extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern void func_80047784(void *, s32, s32);
extern void *func_800A05A4(void *, u8, u8, s16, s32);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern s32 func_800A94A0(void *, u8 *, s32, void *);

extern s32 D_80045340;
extern u8 D_8006DE24[];
extern void *D_800814A8;
extern s16 D_80083228;
extern s32 D_80083460;
extern s32 D_8008346C;
extern u8 D_80083498[];
extern void *D_80170850[];
extern void *D_80170868[];
extern u8 D_80171020[];
extern s32 D_80171728;
extern u8 D_80174DEC[];
extern u8 D_80174E34[];


typedef struct S_80173230_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { u16 u; s16 s; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x10];
    u16 unk_AC;
} S_80173230_0;   /* arg0 in func_80173230 */

typedef struct S_80173230_1_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80173230_1_pre;   /* the 0x14 bytes before active in func_80173230, addressed as active[-1] */

typedef struct S_80173230_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80173230_2;   /* linked in func_80173230 */



typedef struct S_80173230_5 {
    u8 pad_00[0x94];
    u16 unk_94;
    u16 unk_96;
    u8 pad_98[0x10];
    void * unk_A8;
} S_80173230_5;   /* part in func_80173230 */

typedef struct S_80173230_6 {
    u8 pad_00[0x8];
    u8 * unk_08;
    u8 * unk_0C;
    void * unk_10;
} S_80173230_6;   /* (void *)special in func_80173230 */

typedef struct S_80173230_7 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    u16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
    u8 pad_20[0xC];
    void * unk_2C;
} S_80173230_7;   /* target in func_80173230 */

typedef struct S_80173230_8 {
    u8 pad_00[0xC];
    void * unk_0C;
} S_80173230_8;   /* base in func_80173230 */

typedef struct S_80173230_9 {
    u8 pad_00[0x8];
    void * unk_08;
} S_80173230_9;   /* source in func_80173230 */

typedef struct S_80173230_10 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} S_80173230_10;   /* global in func_80173230 */

void func_80173230(void *arg0, void *arg1, void *arg2, void *arg3)
{
    static void *const state_keep[] = {
        &&state_0, &&state_1, &&state_2, &&state_3, &&state_4
    };
    static void *const kind_keep[] = {
        &&kind_1, &&kind_2, &&kind_3, &&kind_default,
        &&kind_7, &&kind_6, &&kind_5
    };
    void *held_arg0;
    void *held_arg1;
    void *held_arg2;
    void *held_arg3;
    register s32 special ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    u16 offset[4];
    register u8 *selection ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    u8 *base;
    s32 next_state;
    u8 state;
    void *active;

    held_arg0 = arg0;
    held_arg1 = arg1;
    held_arg2 = arg2;
    held_arg3 = arg3;
    special = 0;
#define arg0 held_arg0
#define arg1 held_arg1
#define arg2 held_arg2
#define arg3 held_arg3
    ASM_KEEP(held_arg0);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP(held_arg1);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP(held_arg3);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    base = (u8 *)arg0 - 0x20;
    state = ((S_80173230_0 *)arg0)->unk_9B;
    if ((u32)state >= 5) {
        goto end;
    }
    (void)state_keep;
    goto *D_80170850[state];

state_0:
    if ((*(u32 *)((u8 *)arg3 + 0x1C)) & 0x2000) {
        u32 dispatch;

        dispatch = ((*(u16 *)((u8 *)arg3 + 0x46)) & 0x3FFF) - 1;
        if (dispatch >= 7) {
            goto kind_default;
        }
        (void)kind_keep;
        goto *D_80170868[dispatch];

kind_5:
        special = 1;
        goto kind_3;
kind_6:
        special = 1;
        goto kind_2;
kind_7:
        special = 1;
        goto kind_1;
    }

    {
        s32 type;

        type = (*(u16 *)((u8 *)arg3 + 0x46)) & 0x3FFF;
        if (type == 2) {
            goto kind_2;
        }
        if (type < 3) {
            selection = 0;
            if (type == 1) {
                goto normal_kind_1;
            }
            goto selection_ready;
        }
        if (type != 3) {
            selection = 0;
            goto selection_ready;
        }
    }

kind_3:
    selection = (u8 *)arg3 + 0xE;
    goto selection_ready;
kind_2:
    selection = (u8 *)arg3 + 0xB;
    goto selection_ready;
normal_kind_1:
kind_1:
    selection = (u8 *)arg3 + 8;
    goto selection_ready;
kind_default:
    selection = 0;

selection_ready:
    if (*selection == 0) {
        goto empty_selection;
    }
    ((S_80173230_0 *)arg0)->unk_98 &= 0xFF7F;
    ASM_KEEP(selection);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    {
        s32 special_test;

        special_test = special;
        ASM_KEEP(special_test);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
        if (special_test != 0) {
            active = D_800814A8;
            (*(void * *)((u8 *)arg3 + 0x60)) = active;
            goto copy_active_coords;
        }
    }

    {
        u8 item;
        u8 *items;

        item = *selection;
        items = D_8006DE24;
        if (items[item * 20 + 0x12] == 2) {
            active = (*(void * *)((u8 *)arg3 + 0x60));
            if (active != 0) {
                register u8 *linked ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

copy_active_coords:
                linked = ((S_80173230_1_pre *)active)[-1].unk_00;
                (*(u8 *)((u8 *)arg3 + 0x72)) = ((S_80173230_2 *)linked)->unk_24;
                (*(u8 *)((u8 *)arg3 + 0x73)) = ((S_80173230_2 *)linked)->unk_25;
                goto invoke_item;
            }
        } else {
            s32 dx;
            s32 dy;

            active = func_800A05A4(
                arg3, ((Rec_D_80082E80 *)arg2)->unk_24, ((Rec_D_80082E80 *)arg2)->unk_25,
                (*(s16 *)((u8 *)arg3 + 0x2A)), 0x10);
            (*(void * volatile *)((u8 *)arg3 + 0x60)) = active;
            ASM_KEEP(active);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
            dx = (*(s8 *)((u8 *)arg3 + 0x72));
            dy = (*(s8 *)((u8 *)arg3 + 0x73));
            if (dx < 0) {
                dx = -dx;
            }
            if (dy < 0) {
                dy = -dy;
            }
            (*(u8 *)((u8 *)arg3 + 0x72)) = dx;
            (*(u8 *)((u8 *)arg3 + 0x73)) = dy;
        }
    }

invoke_item:
    if (func_800A94A0(arg3, selection, special, (u8 *)arg0 + 0x98) == 0) {
        return;
    }
    ((S_80173230_0 *)arg0)->unk_96.u = 0x11;
    ((S_80173230_0 *)arg0)->unk_9B++;
    return;

empty_selection:
    ((Rec_D_800E3D7C *)arg1)->unk_14.as_s32 = 0;
    ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v = 0;
    ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 = 0;
    func_800A2B04(arg1, ((Rec_D_80082E80 *)arg2)->unk_24, ((Rec_D_80082E80 *)arg2)->unk_25);
    D_8008346C = 0;
    (*(u16 *)((u8 *)D_800814A8 + 0xA6))--;
    func_800A4ACC(arg3);
    (*(u8 *)((u8 *)arg3 + 0x6D))--;
    ((S_80173230_0 *)arg0)->unk_8C = &D_80171728;
    (*(u8 *)((u8 *)arg3 + 0x73)) = 0;
    (*(u8 *)((u8 *)arg3 + 0x72)) = 0;
    (*(u16 *)((u8 *)arg3 + 0x46)) &= 0x7FFF;
    goto end;

state_1:
    if (func_8003F270()) {
        ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v |= 0x800;
        goto end;
    }
    ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v &= 0xF7FF;
    ((S_80173230_0 *)arg0)->unk_9B++;
    func_800A56E0(0x703);

state_2:
    {
        s16 timer;

        timer = ((S_80173230_0 *)arg0)->unk_96.u - 1;
        ((S_80173230_0 *)arg0)->unk_96.u = timer;
        if (timer == 0xB || (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0xE000)) {
            special = (s32)func_8003FD64(0x112, D_80083498);
            if (special != 0) {
                u8 *part;
                u8 *target;
                u32 *copy_src;
                u32 *copy_dst;
                u32 *copy_end;
                void *source;
                u8 animation;

                part = (u8 *)special + 0x20;
                ((S_80173230_5 *)part)->unk_96 = 9;
                ((S_80173230_6 *)((void *)special))->unk_10 = D_80171020;
                ((S_80173230_5 *)part)->unk_A8 = arg1;
                copy_src = (u32 *)arg2;
                ((S_80173230_5 *)part)->unk_94 = (*(u16 *)((u8 *)arg3 + 0x2A));
                target = ((S_80173230_6 *)((void *)special))->unk_0C;
                ASM_KEEP(arg2);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                copy_end = (u32 *)arg2 + 12;
                copy_dst = (u32 *)target;
                do {
                    *(Copy16 *)copy_dst = *(Copy16 *)copy_src;
                    copy_src += 4;
                    copy_dst += 4;
                } while (copy_src != copy_end);
                ((S_80173230_7 *)target)->unk_1E = 0x1000;
                ((S_80173230_7 *)target)->unk_1C = 0x1000;
                ((S_80173230_7 *)target)->unk_0E = 0x80;
                ((S_80173230_7 *)target)->unk_0D = 0x80;
                ((S_80173230_7 *)target)->unk_0C = 0x80;
                func_8004491C((void *)special, &D_80045340);
                animation = D_80174E34[0];
                ((S_80173230_7 *)target)->unk_2C = D_80174E34;
                func_80047784(target, animation, 0);
                ((S_80173230_7 *)target)->unk_10 = 0x20;
                ((S_80173230_7 *)target)->unk_12 = 0xFF80;
                ((S_80173230_7 *)target)->unk_14 |= 0x0C;

                source = ((S_80173230_8 *)base)->unk_0C;
                target = ((S_80173230_6 *)((void *)special))->unk_08;
                if (func_8003DE58(
                        ((S_80173230_9 *)source)->unk_08, source, offset, 1) != 0) {
                    ((S_80173230_7 *)target)->unk_02 = ((Rec_D_800E3D7C *)arg1)->unk_00.at02_u16.v;
                    ((S_80173230_7 *)target)->unk_06 = ((Rec_D_800E3D7C *)arg1)->unk_04.at02_u16.v;
                    ((S_80173230_7 *)target)->unk_0A = ((Rec_D_800E3D7C *)arg1)->unk_08.at02_u16.v;
                    ((S_80173230_7 *)target)->unk_02 += offset[0];
                    ((S_80173230_7 *)target)->unk_06 += offset[1];
                    ((S_80173230_7 *)target)->unk_0A += offset[2];
                }
            }
        }

        if (((S_80173230_0 *)arg0)->unk_96.s == 0xB ||
            (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0xE000)) {
            ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v |= 0x800;
        }
        if (((S_80173230_0 *)arg0)->unk_96.s == 0 ||
            (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0xE000)) {
            ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v &= 0xF7FF;
        }
        if (((S_80173230_0 *)arg0)->unk_96.s <= 0 ||
            (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0xE000)) {
            next_state = ((S_80173230_0 *)arg0)->unk_9B + 1;
            goto store_next_state;
        }
    }
    goto end;

store_next_state:
    ((S_80173230_0 *)arg0)->unk_9B = next_state;
    goto end;

state_3:
    if ((((Rec_D_80082E80 *)arg2)->unk_04.as_s8 == 3 &&
         (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0x1000)) ||
        (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0x8000)) {
        ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v |= 0x800;
        ((S_80173230_0 *)arg0)->unk_96.u = 0x14;
        ((S_80173230_0 *)arg0)->unk_98 |= 0x80;
        ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v |= 0x100;
        ((S_80173230_0 *)arg0)->unk_AC = ((Rec_D_80082E80 *)arg2)->unk_12.at00_u16.v;
        ((Rec_D_80082E80 *)arg2)->unk_12.at00_u16.v = 0x7E80;
        ((S_80173230_0 *)arg0)->unk_9B++;
    }

state_4:
    {
        u8 *global;
        s16 timer;

        global = (u8 *)&D_80083460;
        if (((S_80173230_10 *)global)->unk_0C == 0) {
            ((S_80173230_0 *)arg0)->unk_96.u = 0;
        }
        timer = ((S_80173230_0 *)arg0)->unk_96.u - 1;
        ((S_80173230_0 *)arg0)->unk_96.u = timer;
        if (timer <= 0) {
            ((S_80173230_0 *)arg0)->unk_96.u = 0;
            ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v &= 0xF7FF;
        }
        if (((S_80173230_0 *)arg0)->unk_96.s == 0x12) {
            ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v &= 0xFEFF;
            ((Rec_D_80082E80 *)arg2)->unk_12.at00_u16.v = ((S_80173230_0 *)arg0)->unk_AC;
        }
        if (!(((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0xE000)) {
            goto end;
        }

        ((Rec_D_800E3D7C *)arg1)->unk_14.as_s32 = 0;
        ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v = 0;
        ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 = 0;
        func_800A2B04(arg1, ((Rec_D_80082E80 *)arg2)->unk_24, ((Rec_D_80082E80 *)arg2)->unk_25);
        ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v &= 0xFEFF;
        ((Rec_D_80082E80 *)arg2)->unk_12.at00_u16.v = ((S_80173230_0 *)arg0)->unk_AC;

        if (((Rec_D_80082E80 *)arg2)->unk_2C.as_pu8 != D_80174DEC) {
            u8 *table;
            s32 index;

            table = D_80174DEC;
            (*(u8 * *)((u8 *)arg2 + 0x2C)) = table;
            index = ((D_80083228 + (*(s16 *)((u8 *)arg3 + 0x2A)) + 0x100) >> 9) & 7;
            func_80047784(arg2, table[index], 0);
            ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v &= 0xF7FF;
        }
        if (((S_80173230_10 *)global)->unk_0C != 0) {
            goto end;
        }
        ((S_80173230_10 *)global)->unk_0A--;
        ((S_80173230_0 *)arg0)->unk_8C = &D_80171728;
        func_800A4ACC(arg3);
        (*(u8 *)((u8 *)arg3 + 0x73)) = 0;
        (*(u8 *)((u8 *)arg3 + 0x72)) = 0;
        (*(u8 *)((u8 *)arg3 + 0x6D))--;
        (*(u16 *)((u8 *)arg3 + 0x46)) &= 0x7FFF;
        func_800A56E0(0xB4);
    }

end:
    return;
}
