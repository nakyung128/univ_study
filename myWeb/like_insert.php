<?php
	$con = mysqli_connect("localhost", "root", "", "sample"); 
	$num = $_GET['num'];
	$sql = "select * from board where num=$num";
	$result = mysqli_query($con, $sql);
	$row = mysqli_fetch_array($result);
	$like = $row["like_num"];
	$new_like = $like + 1;
	$sql = "update board set like_num=$new_like where num=$num";
	mysqli_query($con, $sql);

	echo("
		<script>
		alert('해당 글을 추천하셨습니다!');
		history.go(-1);
		</script>
	");
?>