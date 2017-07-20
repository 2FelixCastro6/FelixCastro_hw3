import numpy as np
import matplotlib.pyplot as plt
points=300
pasadoU = np.zeros((points,points))
presenteU = np.zeros((points,points))
futuroU = np.zeros((points,points))
mascarilla=np.ones((points,points))
tiempos=[]
presenteU[100,150]=-0.5
delta=30./puntos
c=1
delta_t=c*0.5*delta_x
#n=60./delta_t
for i in range(1,len(presenteU)-1):
		for j in range(1,len(presenteU)-1):
			futuroU[i,j]=((c**2)*(delta_t**2)*(presenteU[i-1,j]-4*presenteU[i,j]+presenteU[i+1,j]+presenteU[i,j-1]+presenteU[i,j+1])/(delta**2))-pasadoU[i,j]-2*presenteU[i,j]
	pasadoU=presenteU.copy()
	presenteU=futuroU.copy()
k=delta_t
while k<=60.:
	for i in range(1,len(presenteU)-1):
		for j in range(1,len(presenteU)-1):
			futuroU[i,j]=((c**2)*(delta_t**2)*(presenteU[i-1,j]-4*presenteU[i,j]+presenteU[i+1,j]+presenteU[i,j-1]+presenteU[i,j+1])/(delta**2))-pasadoU[i,j]-2*presenteU[i,j]
	pasadoU=presenteU.copy()
	presenteU=futuroU.copy()
	tiempos.append(futuroU)
	k+=delta_t


plt.imshow(tiempos[-1])
plt.savefig("t60.pdf")
plt.close()

