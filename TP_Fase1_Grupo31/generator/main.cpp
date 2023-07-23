#include <iostream>
#include <string>
#include <fstream>
#define _USE_MATH_DEFINES
#include <math.h>
using namespace std;




void sphere(float radius, int slices, int stacks, string namefile) {
    ofstream MyFile("C:/Users/jonny/OneDrive/Ambiente de Trabalho/CG_22/Trabalho_Pratico_Novo/engine/"+namefile);
    //MyFile.open(namefile, ios::out | ios::binary);

    int tt_vertices = 6*stacks*slices,i,j;
    
    MyFile << tt_vertices << endl;

    // Write to the file
    double alpha = (2 * M_PI) / slices, beta =  M_PI / stacks, angle = -M_PI/2 ;
			
			for (i = 0; i < slices; i++) {
				for(j = 0; j < stacks; j++){
					//x = radius * sin(beta * i);

					//Base de baixo
					MyFile << radius * cos(angle - (beta * j))*cos(alpha * i) << " " << radius * sin(angle - (beta * j)) << " " << radius* cos(angle - (beta * j))*sin(alpha * i) << endl;
					MyFile <<  radius * cos(angle - (beta * (j+1))) * cos(alpha * i) << " " << radius * sin(angle - (beta * (j + 1))) << " " << radius * cos(angle - (beta * (j + 1))) * sin(alpha * i)<< endl;
					MyFile <<  radius * cos(angle - (beta * (j+1))) * cos(alpha * (i+1)) << " " << radius * sin(angle - (beta * (j + 1))) << " " << radius * cos(angle - (beta * (j + 1))) * sin(alpha * (i+1))<< endl;

					MyFile <<  radius * cos(angle - (beta * j)) * cos(alpha * (i+1)) << " " << radius * sin(angle - (beta * j)) << " " << radius * cos(angle - (beta * j)) * sin(alpha*(i+1))<< endl;
					MyFile <<  radius * cos(angle - (beta * j)) * cos(alpha*i) << " " << radius * sin(angle - (beta * j)) << " " << radius * cos(angle - (beta * j)) * sin(alpha*i)<< endl;
					MyFile <<  radius * cos(angle - (beta * (j + 1))) * cos(alpha * (i+1)) << " " << radius * sin(angle - (beta * (j + 1))) << " " << radius * cos(angle - (beta * (j + 1))) * sin(alpha * (i + 1))<< endl;
                

				}
			}

    // Close the file
    MyFile.close();
    cout << "Escreveu a esfera";
    }




void plane(float length,float divisions,string namefile) {
     ofstream Myfile("C:/Users/jonny/OneDrive/Ambiente de Trabalho/CG_22/Trabalho_Pratico_Novo/engine/"+namefile);
    //MyFile.open(namefile, ios::out | ios::binary);
    float x = length , y = length, z = length;
    float divX = length / divisions;
	float divY = length / divisions;
	float divZ = length / divisions;

    int tt_vertices = 6*divisions*divisions;
    
    Myfile << tt_vertices << endl;

	for (float i = -x / 2; i < x / 2; i += divX) {
		for (float j = -z / 2; j < z / 2; j += divZ) {
            
			Myfile << i <<" "<< 0.0f <<" "<< j << endl;
			Myfile << i + divX <<" "<< 0.0f <<" "<< j + divZ << endl;
			Myfile << i + divX <<" "<< 0.0f <<" "<< j << endl;


			Myfile << i <<" "<< 0.0f <<" "<< j << endl;
			Myfile << i <<" "<< 0.0f <<" "<< j + divZ << endl;
			Myfile << i + divX <<" "<< 0.0f <<" "<< j + divZ << endl;

		}

	}
    Myfile.close();
    cout << "Escreveu o plano";
}


