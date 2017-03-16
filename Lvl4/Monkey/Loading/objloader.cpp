#include <vector>
#include <stdio.h>
#include <string>
#include <cstring>
#include <glm/glm.hpp>
#include <objloader.h>
using namespace std;
using namespace glm;


bool loadOBJ(const char * path, 
	vector<vec3> & out_vs, 
    vector<vec2> & out_uvs,
	vector<vec3> & out_ns){


	vector<unsigned int> vIndices, uvIndices, nIndices;
	vector<vec3> temp_vs, temp_ns; vector<vec2> temp_uvs;
	 

	FILE * file = fopen(path, "r");
	if( file == NULL ){
		printf("Impossible to open the file ! \n");
		getchar();
		return false;
	}

	while (true){

		char lineHeader[128];
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF) break; 


		if (strcmp(lineHeader, "v") == 0){
			vec3 v;
			fscanf(file, "%f %f %f\n", &v.x, &v.y, &v.z );
            temp_vs.push_back(v);

		} else if (strcmp(lineHeader, "vt") == 0){
			vec2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y );
			uv.y = -uv.y; 
			temp_uvs.push_back(uv);

		} else if (strcmp( lineHeader, "vn" ) == 0){
			vec3 n;
			fscanf(file, "%f %f %f\n", &n.x, &n.y, &n.z );
			temp_ns.push_back(n);

		} else if(strcmp( lineHeader, "f" ) == 0){
			string vertex1, vertex2, vertex3;
			unsigned int vIndex[3], uvIndex[3], nIndex[3];
			int matches=fscanf(file,"%d/%d/%d %d/%d/%d %d/%d/%d\n",
                    &vIndex[0], &uvIndex[0], &nIndex[0],
                    &vIndex[1], &uvIndex[1], &nIndex[1],
                    &vIndex[2], &uvIndex[2], &nIndex[2]);
			
            if (matches < 6){
				printf("File can't be read by our parser\n");
				return false;
			}

			vIndices .push_back(vIndex[0]);
			vIndices .push_back(vIndex[1]);
			vIndices .push_back(vIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
            nIndices .push_back(nIndex[0]);
			nIndices .push_back(nIndex[1]);
			nIndices .push_back(nIndex[2]);

		} else {
			// Probably a comment, eat up the rest of the line
			char stupidBuffer[1000];
			fgets(stupidBuffer, 1000, file);
		}

	}

	// For each vertex of each triangle
	for( unsigned int i=0; i<vIndices.size(); i++ ){

		// Get the indices of its attributes
		unsigned int vIndex = vIndices[i];
		unsigned int uvIndex = uvIndices[i];
        unsigned int nIndex = nIndices[i];
		
		// Get the attributes thanks to the index
		vec3 v = temp_vs[vIndex-1];
		vec2 uv = temp_uvs[uvIndex-1];
        vec3 n = temp_ns[nIndex-1];
		
		// Put the attributes in buffers
		out_vs .push_back(v);
		out_uvs.push_back(uv);
        out_ns .push_back(n);
	
	}

	return true;
}
