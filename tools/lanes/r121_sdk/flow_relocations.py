"""MIPS reaching-upper analysis across branches, delay slots and indexed bases.

Discovery remains separate from admission. Each accepted differing field must
also have its native ELF relocation in the measured production object.
"""
import collections

LOW={9,13,32,33,34,35,36,37,38,40,41,42,43,46}
WRITES={8,9,10,11,12,13,14,15,32,33,34,35,36,37,38}
UNKNOWN=-1


def reaching(words,vram):
    count=len(words);successors={i:[i+1] if i+1<count else [] for i in range(count)}
    call_slots=set()
    def index(address):
        return (address-vram)//4 if vram<=address<vram+4*count and (address-vram)%4==0 else None
    for i,w in enumerate(words):
        op=w>>26;imm=w&65535;imm-=65536 if imm&32768 else 0
        if i+1>=count:continue
        if op in (1,4,5,6,7):
            target=i+1+imm
            successors[i+1]=[j for j in (target,i+2) if 0<=j<count]
        elif op==2:
            target=index((vram&0xf0000000)|((w&0x3ffffff)<<2))
            successors[i+1]=[] if target is None else [target]
        elif op==3:
            successors[i+1]=[i+2] if i+2<count else [];call_slots.add(i+1)
        elif op==0 and (w&63) in (8,9):
            if w&63==9:
                successors[i+1]=[i+2] if i+2<count else [];call_slots.add(i+1)
            else:successors[i+1]=[]
    predecessors=collections.defaultdict(list)
    for i,ss in successors.items():
        for j in ss:predecessors[j].append(i)
    blank=tuple(frozenset({UNKNOWN}) for _ in range(32))
    incoming={};outgoing={};queue=collections.deque(i for i in range(count) if not predecessors[i] or i==0)
    queued=set(queue)
    def transfer(i,state):
        w=words[i];op=w>>26;rs=w>>21&31;rt=w>>16&31;rd=w>>11&31
        values=list(state)
        if op==15:values[rt]=frozenset({i})
        elif op in WRITES:values[rt]=frozenset({UNKNOWN})
        elif op==0 and (w&63) in (32,33,34,35,37):
            # An indexed address can add an arbitrary register between lui
            # and its lo16. Preserve the one symbolic upper, not two bases.
            a,b=state[rs],state[rt]
            known_a=UNKNOWN not in a;known_b=UNKNOWN not in b
            if rt==0:values[rd]=a
            elif rs==0 and (w&63) not in (34,35):values[rd]=b
            elif known_a and not known_b:values[rd]=a
            elif known_b and not known_a and (w&63) not in (34,35):values[rd]=b
            else:values[rd]=frozenset({UNKNOWN})
        elif op==0 and (w&63) not in (8,12,13,17,19,24,25,26,27):values[rd]=frozenset({UNKNOWN})
        if i in call_slots:
            for register in (1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,24,25,31):values[register]=frozenset({UNKNOWN})
        values[0]=frozenset({UNKNOWN})
        return tuple(values)
    while True:
        while queue:
            i=queue.popleft();queued.discard(i)
            parents=[outgoing[p] for p in predecessors[i] if p in outgoing]
            if i==0 or not parents:parents.append(blank)
            state=tuple(frozenset().union(*(p[r] for p in parents)) for r in range(32))
            incoming[i]=state;result=transfer(i,state)
            if outgoing.get(i)==result:continue
            outgoing[i]=result
            for j in successors[i]:
                if j not in queued:queue.append(j);queued.add(j)
        missing=next((i for i in range(count) if i not in outgoing),None)
        if missing is None:break
        queue.append(missing);queued.add(missing)
    refs={};hi=collections.defaultdict(list)
    for i,w in enumerate(words):
        op=w>>26;rs=w>>21&31
        if op not in LOW:continue
        definitions=incoming[i][rs]
        if not definitions or UNKNOWN in definitions:continue
        imm=w&65535;imm=imm if op==13 or imm<32768 else imm-65536
        addresses={(words[j]&65535)*65536+imm for j in definitions}
        if len(addresses)!=1:continue
        address=next(iter(addresses))&0xffffffff
        refs[i]=dict(kind='absolute',address=address,his=sorted(definitions))
        for j in definitions:hi[j].append(i)
    return refs,dict(hi)


def prove(a,b,source_vram,target_vram):
    if len(a)!=len(b):return None
    ar,ah=reaching(a,source_vram);br,bh=reaching(b,target_vram);differences=[]
    for i,(x,y) in enumerate(zip(a,b)):
        if x==y:continue
        op=x>>26
        if op in (2,3) and y>>26==op:kind='jal' if op==3 else 'j'
        elif x>>16!=y>>16:return None
        elif op==15:
            pairs=set(ah.get(i,[]))&set(bh.get(i,[]))
            if not any(0x80000000<=ar[k]['address']<0x82000000 and 0x80000000<=br[k]['address']<0x82000000
                       and ar[k]['his']==br[k]['his'] for k in pairs):return None
            kind='lui'
        elif op in LOW:
            if i not in ar or i not in br or ar[i]['his']!=br[i]['his']:return None
            if not (0x80000000<=ar[i]['address']<0x82000000 and 0x80000000<=br[i]['address']<0x82000000):return None
            kind='paired-lo16'
        else:return None
        differences.append(dict(word=i,kind=kind,before=hex(x),after=hex(y)))
    return differences,ar,br


def self_test():
    # addu between lui and lw forms an indexed symbolic base.
    a=[0x3c028017,0x00441021,0x8c425000,0x03e00008,0]
    b=[0x3c028016,0x00441021,0x8c425000,0x03e00008,0]
    assert prove(a,b,0x80170000,0x80160000)
    changed=list(b);changed[2]=0x8c435000
    assert prove(a,changed,0x80170000,0x80160000) is None
    # The upper lives across a direct jump; the linear later lui is on a
    # separate path. Both origins reach the common lo16.
    a=[0x3c028017,0x0805c004,0,0x3c028017,0x24425000,0x03e00008,0]
    b=[0x3c028016,0x08058004,0,0x3c028016,0x24425000,0x03e00008,0]
    assert prove(a,b,0x80170000,0x80160000)
    print('flow relocation pairs: indexed base, branch and refusal checks PASS')


if __name__=='__main__':self_test()
