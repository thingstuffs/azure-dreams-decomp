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

void func_80124908(struct Ent *arg0)
{
    unsigned char v;

    if (D_80126A01[0] != 0) {
        arg0->unkE |= 1;
    } else {
        arg0->unkE &= 0xFE;
    }
    if (D_80126A01[0] < ((D_801278B0[arg0->unk13].unk4 - 3) << 4)) {
        v = arg0->unkE | 2;
    } else {
        v = arg0->unkE & 0xFD;
    }
    arg0->unkE = v;
}
