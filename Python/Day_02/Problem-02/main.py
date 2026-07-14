import folium
import subprocess
import numpy as np
from scipy.spatial.distance import cdist, euclidean
from geopy.distance import geodesic

def geometric_median(X, eps=1e-5):
    # Source - https://stackoverflow.com/a/30305181
    # Posted by orlp, modified by community. See post 'Timeline' for change history
    # Retrieved 2026-07-14, License - CC BY-SA 3.0

    # stacoverflow에서 가져옴. 좌표를 받아서 가장 최소거리의 지점을 반환하는 함수
    # Weiszfeld 알고리즘이 이용됨

    y = np.mean(X, 0)

    while True:
        D = cdist(X, [y])
        nonzeros = (D != 0)[:, 0]

        Dinv = 1 / D[nonzeros]
        Dinvs = np.sum(Dinv)
        W = Dinv / Dinvs
        T = np.sum(W * X[nonzeros], 0)

        num_zeros = len(X) - np.sum(nonzeros)
        if num_zeros == 0:
            y1 = T
        elif num_zeros == len(X):
            return y
        else:
            R = (T - y) * Dinvs
            r = np.linalg.norm(R)
            rinv = 0 if r == 0 else num_zeros / r
            y1 = max(0, 1 - rinv) * T + min(1, rinv) * y

        if euclidean(y, y1) < eps:
            return y1
        
        y = y1

def cheak_lok(friend_loc):
    # 집 좌표의 위도 / 경도를 가져와서 np형식으로 변환하고 유효성을 확인하는 함수.
    #print(friend_loc)
    friend_loc = friend_loc.split(" ")
    friend_loc_np = np.array(friend_loc)
    if friend_loc_np.shape[0] != 2:
        raise Exception("위치의 입력은 '위도 경도' 2개의 항목만이 올수 있음.")
    friend_loc_np = friend_loc_np.astype(np.float64)

    if friend_loc_np[0] < -90 or 90 < friend_loc_np[0]:
        raise Exception("위도의 범위는 (-90:90)임")
    if friend_loc_np[1] < -180 or 180 < friend_loc_np[1]:
        raise Exception("경도의 범위는 (-180:180)임")

    return friend_loc_np


def input_friend_loc():
    #사용자로 부터 좌표를 입력받는 함수
    friend_loc_list = np.array([])
    print(
        "친구들의 집 좌표를 위도/경도 단위로 입력하시오(형식 : DD(십진법) 37.61947 127.06085)"
    )
    print(
        "입력을 종료 하려면 'e' 를 누르시오"
    )
    while True:
        temp = input(">")
        if temp == "e" : break
        try:
            friend_loc_np = cheak_lok(temp)
        except Exception as e:
            print("데이터 변환 실패 :", e)
        else:
            print("좌표 추가됨 : ", friend_loc_np)
            friend_loc_list = np.append(friend_loc_list, friend_loc_np)
    friend_loc_list_re = friend_loc_list.reshape(-1, 2)

    return friend_loc_list_re

def add_maker(friend_loc, dis_loc, map):
    #지도에 친구들의 집과 목적지를 표시하는 함수
    count = 1
    for row in friend_loc: # 친구들의 집의 위치를 표시하는 함수
        distance = geodesic(row, dis_loc).m # 목적지와 집까지의 거리를 계산하는 함수
        folium.Marker(
            location=row,
            tooltip="친구_" + str(count),
            popup="친구_" + str(count) + "위치 <br>" + "거리:" +  str(round(distance, 3)) + "m",
            icon=folium.Icon(icon="home", color="green"),
        ).add_to(map)
        count+=1

    # 목적지를 표시하는 함수
    folium.Marker(
        location=dis_loc,
        tooltip="destination",
        popup="our destination",
        icon=folium.Icon(icon="star", color="red"),
    ).add_to(map)


def main():

    friend_loc_list = input_friend_loc()

    dis_loc = geometric_median(friend_loc_list)
    print(dis_loc)

    m = folium.Map(location=(dis_loc[0], dis_loc[1]), zoom_start=12)
    add_maker(friend_loc_list, dis_loc, m)
    m.save("map.html")
    subprocess.run(['xdg-open', 'map.html'])


if __name__ == "__main__":
    main()
