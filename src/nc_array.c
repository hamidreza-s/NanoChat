#include "nc.h"

nc_array*
nc_array_string_new(int array_len, int string_len)
{
  int i;
  char **array_ptr = (char**) malloc(array_len * sizeof(char**));

  for(i = 0; i < array_len; i++) {
    array_ptr[i] = (char*) malloc(string_len * sizeof(char));
  }
  
  nc_array *array = (nc_array*) malloc(sizeof(nc_array*));
  array->array_ptr = array_ptr;
  array->array_len = array_len;
  array->string_len = string_len;

  return array;
}

int
nc_array_string_set(nc_array *array, int index, char *string)
{
  strncpy(array->array_ptr[index], string, array->string_len);
  return 0;
}

char*
nc_array_string_get(nc_array *array, int index)
{
  return array->array_ptr[index];
}

int
nc_array_string_len(nc_array *array)
{
  return array->array_len;
}

int
nc_array_string_free(nc_array *array)
{
  int i;
  for(i = 0; i < array->array_len; i++) {
    free(array->array_ptr[i]);
  }
  free(array->array_ptr);
  return 0;
}
