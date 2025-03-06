/* vim: set tabstop=4 expandtab shiftwidth=4 softtabstop=4: */

/*
 * Copyright 2015 University of Piemonte Orientale, Computer Science Institute
 *
 * This file is part of UPOalglib.
 *
 * UPOalglib is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * UPOalglib is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with UPOalglib.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "bst_private.h"
#include <stdio.h>
#include <stdlib.h>


/**** EXERCISE #1 - BEGIN of FUNDAMENTAL OPERATIONS ****/


upo_bst_t upo_bst_create(upo_bst_comparator_t key_cmp)
{
    upo_bst_t tree = malloc(sizeof(struct upo_bst_s));
    if (tree == NULL)
    {
        perror("Unable to create a binary search tree");
        abort();
    }

    tree->root = NULL;
    tree->key_cmp = key_cmp;

    return tree;
}

void upo_bst_destroy(upo_bst_t tree, int destroy_data)
{
    if (tree != NULL)
    {
        upo_bst_clear(tree, destroy_data);
        free(tree);
    }
}

void upo_bst_clear_impl(upo_bst_node_t *node, int destroy_data)
{
    if (node != NULL)
    {
        upo_bst_clear_impl(node->left, destroy_data);
        upo_bst_clear_impl(node->right, destroy_data);

        if (destroy_data)
        {
            free(node->key);
            free(node->value);
        }

        free(node);
    }
}

void upo_bst_clear(upo_bst_t tree, int destroy_data)
{
    if (tree != NULL)
    {
        upo_bst_clear_impl(tree->root, destroy_data);
        tree->root = NULL;
    }
}

upo_bst_node_t* recursive_put(upo_bst_node_t* node, void* key, void* value,upo_bst_comparator_t cmp, void** old_value) {
    if (node == NULL) {
        upo_bst_node_t* new_node = malloc(sizeof(upo_bst_node_t));
        if (new_node == NULL) {
            return NULL; 
        }
        new_node->key = key;
        new_node->value = value;
        new_node->left = NULL;
        new_node->right = NULL;
        return new_node;
    }

    int cmp_result = cmp(key, node->key);
    if (cmp_result < 0) {
        upo_bst_node_t* inserted_node = recursive_put(node->left, key, value, cmp, old_value);
        if (inserted_node == NULL) {
            return NULL; 
        }
        node->left = inserted_node;
    } else if (cmp_result > 0) {
        upo_bst_node_t* inserted_node = recursive_put(node->right, key, value, cmp, old_value);
        if (inserted_node == NULL) {
            return NULL; 
        }
        node->right = inserted_node;
    } else {
        if (old_value != NULL) {
            *old_value = node->value; 
        }
        node->value = value; 
    }

    return node;
}

void* upo_bst_put(upo_bst_t tree, void* key, void* value) {
    if (tree == NULL ) {
        return NULL; 
    }

    if (tree->root == NULL){
        upo_bst_node_t* new_node = malloc(sizeof(upo_bst_node_t));
        if (new_node == NULL) {
            return NULL; 
        }
        new_node->key = key;
        new_node->value = value;
        new_node->left = NULL;
        new_node->right = NULL;
        tree->root = new_node;
        return NULL; 
    }

    void* old_value = NULL;
    upo_bst_node_t* inserted_node = recursive_put(tree->root, key, value, tree->key_cmp, &old_value);
    if (inserted_node == NULL) {
        return NULL; 
    }

    tree->root = inserted_node; 
    return old_value;
}

upo_bst_node_t* recursive_insert(upo_bst_node_t* node, void* key, void* value,upo_bst_comparator_t cmp) {
    if (node == NULL) {
        upo_bst_node_t* new_node = malloc(sizeof(upo_bst_node_t));
        if (new_node == NULL) {
            return NULL; 
        }
        new_node->key = key;
        new_node->value = value;
        new_node->left = NULL;
        new_node->right = NULL;
        return new_node;
    }

    int cmp_result = cmp(key, node->key);
    if (cmp_result < 0) {
        upo_bst_node_t* inserted_node = recursive_insert(node->left, key, value, cmp);
        if (inserted_node == NULL) {
            return NULL; 
        }
        node->left = inserted_node;
    } else if (cmp_result > 0) {
        upo_bst_node_t* inserted_node = recursive_insert(node->right, key, value, cmp);
        if (inserted_node == NULL) {
            return NULL; 
        }
        node->right = inserted_node;
    } else {
        return  NULL;
    }

    return  node;    
}

