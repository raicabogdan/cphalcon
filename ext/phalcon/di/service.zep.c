
#ifdef HAVE_CONFIG_H
#include "../../ext_config.h"
#endif

#include <php.h>
#include "../../php_ext.h"
#include "../../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/object.h"
#include "kernel/operators.h"
#include "kernel/memory.h"
#include "kernel/exception.h"
#include "kernel/array.h"
#include "kernel/fcall.h"
#include "Zend/zend_closures.h"
#include "ext/spl/spl_exceptions.h"


/**
 * This file is part of the Phalcon Framework.
 *
 * (c) Phalcon Team <team@phalcon.io>
 *
 * For the full copyright and license information, please view the LICENSE.txt
 * file that was distributed with this source code.
 */
/**
 * Represents individually a service in the services container
 *
 *```php
 * $service = new \Phalcon\Di\Service(
 *     "request",
 *     \Phalcon\Http\Request::class
 * );
 *
 * $request = service->resolve();
 *```
 */
ZEPHIR_INIT_CLASS(Phalcon_Di_Service)
{
	ZEPHIR_REGISTER_CLASS(Phalcon\\Di, Service, phalcon, di_service, phalcon_di_service_method_entry, 0);

	/**
	 * @var mixed
	 */
	zend_declare_property_null(phalcon_di_service_ce, SL("definition"), ZEND_ACC_PROTECTED);
	/**
	 * @var bool
	 */
	zend_declare_property_bool(phalcon_di_service_ce, SL("resolved"), 0, ZEND_ACC_PROTECTED);
	/**
	 * @var bool
	 */
	zend_declare_property_bool(phalcon_di_service_ce, SL("shared"), 0, ZEND_ACC_PROTECTED);
	/**
	 * @var mixed|null
	 */
	zend_declare_property_null(phalcon_di_service_ce, SL("sharedInstance"), ZEND_ACC_PROTECTED);
	zend_class_implements(phalcon_di_service_ce, 1, phalcon_di_serviceinterface_ce);
	return SUCCESS;
}

/**
 * Phalcon\Di\Service
 */
PHP_METHOD(Phalcon_Di_Service, __construct)
{
	zend_bool shared;
	zval *definition, definition_sub, *shared_param = NULL, __$true, __$false;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&definition_sub);
	ZVAL_BOOL(&__$true, 1);
	ZVAL_BOOL(&__$false, 0);
	ZEND_PARSE_PARAMETERS_START(1, 2)
		Z_PARAM_ZVAL(definition)
		Z_PARAM_OPTIONAL
		Z_PARAM_BOOL(shared)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 1, &definition, &shared_param);
	if (!shared_param) {
		shared = 0;
	} else {
		}
	zephir_update_property_zval(this_ptr, ZEND_STRL("definition"), definition);
	if (shared) {
		zephir_update_property_zval(this_ptr, ZEND_STRL("shared"), &__$true);
	} else {
		zephir_update_property_zval(this_ptr, ZEND_STRL("shared"), &__$false);
	}
}

/**
 * Returns the service definition
 */
PHP_METHOD(Phalcon_Di_Service, getDefinition)
{

	RETURN_MEMBER(getThis(), "definition");
}

/**
 * Returns a parameter in a specific position
 *
 * @return array
 */
PHP_METHOD(Phalcon_Di_Service, getParameter)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *position_param = NULL, arguments, parameter, _0, _1;
	zend_long position;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&arguments);
	ZVAL_UNDEF(&parameter);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(position)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &position_param);
	zephir_memory_observe(&_0);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("definition"), PH_NOISY_CC);
	if (UNEXPECTED(Z_TYPE_P(&_0) != IS_ARRAY)) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_di_exception_ce, "Definition must be an array to obtain its parameters", "phalcon/Di/Service.zep", 80);
		return;
	}
	zephir_read_property(&_1, this_ptr, ZEND_STRL("definition"), PH_NOISY_CC | PH_READONLY);
	if (zephir_array_isset_string_fetch(&arguments, &_1, SL("arguments"), 1)) {
		if (zephir_array_isset_long_fetch(&parameter, &arguments, position, 1)) {
			RETURN_CTOR(&parameter);
		}
	}
	RETURN_MM_NULL();
}

/**
 * Returns true if the service was resolved
 */
PHP_METHOD(Phalcon_Di_Service, isResolved)
{

	RETURN_MEMBER(getThis(), "resolved");
}

