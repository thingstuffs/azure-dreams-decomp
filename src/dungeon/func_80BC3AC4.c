#include "common.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800E3D7C.h"


typedef struct {
    u32 words[3];
} __attribute__((packed)) Packet12;

extern s32 func_8003F270(void);
extern void *func_8003FC64(s32);
extern void func_8004491C(void *, void *);
extern void func_80047784(void *, s32, s32);
extern s32 func_80069EF8(void);
extern void *func_800A05A4(void *, u8, u8, s16, s32);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern s32 func_800A94A0(void *, u8 *, s32, void *);
extern void func_80170D28(void *, s32, s32, s32, s32, s32, s32);
extern void func_80170F2C(void *, s32, s32, s32, s32, s32, s32);

extern s32 D_80045340;
extern u8 D_8006DE24[];
extern void *D_800814A8;
extern s16 D_80083228;
extern s32 D_80083460;
extern s32 D_8008346C;
extern void *D_80170850[];
extern void *D_80170868[];
extern u8 D_80171080[];
extern s32 D_801719DC;
extern u8 D_80174634[];
extern Packet12 D_80174694;


typedef struct S_801732C4_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { u16 u; s16 s; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x8];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_A4;   /* overlapping accesses */
    s32 unk_A8;
    s32 unk_AC;
    s32 unk_B0;
    u8 pad_B4[0x4];
    u16 unk_B8;
} S_801732C4_0;   /* arg0 in func_801732C4 */

typedef struct S_801732C4_1_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_801732C4_1_pre;   /* the 0x14 bytes before active in func_801732C4, addressed as active[-1] */

typedef struct S_801732C4_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_801732C4_2;   /* linked in func_801732C4 */



typedef struct S_801732C4_5 {
    u8 pad_00[0x2];
    u8 unk_02;
    u8 unk_03;
    u8 unk_04;
    u8 pad_05[0x15];
    s16 unk_1A;
    s16 unk_1C;
} S_801732C4_5;   /* object_base in func_801732C4 */

typedef struct S_801732C4_6 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_801732C4_6;   /* transform in func_801732C4 */

typedef struct S_801732C4_7 {
    u8 pad_00[0x6];
    s16 unk_06;
    void * unk_08;
    s32 unk_0C;
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_801732C4_7;   /* display in func_801732C4 */

typedef struct S_801732C4_8 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} S_801732C4_8;   /* global in func_801732C4 */

