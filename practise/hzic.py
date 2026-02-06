import requests
import base64
import numpy as np
from PIL import Image
import os
from tqdm import tqdm
 
# panoid 这个值决定爬取的位置
panoid = "09004800121910171618047619R"
 
 
# 全局图网址
url = "https://mapsv1.bdimg.com/?qt=pdata&sid="+ panoid +"&pos={}_{}&z=4"
 
# 请求头
headers = {
    "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/102.0.5005.63 Safari/537.36 Edg/102.0.1245.39"
}
 
def base64_to_img(bstr, file_path):   # base64编码成图片
    imgdata = base64.b64decode(bstr)
    file = open(file_path, 'wb')
    file.write(imgdata)
    file.close()
 
def image_stitch():
    imgdict = {}
    for i in os.listdir("./img_frag"):
        if i.split(".jpg")[0].split("_")[0] not in imgdict.keys():
            imgdict[i.split(".jpg")[0].split("_")[0]] = []
 
        for j in imgdict.keys():
            if i.split(".jpg")[0].split("_")[0] == j:
                imgdict[j].append(i)
    print(imgdict)
    isfirst = 0
    imglist = []
    tempimg = Image.Image()
    for i in imgdict.keys():
        for j in imgdict[i]:
            if isfirst == 0:
                tempimg = Image.open('./img_frag/' + j)
                isfirst = 1
            else:
                img = Image.open('./img_frag/' + j)
                tempim = np.array(tempimg)  # 转化为ndarray对象
                im = np.array(img)  # 转化为ndarray对象
                imstitch = np.concatenate((tempim, im), axis=1)  # 横向拼接
                tempimg = Image.fromarray(imstitch)
 
        imglist.append(tempimg)
        tempimg = Image.Image()
        isfirst = 0
    print(imglist)
 
    saveim = imglist[0]
    for i in imglist[1:]:
        saveim = np.concatenate((saveim, i), axis=0)  # 纵向拼接
 
    saveimage = Image.fromarray(saveim)
    saveimage.save("output.jpg")
    print("Image stitching completed!")
 
def img_spide():
    # 该平台全景图片被分割为32张，全部爬取后保存
    pbar = tqdm(total=32)   # 进度条
    for i in range(0,4):
        for j in range(0,8):
            response = requests.get(url=url.format(i,j), headers=headers)
            with open('./img_frag/{}_{}.jpg'.format(i,j),'wb') as f:
                f.write(response.content)
                pbar.update(1)
    print("image collect successful!")
 
if __name__ == '__main__':
    if not os.path.exists("./img_frag"):
        os.mkdir("img_frag")
    img_spide()
    image_stitch()