from pathlib import Path
import sys,json
HERE=Path(__file__).resolve().parent
sys.path.insert(0,str(HERE.parent))
import probe as P
P.HERE=HERE
module=json.loads((HERE/'module.json').read_text())
stem='w_8003F240';P.RECIPES['src/'+stem+'.c']={'src':'src/'+stem+'.c','out':'build/src/'+stem+'.o','ccver':'2.7.2-cdk','ccflags':'-G32','asflags':''}
# Use a local include prefix for this independently retained variant.
source=HERE/'f240_owned.c'; local=HERE/'f240_expensive';local.mkdir(exist_ok=True)
(local/'include').symlink_to(HERE/'include') if not (local/'include').exists() else None
P.HERE=local
legs,report=P.compile_legs(stem,source,'candidate')
views={k:P.A.data_piece_view(v.obj,module) for k,v in legs.items()}
func=report['functions'][0];out=local/'objects'/stem/'candidate'
report['projected_retail']={k:P.B.retail_detail(v,func,P.EXTENTS[func],out,'projected_'+k,P.ALIGN) for k,v in views.items()}
report['projected_generic_vs_genuine']=P.B.compare(views['generic'],views['genuine'],[func])
(HERE/'f240_expensive_receipt.json').write_text(json.dumps(report,indent=2)+'\n')
print({k:(v['actual_words'],len(v['masked_indices']),v['exact_unmasked']) for k,v in report['projected_retail'].items()})
