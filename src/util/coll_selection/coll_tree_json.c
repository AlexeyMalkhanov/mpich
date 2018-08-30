#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <strings.h>
#include "mpl.h"
#include "mpiimpl.h"
#include "coll_tree_json.h"
#include "container_parsers.h"

int MPIU_SELECTION_tree_current_collective_id = 0;

char *MPIU_SELECTION_Bcast_composition[] = {
    "alpha",
    "beta",
    "gamma",
    "delta"
};

char *MPIU_SELECTION_Bcast_netmod[] = {
    "binomial",
    "scatter_recursive_doubling_allgather",
    "scatter_ring_allgatherv",
};

char *MPIU_SELECTION_Bcast_shm[] = {
    "binomial",
    "scatter_recursive_doubling_allgather",
    "scatter_ring_allgatherv",
};

char **MPIU_SELECTION_Bcast[] = {
    MPIU_SELECTION_Bcast_composition,
    MPIU_SELECTION_Bcast_netmod,
    MPIU_SELECTION_Bcast_shm
};

char ***MPIU_SELECTION_ALGORITHMS[] = {
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    MPIU_SELECTION_Bcast,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
};

MPIU_SELECTION_tree_entry_t MPIU_SELECTION_tree_parse_bcast[] = {
    {MPIDI_Bcast_intra_composition_alpha_id, bcast_alpha},
    {MPIDI_Bcast_intra_composition_beta_id, bcast_beta},
    {MPIDI_Bcast_intra_composition_gamma_id, bcast_gamma},
    {MPIDI_Bcast_intra_composition_delta_id, bcast_delta},
};

MPIU_SELECTION_tree_entry_t *MPIU_SELECTION_tree_parse[] = {
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    MPIU_SELECTION_tree_parse_bcast,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL
};

int MPIU_SELECTION_MAX_INDICES[MPIU_SELECTION_COLLECTIVES_NUMBER]
    [MPIU_SELECTION_ALGORITHM_LAYERS_NUM] = {
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {
     sizeof(MPIU_SELECTION_Bcast_composition) / sizeof(char *),
     sizeof(MPIU_SELECTION_Bcast_netmod) / sizeof(char *),
#ifndef MPIDI_CH4_DIRECT_NETMOD
     sizeof(MPIU_SELECTION_Bcast_shm) / sizeof(char *)
#else /* !MPIDI_CH4_DIRECT_NETMOD */
     0
#endif /* !MPIDI_CH4_DIRECT_NETMOD */
     },
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
};

static inline MPIU_SELECTION_NODE MPIU_SELECTION_tree_text_to_json(char *contents)
{
    MPIU_SELECTION_NODE root = MPIU_SELECTION_NULL_TYPE;
    root = json_tokener_parse(contents);
    return root;
}

static inline char *MPIU_SELECTION_tree_get_node_json_name(MPIU_SELECTION_NODE json_node, int index)
{
    struct json_object_iter iter;
    int count = 0;

    json_object_object_foreachC(json_node, iter) {
        if (count == index)
            return (char *) lh_entry_k(iter.entry);
        count++;
    }

    return NULL;
}

static inline MPIU_SELECTION_NODE
MPIU_SELECTION_tree_get_node_json_value(MPIU_SELECTION_NODE json_node, int index)
{
    struct json_object_iter iter;
    int count = 0;

    json_object_object_foreachC(json_node, iter) {
        if (count == index)
            return (struct json_object *) lh_entry_v(iter.entry);
        count++;
    }

    return NULL;
}

static inline MPIU_SELECTION_NODE
MPIU_SELECTION_tree_get_node_json_next(MPIU_SELECTION_NODE json_node, int index)
{
    struct json_object_iter iter;
    int count = 0;

    json_object_object_foreachC(json_node, iter) {
        if (count == index)
            return (struct json_object *) lh_entry_v(iter.entry);
        count++;
    }

    return MPIU_SELECTION_NULL_TYPE;
}

static inline int MPIU_SELECTION_tree_get_node_json_type(MPIU_SELECTION_NODE json_node)
{
    return json_node->o_type;
}

