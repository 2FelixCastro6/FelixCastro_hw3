#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
double datos(int i, int j);
int indice(int i,int j);
float aceleracion(int i,int j, double *masas, double *X,double *Y,double *Z, float G);
void velocidadmedia(int i,int j,double *Vx,double *Vy,double *Vz,double *Vmediax, double *Vmediay,double *Vmediaz,float ax,float ay,float az, float delta_t);
void velocidad(int i,int j, double *Vx,double *Vy,double *Vz,double *Vmediax, double *Vmediay,double *Vmediaz,float axmed,float aymed ,float azmed, float delta_t);
void posicion(int i,int j,double *X,double *Y,double *Z,double *Vmediax, double *Vmediay,double *Vmediaz, float delta_t);

int main(void){

	float delta_t=0.1;
	int n=2000;
	float G= 4*pow(3.14159265358979323846,2);
	int i=0;
	int j=0;
	double *masas=malloc(10*sizeof(float));
	double *Vmediax= malloc(10*sizeof(float));
	//Vmediasx[0]=1;
	double *Vmediay= malloc(10*sizeof(float));
	//Vmediasy[0]=1;
	double *Vmediaz= malloc(10*sizeof(float));
	//Vmediasz[0]=1;
	double *X= malloc(((n*10)+n)*sizeof(float));
	double *Y= malloc(((n*10)+n)*sizeof(float));
	double *Z= malloc(((n*10)+n)*sizeof(float));
	double *Vx= malloc(((n*10)+n)*sizeof(float));
	double *Vy= malloc(((n*10)+n)*sizeof(float));
	double *Vz= malloc(((n*10)+n)*sizeof(float));

	for(i; i<=9;i+1){
		masas[i]= datos(i,0)/datos(0,0);
		X[i]= datos(i,1);
	 	Y[i]= datos(i,2);
		Z[i]= datos(i,3);
		Vx[i]= datos(i,4);
		Vy[i]= datos(i,5);
		Vz[i]= datos(i,6);
	}
	//printf("%lf\n",masas[3]);
	float ax;
	float ay;
	float az;
	float axmed;
	float aymed;
	float azmed;
	for(i; i<=9;i+1){	
		for(j;j<=n-1;j+1){
			ax, ay, az=aceleracion(i,j,masas,X,Y,Z,G);
			axmed, aymed, azmed=aceleracion(i,(j+1),masas,X,Y,Z,G);
			velocidadmedia(i,j,Vx,Vy,Vz,Vmediax,Vmediay,Vmediaz,ax,ay,az,delta_t);
			velocidad(i,j,Vx,Vy,Vz,Vmediax,Vmediay,Vmediaz,axmed,aymed ,azmed,delta_t);
			posicion(i,j,X,Y,Z,Vmediax,Vmediay,Vmediaz,delta_t);
			//printf("%f\n",X[indice(i,j)]);
		}
	}	
return 0;
}


double datos(int i,int j){
	FILE*file;
	file=fopen("coordinates.csv","r");
	
	int len=250;
	char line_buffer[len];
	char *split_buffer;
	const char *delimiter;
	delimiter=",";
	float matrizdatos[10][7];
	while(fgets(line_buffer,len,file)){
		j=0;
		split_buffer=strtok(line_buffer,delimiter);
		while(split_buffer != NULL){
			if (j != 0)
			{ 
				matrizdatos[i][j-1]=atof(split_buffer);
				//printf("%f\n",matrizdatos[i][j-1]);
			}
			split_buffer=strtok(NULL,delimiter);
			
			j+=1;
		}
	i+=1;
	}
return(matrizdatos[i][j]);
}	


int indice(int i,int j){
	return ((2000*i)+j);
	}

float aceleracion(int i,int j, double *masas, double *X,double *Y,double *Z, float G ){
	float factor;	
	float *a;
	float *b;
	float *c;
	float ax;
	float ay;
	float az;
	int k=0;
	for(k; k<=9; k+1){
		if(i !=k){
			factor=(-G*masas[i]*masas[k]/pow((pow((X[indice(i,j)]-X[indice(k,j)]),2)+pow((Y[indice(i,j)]-Y[indice(k,j)]),2)+pow((Z[indice(i,j)]-Z[indice(k,j)]),2)),1.5));
			a[i]=factor*(X[indice(i,j)]-X[indice(k,j)]);
			ax=ax+a[k];
			b[i]=factor*(Y[indice(i,j)]-Y[indice(k,j)]);
			ay=ay+b[k];
			c[i]=factor*(Z[indice(i,j)]-Z[indice(k,j)]);	
			az=az+c[k];
			
		}		
	}	
return ax/masas[i];
return ay/masas[i];
return az/masas[i];
}

void velocidadmedia(int i,int j,double *Vx,double *Vy,double *Vz,double *Vmediax, double *Vmediay,double *Vmediaz,float ax,float ay,float az, float delta_t){
	Vmediax[indice(i,j+0.5)]=Vx[indice(i,j)]+ 0.5*ax*delta_t;
	Vmediay[indice(i,j+0.5)]=Vy[indice(i,j)]+ 0.5*ay*delta_t;
	Vmediaz[indice(i,j+0.5)]=Vz[indice(i,j)]+ 0.5*az*delta_t;
}

void velocidad(int i,int j, double *Vx,double *Vy,double *Vz,double *Vmediax, double *Vmediay,double *Vmediaz,float axmed,float aymed ,float azmed, float delta_t){
	Vx[indice(i,j+1)]= Vmediax[indice(i,j+0.5)]+ 0.5*axmed*delta_t;
	Vy[indice(i,j+1)]= Vmediay[indice(i,j+0.5)]+ 0.5*aymed*delta_t;
	Vz[indice(i,j+1)]= Vmediaz[indice(i,j+0.5)]+ 0.5*azmed*delta_t;	
}

void posicion(int i,int j,double *X,double *Y,double *Z,double *Vmediax, double *Vmediay,double *Vmediaz, float delta_t){
	X[indice(i,j+1)]= X[indice(i,j)]+ Vmediax[indice(i,j+0.5)]*delta_t;
	Y[indice(i,j+1)]= Y[indice(i,j)]+ Vmediay[indice(i,j+0.5)]*delta_t;
	Z[indice(i,j+1)]= Z[indice(i,j)]+ Vmediaz[indice(i,j+0.5)]*delta_t;

}




     




                                                                                                                                
