import numpy as np
import matplotlib.pyplot as plt

pasadoU = np.zeros((30,30))
presenteU = np.zeros((30,30))
futuroU = np.zeros((30,30))
tiempos=[]
presenteU[10,15]=-0.5
delta_x=30./30.
delta_y=30./300.
c=1
delta_t=c*0.5*delta_x
n=60./delta_t
k=delta_t
while k<=60:
	for i in range(1,len(presenteU)-1):
		for j in range(1,len(presenteU)-1):
			futuroU[i,j]=((c**2)*(delta_t**2)*(((presenteU[i-1,j]-2*presenteU[i,j]+presenteU[i+1,j])/(delta_x**2))+((presenteU[i,j-1]-2*presenteU[i,j]+presenteU[i,j+1])/(delta_y**2))))-pasadoU[i,j]-presenteU[i,j]
	pasadoU=presenteU.copy()
	presenteU=futuroU.copy()
	tiempos.append(pasadoU)
	k+=delta_t


plt.imshow(tiempos)
plt.savefig("t60.pdf")
plt.close()

