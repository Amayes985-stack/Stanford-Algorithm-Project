#
# Makefile for non-Microsoft compilers
#

execute: 

	g++ -o graph_parameters_PNG graph_analysis_PNG.cpp -I/workspaces/Stanford-Algorithm-Project/snap-core -I/workspaces/Stanford-Algorithm-Project/glib-core -lsnap -lrt -fopenmp
	g++ -o graph_parameters_PUNG graph_analysis_PUNG.cpp -I/workspaces/Stanford-Algorithm-Project/snap-core -I/workspaces/Stanford-Algorithm-Project/glib-core -lsnap -lrt -fopenmp

	./graph_parameters_PNG > result_png.txt
	./graph_parameters_PUNG > result_pung.txt 

generate_graphs : 

	python3 csv_to_txt_twitch.py 
	python3 csv_to_txt_github.py
	python3 csv_to_txt_wikipedia.py
	python3 csv_to_txt_facebook.py

clean : 

	rm -r graph_parameters_PNG
	rm -r graph_parameters_PUNG
	
	