void box(float length, float divisions, string namefile) {
    ofstream Myfile("C:/Users/jonny/OneDrive/Ambiente de Trabalho/CG_22/Trabalho_Pratico_Novo/engine/"+namefile);
    //MyFile.open(namefile, ios::out | ios::binary);
    float x = length , y = length, z = length;
    float divX = length / divisions;
	float divY = length / divisions;
	float divZ = length / divisions;

    int tt_vertices = 6*divisions*divisions*6;
    
    Myfile << tt_vertices << endl;

	for (float i = -x / 2; i < x / 2; i += divX) {
		for (float j = -y / 2; j < y / 2; j += divY) {
			Myfile << i <<" "<< j <<" "<< z / 2 << endl;                    // P1        
			Myfile << i + divX <<" "<< j <<" "<< z / 2 << endl;            // p2
			Myfile << i + divX <<" "<< j + divY <<" "<< z / 2 << endl;  // p4

			Myfile << i <<" "<< j <<" "<< z / 2 << endl;                // p1
			Myfile << i + divX <<" "<< j + divY <<" "<< z / 2 << endl;    // p3
			Myfile << i <<" "<< j + divY <<" "<< z / 2 << endl;            // p4
		}
	}

	for (float i = -x / 2; i < x / 2; i += divX) {
		for (float j = -y / 2; j < y / 2; j += divY) {
			Myfile << i <<" "<< j <<" "<< -z / 2 << endl;
			Myfile << i + divX <<" "<< j + divY <<" "<< -z / 2 << endl;
			Myfile << i + divX <<" "<< j <<" "<< -z / 2 << endl;

			Myfile << i <<" "<< j <<" "<< -z / 2 << endl;
			Myfile << i <<" "<< j + divY <<" "<< -z / 2 << endl;
			Myfile << i + divX <<" "<< j + divY <<" "<< -z / 2 << endl;

		}
	}

	for (float i = -x / 2; i < x / 2; i += divX) {
		for (float j = -z / 2; j < z / 2; j += divZ) {
			Myfile << i <<" "<< y / 2 <<" "<< j << endl;
			Myfile << i + divX <<" "<< y / 2 <<" "<< j + divZ << endl;
			Myfile << i + divX <<" "<< y / 2 <<" "<< j << endl;


			Myfile << i <<" "<< y / 2 <<" "<< j << endl;
			Myfile << i <<" "<< y / 2 <<" "<< j + divZ << endl;
			Myfile << i + divX <<" "<< y / 2 <<" "<< j + divZ << endl;

		}

	}
	for (float i = -x / 2; i < x / 2; i += divX) {
		for (float j = -z / 2; j < z / 2; j += divZ) {
			Myfile << i <<" "<< -y / 2 <<" "<< j << endl;
			Myfile << i + divX <<" "<< -y / 2 <<" "<< j << endl;
			Myfile << i + divX <<" "<< -y / 2 <<" "<< j + divZ << endl;

			Myfile << i <<" "<< -y / 2 <<" "<< j << endl;
			Myfile << i + divX <<" "<< -y / 2 <<" "<< j + divZ << endl;
			Myfile << i <<" "<< -y / 2 <<" "<< j + divZ << endl;
		}

	}
	for (float i = -y / 2; i < y / 2; i += divY) {
		for (float j = -z / 2; j < z / 2; j += divZ) {
			Myfile << x / 2 <<" "<< i <<" "<< j << endl;                    // P1        
			Myfile << x / 2 <<" "<< i + divY <<" "<< j << endl;            // p2
			Myfile << x / 2 <<" "<< i + divY <<" "<< j + divZ << endl;  // p4

			Myfile << x / 2 <<" "<< i <<" "<< j << endl;                // p1
			Myfile << x / 2 <<" "<< i + divY <<" "<< j + divZ << endl;    // p3
			Myfile << x / 2 <<" "<< i <<" "<< j + divZ << endl;            // p4
		}
	}

	for (float i = -y / 2; i < y / 2; i += divY) {
		for (float j = -z / 2; j < z / 2; j += divZ) {
			Myfile << -x / 2 <<" "<< i <<" "<< j << endl;                    // P1        
			Myfile << -x / 2 <<" "<< i + divY <<" "<< j + divZ << endl;  // p4
			Myfile << -x / 2 <<" "<< i + divY <<" "<< j << endl;            // p2

			Myfile << -x / 2 <<" "<< i <<" "<< j << endl;                // p1
			Myfile << -x / 2 <<" "<< i <<" "<< j + divZ << endl;            // p4
			Myfile << -x / 2 <<" "<< i + divY <<" "<< j + divZ << endl;    // p3
		}
	}
    

    Myfile.close();
    cout << "Escreveu a caixa";
}



