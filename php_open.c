/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2012 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_my_open.h"
#include "main/php_main.h"
#include "zend_exceptions.h"

#define PHP_SAMPLE_DESCRIPTOR_RES_NAME "山寨文件描述符"
#define PHP_SAMPLE4_EXTVER "山寨文件描述符"
/* If you declare any globals in php_my_fopen.h uncomment this:*/
ZEND_DECLARE_MODULE_GLOBALS(my_fopen)


/* True global resources - no need for thread safety here */
static int le_my_fopen;
zend_class_entry *class_entry = NULL;


int my_open_globals_id;

typedef struct _old_one {
    char *name;
    int worshippers;
} old_one;

int le_old_one;

/* {{{ 10替换为01，并将01前面1移至最左边 */
/*static void strMove(char* arr,unsigned int len){
        int i,j,k;
		for(i=0;i< len-1;i++){
			if(arr[i]=='1'&&arr[i+1]=='0'){
				arr[i] = '0';
				arr[i+1] = '1';
				for(j=0;j<i-1;j++){
                                for(k=j+1;k<i;k++){
                                        char _tmp;
                                        if( arr[j] < arr[k] ){
                                                _tmp = arr[k];
                                                arr[k] = arr[j];
                                                arr[j] = _tmp;
                                        }
                                }
                        }
                        break;
                }
        }
}
/* }}} */

/* {{{ 求组合数 */
/*static int getComNum(unsigned int a,unsigned int b){
        unsigned int iUp=1,iDown=1;
        int i = a-b>b ? b:a-b;
        while(i){
                iUp *=a;
                iDown *=i;
                i--;
                a--;
        }
        return iUp/iDown;
}
/* }}} */


ZEND_BEGIN_ARG_INFO(arg_person_setname,0)
ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()


PHP_INI_BEGIN()
PHP_INI_ENTRY("hello_greeting", "Hello World!", PHP_INI_ALL, NULL)
PHP_INI_END()

/* {{{ my_fopen_functions[]
 *
 * Every user visible function must have an entry in my_fopen_functions[].
 */
const zend_function_entry my_open_functions[] = {
	PHP_FE(confirm_my_open_compiled,	NULL)		/* For testing, remove later. */
	//PHP_FE(comb,NULL)
	PHP_FE(file_open,NULL)
	PHP_FE(file_read,NULL)
	PHP_FE(file_eof,NULL)
	PHP_FE(test,NULL)
	PHP_FE(hello_dump,NULL)
	PHP_FE(sample_array,NULL)
	PHP_FE(sample_fopen,NULL)
	PHP_FE(sample_fwrite,NULL)
	PHP_FE(sample_fclose,NULL)
	PHP_FE(test_dump,NULL)
	PHP_FE(getYig,NULL) 
	PHP_FE(chant,NULL) 
	PHP_FE(findMonster,NULL)
	PHP_FE(test_callable,NULL)
	PHP_FE(get_variable,NULL) 
	PHP_FE(test_eval_string,NULL) 
	PHP_FE(check_val,NULL) 
	PHP_FE(test_call_user_function,NULL) 
	PHP_FE(test_call_function,NULL)
	PHP_FE(md52,NULL)
	PHP_FE(thread_wrok,NULL)
	PHP_FE(makevalue,NULL)
	//PHP_FE(call,NULL)	
	PHP_FE(php_syntax_check,NULL)
	PHP_FE(str_reverse,NULL)
	PHP_FE_END	/* Must be the last line in my_fopen_functions[] */
};


/* }}} */

/* {{{ my_fopen_module_entry
 */
zend_module_entry my_open_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"my_open",
	my_open_functions,
	PHP_MINIT(my_open),
	PHP_MSHUTDOWN(my_open),
	PHP_RINIT(my_open),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(my_open),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(my_open),
#if ZEND_MODULE_API_NO >= 20010901
	"0.1", /* Replace with version number for your extension */
#endif
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_MY_OPEN
ZEND_GET_MODULE(my_open)
#endif


