/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

typedef struct S_80FD5000_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_80FD5000_0;   /* temp_s1 in BODY_NAME */

typedef struct S_80FD5000_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0x6C];
    M2C_UNK * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
    u8 pad_9D[0x11];
    s16 unk_AE;
} S_80FD5000_1;   /* var_s0 in BODY_NAME */

typedef struct S_80FD5000_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80FD5000_2;   /* temp_s6 in BODY_NAME */

typedef struct S_80FD5000_3 {
    u8 pad_00[0x8];
    u8 * unk_08;
    u8 pad_0C[0x6];
    u16 unk_12;
    u8 pad_14[0x10];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    M2C_UNK * unk_2C;
} S_80FD5000_3;   /* temp_s2 in BODY_NAME */


typedef struct S_80FD5000_4 {
    u8 unk_00;
    u8 pad_01[0x5];
    u16 unk_06;
} S_80FD5000_4;


void *func_8003FD64();
M2C_UNK func_8004491C();
M2C_UNK func_800673A0();
M2C_UNK func_800A48F0();
s32 func_800A6D30();
M2C_UNK func_800A9C18();
M2C_UNK func_800AA36C();
void *func_8014C984();
void *func_8014CA40();
extern M2C_UNK D_80045340;
extern M2C_UNK D_80083498;
extern M2C_UNK D_8014CB40;
extern M2C_UNK D_8014CF6C;
extern M2C_UNK D_80151258;
extern M2C_UNK D_80151298;

typedef void (*Callback)(void);
typedef struct {
    Callback callbacks[27];
    u8 config[56];
} ActorDefinition;

extern void func_8014D12C(void);
extern void func_8014D198(void);
extern void func_8014D26C(void);
extern void func_8014D3FC(void);
extern void func_8014D444(void);
extern void func_8014D794(void);
extern void func_8014D7C0(void);
extern void func_8014D740(void);
extern void func_8014D6D8(void);
extern void func_8014D784(void);
extern void func_8014EF08(void);
extern void func_8014EF00(void);
extern void func_8014EEF8(void);
extern void func_8014EF10(void);
extern void func_8014EEB8(void);
extern void func_8014EEB0(void);
extern void func_8014EEA8(void);

#ifdef __mips__
extern void *func_8014C8A4(void *, s8, s8, s16);

