<!DOCTYPE html>
<html>
<head>
	<meta charset="utf-8">
	<meta name="viewport" content="width=device-width, initial-scale=1">
	<title>쪽지함 목록</title>
	<link rel="stylesheet" type="text/css" href="./css/common.css">
	<link rel="stylesheet" type="text/css" href="./css/message.css">
</head>
<body>
<header>
    <?php include "header.php";?>
</header>
<section>
	<div id="message_box">
		<h3>
			<?php
				if (isset($_GET['page']))
					$page = $_GET['page'];
				else
					$page = 1;
				$mode = $_GET['mode'];
				if ($mode == "sent")
					echo "송신 쪽지함 > 목록 보기";
				else
					echo "수신 쪽지함 > 목록 보기";
			?>
		</h3>
		<ul id="message">
			<li>
				<span class="col1">번호</span>
				<span class="col2">제목</span>
				<span class="col3">
				<?php
					if ($mode == "send")
						echo "받은이";
					else
						echo "보낸이";
				?>
				</span>
				<span class="col4">등록일</span>
			</li>
			<?php
				$con = mysqli_connect("localhost", "root", "", "sample");
				if ($mode == "send")
					$sql = "select * from message where send_id='$userid' order by num desc";
				else
					$sql = "select * from message where rv_id='$userid' order by num desc";
				$result = mysqli_query($con, $sql);
				$total_record = mysqli_num_rows($result); // 전체 쪽지 수

				$scale = 10;

				// 전체 페이지 수 계산
				if ($total_record % $scale == 0)
					$total_page = floor($total_record/$scale);
				else
					$total_page = floor($total_record/$scale)+1;
				// 표시할 페이지에 따라 $start 계산
				$start = ($page - 1) * $scale;
				$number = $total_record - $start;
				for ($i = $start; $i < $start+$scale && $i < $total_record; $i++)
				{
					mysqli_data_seek($result, $i);
					$row = mysqli_fetch_array($result);
					$num = $row["num"];
					$subject = $row["subject"];
					$regist_day = $row["regist_day"];
					if ($mode == "send")
						$msg_id = $row["rv_id"];
					else
						$msg_id = $row["send_id"];
					$result2 = mysqli_query($con, "select name from members where id='$msg_id'");
					$record = mysqli_fetch_array($result2);
					$msg_name = $record["name"];
			?>
			<li>
				<span class="col1"><?=$number?></span>
				<span class="col2">
					<a href="message_view.php?mode=send&num=<?=$num?>">
						<?=$subject?>
					</a>
				</span>
				<span class="col3"><?=$msg_name?>(<?=$msg_id?>)</span>
				<span class="col4"><?=$regist_day?></span>
			</li>
			<?php
					$number--;
				}
				mysqli_close($con);
			?>
		</ul>
		<ul id="page_num">
			<?php
				if ($total_page >= 2 && $page >= 2)
				{
					$new_page = $page - 1;
					echo "<li>
						<a href='message_box.php?mode=$mode&page=$new_page'>
						 ◀ 이전</a></li>";
				}
				else
					echo "<li>&nbsp;</li>";

				// 게시판 목록 하단에 페이지 링크 번호 출력
				for ($i=1; $i<=$total_page; $i++)
				{
					if ($page == $i)
					{
						echo "<li><b> $i </b></li>"; // 현재 페이지 볼드체로
					}
					else
					{
						echo "<li><a href='message_box.php?mode=$mode&page=$i'>
						  $i </a></li>";
					}
				}

				if ($total_page >= 2 && $page != $total_page)
				{
					$new_page = $page + 1;
					echo "<li><a href='message_box.php?mode=$mode&page=$new_page'>
					 ▶ 다음 </a></li>";
				}
				else
					echo "<li>&nbsp;</li>";
			?>
		</ul>
		<ul class="buttons">
			<li><button onclick="location.href='message_box.php?mode=rv'">수신 쪽지함</li>
			<li><button onclick="location.href='message_box.php?mode=send'">송신 쪽지함</li>
			<li><button onclick="location.href='message_form.php'">쪽지 보내기</li>
		</ul>
	</div>
</section>
<footer>
    <?php include "footer.php";?>
</footer>
</body>
</html>