/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("my_fopen.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_my_fopen_globals, my_fopen_globals)
    STD_PHP_INI_ENTRY("my_fopen.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_my_fopen_globals, my_fopen_globals)
PHP_INI_END()

/* }}} */

/* {{{ php_my_fopen_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_my_fopen_init_globals(zend_my_fopen_globals *my_fopen_globals)
{
	my_fopen_globals->global_value = 0;
	my_fopen_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
const zend_function_entry class_functions[]={
	PHP_ME(Person, __construct, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Person, __destruct,  NULL, ZEND_ACC_PUBLIC|ZEND_ACC_DTOR)
	PHP_ME(Person, getName, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Person, setName,  arg_person_setname, ZEND_ACC_PUBLIC)
	PHP_FE_END	/* Must be the last line in my_fopen_functions[] */
};

static zend_function_entry i_myinterface_method[]={
    ZEND_ABSTRACT_ME(i_myinterface, hello, NULL) //注意这里的null指的是arginfo
    {NULL,NULL,NULL}
};



static int le_sample_descriptor;

/* 自定义声明常量*/
void php_sample4_register_boolean_constant(char *name, uint len,zend_bool bval, int flags, int module_number TSRMLS_DC)
{
        zend_constant c;

        ZVAL_BOOL(&c.value, bval);
        c.flags = CONST_CS | CONST_PERSISTENT;
        c.name = zend_strndup(name, len - 1);
        c.name_len = len;
        c.module_number = module_number;
        zend_register_constant(&c TSRMLS_CC);
}

static zend_bool fuck_global_callback(char *name, uint name_len TSRMLS_DC) {
	zval *tmp;
	MAKE_STD_ZVAL(tmp);
	array_init(tmp);
	add_next_index_long(tmp,2222);
	ZEND_SET_SYMBOL(&EG(symbol_table), name, tmp);
	return 0;
}



void rlyeh_old_one_pefree(zend_rsrc_list_entry *rsrc TSRMLS_DC) {
    old_one *god = rsrc->ptr;

    // free the char* field, if set
    if (god->name) {
        pefree(god->name, 1);
    }

    pefree(god, 1);
}

zend_bool php_sample4_autoglobal_callback(char *name, uint name_len TSRMLS_DC)
{
    zval *sample4_val;
    int i;
    MAKE_STD_ZVAL(sample4_val);
    array_init(sample4_val);
    for(i = 0; i < 10; i++) {
        add_next_index_long(sample4_val, i);
    }
    ZEND_SET_SYMBOL(&EG(symbol_table), "_SAMPLE4", sample4_val);
    return 0;
}


zend_class_entry *person_ce;
zend_class_entry *i_myinterface_ce;

PHP_MINIT_FUNCTION(my_open) {

/*
#ifdef ZTS
	ts_allocate_id(
	    &my_open_globals_id,
	    sizeof(zend_my_open_globals),
	    NULL, NULL);
#endif
		*/

	/* If you have INI entries, uncomment these lines
	REGISTER_INI_ENTRIES();
	*/

	zend_class_entry Person,ice;
	INIT_CLASS_ENTRY(Person, "Person" , class_functions);  //第二个参数为类名，第三个参数为函数表
	//person_ce =zend_register_internal_class_ex( &person , NULL , NULL TSRMLS_CC);  //注册类
	person_ce =zend_register_internal_class_ex( &Person , NULL , NULL TSRMLS_CC);  //注册类

	//person_ce->create_object = person_create_handler;

	zend_declare_property_null(person_ce, ZEND_STRL("_name"),ZEND_ACC_PUBLIC TSRMLS_CC); //初始化属性
	
	/*interface*/
	//zend_class_entry ;
    INIT_CLASS_ENTRY(ice, "i_myinterface", i_myinterface_method);
    i_myinterface_ce = zend_register_internal_interface(&ice TSRMLS_CC);
    /*interface end*/


	le_sample_descriptor = zend_register_list_destructors_ex(NULL, NULL, PHP_SAMPLE_DESCRIPTOR_RES_NAME,module_number);
	
	zend_register_auto_global(ZEND_STRL("_FUCK"),fuck_global_callback TSRMLS_CC);


	 zend_register_auto_global("_SAMPLE4", sizeof("_SAMPLE4") - 1
	#ifdef ZEND_ENGINE_2
                , php_sample4_autoglobal_callback
	#endif
                TSRMLS_CC);

	REGISTER_INI_ENTRIES();

	le_old_one = zend_register_list_destructors_ex(NULL, rlyeh_old_one_pefree, "Great Old One", module_number);

	//REGISTER_STRING_CONSTANT("SAMPLE4_VERSION",PHP_SAMPLE4_EXTVER, CONST_CS | CONST_PERSISTENT);
	  
	zend_register_string_constant("SAMPLE4_VERSION",sizeof("SAMPLE4_VERSION"),PHP_SAMPLE4_EXTVER,CONST_CS | CONST_PERSISTENT,module_number TSRMLS_CC);
   	php_sample4_register_boolean_constant("FUCKPHP",sizeof("FUCKPHP"),PHP_SAMPLE4_EXTVER,CONST_CS | CONST_PERSISTENT,module_number TSRMLS_CC);
	//或者php_sample4_register_boolean_constant()自定义函数

    return SUCCESS;
	
	/*
   if( zend_call_method( NULL, *ce, NULL, 
                     "getmodelbyid", 
                     strlen("getmodelbyid"), 
                     &retval_ptr, 1, p1, 
                     NULL TSRMLS_CC ) == FAILURE) {
    php_printf("gosh!");
} 
else {
    php_printf("yep!"); 
}*/

	//PS(module_number) = module_number; /* if we really need this var we need to init it in zts mode as well! */
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */

PHP_MSHUTDOWN_FUNCTION(my_open) {
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	 UNREGISTER_INI_ENTRIES();
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(my_open) {
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(my_open) {
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(my_open) {
	php_info_print_table_start();
	php_info_print_table_header(2, "my_open support", "enabled");
	php_info_print_table_end();
	
	//char *php_info_html_esc(char *str TSRMLS_DC)
//这个函数是php_escape_html_entities()的一个封装，htmlentites() 函数的底层实现。该函数返回的字符串通过emalloc()创建，并在使用后必须使用 efree()函数释放掉。
/*
void php_info_print_table_start(void)
void php_info_print_table_end(void)
//输出开/关表格式所需的标签。HTML输出是与CLI输出一样，表现为一个简单的换行。

void php_info_print_table_header(int cols, ...)
void php_info_print_table_colspan_header(int cols, char *header)
//输出表头行。第一个函数在可变参数列表中的char *元素外面的每一列都会输出一对th标签，第二个函数会在指定列数外面输出一对th标签。

void php_info_print_table_row(int cols, ...)
void php_info_print_table_row_ex(int cols, char *class, ...)
//第一个函数在可变参数列表中的char *元素外面的每一行都会输出一对td标签，第二个函数会在指定列数外面输出一对td标签。当不在HTML中 输出的时候，两个函数将没有任何差别。

void php_info_print_hr(void)
	*/
	

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */


/* Remove the following function when you have succesfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_my_fopen_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(confirm_my_open_compiled) {
	char *arg = NULL;
	int arg_len, len;
	char *strg;

	//TSRMLS_FETCH();
	MY_OPEN_G(global_value)= 2;
	php_printf("\nmm %d mm\n",++MY_OPEN_G(global_value));

    
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	len = spprintf(&strg, 0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "my_open", arg);
	RETURN_STRINGL(strg, len, 0);
}

PHP_FUNCTION(test){
   /*
	 char *varname;
    int varname_len;
    zval **varvalue;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &varname, &varname_len) == FAILURE) {
        RETURN_NULL();
    }

    if (zend_hash_find(&EG(symbol_table), varname, varname_len + 1, (void**)&varvalue) == FAILURE) {
        php_error_docref(NULL TSRMLS_CC, E_NOTICE, "Undefined variable: %s", varname);
        RETURN_NULL();
    }

    *return_value = **varvalue;
    zval_copy_ctor(return_value);
	*/
	RETURN_STRING(INI_STR("hello_greeting"), 1);
	
	/*
	zval *fooval;  	
	if (!EG(active_symbol_table)) {
		zend_rebuild_symbol_table(TSRMLS_C);
	}
	MAKE_STD_ZVAL(fooval);  
    ZVAL_STRING(fooval, "bar", 1);  
	//array_init(fooval);
	//zval_copy_ctor(fooval);	
    ZEND_SET_SYMBOL(EG(active_symbol_table), "foo", fooval);  
	//zend_hash_update(&EG(symbol_table), buf, buf_len + 1, &zvalue, sizeof(zval *), NULL);
	*/
	
	/*
	zval **fooval;

    if (zend_hash_find(EG(active_symbol_table),
                       "foo", sizeof("foo"),
                       (void**)&fooval) == SUCCESS) {
        php_printf("Got the value of $foo!");
    } else {
        php_printf("$foo is not defined.");
    }*/
}
PHP_FUNCTION(hello_dump)
{
    zval *uservar;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z",
     &uservar) == FAILURE) {
        RETURN_NULL();
    }

    switch (Z_TYPE_P(uservar)) {
        case IS_NULL:
            php_printf("NULL\n");
            break;
        case IS_BOOL:
            php_printf("Boolean: %s\n", Z_LVAL_P(uservar) ? "TRUE" : "FALSE");
            break;
        case IS_LONG:
            php_printf("Long: %ld\n", Z_LVAL_P(uservar));
            break;
        case IS_DOUBLE:
            php_printf("Double: %f\n", Z_DVAL_P(uservar));
            break;
        case IS_STRING:
            php_printf("String: ");
            PHPWRITE(Z_STRVAL_P(uservar), Z_STRLEN_P(uservar));
            php_printf("\n");
            break;
        case IS_RESOURCE:
            php_printf("Resource\n");
            break;
        case IS_ARRAY:
            php_printf("Array\n");
            break;
        case IS_OBJECT:
            php_printf("Object\n");
            break;
        default:
            php_printf("Unknown\n");
    }

    RETURN_TRUE;
}

PHP_FUNCTION(chant) {
  int str_len, i;
  long num;
  char *str;
  zval *arr;
 
  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lsa", &num, &str, &str_len, &arr) == FAILURE) {
    return;
  }
 
  // sanity check
  if (num < 0 || num > 100) {
    return;
  } 
 
  for (i=0; i<num; i++) {
    add_next_index_stringl(arr, str, str_len, 1);
  }
}

PHP_FUNCTION(getYig) {
    zend_rsrc_list_entry *le;
    char *key = "yig";
 
    if (zend_hash_find(&EG(persistent_list), key, strlen(key)+1, (void**)&le) == FAILURE) {
        // need to create a new god
        zend_rsrc_list_entry nle;
        old_one *yig;
 
        yig = (old_one*)pemalloc(sizeof(old_one), 1);
        yig->name = pestrdup("Yig", 1);
        yig->worshippers = 4;
 
        php_printf("creating a new god\n");
 
        nle.ptr = yig;
        nle.type = le_old_one;
        nle.refcount = 1;
 
        zend_hash_update(&EG(persistent_list), key, strlen(key)+1, (void*)&nle, sizeof(zend_rsrc_list_entry), NULL);
    }
    else {
        old_one *god = le->ptr;
 
        php_printf("fetched %s: %d worshippers\n", god->name, god->worshippers);
    }
}

PHP_FUNCTION(findMonster) {
  int monster_len;
  char *monster;
  zval *list, **desc;
 
  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sa", &monster, &monster_len, &list) == FAILURE) {
    return;
  }
 
  if (zend_hash_find(Z_ARRVAL_P(list), monster, monster_len+1, (void**)&desc) == FAILURE) {
    RETURN_NULL();
  }
 
  RETURN_STRINGL(Z_STRVAL_PP(desc), Z_STRLEN_PP(desc), 1);
}


PHP_FUNCTION(php_syntax_check){
     volatile int exit_status = 0;
	 char *filename = NULL;     
	 int filename_len;
     int argc = ZEND_NUM_ARGS();
	 zend_file_handle fp;
    if (zend_parse_parameters(argc TSRMLS_CC, "s", &filename,&filename_len) == FAILURE) {
          return;
     }

	if (filename_len == 0) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Filename cannot be empty!");
		RETURN_FALSE;
	}

	if (strlen(filename) != filename_len) {
		RETURN_FALSE;
	}
	memset(&fp, 0, sizeof(fp));
	fp.filename = filename;
	fp.type = ZEND_HANDLE_FILENAME;
	fp.free_filename = 0;
	fp.opened_path = NULL;

	exit_status = php_lint_script(&fp TSRMLS_CC);
	if (exit_status==SUCCESS) {
		zend_printf("No syntax errors detected in %s\n", fp.filename);
	} else {
		zend_printf("Errors parsing %s\n", fp.filename);
	}

}

