<?php
	$select = $_POST['select'];
	$score = $_POST['score'];
	$idx = $_POST['idx'];
	session_start();
	$userid = $_SESSION['userid'];

	if ($select == "yes") {
		echo("
			<script>
			alert('정답입니다! {$score}p 획득!');
			history.go(-1);
			</script>");

		$con = mysqli_connect("localhost", "root", "", "sample");
		$sql = "select * from members where id='$userid'";
		$result = mysqli_query($con, $sql);
		$row = mysqli_fetch_array($result);
		$point = $row["point"];
		$new_point = $point + $score;

		$sql = "update members set point=$new_point where id='$userid'";
		mysqli_query($con, $sql);

		$sql = "update quiz set clear=true where idx=$idx";
		mysqli_query($con, $sql);
		mysqli_close($con);
	} else {
		echo("
			<script>
			alert('오답입니다!');
			history.go(-1);
			</script>");
	}
?>