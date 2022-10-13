<!DOCTYPE html>
<html>
    <head>
        <title>메인 페이지</title>
    </head>
    <body>
        <h2>정보 등록/조회/수정/삭제 페이지</h2>
        <script language='javascript'>
            function submitForm1()
            {
                var form = document.forms['student'];
                form.action = 'edit.php';
                form.submit();
            }
            function submitForm2()
            {
                var form = document.forms['student'];
                form.action = 'delete.php';
                form.submit();
            }
        </script>
        <div>
            <form name="student" method="POST" action="insert.php">
                <ul>
                    <li>이름 : <input type="text" name="name"></li>
                    <li>학번 : <input type="text" name="stdNum"></li>
                    <li>학과 : <input type="text" name="major"></li>
                    <li>생년월일 : <input type="date" name="birth"></li>
                    <br>
                    <input type="submit" value="등록">
                    <input type="button" onclick="location.href='http://sc1.swu.ac.kr/~kyung128/list.php'" value="조회">
                    <input type="button" onclick = "submitForm1()" value="수정">
                    <input type="button" onclick = "submitForm2()" value="삭제">
                </ul>
            </form>
        </div>
    </body>
</html>