PHP_FUNCTION(test_dump)
{
    int i, argc = ZEND_NUM_ARGS();
    zval ***args;


    args = (zval ***)safe_emalloc(argc, sizeof(zval **), 0);
    if (ZEND_NUM_ARGS() == 0 ||
        zend_get_parameters_array_ex(argc, args) == FAILURE) {
        efree(args);
        WRONG_PARAM_COUNT;
    }
    for (i=0; i<argc; i++) {
        php_var_dump(args[i], 1 TSRMLS_CC);
    }
    efree(args);
}

PHP_FUNCTION(test_callable)
{
	zval *var, **callable_name = NULL;
	char *name;
	char *error;
	zend_bool retval;
	zend_bool syntax_only = 0;
	int check_flags = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z|bZ", &var,
							  &syntax_only, &callable_name) == FAILURE) {
		return;
	}
	
	if (syntax_only) {
		check_flags |= IS_CALLABLE_CHECK_SYNTAX_ONLY;
	}
	if (ZEND_NUM_ARGS() > 2) {
		retval = zend_is_callable_ex(var, NULL, check_flags, &name, NULL, NULL, &error TSRMLS_CC);
		zval_dtor(*callable_name);
		ZVAL_STRING(*callable_name, name, 0);
	} else {
		retval = zend_is_callable_ex(var, NULL, check_flags, NULL, NULL, NULL, &error TSRMLS_CC);
	}
	if (error) {
		/* ignore errors */
		efree(error);
	}

	RETURN_BOOL(retval);
}

