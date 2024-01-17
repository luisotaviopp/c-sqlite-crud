<?php
	$command = "io.exe 18";
	$output = array();
	$return_var = 0;
	exec($command, $output, $return_var);

//	echo "Return Var: $return_var\n";
//	echo "Output:\n";
	print_r($output[0]);
?>
