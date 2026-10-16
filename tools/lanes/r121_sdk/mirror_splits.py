"""Mirror proven C extents into independently exported production split lists.

Only empty active extents can gain a record. Existing records, including
historical reruns, retain their exact bytes. Rollback follows canonical splits.
"""
import collections,functools,json,re
from pathlib import Path

MARK='r121_twins2_mirror_of'


@functools.lru_cache(maxsize=1024)
def split_source(root,window):
    import yaml
    return yaml.safe_load((root/'config/overlays'/window).read_text())['standalone_build']['split_results']


def plan(root,row,windows):
    targets=set()
    canonical=f"overlays/{row['container']}/overlay_first_pass_results.json"
    for window in windows:
        split=split_source(root,window)
        if Path(split).as_posix()==canonical:continue
        match=re.fullmatch(r'overlays/([a-z0-9_]+)/overlay_first_pass_results\.json',split)
        if not match:raise ValueError('independent production split source has no ordinary ledger mapping')
        rel=f'ledger/splits/{match[1]}.jsonl';path=root/rel
        if not path.is_file():raise ValueError('independent production split ledger is absent')
        entries=[json.loads(s) for s in path.read_text().splitlines() if s.strip() and not s.startswith('#')]
        active=[s for s in entries if not s.get('rerun') and s['foff']<row['foff']+row['size'] and row['foff']<s['foff']+s['size']]
        if len(active)==1 and (active[0]['foff'],active[0]['size'])==(row['foff'],row['size']) and active[0].get(MARK)==row['id']:continue
        if active:raise ValueError('independent production split extent overlaps existing ownership')
        targets.add(rel)
    return sorted(targets)


def rewrite(before,records):
    lines=before.decode().splitlines(keepends=True);retained=[];active=[]
    for line in lines:
        if line.strip() and not line.startswith('#'):
            record=json.loads(line)
            if record.get(MARK):continue
            if not record.get('rerun'):active.append(record)
        retained.append(line)
    payload=[]
    for record in sorted(records,key=lambda r:(r['foff'],r['func_vram'])):
        assert record.get(MARK) and record.get('mirror_split_ledgers') is None
        if any(s['foff']<record['foff']+record['size'] and record['foff']<s['foff']+s['size'] for s in active):
            raise ValueError('mirror append would overlap active split ownership')
        active.append(record);payload.append(json.dumps(record,separators=(',',':'))+'\n')
    base=''.join(retained)
    if base and not base.endswith('\n'):raise ValueError('mirror ledger needs a terminal newline')
    return (base+''.join(payload)).encode()


def sync(root):
    wanted=collections.defaultdict(list)
    for container in ('dungeon','town','main','ovmovie'):
        for line in (root/f'ledger/splits/{container}.jsonl').read_text().splitlines():
            if '"mirror_split_ledgers"' not in line or line.startswith('#'):continue
            row=json.loads(line)
            for rel in row.get('mirror_split_ledgers',[]):
                if not re.fullmatch(r'ledger/splits/[a-z0-9_]+\.jsonl',rel):raise ValueError('invalid mirror ledger path')
                mirrored=dict(row);mirrored.pop('mirror_split_ledgers');mirrored[MARK]=container+'/'+row['func_vram']
                wanted[rel].append(mirrored)
    # Also remove provisional mirrors when their canonical transaction rolls back.
    for path in (root/'ledger/splits').glob('*.jsonl'):
        if path.stem in ('dungeon','town','main','ovmovie'):continue
        before=path.read_bytes();rel=str(path.relative_to(root))
        if rel not in wanted and MARK.encode() not in before:continue
        after=rewrite(before,wanted[rel])
        if after!=before:
            temp=path.with_name(path.name+'.mirror-tmp');temp.write_bytes(after);temp.replace(path)


def self_test():
    import tempfile
    raw=dict(func_vram='old',foff=0,size=8,result='MATCH')
    historical=dict(func_vram='history',foff=8,size=100,result='M2C_FAIL',rerun=True)
    before=b'# preserve\n'+(''.join(json.dumps(s)+'\n' for s in (raw,historical))).encode()
    new=dict(func_vram='new',foff=8,size=8,result='MATCH',r121_twins2_mirror_of='fixture/new')
    after=rewrite(before,[new]);assert after.startswith(before)
    assert rewrite(after,[new])==after
    assert rewrite(after,[])==before
    for bad in (dict(new,foff=4),dict(new,foff=0)):
        try:rewrite(before,[bad])
        except ValueError:pass
        else:raise AssertionError('active ownership was overwritten')
    try:rewrite(before,[new,new])
    except ValueError:pass
    else:raise AssertionError('duplicate mirror accepted')
    with tempfile.TemporaryDirectory(dir=Path(__file__).resolve().parents[1]/'tmp') as temp:
        root=Path(temp);(root/'ledger/splits').mkdir(parents=True)
        for container in ('dungeon','town','main','ovmovie'):
            (root/f'ledger/splits/{container}.jsonl').write_text('')
        mirror=root/'ledger/splits/dungeon_engine.jsonl';mirror.write_bytes(before)
        config=root/'config/overlays/fixture.overlay.yaml';config.parent.mkdir(parents=True)
        config.write_text('standalone_build:\n  split_results: overlays/dungeon_engine/overlay_first_pass_results.json\n')
        row=dict(id='dungeon/new',container='dungeon',foff=8,size=8)
        rel='ledger/splits/dungeon_engine.jsonl'
        assert plan(root,row,{'fixture.overlay.yaml'})==[rel]
        canonical=dict(new);canonical.pop(MARK);canonical['mirror_split_ledgers']=[rel]
        primary=root/'ledger/splits/dungeon.jsonl';primary.write_text(json.dumps(canonical)+'\n')
        sync(root);admitted=mirror.read_bytes();assert admitted.startswith(before)
        sync(root);assert mirror.read_bytes()==admitted
        assert plan(root,row,{'fixture.overlay.yaml'})==[]
        primary.write_text('');sync(root);assert mirror.read_bytes()==before
        for protected in (dict(raw,foff=8),dict(raw,foff=8,data_segment=True,result='data')):
            mirror.write_text(json.dumps(protected)+'\n')
            try:plan(root,row,{'fixture.overlay.yaml'})
            except ValueError:pass
            else:raise AssertionError('mirror plan replaced existing C/data')
    print('mirror split append/rollback: 13 checks PASS')


if __name__=='__main__':self_test()
