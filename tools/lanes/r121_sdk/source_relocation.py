"""Relocate address spellings hidden from the symbol-token renamer.

Only retail-paired addresses can supply a new symbol. Original C stays intact;
each transformation is recorded and the normal compiler must still prove it.
"""
import re


def prepare(text,mapping,mode='basic'):
    edits=[];decls=set()
    constants={name:int(value,0) for name,value in re.findall(
        r'^\s*#define\s+(\w+)\s+(0x[\da-fA-F]+|\d+)\s*$',text,re.M)}
    byte_arrays=set(re.findall(r'extern\s+(?:const\s+)?(?:u8|s8|char|unsigned char)\s+(D_[\dA-Fa-f]{8})\s*\[',text))
    def indexed(match):
        base,name=match[1],match[2];offset=constants.get(name)
        if offset is None:
            try:offset=int(name,0)
            except ValueError:return match[0]
        old=int(base[2:],16)+offset
        new=mapping.get(old)
        if base not in byte_arrays or new is None or new==old:return match[0]
        symbol=f'D_{new:08X}';decls.add(symbol)
        edits.append(dict(kind='byte-array-base-plus-offset',before=match[0],after=symbol,
            source_address=hex(old),target_address=hex(new)))
        return symbol
    text=re.sub(r'&\s*(D_[\dA-Fa-f]{8})\s*\[\s*(\w+)\s*\]',indexed,text)
    # A local const definition emits storage at the donor TU's section. The
    # target already has retail storage at the paired absolute address; an
    # extern reference is the corresponding relink representation.
    pattern=r'^(const\s+[A-Za-z_][\w \t]*\s+)(D_[\dA-Fa-f]{8})(\s*(?:\[[^\n;=]*\])?)\s*=\s*([^;]*);'
    def rodata(match):
        old=int(match[2][2:],16);new=mapping.get(old)
        if new is None or new==old:return match[0]
        replacement='extern '+match[1]+match[2]+match[3].strip()+';'
        edits.append(dict(kind='local-const-storage-to-paired-extern',before=match[0],after=replacement,
            source_address=hex(old),target_address=hex(new)))
        return replacement
    text=re.sub(pattern,rodata,text,flags=re.M)
    if mode in ('split-address','split-pointer','split-late','split-deferred','split-signed-base','split-zero'):
        # Integer temporaries used for an address may spell upper+offset in
        # separate statements. Keep the integer type and let GCC schedule the
        # symbolic address. No arithmetic literal is changed speculatively.
        for match in list(re.finditer(r'\b(\w+)\s*\+=\s*(0x[\dA-Fa-f]+)\s*;',text)):
            variable=match[1];offset=int(match[2],16)
            assignments=list(re.finditer(r'\b'+variable+r'\s*=\s*(0x[89aA][\dA-Fa-f]{7})\s*;',text[:match.start()]))
            bases={int(a[1],16) for a in assignments}
            if len(bases)!=1:continue
            base=bases.pop();old=base+offset;new=mapping.get(old)
            if new is None or new==old or base&65535:continue
            # Refuse when the integer has other uses between construction
            # and the final +=. Repeated branch assignments are permitted.
            first=assignments[0].start();middle=text[first:match.start()]
            rest=re.sub(r'\b'+variable+r'\s*=\s*0x[\dA-Fa-f]+\s*;','',middle)
            if re.search(r'\b'+variable+r'\b',rest):continue
            symbol=f'D_{new:08X}';decls.add(symbol)
            oldtext=text
            if mode=='split-zero':
                text=re.sub(r'\b'+variable+r'\s*=\s*'+re.escape(assignments[0][1])+r'\s*;',variable+' = 0;',text)
                text=text.replace(match[0],variable+' += (s32)'+symbol+';',1)
                edits.append(dict(kind='split-integer-address',variable=variable,
                    source_address=hex(old),target_address=hex(new),mode=mode))
                continue
            if mode in ('split-deferred','split-signed-base'):
                low=offset if mode=='split-deferred' else (new&65535)-(65536 if new&32768 else 0)
                expression='(s32)'+symbol+(' - ' if low>=0 else ' + ')+hex(abs(low))
                text=re.sub(r'\b'+variable+r'\s*=\s*'+re.escape(assignments[0][1])+r'\s*;',variable+' = '+expression+';',text)
                text=text.replace(match[0],variable+' += '+('-' if low<0 else '')+hex(abs(low))+';',1)
                edits.append(dict(kind='split-integer-address',variable=variable,
                    source_address=hex(old),target_address=hex(new),mode=mode))
                continue
            if mode=='split-late':
                if not re.search(r'\bs32\s+'+variable+r'\s*;',text[:first]) or re.search(r'&\s*'+variable+r'\b',text):
                    decls.discard(symbol);continue
                text=re.sub(r'\b'+variable+r'\s*=\s*'+re.escape(assignments[0][1])+r'\s*;','',text)
                text=text.replace(match[0],variable+' = (s32)'+symbol+';',1)
                edits.append(dict(kind='split-integer-address',variable=variable,
                    source_address=hex(old),target_address=hex(new),mode=mode))
                continue
            cast='(s32)' if mode=='split-address' else ''
            text=re.sub(r'\b'+variable+r'\s*=\s*'+re.escape(assignments[0][1])+r'\s*;',
                variable+' = '+cast+symbol+';',text)
            text=text.replace(match[0],'',1)
            if mode=='split-pointer':
                definition=re.search(r'\bs32\s+'+variable+r'\s*;',text[:first])
                if not definition:
                    text=oldtext;decls.discard(symbol);continue
                temporary=variable+'_relocated'
                start=re.search(r'\b'+variable+r'\s*=\s*'+symbol+r'\s*;',text).start()
                text=text[:start]+re.sub(r'\b'+variable+r'\b',temporary,text[start:])
                text=text[:definition.end()]+'\n    u8 *'+temporary+';'+text[definition.end():]
            if text!=oldtext:edits.append(dict(kind='split-integer-address',variable=variable,
                source_address=hex(old),target_address=hex(new),mode=mode))
    if decls:
        includes=list(re.finditer(r'^\s*#\s*include[^\n]*\n',text,re.M))
        position=includes[-1].end() if includes else 0
        text=text[:position]+''.join('extern u8 '+s+'[];\n' for s in sorted(decls))+text[position:]
    return text,edits
