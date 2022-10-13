<!DOCTYPE html>
<html lang="ko">
  <head>
    <meta charset="utf-8">
    <title>studentInfo</title>
  </head>
  <body>
        <h2>학생 목록 출력</h2>
        <?php
            $conn = mysqli_connect("sc1.swu.ac.kr:13306", "kyung128", "kyung1284", "kyung128_ts");
            $sql = "SELECT * FROM studentInfo";
            $result = mysqli_query($conn, $sql);
            if (mysqli_num_rows($result) > 0)
            {
                while ($row = mysqli_fetch_array($result)) 
                {
                echo '<p>' . "아이디: " .$row['id']. " 나이: " .$row['name'], " 학번: " .$row['stdNumber']. " 학과: " .$row['major']. " 생년월일: " .$row['birth']
                . " 등록 시간: ".$row['rdate'] .'</p>';
                }
            }
            else
            {
                echo "아직 등록된 학생이 없습니다.";
            }
            mysqli_close($conn);
        ?>
  </body>
</html>