/**
 * Check whether the service is shared or not
 */
PHP_METHOD(Phalcon_Di_Service, isShared)
{

	RETURN_MEMBER(getThis(), "shared");
}

/**
 * Resolves the service
 *
 * @param array parameters
 */
PHP_METHOD(Phalcon_Di_Service, resolve)
{
	zend_class_entry *_6$$12;
	zend_bool found = 0, _1, _4$$5;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *parameters = NULL, parameters_sub, *container = NULL, container_sub, __$true, __$false, __$null, definition, instance, builder, _0, _2, _3, _5$$12, _7$$19;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&parameters_sub);
	ZVAL_UNDEF(&container_sub);
	ZVAL_BOOL(&__$true, 1);
	ZVAL_BOOL(&__$false, 0);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&definition);
	ZVAL_UNDEF(&instance);
	ZVAL_UNDEF(&builder);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_5$$12);
	ZVAL_UNDEF(&_7$$19);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(0, 2)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(parameters)
		Z_PARAM_OBJECT_OF_CLASS_OR_NULL(container, phalcon_di_diinterface_ce)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 0, 2, &parameters, &container);
	if (!parameters) {
		parameters = &parameters_sub;
		parameters = &__$null;
	}
	if (!container) {
		container = &container_sub;
		container = &__$null;
	}
	zephir_read_property(&_0, this_ptr, ZEND_STRL("shared"), PH_NOISY_CC | PH_READONLY);
	_1 = zephir_is_true(&_0);
	if (_1) {
		zephir_read_property(&_2, this_ptr, ZEND_STRL("sharedInstance"), PH_NOISY_CC | PH_READONLY);
		_1 = Z_TYPE_P(&_2) != IS_NULL;
	}
	if (_1) {
		RETURN_MM_MEMBER(getThis(), "sharedInstance");
	}
	found = 1;
	ZEPHIR_INIT_VAR(&instance);
	ZVAL_NULL(&instance);
	zephir_read_property(&_3, this_ptr, ZEND_STRL("definition"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&definition, &_3);
	if (Z_TYPE_P(&definition) == IS_STRING) {
		if (zephir_class_exists(&definition, 1)) {
			_4$$5 = Z_TYPE_P(parameters) == IS_ARRAY;
			if (_4$$5) {
				_4$$5 = ((zephir_fast_count_int(parameters)) ? 1 : 0);
			}
			if (_4$$5) {
				ZEPHIR_INIT_NVAR(&instance);
				ZEPHIR_LAST_CALL_STATUS = zephir_create_instance_params(&instance, &definition, parameters);
				zephir_check_call_status();
			} else {
				ZEPHIR_INIT_NVAR(&instance);
				ZEPHIR_LAST_CALL_STATUS = zephir_create_instance(&instance, &definition);
				zephir_check_call_status();
			}
		} else {
			found = 0;
		}
	} else {
		if (Z_TYPE_P(&definition) == IS_OBJECT) {
			if (zephir_is_instance_of(&definition, SL("Closure"))) {
				if (Z_TYPE_P(container) != IS_NULL) {
					_6$$12 = zephir_fetch_class_str_ex(SL("Closure"), ZEND_FETCH_CLASS_AUTO);
					ZEPHIR_CALL_CE_STATIC(&_5$$12, _6$$12, "bind", NULL, 0, &definition, container);
					zephir_check_call_status();
					ZEPHIR_CPY_WRT(&definition, &_5$$12);
				}
				if (Z_TYPE_P(parameters) == IS_ARRAY) {
					ZEPHIR_INIT_NVAR(&instance);
					ZEPHIR_CALL_USER_FUNC_ARRAY(&instance, &definition, parameters);
					zephir_check_call_status();
				} else {
					ZEPHIR_INIT_NVAR(&instance);
					ZEPHIR_CALL_USER_FUNC(&instance, &definition);
					zephir_check_call_status();
				}
			} else {
				ZEPHIR_CPY_WRT(&instance, &definition);
			}
		} else {
			if (Z_TYPE_P(&definition) == IS_ARRAY) {
				ZEPHIR_INIT_VAR(&builder);
				object_init_ex(&builder, phalcon_di_service_builder_ce);
				if (zephir_has_constructor(&builder)) {
					ZEPHIR_CALL_METHOD(NULL, &builder, "__construct", NULL, 0);
					zephir_check_call_status();
				}

				ZEPHIR_CALL_METHOD(&instance, &builder, "build", NULL, 223, container, &definition, parameters);
				zephir_check_call_status();
			} else {
				found = 0;
			}
		}
	}
	if (UNEXPECTED(found == 0)) {
		ZEPHIR_INIT_VAR(&_7$$19);
		object_init_ex(&_7$$19, phalcon_di_exception_serviceresolutionexception_ce);
		ZEPHIR_CALL_METHOD(NULL, &_7$$19, "__construct", NULL, 33);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_7$$19, "phalcon/Di/Service.zep", 195);
		ZEPHIR_MM_RESTORE();
		return;
	}
	zephir_read_property(&_3, this_ptr, ZEND_STRL("shared"), PH_NOISY_CC | PH_READONLY);
	if (zephir_is_true(&_3)) {
		zephir_update_property_zval(this_ptr, ZEND_STRL("sharedInstance"), &instance);
	}
	if (1) {
		zephir_update_property_zval(this_ptr, ZEND_STRL("resolved"), &__$true);
	} else {
		zephir_update_property_zval(this_ptr, ZEND_STRL("resolved"), &__$false);
	}
	RETURN_CCTOR(&instance);
}

