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

s32 func_800ADAE4(Actor *arg0, Ctx *arg1)
{
    s16 idx;
    Ent *base;
    Ent *e;
    u8 flags;
    s32 ret;

    idx = (s16)func_800B500C(arg0->unk24, arg0->unk25, arg1->unk88);
    if (idx < 0) {
        return 1;
    }
    base = D_800E3648;
    e = base + idx;
    flags = e->unk3;
    if ((flags & 0x80) == 0) {
        return 1;
    }
    if ((flags & 0x40) == 0) {
        e->unk3 = flags & 0x7F;
    }
    ret = func_800B627C(e->unk0, arg1, idx, 0);
    if (ret == 0) {
        return 0;
    }
    return (s16)ret;
}