PHP_FUNCTION(get_variable) {
	zval **server, **os;
	if(SUCCESS != zend_symtable_find(&EG(symbol_table), "_SERVER", sizeof("_SERVER"), (void **)&server)) {
		RETURN_BOOL(0);
	}
	if (Z_TYPE_PP(server) == IS_ARRAY) {
		if(SUCCESS == zend_symtable_find(Z_ARRVAL_P(*server), "OS", sizeof("OS"), (void **)&os)) {
			RETURN_ZVAL(*os, 1, 0);
		}
	}
	RETURN_ZVAL(*server, 1, 0);
}

/*
zend_eval_string 说明：
执行类似PHP脚本中的eval()语句。
参数表：
int zend_eval_string(char *str, zval *retval_ptr, char *string_name TSRMLS_DC);
参数	说明
str	需要执行的PHP语句
retval_ptr	执行的返回值
string_name	标示名，这里的标示主要是让用户区分来自于哪个扩展，如果语句运行异常，则会抛出相关的错误，让用户辨识来自于string_name的扩展
范例中的内容很简单，第一个zend_eval_string首先声明了一个名为test_func的PHP函数，第二个zend_eval_string直接调用这个函数，其实2句语句可以写在一起，结果也是一样的，分开来的主要目的就是让retval_ptr显示的更清晰一些。
*/
PHP_FUNCTION(test_eval_string) {
	zval *result;
	MAKE_STD_ZVAL(result);
	zend_eval_string("function test_func($a) {return $a.'_test';}", NULL, "Shop Plus Test" TSRMLS_CC);
	zend_eval_string("test_func('eval')", result, "Shop Plus Test" TSRMLS_CC);
	RETURN_ZVAL(result, 1, 0);
}


