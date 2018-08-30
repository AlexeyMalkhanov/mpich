#ifndef MPIU_SELECTION_H_INCLUDED
#define MPIU_SELECTION_H_INCLUDED

#include <sys/stat.h>
#include "mpiimpl.h"
#include "coll_tree_bin_types.h"
#include "coll_tree_bin_from_cvars.h"

/*
=== BEGIN_MPI_T_CVAR_INFO_BLOCK ===

cvars:
    - name        : MPIR_CVAR_TUNING_JSON_FILE
      category    : COLLECTIVE
      type        : string
      default     : NULL
      class       : device
      verbosity   : MPI_T_VERBOSITY_USER_BASIC
      scope       : MPI_T_SCOPE_ALL_EQ
      description : >-
        Defines the name of json tuning file

    - name        : MPIR_CVAR_TUNING_BIN_FILE
      category    : COLLECTIVE
      type        : string
      default     : NULL
      class       : device
      verbosity   : MPI_T_VERBOSITY_USER_BASIC
      scope       : MPI_T_SCOPE_ALL_EQ
      description : >-
        Defines the name of bin tuning file

    - name        : MPIR_CVAR_TUNING_JSON_FILE_DUMP
      category    : COLLECTIVE
      type        : string
      default     : NULL
      class       : device
      verbosity   : MPI_T_VERBOSITY_USER_BASIC
      scope       : MPI_T_SCOPE_ALL_EQ
      description : >-
        Defines the name of tuning file to dump

    - name        : MPIR_CVAR_TUNING_BIN_FILE_DUMP
      category    : COLLECTIVE
      type        : string
      default     : NULL
      class       : device
      verbosity   : MPI_T_VERBOSITY_USER_BASIC
      scope       : MPI_T_SCOPE_ALL_EQ
      description : >-
        Defines the name of binary tuning file to dump

=== END_MPI_T_CVAR_INFO_BLOCK ===
*/

char *MPIU_SELECTION_coll_names[] = {
    "ALLGATHER",
    "ALLGATHERV",
    "ALLREDUCE",
    "ALLTOALL",
    "ALLTOALLV",
    "ALLTOALLW",
    "BARRIER",
    "BCAST",
    "EXSCAN",
    "GATHER",
    "GATHERV",
    "REDUCE_SCATTER",
    "REDUCE",
    "SCAN",
    "SCATTER",
    "SCATTERV",
    "REDUCE_SCATTER_BLOCK",
    "IALLGATHER",
    "IALLGATHERV",
    "IALLREDUCE",
    "IALLTOALL",
    "IALLTOALLV",
    "IALLTOALLW",
    "IBARRIER",
    "IBCAST",
    "IEXSCAN",
    "IGATHER",
    "IGATHERV",
    "IREDUCE_SCATTER",
    "IREDUCE",
    "ISCAN",
    "ISCATTER",
    "ISCATTERV",
    "IREDUCE_SCATTER_BLOCK"
};

char *MPIU_SELECTION_comm_kind_names[] = {
    "INTRA_COMM",
    "INTER_COMM"
};

char *MPIU_SELECTION_comm_hierarchy_names[] = {
    "FLAT_COMM",
    "TOPO_COMM"
};

/* *INDENT-OFF* */

MPIU_SELECTION_create_coll_tree_cb
    coll_inter_compositions[MPIU_SELECTION_COLLECTIVES_NUMBER] = {
        MPIU_SELECTION_create_coll_tree_inter_compositions_default,
        MPIU_SELECTION_create_coll_tree_inter_compositions_default,
        MPIU_SELECTION_create_coll_tree_inter_compositions_default,
        MPIU_SELECTION_create_coll_tree_inter_compositions_default,
        MPIU_SELECTION_create_coll_tree_inter_compositions_default,
        MPIU_SELECTION_create_coll_tree_inter_compositions_default,
        MPIU_SELECTION_create_coll_tree_inter_compositions_default,
        MPIU_SELECTION_create_coll_tree_inter_compositions_default,
        MPIU_SELECTION_create_coll_tree_inter_compositions_default,
        MPIU_SELECTION_create_coll_tree_inter_compositions_default,
        MPIU_SELECTION_create_coll_tree_inter_compositions_default,
        MPIU_SELECTION_create_coll_tree_inter_compositions_default,
        MPIU_SELECTION_create_coll_tree_inter_compositions_default,
        MPIU_SELECTION_create_coll_tree_inter_compositions_default,
        MPIU_SELECTION_create_coll_tree_inter_compositions_default,
        MPIU_SELECTION_create_coll_tree_inter_compositions_default,
        MPIU_SELECTION_create_coll_tree_inter_compositions_default,
        MPIU_SELECTION_create_coll_tree_inter_compositions_default,
        MPIU_SELECTION_create_coll_tree_inter_compositions_default,
        MPIU_SELECTION_create_coll_tree_inter_compositions_default,
        MPIU_SELECTION_create_coll_tree_inter_compositions_default,
        MPIU_SELECTION_create_coll_tree_inter_compositions_default,
        MPIU_SELECTION_create_coll_tree_inter_compositions_default,
        MPIU_SELECTION_create_coll_tree_inter_compositions_default,
        MPIU_SELECTION_create_coll_tree_inter_compositions_default,
        MPIU_SELECTION_create_coll_tree_inter_compositions_default,
        MPIU_SELECTION_create_coll_tree_inter_compositions_default,
        MPIU_SELECTION_create_coll_tree_inter_compositions_default,
        MPIU_SELECTION_create_coll_tree_inter_compositions_default,
        MPIU_SELECTION_create_coll_tree_inter_compositions_default,
        MPIU_SELECTION_create_coll_tree_inter_compositions_default,
        MPIU_SELECTION_create_coll_tree_inter_compositions_default,
        MPIU_SELECTION_create_coll_tree_inter_compositions_default,
        MPIU_SELECTION_create_coll_tree_inter_compositions_default};

