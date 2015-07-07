<?php
#phpinfo();
$conn = mysql_connect("localhost", "root", "");
if ($conn){
	die("faled to connect mysql... ...");
}

mysql_close($conn);

?>
