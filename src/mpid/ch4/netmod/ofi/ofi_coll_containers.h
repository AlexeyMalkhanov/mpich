#ifndef OFI_COLL_CONTAINERS_H_INCLUDED
#define OFI_COLL_CONTAINERS_H_INCLUDED

/* Barrier OFI containers declaration */
extern const MPIDI_OFI_coll_algo_container_t OFI_Barrier_intra_dissemination_cnt;

/* Bcast OFI containers declaration */
extern const MPIDI_OFI_coll_algo_container_t OFI_Bcast_intra_binomial_cnt;
extern const MPIDI_OFI_coll_algo_container_t
    OFI_Bcast_intra_scatter_recursive_doubling_allgather_cnt;
extern const MPIDI_OFI_coll_algo_container_t OFI_Bcast_intra_scatter_ring_allgather_cnt;

/* Reduce OFI containers declaration */
extern const MPIDI_OFI_coll_algo_container_t OFI_Reduce_intra_binomial_cnt;
extern const MPIDI_OFI_coll_algo_container_t OFI_Reduce_intra_reduce_scatter_gather_cnt;

/* Allreduce OFI containers declaration */
extern const MPIDI_OFI_coll_algo_container_t OFI_Allreduce_intra_recursive_doubling_cnt;
extern const MPIDI_OFI_coll_algo_container_t OFI_Allreduce_intra_reduce_scatter_allgather_cnt;

/* Alltoall OFI containers declaration */
extern const MPIDI_OFI_coll_algo_container_t OFI_Alltoall_intra_brucks_cnt;
extern const MPIDI_OFI_coll_algo_container_t OFI_Alltoall_intra_scattered_cnt;
extern const MPIDI_OFI_coll_algo_container_t OFI_Alltoall_intra_pairwise_cnt;
extern const MPIDI_OFI_coll_algo_container_t OFI_Alltoall_intra_pairwise_sendrecv_replace_cnt;

/* Alltoallv OFI containers declaration */
extern const MPIDI_OFI_coll_algo_container_t OFI_Alltoallv_intra_scattered_cnt;
extern const MPIDI_OFI_coll_algo_container_t OFI_Alltoallv_intra_pairwise_sendrecv_replace_cnt;

/* Alltoallw OFI containers declaration */
extern const MPIDI_OFI_coll_algo_container_t OFI_Alltoallw_intra_scattered_cnt;
extern const MPIDI_OFI_coll_algo_container_t OFI_Alltoallw_intra_pairwise_sendrecv_replace_cnt;

/* Allgather OFI containers declaration */
extern const MPIDI_OFI_coll_algo_container_t OFI_Allgather_intra_recursive_doubling_cnt;
extern const MPIDI_OFI_coll_algo_container_t OFI_Allgather_intra_brucks_cnt;
extern const MPIDI_OFI_coll_algo_container_t OFI_Allgather_intra_ring_cnt;

/* Allgatherv OFI containers declaration */
extern const MPIDI_OFI_coll_algo_container_t OFI_Allgatherv_intra_recursive_doubling_cnt;
extern const MPIDI_OFI_coll_algo_container_t OFI_Allgatherv_intra_brucks_cnt;
extern const MPIDI_OFI_coll_algo_container_t OFI_Allgatherv_intra_ring_cnt;

/* Gather OFI containers declaration */
extern const MPIDI_OFI_coll_algo_container_t OFI_Gather_intra_binomial_cnt;

/* Gatherv OFI containers declaration */
extern const MPIDI_OFI_coll_algo_container_t OFI_Gatherv_allcomm_linear_cnt;

/* Scatter OFI containers declaration */
extern const MPIDI_OFI_coll_algo_container_t OFI_Scatter_intra_binomial_cnt;

/* Scatterv OFI containers declaration */
extern const MPIDI_OFI_coll_algo_container_t OFI_Scatterv_allcomm_linear_cnt;

/* Reduce_scatter OFI containers declaration */
extern const MPIDI_OFI_coll_algo_container_t OFI_Reduce_scatter_intra_noncommutative_cnt;
extern const MPIDI_OFI_coll_algo_container_t OFI_Reduce_scatter_intra_pairwise_cnt;
extern const MPIDI_OFI_coll_algo_container_t OFI_Reduce_scatter_intra_recursive_doubling_cnt;
extern const MPIDI_OFI_coll_algo_container_t OFI_Reduce_scatter_intra_recursive_halving_cnt;

/* Reduce_scatter_block OFI containers declaration */
extern const MPIDI_OFI_coll_algo_container_t OFI_Reduce_scatter_block_intra_noncommutative_cnt;
extern const MPIDI_OFI_coll_algo_container_t OFI_Reduce_scatter_block_intra_pairwise_cnt;
extern const MPIDI_OFI_coll_algo_container_t OFI_Reduce_scatter_block_intra_recursive_doubling_cnt;
extern const MPIDI_OFI_coll_algo_container_t OFI_Reduce_scatter_block_intra_recursive_halving_cnt;

/* Scan OFI containers declaration */
extern const MPIDI_OFI_coll_algo_container_t OFI_Scan_intra_recursive_doubling_cnt;

/* Exscan OFI containers declaration */
extern const MPIDI_OFI_coll_algo_container_t OFI_Exscan_intra_recursive_doubling_cnt;

#endif /* OFI_COLL_CONTAINERS_H_INCLUDED */