static inline int MPIU_SELECTION_tree_get_node_json_peer_count(MPIU_SELECTION_NODE json_node)
{
    if (json_node == MPIU_SELECTION_NULL_TYPE) {
        return 0;
    } else {
        return json_node->o.c_object->count;
    }
}

MPIU_SELECTION_NODE MPIU_SELECTION_tree_read(char *file)
{
    MPIU_SELECTION_NODE root = MPIU_SELECTION_NULL_TYPE;
    FILE *fp = NULL;
    struct stat filestat;
    int size = 0;
    char *contents = NULL;

    if (file == NULL) {
        goto fn_exit;
    }

    if (stat(file, &filestat) != 0) {
        MPL_DBG_MSG_FMT(MPIDI_DBG_COLL, VERBOSE, (MPL_DBG_FDEST, "File %s not found\n", file));
        goto fn_exit;
    }

    size = filestat.st_size;
    contents = (char *) MPL_malloc(filestat.st_size, MPL_MEM_OTHER);
    if (contents == NULL) {
        MPL_DBG_MSG_FMT(MPIDI_DBG_COLL, VERBOSE,
                        (MPL_DBG_FDEST, "Unable to allocate %d bytes\n", size));
        goto fn_exit;
    }

    fp = fopen(file, "rt");
    if (fp == NULL) {
        MPL_DBG_MSG_FMT(MPIDI_DBG_COLL, VERBOSE, (MPL_DBG_FDEST, "Unable to open %s\n", file));
        goto fn_exit;
    }

    size_t left_to_read = size;
    size_t completed = 0;

    while (left_to_read) {
        completed = fread((char *) contents + (size - left_to_read), 1, left_to_read, fp);

        if (completed == 0) {
            break;
        }

        left_to_read -= completed;
    }

    if (left_to_read != 0) {
        MPL_DBG_MSG_FMT(MPIDI_DBG_COLL, VERBOSE,
                        (MPL_DBG_FDEST, "Unable to read content of %s\n", file));
        fclose(fp);
        goto fn_exit;
    }
    fclose(fp);

    root = MPIU_SELECTION_tree_text_to_json(contents);
    if (root == MPIU_SELECTION_NULL_TYPE) {
        MPL_DBG_MSG_FMT(MPIDI_DBG_COLL, VERBOSE,
                        (MPL_DBG_FDEST, "Unable to load tuning settings\n"));
        goto fn_exit;
    }

  fn_exit:
    if (contents)
        MPL_free(contents);

    return root;
}

void MPIU_SELECTION_tree_json_to_bin(MPIU_SELECTION_storage_handler * storage,
                                     MPIU_SELECTION_NODE json_node, MPIU_SELECTION_storage_entry
                                     node)
{
    if (json_node == MPIU_SELECTION_NULL_TYPE) {
        return;
    }
    switch (MPIU_SELECTION_tree_get_node_json_type(json_node)) {
        case MPIU_SELECTION_OBJECT_TYPE:
            MPIU_SELECTION_tree_handle_object(storage, json_node, node);
            break;
        case MPIU_SELECTION_NULL_TYPE:
            MPL_FALLTHROUGH;
        case MPIU_SELECTION_ARRAY_TYPE:
            MPL_FALLTHROUGH;
        case MPIU_SELECTION_INT_TYPE:
            MPL_FALLTHROUGH;
        case MPIU_SELECTION_DOUBLE_TYPE:
            MPL_FALLTHROUGH;
        case MPIU_SELECTION_STR_TYPE:
            MPL_FALLTHROUGH;
        case MPIU_SELECTION_BOOL_TYPE:
            MPL_FALLTHROUGH;
        default:
            MPIR_Assert(0);
            break;
    }
}

int MPIU_SELECTION_tree_get_algorithm_type(char *str)
{
    if (strstr(str, MPIU_SELECTION_COMPOSITION_TOKEN)) {
        return MPIU_SELECTION_COMPOSITION;
    } else if (strstr(str, MPIU_SELECTION_NETMOD_TOKEN)) {
        return MPIU_SELECTION_NETMOD;
    } else if (strstr(str, MPIU_SELECTION_SHM_TOKEN)) {
        return MPIU_SELECTION_SHM;
    } else {
        return -1;
    }
}

