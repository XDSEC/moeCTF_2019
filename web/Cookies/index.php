<html>
<head>
    <style>
    .login {
        height: 408px;
        width: 368px;
        position: absolute;
        top: 20%;
        right: 15%;
    }
    .result {
        position: absolute;
        top: 20%;
        right: 75%;
    }
    </style>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.4.0/css/bootstrap.min.css">
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.4.0/jquery.min.js"></script>
    <script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.4.0/js/bootstrap.min.js"></script>
</head>
<body>

    <div class="login">
    <form method="post">
        <div class="input-group">
              <span class="input-group-addon" id="sizing-addon2">username</span>
              <input type="text" class="form-control" placeholder="username" aria-describedby="sizing-addon2" name="user">
        </div>
        <br>
        <div class="input-group">
              <span class="input-group-addon" id="sizing-addon2">password</span>
              <input type="password" class="form-control" placeholder="password" aria-describedby="sizing-addon2" name="pwd">
        </div>
        <br>
        <div class="input-group">
              <span class="input-group-addon" id="sizing-addon2">verification</span>
              <input type="text" class="form-control" placeholder="verification" aria-describedby="sizing-addon2" name="verify">
        </div>
        <br>
        <button type="submit" class="btn btn-primary button " >登陆</button>
    </form>
    <p>注：认证消息的md5值应当与"aabg7XSs"相等</p>
    <footer>然而认证消息并不能是"aabg7XSs"...</footer>
    </div>
</body>
<div class="result">
<?php
$key = '\'moectf{XsS_1s_s0_b4sic_th4t_I_want3d_some_php}\'';
if(!isset($_POST['user'])||!isset($_POST['pwd']))
	    die('');
if($_POST['verify']=='aabg7XSs'){
	    echo 'hint: phptricks';
}
if(md5($_POST['verify'])!=md5('aabC9RqS'))
	    die('认证消息md5不匹配');
if(strstr($_POST['user'],'<script>')!==false){
	    $_POST['user'] = str_replace('document.cookie',$key,$_POST['user']);
}
echo $_POST['user'];
?>
</div>
</html>