/**
 * Set the service definition
 */
PHP_METHOD(Phalcon_Di_Service, setDefinition)
{
	zval *definition, definition_sub;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&definition_sub);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(definition)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &definition);
	zephir_update_property_zval(this_ptr, ZEND_STRL("definition"), definition);
}

/**
 * Changes a parameter in the definition without resolve the service
 */
PHP_METHOD(Phalcon_Di_Service, setParameter)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval parameter;
	zval *position_param = NULL, *parameter_param = NULL, arguments, _0, _1, _3, _2$$5;
	zend_long position;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&arguments);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_2$$5);
	ZVAL_UNDEF(&parameter);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(position)
		Z_PARAM_ARRAY(parameter)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 0, &position_param, &parameter_param);
	ZEPHIR_OBS_COPY_OR_DUP(&parameter, parameter_param);
	zephir_memory_observe(&_0);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("definition"), PH_NOISY_CC);
	if (UNEXPECTED(Z_TYPE_P(&_0) != IS_ARRAY)) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_di_exception_ce, "Definition must be an array to update its parameters", "phalcon/Di/Service.zep", 228);
		return;
	}
	zephir_memory_observe(&arguments);
	zephir_read_property(&_1, this_ptr, ZEND_STRL("definition"), PH_NOISY_CC | PH_READONLY);
	if (zephir_array_isset_string_fetch(&arguments, &_1, SL("arguments"), 0)) {
		zephir_array_update_long(&arguments, position, &parameter, PH_COPY | PH_SEPARATE ZEPHIR_DEBUG_PARAMS_DUMMY);
	} else {
		ZEPHIR_INIT_VAR(&_2$$5);
		zephir_create_array(&_2$$5, 1, 0);
		zephir_array_update_long(&_2$$5, position, &parameter, PH_COPY ZEPHIR_DEBUG_PARAMS_DUMMY);
		ZEPHIR_CPY_WRT(&arguments, &_2$$5);
	}
	ZEPHIR_INIT_VAR(&_3);
	ZVAL_STRING(&_3, "arguments");
	zephir_update_property_array(this_ptr, SL("definition"), &_3, &arguments);
	RETURN_THIS();
}

/**
 * Sets if the service is shared or not
 */
PHP_METHOD(Phalcon_Di_Service, setShared)
{
	zval *shared_param = NULL, __$true, __$false;
	zend_bool shared;
	zval *this_ptr = getThis();

	ZVAL_BOOL(&__$true, 1);
	ZVAL_BOOL(&__$false, 0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_BOOL(shared)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &shared_param);
	if (shared) {
		zephir_update_property_zval(this_ptr, ZEND_STRL("shared"), &__$true);
	} else {
		zephir_update_property_zval(this_ptr, ZEND_STRL("shared"), &__$false);
	}
}

/**
 * Sets/Resets the shared instance related to the service
 */
PHP_METHOD(Phalcon_Di_Service, setSharedInstance)
{
	zval *sharedInstance, sharedInstance_sub;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&sharedInstance_sub);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(sharedInstance)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &sharedInstance);
	zephir_update_property_zval(this_ptr, ZEND_STRL("sharedInstance"), sharedInstance);
}