MPIU_SELECTION_create_coll_tree_cb
    coll_topo_aware_compositions[MPIU_SELECTION_COLLECTIVES_NUMBER] = {
        MPIU_SELECTION_create_coll_tree_topo_aware_compositions_default,
        MPIU_SELECTION_create_coll_tree_topo_aware_compositions_default,
        MPIU_SELECTION_create_coll_tree_topo_aware_compositions_default,
        MPIU_SELECTION_create_coll_tree_topo_aware_compositions_default,
        MPIU_SELECTION_create_coll_tree_topo_aware_compositions_default,
        MPIU_SELECTION_create_coll_tree_topo_aware_compositions_default,
        MPIU_SELECTION_create_coll_tree_topo_aware_compositions_default,
        MPIU_SELECTION_create_coll_tree_topo_aware_compositions_default,
        MPIU_SELECTION_create_coll_tree_topo_aware_compositions_default,
        MPIU_SELECTION_create_coll_tree_topo_aware_compositions_default,
        MPIU_SELECTION_create_coll_tree_topo_aware_compositions_default,
        MPIU_SELECTION_create_coll_tree_topo_aware_compositions_default,
        MPIU_SELECTION_create_coll_tree_topo_aware_compositions_default,
        MPIU_SELECTION_create_coll_tree_topo_aware_compositions_default,
        MPIU_SELECTION_create_coll_tree_topo_aware_compositions_default,
        MPIU_SELECTION_create_coll_tree_topo_aware_compositions_default,
        MPIU_SELECTION_create_coll_tree_topo_aware_compositions_default,
        MPIU_SELECTION_create_coll_tree_topo_aware_compositions_default,
        MPIU_SELECTION_create_coll_tree_topo_aware_compositions_default,
        MPIU_SELECTION_create_coll_tree_topo_aware_compositions_default,
        MPIU_SELECTION_create_coll_tree_topo_aware_compositions_default,
        MPIU_SELECTION_create_coll_tree_topo_aware_compositions_default,
        MPIU_SELECTION_create_coll_tree_topo_aware_compositions_default,
        MPIU_SELECTION_create_coll_tree_topo_aware_compositions_default,
        MPIU_SELECTION_create_coll_tree_topo_aware_compositions_default,
        MPIU_SELECTION_create_coll_tree_topo_aware_compositions_default,
        MPIU_SELECTION_create_coll_tree_topo_aware_compositions_default,
        MPIU_SELECTION_create_coll_tree_topo_aware_compositions_default,
        MPIU_SELECTION_create_coll_tree_topo_aware_compositions_default,
        MPIU_SELECTION_create_coll_tree_topo_aware_compositions_default,
        MPIU_SELECTION_create_coll_tree_topo_aware_compositions_default,
        MPIU_SELECTION_create_coll_tree_topo_aware_compositions_default,
        MPIU_SELECTION_create_coll_tree_topo_aware_compositions_default,
        MPIU_SELECTION_create_coll_tree_topo_aware_compositions_default};

