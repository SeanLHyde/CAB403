#include <stdio.h>
#include <stdlib.h>
#include "dbl_vector.h"

double max(double a, double b){
    return a > b ? a : b;
}
double min(double a, double b){
    return a < b ? a : b;
}

void dv_init( dbl_vector_t* vec ) {
    double new_mem_size = DV_INITIAL_CAPACITY * 8;
    vec->capacity = DV_INITIAL_CAPACITY;
    vec->size = 0;
    vec->data = malloc(new_mem_size); //
}

void dv_ensure_capacity( dbl_vector_t* vec, size_t new_size ) {
    int old_capacity = vec->capacity;
    int old_size = vec->size;
    double* old_data = vec->data;
    int new_capacity = max(old_capacity * DV_GROWTH_FACTOR, new_size);
    double new_mem_size = new_capacity * 8;

    if(new_size <= old_capacity){
        vec->capacity = old_capacity;
        vec->data = old_data;
    } else{
        vec->capacity = new_capacity;
        vec->data = realloc(old_data, new_mem_size);
    }
}

void dv_destroy( dbl_vector_t* vec ) {
    vec->capacity = 0;
    vec->size = 0;
    free(vec->data);
    vec->data = NULL;
}

void dv_copy( dbl_vector_t* vec, dbl_vector_t* dest ) {
    if(vec != dest){
        dest->size = vec->size;
        dv_ensure_capacity(dest, vec->size);
        for(int i = 0; i < vec->size; i++){
            dest->data[i] = vec->data[i];
        }
    }
}

void dv_clear( dbl_vector_t* vec ) {
    vec->size = 0;
}

void dv_push( dbl_vector_t* vec, double new_item ) {
    int old_size = vec->size;
    double* old_data = vec->data;
    vec->size = old_size + 1;
    for (int i = 0; i < old_size; i++){
        vec->data[i] = old_data[i];
    }
    dv_ensure_capacity(vec, old_size + 1);
    vec->data[old_size] = new_item;
}

void dv_pop( dbl_vector_t* vec ) {
   double* old_data = vec->data;
   int old_size = vec->size;

   if(old_size > 0){
    vec->size = old_size -1;
    for (int i = 0; i < old_size; i++)
    {
        vec->data[i] = old_data[i];
    }
   }else{
    vec->size = 0;
   }
}

double dv_last( dbl_vector_t* vec ) {
    double result = NAN;
    double* old_data = vec->data;
    int old_size = vec->size;
    int old_capacity = vec->capacity;
    vec->size = old_size;
    vec->capacity = old_capacity;
    vec->data = old_data;

    for (int i = 0; i < vec->size; i++)
    {
        vec->data[i] = old_data[i];
    }
    if(vec->size > 0){
        return vec->data[vec->size - 1];
    }
    return result;
}

void dv_insert_at( dbl_vector_t* vec, size_t pos, double new_item ) {
   int loc = min(pos, vec->size);
    vec->size = vec->size + 1;
    dv_ensure_capacity(vec, vec->size);
    for (int i = vec->size - 1; i > loc; i--) {
        vec->data[i] = vec->data[i - 1];
    }
    vec->data[loc] = new_item;
    
}

void dv_remove_at( dbl_vector_t* vec, size_t pos ) {
    int old_size = vec->size;
    double loc = min(pos, old_size);
    double* old_data = vec->data;
    for (int i = 0; i < loc; i++)
    {
        vec->data[i] = old_data[i];
        
    }
    for (int i = loc+1; i < vec->size; i++)
    {
        vec->data[i-1] = old_data[i];      
    }  
    if (pos >= old_size)
    {
        vec->size = old_size;
    }
    else {
        vec->size = old_size - 1;
    }
}

void dv_foreach( dbl_vector_t* vec, void (*callback)(double, void*), void* info ) {
    double* old_data = vec->data;
    int old_size = vec->size;
    int old_capacity = vec->capacity;

    vec->capacity = old_capacity;
    vec->size = old_size;
    vec->data = old_data;

    for (int i = 0; i < vec->size; i++)
    {
        callback(vec->data[i], info);
    }
}