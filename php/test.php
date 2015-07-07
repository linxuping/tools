<?php
$txt1="Hello World";
$txt2="1234";
echo $txt1 . " " . $txt2;
echo strpos("Hello world!","world");

date_default_timezone_set("Asia/Shanghai");
$d=date("D");
if ($d=="Fri")
  echo "Have a nice weekend!"; 
elseif ($d=="Sun")
  echo "Have a nice Sunday!"; 
else
  echo "Have a nice day!\n\n"; 

$names = array("Peter","Quagmire","Joe");
$names[0] = "Peter";
$names[1] = "Quagmire";
$names[2] = "Joe";
echo $names[1] . " and " . $names[2] . " are ". $names[0] . "'s neighbors\n";

$ages['Peter'] = "32";
$ages['Quagmire'] = "30";
$ages['Joe'] = "34";
echo "Peter is " . $ages['Peter'] . " years old.\n";

$families = array
(
  "Griffin"=>array(
	  "Peter",
	  "Lois",
	  "Megan"
  ),
  "Quagmire"=>array(
  	"Glenn"
  ),
  "Brown"=>array(
	  "Cleveland",
	  "Loretta",
	  "Junior"
  )
);
#echo $families

$i=1;
while($i<=5){
  echo "while " . $i . "<br />\n";
  $i++;
}

for ($i=1; $i<=5; $i++){
  echo "for " . $i . "<br />\n";
}

function printme($i){
  echo "Value: " . $i . "<br />\n";
}
$arr=array("one", "two", "three");
foreach ($arr as $value){
	printme($i);
  #echo "Value: " . $value . "<br />\n";
}


#在 PHP 中，提供了超过 700 个内建的函数。
#http://www.phpStudy.net/welcome.php?name=Peter&age=37
#<?php echo $_GET["age"]; 
#PHP 的 $_REQUEST 变量包含了 $_GET, $_POST 以及 $_COOKIE 的内容。

echo date("Y.m.d     ");
$tomorrow = mktime(0,0,0,date("m"),date("d")+1,date("Y"));
echo "Tomorrow is ".date("Y/m/d", $tomorrow);
echo "\n"



?>
