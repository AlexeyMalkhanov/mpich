/* -*- Mode: C ; c-basic-offset:4 ; indent-tabs-mode:nil ; -*- */
/*
 *  (C) 2006 by Argonne National Laboratory.
 *      See COPYRIGHT in top-level directory.
 *
 *  Portions of this code were written by Intel Corporation.
 *  Copyright (C) 2011-2016 Intel Corporation.  Intel provides this material
 *  to Argonne National Laboratory subject to Software Grant and Corporate
 *  Contributor License Agreement dated February 8, 2012.
 */
#ifndef CH4_COLL_SELECT_H_INCLUDED
#define CH4_COLL_SELECT_H_INCLUDED

#include "ch4_impl.h"
#include "ch4r_proc.h"
#include "ch4_coll_impl.h"

#ifdef MPIDI_BUILD_CH4_SHM
#include "../shm/include/shm.h"
#endif

#include "coll_util.h"

MPL_STATIC_INLINE_PREFIX
MPIDI_coll_algo_container_t * MPIDI_CH4_Barrier_select(MPIR_Comm * comm,
                                                       MPIR_Errflag_t * errflag)
{
    if (comm->comm_kind == MPIR_COMM_KIND__INTERCOMM) {
        return (MPIDI_coll_algo_container_t *) &CH4_Barrier_intercomm_cnt;
    }

    if (MPIR_CVAR_ENABLE_SMP_COLLECTIVES && MPIR_CVAR_ENABLE_SMP_BARRIER &&
        MPIR_Comm_is_node_aware(comm)) {
        return (MPIDI_coll_algo_container_t *) &CH4_Barrier_composition_alpha_cnt;
    }

    return (MPIDI_coll_algo_container_t *) &CH4_Barrier_composition_beta_cnt;
}

MPL_STATIC_INLINE_PREFIX
MPIDI_coll_algo_container_t * MPIDI_CH4_Bcast_select(void *buffer,
                                                     int count,
                                                     MPI_Datatype datatype,
                                                     int root,
                                                     MPIR_Comm * comm,
                                                     MPIR_Errflag_t * errflag)
{
    int nbytes = 0;
    MPI_Aint type_size = 0;

    MPIR_Datatype_get_size_macro(datatype, type_size);

    if (comm->comm_kind == MPIR_COMM_KIND__INTERCOMM) {
        return (MPIDI_coll_algo_container_t *) &CH4_Bcast_intercomm_cnt;
    }

    nbytes = MPIR_CVAR_MAX_SMP_BCAST_MSG_SIZE ? type_size * count : 0;
    if (MPIR_CVAR_ENABLE_SMP_COLLECTIVES && MPIR_CVAR_ENABLE_SMP_BCAST &&
        nbytes <= MPIR_CVAR_MAX_SMP_BCAST_MSG_SIZE && MPIR_Comm_is_node_aware(comm)) {
        if ((nbytes < MPIR_CVAR_BCAST_SHORT_MSG_SIZE) ||
            (comm->local_size < MPIR_CVAR_BCAST_MIN_PROCS)) {
            return (MPIDI_coll_algo_container_t *) &CH4_Bcast_composition_alpha_cnt;
        } else {
            if (nbytes < MPIR_CVAR_BCAST_LONG_MSG_SIZE && MPIU_is_pof2(comm->local_size, NULL)) {
                return (MPIDI_coll_algo_container_t *) &CH4_Bcast_composition_beta_cnt;
            }
        }
    }
    return (MPIDI_coll_algo_container_t *) &CH4_Bcast_composition_gamma_cnt;
}