int MPIU_SELECTION_tree_get_node_type(MPIU_SELECTION_NODE json_node, int ind)
{
    if (strstr
        (MPIU_SELECTION_tree_get_node_json_name(json_node, ind), MPIU_SELECTION_COLL_KEY_TOKEN)) {
        return MPIU_SELECTION_COLLECTIVE;
    } else
        if (strstr
            (MPIU_SELECTION_tree_get_node_json_name(json_node, ind),
             MPIU_SELECTION_COMMSIZE_KEY_TOKEN)) {
        return MPIU_SELECTION_COMMSIZE;
    } else
        if (strstr
            (MPIU_SELECTION_tree_get_node_json_name(json_node, ind),
             MPIU_SELECTION_MSGSIZE_KEY_TOKEN)) {
        return MPIU_SELECTION_MSGSIZE;
    } else {
        return MPIU_SELECTION_CONTAINER;
    }
}

void MPIU_SELECTION_tree_get_node_key(MPIU_SELECTION_NODE json_node, int ind, char *key)
{
    if (strstr
        (MPIU_SELECTION_tree_get_node_json_name(json_node, ind), MPIU_SELECTION_COLL_KEY_TOKEN)) {
        MPL_strncpy(key,
                    MPIU_SELECTION_tree_get_node_json_name(json_node,
                                                           ind) +
                    strlen(MPIU_SELECTION_COLL_KEY_TOKEN), MPIU_SELECTION_BUFFER_MAX_SIZE);
    } else
        if (strstr
            (MPIU_SELECTION_tree_get_node_json_name(json_node, ind),
             MPIU_SELECTION_COMMSIZE_KEY_TOKEN)) {
        MPL_strncpy(key,
                    MPIU_SELECTION_tree_get_node_json_name(json_node,
                                                           ind) +
                    strlen(MPIU_SELECTION_COMMSIZE_KEY_TOKEN), MPIU_SELECTION_BUFFER_MAX_SIZE);
    } else
        if (strstr
            (MPIU_SELECTION_tree_get_node_json_name(json_node, ind),
             MPIU_SELECTION_MSGSIZE_KEY_TOKEN)) {
        MPL_strncpy(key,
                    MPIU_SELECTION_tree_get_node_json_name(json_node,
                                                           ind) +
                    strlen(MPIU_SELECTION_MSGSIZE_KEY_TOKEN), MPIU_SELECTION_BUFFER_MAX_SIZE);
    } else {
        return;
    }
}

int MPIU_SELECTION_tree_convert_key_str(char *key_str)
{
    if (strncmp(key_str, "pow2_", strlen("pow2_")) == 0) {
        char buff[MPIU_SELECTION_BUFFER_MAX_SIZE] = { 0 };
        char *head = NULL;
        char *value = NULL;

        MPL_strncpy(buff, key_str, MPIU_SELECTION_BUFFER_MAX_SIZE);

        head = strtok(buff, MPIU_SELECTION_DELIMITER_SUFFIX);
        value = strtok(NULL, MPIU_SELECTION_DELIMITER_SUFFIX);

        MPL_snprintf(key_str, MPIU_SELECTION_BUFFER_MAX_SIZE, "%s%s",
                     MPIU_SELECTION_POW2_TOKEN, value);
        return atoi(key_str);
    } else if (strncmp(key_str, "pow2", strlen("pow2")) == 0) {
        MPL_snprintf(key_str, MPIU_SELECTION_BUFFER_MAX_SIZE, MPIU_SELECTION_POW2_TOKEN);
        return atoi(key_str);
    } else {
        return atoi(key_str);
    }
}

void MPIU_SELECTION_tree_convert_key_int(int key_int, char *key_str, int *is_pow2)
{
    MPL_snprintf(key_str, MPIU_SELECTION_BUFFER_MAX_SIZE, "%d", key_int);

    if (strncmp(key_str, MPIU_SELECTION_POW2_TOKEN, strlen(MPIU_SELECTION_POW2_TOKEN)) == 0) {
        *is_pow2 = 1;

        MPL_snprintf(key_str, MPIU_SELECTION_BUFFER_MAX_SIZE, "%s",
                     key_str + strlen(MPIU_SELECTION_POW2_TOKEN));
    }

}

