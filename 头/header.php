<?php
if(!isset($_COOKIE['login'])) {
    setcookie('login', 'false');
    $_COOKIE['login'] = 'false';
}
if($_COOKIE['login'] === 'false') {
    die('permission denied');
}
if(strstr($_SERVER['HTTP_USER_AGENT'], 'PowerPC') === false){
    die('this page is too old for modern PCs. Use PowerPC.');
}
if(strstr($_SERVER['HTTP_ACCEPT'], 'flag') === false){
    echo('$_SERVER[\'HTTP_ACCEPT\']'.$_SERVER['HTTP_ACCEPT']."<br>\n");
    die('I don\'t think that you are ready to receive a "application/flag" message');
}
header('flag: moectf{M0m_I_c4n_m0dify_HTTP_H3aders!}');