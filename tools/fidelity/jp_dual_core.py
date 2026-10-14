"""Address mask v4 and exact word LCS, retained from r118 jpfinger core.py."""
import array, re, struct, sys

def words(blob):
    return list(struct.unpack('<'+'I'*(len(blob)//4), blob[:len(blob)//4*4]))

def packed(seq):
    a = array.array('I', seq)
    if sys.byteorder != 'little': a.byteswap()
    return a.tobytes()

def c89_comments(source):
    # Old GCC 2.6.3 rejects // in plain C mode. Convert comments only, preserving
    # every newline (__LINE__), quoted string, character literal, and C token.
    token=re.compile(r'"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'|/\*.*?\*/|//[^\n]*',re.S)
    return token.sub(lambda m:'/*'+m.group()[2:].replace('*/','* /')+' */'
                     if m.group().startswith('//') else m.group(),source)

def opcode(w):
    op = w >> 26
    if op == 0: return w & 0xfc00003f
    if op == 1: return w & 0xfc1f0000
    if op in (16,17,18,19): return w & 0xffe0003f
    return w & 0xfc000000

def address_high(w,typ=None):
    imm=w&65535
    return w>>26==15 and (typ=='HI16' or 0x8000<=imm<=0x81ff or
                           0xa000<=imm<=0xa1ff or imm in (0x1f80,0x1f00))

def reaching_pages(ws,rm):
    """May-reaching page bases through conditional branches and their delay slots.

    Use only for small function slices, never a whole container. Absolute jump
    destinations are not assumed to be known. The linear recognizer remains the
    fallback for regions only reached through an absolute jump.
    """
    n=len(ws)
    if not n or n>4096:return []
    incoming=[-1]*n;incoming[0]=0;todo=[0]
    callmask=sum(1<<r for r in [1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,24,25,31])
    while todo:
        i=todo.pop();w=ws[i];state=incoming[i]
        op,rs,rt,rd=w>>26,(w>>21)&31,(w>>16)&31,(w>>11)&31
        if op==15:
            state&=~(1<<rt)
            if address_high(w,rm.get(i)):state|=1<<rt
        elif op==0 and w&63 not in (8,9,12,13,17,19,24,25,26,27):
            have=w&63 in (0x21,0x23,0x25) and state & ((1<<rs)|(1<<rt))
            state&=~(1<<rd)
            if have:state|=1<<rd
        elif op not in (0,1,2,3,4,5,6,7,16,17,18,19) and not 40<=op<=63:
            state&=~(1<<rt)
        nexts=[i+1]
        if i:
            prev=ws[i-1];po=prev>>26
            if po in (1,4,5,6,7):
                imm=prev&65535;imm=imm-65536 if imm&32768 else imm
                nexts=[i+1,i+imm]
            elif po==3 or (po==0 and prev&63==9):state&=~callmask
            elif po==2 or (po==0 and prev&63==8):nexts=[]
        for j in nexts:
            if not 0<=j<n:continue
            merged=state if incoming[j]<0 else incoming[j]|state
            if merged!=incoming[j]:incoming[j]=merged;todo.append(j)
    return incoming

def masked(ws, relocs=()):
    """Only address fields are erased; register, constant and branch bits survive.

    Recognize RAM/scratchpad/IO LUI pages, ELF address relocations, and GP memory
    accesses. Track literal page bases through moves, not arbitrary pointer loads.
    Mask only the first addiu/ori resolving a page; object-member offsets survive.
    Absolute j/jal target bits are masked. Relative branch displacements survive.
    This intentionally cannot prove callee identity or object-field identity.
    """
    rm = {off//4:typ for off,typ in relocs}
    incoming=reaching_pages(ws,rm)
    pages = set()
    out, reasons = [], {}
    for i,w in enumerate(ws):
        op, rs, rt, rd, imm = w>>26, (w>>21)&31, (w>>16)&31, (w>>11)&31, w&65535
        typ = rm.get(i)
        reaching = incoming[i] if incoming and incoming[i]>=0 else 0
        ispage = rs in pages or bool(reaching & (1<<rs))
        mask = 0xffffffff
        reason = None
        if op in (2,3):
            mask,reason = 0xfc000000,'absolute_jump'
        elif typ in ('HI16','LO16','GPREL16'):
            mask,reason = 0xffff0000,'elf_'+typ
        elif address_high(w):
            mask,reason = 0xffff0000,'literal_address_hi'
        elif op in (8,9,13) and ispage:
            mask,reason = 0xffff0000,'literal_address_lo'
        elif op in range(32,64) and (ispage or rs == 28):
            mask,reason = 0xffff0000,'literal_or_gp_memory'
        if reason:
            reasons[i] = reason
        out.append(w & mask)
        if op == 15:
            pages.discard(rt)
            if reason: pages.add(rt)
        elif op == 0:
            if (w&63) in (0x21,0x23,0x25) and (rs in pages or rt in pages):
                have = True
                pages.discard(rd)
                if have: pages.add(rd)
            elif (w&63) not in (8,9,12,13,17,19,24,25,26,27):
                pages.discard(rd)
        elif op not in (1,2,3,4,5,6,7,16,17,18,19) and not (40 <= op <= 63):
            pages.discard(rt)
        # A call clobbers caller-saved registers after its delay instruction.
        if i and (ws[i-1]>>26 == 3 or (ws[i-1]>>26 == 0 and ws[i-1]&63 == 9)):
            pages.difference_update([1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,24,25,31])
    return out,reasons

def lcs(a,b):
    # Bit-parallel exact LCS, preserving repeated instructions unlike autojunk.
    masks = {}
    for j,w in enumerate(b): masks[w] = masks.get(w,0) | (1<<j)
    state = 0
    for w in a:
        x = state | masks.get(w,0)
        state = x & ~(x - ((state<<1)|1))
    return state.bit_count()

def distance(a,b):
    n = lcs(a,b)
    return {'exact': a==b, 'lcs':n, 'distance':len(a)+len(b)-2*n,
            'normalized_distance': (len(a)+len(b)-2*n)/max(len(a),len(b),1),
            'generated_words':len(a), 'target_words':len(b)}

