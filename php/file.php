<?php
$file = fopen("file.php", "r") or exit("Unable to open file!");
while(!feof($file)){
	echo fgetc($file); //fgets
}
fclose($file);

#通过使用 PHP 的全局数组 $_FILES，你可以从客户计算机向远程服务器上传文件。
#setcookie("user", "Alex Porter", time()+3600);
if (isset($_COOKIE["user"]))
  echo "Welcome " . $_COOKIE["user"] . "!<br />\n";
else
  echo "Welcome guest! (no _COOKIE)<br />\n";


#error format process.
function customError($error, $errstr){
	trigger_error("Errno: " . $error . " ErrMsg: " . $errstr, E_USER_WARNING); #detailed msgs
}
set_error_handler("customError");
echo ($aa);
#error_log("A custom error has been triggered",1,"someone@example.com","From: webmaster@example.com");


if (!file_exists("aaa.txt"))
	die("die! file not found. \n");


echo "end\n"

?>
