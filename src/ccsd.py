import pdaggerq

pq = pdaggerq.pq_helper("fermi")

print('')
print('    < 0 | e(-T) H e(T) | 0> :')
print('')

pq.add_st_operator(1.0, ['f'], ['t1','t2'])
pq.add_st_operator(1.0, ['v'], ['t1','t2'])

pq.simplify()

if False:
    terms = pq.strings()
    for term in terms:
        print(term)
    
if True:
    options = {
        'permute_eri': True,
    }
    graph = pdaggerq.pq_graph(options)

    # graph.add(pq, "E_CC", ['a', 'b', 'i', 'j'])
    graph.add(pq, "E_CC", [])
    graph.optimize()

    graph.print('c++')