void cone(float radius,float height, int slices, int stacks,string namefile) {
    
    
	float raio = radius / stacks;
	float heights = height / stacks;

    ofstream MyFile("C:/Users/jonny/OneDrive/Ambiente de Trabalho/CG_22/Trabalho_Pratico_Novo/engine/"+namefile);

    int tt_vertices = (6*slices * stacks) + (3*slices)  ,i,j;

    
	MyFile << tt_vertices << endl;

	double alpha = (2 * M_PI) / slices;
	for (i = 0; i < slices; i++) {
		//Base de baixo
		MyFile << radius * cos(alpha * i) <<" "<< -height/2 <<" "<< radius * sin(alpha * i) << endl;
		MyFile<< radius * cos(alpha * (i + 1)) <<" "<< -height/2 <<" "<< radius * sin(alpha * (i + 1)) << endl;
		MyFile<< 0.0f <<" "<< -height/2 <<" "<< 0.0f << endl;

		//Laterais
		for(j = 0; j < stacks; j++){
			MyFile<< (raio*j) * cos(alpha * i) <<" "<< (height/2) - (j * heights) <<" "<< (raio * j) * sin(alpha * i) << endl;
			MyFile<< (raio * (j + 1)) * cos(alpha * (i + 1)) <<" "<< (height/2) - ((j + 1) * heights) <<" "<< (raio * (j + 1)) * sin(alpha * (i + 1)) << endl;
			MyFile<< (raio * (j + 1)) * cos(alpha * i) <<" "<< (height/2) - ((j+1) * heights) <<" "<< (raio * (j+1)) * sin(alpha * i) << endl;
			
			
			MyFile<< (raio*j) * cos(alpha * i) <<" "<< (height/2) - (j * heights) <<" "<< (raio * j) * sin(alpha * i) << endl;
			MyFile<< (raio*j) * cos(alpha * (i+1)) <<" "<< (height/2) - (j * heights) <<" "<< (raio * j) * sin(alpha * (i+1)) << endl;
			MyFile<< (raio * (j + 1)) * cos(alpha * (i + 1)) <<" "<< (height/2) - ((j + 1) * heights) <<" "<< (raio * (j + 1)) * sin(alpha * (i + 1)) << endl;

		}
    }
    MyFile.close();

    cout << "Escreveu o cone";
     
    }




void end() {
    std::cout << "Erro";
    exit(1);
    //ACABA TUDO
}

void erroArgs(){
    cout << "Argumentos insuficientes.";
}


void handlePlane(int argc, char* argv[],string namefile){
    float length = stoi (argv[2]);
    float divisions = stoi (argv[3]);
    plane(length,divisions,namefile);
}

void handleCone(int argc, char* argv[],string namefile){
    float radius = stoi (argv[2]);
    float height = stoi (argv[3]);
    int slices = atoi (argv[4]);
    int stacks = atoi (argv[5]);
    cone(radius,height,slices,stacks,namefile);
}

void handleBox(int argc, char* argv[],string namefile){
        float length = stof(argv[2]);
        float divisions = stof(argv[3]);
        box(length,divisions, namefile);
}

void handleSphere(int argc, char* argv[],string namefile){
    float radius = stof(argv[2]);
    int slices = atoi(argv[3]);
    int stacks = atoi(argv[4]);
    sphere(radius,slices,stacks,namefile);
}

void handler(int argc, char* argv[]){
    string p = "plane";
    string b = "box";
    string s = "sphere";
    string c = "cone";
    string comm = argv[1];
    string namefile = argv[argc-1];
    //cout << namefile;
    int file = namefile.length();
    string check = namefile.substr(file-3,file);
    if(check.compare(".3d") == 0){
        if(b.compare(comm) == 0) {
            if(argc == 5)handleBox(argc,argv,namefile);
            else erroArgs();
        }
        else if(c.compare(comm) == 0) {
            //cout << argc;
            if(argc == 7) handleCone(argc,argv,namefile);
            else erroArgs();
        }
        else if(p.compare(comm) == 0) {
            if(argc == 5)handlePlane(argc,argv,namefile);
            else erroArgs();
        }
        else if (s.compare(comm) == 0) {
            if(argc == 6)handleSphere(argc,argv,namefile);
            else erroArgs();
        }
        else end();

    }
    else end();
}


int main(int argc, char* argv[]) {
    
    handler(argc,argv);
}