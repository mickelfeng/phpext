#include <sapi/embed/php_embed.h>
#include <zend_stream.h>
int main(int argc,char*argv[]){
  zend_file_handle script;
  volatile int exit_status = 0;
  if(argc<=1){
    fprintf(stderr,"Usage: syntax filename.php <arguments>\n");
    return -1;
  }

  script.type=ZEND_HANDLE_FP;
  script.filename=argv[1];
  script.opened_path=NULL;
  script.free_filename=0;
  if(!(script.handle.fp=fopen(script.filename,"rb"))){
    fprintf(stderr,"Unable to open : %s\n",argv[1]);
    return -1;
  }
  argc--;
  argv++;

  PHP_EMBED_START_BLOCK(argc,argv)
  exit_status = php_lint_script(&script TSRMLS_CC);
	if (exit_status==SUCCESS) {
		zend_printf("No syntax errors detected in %s\n", script.filename);
	} else {
		zend_printf("Errors parsing %s\n", script.filename);
	}
  PHP_EMBED_END_BLOCK()
  return 0;
}
