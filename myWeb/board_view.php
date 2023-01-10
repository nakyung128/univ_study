<!DOCTYPE html>
<html>
<head>
	<meta charset="utf-8">
	<meta name="viewport" content="width=device-width, initial-scale=1">
	<title>게시판 보기</title>
	<link rel="stylesheet" type="text/css" href="./css/common.css">
	<link rel="stylesheet" type="text/css" href="./css/board.css">
	<script>
		function check_input() {
			if (!document.reply_form.content.value)
			{
				alert("내용을 입력하세요!");
				document.reply_form.content.focus();
				return;
			}
			document.reply_form.submit();
		}
	</script>
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
		<h3 class="title">
			게시판 > 내용 보기
		</h3>
	<?php
		$num = $_GET['num'];
		$page = $_GET['page'];
		$rep = $_GET['rep'];

		$con = mysqli_connect("localhost", "root", "", "sample");
		$sql = "select * from board where num=$num";
		$result = mysqli_query($con, $sql);
		$row = mysqli_fetch_array($result);

		$id = $row["id"];
		$name = $row["name"];
		$regist_day = $row["regist_day"];
		$subject = $row["subject"];
		$content = $row["content"];
		$file_name = $row["file_name"];
		$file_type = $row["file_type"];
		$file_copied = $row["file_copied"];
		$hit = $row["hit"];
		$like = $row["like_num"];

		$content = str_replace(" ", "&nbsp;", $content);
		$content = str_replace("\n", "<br>", $content);
		$new_hit = $hit + 1;
		$sql = "update board set hit=$new_hit where num=$num";
		mysqli_query($con, $sql);
	?>
		<ul id="view_content">
			<li>
				<span class="col1"><b>제목: </b><?=$subject?></span>
				<span class="col2"><?=$name?> | <?=$regist_day?> | 조회 <?=$hit?> | 추천 <?=$like?></span>
			</li>
			<li>
			<?php
				if ($file_name) {
					$real_name = $file_copied;
					$file_path = "./data/".$real_name;
					$file_size = filesize($file_path);
					echo "▷ 첨부파일: $real_name ($file_size Byte)
								&nbsp;&nbsp;&nbsp;&nbsp;
						<a href='board_download.php?num=$num&real_name=$real_name&file_name=$file_name&file_type=$file_type'>
						[저장]</a><br><br>";
				}
			?>
				<?=$content?>
			</li>
			<!--좋아요 버튼-->
			<li>
				<button onclick="location.href='like_insert.php?num=<?=$num?>'" style="width: 80px;">추천</button>
			</li>
		</ul>
		<!--댓글 기능-->
		<form name="reply_form" method="post" action="reply_insert.php">
			<div id="board_form">
				<input type="hidden" name="num" value=<?=$num?>>
				<input type="hidden" name="page" value=<?=$page?>>
				<input type="hidden" name="rep" value=<?=$rep?>>
				<div id="board_box">
					<h2 class="title">
						댓글 목록
					</h2>
				</div>
				<br>
				<ul id="board_list">
				<?php
					$con = mysqli_connect("localhost", "root", "", "sample");
					$sql = "select * from reply where con_num=$num order by idx";
					$result = mysqli_query($con, $sql);
					$total_record = mysqli_num_rows($result); // 전체 댓글 수

					if ($total_record != 0)
					{
						$scale = 10;

						// 전체 댓글 수 계산
						if ($total_record % $scale == 0)
							$total_page = floor($total_record / $scale);
						else
							$total_page = floor($total_record / $scale) + 1;

						// 표시할 페이지에 따라 $start 계산
						$start = ($rep - 1) * $scale;
						$number = $total_record - $start;

						for ($i=$start; $i<$start+$scale && $i<$total_record; $i++)
						{
							mysqli_data_seek($result, $i);
							// 가져올 레코드로 위치(포인터) 이동
							$row = mysqli_fetch_array($result);
							// 하나의 레코드 가져오기
							$id = $row["id"];
							$content = $row["content"];
							$regist_day = $row["regist_day"];
				?>
					<li>
						<span class="col1"><?=$id?></span>
						<span class="col2"><?=$content?></span>
						<span class="col3"><?=$regist_day?></span>
					</li>
				<?php
							$number--;
						}
				?>
				</ul>
				<ul id="page_num">
				<?php
					if ($total_page >= 2 && $rep >= 2)
					{
						$new_rep = $rep - 1;
						echo "<li><a href='board_view.php?num=$num&page=$page&rep=$new_rep'> ◀ 이전</a></li>";
					}
					else
						echo "<li>&nbsp;</li>";
					// 게시판 목록 하단에 페이지 링크 번호 출력
					for ($i=1; $i<=$total_page; $i++)
					{
						if ($rep == $i) // 현재 페이지 번호를 링크하지 않음
						{
							echo "<li><b> $i </b></li>";
						}
						else
						{
							echo "<li><a href='board_view.php?num=$num&page=$page&rep=$i'> $i </a></li>";
						}
					}
					if ($total_page >= 2 && $rep != $total_page)
					{
						$new_rep = $rep + 1;
						echo "<li><a href='board_view.php?num=$num&page=$page&rep=$new_rep'> 다음 ▶</a></li>";
					}
					else
						echo "<li>&nbsp;</li>";
				}
			?>
				</ul>
				<br>
				<?php
					if (isset($_SESSION['userid']))
					{
				?>
				<input type="text" name="content">
				<button type="button" onclick="check_input()" style="width: 100px; height: 30px;">작성</button>
				<?php
					}
				?>
			</div>
		</form>
		<ul class="buttons">
		<?php
			$sql = "select * from board where num=$num";
			$result = mysqli_query($con, $sql);
			$row = mysqli_fetch_array($result);
			if (!isset($_SESSION['userid']))
			{				
		?>
			<li><button onclick="location.href='board_list.php?page=<?=$page?>'">목록</li>
		<?php
			}
			elseif ($row["id"] == $_SESSION['userid'])
			{
		?>
			<li><button onclick="location.href='board_list.php?page=<?=$page?>'">목록</li>
			<li><button onclick="location.href='board_modify_form.php?num=<?=$num?>&page=<?=$page?>'">수정</li>
			<li><button onclick="location.href='board_delete.php?num=<?=$num?>&page=<?=$page?>'">삭제</li>
			<li><button onclick="location.href='board_form.php'">글쓰기</li>
		<?php
			}
			else 
			{
		?>
			<li><button onclick="location.href='board_list.php?page=<?=$page?>'">목록</li>
			<li><button onclick="location.href='board_form.php'">글쓰기</li>
		<?php
			}
		?>
		</ul>
	</div>
</section>
<footer>
    <?php include "footer.php";?>
</footer>
</body>
</html>