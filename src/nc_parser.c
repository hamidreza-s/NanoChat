#include "nc.h"

int
nc_parser_make_otoc_msg(char **type, char **body, char **msg)
{
  JSON_Value *root_value = json_value_init_object();
  JSON_Object *root_object = json_value_get_object(root_value);
  json_object_set_string(root_object, "type", *type);
  json_object_set_string(root_object, "body", *body);
  *msg = json_serialize_to_string(root_value);

  return 0;
}

int
nc_parser_extract_otoc_msg(char **msg, char **type, char **body)
{
  JSON_Value *root_value;
  JSON_Object *root_object;
  root_value = json_parse_string(*msg);
  root_object = json_value_get_object(root_value);
  *type = json_object_get_string(root_object, "type");
  *body = json_object_get_string(root_object, "body");
  
  return 0;
}
