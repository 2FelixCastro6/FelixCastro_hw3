
Resultados_hw3.pdf : Resultados_hw3.tex  Onda.pdf trayectorias.pdf
	pdflatex Resultados_hw3.tex

Onda.pdf : Onda.py
	python Onda.py 

trayectorias.pdf : Plots_Planetas.py
	python  Plots_Planetas.py


Plots_Planetas.py : datos.txt Planetas.x
	./Planetas.x > posiciones.txt 

Planetas.x : Planetas.c
	cc -lm Planetas.c -o Planetas.x

 