MPIU_SELECTION_create_coll_tree_cb
    coll_flat_compositions[MPIU_SELECTION_COLLECTIVES_NUMBER] = {
        MPIU_SELECTION_create_coll_tree_flat_compositions_default,
        MPIU_SELECTION_create_coll_tree_flat_compositions_default,
        MPIU_SELECTION_create_coll_tree_flat_compositions_default,
        MPIU_SELECTION_create_coll_tree_flat_compositions_default,
        MPIU_SELECTION_create_coll_tree_flat_compositions_default,
        MPIU_SELECTION_create_coll_tree_flat_compositions_default,
        MPIU_SELECTION_create_coll_tree_flat_compositions_default,
        MPIU_SELECTION_create_coll_tree_flat_compositions_default,
        MPIU_SELECTION_create_coll_tree_flat_compositions_default,
        MPIU_SELECTION_create_coll_tree_flat_compositions_default,
        MPIU_SELECTION_create_coll_tree_flat_compositions_default,
        MPIU_SELECTION_create_coll_tree_flat_compositions_default,
        MPIU_SELECTION_create_coll_tree_flat_compositions_default,
        MPIU_SELECTION_create_coll_tree_flat_compositions_default,
        MPIU_SELECTION_create_coll_tree_flat_compositions_default,
        MPIU_SELECTION_create_coll_tree_flat_compositions_default,
        MPIU_SELECTION_create_coll_tree_flat_compositions_default,
        MPIU_SELECTION_create_coll_tree_flat_compositions_default,
        MPIU_SELECTION_create_coll_tree_flat_compositions_default,
        MPIU_SELECTION_create_coll_tree_flat_compositions_default,
        MPIU_SELECTION_create_coll_tree_flat_compositions_default,
        MPIU_SELECTION_create_coll_tree_flat_compositions_default,
        MPIU_SELECTION_create_coll_tree_flat_compositions_default,
        MPIU_SELECTION_create_coll_tree_flat_compositions_default,
        MPIU_SELECTION_create_coll_tree_flat_compositions_default,
        MPIU_SELECTION_create_coll_tree_flat_compositions_default,
        MPIU_SELECTION_create_coll_tree_flat_compositions_default,
        MPIU_SELECTION_create_coll_tree_flat_compositions_default,
        MPIU_SELECTION_create_coll_tree_flat_compositions_default,
        MPIU_SELECTION_create_coll_tree_flat_compositions_default,
        MPIU_SELECTION_create_coll_tree_flat_compositions_default,
        MPIU_SELECTION_create_coll_tree_flat_compositions_default,
        MPIU_SELECTION_create_coll_tree_flat_compositions_default,
        MPIU_SELECTION_create_coll_tree_flat_compositions_default};

/* *INDENT-ON* */

char MPIU_SELECTION_offset_tree[MPIU_SELECTION_STORAGE_SIZE];
MPIU_SELECTION_storage_handler MPIU_SELECTION_tree_global_storage = {
    .base_addr = MPIU_SELECTION_offset_tree,
    .current_offset = 0
};

MPIU_SELECTION_storage_entry
MPIU_SELECTION_create_node(MPIU_SELECTION_storage_handler * storage,
                           MPIU_SELECTION_storage_entry parent,
                           MPIU_SELECTION_node_type_t node_type,
                           MPIU_SELECTION_node_type_t next_layer_type,
                           int node_key, int children_count)
{
    int node_offset = 0;
    int child_index = 0;
    MPIU_SELECTION_storage_entry tmp = storage->current_offset;

    node_offset =
        sizeof(MPIU_SELECTION_node_t) + sizeof(MPIU_SELECTION_storage_entry) * children_count;
    if (parent != MPIU_SELECTION_NULL_ENTRY) {
        child_index = MPIU_SELECTION_NODE_FIELD(storage, parent, cur_child_idx);
        MPIU_SELECTION_NODE_FIELD(storage, parent, offset[child_index]) = tmp;
        MPIU_SELECTION_NODE_FIELD(storage, parent, cur_child_idx)++;
    }

    storage->current_offset += node_offset;
    MPIR_Assertp(storage->current_offset <= MPIU_SELECTION_STORAGE_SIZE);

    MPIU_SELECTION_NODE_FIELD(storage, tmp, parent) = parent;
    MPIU_SELECTION_NODE_FIELD(storage, tmp, cur_child_idx) = 0;
    MPIU_SELECTION_NODE_FIELD(storage, tmp, type) = node_type;
    MPIU_SELECTION_NODE_FIELD(storage, tmp, next_layer_type) = next_layer_type;
    MPIU_SELECTION_NODE_FIELD(storage, tmp, key) = node_key;
    MPIU_SELECTION_NODE_FIELD(storage, tmp, children_count) = children_count;

    return tmp;
}

