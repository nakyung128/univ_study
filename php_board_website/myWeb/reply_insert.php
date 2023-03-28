<meta charset="utf-8">
<?php
	session_start();
	if (isset($_SESSION['userid'])) $userid = $_SESSION['userid'];
	else $userid = "";
	if (isset($_SESSION['username'])) $username = $_SESSION['username'];
	else $username = "";

	if (!$userid)
	{
		echo("
			<script>
				alert('댓글 작성은 로그인 후 이용해 주세요!');
				history.go(-1)
			</script>
		");
		exit;
	}

	$content = $_POST['content'];
	$content = htmlspecialchars($content, ENT_QUOTES);
	$con_num = $_POST['num'];
	$page = $_POST['page'];
	$rep = $_POST['rep'];
	$regist_day = date("Y-m-d (H:i)");

	$con = mysqli_connect("localhost", "root", "", "sample");
	$sql = "insert into reply (con_num, name, id, content, regist_day)"; 
	$sql .= "values ($con_num, '$username', '$userid', '$content', '$regist_day')";
	mysqli_query($con, $sql);
	mysqli_close($con);

	echo("
		<script>
		location.href = 'board_view.php?num=$con_num&page=$page&rep=$rep';
		</script>
	");
?>