void MPIU_SELECTION_tree_handle_object(MPIU_SELECTION_storage_handler * storage,
                                       MPIU_SELECTION_NODE json_node,
                                       MPIU_SELECTION_storage_entry node)
{
    int length = 0;
    int i = 0;
    char key_str[MPIU_SELECTION_BUFFER_MAX_SIZE];
    MPIU_SELECTION_storage_entry new_node = MPIU_SELECTION_NULL_ENTRY;

    if (json_node == MPIU_SELECTION_NULL_TYPE) {
        return;
    }

    length = MPIU_SELECTION_tree_get_node_json_peer_count(json_node);
    for (i = 0; i < length; i++) {
        MPIR_Assert(MPIU_SELECTION_tree_get_node_type(json_node, 0) ==
                    MPIU_SELECTION_tree_get_node_type(json_node, i));
        if (MPIU_SELECTION_tree_get_node_type(json_node, 0) != MPIU_SELECTION_CONTAINER) {
            MPIU_SELECTION_tree_get_node_key(json_node, i, key_str);
            if (MPIU_SELECTION_tree_get_node_type(json_node, 0) == MPIU_SELECTION_COLLECTIVE) {
                int coll_id = 0;
                for (coll_id = 0; coll_id < MPIU_SELECTION_COLLECTIVES_NUMBER; coll_id++) {
                    if (strcasecmp(MPIU_SELECTION_coll_names[coll_id], key_str) == 0) {
                        MPIU_SELECTION_tree_current_collective_id = coll_id;
                        break;
                    }
                }
                MPL_snprintf(key_str, MPIU_SELECTION_BUFFER_MAX_SIZE, "%d", coll_id);
            }

            MPIR_Assert(MPIU_SELECTION_tree_get_node_type
                        (MPIU_SELECTION_tree_get_node_json_next(json_node, 0),
                         0) ==
                        MPIU_SELECTION_tree_get_node_type
                        (MPIU_SELECTION_tree_get_node_json_next(json_node, i), 0));

            new_node =
                MPIU_SELECTION_create_node(storage, node,
                                           MPIU_SELECTION_tree_get_node_type
                                           (json_node, 0),
                                           MPIU_SELECTION_tree_get_node_type
                                           (MPIU_SELECTION_tree_get_node_json_next
                                            (json_node, 0), 0),
                                           MPIU_SELECTION_tree_convert_key_str(key_str),
                                           MPIU_SELECTION_tree_get_node_json_peer_count
                                           (MPIU_SELECTION_tree_get_node_json_next(json_node, i)));

            MPIU_SELECTION_tree_json_to_bin(storage, MPIU_SELECTION_tree_get_node_json_next
                                            (json_node, i), new_node);

        } else {
            /* call cnt handler */
            MPIDIG_coll_algo_generic_container_t cnt[MPIU_SELECTION_MAX_CNT];
            int cnt_num = 0;

            MPIU_SELECTION_tree_create_containers(json_node, &cnt_num, cnt,
                                                  MPIU_SELECTION_tree_current_collective_id);
            new_node =
                MPIU_SELECTION_create_leaf(storage, node, MPIU_SELECTION_CONTAINER, cnt_num, cnt);
        }
    }
}

