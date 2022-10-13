<!DOCTYPE html>
<html>
    <head>
        <title>삭제 페이지</title>
    </head>
    <body>
        <?php
        $name = isset($_POST['name']) ? $_POST['name'] : "";

        // DB 연결
        $conn = mysqli_connect("sc1.swu.ac.kr:13306", "kyung128", "kyung1284", "kyung128_ts");
        $sql = "DELETE FROM studentInfo WHERE name='$name'";
        $result = mysqli_query($conn, $sql);

        echo "'$name'의 정보가 삭제되었습니다.";
        ?>
    </body>
</html>