PHP_FUNCTION(file_open) {
	char *filename = NULL;
	char *mode = NULL;
	int argc = ZEND_NUM_ARGS();
	int filename_len;
	int mode_len;
	FILE *fp;

	if (zend_parse_parameters(argc TSRMLS_CC, "ss", &filename,&filename_len, &mode, &mode_len) == FAILURE) {
		return;
	}

	fp = VCWD_FOPEN(filename, mode);

	if (fp == NULL) {
		RETURN_FALSE;
	}

	ZEND_REGISTER_RESOURCE(return_value, fp, le_sample_descriptor);
}
/*
compare_function
说明：
比较两个不同的变量，返回其结果，返回结果形式与C语言中的strcmp类似
附言：
此方法就是PHP中的数据比较方法，使用上类似于PHP中的>、< 、==，这些比较方法（===不包含在内，PHP另外提供了一个叫做is_identical_function的方法来做强等于）。
范例代码：
*/

PHP_FUNCTION(check_val) {
	zval *v1, *v2;
	zval *result;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zz", &v1, &v2) == FAILURE) {
		return;
	}
	MAKE_STD_ZVAL(result);
	compare_function(result, v1, v2 TSRMLS_CC);
	RETURN_ZVAL(result, 0, 0);
}

ZEND_FUNCTION(test_call_user_function) {
	zval function_name, *retval, **argv[1], *param;
	MAKE_STD_ZVAL(retval);
	MAKE_STD_ZVAL(param);
	ZVAL_STRING(param, "-1.5", 1);
	argv[0] = &param;

	ZVAL_STRING(&function_name, "abs", 1);
	if (call_user_function(EG(function_table), NULL, &function_name, retval, 1, *argv TSRMLS_CC) == FAILURE) {
		RETURN_BOOL(0);
	}
	else {
		RETURN_ZVAL(retval, 1, 0);
	}
}

/*
zend_call_function

说明：

执行指定的函数并返回结果，函数包括内部函数与用户函数。

参数表：

int zend_call_function(zend_fcall_info *fci, zend_fcall_info_cache *fci_cache TSRMLS_DC);

参数	说明
fci	zend function call info，zend函数调用信息结构体
fci_cache	zend function call info cache，zend函数调用信息缓存结构体
zend_fcall_info与zend_fcall_info_cache结构原型：

typedef struct _zend_fcall_info {
	size_t size;
	HashTable *function_table;
	zval *function_name;
	HashTable *symbol_table;
	zval **retval_ptr_ptr;
	zend_uint param_count;
	zval ***params;
	zval *object_ptr;
	zend_bool no_separation;
} zend_fcall_info;

typedef struct _zend_fcall_info_cache {
	zend_bool initialized;
	zend_function *function_handler;
	zend_class_entry *calling_scope;
	zend_class_entry *called_scope;
	zval *object_ptr;
} zend_fcall_info_cache;
这2个数据结构我在这里先不仔细阐述，我会在之后的草堂笔记中详细阐述2个结构体的功能。

范例代码：http://www.babafan.com/
*/
PHP_FUNCTION(test_call_function) {
	zend_fcall_info fci;
	zend_fcall_info_cache fcc;
	zval *retval;
	zval *handle = NULL;
	zval function_name;
	zval **argv[1];

	ZVAL_STRING(&function_name, "abs", 1);
	MAKE_STD_ZVAL(handle);
	ZVAL_STRING(handle, "-1.5", 1);

	argv[0] = &handle;
	fci.size = sizeof(fci);
	fci.function_table = EG(function_table);
	fci.function_name = &function_name;
	fci.symbol_table = NULL;
	fci.object_ptr = NULL;
	fci.retval_ptr_ptr = &retval;
	fci.param_count = 1;
	fci.params = argv;
	fci.no_separation = 0;

	if (zend_call_function(&fci, NULL TSRMLS_CC) == FAILURE) {
		RETURN_BOOL(0);
	}
	else {
		RETURN_ZVAL(retval, 1, 0);
	}
}

