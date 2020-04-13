#include "../../msl_dem/inc/msl_err.h"
#include <stddef.h>
#include "stdbool.h"

typedef struct{
    void* p_buff;
    size_t num_elements;
    size_t element_size;
    size_t write_idx;
    size_t read_idx;
    bool full;
}msl_rb_handle_t;

typedef msl_rb_handle_t MSL_RB_HANDLE;

msl_err_t msl_rb_init(MSL_RB_HANDLE* p_handle,size_t num_elements,size_t element_size,void* p_buff);

msl_err_t msl_rb_get_num_elements(MSL_RB_HANDLE* p_handle,size_t* p_num_elements);
msl_err_t msl_rb_get_element(MSL_RB_HANDLE* p_handle,void* p_element);
msl_err_t msl_rb_put_element(MSL_RB_HANDLE* p_handle,void* p_element);
msl_err_t msl_rb_put_element_no_overwrite(MSL_RB_HANDLE* p_handle,void* p_element);

msl_err_t msl_rb_is_empty(MSL_RB_HANDLE* p_handle);
msl_err_t msl_rb_is_full(MSL_RB_HANDLE* p_handle);

msl_err_t __msl_rb_put(MSL_RB_HANDLE* p_handle,uint8_t val);
msl_err_t __msl_rb_get(MSL_RB_HANDLE* p_handle,uint8_t* p_buff);
msl_err_t __msl_rb_put_no_overwrite(MSL_RB_HANDLE* p_handle,uint8_t val);

msl_err_t msl_rb_deinit(MSL_RB_HANDLE* p_handle);