MPIU_SELECTION_storage_entry
MPIU_SELECTION_create_leaf(MPIU_SELECTION_storage_handler * storage,
                           MPIU_SELECTION_storage_entry parent, int node_type, int containers_count,
                           void *containers)
{
    int node_offset = 0;
    MPIU_SELECTION_storage_entry tmp = storage->current_offset;

    node_offset =
        sizeof(MPIU_SELECTION_node_t) +
        sizeof(MPIDIG_coll_algo_generic_container_t) * containers_count;
    if (parent != MPIU_SELECTION_NULL_ENTRY)
        MPIU_SELECTION_NODE_FIELD(storage, parent, offset[0]) = tmp;
    memset(MPIU_SELECTION_HANDLER_TO_POINTER(storage, tmp), 0, node_offset);
    storage->current_offset += node_offset;

    MPIU_SELECTION_NODE_FIELD(storage, tmp, parent) = parent;
    MPIU_SELECTION_NODE_FIELD(storage, tmp, type) = node_type;
    MPIU_SELECTION_NODE_FIELD(storage, tmp, children_count) = containers_count;
    if (containers != NULL) {
        MPIR_Memcpy((void *) MPIU_SELECTION_NODE_FIELD(storage, tmp, containers), containers,
                    sizeof(MPIDIG_coll_algo_generic_container_t) * containers_count);
    }

    return tmp;
}

void *MPIU_SELECTION_get_container(MPIU_SELECTION_storage_handler * storage,
                                   MPIU_SELECTION_storage_entry node)
{
    if ((MPIU_SELECTION_NODE_FIELD(storage, node, type) == MPIU_SELECTION_CONTAINER) &&
        MPIU_SELECTION_NODE_FIELD(storage, node, containers) != NULL) {
        return (void *) MPIU_SELECTION_NODE_FIELD(storage, node, containers);
    } else {
        return NULL;
    }
}

MPIU_SELECTION_storage_entry MPIU_SELECTION_get_node_parent(MPIU_SELECTION_storage_handler *
                                                            storage,
                                                            MPIU_SELECTION_storage_entry node)
{
    return MPIU_SELECTION_NODE_FIELD(storage, node, parent);
}

int MPIU_SELECTION_dump(MPIU_SELECTION_storage_handler * storage)
{
    int mpi_errno = MPI_SUCCESS;
    FILE *fp = NULL;

    if (MPIR_CVAR_TUNING_BIN_FILE_DUMP) {
        if (MPIR_Process.comm_world->rank == 0) {
            if ((fp = fopen(MPIR_CVAR_TUNING_BIN_FILE_DUMP, "wb")) == NULL) {
                MPL_DBG_MSG_FMT(MPIDI_DBG_COLL, VERBOSE,
                                (MPL_DBG_FDEST, "Unable to open %s\n",
                                 MPIR_CVAR_TUNING_BIN_FILE_DUMP));
                mpi_errno = MPI_ERR_OTHER;
            } else {
                size_t size = storage->current_offset;
                size_t left_to_write = size;
                size_t completed = 0;

                while (left_to_write) {
                    completed =
                        fwrite((char *) storage->base_addr + (size - left_to_write), 1,
                               left_to_write, fp);

                    if (completed == 0) {
                        break;
                    }

                    left_to_write -= completed;
                }

                if (left_to_write != 0) {
                    MPL_DBG_MSG_FMT(MPIDI_DBG_COLL, VERBOSE,
                                    (MPL_DBG_FDEST, "Unable to write %s\n",
                                     MPIR_CVAR_TUNING_BIN_FILE_DUMP));
                }

                fclose(fp);
            }
        }
    }
    return mpi_errno;
}

int MPIU_SELECTION_init()
{
    int mpi_errno = MPI_SUCCESS;

    MPIDI_CH4_Global.coll_selection =
        MPIU_SELECTION_tree_load(&MPIU_SELECTION_tree_global_storage, MPIR_CVAR_TUNING_BIN_FILE);

    if (MPIDI_CH4_Global.coll_selection == MPIU_SELECTION_NULL_ENTRY) {
        mpi_errno = MPI_ERR_OTHER;
    }

    return mpi_errno;
}