PHP_FUNCTION(md52)
{
	/*
	zval **strtomd5;
	if((ZEND_NUM_ARGS()!= 1) || (zend_get_parameters_ex(1, &strtomd5) != SUCCESS))
	{
	   WRONG_PARAM_COUNT;
	}
	zend_fcall_info fci;
	zend_fcall_info_cache fcic = empty_fcall_info_cache;
	zval *funname,*ret_ptr = NULL;
	MAKE_STD_ZVAL(funname);
	ZVAL_STRING(funname, "md5", 1); 
	zval **param[1];

	param[0] = strtomd5;
	call_user_function_ex(EG(function_table), NULL, funname, &ret_ptr, 1, param, 0, EG(active_symbol_table));
	//call_user_function_ex(EG(function_table), NULL, funname, &ret_ptr, 1, param, 0, NULL);

	zval *new_variable;

	MAKE_STD_ZVAL(new_variable);
	ZVAL_LONG(new_variable,317);
	ZEND_SET_SYMBOL(&EG(symbol_table), "new_variable_name", new_variable);

	RETVAL_ZVAL(ret_ptr, 1, 0);
	
	zval_ptr_dtor(&funname);
	MAKE_STD_ZVAL(funname);
	
	ZVAL_STRING(funname, "gg", 1); 

	char *string_contents = "new_variable_name";
	zval *var_name;
	MAKE_STD_ZVAL(var_name);

	ZVAL_STRING(var_name, string_contents, 1); 	
	
	zend_printf("c_ext *strtomd5 = %s, func=%s\n", var_name->value.str.val , funname->value.str.val);

	param[0] = &var_name;	

	
	if(call_user_function_ex(EG(function_table), NULL, funname, &ret_ptr, 1, param, 0, EG(active_symbol_table)) != SUCCESS)
	{
	   zend_error(E_ERROR, "Function call failed");
	}

	zend_printf("c_ext new_variable = %d\n", new_variable->value.lval);
	efree(funname);
	efree(var_name);
	*/
	
}



PHP_FUNCTION(thread_wrok)
{
    /*
	zval *cls=NULL,*zvalue=NULL,*z_method;
    zval ***params=NULL;
 
    int arg_count = ZEND_NUM_ARGS();
 
    if (arg_count <1 ) {
        WRONG_PARAM_COUNT;
    }
     
    params = (zval ***) safe_emalloc(sizeof(zval **), arg_count, 0);
 
    if (zend_get_parameters_array_ex(arg_count, params) == FAILURE) {
        efree(params);
        RETURN_FALSE;
    }
 
    z_method=*params[0];
     
    if(arg_count>1)
    {
        cls=*params[1];
    }
 
    if ( Z_TYPE_P(z_method) != IS_STRING ) 
    {
        php_error_docref(NULL TSRMLS_CC, E_WARNING, "First param must be string");
        RETURN_FALSE;
    } 
    //---------------------------------------------------------
    /*
    char *method;
    int method_len;
    if (
        zend_parse_parameters( ZEND_NUM_ARGS() TSRMLS_CC, "s|o", &method, &method_len, &cls) == FAILURE
    )
    {
        RETURN_FALSE;
    }
 
    MAKE_STD_ZVAL(z_method);
 
    ZVAL_STRING(z_method, method, 1);
     
    if (method && zend_hash_find(Z_ARRVAL_P(method_records), method, method_len + 1, (void**)&zvalue) != FAILURE) 
    {
        RETURN_FALSE;
    }
 
    */
 
    //---------------------------------------------------------
	/*
	zval *retval_ptr=NULL;
    arg_count = arg_count-2>0?arg_count-2:0;
    if(Z_TYPE_P(cls) == IS_OBJECT || Z_TYPE_P(cls) == IS_STRING )
    {
        if (call_user_function_ex(EG(function_table), &cls  , z_method, &retval_ptr, arg_count, arg_count?params+2:NULL , 0, NULL TSRMLS_CC) == SUCCESS) {
            if (retval_ptr) {       
                zval_ptr_dtor(&retval_ptr);
            }
        } else {
            php_error_docref(NULL TSRMLS_CC, E_WARNING, "Unable to call class method: %s()", Z_STRVAL_P(z_method));
            RETURN_FALSE;
        }
    }else{
        if (call_user_function_ex(CG(function_table), NULL, z_method, &retval_ptr, arg_count, arg_count?params+2:NULL , 0, NULL TSRMLS_CC) == SUCCESS )
        {
            if (retval_ptr) {       
                zval_ptr_dtor(&retval_ptr);
            }
        } else {
            php_error_docref(NULL TSRMLS_CC, E_WARNING, "Unable to call %s()", Z_STRVAL_P(z_method));
            RETURN_FALSE;
        }
    }
 
    //efree(z_method);
 
    RETURN_TRUE;*/
}

PHP_FUNCTION(makevalue) {
    Z_TYPE_P(return_value) = IS_BOOL;
    Z_LVAL_P(return_value) = 1;
   
	/*
    Z_TYPE_P(return_value) = IS_LONG;
    Z_LVAL_P(return_value) = 1;
	*/
}