MPL_STATIC_INLINE_PREFIX
MPIDI_coll_algo_container_t * MPIDI_CH4_Allreduce_select(const void *sendbuf,
                                                         void *recvbuf,
                                                         int count,
                                                         MPI_Datatype
                                                         datatype,
                                                         MPI_Op op,
                                                         MPIR_Comm * comm,
                                                         MPIR_Errflag_t * errflag)
{
    MPI_Aint type_size = 0;
    int nbytes = 0;
    int is_commutative = -1;

    is_commutative = MPIR_Op_is_commutative(op);
    if (comm->comm_kind == MPIR_COMM_KIND__INTERCOMM) {
        return (MPIDI_coll_algo_container_t *) &CH4_Allreduce_intercomm_cnt;
    }

    if (MPIR_CVAR_ENABLE_SMP_COLLECTIVES && MPIR_CVAR_ENABLE_SMP_ALLREDUCE) {
        /* is the op commutative? We do SMP optimizations only if it is. */
        MPIR_Datatype_get_size_macro(datatype, type_size);
        nbytes = MPIR_CVAR_MAX_SMP_ALLREDUCE_MSG_SIZE ? type_size * count : 0;
        if (MPIR_Comm_is_node_aware(comm) && is_commutative &&
            nbytes <= MPIR_CVAR_MAX_SMP_ALLREDUCE_MSG_SIZE) {
            return (MPIDI_coll_algo_container_t *) &CH4_Allreduce_composition_alpha_cnt;
        }
    }
    return (MPIDI_coll_algo_container_t *) &CH4_Allreduce_composition_beta_cnt;
}

MPL_STATIC_INLINE_PREFIX
MPIDI_coll_algo_container_t * MPIDI_CH4_Reduce_select(const void *sendbuf,
                                                      void *recvbuf,
                                                      int count,
                                                      MPI_Datatype datatype,
                                                      MPI_Op op, int root,
                                                      MPIR_Comm * comm,
                                                      MPIR_Errflag_t * errflag)
{
    int is_commutative = -1;
    MPI_Aint type_size = 0;
    int nbytes = 0;
    MPIR_Op * op_ptr = NULL;

    if (comm->comm_kind == MPIR_COMM_KIND__INTERCOMM) {
        return (MPIDI_coll_algo_container_t *) &CH4_Reduce_intercomm_cnt;
    }

    if (MPIR_CVAR_ENABLE_SMP_COLLECTIVES && MPIR_CVAR_ENABLE_SMP_REDUCE) {
        /* is the op commutative? We do SMP optimizations only if it is. */
        if (HANDLE_GET_KIND(op) == HANDLE_KIND_BUILTIN) {
            is_commutative = 1;
        } else {
            MPIR_Op_get_ptr(op, op_ptr);
            is_commutative = (op_ptr->kind == MPIR_OP_KIND__USER_NONCOMMUTE) ? 0 : 1;
        }

        MPIR_Datatype_get_size_macro(datatype, type_size);
        nbytes = MPIR_CVAR_MAX_SMP_REDUCE_MSG_SIZE ? type_size * count : 0;
        if (MPIR_Comm_is_node_aware(comm) && is_commutative &&
            nbytes <= MPIR_CVAR_MAX_SMP_REDUCE_MSG_SIZE) {
            return (MPIDI_coll_algo_container_t *) &CH4_Reduce_composition_alpha_cnt;
        }
    }
    return (MPIDI_coll_algo_container_t *) &CH4_Reduce_composition_beta_cnt;
}

MPL_STATIC_INLINE_PREFIX
MPIDI_coll_algo_container_t * MPIDI_CH4_Gather_select(const void *sendbuf,
                                                      int sendcount,
                                                      MPI_Datatype sendtype,
                                                      void *recvbuf,
                                                      int recvcount,
                                                      MPI_Datatype recvtype,
                                                      int root,
                                                      MPIR_Comm * comm,
                                                      MPIR_Errflag_t * errflag)
{
    if (comm->comm_kind == MPIR_COMM_KIND__INTERCOMM) {
        return (MPIDI_coll_algo_container_t *) &CH4_Gather_intercomm_cnt;
    }

    return (MPIDI_coll_algo_container_t *) &CH4_Gather_composition_alpha_cnt;
}

MPL_STATIC_INLINE_PREFIX
MPIDI_coll_algo_container_t * MPIDI_CH4_Gatherv_select(const void *sendbuf,
                                                       int sendcount,
                                                       MPI_Datatype sendtype,
                                                       void *recvbuf,
                                                       const int *recvcounts,
                                                       const int *displs,
                                                       MPI_Datatype recvtype,
                                                       int root,
                                                       MPIR_Comm * comm,
                                                       MPIR_Errflag_t * errflag)
{
    if (comm->comm_kind == MPIR_COMM_KIND__INTERCOMM) {
        return (MPIDI_coll_algo_container_t *) &CH4_Gatherv_intercomm_cnt;
    }

    return (MPIDI_coll_algo_container_t *) &CH4_Gatherv_composition_alpha_cnt;
}

