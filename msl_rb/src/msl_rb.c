#include "msl_ring_buffer.h"

static msl_err_t msl_rb_is_handle_valid(MSL_RB_HANDLE* p_handle){
    msl_err_t retval = MSL_OK;
    if(p_handle != NULL){
        if(((p_handle->num_elements)>0) && ((p_handle->element_size)>0) && ((p_handle->p_buff)!=NULL)){
            retval = MSL_OK;
        }else{
            retval = MSL_PARAM_ERROR;
        }
    }else{
        retval = MSL_PARAM_ERROR;
    }
    return retval;
}

static void msl_rb_reset(MSL_RB_HANDLE* p_handle){
    p_handle->read_idx = 0;
    p_handle->write_idx = 0;
    p_handle->full = false;
}

static void msl_rb_advance_idx(MSL_RB_HANDLE* p_handle){
    if(p_handle->full){
        p_handle->read_idx = ((p_handle->read_idx) + 1) % ( (p_handle->num_elements)*(p_handle->element_size));
    }

    p_handle->write_idx = ((p_handle->write_idx) + 1) % ( (p_handle->num_elements)*(p_handle->element_size));

    p_handle->full = ((p_handle->read_idx)==(p_handle->write_idx));
}

static void msl_rb_retreat_idx(MSL_RB_HANDLE* p_handle){
    p_handle->full = false;
    p_handle->read_idx = ((p_handle->read_idx) + 1) % ( (p_handle->num_elements)*(p_handle->element_size));
}

msl_err_t msl_rb_is_empty(MSL_RB_HANDLE* p_handle){
    msl_err_t retval = MSL_FALSE;
    if(msl_rb_is_handle_valid(p_handle) == MSL_OK){
        if((!(p_handle->full)) && ((p_handle->read_idx)==(p_handle->write_idx))){
            retval = MSL_TRUE;
        }
    }else{
        retval = MSL_PARAM_ERROR;
    }
    return retval;
}

msl_err_t msl_rb_is_full(MSL_RB_HANDLE* p_handle){
    msl_err_t retval = MSL_FALSE;
    if(msl_rb_is_handle_valid(p_handle) == MSL_OK){
        if((p_handle->full) == true){
            retval = MSL_TRUE;
        }
    }else{
        retval = MSL_PARAM_ERROR;
    }
    return retval;
}

msl_err_t msl_rb_init(MSL_RB_HANDLE* p_handle,size_t num_elements,size_t element_size,void* p_buff){
    msl_err_t retval = MSL_OK;
    p_handle->num_elements = num_elements;
    p_handle->element_size = element_size;
    p_handle->p_buff = p_buff;
    if(msl_rb_is_handle_valid(p_handle) == MSL_OK){
            msl_rb_reset(p_handle);
            if(msl_rb_is_empty(p_handle) != MSL_TRUE){
                retval = MSL_ASSERT_FAIL;
            }
    }else{
        retval = MSL_PARAM_ERROR;
    }
    return retval;
}

msl_err_t msl_rb_get_num_elements(MSL_RB_HANDLE* p_handle,size_t* p_num_elements){
    msl_err_t retval = MSL_OK;
    if(msl_rb_is_handle_valid(p_handle) == MSL_OK){
        if(p_num_elements != NULL){
            if((p_handle->full)==true){
                *p_num_elements = p_handle->num_elements;
            }else{
                if((p_handle->write_idx)>=(p_handle->read_idx)){
                    *p_num_elements = ((p_handle->write_idx) - (p_handle->read_idx))/(p_handle->element_size);
                }else{
                    *p_num_elements = (((p_handle->num_elements)*(p_handle->element_size))+(p_handle->write_idx)-(p_handle->read_idx))/(p_handle->element_size);
                }
            }
        }else{
            retval = MSL_PARAM_ERROR;
        }
    }else{
        retval = MSL_PARAM_ERROR;
    }
    return retval;
}