PHP_FUNCTION(file_read)
{
	int argc = ZEND_NUM_ARGS();
	long size;
	zval *filehandle = NULL;
	FILE *fp;
	char *result;
	size_t bytes_read;
	if (zend_parse_parameters(argc TSRMLS_CC, "rl", &filehandle,&size) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(fp, FILE *, &filehandle, -1, "standard-cfile", le_sample_descriptor);
	result = (char *) emalloc(size+1);
	bytes_read = fread(result, 1, size, fp);
	result[bytes_read] = '\0';
	RETURN_STRING(result, 0);

}


PHP_FUNCTION(file_eof){

int argc = ZEND_NUM_ARGS();

zval *filehandle = NULL;

FILE *fp;

if (zend_parse_parameters(argc TSRMLS_CC, "r", &filehandle) ==FAILURE) {

	return;

}

ZEND_FETCH_RESOURCE(fp, FILE *, &filehandle, -1, "standard-c-file",le_sample_descriptor);

if (fp == NULL) {

	RETURN_FALSE;

}

if (feof(fp) <= 0) {

	/* Return eof also if there was an error */

	RETURN_TRUE;

}

RETURN_FALSE;

}


PHP_FUNCTION(sample_array) {
	zval *subarray;

	array_init(return_value);

	/* Add some scalars */
	add_assoc_long(return_value, "life", 42);
	add_index_bool(return_value, 123, 1);
	add_next_index_double(return_value, 3.1415926535);

	/* Toss in a static string, dup'd by PHP */
	add_next_index_string(return_value, "Foo", 1);

	/* Now a manually dup'd string */
	add_next_index_string(return_value, estrdup("Bar"), 0);

	/* Create a subarray */
	MAKE_STD_ZVAL(subarray);
	array_init(subarray);

	/* Populate it with some numbers */
	add_next_index_long(subarray, 1);
	add_next_index_long(subarray, 20);
	add_next_index_long(subarray, 300);

	/* Place the subarray in the parent */
	add_index_zval(return_value, 444, subarray);
}


PHP_FUNCTION(sample_fopen) {
	FILE *fp;
	char *filename, *mode;
	int filename_len, mode_len;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ss",&filename, &filename_len,&mode, &mode_len) == FAILURE) {
		RETURN_NULL();
	}
	if (!filename_len || !mode_len) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING,"Invalid filename or mode length");
		RETURN_FALSE;
	}
	fp = fopen(filename, mode);
	if (!fp) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING,"Unable to open %s using mode %s",filename, mode);
		RETURN_FALSE;
	}
	//将fp添加到资源池中去，并标记它为le_sample_descriptor类型的。
	ZEND_REGISTER_RESOURCE(return_value,fp,le_sample_descriptor);
}


PHP_FUNCTION(sample_fwrite) {
	FILE *fp;
	zval *file_resource;
	char *data;
	int data_len;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rs",&file_resource, &data, &data_len) == FAILURE) {
		RETURN_NULL();
	}
	/* Use the zval* to verify the resource type and
	 * retrieve its pointer from the lookup table */
	ZEND_FETCH_RESOURCE(fp,FILE *,&file_resource,-1,PHP_SAMPLE_DESCRIPTOR_RES_NAME,le_sample_descriptor);

	/* Write the data, and
	 * return the number of bytes which were
	 * successfully written to the file */
	RETURN_LONG(fwrite(data, 1, data_len, fp));
}

PHP_FUNCTION(sample_fclose) {
	FILE *fp;
	zval *file_resource;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r",&file_resource) == FAILURE) {
		RETURN_NULL();
	}

	/* While it's not necessary to actually fetch the
	 * FILE* resource, performing the fetch provides
	 * an opportunity to verify that we are closing
	 * the correct resource type. */
	ZEND_FETCH_RESOURCE(fp, FILE *, &file_resource, -1,PHP_SAMPLE_DESCRIPTOR_RES_NAME, le_sample_descriptor);

	/* Force the resource into self-destruct mode
	*/

	/*
	使用出错了 zend_hash_index_del(&EG(regular_list),Z_RESVAL_P(file_resource));
	*/
	RETURN_TRUE;
}

/*
PHP_FUNCTION(sample_fclose)
{
	zval *res;
	FILE *fp;
	if(zend_parse_parameters(ZEND_NUM_ARGS TSRMS_CC, "r", &res) == FAILURE){
		RETURN_FALSE;
	}
	if(Z_TYPE_P(res) == IS_RESOURCE){//判断变量类型是否是资源类型
		zend_hash_index_del(&EG(regular_list), Z_RESVAL_P(res));//EG就类似于PHP中的$_GLOBALS。在全局资源变量regular_list中删除对应ID的资源
	}else{
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "参数必须是资源类型变量");
		RETURN_FALSE;
	}

	RETURN_TRUE;
}*/

