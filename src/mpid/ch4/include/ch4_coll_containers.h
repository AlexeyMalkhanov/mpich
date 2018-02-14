#ifndef CH4_COLL_CONTAINERS_H_INCLUDED
#define CH4_COLL_CONTAINERS_H_INCLUDED

/* Barrier CH4 level containers declaration */
extern const MPIDI_coll_algo_container_t CH4_Barrier_intra_composition_alpha_cnt;
extern const MPIDI_coll_algo_container_t CH4_Barrier_intra_composition_beta_cnt;
#ifdef MPIDI_BUILD_CH4_SHM
extern const MPIDI_coll_algo_container_t CH4_Barrier_intra_composition_gamma_cnt;
#endif /*  MPIDI_BUILD_CH4_SHM */
extern const MPIDI_coll_algo_container_t CH4_Barrier_inter_composition_alpha_cnt;

/* Bcast  CH4 level containers declaration */
extern const MPIDI_coll_algo_container_t CH4_Bcast_intra_composition_alpha_cnt;
extern const MPIDI_coll_algo_container_t CH4_Bcast_intra_composition_beta_cnt;
extern const MPIDI_coll_algo_container_t CH4_Bcast_intra_composition_gamma_cnt;
#ifdef MPIDI_BUILD_CH4_SHM
extern const MPIDI_coll_algo_container_t CH4_Bcast_intra_composition_delta_cnt;
#endif /*  MPIDI_BUILD_CH4_SHM */
extern const MPIDI_coll_algo_container_t CH4_Bcast_inter_composition_alpha_cnt;

/* Reduce  CH4 level containers declaration */
extern const MPIDI_coll_algo_container_t CH4_Reduce_intra_composition_alpha_cnt;
extern const MPIDI_coll_algo_container_t CH4_Reduce_intra_composition_beta_cnt;
#ifdef MPIDI_BUILD_CH4_SHM
extern const MPIDI_coll_algo_container_t CH4_Reduce_intra_composition_gamma_cnt;
#endif /*  MPIDI_BUILD_CH4_SHM */
extern const MPIDI_coll_algo_container_t CH4_Reduce_inter_composition_alpha_cnt;

/* Allreduce  CH4 level containers declaration */
extern const MPIDI_coll_algo_container_t CH4_Allreduce_intra_composition_alpha_cnt;
extern const MPIDI_coll_algo_container_t CH4_Allreduce_intra_composition_beta_cnt;
#ifdef MPIDI_BUILD_CH4_SHM
extern const MPIDI_coll_algo_container_t CH4_Allreduce_intra_composition_gamma_cnt;
#endif /*  MPIDI_BUILD_CH4_SHM */
extern const MPIDI_coll_algo_container_t CH4_Allreduce_inter_composition_alpha_cnt;

#endif /* CH4_COLL_CONTAINERS_H_INCLUDED */
