<!DOCTYPE html>
<html>
    <head>
        <title>정보 수정</title>
    </head>
    <body>
        <h2>수정된 정보</h2>
        <?php
        $name = isset($_POST['name']) ? $_POST['name'] : "";
        $stdNum = isset($_POST['stdNum']) ? $_POST['stdNum'] : "";
        $major = isset($_POST['major']) ? $_POST['major'] : "";
        $birth = isset($_POST['birth']) ? $_POST['birth'] : "";

        // DB 연결
        $conn = mysqli_connect("sc1.swu.ac.kr:13306", "kyung128", "kyung1284", "kyung128_ts");
        $sql = "UPDATE studentInfo SET name='$name', major='$major', birth='$birth', rdate=null WHERE stdNumber='$stdNum'";
        $result = mysqli_query($conn, $sql);

        echo "이름: " .$name;
        echo "<br>";
        echo "학번: " .$stdNum;
        echo "<br>";
        echo "학과: " .$major;
        echo "<br>";
        echo "생년월일: " .$birth;
        ?>
    </body>
</html>