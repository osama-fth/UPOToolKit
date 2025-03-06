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

#include <assert.h>
#include "sort_private.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void upo_insertion_sort(void *base, size_t n, size_t size, upo_sort_comparator_t cmp)
{
    unsigned char *pc = base;
    
    if(pc == NULL)
        return;
    
    for(size_t i = 1; i<=n-1; i++)
    {
        for(size_t j = i; j > 0; j--)
        {
            if(cmp(pc + j*size, pc + (j-1)*size)<0)
            {
                upo_swap(pc + j*size, pc + (j-1)*size, size);
            }
            else
            {
                break;
            }
        }
    }
}

void upo_copy_array(void* aux, void* base, size_t lo, size_t hi, size_t size)
{
    unsigned char *src = (unsigned char*)base + lo * size; 
    unsigned char *dst = (unsigned char*)aux;  

    for (size_t i = lo; i <= hi; i++) {
        memcpy(dst, src, size);  
        src += size;  
        dst += size;  
    }
}

static void upo_merge_sort_merge(void *base, size_t lo, size_t mid, size_t hi, size_t size, upo_sort_comparator_t cmp)
{
    size_t i = 0;
    size_t j = mid + 1 - lo;

    unsigned char *aux = (unsigned char*)malloc((hi-lo+1) * size);
    if (aux == NULL)
        return;
    
    upo_copy_array(aux,base,lo,hi,size);

    for (size_t k = lo; k <= hi; k++) {
        if (i > mid - lo) 
        {
            memcpy((unsigned char*)base + k * size, aux + j * size, size);
            j++;
        } 
        else if (j > hi - lo) 
        {
            memcpy((unsigned char*)base + k * size, aux + i * size, size);
            i++;
        } 
        else if (cmp(aux + i * size, aux + j * size) <= 0) 
        {
            memcpy((unsigned char*)base + k * size, aux + i * size, size);
            i++;
        } 
        else
        {
            memcpy((unsigned char*)base + k * size, aux + j * size, size);
            j++;
        }
    }

    free(aux);
}

static void upo_merge_sort_rec(void *base, size_t lo, size_t hi, size_t size, upo_sort_comparator_t cmp)
{
    if (lo >= hi)
    {
        return;
    }
    
    size_t mid = (lo + hi)/2;
    upo_merge_sort_rec(base, lo, mid, size, cmp);
    upo_merge_sort_rec(base, mid+1, hi, size, cmp);
    upo_merge_sort_merge(base,lo,mid,hi,size,cmp);
}

void upo_merge_sort(void *base, size_t n, size_t size, upo_sort_comparator_t cmp)
{
    if(base == NULL || n == 0)
        return;

    upo_merge_sort_rec(base, 0, n-1, size, cmp);
}

static size_t upo_quick_sort_partition(void *base, size_t lo, size_t hi, size_t size, upo_sort_comparator_t cmp)
{
    size_t p = lo;
    size_t i = lo;
    size_t j = hi+1;

    unsigned char *array = (unsigned char *)base;

    while (1) 
    {
        do 
        {
            i++;
        } while (i <= hi && cmp(array + i * size, array + p * size) < 0);

        do 
        {
            j--;
        } while (j > lo && cmp(array + j * size, array + p * size) > 0);

        if (i >= j) 
            break;

        upo_swap(array + i * size, array + j * size, size);
    }

    if (p != j)
        upo_swap(array + p * size, array + j * size, size);
    

    return j;    
}


static void upo_quick_sort_rec(void *base, size_t lo, size_t hi, size_t size, upo_sort_comparator_t cmp)
{
    if (lo >= hi)
    {
        return;
    }
    
    size_t j = upo_quick_sort_partition(base,lo,hi,size,cmp);
    
    if (j > 0) 
        upo_quick_sort_rec(base, lo, j - 1, size, cmp);
        
    upo_quick_sort_rec(base,j+1,hi,size,cmp);
    
}

void upo_quick_sort(void *base, size_t n, size_t size, upo_sort_comparator_t cmp)
{
  if(base == NULL || n == 0)
        return;

    upo_quick_sort_rec(base, 0, n-1, size, cmp);
}