void upo_bst_insert(upo_bst_t tree, void *key, void *value)
{
    if (tree == NULL ) {
        return ; 
    }

    if (tree->root == NULL){
        upo_bst_node_t* new_node = malloc(sizeof(upo_bst_node_t));
        if (new_node == NULL) {
            return; 
        }
        new_node->key = key;
        new_node->value = value;
        new_node->left = NULL;
        new_node->right = NULL;
        tree->root = new_node;
        return; 
    }

    upo_bst_node_t* inserted_node = recursive_insert(tree->root, key, value, tree->key_cmp);
    if (inserted_node == NULL) {
        return; 
    }

    tree->root = inserted_node; 
}

void* recursive_get(upo_bst_node_t* tree, const void* key, upo_bst_comparator_t cmp)
{
    if (tree == NULL ) {
        return NULL; 
    }

    int cmp_result = cmp(key, tree->key);

    if(cmp_result == 0)
    {
        return tree->value;
    }
    else if(cmp_result<0)
    {
        return recursive_get(tree->left,key,cmp);
    }
    else
    {
        return recursive_get(tree->right,key,cmp);
    }
}

void* upo_bst_get(const upo_bst_t tree, const void *key)
{
    if (tree == NULL ) {
        return NULL; 
    }

    void* n = recursive_get(tree->root,key,tree->key_cmp);

    if (n == NULL ) {
        return NULL; 
    }

    return n;
}

