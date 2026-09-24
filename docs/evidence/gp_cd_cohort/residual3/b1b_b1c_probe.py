from pathlib import Path
import sys,json
HERE=Path(__file__).resolve().parent
sys.path.insert(0,str(HERE.parent))
import probe as P
local=HERE/'b1b_b1c_table';local.mkdir(exist_ok=True)
if not (local/'include').exists():(local/'include').symlink_to(HERE/'include')
P.HERE=local
stem='w_80048DA0'
P.RECIPES['src/'+stem+'.c']={'src':'src/'+stem+'.c','out':'build/src/'+stem+'.o','ccver':'2.8.1','ccflags':'','asflags':''}
module=json.loads((HERE/'module.json').read_text())
module['data']=[{'symbol':'D_80080B1B','asset':'assets/54240.bin','offset':0xDB,'size':1,'vram':0x80080B1B,'bytes':'00','section':'.sdata.D_80080B1B'}, {'symbol':'D_80080B1C','asset':'assets/54240.bin','offset':0xDC,'size':1,'vram':0x80080B1C,'bytes':'00','section':'.sdata.D_80080B1C'}]
module['data_pieces']=[{'symbol':n,'source_section':'.sdata','alignment':1} for n in ['D_80080B1B','D_80080B1C']]
legs,report=P.compile_legs(stem,HERE/'b1b_b1c_table.c','candidate')
views={k:P.A.data_piece_view(v.obj,module) for k,v in legs.items()}
out=local/'objects'/stem/'candidate'
report['projected_retail']={k:{f:P.B.retail_detail(v,f,P.EXTENTS[f],out,'projected_'+k,P.ALIGN) for f in report['functions']} for k,v in views.items()}
report['projected_generic_vs_genuine']=P.B.compare(views['generic'],views['genuine'],report['functions'])
(HERE/'b1b_b1c_table_receipt.json').write_text(json.dumps(report,indent=2)+'\n')
print({k:{f:(r['actual_words'],r['exact_unmasked']) for f,r in v.items()} for k,v in report['projected_retail'].items()})