static const ActorDefinition extent_prefix
    __asm__("func_8014C800")
    __attribute__((used, section(".text.func_8014C800"), aligned(4))) = {
    {
        (Callback)func_8014C8A4,
        (Callback)&D_8014CB40,
        func_8014D12C,
        func_8014D198,
        func_8014D26C,
        func_8014D3FC,
        func_8014D444,
        0,
        func_8014D794,
        func_8014D794,
        func_8014D794,
        func_8014D7C0,
        func_8014D740,
        func_8014D740,
        func_8014D740,
        func_8014D6D8,
        func_8014D6D8,
        func_8014D7C0,
        func_8014D7C0,
        func_8014D784,
        func_8014EF08,
        func_8014EF00,
        func_8014EEF8,
        func_8014EF10,
        func_8014EEB8,
        func_8014EEB0,
        func_8014EEA8,
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
__asm__(".globl func_8014C800\n"
        ".size func_8014C800, 832");
#define BODY_NAME func_8014C8A4
#else
#define BODY_NAME func_8014C800
#endif


typedef struct {
    s16 x;
    s16 y;
    s16 w;
    s16 h;
} Rect;

/* Creates a monster actor and initializes its state, placement, and palette. */
void *BODY_NAME(void *spawn_flags, s8 tile_x, s8 tile_y, s16 heading)
{
    s8 saved_x;
    register s8 saved_y ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register s16 saved_heading ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    S_80FD5000_0 *created;
    register S_80FD5000_1 *actor_state ASM_REG("$16") = 0;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    S_80FD5000_2 *position;
    register S_80FD5000_3 *monster ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    register S_80FD5000_1 *actor ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register s32 call_id ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    register void *call_definition ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s32 spawn_kind;
    Rect palette_strip;

    call_id = 0x112;
    saved_x = tile_x;
    ASM_KEEP_DEP_NV(saved_x, call_id);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    call_definition = &D_80083498;
    ASM_KEEP_DEP_NV(call_definition, saved_x);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    saved_heading = heading;
    saved_y = tile_y;
    created = func_8003FD64(call_id, call_definition);
    if (created != 0) {
        register s32 saved_flags ASM_REG("$23");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        s32 actor_flags;
        s32 state_flags;
        register void *call_created ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        register S_80FD5000_2 *call_position ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        s32 random_bits;
        s32 appearance_id;
        s32 palette_y;
        S_80FD5000_4 *entry;
        s32 entry_index;
        s32 twice_index;
        Rect *palette_rect;
        S_80FD5000_4 *selected;
        S_80FD5000_4 *selected2;
        S_80FD5000_4 *selected3;

        actor_state = (S_80FD5000_1 *)((u8 *)created + 0x20);
        saved_flags = (s32)spawn_flags;
        ASM_KEEP(saved_flags);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        created->unk_10 = &D_8014CB40;
        actor_state->unk_13 = 0x27;
        func_8004491C(created, &D_80045340);

        position = created->unk_08;
        position->unk_0A = saved_heading;
        monster = created->unk_0C;
        monster->unk_25 = saved_y;
        actor = actor_state;
        monster->unk_2C = &D_80151258;
        monster->unk_24 = saved_x;

        spawn_kind = (s32)spawn_flags & 3;
        if (spawn_kind == 1) {
            actor_flags = actor_state->unk_14 | 0x6000;
            state_flags = actor_state->unk_1C | 0x6000;
            goto finish_kind;
        }
        if (spawn_kind >= 2) {
            actor_flags = actor_state->unk_14 | 0x2000;
            state_flags = actor_state->unk_1C | 0x2000;
finish_kind:
            actor_state->unk_14 = actor_flags;
            actor_state->unk_1C = state_flags;
            goto finish_kind_args;
        }
        call_created = created;
        if (((s32)spawn_flags & ~3) << 16 != 0)
            goto have_call_position;
        call_position = position;
        if (actor_state->unk_14 & 0x200)
            goto have_call_args;
        random_bits = func_800A6D30(call_created, call_position);
        call_created = created;
        if (!(random_bits & 1))
            goto have_call_position;
        actor_state->unk_1C |= 0x200;
        random_bits = func_800A6D30(created);
        func_800A48F0(actor_state, 1, (random_bits & 0x3F) | 0x20);
        monster->unk_2C = &D_80151298;

finish_kind_args:
        call_created = created;
have_call_position:
        call_position = position;
have_call_args:
        func_800A9C18(call_created, call_position, monster, (s16)saved_flags);

        entry_index = 0;
        appearance_id = monster->unk_12;
        actor->unk_9A = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C = &D_8014CF6C;
        actor->unk_AE = appearance_id;

        entry = (S_80FD5000_4 *)monster->unk_08;
scan_entry:
        twice_index = entry_index << 1;
        if (entry->unk_00 & 0x20) {
            entry = (S_80FD5000_4 *)((u8 *)entry + 12);
            entry_index++;
            goto scan_entry;
        }

        palette_rect = &palette_strip;
        selected = (S_80FD5000_4 *)(twice_index + entry_index);
        selected2 = (S_80FD5000_4 *)((s32)selected * 4);
        selected3 = (S_80FD5000_4 *)((u8 *)selected2 + (s32)monster->unk_08);
        palette_y = selected3->unk_06 >> 6;
        palette_strip.x = 0;
        palette_strip.y = palette_y;
        palette_strip.w = 0x100;
        palette_strip.h = 1;
        func_800673A0(palette_rect, 0, palette_y - 1);

        palette_strip.w = 0x10;
        palette_strip.x = 0x30;
        palette_strip.y--;
        do {
            func_800673A0(&palette_strip, palette_strip.x - 0x30, palette_strip.y);
            palette_strip.x += 0x40;
        } while (palette_strip.x < 0x100);

        func_800AA36C(actor, position, monster, actor_state);
    }
    return actor_state;
}
