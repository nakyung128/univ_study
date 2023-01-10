<<!DOCTYPE html>
<html>
<head>
	<meta charset="utf-8">
	<meta name="viewport" content="width=device-width, initial-scale=1">
	<title>포인트 퀴즈</title>
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
		<h3>퀴즈 맞히고 포인트 쌓자!</h3>
		<ul id="board_list">
		<?php
				$con = mysqli_connect("localhost", "root", "", "sample");
				$sql = "select * from quiz where clear=false order by idx";
				$result = mysqli_query($con, $sql);
				$total = mysqli_num_rows($result);

				if ($total == 0) {
					echo "<br><br><h2>풀 문제가 없어요! 업데이트를 기다려 주세요.</h2>";
				}

				else {
					for ($i = 0; $i < $total; $i++)
					{
						mysqli_data_seek($result, $i);
						$row = mysqli_fetch_array($result);
						$idx = $row["idx"];
						$question = $row["question"];
						$answer = $row["answer"];
						$score = $row["score"];
						$one = $row["one"];
						$two = $row["two"];
						$three = $row["three"];
						$answer = $row["answer"];		
		?>
			<li>
				<form name="quiz_form" method="post" action="quiz_insert.php">
					<input type="hidden" name="score" value=<?=$score?>>
					<input type="hidden" name="idx" value=<?=$idx?>>
					<span style="width: 800px; text-align: left; padding-left: 20px;"><?=$idx.'.'?> &nbsp; <?=$question?> ------- <?=$score?>점</span>
					<br><br>
					<span style="padding-left: 80px;">
						<input type="radio" name="select" value="no"> <?=$one?> &nbsp;
						<input type="radio" name="select" value="no"> <?=$two?> &nbsp;
						<input type="radio" name="select" value="yes"> <?=$answer?> &nbsp;
						<input type="radio" name="select" value="no"> <?=$three?> &nbsp;&nbsp;&nbsp;
						<input type="submit" value="정답 확인!" style="width: 100px; height:30px;">
					</span>
				</form>
			</li>
		<?php
			}
		}
		?>
		</ul>
	</div>
</section>
</body>
</html>