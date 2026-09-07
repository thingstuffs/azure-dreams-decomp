struct Tbl {
    unsigned char unk0[4];
    unsigned char unk4;
    unsigned char unk5[3];
};

struct Ent {
    unsigned char unk0[14];
    unsigned char unkE;
    unsigned char unkF[4];
    unsigned char unk13;
};

extern unsigned char D_80126A01[];
extern struct Tbl D_801278B0[];

/* Update entry flags from the global value and the entry's table threshold. */
void func_80124908(struct Ent *entry)
{
    unsigned char flags;

    if (D_80126A01[0] != 0) {
        entry->unkE |= 1;
    } else {
        entry->unkE &= 0xFE;
    }
    if (D_80126A01[0] < ((D_801278B0[entry->unk13].unk4 - 3) << 4)) {
        flags = entry->unkE | 2;
    } else {
        flags = entry->unkE & 0xFD;
    }
    entry->unkE = flags;
}
