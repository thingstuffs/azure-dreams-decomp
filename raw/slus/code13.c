/* gcc 2.8.1 -O2 — own TU (func_8004D09C: callback fwd-decl conflict) */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

/* Inner struct pointed to by arg->unk20; only offsets 0x2/0x6/0xA are read (u16 fields). */
typedef struct {
    u8 pad0[2];
    u16 unk2;
    u8 pad4[2];
    u16 unk6;
    u8 pad8[2];
    u16 unkA;
} SrcStruct;

/* Outer struct passed in; only the pointer at offset 0x20 is used. */
typedef struct {
    u8 pad0[0x20];
    SrcStruct *unk20;
} InStruct;

/* Destination global struct; only offsets 0xBC/0xBE/0xC0 are written. Size forces hi/lo access. */
typedef struct {
    u8 pad[0xBC];
    u16 unkBC;
    u16 unkBE;
    u16 unkC0;
} D_80083160_t;

extern D_80083160_t D_80083160;

/* Copies three u16 fields from arg0->unk20 into the global D_80083160. */
void func_8004D09C(InStruct *arg0)
{
    SrcStruct *src = arg0->unk20;

    D_80083160.unkBC = src->unk2;
    D_80083160.unkBE = src->unk6;
    D_80083160.unkC0 = src->unkA;
}