void MPIU_SELECTION_build_bin_tree_generic_part(MPIU_SELECTION_storage_handler * storage,
                                                MPIU_SELECTION_storage_entry * root,
                                                MPIU_SELECTION_storage_entry *
                                                inter_comm_subtree,
                                                MPIU_SELECTION_storage_entry *
                                                topo_aware_comm_subtree,
                                                MPIU_SELECTION_storage_entry * flat_comm_subtree)
{
    MPIU_SELECTION_storage_entry intra_comm_subtree = MPIU_SELECTION_NULL_ENTRY;
    MPIU_SELECTION_storage_entry composition = MPIU_SELECTION_NULL_ENTRY;

    *root =
        MPIU_SELECTION_create_node(storage, *root,
                                   MPIU_SELECTION_DEFAULT_NODE_TYPE, MPIU_SELECTION_DIRECTORY, -1,
                                   1);

    composition =
        MPIU_SELECTION_create_node(storage, *root,
                                   MPIU_SELECTION_DIRECTORY,
                                   MPIU_SELECTION_COMM_KIND,
                                   MPIU_SELECTION_COMPOSITION, MPIU_SELECTION_COMM_KIND_NUM);
    *inter_comm_subtree =
        MPIU_SELECTION_create_node(storage, composition, MPIU_SELECTION_COMM_KIND,
                                   MPIU_SELECTION_COLLECTIVE,
                                   MPIU_SELECTION_INTER_COMM, MPIU_SELECTION_COLLECTIVES_NUMBER);
    intra_comm_subtree =
        MPIU_SELECTION_create_node(storage, composition, MPIU_SELECTION_COMM_KIND,
                                   MPIU_SELECTION_COMM_HIERARCHY, MPIU_SELECTION_INTRA_COMM,
                                   MPIU_SELECTION_COMM_HIERARCHY_NUM);
    *topo_aware_comm_subtree =
        MPIU_SELECTION_create_node(storage, intra_comm_subtree, MPIU_SELECTION_COMM_HIERARCHY,
                                   MPIU_SELECTION_COLLECTIVE, MPIU_SELECTION_TOPO_COMM,
                                   MPIU_SELECTION_COLLECTIVES_NUMBER);
    *flat_comm_subtree =
        MPIU_SELECTION_create_node(storage, intra_comm_subtree, MPIU_SELECTION_COMM_HIERARCHY,
                                   MPIU_SELECTION_COLLECTIVE, MPIU_SELECTION_FLAT_COMM,
                                   MPIU_SELECTION_COLLECTIVES_NUMBER);
}

void MPIU_SELECTION_build_bin_tree_default_inter(MPIU_SELECTION_storage_handler * storage,
                                                 MPIU_SELECTION_storage_entry inter_comm_subtree)
{
    int coll_id = 0;

    for (coll_id = 0; coll_id < MPIU_SELECTION_COLLECTIVES_NUMBER; coll_id++) {
        coll_inter_compositions[coll_id] (storage, inter_comm_subtree, coll_id);
    }
}

void MPIU_SELECTION_build_bin_tree_default_topo_aware(MPIU_SELECTION_storage_handler * storage,
                                                      MPIU_SELECTION_storage_entry
                                                      topo_aware_comm_subtree)
{
    int coll_id = 0;

    for (coll_id = 0; coll_id < MPIU_SELECTION_COLLECTIVES_NUMBER; coll_id++) {
        coll_topo_aware_compositions[coll_id] (storage, topo_aware_comm_subtree, coll_id);
    }
}

void MPIU_SELECTION_build_bin_tree_default_flat(MPIU_SELECTION_storage_handler * storage,
                                                MPIU_SELECTION_storage_entry flat_comm_subtree)
{
    int coll_id = 0;

    for (coll_id = 0; coll_id < MPIU_SELECTION_COLLECTIVES_NUMBER; coll_id++) {
        coll_flat_compositions[coll_id] (storage, flat_comm_subtree, coll_id);
    }
}

