#include "gen_uuid.hpp"
#include <uuid/uuid.h>

std::string genUuid()
{
  uuid_t out;
  uuid_generate(out);
  char uuid_str[37]; // ex. "1b4e28ba-2fa1-11d2-883f-0016d3cca427" + "\0"
  uuid_unparse_lower(out, uuid_str);
  uuid_clear(out);
  return std::string{uuid_str};
}
