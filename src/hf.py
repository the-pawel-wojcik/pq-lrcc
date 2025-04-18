import pdaggerq

pq = pdaggerq.pq_helper("fermi")

print('')
print('    < 0 | H | 0> :')
print('')

pq.add_st_operator(1.0, ['f'], [])
pq.add_st_operator(1.0, ['v'], [])

pq.simplify()

if False:
    terms = pq.strings()
    for term in terms:
        print(term)
    
if True:
    options = {}
    graph = pdaggerq.pq_graph(options)

    graph.add(pq, "E_HF", ['a', 'b', 'i', 'j'])
    graph.optimize()

    graph.print('c++')
