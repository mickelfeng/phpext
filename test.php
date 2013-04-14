<?php 
echo "***********INI******************\n";
echo test("aaaaaaaa");

echo "\n************type test*****************\n";
    hello_dump(1234);
    echo '<br/>';
    hello_dump('terrylee');
    echo '<br/>';
    hello_dump(array('foo', 'bar'));
echo "\n*************type test end****************\n";

echo "\n************class test*****************\n";
$height = 12;
$width = -10;
//$width=22;
$rectangle = new Rectangle($width, $height);
$area = $rectangle->getArea();
var_dump($area);

$circle = $rectangle->getCircle();
var_dump($circle);

$clone = $rectangle->clone();
$_area = $clone->getArea();
var_dump($_area);

$clone->setWidth(100);
$clone->setHeight(200);
$_area = $clone->getArea();
var_dump($_area);

$width = $clone->getWidth();
var_dump($width);
$height = $clone->getHeight();
var_dump($height);
echo "\n************class test end****************\n";


echo "\n************test_dump start*****************\n";
$a=array('dfasfdasf','test');
test_dump($a);


echo "\n************test_dump end chant****************\n";
$a = array();
chant(6, "derp", $a);
echo join($a, "\n")."\n";
 
echo "\n************test_dump start*****************\n";


getYig();

echo "\n************find array start*****************\n";

$ba = array("Tsathoggua" => "The Toad God",
           "Yig" => "Father of Serpents",
           "Ythogtha" => "The Thing in the Pit");
 
var_dump(findMonster("Yig", $ba));

echo "\n************find array end*****************\n";
/*
  ZVAL_NULL(pzv);
  Z_TYPE_P(pzv) = IS_NULL
  
  ZVAL_BOOL(pzv, b);
  Z_TYPE_P(pzv) = IS_BOOL
  Z_BVAL_P(pzv) = b ? 1 : 0;
  
  
  ZVAL_TRUE(pzv);
  ZVAL_BOOL(pzv, 1);
  ZVAL_BOOL(pzv, 0);
  ZVAL_LONG(pzv, L);
  Z_TYPE_P(pzv) = IS_LONG;
  Z_LVAL_P(pzv) = L;
  ZVAL_DOUBLE(pzv, d);
  Z_TYPE_P(pzv) = IS_DOUBLE;
  Z_DVAL_P(pzv) = d;
  ZVAL_STRINGL(pzv, str, len, dup);
  Z_TYPE_P(pzv) = IS_STRING;
  Z_STRLEN_P(pzv) = len;
  
  if (dup) {
  Z_STRVAL_P(pzv) = estrndup(str, len + 1);
  } else {
  Z_STRVAL_P(pzv) = str;
  }
  
  ZVAL_STRING(pzv, str, dup);
  ZVAL_STRING(pzv, str, strlen(str), dup);
  // dup值为1：申请新的内存并复制字符串的内容；dup值为0：直接指向已有的字符串数据)
  ZVAL_RESOURCE(pzv, res);
  Z_TYPE_P(pzv) = IS_RESOURCE;
  Z_RESVAL_P(pzv) = res;
*/

  $a = 'Hello world';
  $b = $a;
  unset($a);
  
  php_syntax_check("a.php");
  
  class Example{
  public static function factory($type){
  if(include_once('Drivers/'.$type.'.php')){
  $classname='Driver_'.$type;
  return new $classname;
  }else{
  throw new Exception("driver not found");
  }
  }
  }
  
  //$mysql = Example::factory('MySQL');
  
  
  // dl("php_ext_bankie.dll");
  // echo confirm_ext_bankie_compiled("aaaaaaaaaa");
  //print_r(get_extension_funcs("my_open"));
  var_dump($_FUCK);
  echo confirm_my_open_compiled("aaaaaaaaaa");
  
  echo __FILE__;
  $fp_in = file_open("C:\\1.c", "r") or die("Unable to open input file/n");
  $fp_out = file_open("test.txt.new", "w") or die("Unable to open output file/n");
  
  while (!file_eof($fp_in))
  {
  $str = file_read($fp_in, 1024);
  echo $str;echo "aa";
  
  file_write($fp_out, $str);
  } 
  
  sample_fclose($fp_in);
  
  echo $_MYEXTENSION['aa'];
  
  file_close($fp_out);
  
  echo file_read("my_open.c");

  echo confirm_fuckphp_compiled("aaaaaaaaaa");
  echo "\n";
  
  $person = new Person();  
  $person->setName("TerryLee");  
  echo $person->getName().'<br/>';

?>
