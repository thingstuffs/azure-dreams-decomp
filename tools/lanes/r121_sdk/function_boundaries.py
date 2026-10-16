"""Conservative MIPS function-entry and terminal-return evidence.

These are discovery boundaries. Complete donor bytes, existing rowbase, source
compilation and full production gates remain mandatory admission authorities.
"""
JR_RA=0x03E00008


def stack_prologue(word):
    return word>>16==0x27BD and word&0x8000 and (0x10000-(word&0xffff))%8==0


def entries(words,start,region_edges=(),previous_words=()):
    prefix=tuple(previous_words[-5:]);origin=start-len(prefix)*4
    combined=prefix+tuple(words)
    out={}
    for i,word in enumerate(combined):
        if stack_prologue(word):out.setdefault(origin+4*i,[]).append('addiu-sp-negative-frame')
        if word==JR_RA and i+2<len(combined):
            # Delay slot is part of the previous function. Permit ordinary
            # zero alignment padding before a leaf entry, at most 3 words.
            j=i+2
            for k in range(j,min(j+4,len(combined))):
                out.setdefault(origin+4*k,[]).append('after-jr-ra-delay-slot')
                if combined[k]:break
    for edge in region_edges:
        if start<=edge<start+4*len(words):out.setdefault(edge,[]).append('existing-rowbase-region-edge')
    return {address:reasons for address,reasons in out.items() if start<=address<start+len(words)*4}


def terminal_return(words):
    # A return instruction and its delay slot must terminate the complete
    # matched extent, with no more than three words of zero alignment padding.
    for i in range(max(0,len(words)-5),max(0,len(words)-1)):
        if words[i]==JR_RA and not any(words[i+2:]):return i
    return None


def self_test():
    assert stack_prologue(0x27BDFFE0)
    assert not stack_prologue(0x27BD0020) and not stack_prologue(0x27BDFFFD)
    words=[0x27BDFFE0,0,JR_RA,0x27BD0020,0,0x24020001,JR_RA,0]
    out=entries(words,0x100,[0x100,0x114])
    assert out[0x100]==['addiu-sp-negative-frame','existing-rowbase-region-edge']
    assert 'after-jr-ra-delay-slot' in out[0x114] and 0x10C not in out
    assert terminal_return(words)==6 and terminal_return([JR_RA,0,0,0])==0
    assert terminal_return([JR_RA,0,1]) is None and terminal_return([JR_RA]) is None
    assert entries([0x24020001,JR_RA,0],0x200,previous_words=[JR_RA,0])[0x200]==['after-jr-ra-delay-slot']
    print('function boundary evidence: 8 checks PASS')


if __name__=='__main__':self_test()
