"""PsyQ ABI authority: existing declarations in headers used by matched C.

Only symbols inside named psyq ASM segments qualify. Conflicting header
declarations refuse the symbol, and resident SDK targets may never relocate.
This is a static declaration binding, not a reconstructed C body.
"""
import hashlib
import re
from pathlib import Path
import yaml
from contracts import declaration


def digest(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def signature(contract):
    definition=contract['definition'];name=contract['name']
    match=re.fullmatch(r'(.*?)\b'+re.escape(name)+r'\((.*)\)',definition)
    if not match:raise ValueError('unparsed SDK declaration')
    def canonical(value,parameter=False):
        value=' '.join(value.split())
        if '(' in value or ')' in value or '[' in value:raise ValueError('complex SDK parameter')
        if parameter:
            if '*' in value:value=re.sub(r'(?<=\*)\s*[A-Za-z_]\w*$', '',value)
            else:
                from contracts import SCALARS,ALIASES
                if value not in SCALARS and value not in ALIASES and value!='...':
                    value=re.sub(r'\s+[A-Za-z_]\w*$', '',value)
        from contracts import ALIASES
        value=re.sub(r'\bM2C_UNK\w*\b',lambda m:ALIASES.get(m[0],m[0]),value)
        for old,new in [('unsigned int','u32'),('unsigned short','u16'),('unsigned char','u8'),
                        ('signed char','s8'),('int','s32'),('short','s16')]:
            value=re.sub(r'\b'+old+r'\b',new,value)
        return re.sub(r'\s*\*\s*','*',value).strip()
    params=match[2].strip()
    if not params:raise ValueError('old-style unspecified parameters')
    return canonical(match[1])+'('+','.join(canonical(p,True) for p in params.split(','))+')'


def compatible_incomplete(declarations,typed_signature):
    """C89 f() does not assert zero arguments; use its actual compatibility rule."""
    if all(d['signature']==typed_signature for d in declarations):return True
    params=typed_signature[typed_signature.index('(')+1:-1].split(',')
    if params==['void']:params=[]
    if any('*' not in p and p not in ('s32','u32','long','unsigned long','double') for p in params):return False
    expected_return=typed_signature[:typed_signature.index('(')]
    for declaration in declarations:
        if declaration['signature']==typed_signature:continue
        if declaration['signature']!='UNRESOLVED: old-style unspecified parameters':return False
        text=declaration['definition'];name=declaration['name']
        explicit=dict(declaration,definition=text[:text.rfind('(')]+'(void)')
        if signature(explicit).split('(')[0]!=expected_return:return False
    return True


class HeaderSDK:
    def __init__(self,world,base):
        self.base=Path(base)
        cfg=self.base/'config/slus_006.14.yaml'
        symbols=self.base/'config/slus_006.14.symbols.txt'
        self.authorities={str(p.relative_to(self.base)):digest(p) for p in (cfg,symbols)}
        ranges=[]
        for parent in yaml.safe_load(cfg.read_text())['segments']:
            if not isinstance(parent,dict) or 'vram' not in parent:continue
            subs=parent.get('subsegments',[])
            for i,segment in enumerate(subs[:-1]):
                if not isinstance(segment,list) or len(segment)<3 or segment[1]!='asm' or not segment[2].startswith('psyq/'):continue
                end=subs[i+1][0] if isinstance(subs[i+1],list) else subs[i+1]['start']
                delta=parent['vram']-parent['start']
                ranges.append((segment[0]+delta,end+delta,segment[2]))
        self.symbols={}
        for match in re.finditer(r'^\s*(\w+)\s*=\s*(0x[\dA-Fa-f]+);[^\n]*type:func',symbols.read_text(),re.M):
            name,address=match[1],int(match[2],16)
            owners=[obj for lo,hi,obj in ranges if lo<=address<hi]
            if len(owners)==1:self.symbols.setdefault(address,dict(names=[],object=owners[0]))['names'].append(name)
        # Follow only include/ dependencies actually referenced by matched C,
        # including recipe -include arguments. Record a source witness per header.
        used={};todo=[]
        def enqueue(text,witness,parent=None):
            names=re.findall(r'^\s*#\s*include\s*[<"]([^>"\n]+)[>"]',text,re.M)
            names+=re.findall(r'(?:^|\s)-include\s+(\S+)',text)
            for name in names:
                paths=[self.base/'include'/name]
                if parent:paths.insert(0,parent/name)
                path=next((p for p in paths if p.is_file() and p.resolve().is_relative_to((self.base/'include').resolve())),None)
                if path is not None and path not in used:used[path]=witness;todo.append(path)
        for row in world.rows:
            if row['id'] not in world.text:continue
            enqueue(world.text[row['id']],row['id'])
            enqueue(str(row.get('flags','')),row['id'])
        while todo:
            p=todo.pop();enqueue(p.read_text(),used[p],p.parent)
        declarations={}
        for p,witness in used.items():
            original=p.read_text();text=re.sub(r'/\*.*?\*/|//[^\n]*','',original,flags=re.S)
            for m in re.finditer(r'^[ \t]*(?:extern\s+)?([A-Za-z_][\w \t*]*?)\b(\w+)\s*\(([^;{}]*)\)\s*;',text,re.M):
                contract=dict(source=str(p.relative_to(self.base)),name=m[2],
                    definition=' '.join((m[1]+m[2]+'('+m[3]+')').split()))
                try:key=signature(contract)
                except ValueError as error:key='UNRESOLVED: '+str(error)
                declarations.setdefault(m[2],[]).append(dict(contract,signature=key,matched_header_witness=witness,
                    header_sha256=digest(p),line=original[:original.find(m[2])].count('\n')+1))
        self.contracts={};self.report=[]
        for address,symbol in sorted(self.symbols.items()):
            names=set(symbol['names'])|{f'func_{address:08X}'}
            decls=[dict(d,row='sdk/'+symbol['names'][0]) for name in names for d in declarations.get(name,[])]
            signatures={d['signature'] for d in decls}
            typed={s for s in signatures if not s.startswith('UNRESOLVED:')}
            compatible=len(typed)==1 and compatible_incomplete(decls,next(iter(typed)))
            status='BOUND' if compatible else 'CONFLICT' if len(signatures)>1 else 'NO_USABLE_MATCHED_HEADER'
            record=dict(address=hex(address),**symbol,status=status,declarations=decls)
            if status=='BOUND':
                chosen=min((d for d in decls if not d['signature'].startswith('UNRESOLVED:')),key=lambda d:(d['source'],d['definition']))
                contract={k:chosen[k] for k in ('row','source','name','definition')}
                contract.update(binding='psyq-sdk-matched-header',sdk_address=hex(address),sdk_object=symbol['object'],
                    header_sha256=chosen['header_sha256'],matched_header_witness=chosen['matched_header_witness'],
                    agreeing_headers=sorted({d['source'] for d in decls}),sdk_authorities=self.authorities)
                self.contracts[address]=contract
            self.report.append(record)

    def get(self,address):
        contract=self.contracts.get(address)
        return dict(contract) if contract else None

    def proof(self,address,old,contract):
        if old is None or old!=address or contract.get('binding')!='psyq-sdk-matched-header':return None
        expected=self.get(address)
        if not expected or contract!=expected:return None
        return dict(binding='unchanged-resident-psyq-sdk-header',row=contract['row'],source=contract['source'],
            address=hex(address),definition=contract['definition'],header_sha256=contract['header_sha256'],
            matched_header_witness=contract['matched_header_witness'],sdk_object=contract['sdk_object'])


class SDK(HeaderSDK):
    """Decision 54: preserve a donor declaration, otherwise use PsyQ consensus.

    Canonical prototypes are declarations only. They never establish a C body,
    permit an SDK relocation, or substitute for any production byte gate.
    """
    def __init__(self, world, base):
        import collections, json
        super().__init__(world, base)
        self.world = world
        self.header_contracts = dict(self.contracts)
        self.canonical = json.loads(Path(__file__).with_name('psyq_prototypes.json').read_text())
        import zipfile
        archives={}
        for authority in self.canonical.values():
            archive=authority['archive'];member=authority['member']
            if archive not in archives:
                with zipfile.ZipFile(self.base/archive) as package:
                    archives[archive]={item['member']:package.read(item['member'])
                        for item in self.canonical.values() if item['archive']==archive}
            data=archives[archive][member]
            assert hashlib.sha256(data).hexdigest()==authority['member_sha256'],'PsyQ header authority drift'
            bare=re.sub(r'/\*.*?\*/|//[^\n]*','',data.decode('latin1'),flags=re.S)
            assert authority['definition'] in ' '.join(bare.split()),'PsyQ prototype authority drift'
        self.local = {}
        declarations = collections.defaultdict(list)
        pattern = r'^[ \t]*(?:extern\s+)?([A-Za-z_][\w \t*]*?)\b(\w+)\s*\(([^;{}]*)\)\s*;'
        byname = {name: addr for addr, sym in self.symbols.items()
                  for name in sym['names']+[f'func_{addr:08X}']}
        for row, source in world.text.items():
            bare = re.sub(r'/\*.*?\*/|//[^\n]*', '', source, flags=re.S)
            for match in re.finditer(pattern, bare, re.M):
                if match[1].strip() in ('return', 'break', 'goto'):
                    continue
                address = byname.get(match[2])
                if address is None:
                    continue
                contract = dict(name=match[2], definition=' '.join(
                    (match[1]+match[2]+'('+match[3]+')').split()), row=row,
                    source='src/'+row+'.c')
                try:
                    sig = self.abi(contract)
                except ValueError:
                    sig = 'UNRESOLVED'
                declarations[address].append(dict(contract, signature=sig))
                self.local.setdefault((row, address), []).append(contract)
        for record in self.report:
            address = int(record['address'], 0)
            name = record['names'][0]
            counts = collections.Counter(d['signature'] for d in declarations[address]
                                         if d['signature'] != 'UNRESOLVED')
            oldstyle=collections.Counter()
            for d in declarations[address]:
                if not re.search(r'\(\s*\)$',d['definition']):continue
                explicit=dict(d,definition=re.sub(r'\(\s*\)$','(void)',d['definition']))
                try:oldstyle[self.abi(explicit).split('(')[0]]+=1
                except ValueError:oldstyle['UNRESOLVED']+=1
            # An old-style declaration votes for its return type only. It can
            # agree with a canonical prototype only under C default promotions.
            canonical = self.canonical.get(name)
            sig = None
            if canonical:
                try:
                    sig = self.abi(canonical)
                except ValueError:
                    pass
            votes=self.consensus(declarations[address]+record['declarations'],sig)
            dominant = votes.most_common()
            record['matched_source_signatures'] = dict(counts)
            record['matched_oldstyle_returns'] = dict(oldstyle)
            record['matched_source_and_header_votes'] = dict(votes)
            record['canonical_authority'] = canonical
            record['prior_header_status'] = record['status']
            record['canonical_abi'] = sig
            agrees = bool(sig and dominant and dominant[0][0] == sig and
                          (len(dominant) == 1 or dominant[0][1] > dominant[1][1]))
            if name in ('rand', 'rsin'):
                agrees = True  # Explicit orchestrator decision, CONTINUE4.
                sig = 's32(void)' if name == 'rand' else 's32(s32)'
            if canonical and agrees:
                definition = self.portable(canonical['definition'])
                if name == 'rand': definition = 's32 rand(void)'
                if name == 'rsin': definition = 's32 rsin(s32)'
                self.contracts[address] = dict(row='sdk/'+name,
                    source=canonical['archive'], name=name, definition=definition,
                    binding='psyq-sdk-matched-header', sdk_address=hex(address),
                    sdk_object=record['object'], decision=54,
                    declaration_policy='canonical-PsyQ-dominant-matched',
                    canonical_authority=canonical, matched_source_signatures=dict(counts),
                    sdk_authorities=self.authorities)
                record['status'] = 'BOUND_CANONICAL'
            elif record['status'] == 'CONFLICT':
                record['status'] = 'HOLD_CANONICAL_DISAGREEMENT' if sig else 'HOLD_NO_TYPED_PSYQ_PROTOTYPE'
            record['donor_declarations'] = len(declarations[address])

    @classmethod
    def consensus(cls, declarations, canonical_signature):
        """Count matched source and header declarations under C89 compatibility.

        Unspecified parameters support a unique compatible typed signature;
        ambiguous or incompatible declarations remain separate vote buckets.
        This never changes the inherited declaration in a donor translation unit.
        """
        import collections
        typed=collections.Counter();oldstyle=collections.Counter()
        for declaration in declarations:
            try:typed[cls.abi(declaration)]+=1
            except ValueError:
                if not re.search(r'\(\s*\)$',declaration['definition']):continue
                explicit=dict(declaration,definition=re.sub(r'\(\s*\)$','(void)',declaration['definition']))
                try:oldstyle[cls.abi(explicit).split('(')[0]]+=1
                except ValueError:oldstyle['UNRESOLVED']+=1
        signatures=set(typed)
        if canonical_signature:signatures.add(canonical_signature)
        votes=typed.copy()
        for ret,count in oldstyle.items():
            compatible=[]
            for candidate in signatures:
                if candidate.split('(')[0]!=ret:continue
                params=candidate[candidate.index('(')+1:-1].split(',')
                if params==['void']:params=[]
                if all('*' in p or p in ('s32','u32','long','unsigned long','double') for p in params):compatible.append(candidate)
            key=compatible[0] if len(compatible)==1 else ret+'(unspecified)'
            votes[key]+=count
        return votes

    @staticmethod
    def portable(definition):
        for old, new in [('unsigned long', 'u32'), ('u_long', 'u32'),
                         ('u_short', 'u16'), ('long', 's32')]:
            definition = re.sub(r'\b'+old+r'\b', new, definition)
        # Independent translation units keep pointer pointees opaque, matching
        # the existing body-backed callee declaration rule.
        match = re.fullmatch(r'(.*?)\b(\w+)\s*\((.*)\)', definition)
        if not match:
            raise ValueError('unparsed prototype')
        ret = 'void *' if '*' in match[1] else match[1]
        params = ['void *' if '*' in p else p for p in match[3].split(',')]
        return ret+' '+match[2]+'('+','.join(params)+')'

    @classmethod
    def abi(cls, contract):
        from contracts import declaration
        value = dict(contract, definition=cls.portable(contract['definition']))
        # Preserve old-style return information without inventing an arity.
        if re.search(r'\(\s*\)$', value['definition']):
            raise ValueError('unspecified parameters')
        return signature(value)

    def get(self, address, donor=None):
        row = donor['id'] if isinstance(donor, dict) else donor
        own = self.local.get((row, address), []) if row else []
        if own:
            if len({d['definition'] for d in own}) != 1:
                return None
            declared = own[0]
            return dict(declared, binding='psyq-sdk-matched-header',
                sdk_address=hex(address), sdk_object=self.symbols[address]['object'],
                decision=54, declaration_policy='inherited-matched-donor-declaration',
                donor_row=row, donor_source_sha256=digest(self.base/declared['source']),
                sdk_authorities=self.authorities)
        return super().get(address)

    def proof(self, address, old, contract):
        if old != address or contract.get('binding') != 'psyq-sdk-matched-header':
            return None
        expected = self.get(address, contract.get('donor_row'))
        if not expected or contract != expected:
            return None
        return dict(binding='unchanged-resident-psyq-decision54', address=hex(address),
                    contract=contract)


if __name__=='__main__':
    import collections
    from twins import World,L,save
    world=World()
    save(L/'evidence/continue3/sdk_contracts.json',dict(symbols=world.sdk.report,authorities=world.sdk.authorities))
    print('SDK',dict(collections.Counter(r['status'] for r in world.sdk.report)))
    for address in (0x80069EF8,0x800644B8):print(hex(address),world.sdk.get(address))