MPIU_SELECTION_storage_entry MPIU_SELECTION_tree_load(MPIU_SELECTION_storage_handler * storage,
                                                      char *filename)
{
    MPIU_SELECTION_storage_entry root = MPIU_SELECTION_NULL_ENTRY;

    if (filename) {
        FILE *fp = NULL;
        struct stat filestat;
        int size = 0;
        if (stat(filename, &filestat) == 0) {
            size = filestat.st_size;

            if ((fp = fopen(filename, "rb")) != NULL) {
                size_t left_to_read = size;
                size_t completed = 0;

                while (left_to_read) {
                    completed =
                        fread((char *) storage->base_addr + (size - left_to_read), 1,
                              left_to_read, fp);

                    if (completed == 0) {
                        break;
                    }

                    left_to_read -= completed;
                }

                if (left_to_read == 0) {
                    root = (MPIU_SELECTION_storage_entry) 0;
                } else {
                    MPL_DBG_MSG_FMT(MPIDI_DBG_COLL, VERBOSE,
                                    (MPL_DBG_FDEST, "Unable to read %s\n", filename));
                }

                fclose(fp);
            } else {
                MPL_DBG_MSG_FMT(MPIDI_DBG_COLL, VERBOSE,
                                (MPL_DBG_FDEST, "Unable to open %s\n", filename));
            }
        } else {
            MPL_DBG_MSG_FMT(MPIDI_DBG_COLL, VERBOSE,
                            (MPL_DBG_FDEST, "File %s not found\n", filename));
        }
    }
    if (root == MPIU_SELECTION_NULL_ENTRY) {
        MPIU_SELECTION_storage_entry inter_comm_subtree = MPIU_SELECTION_NULL_ENTRY;
        MPIU_SELECTION_storage_entry intra_comm_subtree = MPIU_SELECTION_NULL_ENTRY;
        MPIU_SELECTION_storage_entry topo_aware_comm_subtree = MPIU_SELECTION_NULL_ENTRY;
        MPIU_SELECTION_storage_entry flat_comm_subtree = MPIU_SELECTION_NULL_ENTRY;
        MPIU_SELECTION_NODE custom_subtree = MPIU_SELECTION_NULL_TYPE;
        int coll_id = 0;

        /***************************************************************************/
        /*               Build generic part of binary selection tree               */
        /***************************************************************************/
        MPIU_SELECTION_build_bin_tree_generic_part(storage,
                                                   &root,
                                                   &inter_comm_subtree,
                                                   &topo_aware_comm_subtree, &flat_comm_subtree);

        /***************************************************************************/
        /*               Build json to binary trees for topo aware comm            */
        /***************************************************************************/
        custom_subtree = MPIU_SELECTION_tree_read(MPIR_CVAR_TUNING_JSON_FILE);
        for (coll_id = 0; coll_id < MPIU_SELECTION_COLLECTIVES_NUMBER; coll_id++) {
            MPIU_SELECTION_NODE coll_json = MPIU_SELECTION_NULL_TYPE;
            int is_found = 0;

            MPIU_SELECTION_tree_init_json_node(&coll_json);
            if (coll_json != MPIU_SELECTION_NULL_TYPE) {
                is_found = MPIU_SELECTION_tree_is_coll_in_json(custom_subtree, &coll_json, coll_id);
                if (is_found) {
                    MPIU_SELECTION_tree_json_to_bin(storage, coll_json, topo_aware_comm_subtree);
                } else {
                    coll_topo_aware_compositions[coll_id] (storage, topo_aware_comm_subtree,
                                                           coll_id);
                }
                MPIU_SELECTION_tree_free_json_node(coll_json);
            } else {
                coll_topo_aware_compositions[coll_id] (storage, topo_aware_comm_subtree, coll_id);
            }
        }

        /***************************************************************************/
        /*               Build json to binary trees for flat and inter comms       */
        /***************************************************************************/
        MPIU_SELECTION_build_bin_tree_default_inter(storage, inter_comm_subtree);
        MPIU_SELECTION_build_bin_tree_default_flat(storage, flat_comm_subtree);
    }

    return root;
}

void MPIU_SELECTION_set_match_pattern_key(MPIU_SELECTION_match_pattern_t * match_pattern,
                                          MPIU_SELECTION_node_type_t layer_type, int key)
{
    switch (layer_type) {
        case MPIU_SELECTION_DIRECTORY:
            match_pattern->directory = key;
            break;
        case MPIU_SELECTION_COMM_KIND:
            match_pattern->comm_kind = key;
            break;
        case MPIU_SELECTION_COMM_HIERARCHY:
            match_pattern->comm_hierarchy_kind = key;
            break;
        case MPIU_SELECTION_COLLECTIVE:
            match_pattern->coll_id = key;
            break;
        case MPIU_SELECTION_COMMSIZE:
            match_pattern->comm_size = key;
            break;
        case MPIU_SELECTION_MSGSIZE:
            match_pattern->msg_size = key;
            break;
        default:
            break;
    }
}

int MPIU_SELECTION_get_match_pattern_key(MPIU_SELECTION_match_pattern_t * match_pattern,
                                         MPIU_SELECTION_node_type_t layer_type)
{
    switch (layer_type) {
        case MPIU_SELECTION_DIRECTORY:
            return match_pattern->directory;
        case MPIU_SELECTION_COMM_KIND:
            return match_pattern->comm_kind;
        case MPIU_SELECTION_COMM_HIERARCHY:
            return match_pattern->comm_hierarchy_kind;
        case MPIU_SELECTION_COLLECTIVE:
            return match_pattern->coll_id;
        case MPIU_SELECTION_COMMSIZE:
            return match_pattern->comm_size;
        case MPIU_SELECTION_MSGSIZE:
            return match_pattern->msg_size;
        default:
            break;
    }
    return MPIU_SELECTION_DEFAULT_KEY;
}

