<?php
error_reporting(0);
//flag在flag.php里
class flag
{
    public $cmd='index.php';

    public function __destruct(){
        if (preg_match('/\w+\((?R)?\)/', $this->cmd)){
            eval('$a="'.$this->cmd.'";');
        }
        else {
            die('hack!!!');
        }
    }
}


if (!isset($_GET['fl']) || !isset($_GET['ag'])) {
    die(@highlight_file('index.php',true));
}
else {
    if (!(preg_match('/[A-Za-z0-9]+\(/i', $_GET['fl']))) {
        die('hack!!!');
    }
    else {
        echo unserialize($_GET['ag']);
    }
} 