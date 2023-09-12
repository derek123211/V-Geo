from ast import Yield
import random
import math
from re import X
import secrets
import numpy as np
from matplotlib import pyplot as plt
import string
import datetime



def gamma(l,epsilon):
    u = 1
    c1 = 0.01
    q = np.random.uniform(5, u / c1)
    epsilon1 = epsilon + np.log(((q - 2 + 3 * pow(math.e, epsilon * math.sqrt(2))) / (q - 5)))
    r = np.random.gamma(2, 1 / epsilon1, 1)
    return r
def rr(epsilon):
    r=np.random.uniform(0,4+pow(math.e,epsilon))
    if r<4:
        cet=0
    if r>=4:
        cet=1
    return cet
def localcom(d):
    l=d*1000*1024
    return l/(fuser*1e6)
def edgecom(d,dis,bmec,users):
    p=0.01
    r=mec*bmec*math.log2(1+p*pow(dis,-3)/(mec*bmec*1e-16))*1024
    tup=d/r
    l=d*1000*1024
    tmec=l/(fmec/users*1e6)
    return tup+tmec
def get_e(epsilon,r):
    the=0.01
    q=1/(r*the)
    e=epsilon+math.log((q*r-2+3*pow(math.e, epsilon*math.sqrt(2)))/(q*r-5))
    return np.random.uniform(epsilon,e)


if __name__ == '__main__':
    start=datetime.datetime.now()
    mec=0.5#500kHz
    # dis=1100
    # users=10
    # n=1e-16
    p=0.01
    # x=mec*0.004
    # r=x*math.log2(1+p*pow(dis,-3)/(x*n))*1024
    # d=800
    # tup=d/r
    # l=d*1000*1024
    fuser=400#500MHz
    fmec=8000#5000MHz
    # tloc=l/(fuser*1e6)
    # tmec=l/(fmec/users*1e6)
    # print(tup)
    # print(tloc)
    # print(tmec)
    # print(tmec+tup)

    qloss=0
    l =10
    epsilon = 0.3
    rmax=l/epsilon
    epsilon=get_e(epsilon,rmax)
    ex=[]
    ey=[]
    with open("C:/Users/csn/Desktop/text/Edgenode.txt") as A:
        for eachline in A :
            tmp =eachline.split()
            ex.append(float(tmp[0]))
            ey.append(float(tmp[1]))
    ux=[]
    uy=[]
    with open("C:/Users/csn/Desktop/text/user.txt") as A:
        for eachline in A:
            tmp = eachline.split()
            ux.append(float(tmp[0]))
            uy.append(float(tmp[1]))
    r=0
    dis=0
    dis1=0
    d=[]
    cdis=[]
    cdis1=[]
    ue=[]




    for i in range(len(ux)):
        d.append(random.randint(500,1000))
        cdis.append(0)
        cdis1.append(0)
        ue.append(0)
    uine=[([-1]*len(ux)) for i in range(len(ex))]

    for i in range(len(ux)):
        num=0
        dis=math.sqrt(pow(ux[i]-ex[0],2)+pow(uy[i]-ey[0],2))
        j=0
        for j in range(len(ex)):
            if dis>math.sqrt(pow(ux[i]-ex[j],2)+pow(uy[i]-ey[j],2)):
                dis=math.sqrt(pow(ux[i]-ex[j],2)+pow(uy[i]-ey[j],2))
                num=j
            ue[i]=num
        for z in range(len(ux)):
            if uine[num][z] == -1:
                uine[num][z] = i
                break
        while 1:
            theta=np.random.uniform(0,2*math.pi)
            while 1:
                r=gamma(l,epsilon)
                if r <= rmax:
                    break
            tx = ux[i] + r * math.cos(theta)
            ty=uy[i]+r*math.sin(theta)
            temp=0
            dis1=math.sqrt(pow(tx-ex[num],2)+pow(ty-ey[num],2))
            z=0
            for z in range(len(ex)):
                if dis1>math.sqrt(pow(tx-ex[z],2)+pow(ty-ey[z],2)):
                    temp=1
            if temp==0:
                break

        # ldp
        # if rr(epsilon)!=1:
        #     tx = ux[i] + random.randint(0, 15)
        #     ty = uy[i] + random.randint(0, 15)
        #     dis1 = math.sqrt(pow(tx - ex[num], 2) + pow(ty - ey[num], 2))
        # else:
        #     tx=ux[i]
        #     ty=uy[i]
        #     dis1=dis
        # r=math.sqrt(pow(tx - ux[i], 2) + pow(ty - uy[i], 2))

        # Geo
        # theta = np.random.uniform(0, 2 * math.pi)
        # while 1:
        #     r=gamma(l,epsilon)
        #     if r <= rmax:
        #         break
        # tx = ux[i] + r * math.cos(theta)
        # ty=uy[i]+r*math.sin(theta)
        # temp=0
        # dis1=math.sqrt(pow(tx-ex[num],2)+pow(ty-ey[num],2))


        qloss=qloss+r*0.4
        cdis[i]=dis
        cdis1[i]=dis1
    for i in range(len(ux)):
        disz=0
        disfz=0
        users=0
        for j in range(len(ux)):
            if uine[ue[i]][j]!=-1:
                disz=disz+cdis[uine[ue[i]][j]]
                disfz=disfz+cdis1[uine[ue[i]][j]]
                users=users+1
        tloc=localcom(d[i])
        tmec=edgecom(d[i],cdis[i],cdis[i]/disz,users)
        tmecf=edgecom(d[i],cdis[i],cdis1[i]/disfz,users)
        eup=0
        if tmecf>=tmec:
            eup=(tmecf-tmec)*p
            qloss=qloss+(tmecf-tmec)*0.3+eup*0.3


    print(qloss/len(ux))
    end=datetime.datetime.now()
    print("ruinning =",end-start)










    # # 写边缘节点
    # Note=open("C:/Users/csn/Desktop/text/Edgenode.txt",mode='w')
    # for i in range(500):
    #     Note.write(str(np.random.uniform(0, 1000)))
    #     Note.write(' ')
    #     Note.write(str(np.random.uniform(0, 1000)))
    #     Note.write('\n')
    # Note.close()
    #
    # # 写用户位置
    # Note = open("C:/Users/csn/Desktop/text/user.txt", mode='w')
    # for i in range(5000):
    #     Note.write(str(np.random.uniform(0, 1000)))
    #     Note.write(' ')
    #     Note.write(str(np.random.uniform(0, 1000)))
    #     Note.write('\n')
    # Note.close()