MPL_STATIC_INLINE_PREFIX
MPIDI_coll_algo_container_t * MPIDI_CH4_Scatter_select(const void *sendbuf,
                                                       int sendcount,
                                                       MPI_Datatype sendtype,
                                                       void *recvbuf,
                                                       int recvcount,
                                                       MPI_Datatype recvtype,
                                                       int root,
                                                       MPIR_Comm * comm,
                                                       MPIR_Errflag_t * errflag)
{

    if (comm->comm_kind == MPIR_COMM_KIND__INTERCOMM) {
        return (MPIDI_coll_algo_container_t *) &CH4_Scatter_intercomm_cnt;
    }

    return (MPIDI_coll_algo_container_t *) &CH4_Scatter_composition_alpha_cnt;
}

MPL_STATIC_INLINE_PREFIX
MPIDI_coll_algo_container_t * MPIDI_CH4_Scatterv_select(const void *sendbuf,
                                                        const int *sendcounts,
                                                        const int *displs,
                                                        MPI_Datatype sendtype,
                                                        void *recvbuf,
                                                        int recvcount,
                                                        MPI_Datatype recvtype,
                                                        int root,
                                                        MPIR_Comm * comm,
                                                        MPIR_Errflag_t * errflag)
{

    if (comm->comm_kind == MPIR_COMM_KIND__INTERCOMM) {
        return (MPIDI_coll_algo_container_t *) &CH4_Scatterv_intercomm_cnt;
    }

    return (MPIDI_coll_algo_container_t *) & CH4_Scatterv_composition_alpha_cnt;
}

MPL_STATIC_INLINE_PREFIX
MPIDI_coll_algo_container_t * MPIDI_CH4_Alltoall_select(const void *sendbuf,
                                                        int sendcount,
                                                        MPI_Datatype sendtype,
                                                        void *recvbuf,
                                                        int recvcount,
                                                        MPI_Datatype recvtype,
                                                        MPIR_Comm * comm,
                                                        MPIR_Errflag_t * errflag)
{
    if (comm->comm_kind == MPIR_COMM_KIND__INTERCOMM) {
        return (MPIDI_coll_algo_container_t *) &CH4_Alltoall_intercomm_cnt;
    }

    return (MPIDI_coll_algo_container_t *) &CH4_Alltoall_composition_alpha_cnt;
}

MPL_STATIC_INLINE_PREFIX
MPIDI_coll_algo_container_t * MPIDI_CH4_Alltoallv_select(const void *sendbuf, const int *sendcounts,
                                                         const int *sdispls, MPI_Datatype sendtype,
                                                         void *recvbuf, const int *recvcounts,
                                                         const int *rdispls, MPI_Datatype recvtype,
                                                         MPIR_Comm *comm, MPIR_Errflag_t *errflag)
{
    if (comm->comm_kind == MPIR_COMM_KIND__INTERCOMM) {
        return (MPIDI_coll_algo_container_t *) & CH4_Alltoallv_intercomm_cnt;
    }

    return (MPIDI_coll_algo_container_t *) & CH4_Alltoallv_composition_alpha_cnt;
}

MPL_STATIC_INLINE_PREFIX
MPIDI_coll_algo_container_t * MPIDI_CH4_Alltoallw_select(const void *sendbuf, const int sendcounts[],
                                                         const int sdispls[], const MPI_Datatype sendtypes[],
                                                         void *recvbuf, const int recvcounts[],
                                                         const int rdispls[], const MPI_Datatype recvtypes[],
                                                         MPIR_Comm *comm, MPIR_Errflag_t *errflag)
{
    if (comm->comm_kind == MPIR_COMM_KIND__INTERCOMM) {
        return (MPIDI_coll_algo_container_t *) & CH4_Alltoallw_intercomm_cnt;
    }

    return (MPIDI_coll_algo_container_t *) & CH4_Alltoallw_composition_alpha_cnt;
}

