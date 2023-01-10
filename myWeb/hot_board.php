<!DOCTYPE html>
<html>
<head>
	<meta charset="utf-8">
	<meta name="viewport" content="width=device-width, initial-scale=1">
	<title>HOT 게시판</title>
	<link rel="stylesheet" type="text/css" href="./css/common.css">
	<link rel="stylesheet" type="text/css" href="./css/board.css">
</head>
<body>
<header>
    <?php include "header.php";?>
</header>
<section>
<div id="main_img_bar">
	<img src="./img/main_img.png">
</div>
<div id="board_box">
	<h3>HOT 게시판 - 추천수 TOP5</h3>
	<ul id="board_list">
		<li>
			<span class="col1">순위</span>
			<span class="col2">제목</span>
			<span class="col3">글쓴이</span>
			<span class="col4">첨부</span>
			<span class="col5">등록일</span>
			<span class="col6">조회</span>
			<span class="col7">추천</span>
		</li>
		<?php
			if (isset($_GET['page']))
				$page = $_GET['page'];
			else
				$page = 1;

			$con = mysqli_connect("localhost", "root", "", "sample");
			$sql = "select * from board order by like_num desc limit 5";
			$result = mysqli_query($con, $sql);

			for ($number=0; $number<5; $number++)
			{
				mysqli_data_seek($result, $number);
				// 가져올 레코드로 위치(포인터) 이동
				$row = mysqli_fetch_array($result);
				// 하나의 레코드 가져오기
				$num = $row["num"];
				$id = $row["id"];
				$name = $row["name"];
				$subject = $row["subject"];
				$regist_day = $row["regist_day"];
				$hit = $row["hit"];
				$like = $row["like_num"];
				if ($row["file_name"])
					$file_image = "<img src='./img/file.gif'>";
				else
					$file_image = " ";
		?>
		<li>
			<?php $rank = $number + 1?>
			<span class="col1"><?=$rank?></span>
			<span class="col2">
				<?php
					if ($userid) {
				?>
				<a href="board_view.php?num=<?=$num?>&page=<?=$page?>&rep=1"><?=$subject?></a>
				<?php
					}					
					else {
				?>
				<a href="javascript:alert('로그인 후 이용해 주세요!')"><?=$subject?></a>
				<?php
					}
				?>
			</span>
			<span class="col3"><?=$name?></span>
			<span class="col4"><?=$file_image?></span>
			<span class="col5"><?=$regist_day?></span>
			<span class="col6"><?=$hit?></span>
			<span class="col7"><?=$like?></span>
		</li>
		<?php
			}		
			mysqli_close($con);
		?>
	</ul>
</div>
</body>
</html>