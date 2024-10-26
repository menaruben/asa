#include <exception>
#include <string>

namespace asa {
enum Type;
enum Error;
std::string typeToStr(Type t);

struct Object;
Object ERROR_OK;
Object ERROR_STACKOVERFLOW;
Object ERROR_STACKUNDERFLOW;
Object ERROR_TYPEMISMATCH;
Object ERROR_ARITHMETIC;
Object ERROR_DIVBYZERO;
Object ERROR_ILLEGALINSTRUCTION;
} // namespace asa