ZEND_FUNCTION(str_reverse) {
	
	char *swap="mickelfeng is comming soon\n";
	int len=strlen(swap);
	int i=0;
	for(i;i<len;i++){
		printf("%c\n",*(swap+i));
	}
	
/*
	if (ZEND_NUM_ARGS()!= 1)
		WRONG_PARAM_COUNT;
	zval **args;
		//MAKE_STD_ZVAL(tmp);
	if (zend_get_parameters_array_ex(ZEND_NUM_ARGS(), &args TSRMLS_CC)==FAILURE)
	{
		return;
	}
	convert_to_string(*args);
	char swap;
	char *head = Z_STRVAL_PP(args);
	char *end = head + Z_STRLEN_PP(args) - 1;
	for (; head < end; ++head, --end)
	{
		swap = *end;
		*end = *head;
		*head = swap;
	}
	// 销毁临时zval
	zval_ptr_dtor(return_value_ptr);
	// 返回传入的参数
	*return_value_ptr = *args;
	// 增加引用计数
	++(*return_value_ptr)->refcount;
	*/

}

/*
PHP_FUNCTION(call) {
	int num_args = ZEND_NUM_ARGS();
	if (num_args < 1)
		WRONG_PARAM_COUNT;
	zval ***args = (zval ***)emalloc(sizeof(zval **)*num_args);
	zval *ret_zval;
// 获取传入的参数
	if (zend_get_parameters_array_ex(num_args, args TSRMLS_CC) == FAILURE) {
		efree(args);
		return;
	}
// 第一个参数作为函数名，后面的作为函数参数
	if (call_user_function_ex(CG(function_table), NULL, **args,&ret_zval, num_args - 1, args + 1, 0, NULL TSRMLS_CC)== FAILURE) {
		efree(args);
		zend_error(E_ERROR, "Function call failed");
	}
// 将函数返回值反馈给用户
	*return_value = *ret_zval;
	efree(args);
}

/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and
   unfold functions in source code. See the corresponding marks just before
   function definition, where the functions purpose is also documented. Please
   follow this convention for the convenience of others editing your code.
*/


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */


/* {{{ 组合函数 */
/*
PHP_FUNCTION(comb)
{
        zval *arr;
        uint n;

        uint num,i,j,k;
        ulong iComNum ;
        char *str = NULL;
        zval *subarr;
        HashPosition pos;
        zval **entry;

        if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "al", &arr, &n) == FAILURE) {
                return;
        }
        num = zend_hash_num_elements(Z_ARRVAL_P(arr));
        if(num==0||n>num){
                php_error_docref(NULL TSRMLS_CC, E_WARNING, "the argument is wrong");
        }

        /*
		**初始化01串
		*/
/*str = (char *)emalloc(num+1);
str[num]='\0';
for(i=0;i<num;i++){
        str[i] = i<n?'1':'0';
}

/* 组合数 */
/*iComNum = getComNum(num,n);

/* 初始化返回数组 */
/* array_init(return_value);
 ALLOC_INIT_ZVAL(subarr);
 array_init(subarr);
 j=k=0;
 zend_hash_internal_pointer_reset_ex(Z_ARRVAL_P(arr), &pos);
 while (k<=num && zend_hash_get_current_data_ex(Z_ARRVAL_P(arr), (void **)&entry, &pos) == SUCCESS) {
         if(str[j]=='1'){
                 add_next_index_zval(subarr,*entry);
                 k++;
         }
         zend_hash_move_forward_ex(Z_ARRVAL_P(arr), &pos);
         j++;
 }

 add_next_index_zval(return_value,subarr);

 /* 其他组合计算 */
/*   for(i=0;i<iComNum-1;i++){
           strMove(str,num);
           ALLOC_INIT_ZVAL(subarr);
           array_init(subarr);
           j=k=0;
           zend_hash_internal_pointer_reset_ex(Z_ARRVAL_P(arr), &pos);
           while (k<=num && zend_hash_get_current_data_ex(Z_ARRVAL_P(arr), (void **)&entry, &pos) == SUCCESS) {
                   if(str[j]=='1'){
                           add_next_index_zval(subarr,*entry);
                           k++;
                   }
                   zend_hash_move_forward_ex(Z_ARRVAL_P(arr), &pos);
                   j++;
           }
           add_next_index_zval(return_value,subarr);
   }

   efree(str);
}
/*}}} */

PHP_METHOD(Person, __construct) {
	php_printf("__construct called.");
}

PHP_METHOD(Person, __destruct) {
	php_printf("__destruct called.");
}

PHP_METHOD(Person,getName) {
	zval *self, *name;
	self = getThis();

	name = zend_read_property(Z_OBJCE_P(self), self, ZEND_STRL("_name"), 0 TSRMLS_CC);

	RETURN_STRING(Z_STRVAL_P(name), 0);
}

PHP_METHOD(Person, setName) {
	char *arg = NULL;
	int arg_len;
	zval *value, *self;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &arg, &arg_len) == FAILURE) {
		WRONG_PARAM_COUNT;
	}

	self = getThis();

	MAKE_STD_ZVAL(value);
	ZVAL_STRINGL(value, arg, arg_len, 0);

	SEPARATE_ZVAL_TO_MAKE_IS_REF(&value);
	zend_update_property(Z_OBJCE_P(self), self, ZEND_STRL("_name"), value TSRMLS_CC);

	RETURN_TRUE;

}