void func_801732C4(void *arg0, void *arg1, void *arg2, void *arg3)
{
    static void *const state_keep[] = {
        &&state_0, &&state_1, &&state_2, &&state_3, &&state_4, &&state_5
    };
    static void *const kind_keep[] = {
        &&kind_1, &&kind_2, &&kind_3, &&kind_default,
        &&kind_7, &&kind_6, &&kind_5
    };
    register u8 *selection ASM_REG("$17");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register s32 special ASM_REG("$19");   /* MATCH pin: keeps a constant in a register as retail does */
    u8 state;
    u8 next_state;
    void *active;

    special = 0;
    state = ((S_801732C4_0 *)arg0)->unk_9B;
    if ((u32)state >= 6) {
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
    ((S_801732C4_0 *)arg0)->unk_98 &= 0xFF7F;
    ASM_KEEP(selection);   /* MATCH pin: retail delay-slot fill depends on it */
    {
        s32 special_test;

        special_test = special;
        ASM_KEEP(special_test);   /* MATCH pin: retail delay-slot fill depends on it */
        if (special_test != 0) {
            active = D_800814A8;
            (*(void * *)((u8 *)arg3 + 0x60)) = active;
            goto copy_active_coords;
        }
    }

    {
        u8 item;
        u8 *item_table;

        item_table = D_8006DE24;
        item = *selection;
        if (item_table[item * 20 + 0x12] == 2) {
            active = (*(void * *)((u8 *)arg3 + 0x60));
            if (active != 0) {
                register u8 *linked ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */

copy_active_coords:
                linked = ((S_801732C4_1_pre *)active)[-1].unk_00;
                (*(u8 *)((u8 *)arg3 + 0x72)) = ((S_801732C4_2 *)linked)->unk_24;
                (*(u8 *)((u8 *)arg3 + 0x73)) = ((S_801732C4_2 *)linked)->unk_25;
                goto invoke_item;
            }
        } else {
            s32 dx;
            s32 dy;

            active = func_800A05A4(
                arg3, ((Rec_D_80082E80 *)arg2)->unk_24, ((Rec_D_80082E80 *)arg2)->unk_25,
                (*(s16 *)((u8 *)arg3 + 0x2A)), 0x10);
            (*(void * volatile *)((u8 *)arg3 + 0x60)) = active;
            ASM_KEEP(active);   /* MATCH pin: keeps a statement from moving across a call/branch */
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
        goto end;
    }
    goto increment_state;

empty_selection:
    ((Rec_D_800E3D7C *)arg1)->unk_14.as_s32 = 0;
    ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v = 0;
    ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 = 0;
    func_800A2B04(arg1, ((Rec_D_80082E80 *)arg2)->unk_24, ((Rec_D_80082E80 *)arg2)->unk_25);
    D_8008346C = 0;
    (*(u16 *)((u8 *)D_800814A8 + 0xA6))--;
    func_800A4ACC(arg3);
    (*(u8 *)((u8 *)arg3 + 0x6D))--;
    ((S_801732C4_0 *)arg0)->unk_8C = &D_801719DC;
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
    ((S_801732C4_0 *)arg0)->unk_9B++;
    func_800A56E0(0x703);

state_2:
    {
        u16 flags;
        s16 timer;

        flags = ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v;
        if (flags & 0x8000) {
            next_state = ((S_801732C4_0 *)arg0)->unk_9B;
            ((S_801732C4_0 *)arg0)->unk_96.u = 0;
            goto increment_state_loaded;
        }
        if (((Rec_D_80082E80 *)arg2)->unk_04.as_s8 == 2 && (flags & 0x1000)) {
            ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v = flags | 0x800;
            ((S_801732C4_0 *)arg0)->unk_96.u = 0x16;
        }
        if (((Rec_D_80082E80 *)arg2)->unk_04.as_s8 < 2) {
            goto end;
        }
        timer = ((S_801732C4_0 *)arg0)->unk_96.u - 1;
        ((S_801732C4_0 *)arg0)->unk_96.u = timer;
        if (timer <= 0) {
            ((S_801732C4_0 *)arg0)->unk_96.u = 0;
            ((S_801732C4_0 *)arg0)->unk_9B++;
            ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v &= 0xF7FF;
        }
        if (((S_801732C4_0 *)arg0)->unk_96.s < 7) {
            goto particle_done;
        }
    }

    special = 0;
state_2_particles:
    {
        s32 color;
        register s32 x ASM_REG("$17");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
        register s32 y ASM_REG("$16");   /* MATCH pin: load-bearing for the whole function shape */
        s16 z;

        special++;
        color = (func_80069EF8() & 0xFF) | 0x80;
        x = func_80069EF8();
        x &= 0x7F;
        x -= 0x40;
        x = (s16)x;
        y = func_80069EF8();
        y &= 0x7F;
        y -= 0x40;
        y = (s16)y;
        z = (func_80069EF8() & 0x7F) - 0x40;
        func_80170D28((u8 *)arg0 - 0x20, 0, 0x00C0C0C0,
                      color, x, y, z);
        if ((u16)special < 5) {
            goto state_2_particles;
        }
    }

particle_done:
    {
        void *object;
        u8 *object_base;
        void *transform;
        void *display;
        u16 timer;
        u16 flags;

        timer = ((S_801732C4_0 *)arg0)->unk_96.u;
        if (!(timer & 1) || (s16)timer < 0x13) {
            goto end;
        }
        object = func_8003FC64(0x212);
        if (object == 0) {
            goto end;
        }
        object_base = (u8 *)object + 0x20;
        ((S_801732C4_5 *)object_base)->unk_1A = 0x19;
        ((S_801732C4_5 *)object_base)->unk_1C = 0x19;
        (*(void * *)((u8 *)object + 0x10)) = D_80171080;
        func_8004491C(object, &D_80045340);
        transform = (*(void * *)((u8 *)object + 8));
        ((S_801732C4_6 *)transform)->unk_02 = ((Rec_D_800E3D7C *)arg1)->unk_00.at02_u16.v;
        ((S_801732C4_6 *)transform)->unk_06 = ((Rec_D_800E3D7C *)arg1)->unk_04.at02_u16.v;
        ((S_801732C4_6 *)transform)->unk_0A = ((Rec_D_800E3D7C *)arg1)->unk_08.at02_u16.v - 0x60;
        display = (*(void * *)((u8 *)object + 0xC));
        (*(Packet12 *)((u8 *)object + 0x48)) = D_80174694;
        ((S_801732C4_7 *)display)->unk_08 = (u8 *)object + 0x48;
        ((S_801732C4_7 *)display)->unk_10 = 0x40;
        ((S_801732C4_7 *)display)->unk_1E = 0x32C8;
        ((S_801732C4_7 *)display)->unk_1C = 0x32C8;
        ((S_801732C4_7 *)display)->unk_06 = 0x64;
        ((S_801732C4_7 *)display)->unk_0C = 0;
        flags = ((S_801732C4_7 *)display)->unk_14;
        ((S_801732C4_7 *)display)->unk_14 = flags | 0xC;
        ((S_801732C4_5 *)object_base)->unk_04 = 0x80;
        ((S_801732C4_5 *)object_base)->unk_03 = 0x80;
        ((S_801732C4_5 *)object_base)->unk_02 = 0x80;
    }
    goto end;

state_3:
    if ((((Rec_D_80082E80 *)arg2)->unk_04.as_s8 == 5 &&
         (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0x1000)) ||
        (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0xE000)) {
        ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v |= 0x800;
        ((S_801732C4_0 *)arg0)->unk_96.u = 0x14;
        ((S_801732C4_0 *)arg0)->unk_98 |= 0x80;
        ((S_801732C4_0 *)arg0)->unk_9B++;
        special = 0;
state_3_particles:
        {
            s32 color;

            special++;
            color = (func_80069EF8() & 0xFF) | 0x80;
            func_80170F2C((u8 *)arg0 - 0x20, 0, 0x00C0C0C0,
                          color, 0, 0, 0);
        }
        if ((u16)special >= 20) {
            goto end;
        }
        goto state_3_particles;
    }
    goto end;

state_4:
    {
        s16 timer;

        if (D_8008346C == 0) {
            ((S_801732C4_0 *)arg0)->unk_96.u = 0;
        }
        timer = ((S_801732C4_0 *)arg0)->unk_96.u - 1;
        ((S_801732C4_0 *)arg0)->unk_96.u = timer;
        if (timer > 0 && !(((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0xE000)) {
            goto end;
        }
        ((S_801732C4_0 *)arg0)->unk_96.u = 0;
        ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v &= 0xF7FF;
increment_state:
        next_state = ((S_801732C4_0 *)arg0)->unk_9B;
increment_state_loaded:
        next_state++;
        ((S_801732C4_0 *)arg0)->unk_9B = next_state;
        goto end;
    }

state_5:
    if (!(((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0xE000)) {
        goto end;
    }
    ((Rec_D_800E3D7C *)arg1)->unk_14.as_s32 = 0;
    ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v = 0;
    ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 = 0;
    func_800A2B04(arg1, ((Rec_D_80082E80 *)arg2)->unk_24, ((Rec_D_80082E80 *)arg2)->unk_25);
    if (((Rec_D_80082E80 *)arg2)->unk_2C.as_pu8 != D_80174634) {
        u8 *table;
        s32 index;
        s32 prior_a4;

        table = D_80174634;
        (*(u8 * *)((u8 *)arg2 + 0x2C)) = table;
        index = ((D_80083228 + (*(s16 *)((u8 *)arg3 + 0x2A)) + 0x100) >> 9) & 7;
        func_80047784(arg2, table[index], 2);
        ((Rec_D_80082E80 *)arg2)->unk_05.as_u8 = 1;
        prior_a4 = ((S_801732C4_0 *)arg0)->unk_A4.at00.v;
        ((S_801732C4_0 *)arg0)->unk_A4.at02.v = 0;
        ((S_801732C4_0 *)arg0)->unk_B8 = 0;
        ((S_801732C4_0 *)arg0)->unk_AC = 0;
        ((S_801732C4_0 *)arg0)->unk_B0 = 0;
        ((S_801732C4_0 *)arg0)->unk_A8 = prior_a4;
    }
    {
        u8 *global;

        global = (u8 *)&D_80083460;
        if (((S_801732C4_8 *)global)->unk_0C != 0) {
            goto end;
        }
        ((S_801732C4_8 *)global)->unk_0A--;
        ((S_801732C4_0 *)arg0)->unk_8C = &D_801719DC;
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
