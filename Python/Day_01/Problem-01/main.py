robot_status = [
    {"name": "mobilebot", "battery": 82, "position": (1.2, 0.5), "distance": 0.8},
    {"name": "drone", "battery": 18, "position": (0.3, 1.5), "distance": 0.4},
    {"name": "manipulator", "battery": 45, "position": (2.0, 1.0), "distance": 1.2},
]

def robot_status_printer(robot_state_dic):
    # robot 상태를 딕셔너리 형식으로 받아와서 출력하는 함수
    
    #robot의 이름을 출력한다.
    print("[" + robot_state_dic["name"] + "]")
    
    #로봇의 배터리 상태를 출력한다.
    print("배터리 : ", end="")
    if robot_state_dic["battery"] >= 60 : print("배터리 충분")
    elif robot_state_dic["battery"] >= 20 : print("배터리 주의")
    else : print("배터리 부족")
    
    #로봇의 위치를 출력한다.
    print("위치 : x=" + str(robot_state_dic["position"][0]) + ", y=" + str(robot_state_dic["position"][1]) )
    #로봇의 전진가능성을 출력한다.
    print("상태 :", "전진 가능" if robot_state_dic["distance"] >= 0.5 else "장애물 감지", end="\n\n")
    

for robot in robot_status:
    robot_status_printer(robot)