void MPIU_SELECTION_init_match_pattern(MPIU_SELECTION_match_pattern_t * match_pattern)
{
    MPIR_Assert(match_pattern != NULL);
    match_pattern->terminal_node_type = MPIU_SELECTION_DEFAULT_TERMINAL_NODE_TYPE;

    match_pattern->directory = -1;
    match_pattern->comm_kind = -1;
    match_pattern->comm_hierarchy_kind = -1;
    match_pattern->coll_id = -1;
    match_pattern->comm_size = -1;
    match_pattern->msg_size = -1;
}

void MPIU_SELECTION_init_comm_match_pattern(MPIR_Comm * comm,
                                            MPIU_SELECTION_match_pattern_t *
                                            match_pattern, MPIU_SELECTION_node_type_t
                                            terminal_node_type)
{
    MPI_Aint type_size = 0;

    MPIU_SELECTION_init_match_pattern(match_pattern);

    match_pattern->terminal_node_type = terminal_node_type;
    MPIR_Assert(comm != NULL);
    MPIU_SELECTION_set_match_pattern_key(match_pattern, MPIU_SELECTION_COMMSIZE, comm->local_size);
    MPIU_SELECTION_set_match_pattern_key(match_pattern, MPIU_SELECTION_COMM_KIND, comm->comm_kind);
    switch (comm->hierarchy_kind) {
        case MPIR_COMM_HIERARCHY_KIND__FLAT:
            MPL_FALLTHROUGH;
        case MPIR_COMM_HIERARCHY_KIND__PARENT:
            MPIU_SELECTION_set_match_pattern_key(match_pattern,
                                                 MPIU_SELECTION_COMM_HIERARCHY,
                                                 comm->hierarchy_kind);
            break;
        case MPIR_COMM_HIERARCHY_KIND__NODE_ROOTS:
            MPL_FALLTHROUGH;
        case MPIR_COMM_HIERARCHY_KIND__NODE:
            MPIU_SELECTION_set_match_pattern_key(match_pattern,
                                                 MPIU_SELECTION_COMM_HIERARCHY,
                                                 MPIR_COMM_HIERARCHY_KIND__FLAT);
            break;
        default:
            MPIR_Assert(0);
            break;
    }
}

void MPIU_SELECTION_init_coll_match_pattern(MPIU_SELECTON_coll_signature_t * coll_sig,
                                            MPIU_SELECTION_match_pattern_t *
                                            match_pattern, MPIU_SELECTION_node_type_t
                                            terminal_node_type)
{
    MPI_Aint type_size = 0;

    MPIR_Assert(coll_sig != NULL);

    MPIU_SELECTION_init_match_pattern(match_pattern);
    match_pattern->terminal_node_type = terminal_node_type;

    MPIU_SELECTION_set_match_pattern_key(match_pattern,
                                         MPIU_SELECTION_COLLECTIVE, coll_sig->coll_id);

    switch (coll_sig->coll_id) {
        case MPIU_SELECTION_BCAST:
            MPIR_Datatype_get_size_macro(coll_sig->coll.bcast.datatype, type_size);
            MPIU_SELECTION_set_match_pattern_key(match_pattern,
                                                 MPIU_SELECTION_MSGSIZE,
                                                 (type_size * coll_sig->coll.bcast.count));
            break;
        case MPIU_SELECTION_BARRIER:
            break;
        default:
            break;
    }
}