MPL_STATIC_INLINE_PREFIX
MPIDI_coll_algo_container_t * MPIDI_CH4_Allgather_select(const void *sendbuf, int sendcount,
                                                         MPI_Datatype sendtype, void *recvbuf,
                                                         int recvcount, MPI_Datatype recvtype,
                                                         MPIR_Comm * comm, MPIR_Errflag_t * errflag)
{
    if (comm->comm_kind == MPIR_COMM_KIND__INTERCOMM) {
        return (MPIDI_coll_algo_container_t *) & CH4_Allgather_intercomm_cnt;
    }

    return (MPIDI_coll_algo_container_t *) & CH4_Allgather_composition_alpha_cnt;
}

MPL_STATIC_INLINE_PREFIX
MPIDI_coll_algo_container_t * MPIDI_CH4_Allgatherv_select(const void *sendbuf, int sendcount,
                                                          MPI_Datatype sendtype, void *recvbuf,
                                                          const int *recvcounts, const int *displs,
                                                          MPI_Datatype recvtype, MPIR_Comm *comm,
                                                          MPIR_Errflag_t *errflag)
{
    if (comm->comm_kind == MPIR_COMM_KIND__INTERCOMM) {
        return (MPIDI_coll_algo_container_t *) &CH4_Allgatherv_intercomm_cnt;
    }

    return (MPIDI_coll_algo_container_t *) &CH4_Allgatherv_composition_alpha_cnt;
}

MPL_STATIC_INLINE_PREFIX
MPIDI_coll_algo_container_t * MPIDI_CH4_Reduce_scatter_select(const void *sendbuf,
                                                              void *recvbuf,
                                                              const int recvcounts[],
                                                              MPI_Datatype datatype,
                                                              MPI_Op op, MPIR_Comm * comm,
                                                              MPIR_Errflag_t * errflag)
{

    if (comm->comm_kind == MPIR_COMM_KIND__INTERCOMM) {
        return (MPIDI_coll_algo_container_t *) & CH4_Reduce_scatter_intercomm_cnt;
    }

    return (MPIDI_coll_algo_container_t *) & CH4_Reduce_scatter_composition_alpha_cnt;
}

MPL_STATIC_INLINE_PREFIX
MPIDI_coll_algo_container_t * MPIDI_CH4_Reduce_scatter_block_select(const void *sendbuf,
                                                                    void *recvbuf,
                                                                    int recvcount,
                                                                    MPI_Datatype datatype,
                                                                    MPI_Op op, MPIR_Comm * comm,
                                                                    MPIR_Errflag_t * errflag)
{

    if (comm->comm_kind == MPIR_COMM_KIND__INTERCOMM) {
        return (MPIDI_coll_algo_container_t *) & CH4_Reduce_scatter_block_intercomm_cnt;
    }

    return (MPIDI_coll_algo_container_t *) & CH4_Reduce_scatter_block_composition_alpha_cnt;
}

MPL_STATIC_INLINE_PREFIX
MPIDI_coll_algo_container_t * MPIDI_CH4_Scan_select(const void *sendbuf,
                                                    void *recvbuf,
                                                    int count,
                                                    MPI_Datatype datatype,
                                                    MPI_Op op, MPIR_Comm * comm,
                                                    MPIR_Errflag_t * errflag)
{
    if (MPII_Comm_is_node_consecutive(comm)) {
        return (MPIDI_coll_algo_container_t *) & CH4_Scan_composition_alpha_cnt;
    }

    return (MPIDI_coll_algo_container_t *) & CH4_Scan_composition_beta_cnt;
}

MPL_STATIC_INLINE_PREFIX
MPIDI_coll_algo_container_t * MPIDI_CH4_Exscan_select(const void *sendbuf,
                                                      void *recvbuf,
                                                      int count,
                                                      MPI_Datatype datatype,
                                                      MPI_Op op, MPIR_Comm * comm,
                                                      MPIR_Errflag_t * errflag)
{
    return (MPIDI_coll_algo_container_t *) & CH4_Exscan_composition_alpha_cnt;
}

#endif /* CH4_COLL_SELECT_H_INCLUDED */
