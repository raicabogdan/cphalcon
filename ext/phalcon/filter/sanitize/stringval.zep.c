
#ifdef HAVE_CONFIG_H
#include "../../../ext_config.h"
#endif

#include <php.h>
#include "../../../php_ext.h"
#include "../../../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/fcall.h"
#include "kernel/operators.h"
#include "kernel/memory.h"
#include "kernel/object.h"


/**
 * This file is part of the Phalcon Framework.
 *
 * (c) Phalcon Team <team@phalcon.io>
 *
 * For the full copyright and license information, please view the LICENSE.txt
 * file that was distributed with this source code.
 */
/**
 * Sanitizes a value to string
 */
ZEPHIR_INIT_CLASS(Phalcon_Filter_Sanitize_StringVal)
{
	ZEPHIR_REGISTER_CLASS(Phalcon\\Filter\\Sanitize, StringVal, phalcon, filter_sanitize_stringval, phalcon_filter_sanitize_stringval_method_entry, 0);

	return SUCCESS;
}

/**
 * @param string $input The text to sanitize
 * @param int    $flags The flags for `htmlspecialchars()`
 *
 * @return string
 */
PHP_METHOD(Phalcon_Filter_Sanitize_StringVal, __invoke)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long flags, ZEPHIR_LAST_CALL_STATUS;
	zval *input_param = NULL, *flags_param = NULL, _0;
	zval input;

	ZVAL_UNDEF(&input);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 2)
		Z_PARAM_STR(input)
		Z_PARAM_OPTIONAL
		Z_PARAM_LONG(flags)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 1, &input_param, &flags_param);
	zephir_get_strval(&input, input_param);
	if (!flags_param) {
		flags = 11;
	} else {
		}
	ZVAL_LONG(&_0, flags);
	ZEPHIR_RETURN_CALL_FUNCTION("htmlspecialchars", NULL, 287, &input, &_0);
	zephir_check_call_status();
	RETURN_MM();
}

