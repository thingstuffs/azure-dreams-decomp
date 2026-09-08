typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef int s32;

typedef struct Ent {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ u8 unk1;
    /* 0x02 */ u8 unk2;
    /* 0x03 */ u8 unk3;
} Ent;

typedef struct Actor {
    /* 0x00 */ u8 pad0[0x24];
    /* 0x24 */ u8 unk24;
    /* 0x25 */ u8 unk25;
} Actor;

typedef struct Ctx {
    /* 0x00 */ u8 pad0[0x88];
    /* 0x88 */ s16 unk88;
} Ctx;

extern Ent D_800E3648[];

extern s32 func_800B500C(s32 a, s32 b, s32 c);
extern s32 func_800B627C(s32 a, Ctx *b, s32 c, s32 d);

/* Process the actor's matching entry if enabled, clearing its enable bit unless retained. */
s32 func_800ADAE4(Actor *actor, Ctx *ctx)
{
    s16 entry_index;
    Ent *entries;
    Ent *entry;
    u8 entry_flags;
    s32 result;

    entry_index = (s16)func_800B500C(actor->unk24, actor->unk25, ctx->unk88);
    if (entry_index < 0) {
        return 1;
    }
    entries = D_800E3648;
    entry = entries + entry_index;
    entry_flags = entry->unk3;
    if ((entry_flags & 0x80) == 0) {
        return 1;
    }
    if ((entry_flags & 0x40) == 0) {
        entry->unk3 = entry_flags & 0x7F;
    }
    result = func_800B627C(entry->unk0, ctx, entry_index, 0);
    if (result == 0) {
        return 0;
    }
    return (s16)result;
}
