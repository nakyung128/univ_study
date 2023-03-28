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
				alert('게시판 글쓰기는 로그인 후 이용해 주세요!');
				history.go(-1)
			</script>
		");
		exit;
	}

	$subject = $_POST['subject'];
	$content = $_POST['content'];

	$subject = htmlspecialchars($subject, ENT_QUOTES);
	$content = htmlspecialchars($content, ENT_QUOTES);

	$regist_day = date("Y-m-d (H:i)");

	$upload_dir = './data/';

	$upfile_name = $_FILES['upfile']['name'];
	$upfile_tmp_name = $_FILES['upfile']['tmp_name'];
	$upfile_type = $_FILES['upfile']['type'];
	$upfile_size = $_FILES['upfile']['size'];
	$upfile_error = $_FILES['upfile']['error'];

	if ($upfile_name && !$upfile_error)
	{
		$file = explode(".", $upfile_name);
		$file_name = $file[0];
		$copied_file_name = $upfile_name;
		$uploaded_file = $upload_dir.$copied_file_name;
		if ($upfile_size > 1000000) {
			echo("
				<script>
				alert('업로드 파일 크기가 지정된 용량 (1MB)을 초과합니다!<br>
				파일 크기를 체크해 주세요.');
				history.go(-1)
				</script>
			");
			exit;
		}

		if (!move_uploaded_file($upfile_tmp_name, $uploaded_file))
		{
			echo("
				<script>
				alert('파일을 지정한 디렉터리에 복사하는 데 실패했습니다.');
				history.go(-1)
				</script>
			");
			exit;
		}
	}
	else
	{
		$upfile_name = "";
		$upfile_type = "";
		$copied_file_name = "";
	}

	$con = mysqli_connect("localhost", "root", "", "sample");
	$sql = "insert into board (id, name, subject, content, regist_day, hit, file_name, file_type, file_copied) ";
	$sql .= "values ('$userid', '$username', '$subject', '$content', '$regist_day', 0, ";
	$sql .= "'$upfile_name', '$upfile_type', '$copied_file_name')";
	mysqli_query($con, $sql); // $sql에 저장된 명령 실행

	// 포인트 부여하기
	$point_up = 100;
	$sql = "select point from members where id='$userid'";
	$result = mysqli_query($con, $sql);
	$row = mysqli_fetch_array($result);
	$new_point = $row["point"] + $point_up;

	$sql = "update members set point=$new_point where id='$userid'";
	mysqli_query($con, $sql);

	mysqli_close($con);

	echo("
		<script>
		location.href = 'board_list.php';
		</script>
	");
?>