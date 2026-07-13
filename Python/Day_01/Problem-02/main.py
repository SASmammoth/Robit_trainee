logs=[]

def add_log(robot_name , battery,):
    log = (
        robot_name + " battery: " + str(battery)
    )  # 2. 배터리 값은 int형식으로 들어오지만, 피연산자인 robot_name 과 " battery:" 는 string형식이라 + 연산자를 사용할수 없다. 따라서 battery를 string형식으로 형변환을 시킴
    logs.append(log) # 3. logs는 add_log의 매개변수로 들어오는 값으로써, 함수의 지역 변수이다. 따라서 함수가 종료되면 logs의 값은 삭제되므로 logs를 전역변수화 시켜 로그가 누적이 안되는 것을 없앴다.
    return logs

print(add_log("frontbot", 80))
print(add_log("rearbot", 50))
print(add_log("armbot", 20))
