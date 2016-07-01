#include "nc.h"

int
nc_json_make_otoc_msg(char **type, char **body, int original_body_len, char **msg)
{
  JSON_Value *root_value = json_value_init_object();
  JSON_Object *root_object = json_value_get_object(root_value);
  json_object_set_string(root_object, "type", *type);
  json_object_set_string(root_object, "body", *body);
  json_object_set_number(root_object, "original_body_len", original_body_len);
  *msg = json_serialize_to_string(root_value);

  return 0;
}

int
nc_json_extract_otoc_msg(char **msg, char **type, int *original_body_len, char **body)
{
  JSON_Value *root_value;
  JSON_Object *root_object;
  root_value = json_parse_string(*msg);
  root_object = json_value_get_object(root_value);
  *type = json_object_get_string(root_object, "type");
  *body = json_object_get_string(root_object, "body");
  *original_body_len = json_object_get_number(root_object, "original_body_len");
  
  return 0;
}
