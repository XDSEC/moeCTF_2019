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