#if defined (MPL_USE_DBG_LOGGING)
void MPIU_SELECTION_match_layer_and_key_to_str(char *layer_str, char *key_str,
                                               MPIU_SELECTION_storage_handler storage,
                                               MPIU_SELECTION_storage_entry match_node)
{
    switch (MPIU_SELECTION_NODE_FIELD(storage, match_node, type)) {
        case MPIU_SELECTION_COMM_KIND:
            sprintf(layer_str, "%s", "COMM_KIND");
            MPIR_Assert(sizeof(MPIU_SELECTION_comm_kind_names) /
                        sizeof(MPIU_SELECTION_comm_kind_names[0]) >
                        MPIU_SELECTION_NODE_FIELD(storage, match_node, key));
            sprintf(key_str, "%s",
                    MPIU_SELECTION_comm_kind_names[MPIU_SELECTION_NODE_FIELD(match_node, key)]);
            break;
        case MPIU_SELECTION_COMM_HIERARCHY:
            sprintf(layer_str, "%s", "COMM_HIERARCHY");
            MPIR_Assert(sizeof(MPIU_SELECTION_comm_hierarchy_names) /
                        sizeof(MPIU_SELECTION_comm_hierarchy_names[0]) >
                        MPIU_SELECTION_NODE_FIELD(storage, match_node, key));
            sprintf(key_str, "%s",
                    MPIU_SELECTION_comm_hierarchy_names[MPIU_SELECTION_NODE_FIELD
                                                        (match_node, key)]);
            break;
        case MPIU_SELECTION_COLLECTIVE:
            sprintf(layer_str, "%s", "COLLECTIVE");
            MPIR_Assert(sizeof(MPIU_SELECTION_coll_names) /
                        sizeof(MPIU_SELECTION_coll_names[0]) >
                        MPIU_SELECTION_NODE_FIELD(storage, match_node, key));
            sprintf(key_str, MPIU_SELECTION_coll_names[MPIU_SELECTION_NODE_FIELD(match_node, key)]);
            break;
        case MPIU_SELECTION_COMMSIZE:
            sprintf(layer_str, "%s", "COMMSIZE");
            sprintf(key_str, "%d", MPIU_SELECTION_NODE_FIELD(storage, match_node, key));
            break;
        case MPIU_SELECTION_MSGSIZE:
            sprintf(layer_str, "%s", "MSGSIZE");
            sprintf(key_str, "%d", MPIU_SELECTION_NODE_FIELD(storage, match_node, key));
            break;
        default:
            sprintf(layer_str, "%s", "UNKNOWN");
            sprintf(key_str, "%d", MPIU_SELECTION_NODE_FIELD(storage, match_node, key));
            break;
    }
}

#endif /* MPL_USE_DBG_LOGGING */

MPIU_SELECTION_storage_entry
MPIU_SELECTION_find_entry(MPIU_SELECTION_storage_handler * storage,
                          MPIU_SELECTION_storage_entry root_node,
                          MPIU_SELECTION_match_pattern_t * match_pattern)
{
    MPIU_SELECTION_node_type_t root_type = MPIU_SELECTION_DEFAULT_TERMINAL_NODE_TYPE;
    MPIU_SELECTION_node_type_t next_layer_type = MPIU_SELECTION_DEFAULT_TERMINAL_NODE_TYPE;
    MPIU_SELECTION_storage_entry match_node = MPIU_SELECTION_NULL_ENTRY;
    int match_pattern_key = 0;

    if (root_node != MPIU_SELECTION_NULL_ENTRY) {

        root_type = MPIU_SELECTION_NODE_FIELD(storage, root_node, type);

        while ((root_type != match_pattern->terminal_node_type) &&
               (root_type != MPIU_SELECTION_DEFAULT_TERMINAL_NODE_TYPE)) {

            next_layer_type = MPIU_SELECTION_NODE_FIELD(storage, root_node, next_layer_type);
            match_pattern_key =
                MPIU_SELECTION_get_match_pattern_key(match_pattern, next_layer_type);

            switch (next_layer_type) {
                case MPIU_SELECTION_DIRECTORY:
                    MPL_FALLTHROUGH;
                case MPIU_SELECTION_COMM_KIND:
                    MPL_FALLTHROUGH;
                case MPIU_SELECTION_COMM_HIERARCHY:
                    MPIU_SELECTION_level_match_condition(storage, root_node, match_node,
                                                         (match_pattern_key ==
                                                          MPIU_SELECTION_NODE_FIELD
                                                          (storage, match_node, key)));
                    break;
                case MPIU_SELECTION_COLLECTIVE:
                    MPIU_SELECTION_level_match_id(storage, root_node, match_node,
                                                  match_pattern_key,
                                                  MPIU_SELECTION_COLLECTIVES_NUMBER);
                    break;
                case MPIU_SELECTION_COMMSIZE:
                    MPIU_SELECTION_level_match_complex_condition(storage, root_node, match_node,
                                                                 match_pattern_key);
                    break;
                case MPIU_SELECTION_MSGSIZE:
                    MPIU_SELECTION_level_match_condition(storage, root_node, match_node,
                                                         (match_pattern_key <=
                                                          MPIU_SELECTION_NODE_FIELD
                                                          (storage, match_node, key)));
                    break;
                default:
                    /* Move to the next layer from the last element on current layer */
                    MPIU_SELECTION_level_match_default(storage, root_node, match_node);
                    break;
            }

            /* Stop searching if a layer with a given key has not been found */
            if (match_node == MPIU_SELECTION_NULL_ENTRY) {
                return MPIU_SELECTION_NULL_ENTRY;
            }
            root_node = match_node;
            root_type = MPIU_SELECTION_NODE_FIELD(storage, root_node, type);
        }

        return root_node;
    }

    return MPIU_SELECTION_NULL_ENTRY;
}

#endif /* MPIU_SELECTION_H_INCLUDED */