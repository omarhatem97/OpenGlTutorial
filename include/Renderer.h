#ifdef __GNUC__
    #define DEBUG_BREAK() __builtin_trap()
#else
    #define DEBUG_BREAK() __debugbreak()
#endif

#define ASSERT(x) if(!(x)) DEBUG_BREAK()
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))


bool GLLogCall(const char* function, const char* file, int line);

void GLClearError();