void MPIU_SELECTION_tree_create_containers(MPIU_SELECTION_NODE
                                           json_node, int *cnt_num,
                                           MPIDIG_coll_algo_generic_container_t * cnt, int coll_id)
{
    int i = 0;
    char *leaf_name = NULL;
    int is_known_token = 1;
    int composition_id = 0;

    if (json_node == MPIU_SELECTION_NULL_TYPE) {
        return;
    }

    *cnt_num = MPIU_SELECTION_MAX_CNT;

    leaf_name = MPL_strdup(MPIU_SELECTION_tree_get_node_json_name(json_node, 0));

    is_known_token = 1;

    char buff[MPIU_SELECTION_BUFFER_MAX_SIZE] = { 0 };

    if (leaf_name) {

        MPL_strncpy(buff, leaf_name, MPIU_SELECTION_BUFFER_MAX_SIZE);

        char *key = NULL;
        char *value = NULL;
        int algorithm_type = -1;

        key = strtok(buff, MPIU_SELECTION_DELIMITER_VALUE);
        value = strtok(NULL, MPIU_SELECTION_DELIMITER_VALUE);
        algorithm_type = MPIU_SELECTION_tree_get_algorithm_type(key);
        if ((coll_id == MPIU_SELECTION_COLLECTIVES_NUMBER) ||
            (algorithm_type != MPIU_SELECTION_COMPOSITION)) {
            is_known_token = 0;
        }
        if (is_known_token) {
            for (composition_id = 0;
                 composition_id < MPIU_SELECTION_MAX_INDICES[coll_id][algorithm_type];
                 composition_id++) {
                if (strcasecmp
                    (MPIU_SELECTION_ALGORITHMS[coll_id][algorithm_type][composition_id],
                     value) == 0) {
                    break;
                }
            }
        }
        if (composition_id == MPIU_SELECTION_MAX_INDICES[coll_id][algorithm_type]) {
            is_known_token = 0;
        }
        MPL_free(leaf_name);
    }

    if (is_known_token) {
        MPIU_SELECTION_tree_parse[coll_id][composition_id].create_container(json_node, cnt_num,
                                                                            cnt, composition_id);
    } else {
        MPL_DBG_MSG_FMT(MPIDI_DBG_COLL, VERBOSE, (MPL_DBG_FDEST, "Incorrect token: %s", leaf_name));

        cnt[0].id = MPIU_SELECTION_DEFAULT_ALGO_ID;
        for (i = 1; i < MPIU_SELECTION_MAX_CNT; i++) {
            cnt[i].id = MPIU_SELECTION_DEFAULT_ALGO_ID;
        }
    }
}

int MPIU_SELECTION_tree_is_coll_in_json(MPIU_SELECTION_NODE
                                        json_node_in,
                                        MPIU_SELECTION_NODE * json_node_out, int coll_id)
{
    int length = 0;
    int index = 0;
    char key_str[MPIU_SELECTION_BUFFER_MAX_SIZE];

    if (json_node_in == MPIU_SELECTION_NULL_TYPE) {
        return 0;
    }

    length = MPIU_SELECTION_tree_get_node_json_peer_count(json_node_in);
    for (index = 0; index < length; index++) {
        MPIR_Assert(MPIU_SELECTION_tree_get_node_type(json_node_in, 0) ==
                    MPIU_SELECTION_tree_get_node_type(json_node_in, index));

        MPIU_SELECTION_tree_get_node_key(json_node_in, index, key_str);

        if (MPIU_SELECTION_tree_get_node_type(json_node_in, 0) == MPIU_SELECTION_COLLECTIVE) {
            if (strcasecmp(MPIU_SELECTION_coll_names[coll_id], key_str) == 0) {
                char *key = NULL;
                MPIU_SELECTION_NODE value = MPIU_SELECTION_NULL_TYPE;

                key = MPIU_SELECTION_tree_get_node_json_name(json_node_in, index);
                value = MPIU_SELECTION_tree_get_node_json_value(json_node_in, index);
                MPIU_SELECTION_tree_fill_json_node(*json_node_out, key, value);
                return 1;
            }
        }
    }
    return 0;
}

void MPIU_SELECTION_tree_init_json_node(MPIU_SELECTION_NODE * json_node)
{
    *json_node = json_object_new_object();
}

int MPIU_SELECTION_tree_free_json_node(MPIU_SELECTION_NODE json_node)
{
    int res = 0;
    res = json_object_put(json_node);
    return res;
}

int MPIU_SELECTION_tree_fill_json_node(MPIU_SELECTION_NODE json_node,
                                       char *key, MPIU_SELECTION_NODE value)
{
    int res = 0;
    res = json_object_object_add(json_node, key, value);
    return res;
}