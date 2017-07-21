#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
int indice(int i,int j);
float aceleracionx(int i,int j, double *masas, double *X,double *Y,double *Z, float G);
float aceleraciony(int i,int j, double *masas, double *X,double *Y,double *Z, float G);
float aceleracionz(int i,int j, double *masas, double *X,double *Y,double *Z, float G);
void velocidadmedia(int i,int j,double *Vx,double *Vy,double *Vz,double *Vmediax, double *Vmediay,double *Vmediaz,float ax,float ay,float az, float delta_t);
void velocidad(int i,int j, double *Vx,double *Vy,double *Vz,double *Vmediax, double *Vmediay,double *Vmediaz,float axuno,float ayuno ,float azuno, float delta_t);
void posicion(int i,int j,double *X,double *Y,double *Z,double *Vmediax, double *Vmediay,double *Vmediaz, float delta_t);

int main(void){

	FILE*file;
	file=fopen("coordinates.csv","r");
	
	int len=250;
	char line_buffer[len];
	char *split_buffer;
	const char *delimiter;
	delimiter=",";
	float matrizdatos[10][7];
	int i=0;
	int j=0;
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
	fclose(file);

	float delta_t=0.1;
	int n=2000;
	float G= 4*pow(3.14159265358979323846, 2);

	double *masas=malloc(10*sizeof(double));
	double *Vmediax= malloc(10*sizeof(double));
	double *Vmediay= malloc(10*sizeof(double));
	double *Vmediaz= malloc(10*sizeof(double));
	
	double *X= malloc((n*10)*sizeof(double));
	double *Y= malloc((n*10)*sizeof(double));
	double *Z= malloc((n*10)*sizeof(double));

	double *Vx= malloc((n*10)*sizeof(double));
	double *Vy= malloc((n*10)*sizeof(double));
	double *Vz= malloc((n*10)*sizeof(double));

	for(i=0; i<=9;i++){
	masas[i]= (matrizdatos[i][0]/matrizdatos[0][0]);
	X[i]= matrizdatos[i][1];
	Y[i]= matrizdatos[i][2];
	Z[i]= matrizdatos[i][3];
	Vx[i]= matrizdatos[i][4];
	Vy[i]= matrizdatos[i][5];
	Vz[i]= matrizdatos[i][6];
	}
	//printf("%lf\n",masas[3]);
	float ax;
	float ay;
	float az;
	float axuno;
	float ayuno;
	float azuno;
	for(i=0; i<=9;i++){	
		for(j=0;j<=n-1;j++){
			ax=aceleracionx(i,j,masas,X,Y,Z,G);
			ay=aceleraciony(i,j,masas,X,Y,Z,G);
			az=aceleracionz(i,j,masas,X,Y,Z,G);

			axuno=aceleracionx(i,(j+1),masas,X,Y,Z,G);
			ayuno=aceleraciony(i,(j+1),masas,X,Y,Z,G);
			azuno=aceleracionz(i,(j+1),masas,X,Y,Z,G);

			velocidadmedia(i,j,Vx,Vy,Vz,Vmediax,Vmediay,Vmediaz,ax,ay,az,delta_t);
			velocidad(i,j,Vx,Vy,Vz,Vmediax,Vmediay,Vmediaz,axuno,ayuno,azuno,delta_t);
			posicion(i,j,X,Y,Z,Vmediax,Vmediay,Vmediaz,delta_t);
			
		}
	}	
//printf("%lf %lf %lf\n",X,Y,Z);
return 0;
}

	


int indice(int i,int j){
	return ((2000*i)+j);
	}

float aceleracionx(int i,int j, double *masas, double *X,double *Y,double *Z, float G ){
	float factor;	
	float *a;
	float ax;
	int k=0;
	for(k; k<=9; k+1){
		if(i !=k){
			float x=X[indice(i,j)]-X[indice(k,j)];
			float y=Y[indice(i,j)]-Y[indice(k,j)];
			float z=Z[indice(i,j)]-Z[indice(k,j)];
			float suma=pow(x, 2)+pow(y, 2)+pow(z, 2);		
			factor=-G*masas[i]*masas[k]/pow(suma, 1.5);
			a[k]=factor*x;
			ax=ax+a[k];
		}		
	}	
return ax/masas[i];
}

float aceleraciony(int i,int j, double *masas, double *X,double *Y,double *Z, float G ){
	float factor;	
	float *b;
	float ay;
	int k=0;
	for(k; k<=9; k+1){
		if(i !=k){
			float x=X[indice(i,j)]-X[indice(k,j)];
			float y=Y[indice(i,j)]-Y[indice(k,j)];
			float z=Z[indice(i,j)]-Z[indice(k,j)];
			float suma=pow(x,2)+pow(y,2)+pow(z,2);		
			factor=-G*masas[i]*masas[k]/pow(suma,1.5);
			b[k]=factor*y;
			ay=ay+b[k];
		}		
	}	
return ay/masas[i];

}
float aceleracionz(int i,int j, double *masas, double *X,double *Y,double *Z, float G ){
	float factor;	
	float *c;
	float az;
	int k=0;
	for(k; k<=9; k+1){
		if(i !=k){
			float x=X[indice(i,j)]-X[indice(k,j)];
			float y=Y[indice(i,j)]-Y[indice(k,j)];
			float z=Z[indice(i,j)]-Z[indice(k,j)];
			float suma=pow(x,2)+pow(y,2)+pow(z,2);		
			factor=-G*masas[i]*masas[k]/pow(suma,1.5);
			c[k]=factor*z;	
			az=az+c[k];
			
		}		
	}	
return az/masas[i];
}
void velocidadmedia(int i,int j,double *Vx,double *Vy,double *Vz,double *Vmediax, double *Vmediay,double *Vmediaz,float ax,float ay,float az, float delta_t){
	Vmediax[i]=Vx[indice(i,j)]+ 0.5*ax*delta_t;
	Vmediay[i]=Vy[indice(i,j)]+ 0.5*ay*delta_t;
	Vmediaz[i]=Vz[indice(i,j)]+ 0.5*az*delta_t;
}

void velocidad(int i,int j, double *Vx,double *Vy,double *Vz,double *Vmediax, double *Vmediay,double *Vmediaz,float axuno,float ayuno ,float azuno, float delta_t){
	Vx[indice(i,j+1)]= Vmediax[indice(i,j)]+ 0.5*axuno*delta_t;
	Vy[indice(i,j+1)]= Vmediay[indice(i,j)]+ 0.5*ayuno*delta_t;
	Vz[indice(i,j+1)]= Vmediaz[indice(i,j)]+ 0.5*azuno*delta_t;	
}

void posicion(int i,int j,double *X,double *Y,double *Z,double *Vmediax, double *Vmediay,double *Vmediaz, float delta_t){
	X[indice(i,j+1)]= X[indice(i,j)]+ Vmediax[indice(i,j)]*delta_t;
	Y[indice(i,j+1)]= Y[indice(i,j)]+ Vmediay[indice(i,j)]*delta_t;
	Z[indice(i,j+1)]= Z[indice(i,j)]+ Vmediaz[indice(i,j)]*delta_t;

}




     




                                                                                                                                
