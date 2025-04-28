
/////////////////// PQ GRAPH ///////////////////

Options:
--------
    print_level: 0  // verbosity level:
                    // 0: no printing of optimization steps (default)
                    // 1: print optimization steps without fusion or merging
                    // 2: print optimization steps with fusion and merging
    permute_eri: true  // whether to permute two-electron integrals to common order (default: true)
    no_scalars: false  // whether to skip the scalar terms in the final equations (default: false)
    use_trial_index: false  // whether to store trial vectors as an additional index/dimension for tensors in a sigma-vector build (default: false)
    separate_sigma: false  // whether to separate reusable intermediates for sigma-vector build (default: false)
    opt_level: 6  // optimization level:
                  // 0: no optimization
                  // 1: single-term optimization only (reordering)
                  // 2: reordering and subexpression elimination (substitution)
                  // 3: reordering, substitution, and separation of reusable intermediates (for sigma vectors)
                  // 4: reordering, substitution, and separation; unused intermediates are removed (pruning)
                  // 5: reordering, substitution, separation, pruning, and merging of equivalent terms
                  // 6: reordering, substitution, separation, pruning, merging, and fusion of intermediates (default)
    batched: false  // candidate substitutions are applied in batches rather than one at a time. (default: false)
                   // Generally faster, but may not yield optimal results compared to single substitutions.
    batch_size: 10  // size of the batch for batched substitution (default: 10; -1 for no limit)
    max_temps: -1  // maximum number of intermediates to find (default: -1 for no limit)
    max_depth: -1  // maximum depth for chain of contractions (default: -1 for no limit)
    max_shape: o255v255 // a map of maximum sizes for each line type in an intermediate (default: {o: 255, v: 255}, for no limit.): 
    low_memory: false  // whether to recompute or save all possible permutations of each term in memory (default: false)
                       // if true, permutations are recomputed on the fly. Recommended if memory runs out.
    nthreads: 1  // number of threads to use (default: OMP_NUM_THREADS | available: 24)

Using custom label order: i a 
Formatting equations for c++

/////////////////// PQ GRAPH Output ///////////////////

///// Declarations /////

// initialize -> cc_jacobian;
// initialize -> eri["oovv"];
// initialize -> f["ov"];
// initialize -> perm_tmps;
// initialize -> t1;
// initialize -> tmps;

/////////////////// Evaluate Equations ///////////////////

    
    // cc_jacobian  = +1.00 f(i,a) 
    cc_jacobian("i,a")  = f["ov"]("i,a");
    
    // cc_jacobian += -1.00 <j,i||a,b> t1(b,j) 
    // flops: o1v1 += o2v2
    //  mems: o1v1 += o1v1
    cc_jacobian("i,a") += eri["oovv"]("i,j,a,b") * t1("b,j");

/////////////////////////////////////////////////////////


/////////////////// PQ GRAPH Analysis ///////////////////

Net time: 2.093 ms

Total Number of Terms: 2
Total Contractions: (last) 3 -> (new) 3

Total FLOP scaling: 
------------------
 Scaling :   I   |   R   |   F   ||  F-I  |  F-R 
-------- : ----- | ----- | ----- || ----- |  ----
    o2v2 :     1 |     1 |     1 ||     0 |     0 
-------- : ----- | ----- | ----- || ----- |  ----
    o1v1 :     2 |     2 |     2 ||     0 |     0 
-------- : ----- | ----- | ----- || ----- |  ----
   Total :     3 |     3 |     3 ||     0 |     0 

Total MEM scaling: 
------------------
 Scaling :   I   |   R   |   F   ||  F-I  |  F-R 
-------- : ----- | ----- | ----- || ----- |  ----
    o1v1 :     3 |     3 |     3 ||     0 |     0 
-------- : ----- | ----- | ----- || ----- |  ----
   Total :     3 |     3 |     3 ||     0 |     0 


/////////////////////////////////////////////////////////

