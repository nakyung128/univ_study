from tkinter import*
import random


#gif 이름 리스트 생성
fnameList = ["바위_big.gif", "가위_big.gif", "보_big.gif"]

#user와 computer가 이긴 횟수를 세기 위한 전역 변수 선언
computer = 0
user = 0

## 함수 선언 부분 ##

def clickRock():   #주먹 버튼을 눌렀을 때의 함수
    global computer
    global user
    num = 0
    answer = random.randrange(0, 3) #컴퓨터가 임의의 사진을 띄우기 위해 랜덤 함수 사용
    photo = PhotoImage(file = "C:/Users/02280/OneDrive/바탕 화면/가위바위보그림파일/" + fnameList[num])
    pLabel.configure(image = photo) #이미지가 계속해서 갱신됨
    pLabel.image = photo
   
    photo1 = PhotoImage(file = "C:/Users/02280/OneDrive/바탕 화면/가위바위보그림파일/" + fnameList[answer])
    pLabel1.configure(image = photo1) #랜덤 이미지로 계속해서 갱신
    pLabel1.image = photo1
  

    ## 가위바위보 결과를 판정하기 위한 if문 ##
    if num == answer:
        pLabel2 = Label(window, text = "비겼습니다.")
        pLabel2.pack()
        pLabel2.place(x=205, y= 400)
        pLabel13.configure(text = "user: %d승"%user) #"user: n승"으로 계속해서 갱신하기 위한 코드
        pLabel12.configure(text = "computer: %d승"%computer) #"computer: n승"으로 계속해서 갱신하기 위한 코드

    elif answer == 1:
        pLabel3 = Label(window, text= "이겼습니다!")
        pLabel3.pack()
        pLabel3.place(x=205, y= 400)
        user += 1
        pLabel13.configure(text = "user: %d승"%user)
        pLabel12.configure(text = "computer: %d승"%computer)
    
    else:
        pLabel4 = Label(window, text = " 졌습니다. ")
        pLabel4.pack()
        pLabel4.place(x=205, y= 400)
        computer += 1
        pLabel12.configure(text = "computer: %d승"%computer)
        pLabel13.configure(text = "user: %d승"%user)
        

def clickScissors(): #가위 버튼을 눌렀을 때의 함수
    global computer
    global user
    num = 1
    answer = random.randrange(0, 3)
    photo = PhotoImage(file = "C:/Users/02280/OneDrive/바탕 화면/가위바위보그림파일/" + fnameList[num])
    pLabel.configure(image = photo)
    pLabel.image = photo
    
    photo1 = PhotoImage(file = "C:/Users/02280/OneDrive/바탕 화면/가위바위보그림파일/" + fnameList[answer])
    pLabel1.configure(image = photo1)
    pLabel1.image = photo1


    ## 가위바위보 결과를 판정하기 위한 if문 ##
    if num == answer:
        pLabel2 = Label(window, text = "비겼습니다.")
        pLabel2.pack()
        pLabel2.place(x=205, y= 400)
        pLabel13.configure(text = "user: %d승"%user)
        pLabel12.configure(text = "computer: %d승"%computer)
    elif answer == 2:
        pLabel3 = Label(window, text= "이겼습니다!")
        pLabel3.pack()
        pLabel3.place(x=205, y= 400)
        user += 1
        pLabel13.configure(text = "user: %d승"%user)
        pLabel12.configure(text = "computer: %d승"%computer)
    else:
        pLabel4 = Label(window, text = " 졌습니다. ")
        pLabel4.pack()
        pLabel4.place(x=205, y= 400)
        computer +=1
        pLabel12.configure(text = "computer: %d승"%computer)
        pLabel13.configure(text = "user: %d승"%user)


