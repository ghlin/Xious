#include "component.h"

namespace Xi {

param_v_value_t   Component::get(param_v_key_t key) const { XI_UNUSED(key); return { }; }
param_f_value_t   Component::get(param_f_key_t key) const { XI_UNUSED(key); return { }; }
param_i_value_t   Component::get(param_i_key_t key) const { XI_UNUSED(key); return { }; }
param_u_value_t   Component::get(param_u_key_t key) const { XI_UNUSED(key); return { }; }
param_x_value_t   Component::get(param_x_key_t key) const { XI_UNUSED(key); return { }; }

void Component::set(param_v_key_t key, param_v_value_t param) { XI_UNUSED(key); XI_UNUSED(param); }
void Component::set(param_f_key_t key, param_f_value_t param) { XI_UNUSED(key); XI_UNUSED(param); }
void Component::set(param_i_key_t key, param_i_value_t param) { XI_UNUSED(key); XI_UNUSED(param); }
void Component::set(param_u_key_t key, param_u_value_t param) { XI_UNUSED(key); XI_UNUSED(param); }
void Component::set(param_x_key_t key, param_x_value_t param) { XI_UNUSED(key); XI_UNUSED(param); }

} // namespace Xi

