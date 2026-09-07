#include "common.h"


typedef void (*Callback)(void);

typedef struct {
    Callback callbacks[27];
    u8 config[56];
} ActorDefinition;

typedef struct {
    s16 x;
    s16 y;
    s16 w;
    s16 h;
} Rect;

extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern s32 func_800A6D30();
extern void func_800A48F0(void *, s32, s32);
extern void func_800A9C18(void *, void *, void *, s32);
extern void func_800673A0(Rect *, s32, s32);
extern void func_800AA36C(void *, void *, void *, void *);

extern void func_80045340(void);
extern void func_80170B40(void);
extern void func_8017112C(void);
extern void func_80171198(void);
extern void func_8017126C(void);
extern void func_801713FC(void);
extern void func_80171444(void);
extern void func_801716D8(void);
extern void func_80171740(void);
extern void func_80171784(void);
extern void func_80171794(void);
extern void func_801717C0(void);
extern void func_80172EA8(void);
extern void func_80172EB0(void);
extern void func_80172EB8(void);
extern void func_80172EF8(void);
extern void func_80172F00(void);
extern void func_80172F08(void);
extern void func_80172F10(void);
extern void func_80175258(void);
extern void func_80175298(void);
extern void func_80170F6C(void);
extern u8 D_80083498[];

#ifdef __mips__
#define BODY_NAME composite_body_80170800
#define BODY_STORAGE static
#define BODY_ATTR __attribute__((used, section(".text.func_80170800")))
#else
#define BODY_NAME func_80170800
#define BODY_STORAGE
#define BODY_ATTR
#endif

BODY_STORAGE void *BODY_NAME(void *, s8, s8, s16) BODY_ATTR;

#ifdef __mips__
static const ActorDefinition actor_definition
    __asm__("func_80170800")
    __attribute__((section(".text.func_80170800"), aligned(4))) = {
    {
        (Callback)BODY_NAME,
        func_80170B40,
        func_8017112C,
        func_80171198,
        func_8017126C,
        func_801713FC,
        func_80171444,
        0,
        func_80171794,
        func_80171794,
        func_80171794,
        func_801717C0,
        func_80171740,
        func_80171740,
        func_80171740,
        func_801716D8,
        func_801716D8,
        func_801717C0,
        func_801717C0,
        func_80171784,
        func_80172F08,
        func_80172F00,
        func_80172EF8,
        func_80172F10,
        func_80172EB8,
        func_80172EB0,
        func_80172EA8,
    },
    {
        0x40, 0x03, 0x00, 0x01, 0x40, 0x00, 0x80, 0x00,
        0x81, 0x40, 0x82, 0x8C, 0x82, 0x85, 0x82, 0x84,
        0x81, 0x40, 0x82, 0x81, 0x81, 0x40, 0x82, 0x8D,
        0x82, 0x85, 0x82, 0x92, 0x82, 0x92, 0x82, 0x99,
        0x81, 0x40, 0x82, 0x84, 0x82, 0x81, 0x82, 0x8E,
        0x82, 0x83, 0x82, 0x85, 0x81, 0x44, 0x00, 0x00,
        0x40, 0x03, 0x00, 0x01, 0x40, 0x00, 0x40, 0x00,
    },
};
__asm__(".globl func_80170800\n"
        ".type func_80170800,@function\n"
        ".size func_80170800, 832");
#endif


typedef struct S_80FB1000_0 {
    u8 pad_00[0x13];
    u8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_80FB1000_0;   /* work in BODY_NAME */

typedef struct S_80FB1000_1 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80FB1000_1;   /* position in BODY_NAME */

typedef struct S_80FB1000_2 {
    u8 pad_00[0x6];
    u16 unk_06;
} S_80FB1000_2;   /* (*(u8 * *)((u8 *)monster + 8)) + (scale + i) * 4 in BODY_NAME */

BODY_STORAGE void *BODY_NAME(void *arg0, s8 arg1, s8 arg2, s16 arg3)
{
    register s8 arg1_role ASM_REG("$21");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register s8 arg2_role ASM_REG("$20");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
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
    created = func_8003FD64(0x112, D_80083498);
    if (created != 0) {
        register s32 arg0_copy ASM_REG("$23");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
        void *init_arg0;
        s32 flags0;
        s32 flags1;
        s32 value;
        u8 *entry;
        s32 i;
        s32 scale;

        work = (u8 *)created + 0x20;
        arg0_copy = (s32)arg0;
        ASM_KEEP(arg0_copy);   /* MATCH pin: retail schedule: same instructions, different order without it */
        (*(Callback *)((u8 *)created + 0x10)) = func_80170B40;
        ((S_80FB1000_0 *)work)->unk_13 = 0x27;
        func_8004491C(created, func_80045340);

        position = (*(u8 * *)((u8 *)created + 8));
        ((S_80FB1000_1 *)position)->unk_0A = arg3_role;
        monster = (*(u8 * *)((u8 *)created + 0xC));
        (*(u8 *)((u8 *)monster + 0x25)) = arg2_role;
        actor = work;
        (*(Callback *)((u8 *)monster + 0x2C)) = func_80175258;
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
#ifdef __mips__
                value = func_800A6D30();
#else
                value = func_800A6D30(created, position);
#endif
                init_arg0 = created;
                if (!(value & 1)) {
                    goto initialize_after_a0;
                }
                ((S_80FB1000_0 *)work)->unk_1C |= 0x200;
                value = func_800A6D30(created);
                func_800A48F0(work, 1, (value & 0x3F) | 0x20);
                (*(Callback *)((u8 *)monster + 0x2C)) = func_80175298;
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
        (*(Callback *)((u8 *)actor + 0x8C)) = func_80170F6C;
        (*(s16 *)((u8 *)actor + 0xAE)) = value;

        entry = (*(u8 * *)((u8 *)monster + 8));
loop_test:
        scale = i << 1;
        if (!(entry[0] & 0x20)) {
            goto loop_done;
        }
        entry += 12;
        i++;
        goto loop_test;

loop_done:
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
