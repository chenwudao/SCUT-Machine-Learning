import folium
import numpy as np

# 假设大学坐标存储在列表coords中（按排名顺序）
coords = [
    # Node 1
    (125, 374),
    # Node 2
    (240, 450),
    # Node 3
    (365, 134),
    # Node 4
    (98, 292),
    # Node 5
    (412, 367),
    # Node 6
    (221, 301),
    # Node 7
    (459, 429),
    # Node 8
    (188, 49),
    # Node 9
    (67, 365),
    # Node 10
    (201, 411),
    # Node 11
    (308, 217),
    # Node 12
    (414, 257),
    # Node 13
    (152, 380),
    # Node 14
    (26, 412),
    # Node 15
    (320, 95),
    # Node 16
    (178, 174),
    # Node 17
    (77, 138),
    # Node 18
    (344, 301),
    # Node 19
    (89, 215),
    # Node 20
    (250, 440),
    # Node 21
    (423, 92),
    # Node 22
    (329, 364),
    # Node 23
    (158, 301),
    # Node 24
    (372, 178),
    # Node 25
    (195, 88),
    # Node 26
    (91, 40),
    # Node 27
    (281, 206),
    # Node 28
    (359, 401),
    # Node 29
    (450, 50),
    # Node 30
    (115, 312),
    # Node 31
    (489, 298),
    # Node 32
    (203, 140),
    # Node 33
    (408, 345),
    # Node 34
    (145, 108),
    # Node 35
    (280, 419),
    # Node 36
    (56, 202),
    # Node 37
    (369, 484),
    # Node 38
    (224, 390),
    # Node 39
    (198, 471),
    # Node 40
    (96, 176),
    # Node 41
    (389, 121),
    # Node 42
    (351, 290),
    # Node 43
    (277, 97),
    # Node 44
    (485, 361),
    # Node 45
    (174, 250),
    # Node 46
    (410, 205),
    # Node 47
    (140, 60),
    # Node 48
    (303, 465),
    # Node 49
    (228, 485),
    # Node 50
    (373, 38),
    # Node 51
    (87, 320),
    # Node 52
    (390, 201),
    # Node 53
    (169, 99),
    # Node 54
    (267, 189),
    # Node 55
    (191, 344),
    # Node 56
    (91, 251),
    # Node 57
    (456, 320),
    # Node 58
    (173, 395),
    # Node 59
    (420, 429),
    # Node 60
    (123, 256),
    # Node 61
    (496, 481),
    # Node 62
    (239, 233),
    # Node 63
    (294, 142),
    # Node 64
    (72, 487),
    # Node 65
    (165, 222),
    # Node 66
    (83, 34),
    # Node 67
    (265, 47),
    # Node 68
    (448, 158),
    # Node 69
    (132, 283),
    # Node 70
    (325, 332),
    # Node 71
    (242, 287),
    # Node 72
    (100, 79),
    # Node 73
    (312, 458),
    # Node 74
    (369, 271),
    # Node 75
    (37, 114),
    # Node 76
    (180, 439),
    # Node 77
    (249, 316),
    # Node 78
    (199, 362),
    # Node 79
    (450, 283),
    # Node 80
    (344, 220),
    # Node 81
    (215, 498),
    # Node 82
    (267, 424),
    # Node 83
    (158, 422),
    # Node 84
    (480, 192),
    # Node 85
    (99, 59),
    # Node 86
    (362, 356),
    # Node 87
    (442, 102),
    # Node 88
    (212, 59),
    # Node 89
    (78, 275),
    # Node 90
    (275, 260),
    # Node 91
    (153, 467),
    # Node 92
    (488, 270),
    # Node 93
    (371, 83),
    # Node 94
    (317, 317),
    # Node 95
    (401, 209),
    # Node 96
    (283, 372),
    # Node 97
    (49, 178),
    # Node 98
    (451, 393),
    # Node 99
    (229, 182),
    # Node 100
    (94, 121)
]

# 假设 best_route 是最优路线的节点顺序（示例：随机排列）
best_route = np.random.permutation(len(coords))

# 创建地图
m = folium.Map(location=[40, -100], zoom_start=3)

# 绘制路线
route_coords = [coords[i] for i in best_route] + [coords[best_route[0]]]  # 闭合路径
folium.PolyLine(route_coords, color="red", weight=2.5).add_to(m)

# 保存为HTML文件
m.save("tsp_route.html")