def clickPaper(): #보자기 버튼을 눌렀을 때의 함수
    global computer
    global user
    num = 2
    answer = random.randrange(0, 3)
    photo = PhotoImage(file = "C:/Users/02280/OneDrive/바탕 화면/가위바위보그림파일/" + fnameList[num])
    pLabel.configure(image=photo)
    pLabel.image = photo

    photo1 = PhotoImage(file = "C:/Users/02280/OneDrive/바탕 화면/가위바위보그림파일/" + fnameList[answer])
    pLabel1.configure(image = photo1)
    pLabel1.image = photo1



    ## 가위바위보 결과를 판정하기 위한 if문 ##
    if num == answer:
        pLabel2 = Label(window, text = "비겼습니다.")
        pLabel2.pack()
        pLabel2.place(x=205, y= 400)
        pLabel13.configure(text = "user: %d승"%user)
        pLabel12.configure(text = "computer: %d승"%computer)
    elif answer == 0:
        pLabel3 = Label(window, text= "이겼습니다!")
        pLabel3.pack()
        pLabel3.place(x=205, y= 400)
        user += 1
        pLabel13.configure(text = "user: %d승"%user)
        pLabel12.configure(text = "computer: %d승"%computer)

    else:
        pLabel4 = Label(window, text = " 졌습니다. ")
        pLabel4.pack()
        pLabel4.place(x=205, y= 400)
        computer += 1
        pLabel12.configure(text = "computer: %d승"%computer)
        pLabel13.configure(text = "user: %d승"%user)


## 메인 코드 부분 ##
    
window = Tk()
window.geometry("500x500") #창의 크기를 500x500으로 정함

pLabel12 = Label(window, text = "computer", fg = "blue") #처음에는 'computer'라는 텍스트만 나오게 함
pLabel12.pack()
pLabel12.place(x=70, y=400)

pLabel13 = Label(window, text = "user", fg = "red") #처음에는 'user'라는 텍스트만 나오게 함
pLabel13.pack()
pLabel13.place(x=350, y=400)

pLabel14 = Label(window, text = "   결과   ") #처음에는 '결과'라는 텍스트만 나오게 함
pLabel14.pack()
pLabel14.place(x=205, y=400)


photo4 = PhotoImage()  #처음에 아무 이미지도 뜨지 않게 하기 위한 코드
pLabel = Label(window, image = photo4)
pLabel.pack()
pLabel.place(x=250, y=150)

photo5 = PhotoImage() #처음에 아무 이미지도 뜨지 않게 하기 위한 코드
pLabel1 = Label(window, image = photo5)
pLabel1.pack()
pLabel1.place(x=50, y=150)
    

label1 = Label(window, text = "*** 가위바위보 게임 ***") #상단에 *** 가위바위보 게임 *** 출력
label1.pack()

label2 = Label(window, text = "버튼을 선택하세요!", fg = "red") #버튼을 선택하세요! 출력
label2.pack()

photo = PhotoImage(file = "C:/Users/02280/OneDrive/바탕 화면/가위바위보그림파일/바위.gif" )
btnrock = Button(window, image = photo, command = clickRock) #주먹 그림의 버튼 생성, 눌렀을 때 함수 clickRock 실행됨
btnrock.pack()
btnrock.place(x = 205, y = 50)

photo2 = PhotoImage(file = "C:/Users/02280/OneDrive/바탕 화면/가위바위보그림파일/가위.gif")
btnscissor = Button(window, image = photo2, command = clickScissors) #가위 그림의 버튼 생성, 눌렀을 때 함수 clickScissors 실행됨
btnscissor.pack()
btnscissor.place(x = 100, y = 50)


photo3 = PhotoImage(file = "C:/Users/02280/OneDrive/바탕 화면/가위바위보그림파일/보.gif")
btnpaper = Button(window, image = photo3, command = clickPaper) #보자기 그림의 버튼 생성, 눌렀을 때 함수 clickPaper 실행됨
btnpaper.pack()
btnpaper.place(x = 310, y = 50)




window.mainloop()