int upo_bst_contains(const upo_bst_t tree, const void *key)
{
    if (tree == NULL ) {
        return 0; 
    }

    if (upo_bst_get(tree,key)!= NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

upo_bst_node_t* max_rec(upo_bst_node_t* tree)
{
    if (tree == NULL)
    {
        return NULL;
    }
    else if(tree->right != NULL )
    {
        return max_rec(tree->right);
    }
    else
    {
        return tree;
    }
}

upo_bst_node_t* delete2Cl(upo_bst_node_t* tree, int destroy_data,upo_bst_comparator_t cmp)
{
    upo_bst_node_t* max_node = max_rec(tree->left);

    void* temp_key = tree->key;
    void* temp_value = tree->value;

    tree->key = max_node->key;
    tree->value = max_node->value;

    max_node->key = temp_key;
    max_node->value = temp_value;

    tree->left = recursive_delete(tree->left, temp_key, destroy_data, cmp);

    return tree;
}

upo_bst_node_t* delete1Cl(upo_bst_node_t* tree, int destroy_data)
{
    upo_bst_node_t* x;

    if (tree->left != NULL)
    {
        x = tree->left;
    }
    else
    {
        x = tree->right;
    }

    if (destroy_data)
    {
        free(tree->key);
        free(tree->value);
    }

    free(tree);
    return x;
}

void* recursive_delete(upo_bst_node_t* tree, const void *key, int destroy_data,upo_bst_comparator_t cmp)
{
    if (tree == NULL)
    {
        return NULL;
    }

    int cmp_result = cmp(key, tree->key);
    if (cmp_result < 0)
    {
        tree->left=recursive_delete(tree->left, key, destroy_data, cmp);
    }
    else if (cmp_result > 0)
    {
        tree->right=recursive_delete(tree->right, key, destroy_data, cmp);
    }
    else
    {
        if (tree->left != NULL && tree->right != NULL)
        {
            tree = delete2Cl(tree, destroy_data, cmp);
        }
        else
        {
            tree = delete1Cl(tree, destroy_data);
        }
    }
    
    return tree;
}

void upo_bst_delete(upo_bst_t tree, const void *key, int destroy_data)
{
    if (tree == NULL)
    {
        return;
    }
    
    tree->root=recursive_delete(tree->root, key, destroy_data, tree->key_cmp);
    
}

size_t recursive_size(upo_bst_node_t* tree)
{
    if(tree == NULL)
        return 0;
    
    return 1 + recursive_size(tree->left) + recursive_size(tree->right);
}

size_t upo_bst_size(const upo_bst_t tree)
{
    if(upo_bst_is_empty(tree))
        return 0;

    return recursive_size(tree->root);
}

int upo_bst_is_leaf(upo_bst_node_t* tree)
{
    return (tree->left == NULL && tree->right == NULL);
}

size_t max(size_t tree_sx, size_t tree_dx)
{
    if(tree_sx >= tree_dx)
    {
        return tree_sx;
    }
    else
    {
        return tree_dx;
    }
    
}

size_t recursive_height(upo_bst_node_t* tree)
{
    if(tree == NULL)
        return 0;
    
    if (upo_bst_is_leaf(tree))
    {
        return 0;
    }
    
    return 1 + max(recursive_height(tree->left),recursive_height(tree->right));
}

size_t upo_bst_height(const upo_bst_t tree)
{
    if(upo_bst_is_empty(tree))
        return 0;

    return recursive_height(tree->root);   
}

void recursive_traverse(upo_bst_node_t* tree, upo_bst_visitor_t visit, void *visit_context)
{
    if(tree != NULL)
    {
        recursive_traverse(tree->left, visit, visit_context);
        visit(tree->key, tree->value, visit_context);
        recursive_traverse(tree->right, visit, visit_context);
    }
}

void upo_bst_traverse_in_order(const upo_bst_t tree, upo_bst_visitor_t visit, void *visit_context)
{
    if (upo_bst_is_empty(tree))
    {
        return;
    }
    
    recursive_traverse(tree->root, visit, visit_context);
}

int upo_bst_is_empty(const upo_bst_t tree)
{
    if(tree == NULL || tree->root == NULL){
        return 1;
    }
    else{
        return 0;
    }
}


/**** EXERCISE #1 - END of FUNDAMENTAL OPERATIONS ****/


/**** EXERCISE #2 - BEGIN of EXTRA OPERATIONS ****/

upo_bst_node_t* upo_bst_min_rec(upo_bst_node_t* tree)
{
    if (tree == NULL)
    {
        return NULL; 
    }

    if (tree->left == NULL)
    {
        return tree->key;
    }

    return upo_bst_min_rec(tree->left);
}

void* upo_bst_min(const upo_bst_t tree)
{
    if (upo_bst_is_empty(tree))
    {
        return NULL;
    }

    return upo_bst_min_rec(tree->root);
}

upo_bst_node_t* upo_bst_max_rec(upo_bst_node_t* tree)
{
    if (tree == NULL)
    {
        return NULL; 
    }

    if (tree->right == NULL)
    {
        return tree->key;
    }

    return upo_bst_max_rec(tree->right);
}

void* upo_bst_max(const upo_bst_t tree)
{
    if (upo_bst_is_empty(tree))
    {
        return NULL;
    }

    return upo_bst_max_rec(tree->root);
}

void upo_bst_delete_min(upo_bst_t tree, int destroy_data)
{
    if (upo_bst_is_empty(tree))
    {
        return;
    }

    upo_bst_node_t* min = upo_bst_min(tree);
    upo_bst_delete(tree, min,destroy_data);
}

void upo_bst_delete_max(upo_bst_t tree, int destroy_data)
{
    if (upo_bst_is_empty(tree))
    {
        return;
    }

    upo_bst_node_t* max = upo_bst_max(tree);
    upo_bst_delete(tree, max,destroy_data);
}

void* upo_bst_floor_rec(upo_bst_node_t* tree, const void* key,upo_bst_comparator_t cmp)
{
    if (tree == NULL)
    {
        return NULL;
    }

    int cmp_result = cmp(key, tree->key);

    if (cmp_result == 0)
    {
        return tree->key;
    }
    else if (cmp_result < 0)
    {
        return upo_bst_floor_rec(tree->left, key, cmp);
    }
    else
    {
        void* temp = upo_bst_floor_rec(tree->right, key, cmp);
        if (temp != NULL){
            return temp;
        }else{
            return tree->key;
        }
    }
}

void* upo_bst_floor(const upo_bst_t tree, const void *key)
{
    if (upo_bst_is_empty(tree))
    {
        return NULL;
    }

    return upo_bst_floor_rec(tree->root, key, tree->key_cmp);
}

void* upo_bst_ceiling_rec(upo_bst_node_t* tree, const void* key,upo_bst_comparator_t cmp)
{
    if (tree == NULL)
    {
        return NULL;
    }

    int cmp_result = cmp(key, tree->key);

    if (cmp_result == 0)
    {
        return tree->key;
    }
    else if (cmp_result > 0)
    {
        return upo_bst_ceiling_rec(tree->right, key, cmp);
    }
    else
    {
        void* temp = upo_bst_ceiling_rec(tree->left, key, cmp);
        if (temp != NULL){
            return temp;
        }else{
            return tree->key;
        }
    }
}

void* upo_bst_ceiling(const upo_bst_t tree, const void *key)
{
    if (upo_bst_is_empty(tree))
    {
        return NULL;
    }

    return upo_bst_ceiling_rec(tree->root, key, tree->key_cmp);
}

upo_bst_key_list_t recursive_keys_range(upo_bst_node_t* tree, const void* low_key, const void* high_key, upo_bst_key_list_t list, upo_bst_comparator_t cmp)
{
    if (tree == NULL)
    {
        return list;
    }

    int cmp_low = cmp(low_key, tree->key);          
    int cmp_high = cmp(tree->key, high_key);
    
    list = recursive_keys_range(tree->left, low_key, high_key, list, cmp);
    list = recursive_keys_range(tree->right, low_key, high_key, list, cmp);
    
    if (cmp_low <= 0 && cmp_high <= 0)
    {
        upo_bst_key_list_node_t *new_node = (upo_bst_key_list_node_t*)malloc(sizeof(upo_bst_key_list_node_t));
        if (new_node == NULL)
        {
            return NULL;
        }

        new_node->key = tree->key;
        new_node->next = list;
        list = new_node;
    }

    

    return list;
}

upo_bst_key_list_t upo_bst_keys_range(const upo_bst_t tree, const void* low_key, const void* high_key)
{
    if (upo_bst_is_empty(tree))
    {
        return NULL; 
    }

    upo_bst_key_list_t list = NULL;

    list = recursive_keys_range(tree->root, low_key, high_key, list, tree->key_cmp);

    return list;
}

upo_bst_key_list_t recursive_keys(upo_bst_node_t* tree, upo_bst_key_list_t list)
{
    if (tree == NULL)
        return list;
    
    upo_bst_key_list_node_t *temp = (upo_bst_key_list_node_t*)malloc(sizeof(upo_bst_key_list_node_t));
    if (temp == NULL)
        return NULL; 
    
    temp->key = tree->key;
    temp->next = list; 
    list = temp;

    list = recursive_keys(tree->left, list);
    list = recursive_keys(tree->right, list);
    
    return list; 
}

upo_bst_key_list_t upo_bst_keys(const upo_bst_t tree)
{
    if (upo_bst_is_empty(tree))
    {
        return NULL;  
    }

    upo_bst_key_list_t list = NULL;

    list = recursive_keys(tree->root, list);
    
    return list;  
}

int upo_bst_is_bst_rec(upo_bst_node_t* node, const void* min_key, const void* max_key, upo_bst_comparator_t cmp)
{
    if (node == NULL)
    {
        return 1;  
    }

    if ((min_key != NULL && cmp(node->key, min_key) <= 0) || (max_key != NULL && cmp(node->key, max_key) >= 0))
    {
        return 0;
    }

    return upo_bst_is_bst_rec(node->left, min_key, node->key, cmp) &&
           upo_bst_is_bst_rec(node->right, node->key, max_key, cmp);
}

int upo_bst_is_bst(const upo_bst_t tree, const void* min_key, const void* max_key)
{
    if (upo_bst_is_empty(tree))
    {
        return 1;
    }

    return upo_bst_is_bst_rec(tree->root, min_key, max_key, tree->key_cmp);
}


/**** EXERCISE #2 - END of EXTRA OPERATIONS ****/


upo_bst_comparator_t upo_bst_get_comparator(const upo_bst_t tree)
{
    if (tree == NULL)
    {
        return NULL;
    }

    return tree->key_cmp;
}
