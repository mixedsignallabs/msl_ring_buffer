#include "msl_err_codes.h"

typedef uint32_t msl_err_t;

const char* msl_err_code_to_string(msl_err_t code);

#define MSL_TEST(result,expected) (result==expected?MSL_TEST_PASS:MSL_TEST_FAIL)
#define MSL_TEST_BANNER_API(api_name) printf("\r\n[*] %s\r\n",#api_name);
#define MSL_TEST_PRINT(test_expression,expected) printf("    %s   :::::::::::::  %s    \r\n",#test_expression,msl_err_code_to_string(MSL_TEST(test_expression,expected)));
#define MSL_TEST_VAL_PRINT(got,expected) printf("    got: %d    expected: %d  ::::::::::::: %s \r\n",got,expected,msl_err_code_to_string(MSL_TEST(got,expected)) );
#define MSL_ASSERT(result,expected) (result==expected?MSL_ASSERT_SUCCESS:MSL_ASSERT_FAIL)
#define MSL_TEST_BANNER_1(banner) printf("\r\n\r\n---------------- %s   ----------------\r\n",#banner);
