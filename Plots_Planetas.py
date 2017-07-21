import numpy as np
import matplotlib.pyplot as plt

datos=np.loadtxt('posiciones.txt', delimiter=" ", dtype=float)

fig=plt.figure()
ax=fig.add_subplot(111, projection='3d')
x=datos[:,0]
y=datos[:,1]
z=datos[:,2]

ax.plot(x,y,z, marker='o')
ax.set_xlabel('x(AU)')
ax.set_ylabel('y(AU)')
ax.set_zlabel('z(AU)')

plt.savefig("orbitas.pdf")
