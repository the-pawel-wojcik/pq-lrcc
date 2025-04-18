
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

Using custom label order: a b i j 
Formatting equations for c++

/////////////////// PQ GRAPH Output ///////////////////

///// Declarations /////

// initialize -> E_HF;
// initialize -> Id["oo"];
// initialize -> eri["oooo"];
// initialize -> f["oo"];
// initialize -> perm_tmps;
// initialize -> tmps;

///// Scalars /////

    scalars_["1"]  = 1.00 * dot(Id["oo"]("i,j") * eri["oooo"]("k,i,l,j"), Id["oo"]("k,l"));
    scalars_["2"]  = 1.00 * dot(Id["oo"]("i,j"), f["oo"]("i,j"));
    scalars_["3"]  = -0.50 * scalars_["1"];
    scalars_["3"] += scalars_["2"];

///// End of Scalars /////

/////////////////// Evaluate Equations ///////////////////

    
    // E_HF  = +1.00 f(i,i) 
    //      += -0.50 <j,i||j,i> 
    E_HF  = scalars_["3"];

/////////////////////////////////////////////////////////



    < 0 | H | 0> :