msl_err_t __msl_rb_get(MSL_RB_HANDLE* p_handle,uint8_t* p_buff){
    msl_err_t retval = MSL_OK;
    uint8_t* buff_byte_ptr;
    if(msl_rb_is_handle_valid(p_handle) == MSL_OK){
        if(p_buff != NULL){
            if(msl_rb_is_empty(p_handle) == MSL_FALSE){
                buff_byte_ptr = (uint8_t*)p_handle->p_buff;
                *p_buff = buff_byte_ptr[p_handle->read_idx];
                msl_rb_retreat_idx(p_handle);
            }else{
                retval = MSL_EMPTY;
            }
        }else{
            retval = MSL_PARAM_ERROR;
        }
    }else{
        retval = MSL_PARAM_ERROR;
    }
    return retval;
}

msl_err_t __msl_rb_put(MSL_RB_HANDLE* p_handle,uint8_t val){
    msl_err_t retval = MSL_OK;
    uint8_t* buff_byte_ptr;
    if(msl_rb_is_handle_valid(p_handle) == MSL_OK){
        buff_byte_ptr = (uint8_t*)p_handle->p_buff;
        buff_byte_ptr[p_handle->write_idx] = val;
        msl_rb_advance_idx(p_handle);
    }else{
        retval = MSL_PARAM_ERROR;
    }
    return retval;
}

msl_err_t __msl_rb_put_no_overwrite(MSL_RB_HANDLE* p_handle,uint8_t val){
    msl_err_t retval = MSL_OK;
    uint8_t* buff_byte_ptr;
    if(msl_rb_is_handle_valid(p_handle) == MSL_OK){
        if(msl_rb_is_full(p_handle) == MSL_FALSE){
            buff_byte_ptr = (uint8_t*)p_handle->p_buff;
            buff_byte_ptr[p_handle->write_idx] = val;
            msl_rb_advance_idx(p_handle);
        }else{
            retval = MSL_FULL;
        }
    }else{
        retval = MSL_PARAM_ERROR;
    }
    return retval;
}

msl_err_t msl_rb_get_element(MSL_RB_HANDLE* p_handle,void* p_element){
    msl_err_t retval = MSL_OK;
    uint8_t* byte_ptr = (uint8_t*)p_element;
    if(msl_rb_is_handle_valid(p_handle) == MSL_OK){
        if((p_element != NULL)){
            retval = msl_rb_is_empty(p_handle);
            if(retval == MSL_FALSE){
                for(uint16_t idx=0;idx<(p_handle->element_size);idx++){
                    __msl_rb_get(p_handle,&byte_ptr[idx]);
                }
                retval = MSL_OK;
            }
        }else{
            retval = MSL_PARAM_ERROR;
        }
    }else{
        retval = MSL_PARAM_ERROR;
    }
    return retval;
}

msl_err_t msl_rb_put_element(MSL_RB_HANDLE* p_handle,void* p_element){
    msl_err_t retval = MSL_OK;
    uint8_t* byte_ptr = (uint8_t*)p_element;
    if(msl_rb_is_handle_valid(p_handle) == MSL_OK){
        if((p_element != NULL)){
            for(uint16_t idx=0;idx<(p_handle->element_size);idx++){
                __msl_rb_put(p_handle,byte_ptr[idx]);
            }
        }else{
            retval = MSL_PARAM_ERROR;
        }
    }else{
        retval = MSL_PARAM_ERROR;
    }
    return retval;
}

msl_err_t msl_rb_put_element_no_overwrite(MSL_RB_HANDLE* p_handle,void* p_element){
    msl_err_t retval = MSL_OK;
    uint8_t* byte_ptr = (uint8_t*)p_element;
    if(msl_rb_is_handle_valid(p_handle) == MSL_OK){
        if(p_element != NULL){
            if(msl_rb_is_full(p_handle) == MSL_FALSE){
                for(uint16_t idx=0;idx<(p_handle->element_size);idx++){
                    __msl_rb_put_no_overwrite(p_handle,byte_ptr[idx]);
                }
            }else{
                retval = MSL_FULL;
            }
        }else{
            retval = MSL_PARAM_ERROR;
        }
    }else{
        retval = MSL_PARAM_ERROR;
    }
    return retval;
}

msl_err_t msl_rb_deinit(MSL_RB_HANDLE* p_handle){
    msl_err_t retval = MSL_OK;
    if(msl_rb_is_handle_valid(p_handle) == MSL_OK){
        msl_rb_reset(p_handle);
        p_handle->num_elements = 0;
        p_handle->element_size = 0;
        p_handle->p_buff = NULL;
    }else{
        retval = MSL_PARAM_ERROR;
    }
    return retval;
}
