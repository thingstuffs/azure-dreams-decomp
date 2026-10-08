#include "common.h"
#include "shared/object_node.h"


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
extern s32 func_800A6D30(void); /* Retail RNG at 0x800A6D30 reads no incoming argument registers, including a3. */
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

void *func_801708A4(s16, s32, s16, s16);

typedef struct S_80FB1000_0 {
    u8 pad_00[0x13];
    u8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_80FB1000_0;   /* work in func_801708A4 */

typedef struct S_80FB1000_1 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80FB1000_1;   /* position in func_801708A4 */

typedef struct S_80FB1000_2 {
    u8 pad_00[0x6];
    u16 unk_06;
} S_80FB1000_2;   /* (*(u8 * *)((u8 *)monster + 8)) + (scale + i) * 4 in func_801708A4 */

void *func_801708A4(s16 mode, s32 value1, s16 value2, s16 value3)
{
    s16 mode_copy;
    s32 value1_saved;
    s8 value2_byte;
    s16 value3_saved;
    void *created;
    u8 *work = 0;
    u8 *position;
    u8 *monster;
    u8 *actor;
    s32 kind;
    Rect rect;

    value1_saved = value1;
    value3_saved = value3;
    value2_byte = value2;
    value1 = 0x112;
    created = func_8003FD64(value1, ((u8 *)(&D_80083498)));
    mode_copy = (s32)mode;
    if (created != 0) {
        void *init_object;
        s32 flags0;
        s32 flags1;
        s32 value;
        u8 *entry;
        s32 i;
        s32 scale;

        work = (u8 *)created + 0x20;
        (*(Callback *)((u8 *)created + 0x10)) = func_80170B40;
        ((S_80FB1000_0 *)work)->unk_13 = 0x27;
        func_8004491C(created, func_80045340);

        position = (*(u8 * *)((u8 *)created + 8));
        ((S_80FB1000_1 *)position)->unk_0A = value3_saved;
        monster = (*(u8 * *)((u8 *)created + 0xC));
        (*(u8 *)((u8 *)monster + 0x25)) = value2_byte;
        actor = work;
        (*(Callback *)((u8 *)monster + 0x2C)) = func_80175258;
        (*(u8 *)((u8 *)monster + 0x24)) = value1_saved;

        kind = (s32)mode & 3;
        if (kind == 1) {
            flags0 = ((S_80FB1000_0 *)work)->unk_14 | 0x6000;
            flags1 = ((S_80FB1000_0 *)work)->unk_1C | 0x6000;
            ((S_80FB1000_0 *)work)->unk_14 = flags0;
            ((S_80FB1000_0 *)work)->unk_1C = flags1;
        } else if (kind >= 2) {
            flags0 = ((S_80FB1000_0 *)work)->unk_14 | 0x2000;
            flags1 = ((S_80FB1000_0 *)work)->unk_1C | 0x2000;
            ((S_80FB1000_0 *)work)->unk_14 = flags0;
            ((S_80FB1000_0 *)work)->unk_1C = flags1;
        } else {
            if ((s16)((s32)mode & -4) == 0 &&
                !(((S_80FB1000_0 *)work)->unk_14 & 0x200)) {
                value = func_800A6D30();
                if (value & 1) {
                    ((S_80FB1000_0 *)work)->unk_1C |= 0x200;
                    value = func_800A6D30();
                    func_800A48F0(work, 1, (value & 0x3F) | 0x20);
                    (*(Callback *)((u8 *)monster + 0x2C)) = func_80175298;
                }
            }
        }

        init_object = created;
        func_800A9C18(init_object, position, monster, (s16)mode_copy);
        i = 0;
        value = (*(u16 *)((u8 *)monster + 0x12));
        (*(u8 *)((u8 *)actor + 0x9A)) = 0xFF;
        (*(s8 *)((u8 *)actor + 0x9C)) = -1;
        (*(Callback *)((u8 *)actor + 0x8C)) = func_80170F6C;
        (*(s16 *)((u8 *)actor + 0xAE)) = value;

        entry = (*(u8 * *)((u8 *)monster + 8));
        while (1) {
            scale = i << 1;
            if (!(entry[0] & 0x20)) {
                break;
            }
            entry += 12;
            i++;
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
