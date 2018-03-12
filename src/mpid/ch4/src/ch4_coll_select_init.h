#ifndef CH4_COLL_SELECT_INIT_H_INCLUDED
#define CH4_COLL_SELECT_INIT_H_INCLUDED

#undef FUNCNAME
#define FUNCNAME MPIDI_CH4_mpi_comm_collective_selection_init
#undef FCNAME
#define FCNAME MPL_QUOTE(FUNCNAME)
MPL_STATIC_INLINE_PREFIX int MPIDI_CH4_mpi_comm_collective_selection_init(MPIR_Comm * comm)
{
    int mpi_errno = MPI_SUCCESS;

    MPIR_FUNC_VERBOSE_STATE_DECL(MPID_STATE_MPIDI_CH4_COMM_COLLECTIVE_SELECTION_INIT);
    MPIR_FUNC_VERBOSE_ENTER(MPID_STATE_MPIDI_COMM_CH4_COLLECTIVE_SELECTION_INIT);

    MPIR_FUNC_VERBOSE_EXIT(MPID_STATE_MPIDI_COMM_CH4_COLLECTIVE_SELECTION_INIT);
    return mpi_errno;
}

#undef FUNCNAME
#define FUNCNAME MPIDI_CH4_mpi_comm_collective_selection_finalize
#undef FCNAME
#define FCNAME MPL_QUOTE(FUNCNAME)
MPL_STATIC_INLINE_PREFIX int MPIDI_CH4_mpi_comm_collective_selection_finalize(MPIR_Comm * comm)
{
    int mpi_errno = MPI_SUCCESS;

    MPIR_FUNC_VERBOSE_STATE_DECL(MPID_STATE_MPIDI_CH4_COMM_COLLECTIVE_SELECTION_FINALIZE);
    MPIR_FUNC_VERBOSE_ENTER(MPID_STATE_MPIDI_COMM_CH4_COLLECTIVE_SELECTION_FINALIZE);

    MPIR_FUNC_VERBOSE_EXIT(MPID_STATE_MPIDI_COMM_CH4_COLLECTIVE_SELECTION_FINALIZE);
    return mpi_errno;
}

#endif /* CH4_COLL_SELECT_INIT_H_INCLUDED */
