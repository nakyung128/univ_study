<!DOCTYPE html>
<html>
<head>
	<meta charset="utf-8">
	<meta name="viewport" content="width=device-width, initial-scale=1">
	<title>로그인 페이지</title>
	<link rel="stylesheet" type="text/css" href="./css/common.css">
	<link rel="stylesheet" type="text/css" href="./css/login.css">
	<script type="text/javascript" src="./js/login.js"></script>
</head>
<body>
<header>
    <?php include "header.php";?>
</header>
<div id="login_box">
	<div id="login_title">
		<span>로그인</span>
	</div>
	<div id="login_form">
		<form name="login_form" method="post" action="login.php">
			<ul>
				<li>아이디 <input type="text" name="id"></li>
				<li>비밀번호 <input type="password" name="pass"></li>
			</ul>
			<div id="login_btn">
            	<a href="#"><img src="./img/login.png" onclick="check_input()"></a>
            </div>		
		</form>
	</div>
</div>
</body>
</html>