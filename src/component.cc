#include "component.h"

namespace Xi {

param_type_f_t Component::query_f(param_key_t key) const { return { }; }
param_type_v_t Component::query_v(param_key_t key) const { return { }; }
param_type_i_t Component::query_i(param_key_t key) const { return { }; }
param_type_u_t Component::query_u(param_key_t key) const { return { }; }
param_type_v_t Component::query_x(param_key_t key) const { return { }; }

void Component::set_f(param_key_t key, param_type_f_t) { }
void Component::set_i(param_key_t key, param_type_v_t) { }
void Component::set_u(param_key_t key, param_type_i_t) { }
void Component::set_v(param_key_t key, param_type_u_t) { }
void Component::set_x(param_key_t key, param_type_x_t) { }


} // namespace Xi

