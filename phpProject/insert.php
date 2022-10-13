<!DOCTYPE html>
<html>
    <head>
        <title>저장 완료</title>
    </head>
    <body>
        <h2>저장 결과</h2>
        <?php
        $name = isset($_POST['name']) ? $_POST['name'] : "";
        $stdNum = isset($_POST['stdNum']) ? $_POST['stdNum'] : "";
        $major = isset($_POST['major']) ? $_POST['major'] : "";
        $birth = isset($_POST['birth']) ? $_POST['birth'] : "";
        echo "이름: " .$name;
        echo "<br>";
        echo "학번: " .$stdNum;
        echo "<br>";
        echo "학과: " .$major;
        echo "<br>";
        echo "생년월일: " .$birth;

        # 데이터 등록
        $conn = mysqli_connect("sc1.swu.ac.kr:13306", "kyung128", "kyung1284", "kyung128_ts");
        $sql = "INSERT INTO studentInfo(stdNumber, name, major, birth, rdate) VALUES ('$stdNum','$name','$major', '$birth', null)";
        $result = mysqli_query($conn, $sql);

        mysqli_close($conn);
        ?>
    </body>
</html>