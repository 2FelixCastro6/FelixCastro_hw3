import numpy as np
import matplotlib.pyplot as plt
from matplotlib import animation 
points=300
pasadoU = np.zeros((points,points))
presenteU = np.zeros((points,points))
futuroU = np.zeros((points,points))
mascarilla=np.ones((points,points))
tiempos=[]

presenteU[points/3,points/2]=-0.5
delta=30./points
c=1
delta_t=c*0.5*delta
alfa=float((c**2)*(delta_t**2)/(delta**2))
n=int(60./delta_t)

for i in range(points):
	if (i<135 or i>165):
		mascarilla[200,i]=0.

for i in range(1,points-1):
	for j in range(1,points-1):
		futuroU[i,j]=(alfa*(presenteU[i,j-1]+presenteU[i,j+1]+presenteU[i-1,j]+presenteU[i+1,j]-4*presenteU[i,j]))-presenteU[i,j]
pasadoU=presenteU.copy()
presenteU=futuroU.copy()
presenteU=presenteU*mascarilla
for i in range(n):
	for i in range(1,points-1):
		for j in range(1,points-1):
			futuroU[i,j]=(alfa*(presenteU[i,j-1]+presenteU[i,j+1]+presenteU[i-1,j]+presenteU[i+1,j]-4*presenteU[i,j]))+2*presenteU[i,j]-pasadoU[i,j]
	tiempos.append(futuroU.copy())
	pasadoU=presenteU.copy()
	presenteU=futuroU.copy()
	presenteU=presenteU*mascarilla

plt.imshow(tiempos[-1])
plt.savefig("t60.pdf")
plt.close()
plt.imshow(tiempos[n/2])
plt.savefig("t30.pdf")
plt.close()

fig=plt.figure()
cubeta=plt.imshow(abs(tiempos[0]), cmap='flag', extent=(30+delta, 30-delta,30+delta, 30-delta))
def refresca(i):
	cubeta.set_array(tiempos[i])
	return cubeta,

anime=animation.FuncAnimation(fig, refresca, np.arange(1,len(tiempos)), interval=20, blit=False)
anime.save('Onda.mp4', fps=10)

